// Copyright 2021 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "Runtime/Launch/Resources/Version.h"

static const int MAX_RSMG_HISTORY = 50;

enum class BCRelayConnectionType : uint8;
enum class BCRelayChannel : uint8;
class BrainCloudClient;
class IRelayConnectCallback;
class IRelayCallback;
class IRelaySystemCallback;
class UWebSocketBase;
class UBCRelayCommsProxy;
class UBCBlueprintRelayConnectCallProxyBase;
class UBCBlueprintRelayCallProxyBase;
class UBCBlueprintRelaySystemCallProxyBase;
class UBCRelayProxy;
namespace BrainCloud
{
    class IRelaySocket;
};

class BrainCloudRelayComms
{
public:
    BrainCloudRelayComms(BrainCloudClient* in_client);
    virtual ~BrainCloudRelayComms();

    void initialize();
    bool isInitialized();
    void shutdown();
    void resetCommunication();
    void RunCallbacks();

    void connect(BCRelayConnectionType in_connectionType, const FString& host, int port, const FString& passcode, const FString& lobbyId, IRelayConnectCallback* in_callback);
    void connect(BCRelayConnectionType in_connectionType, const FString& host, int port, const FString& passcode, const FString& lobbyId, UBCRelayProxy* in_callback);
    void disconnect();
    bool isConnected() const;
    int getPing() const;
    void setPingInterval(int in_intervalMS);
    const FString& getOwnerProfileId() const;
    const FString& getProfileIdForNetId(int in_netId) const;
    int getNetIdForProfileId(const FString& in_profileId) const;
    const FString& getOwnerCxId() const;
    const FString& getCxIdForNetId(int in_netId) const;
    int getNetIdForCxId(const FString& in_cxId) const;
    void registerRelayCallback(IRelayCallback* in_callback);
    void registerRelayCallback(UBCBlueprintRelayCallProxyBase* in_callback);
    void deregisterRelayCallback();
    void registerSystemCallback(IRelaySystemCallback* in_callback);
    void registerSystemCallback(UBCBlueprintRelaySystemCallProxyBase* in_callback);
    void deregisterSystemCallback();
    void send(const TArray<uint8> &in_data, uint64 in_playerMask, bool in_reliable, bool in_ordered, BCRelayChannel in_channel);

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
        FString message;
        int netId;
        TArray<uint8> data;

        static int allocCount;
        Event() { ++allocCount; }
        ~Event() { --allocCount; }
    };

    struct ConnectOptions
    {
        FString host;
        int port = 0;
        FString passcode;
        FString lobbyId;
    };

    struct Packet
    {
        int id;
        int netId;
        TArray<uint8> data;
        double resendInterval;
        double lastResendTime;
        double timeSinceFirstSend;

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
            if (m_pool.Num() == 0)
            {
                auto pT = new T();
                m_all.Add(pT);
                return pT;
            }
            auto pT = m_pool[m_pool.Num() - 1];
            m_pool.RemoveAt(m_pool.Num() - 1);
            return pT;
        }

        size_t size() const
        {
            return m_all.Num();
        }

        void free(T* pT)
        {
            m_pool.Add(pT);
        }

        void reclaim()
        {
            m_pool = m_all;
        }

    private:
        TArray<T*> m_pool;
        TArray<T*> m_all;
    };

    void connect(BCRelayConnectionType in_connectionType, const FString& host, int port, const FString& passcode, const FString& lobbyId);

    void queueConnectSuccessEvent(const FString& jsonString);
    void queueErrorEvent(const FString& message);
    void queueSystemEvent(const FString& jsonString);
    void queueRelayEvent(int netId, const uint8* pData, int size);
    TSharedRef<FJsonObject> buildConnectionRequest();
    void sendPing();
    void sendRSMGAck(int rsmgPacketId);
    void sendAck(const uint8* in_data);
    void send(const uint8* in_data, int in_size);
    void send(int netId, const TSharedRef<FJsonObject>& json);
    void send(int netId, const FString& text);

    void onRecv(const uint8* in_data, int in_size);
    void onRSMG(const uint8* in_data, int in_size);
    void onPONG();
    void onRelay(const uint8* in_data, int in_size);
    void onAck(const uint8* in_data);

    // Main objects/flags
    BrainCloudClient* m_client = nullptr;
    BrainCloud::IRelaySocket* m_pSocket = nullptr;
    bool m_isInitialized = false;

    // Connection
    BCRelayConnectionType m_connectionType;
    ConnectOptions m_connectOptions;
    bool m_isSocketConnected = false;
    bool m_resendConnectRequest = false;
    double m_lastConnectResendTime;
    bool m_isConnected = false;

    // Events
    TArray<Event*> m_events;
    TArray<Event*> m_eventsCopy;
    IRelayConnectCallback* m_pRelayConnectCallback = nullptr;
    UBCBlueprintRelayConnectCallProxyBase* m_pRelayConnectCallbackBP = nullptr;
    IRelayCallback* m_pRelayCallback = nullptr;
    UBCBlueprintRelayCallProxyBase* m_pRelayCallbackBP = nullptr;
    IRelaySystemCallback* m_pSystemCallback = nullptr;
    UBCBlueprintRelaySystemCallProxyBase* m_pSystemCallbackBP = nullptr;

    // Ping
    int m_ping = 999;
    double m_pingInterval;
    double m_lastPingTime;
    double m_lastRecvTime; // For UDP timeout

    // Profile/Cx/Net IDs
    int32 m_netId = -1;
    FString m_cxId = "";
    FString m_ownerProfileId = "";
    FString m_ownerCxId = "";
    TMap<FString, int32> m_profileIdToNetId;
    TMap<int32, FString> m_netIdToProfileId;
    TMap<FString, int32> m_cxIdToNetId;
    TMap<int32, FString> m_netIdToCxId;

    // Packet ID/History
    TArray<int> m_rsmgHistory;
    TMap<uint64, int> m_sendPacketId;
    TMap<uint64, int> m_recvPacketId;
    TMap<uint64, Packet*> m_reliables;
    TMap<uint64, TArray<Packet*>> m_orderedReliablePackets;

    // Memory
    Pool<Event> m_eventPool;
    Pool<Packet> m_packetPool;
};
