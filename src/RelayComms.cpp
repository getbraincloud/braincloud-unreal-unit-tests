// Copyright 2020 bitHeads, Inc. All Rights Reserved.

#include <braincloud/BrainCloudClient.h>
#include <braincloud/IRelayConnectCallback.h>
#include <braincloud/IRelayCallback.h>
#include <braincloud/IRelaySystemCallback.h>

#include "braincloud/internal/IRelayTCPSocket.h"
#if (TARGET_OS_WATCH != 1)
#include "braincloud/internal/IWebSocket.h"
#endif
#include "braincloud/internal/RelayComms.h"

#include <iostream>
#include <cstring>
#if !defined(WIN32)
#include <arpa/inet.h>
#endif

static const int CONTROL_BYTES_SIZE = 1;
static const int MAX_PACKET_ID_HISTORY = 128;

static const int MAX_PLAYERS = 128;
static const int INVALID_NET_ID = MAX_PLAYERS;

// Messages sent from Client to Relay-Server
static const int CL2RS_CONNECTION = 129;
static const int CL2RS_DISCONNECT = 130;
static const int CL2RS_RELAY = 131;
static const int CL2RS_PING = 133;
static const int CL2RS_RSMG_ACKNOWLEDGE = 134;
static const int CL2RS_ACKNOWLEDGE = 135;

// Messages sent from Relay-Server to Client
static const int RS2CL_RSMG = 129;
static const int RS2CL_PONG = CL2RS_PING;
static const int RS2CL_ACKNOWLEDGE = CL2RS_ACKNOWLEDGE;

static const int RELIABLE_BIT = 0x8000;
static const int ORDERED_BIT = 0x4000;

static const long CONNECT_RESEND_INTERVAL_MS = 500;

static const int MAX_PACKET_ID = 0xFFF;
static const int PACKET_LOWER_THRESHOLD = MAX_PACKET_ID * 25 / 100;
static const int PACKET_HIGHER_THRESHOLD = MAX_PACKET_ID * 75 / 100;

static const int MAX_PACKET_SIZE = 1024;

namespace BrainCloud
{
    RelayComms::RelayComms(BrainCloudClient* in_client)
        : m_client(in_client)
        , m_isInitialized(false)
    {
        m_isConnected = false;
        m_isSocketConnected = false;
        m_pingInterval = std::chrono::milliseconds(1000);

        for (int i = 0; i < CHANNEL_COUNT * 2; ++i)
        {
            m_sendPacketId[i] = 0;
        }
    }

    RelayComms::~RelayComms()
    {
        disconnect();
    }

    void RelayComms::initialize()
    {
        m_isInitialized = true;
    }

    bool RelayComms::isInitialized()
    {
        return m_isInitialized;
    }

    void RelayComms::shutdown()
    {
        resetCommunication();
        m_isInitialized = false;
    }

    void RelayComms::resetCommunication()
    {
        disconnect();
    }

    void RelayComms::enableLogging(bool shouldEnable)
    {
        m_loggingEnabled = shouldEnable;
    }

    void RelayComms::connect(eRelayConnectionType in_connectionType, const std::string& host, int port, const std::string& passcode, const std::string& lobbyId, IRelayConnectCallback* in_callback)
    {
        if (m_isSocketConnected)
        {
            disconnect();
        }

        m_connectionType = in_connectionType;
        m_connectOptions.host = host;
        m_connectOptions.port = port;
        m_connectOptions.passcode = passcode;
        m_connectOptions.lobbyId = lobbyId;
        m_pRelayConnectCallback = in_callback;
        m_ping = 999;
        m_pingInFlight = false;
        m_netId = -1;
        m_ownerProfileId.clear();
        m_profileIdToNetId.clear();
        m_netIdToProfileId.clear();

        switch (m_connectionType)
        {
            case eRelayConnectionType::TCP:
            {
                m_pSocket = IRelayTCPSocket::create(host, port, MAX_PACKET_SIZE);
                break;
            }
            default:
            {
                disconnect();
                queueErrorEvent("Protocol Unimplemented");
                break;
            }
        }
    }

