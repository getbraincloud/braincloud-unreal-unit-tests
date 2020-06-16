// Copyright 2020 bitHeads, Inc. All Rights Reserved.

#ifndef _RELAYCOMMS_H_
#define _RELAYCOMMS_H_

#include "braincloud/RelayChannel.h"
#include "braincloud/RelayConnectionType.h"
#include "braincloud/internal/IRelaySocket.h"

#include <atomic>
#include <cinttypes>
#include <condition_variable>
#include <string>
#include <map>
#include <mutex>
#include <vector>

namespace BrainCloud
{
    class BrainCloudClient;
    class IRelayConnectCallback;
    class IRelayCallback;
    class IRelaySystemCallback;
    class ISocket;

    class RelayComms
    {
    public:
        RelayComms(BrainCloudClient* in_client);
        virtual ~RelayComms();

        void initialize();
        bool isInitialized();
        void shutdown();
        void resetCommunication();
        void runCallbacks();
        void enableLogging(bool shouldEnable);

        void connect(eRelayConnectionType in_connectionType, const std::string& host, int port, const std::string& passcode, const std::string& lobbyId, IRelayConnectCallback* in_callback);
        void disconnect();
        bool isConnected() const;
        int getPing() const;
        void setPingInterval(int in_intervalMS);
        const std::string& getOwnerProfileId() const;
        const std::string& getProfileIdForNetId(int in_netId) const;
        int getNetIdForProfileId(const std::string& in_profileId) const;
        void registerRelayCallback(IRelayCallback* in_callback);
        void deregisterRelayCallback();
        void registerSystemCallback(IRelaySystemCallback* in_callback);
        void deregisterSystemCallback();
        void send(const uint8_t* in_data, int in_size, int in_toNetId, bool in_reliable, bool in_ordered, eRelayChannel in_channel);

    private:
        static const int CHANNEL_COUNT = 4;

        enum class EventType
        {
            ConnectSuccess,
            ConnectFailure,
            Relay,
            System
        };

        struct Event
        {
            EventType type;
            std::string message;
            int netId;
            std::vector<uint8_t> data;
        };

        struct ConnectOptions
        {
            std::string host;
            int port = 0;
            std::string passcode;
            std::string lobbyId;
        };

        void queueConnectSuccessEvent(const std::string& jsonString);
        void queueErrorEvent(const std::string& message);
        void queueSystemEvent(const std::string& jsonString);
        void queueRelayEvent(int netId, const uint8_t* pData, int size);
        Json::Value buildConnectionRequest();
        void sendPing();
        void send(const uint8_t* in_data, int in_size);
        void send(int netId, const Json::Value& json);
        void send(int netId, const std::string& text);

        void onRecv(const uint8_t* in_data, int in_size);
        void onRSMG(const uint8_t* in_data, int in_size);
        void onPONG();
        void onRelay(const uint8_t* in_data, int netId, int in_size);

        BrainCloudClient* m_client = nullptr;
        bool m_isInitialized = false;
        bool m_loggingEnabled = false;

        bool m_isConnected;
        bool m_isSocketConnected;

        std::vector<Event> m_events;
        IRelayConnectCallback* m_pRelayConnectCallback = nullptr;
        IRelayCallback* m_pRelayCallback = nullptr;
        IRelaySystemCallback* m_pSystemCallback = nullptr;

        eRelayConnectionType m_connectionType;
        ConnectOptions m_connectOptions;

        IRelaySocket* m_pSocket = nullptr;

        int m_ping = 999;
        bool m_pingInFlight = false;
        std::chrono::milliseconds m_pingInterval;
        std::chrono::time_point<std::chrono::system_clock> m_lastPingTime;

        int m_netId = -1;
        std::string m_ownerProfileId = "";
        std::map<std::string, int> m_profileIdToNetId;
        std::map<int, std::string> m_netIdToProfileId;

        // Packet ID/History
        int m_sendPacketId[CHANNEL_COUNT * 2]; // *2 here is for reliable vs unreliable
    };
};

#endif /* _RELAYCOMMS_H_ */
