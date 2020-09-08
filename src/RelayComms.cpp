// Copyright 2020 bitHeads, Inc. All Rights Reserved.

#include <braincloud/BrainCloudClient.h>
#include <braincloud/IRelayConnectCallback.h>
#include <braincloud/IRelayCallback.h>
#include <braincloud/IRelaySystemCallback.h>

#include "braincloud/internal/IRelayTCPSocket.h"
#include "braincloud/internal/IRelayUDPSocket.h"
#if (TARGET_OS_WATCH != 1)
#include "braincloud/internal/IWebSocket.h"
#endif
#include "braincloud/internal/RelayComms.h"

#include <algorithm>
#include <iostream>
#include <cstring>
#if !defined(WIN32)
#include <arpa/inet.h>
#endif

#define VERBOSE_LOG 0

static const int CONTROL_BYTES_SIZE = 1;
static const int MAX_PACKET_ID_HISTORY = 60 * 10; // So we last 10 seconds at 60 fps

static const int MAX_PLAYERS = 40;
static const int INVALID_NET_ID = MAX_PLAYERS;

// Messages sent from Client to Relay-Server
static const int CL2RS_CONNECT = 0;
static const int CL2RS_DISCONNECT = 1;
static const int CL2RS_RELAY = 2;
static const int CL2RS_ACK = 3;
static const int CL2RS_PING = 4;
static const int CL2RS_RSMG_ACK = 5;

// Messages sent from Relay-Server to Client
static const int RS2CL_RSMG = 0;
static const int RS2CL_DISCONNECT = 1;
static const int RS2CL_RELAY = 2;
static const int RS2CL_ACK = 3;
static const int RS2CL_PONG = 4;

static const int RELIABLE_BIT = 0x8000;
static const int ORDERED_BIT = 0x4000;

static const long CONNECT_RESEND_INTERVAL_MS = 500;
static const long MAX_RELIABLE_RESEND_INTERVAL_MS = 500;

static const int MAX_PACKET_ID = 0xFFF;
static const int PACKET_LOWER_THRESHOLD = MAX_PACKET_ID * 25 / 100;
static const int PACKET_HIGHER_THRESHOLD = MAX_PACKET_ID * 75 / 100;

static const int MAX_PACKET_SIZE = 1024;
static const int TIMEOUT_SECONDS = 10;

static const double RELIABLE_RESEND_INTERVALS[] = {
    50.0, 50.0, // High priority 1 and 2
    150.0,      // Normal priority
    500.0       // Low priority
};

namespace BrainCloud
{
    int RelayComms::Event::allocCount = 0;
    int RelayComms::Packet::allocCount = 0;