    void RelayComms::disconnect()
    {
        m_isConnected = false;
        m_isSocketConnected = false;

        // Close socket
        delete m_pSocket;
        m_pSocket = nullptr;

        for (int i = 0; i < CHANNEL_COUNT * 2; ++i)
        {
            m_sendPacketId[i] = 0;
        }
    }

    bool RelayComms::isConnected() const
    {
        return m_isConnected;
    }

    int RelayComms::getPing() const
    {
        return m_ping;
    }

    void RelayComms::setPingInterval(int in_intervalMS)
    {
        m_pingInterval = std::chrono::milliseconds(in_intervalMS);
    }

    const std::string& RelayComms::getOwnerProfileId() const
    {
        return m_ownerProfileId;
    }

    const std::string& RelayComms::getProfileIdForNetId(int in_netId) const
    {
        auto it = m_netIdToProfileId.find(in_netId);
        if (it == m_netIdToProfileId.end())
        {
            static std::string empty;
            return empty;
        }
        return it->second;
    }

    int RelayComms::getNetIdForProfileId(const std::string& in_profileId) const
    {
        auto it = m_profileIdToNetId.find(in_profileId);
        if (it == m_profileIdToNetId.end()) return INVALID_NET_ID;
        return it->second;
    }

    void RelayComms::registerRelayCallback(IRelayCallback* in_callback)
    {
        m_pRelayCallback = in_callback;
    }

    void RelayComms::deregisterRelayCallback()
    {
        m_pRelayCallback = nullptr;
    }

    void RelayComms::registerSystemCallback(IRelaySystemCallback* in_callback)
    {
        m_pSystemCallback = in_callback;
    }

    void RelayComms::deregisterSystemCallback()
    {
        m_pSystemCallback = nullptr;
    }

    Json::Value RelayComms::buildConnectionRequest()
    {
        Json::Value request;

        request["lobbyId"] = m_connectOptions.lobbyId;
        request["profileId"] = m_client->getAuthenticationService()->getProfileId();
        request["passcode"] = m_connectOptions.passcode;

        return request;
    }

    void RelayComms::send(const uint8_t* in_data, int in_size, int in_toNetId, bool in_reliable, bool in_ordered, eRelayChannel in_channel)
    {
        // Allocate buffer
        auto totalSize = in_size + 5;
        static std::vector<uint8_t> buffer;
        buffer.resize(totalSize);

        // Size
        auto len = htons((u_short)totalSize);
        memcpy(buffer.data(), &len, 2);

        // NetId
        buffer[2] = (uint8_t)in_toNetId;

        // Reliable header
        uint16_t rh = 0;
        if (in_reliable) rh |= RELIABLE_BIT;
        if (in_ordered) rh |= ORDERED_BIT;
        rh |= (int)in_channel << 12;
        int channelIdx = (int)in_channel + (in_reliable ? 0 : CHANNEL_COUNT);
        int packetId = m_sendPacketId[channelIdx];
        rh |= packetId;
        m_sendPacketId[channelIdx] = (packetId + 1) & 0xFFF;
        auto rhBE = htons((u_short)rh);
        memcpy(buffer.data() + 3, &rhBE, 2);

        // Rest of data
        memcpy(buffer.data() + 5, in_data, in_size);

        // Send
        send(buffer.data(), (int)buffer.size());
    }

    void RelayComms::sendPing()
    {
        struct PingData
        {
            uint16_t size = (uint16_t)htons((u_short)5);
            uint8_t netId = CL2RS_PING;
            uint16_t ping = 999;
        } pingData;

        if (m_pingInFlight)
        {
            return;
        }
        pingData.ping = (uint16_t)htons((u_short)m_ping);;
        m_pingInFlight = true;
        m_lastPingTime = std::chrono::system_clock::now();

        if (m_loggingEnabled)
        {
            std::cout << "#RELAY SEND: PING " << std::endl;
        }

        send((uint8_t*)&pingData, 5);
    }

