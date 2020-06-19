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
#include <unordered_map>

static const int MAX_RSMG_HISTORY = 50;

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
        void send(const uint8_t* in_data, int in_size, uint64_t in_playerMask, bool in_reliable, bool in_ordered, eRelayChannel in_channel);

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

            static int allocCount;
            Event() { ++allocCount; }
            ~Event() { --allocCount; }
        };

        struct ConnectOptions
        {
            std::string host;
            int port = 0;
            std::string passcode;
            std::string lobbyId;
        };

        struct Packet
        {
            int id;
            int netId;
            std::vector<uint8_t> data;
            double resendInterval;
            std::chrono::time_point<std::chrono::system_clock> lastResendTime;
            std::chrono::time_point<std::chrono::system_clock> timeSinceFirstSend;

            static int allocCount;
            Packet() { ++allocCount; }
            ~Packet() { --allocCount; }
        };

        template<typename T>
        class Pool final
        {
        public:
            ~Pool()
            {
                for (auto pT : m_all) delete pT;
            }

            T* alloc()
            {
                if (m_pool.empty())
                {
                    auto pT = new T();
                    m_all.push_back(pT);
                    return pT;
                }
                auto pT = m_pool.back();
                m_pool.pop_back();
                return pT;
            }

            size_t size() const
            {
                return m_all.size();
            }

            void free(T* pT)
            {
                m_pool.push_back(pT);
            }

            void reclaim()
            {
                m_pool = m_all;
            }

        private:
            std::vector<T*> m_pool;
            std::vector<T*> m_all;
        };

        void queueConnectSuccessEvent(const std::string& jsonString);
        void queueErrorEvent(const std::string& message);
        void queueSystemEvent(const std::string& jsonString);
        void queueRelayEvent(int netId, const uint8_t* pData, int size);
        Json::Value buildConnectionRequest();
        void sendPing();
        void sendRSMGAck(int rsmgPacketId);
        void sendAck(const uint8_t* in_data);
        void send(const uint8_t* in_data, int in_size);
        void send(int netId, const Json::Value& json);
        void send(int netId, const std::string& text);

        void onRecv(const uint8_t* in_data, int in_size);
        void onRSMG(const uint8_t* in_data, int in_size);
        void onPONG();
        void onRelay(const uint8_t* in_data, int in_size);
        void onAck(const uint8_t* in_data);

        // Main objects/flags
        BrainCloudClient* m_client = nullptr;
        IRelaySocket* m_pSocket = nullptr;
        bool m_isInitialized = false;
        bool m_loggingEnabled = false;

        // Connection
        eRelayConnectionType m_connectionType;
        ConnectOptions m_connectOptions;
        bool m_isSocketConnected = false;
        bool m_resendConnectRequest = false;
        std::chrono::time_point<std::chrono::system_clock> m_lastConnectResendTime;
        bool m_isConnected = false;

        // Events
        std::vector<Event*> m_events;
        std::vector<Event*> m_eventsCopy;
        IRelayConnectCallback* m_pRelayConnectCallback = nullptr;
        IRelayCallback* m_pRelayCallback = nullptr;
        IRelaySystemCallback* m_pSystemCallback = nullptr;

        // Ping
        int m_ping = 999;
        bool m_pingInFlight = false;
        std::chrono::milliseconds m_pingInterval;
        std::chrono::time_point<std::chrono::system_clock> m_lastPingTime;
        std::chrono::time_point<std::chrono::system_clock> m_lastRecvTime; // For UDP timeout

        // Profile/Net IDs
        int m_netId = -1;
        std::string m_ownerProfileId = "";
        std::map<std::string, int> m_profileIdToNetId;
        std::map<int, std::string> m_netIdToProfileId;

        // Packet ID/History
        std::vector<int> m_rsmgHistory;
        std::map<uint64_t, int> m_sendPacketId;
        std::map<uint64_t, int> m_recvPacketId;
        std::map<uint64_t, Packet*> m_reliables;
        std::map<uint64_t, std::vector<Packet*>> m_orderedReliablePackets;

        // Memory
        Pool<Event> m_eventPool;
        Pool<Packet> m_packetPool;
    };
};

#endif /* _RELAYCOMMS_H_ */