    RelayComms::RelayComms(BrainCloudClient* in_client)
        : m_client(in_client)
        , m_isInitialized(false)
    {
        m_isConnected = false;
        m_isSocketConnected = false;
        m_pingInterval = std::chrono::milliseconds(1000);
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
        m_sendPacketId.clear();
        m_recvPacketId.clear();
        m_reliables.clear();
        m_orderedReliablePackets.clear();
        m_eventPool.reclaim();
        m_packetPool.reclaim();
        m_rsmgHistory.clear();

        switch (m_connectionType)
        {
            case eRelayConnectionType::TCP:
            {
                m_pSocket = IRelayTCPSocket::create(host, port, MAX_PACKET_SIZE);
                break;
            }
            case eRelayConnectionType::UDP:
            {
                m_pSocket = IRelayUDPSocket::create(host, port, MAX_PACKET_SIZE);
                m_lastRecvTime = std::chrono::system_clock::now();
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
        m_resendConnectRequest = false;

        // Close socket
        delete m_pSocket;
        m_pSocket = nullptr;
        
        m_sendPacketId.clear();
        m_recvPacketId.clear();

        m_rsmgHistory.clear();
        m_reliables.clear();
        m_orderedReliablePackets.clear();
        m_packetPool.reclaim();
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
        request["version"] = m_client->getBrainCloudClientVersion();

        return request;
    }

    void RelayComms::send(const uint8_t* in_data, int in_size, uint64_t in_playerMask, bool in_reliable, bool in_ordered, eRelayChannel in_channel)
    {
        if (!isConnected()) return;
        if (in_size > 1024)
        {
            disconnect();
            queueErrorEvent("Relay Error: Packet is too big " + std::to_string(in_size) + " > max 1024");
            return;
        }

        // Allocate buffer
        auto totalSize = in_size + 11;
        auto pPacket = m_packetPool.alloc();
        pPacket->data.resize(totalSize);

        // Size
        auto len = htons((u_short)totalSize);
        memcpy(pPacket->data.data(), &len, 2);

        // NetId
        pPacket->data[2] = (uint8_t)CL2RS_RELAY;

        // Reliable header
        uint16_t rh = 0;
        if (in_reliable) rh |= RELIABLE_BIT;
        if (in_ordered) rh |= ORDERED_BIT;
        rh |= ((uint16_t)in_channel << 12) & 0x3000;

        // Store inverted player mask
        uint64_t playerMask = 0;
        for (uint64_t i = 0, len = (uint64_t)MAX_PLAYERS; i < len; ++i)
        {
            playerMask |= ((in_playerMask >> ((uint64_t)MAX_PLAYERS - i - 1)) & 1) << i;
        }
        playerMask = (playerMask << 8) & 0x0000FFFFFFFFFF00;

        // AckId without packet id
        uint64_t ackIdWithoutPacketId = (((uint64_t)rh << 48) & 0xFFFF000000000000) | playerMask;

        // Packet Id
        int packetId = 0;
        auto it = m_sendPacketId.find(ackIdWithoutPacketId);
        if (it != m_sendPacketId.end())
        {
            packetId = it->second;
        }
        m_sendPacketId[ackIdWithoutPacketId] = (packetId + 1) & MAX_PACKET_ID;

        // Add packet id to the header, then encode
        rh |= packetId;

        auto rhBE = htons((u_short)rh);
        auto playerMask0BE = (uint64_t)ntohs((u_short)((playerMask >> 32) & 0xFFFF));
        auto playerMask1BE = (uint64_t)ntohs((u_short)((playerMask >> 16) & 0xFFFF));
        auto playerMask2BE = (uint64_t)ntohs((u_short)((playerMask)       & 0xFFFF));
        memcpy(pPacket->data.data() + 3, &rhBE, 2);
        memcpy(pPacket->data.data() + 5, &playerMask0BE, 2);
        memcpy(pPacket->data.data() + 7, &playerMask1BE, 2);
        memcpy(pPacket->data.data() + 9, &playerMask2BE, 2);

        // Rest of data
        memcpy(pPacket->data.data() + 11, in_data, in_size);

        // Send
        send(pPacket->data.data(), (int)pPacket->data.size());

        // UDP, store reliable in send map
        if (in_reliable)
        {
            pPacket->id = packetId;
            pPacket->lastResendTime = std::chrono::system_clock::now();
            pPacket->timeSinceFirstSend = pPacket->lastResendTime;
            pPacket->resendInterval = RELIABLE_RESEND_INTERVALS[(int)in_channel];
            uint64_t ackId = *(uint64_t*)(pPacket->data.data() + 3);
            m_reliables[ackId] = pPacket;
        }
        else
        {
            m_packetPool.free(pPacket);
        }
    }

    void RelayComms::sendPing()
    {
        if (m_pingInFlight)
        {
            return;
        }

        m_pingInFlight = true;
        m_lastPingTime = std::chrono::system_clock::now();

        uint8_t data[5];
        *(uint16_t*)(data) = (uint16_t)htons((u_short)5);
        data[2] = CL2RS_PING;
        *(uint16_t*)(data + 3) = (uint16_t)htons((u_short)m_ping);
        send(data, 5);
    }

    void RelayComms::send(int netId, const Json::Value& json)
    {
        Json::FastWriter writer;
        send(netId, writer.write(json));
    }

    void RelayComms::send(int netId, const std::string& text)
    {
#if VERBOSE_LOG
        if (m_loggingEnabled)
        {
            std::cout << "RELAY SEND: " << text << std::endl;
        }
#endif

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
        m_lastRecvTime = std::chrono::system_clock::now();

        if (in_size < 3)
        {
            disconnect();
            queueErrorEvent("Relay Recv Error: packet cannot be smaller than 3 bytes");
            return;
        }

        int size = (int)ntohs(*(u_short*)in_data);
        int controlByte = (int)in_data[2];

        if (size < in_size)
        {
            disconnect();
            queueErrorEvent("Relay Recv Error: Packet is smaller than header's size");
            return;
        }

        if (controlByte == RS2CL_RSMG)
        {
            if (size < 5)
            {
                disconnect();
                queueErrorEvent("Relay Recv Error: RSMG cannot be smaller than 5 bytes");
                return;
            }
            onRSMG(in_data + 3, size - 3);
        }
        else if (controlByte == RS2CL_DISCONNECT)
        {
            disconnect();
            queueErrorEvent("Relay: Disconnected by server");
        }
        else if (controlByte == RS2CL_PONG)
        {
            onPONG();
        }
        else if (controlByte == RS2CL_ACK)
        {
            if (size < 11)
            {
                disconnect();
                queueErrorEvent("Relay Recv Error: ack packet cannot be smaller than 5 bytes");
                return;
            }
            if (m_connectionType == eRelayConnectionType::UDP)
            {
                onAck(in_data + 3);
            }
        }
        else if (controlByte == RS2CL_RELAY)
        {
            if (size < 11)
            {
                disconnect();
                queueErrorEvent("Relay Recv Error: relay packet cannot be smaller than 5 bytes");
                return;
            }
            onRelay(in_data + 3, in_size - 3);
        }
        else
        {
            disconnect();
            queueErrorEvent("Relay Recv Error: Unknown control byte: " + std::to_string(controlByte));
        }
    }

    void RelayComms::sendRSMGAck(int rsmgPacketId)
    {
#if VERBOSE_LOG
        if (m_loggingEnabled)
        {
            std::cout << "#RELAY SEND: RSMG ACK" << std::endl;
        }
#endif

        uint8_t data[5];
        *(uint16_t*)(data) = (uint16_t)htons((u_short)5);
        data[2] = CL2RS_RSMG_ACK;
        *(uint16_t*)(data + 3) = (uint16_t)htons((u_short)rsmgPacketId);
        send(data, 5);
    }

    void RelayComms::sendAck(const uint8_t* in_data)
    {
        uint8_t data[11];
        *(uint16_t*)(data) = (uint16_t)htons((u_short)11);
        data[2] = CL2RS_ACK;
        memcpy(data + 3, in_data, 8);
        send(data, 11);
    }

    void RelayComms::onRSMG(const uint8_t* in_data, int in_size)
    {
        int rsmgPacketId = (int)ntohs(*(u_short*)in_data);

        std::string jsonString((char*)in_data + 2, (char*)in_data + in_size);
        if (m_loggingEnabled)
        {
            std::cout << "RELAY System Msg: " << jsonString << std::endl;
        }

        if (m_connectionType == eRelayConnectionType::UDP)
        {
            // Send ack, always. Even if we already received it
            sendRSMGAck(rsmgPacketId);

            // If already received, we ignore
            for (int packetId : m_rsmgHistory)
            {
                if (packetId == rsmgPacketId)
                {
#if VERBOSE_LOG
                    if (m_loggingEnabled)
                    {
                        std::cout << "RELAY Duplicated System Msg" << std::endl;
                    }
#endif
                    return;
                }
            }

            // Add to history
            m_rsmgHistory.push_back(rsmgPacketId);

            // Crop to max history
            while ((int)m_rsmgHistory.size() > MAX_RSMG_HISTORY)
            {
                m_rsmgHistory.erase(m_rsmgHistory.begin());
            }
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
                m_resendConnectRequest = false;
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
        else if (op == "DISCONNECT")
        {
            auto profileId = json["profileId"].asString();
            auto myProfileId = m_client->getAuthenticationService()->getProfileId();
            if (myProfileId == profileId)
            {
                // We are the one that got disconnected!
                disconnect();
                queueErrorEvent("Disconnected by server");
                return;
            }
        }

        queueSystemEvent(jsonString);
    }

    void RelayComms::onPONG()
    {
        if (m_pingInFlight)
        {
            m_pingInFlight = false;
            m_ping = (int)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - m_lastPingTime).count();
#if VERBOSE_LOG
            if (m_loggingEnabled)
            {
                std::cout << "RELAY PONG: " << m_ping << std::endl;
            }
#endif
        }
    }

    void RelayComms::onAck(const uint8_t* in_data)
    {
        auto ackId = *(uint64_t*)in_data;
        auto it = m_reliables.find(ackId);
        if (it != m_reliables.end())
        {
            auto pPacket = it->second;
#if VERBOSE_LOG
            if (m_loggingEnabled)
            {
                auto rh = (int)ntohs(*(u_short*)in_data);
                auto packetId = rh & 0xFFF;
                std::cout << "Acked packet id: " << packetId << std::endl;
            }
#endif
            m_packetPool.free(pPacket);
            m_reliables.erase(it);
        }
    }

    static bool packetLE(int a, int b)
    {
        if (a > PACKET_HIGHER_THRESHOLD && b <= PACKET_LOWER_THRESHOLD)
        {
            return true;
        }
        if (b > PACKET_HIGHER_THRESHOLD && a <= PACKET_LOWER_THRESHOLD)
        {
            return false;
        }
        return a <= b;
    }

    void RelayComms::onRelay(const uint8_t* in_data, int in_size)
    {
        auto rh = (int)ntohs(*(u_short*)in_data);
        auto playerMask0 = (uint64_t)ntohs(*(u_short*)(in_data + 2));
        auto playerMask1 = (uint64_t)ntohs(*(u_short*)(in_data + 4));
        auto playerMask2 = (uint64_t)ntohs(*(u_short*)(in_data + 6));
        auto ackId = 
            (((uint64_t)rh << 48)          & 0xFFFF000000000000) |
            (((uint64_t)playerMask0 << 32) & 0x0000FFFF00000000) |
            (((uint64_t)playerMask1 << 16) & 0x00000000FFFF0000) |
            (((uint64_t)playerMask2)       & 0x000000000000FFFF);
        uint64_t ackIdWithoutPacketId = ackId & 0xF000FFFFFFFFFFFF;
        auto reliable = rh & RELIABLE_BIT ? true : false;
        auto ordered = rh & ORDERED_BIT ? true : false;
        auto channel = (rh >> 12) & 0x3;
        auto packetId = rh & 0xFFF;
        auto netId = (uint8_t)(playerMask2 & 0x00FF);

        // Reconstruct ack id without packet id
        if (m_connectionType == eRelayConnectionType::UDP)
        {
            // Ack reliables, always. An ack might have been previously dropped.
            if (reliable)
            {
                sendAck(in_data);
            }

            if (ordered)
            {
                int prevPacketId = MAX_PACKET_ID;
                auto it = m_recvPacketId.find(ackIdWithoutPacketId);
                if (it != m_recvPacketId.end())
                {
                    prevPacketId = it->second;
                }

                if (reliable)
                {
                    if (packetLE(packetId, prevPacketId))
                    {
                        // We already received that packet if it's lower than the last confirmed
                        // packetId. This must be a duplicate
#if VERBOSE_LOG
                        if (m_loggingEnabled)
                        {
                            std::cout << "Duplicated packet from " << (int)netId << ". got " << packetId << std::endl;
                        }
#endif
                        return;
                    }

                    // Check if it's out of order, then save it for later
                    auto& orderedReliablePackets = m_orderedReliablePackets[ackIdWithoutPacketId];
                    if (packetId != ((prevPacketId + 1) & MAX_PACKET_ID))
                    {
                        if ((int)orderedReliablePackets.size() > MAX_PACKET_ID_HISTORY)
                        {
                            disconnect();
                            queueErrorEvent("Relay disconnected, too many queued out of order packets.");
                            return;
                        }

                        int insertIdx = 0;
                        for (; insertIdx < (int)orderedReliablePackets.size(); ++insertIdx)
                        {
                            auto pPacket = orderedReliablePackets[insertIdx];
                            if (pPacket->id == packetId)
                            {
#if VERBOSE_LOG
                                if (m_loggingEnabled)
                                {
                                    std::cout << "Duplicated packet from " << (int)netId << ". got " << packetId << std::endl;
                                }
#endif
                                return;
                            }
                            if (packetLE(packetId, pPacket->id)) break;
                        }
                        auto pNewPacket = m_packetPool.alloc();
                        pNewPacket->id = packetId;
                        pNewPacket->netId = netId;
                        pNewPacket->data.assign(in_data + 8, in_data + in_size);
                        orderedReliablePackets.insert(orderedReliablePackets.begin() + insertIdx, pNewPacket);
#if VERBOSE_LOG
                        if (m_loggingEnabled)
                        {
                            std::cout << "Queuing out of order reliable from " << (int)netId << ". got " << packetId << std::endl;
                        }
#endif
                        return;
                    }

                    // It's in order, queue event
                    m_recvPacketId[ackIdWithoutPacketId] = packetId;
                    queueRelayEvent(netId, in_data + 8, in_size - 8);

                    // Empty previously queued packets if they follow this one
                    while (!orderedReliablePackets.empty())
                    {
                        auto pPacket = orderedReliablePackets.front();
                        if (pPacket->id == ((packetId + 1) & MAX_PACKET_ID))
                        {
                            queueRelayEvent(pPacket->netId, pPacket->data.data(), (int)pPacket->data.size());
                            orderedReliablePackets.erase(orderedReliablePackets.begin());
                            packetId = pPacket->id;
                            m_recvPacketId[ackIdWithoutPacketId] = packetId;
                            m_packetPool.free(pPacket);
                            continue;
                        }
                        break; // Out of order
                    }
                    return;
                }
                else
                {
                    if (packetLE(packetId, prevPacketId))
                    {
                        // Just drop out of order packets for unreliables
#if VERBOSE_LOG
                        if (m_loggingEnabled)
                        {
                            std::cout << "Out of order packet from " << (int)netId << ". Expecting " << ((prevPacketId + 1) & MAX_PACKET_ID) << ", got " << packetId << std::endl;
                        }
#endif
                        return;
                    }
                    m_recvPacketId[ackIdWithoutPacketId] = packetId;
                }
            }
        }

        queueRelayEvent(netId, in_data + 8, in_size - 8);
    }

    void RelayComms::runCallbacks()
    {
        auto now = std::chrono::system_clock::now();

        // Update socket
        if (m_pSocket)
        {
            if (m_pSocket->isConnected())
            {
                // Peek messages
                int packetSize;
                const uint8_t* pPacketData;
                while (m_pSocket && (pPacketData = m_pSocket->peek(packetSize)))
                {
                    onRecv(pPacketData, packetSize);
                }

                // Check for connect request resend
                if (m_connectionType == eRelayConnectionType::UDP &&
                    m_resendConnectRequest &&
                    now - m_lastConnectResendTime > std::chrono::milliseconds(CONNECT_RESEND_INTERVAL_MS))
                {
                    m_lastConnectResendTime = now;
                    send(CL2RS_CONNECT, buildConnectionRequest());
                }

                // Ping. Which also works as an heartbeat
                if (now - m_lastPingTime >= m_pingInterval)
                {
                    sendPing();
                }

                // Process reliable resends
                if (m_connectionType == eRelayConnectionType::UDP)
                {
                    for (auto it = m_reliables.begin(); it != m_reliables.end(); ++it)
                    {
                        auto pPacket = it->second;
                        if (pPacket->timeSinceFirstSend - now > std::chrono::seconds(10))
                        {
                            disconnect();
                            queueErrorEvent("Relay disconnected, too many packet lost");
                            break;
                        }
                        if (now - pPacket->lastResendTime >= std::chrono::milliseconds((int)pPacket->resendInterval))
                        {
                            pPacket->lastResendTime = now;
                            pPacket->resendInterval = std::min<double>((double)pPacket->resendInterval * 1.25, (double)MAX_RELIABLE_RESEND_INTERVAL_MS);
                            send(pPacket->data.data(), (int)pPacket->data.size());
#if VERBOSE_LOG
                            if (m_loggingEnabled)
                            {
                                std::cout << "Resend reliable (" << pPacket->id << ", " << std::chrono::duration_cast<std::chrono::milliseconds>(pPacket->timeSinceFirstSend - now).count() << "ms)" << std::endl;
                            }
#endif
                        }
                    }
                }

                // Check if we timeout
                if (m_connectionType == eRelayConnectionType::UDP && 
                    m_pSocket && 
                    now - m_lastRecvTime > std::chrono::seconds(TIMEOUT_SECONDS))
                {
                    disconnect();
                    queueErrorEvent("Relay Socket Timeout");
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
                    send(CL2RS_CONNECT, buildConnectionRequest());
                    if (m_connectionType == eRelayConnectionType::UDP)
                    {
                        m_resendConnectRequest = true;
                        m_lastConnectResendTime = now;
                    }
                }
            }
        }

        // Perform event callbacks
        {
            m_eventsCopy = m_events;
            m_events.clear();
            for (auto pEvent : m_eventsCopy)
            {
                switch (pEvent->type)
                {
                    case EventType::ConnectSuccess:
                        if (m_pRelayConnectCallback)
                        {
                            m_pRelayConnectCallback->relayConnectSuccess(pEvent->message);
                        }
                        break;
                    case EventType::ConnectFailure:
                        if (m_pRelayConnectCallback)
                        {
                            if (m_loggingEnabled)
                            {
                                std::cout << "Relay: " << pEvent->message << std::endl;
                            }
                            m_pRelayConnectCallback->relayConnectFailure(pEvent->message);
                        }
                        break;
                    case EventType::System:
                        if (m_pSystemCallback)
                        {
                            m_pSystemCallback->relaySystemCallback(pEvent->message);
                        }
                        break;
                    case EventType::Relay:
                        if (m_pRelayCallback)
                        {
                            m_pRelayCallback->relayCallback(pEvent->netId, pEvent->data.data(), (int)pEvent->data.size());
                        }
                        break;
                }
                m_eventPool.free(pEvent);
            }
        }

        // Report debug info on memory (Lets only do that when connected)
#if VERBOSE_LOG
        if (m_isConnected && m_loggingEnabled)
        {
            static auto lastPoolReportingTime = now;
            if (now - lastPoolReportingTime > std::chrono::seconds(5))
            {
                lastPoolReportingTime = now;
                std::cout << "Relay Pool sizes: (Events = " << m_eventPool.size() << "," << Event::allocCount << ") (Packets = " << m_packetPool.size() << "," << Packet::allocCount << ")" << std::endl;
            }
        }
#endif
    }

    void RelayComms::queueConnectSuccessEvent(const std::string& jsonString)
    {
        auto pEvent = m_eventPool.alloc();
        pEvent->type = EventType::ConnectSuccess;
        pEvent->message = jsonString;
        m_events.push_back(pEvent);
    }

    void RelayComms::queueErrorEvent(const std::string& message)
    {
        auto pEvent = m_eventPool.alloc();
        pEvent->type = EventType::ConnectFailure;
        pEvent->message = message;
        m_events.push_back(pEvent);
    }

    void RelayComms::queueSystemEvent(const std::string& jsonString)
    {
        auto pEvent = m_eventPool.alloc();
        pEvent->type = EventType::System;
        pEvent->message = jsonString;
        m_events.push_back(pEvent);
    }

    void RelayComms::queueRelayEvent(int netId, const uint8_t* pData, int size)
    {
        auto pEvent = m_eventPool.alloc();
        pEvent->type = EventType::Relay;
        pEvent->netId = netId;
        pEvent->data.assign(pData, pData + size);
        m_events.push_back(pEvent);
    }
};