    void RelayComms::send(int netId, const Json::Value& json)
    {
        Json::FastWriter writer;
        send(netId, writer.write(json));
    }

    void RelayComms::send(int netId, const std::string& text)
    {
        if (m_loggingEnabled)
        {
            std::cout << "RELAY SEND: " << text << std::endl;
        }

        auto totalSize = text.length() + 3;
        std::vector<uint8_t> buffer(totalSize);
        auto len = htons((u_short)totalSize);
        memcpy(buffer.data(), &len, 2);
        buffer[2] = (uint8_t)netId;
        memcpy(buffer.data() + 3, text.data(), text.length());
        send(buffer.data(), (int)buffer.size());
    }

    void RelayComms::send(const uint8_t* in_data, int in_size)
    {
        if (m_pSocket)
        {
            m_pSocket->send(in_data, in_size);
        }
    }

    void RelayComms::onRecv(const uint8_t* in_data, int in_size)
    {
        if (in_size < 3)
        {
            disconnect();
            queueErrorEvent("Relay Recv Error: packet cannot be smaller than 3 bytes");
            return;
        }

        int size = (int)ntohs(*(u_short*)in_data);
        int netId = (int)in_data[2];

        if (size < in_size)
        {
            disconnect();
            queueErrorEvent("Relay Recv Error: Packet is smaller than header's size");
            return;
        }

        if (netId == RS2CL_RSMG)
        {
            onRSMG(in_data + 3, size - 3);
        }
        else if (netId == RS2CL_PONG)
        {
            onPONG();
        }
        else if (netId == RS2CL_ACKNOWLEDGE)
        {
            if (size < 5)
            {
                disconnect();
                queueErrorEvent("Relay Recv Error: ack packet cannot be smaller than 5 bytes");
                return;
            }
            if (m_connectionType == eRelayConnectionType::UDP)
            {
            }
        }
        else if (netId >= 0 && netId < MAX_PLAYERS)
        {
            if (size < 5)
            {
                disconnect();
                queueErrorEvent("Relay Recv Error: relay packet cannot be smaller than 5 bytes");
                return;
            }
            onRelay(in_data + 3, netId, in_size - 3);
        }
        else
        {
            disconnect();
            queueErrorEvent("Relay Recv Error: Unknown netId: " + std::to_string(netId));
        }
    }

    void RelayComms::onRSMG(const uint8_t* in_data, int in_size)
    {
        int rsmgPacketId = (int)ntohs(*(u_short*)in_data);

        if (m_connectionType == eRelayConnectionType::UDP)
        {
            // Ack
        }

        std::string jsonString((char*)in_data + 2, (char*)in_data + in_size);
        if (m_loggingEnabled)
        {
            std::cout << "RELAY System Msg: " << jsonString << std::endl;
        }

        Json::Value json;
        Json::Reader reader;
        reader.parse(jsonString, json);

        auto op = json["op"].asString();
        if (op == "CONNECT")
        {
            auto netId = json["netId"].asInt();
            auto profileId = json["profileId"].asString();
            {
                m_netIdToProfileId[netId] = profileId;
                m_profileIdToNetId[profileId] = netId;
            }
            if (profileId == m_client->getAuthenticationService()->getProfileId())
            {
                m_netId = netId;
                m_ownerProfileId = json["ownerId"].asString();
                m_lastPingTime = std::chrono::system_clock::now();
                m_isConnected = true;
                queueConnectSuccessEvent(jsonString);
            }
        }
        else if (op == "NET_ID")
        {
            auto netId = json["netId"].asInt();
            auto profileId = json["profileId"].asString();

            m_netIdToProfileId[netId] = profileId;
            m_profileIdToNetId[profileId] = netId;
        }
        else if (op == "MIGRATE_OWNER")
        {
            auto profileId = json["profileId"].asString();
            m_ownerProfileId = profileId;
        }

        queueSystemEvent(jsonString);
    }

    void RelayComms::onPONG()
    {
        if (m_pingInFlight)
        {
            m_pingInFlight = false;
            m_ping = (int)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - m_lastPingTime).count();
            if (m_loggingEnabled)
            {
                std::cout << "RELAY PONG: " << m_ping << std::endl;
            }
        }
    }

    void RelayComms::onRelay(const uint8_t* in_data, int netId, int in_size)
    {
        auto rh = (int)ntohs(*(u_short*)in_data);
        auto reliable = rh & RELIABLE_BIT ? true : false;
        auto ordered = rh & ORDERED_BIT ? true : false;
        auto channel = (rh >> 12) & 0x3;
        auto packetId = rh & 0xFFF;
        auto channelIdx = channel + (reliable ? 0 : CHANNEL_COUNT);

        // Ack reliables, always. An ack might have been previously dropped.
        if (m_connectionType == eRelayConnectionType::UDP)
        {
        }

        queueRelayEvent(netId, in_data + 2, in_size - 2);
    }

    void RelayComms::runCallbacks()
    {
        // Update socket
        if (m_pSocket)
        {
            if (m_pSocket->isConnected())
            {
                // Peek messages
                int packetSize;
                const uint8_t* pPacketData;
                while (pPacketData = m_pSocket->peek(packetSize))
                {
                    onRecv(pPacketData, packetSize);
                }
            }
            else if (!m_pSocket->isValid())
            {
                disconnect();
                queueErrorEvent("Relay Socket Error: failed to connect");
            }
            else
            {
                m_pSocket->updateConnection();
                if (m_pSocket->isConnected())
                {
                    m_isSocketConnected = true;
                    if (m_loggingEnabled)
                    {
                        std::cout << "Relay Socket Connected" << std::endl;
                    }
                    send(CL2RS_CONNECTION, buildConnectionRequest());
                }
            }
        }

        // Perform event callbacks
        {
            auto eventsCopy = m_events;
            m_events.clear();
            for (const auto& evt : eventsCopy)
            {
                switch (evt.type)
                {
                    case EventType::ConnectSuccess:
                        if (m_pRelayConnectCallback)
                        {
                            m_pRelayConnectCallback->relayConnectSuccess(evt.message);
                        }
                        break;
                    case EventType::ConnectFailure:
                        if (m_pRelayConnectCallback)
                        {
                            m_pRelayConnectCallback->relayConnectFailure(evt.message);
                        }
                        break;
                    case EventType::System:
                        if (m_pSystemCallback)
                        {
                            m_pSystemCallback->relaySystemCallback(evt.message);
                        }
                        break;
                    case EventType::Relay:
                        if (m_pRelayCallback)
                        {
                            m_pRelayCallback->relayCallback(evt.netId, evt.data.data(), (int)evt.data.size());
                        }
                        break;
                }
            }
        }

        if (m_connectionType == eRelayConnectionType::UDP)
        {
            // Resend connection packet

            // Resend reliables
 
        }

        // Ping. Which also works as an heartbeat
        if (m_isConnected)
        {
            if (std::chrono::system_clock::now() - m_lastPingTime >= m_pingInterval)
            {
                sendPing();
            }
        }
    }

    void RelayComms::queueConnectSuccessEvent(const std::string& jsonString)
    {
        m_events.push_back({ EventType::ConnectSuccess, jsonString });
    }

    void RelayComms::queueErrorEvent(const std::string& message)
    {
        m_events.push_back({ EventType::ConnectFailure, message });
    }

    void RelayComms::queueSystemEvent(const std::string& jsonString)
    {
        m_events.push_back({ EventType::System, jsonString });
    }

    void RelayComms::queueRelayEvent(int netId, const uint8_t* pData, int size)
    {
        m_events.push_back({ EventType::Relay });
        auto& evt = m_events.back();
        evt.netId = netId;
        evt.data.assign(pData, pData + size);
    }
};
