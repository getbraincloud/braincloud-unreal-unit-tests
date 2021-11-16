// Copyright 2020 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudRelayComms.h"
#include "ConvertUtilities.h"
#include "RelayWebSocket.h"

#include "BCClientPluginPrivatePCH.h"
#include "Serialization/JsonTypes.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "GenericPlatform/GenericPlatformProperties.h"

#include "JsonUtil.h"
#include "BCBlueprintRelayConnectCallProxyBase.h"
#include "BCBlueprintRelayCallProxyBase.h"
#include "BCBlueprintRelaySystemCallProxyBase.h"
#include "BCRelayProxy.h"
#include "IServerCallback.h"
#include "ServerCall.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "BrainCloudWrapper.h"
#include "BrainCloudClient.h"
#include "BCFileUploader.h"
#include "ReasonCodes.h"
#include "HttpCodes.h"

// #include "BCRelayCommsProxy.h"
#include "WebSocketBase.h"
#include <iostream>
#include "Runtime/Launch/Resources/Version.h"


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

static const int RELAY_MAX_PACKET_SIZE = 1024;
static const int TIMEOUT_SECONDS = 10;

static const double RELIABLE_RESEND_INTERVALS[] = {
    50.0, 50.0, // High priority 1 and 2
    150.0,      // Normal priority
    500.0       // Low priority
};

static FString extractProfileIdFromCxId(const FString &cxId)
{
    int32 first, last;
    if (!cxId.FindChar(':', first)) return "";
    cxId.FindLastChar(':', last);
    if (last == first) return "";
    if (last - first < 2) return "";

    return cxId.Mid(first + 1, last - first - 1);
}

static uint16 hostToNet(uint16 val)
{
	if (!FGenericPlatformProperties::IsLittleEndian())
		return val;

	return (uint16)(((val >> 8) & 0x00FF) |
		            ((val << 8) & 0xFF00));
}

static uint16 netToHost(uint16 val)
{
	if (!FGenericPlatformProperties::IsLittleEndian())
		return val;

	return (uint16)(((val >> 8) & 0x00FF) |
		            ((val << 8) & 0xFF00));
}

int BrainCloudRelayComms::Event::allocCount = 0;
int BrainCloudRelayComms::Packet::allocCount = 0;

BrainCloudRelayComms::BrainCloudRelayComms(BrainCloudClient* in_client)
    : m_client(in_client)
    , m_isInitialized(false)
{
    m_isConnected = false;
    m_isSocketConnected = false;
    m_pingInterval = 1.0;
}

BrainCloudRelayComms::~BrainCloudRelayComms()
{
    disconnect();
    
	if (m_pRelayConnectCallbackBP != nullptr)
	{
        m_pRelayConnectCallbackBP->RemoveFromRoot();
        m_pRelayConnectCallbackBP->ConditionalBeginDestroy();
	}
	m_pRelayConnectCallbackBP = nullptr;
    
	if (m_pRelayCallbackBP != nullptr)
	{
        m_pRelayCallbackBP->RemoveFromRoot();
        m_pRelayCallbackBP->ConditionalBeginDestroy();
	}
	m_pRelayCallbackBP = nullptr;
    
	if (m_pSystemCallbackBP != nullptr)
	{
        m_pSystemCallbackBP->RemoveFromRoot();
        m_pSystemCallbackBP->ConditionalBeginDestroy();
	}
	m_pSystemCallbackBP = nullptr;
}

void BrainCloudRelayComms::initialize()
{
    m_isInitialized = true;
}

bool BrainCloudRelayComms::isInitialized()
{
    return m_isInitialized;
}

void BrainCloudRelayComms::shutdown()
{
    resetCommunication();
    m_isInitialized = false;
}

void BrainCloudRelayComms::resetCommunication()
{
    disconnect();
}

void BrainCloudRelayComms::connect(BCRelayConnectionType in_connectionType, const FString& host, int port, const FString& passcode, const FString& lobbyId, IRelayConnectCallback* in_callback)
{
    if (m_isSocketConnected)
    {
        disconnect();
    }

    m_pRelayConnectCallback = in_callback;

    connect(in_connectionType, host, port, passcode, lobbyId);
}

void BrainCloudRelayComms::connect(BCRelayConnectionType in_connectionType, const FString& host, int port, const FString& passcode, const FString& lobbyId, UBCRelayProxy* in_callback)
{
    if (m_isSocketConnected)
    {
        disconnect();
    }

    m_pRelayConnectCallbackBP = in_callback;

    connect(in_connectionType, host, port, passcode, lobbyId);
}

void BrainCloudRelayComms::connect(BCRelayConnectionType in_connectionType, const FString& host, int port, const FString& passcode, const FString& lobbyId)
{
    m_connectionType = in_connectionType;
    m_connectOptions.host = host;
    m_connectOptions.port = port;
    m_connectOptions.passcode = passcode;
    m_connectOptions.lobbyId = lobbyId;
    m_ping = 999;
    m_netId = -1;
    m_ownerProfileId.Reset(0);
    m_profileIdToNetId.Reset();
    m_netIdToProfileId.Reset();
    m_ownerCxId.Reset(0);
    m_cxIdToNetId.Reset();
    m_netIdToCxId.Reset();
    m_sendPacketId.Reset();
    m_recvPacketId.Reset();
    m_reliables.Reset();
    m_orderedReliablePackets.Reset();
    m_eventPool.reclaim();
    m_packetPool.reclaim();
    m_rsmgHistory.Reset(0);

    switch (m_connectionType)
    {
        case BCRelayConnectionType::WEBSOCKET:
        {
            m_pSocket = new BrainCloud::RelayWebSocket(host, port, false);
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

void BrainCloudRelayComms::disconnect()
{
    m_isConnected = false;
    m_isSocketConnected = false;
    m_resendConnectRequest = false;

    // Close socket
    delete m_pSocket;
    m_pSocket = nullptr;
    
    m_sendPacketId.Reset();
    m_recvPacketId.Reset();

    m_rsmgHistory.Reset(0);
    m_reliables.Reset();
    m_orderedReliablePackets.Reset();
    m_packetPool.reclaim();
}

bool BrainCloudRelayComms::isConnected() const
{
    return m_isConnected;
}

int BrainCloudRelayComms::getPing() const
{
    return m_ping;
}

void BrainCloudRelayComms::setPingInterval(int in_intervalMS)
{
    m_pingInterval = (double)in_intervalMS / 1000.0f;
}

const FString& BrainCloudRelayComms::getOwnerProfileId() const
{
    return m_ownerProfileId;
}

const FString& BrainCloudRelayComms::getOwnerCxId() const
{
    return m_ownerCxId;
}

const FString& BrainCloudRelayComms::getProfileIdForNetId(int in_netId) const
{
    auto it = m_netIdToProfileId.Find(in_netId);
    if (!it)
    {
        static FString empty;
        return empty;
    }
    return *it;
}

int BrainCloudRelayComms::getNetIdForProfileId(const FString& in_profileId) const
{
    auto it = m_profileIdToNetId.Find(in_profileId);
    if (!it) return INVALID_NET_ID;
    return *it;
}

const FString& BrainCloudRelayComms::getCxIdForNetId(int in_netId) const
{
    auto it = m_netIdToCxId.Find(in_netId);
    if (!it)
    {
        static FString empty;
        return empty;
    }
    return *it;
}

int BrainCloudRelayComms::getNetIdForCxId(const FString& in_cxId) const
{
    auto it = m_cxIdToNetId.Find(in_cxId);
    if (!it) return INVALID_NET_ID;
    return *it;
}

void BrainCloudRelayComms::registerRelayCallback(IRelayCallback* in_callback)
{
    m_pRelayCallback = in_callback;
}

void BrainCloudRelayComms::registerRelayCallback(UBCBlueprintRelayCallProxyBase* in_callback)
{
    m_pRelayCallbackBP = in_callback;
}

void BrainCloudRelayComms::deregisterRelayCallback()
{
    m_pRelayCallback = nullptr;
	if (m_pRelayCallbackBP != nullptr)
	{
        m_pRelayCallbackBP->RemoveFromRoot();
        m_pRelayCallbackBP->ConditionalBeginDestroy();
	}
	m_pRelayCallbackBP = nullptr;
}

void BrainCloudRelayComms::registerSystemCallback(IRelaySystemCallback* in_callback)
{
    m_pSystemCallback = in_callback;
}

void BrainCloudRelayComms::registerSystemCallback(UBCBlueprintRelaySystemCallProxyBase* in_callback)
{
    m_pSystemCallbackBP = in_callback;
}

void BrainCloudRelayComms::deregisterSystemCallback()
{
    m_pSystemCallback = nullptr;
	if (m_pSystemCallbackBP != nullptr)
	{
        m_pSystemCallbackBP->RemoveFromRoot();
        m_pSystemCallbackBP->ConditionalBeginDestroy();
	}
	m_pSystemCallbackBP = nullptr;
}

TSharedRef<FJsonObject> BrainCloudRelayComms::buildConnectionRequest()
{
    TSharedRef<FJsonObject> request = MakeShareable(new FJsonObject());

    m_cxId = m_client->getRTTService()->getRTTConnectionId();

	request->SetStringField("lobbyId", m_connectOptions.lobbyId);
	request->SetStringField("cxId", m_cxId);
	request->SetStringField("passcode", m_connectOptions.passcode);
	request->SetStringField("version", m_client->getBrainCloudClientVersion());

    return request;
}

void BrainCloudRelayComms::send(const TArray<uint8> &in_dataArr, uint64 in_playerMask, bool in_reliable, bool in_ordered, BCRelayChannel in_channel)
{
    if (!isConnected()) return;

    const uint8 *in_data = in_dataArr.GetData();
    int in_size = (int)in_dataArr.Num();

    if (in_size > RELAY_MAX_PACKET_SIZE)
    {
        disconnect();
        queueErrorEvent("Relay Error: Packet is too big " + FString::FromInt(in_size) + " > max 1024");
        return;
    }

    // Allocate buffer
    auto totalSize = in_size + 11;
    auto pPacket = m_packetPool.alloc();
    pPacket->data.SetNum(totalSize, false);

    // Size
    auto len = hostToNet((uint16)totalSize);
    memcpy(pPacket->data.GetData(), &len, 2);

    // NetId
    pPacket->data[2] = (uint8)CL2RS_RELAY;

    // Reliable header
    uint16 rh = 0;
    if (in_reliable) rh |= RELIABLE_BIT;
    if (in_ordered) rh |= ORDERED_BIT;
    rh |= ((uint16)in_channel << 12) & 0x3000;

    // Store inverted player mask
    uint64 playerMask = 0;
    for (uint64 i = 0, len2 = (uint64)MAX_PLAYERS; i < len2; ++i)
    {
        playerMask |= ((in_playerMask >> ((uint64)MAX_PLAYERS - i - 1)) & 1) << i;
    }
    playerMask = (playerMask << 8) & 0x0000FFFFFFFFFF00;

    // AckId without packet id
    uint64 ackIdWithoutPacketId = (((uint64)rh << 48) & 0xFFFF000000000000) | playerMask;

    // Packet Id
    int packetId = 0;
    auto it = m_sendPacketId.Find(ackIdWithoutPacketId);
    if (it)
    {
        packetId = *it;
    }
    m_sendPacketId.Add(ackIdWithoutPacketId, (packetId + 1) & MAX_PACKET_ID);

    // Add packet id to the header, then encode
    rh |= packetId;

    auto rhBE = hostToNet((uint16)rh);
    auto playerMask0BE = (uint64)netToHost((uint16)((playerMask >> 32) & 0xFFFF));
    auto playerMask1BE = (uint64)netToHost((uint16)((playerMask >> 16) & 0xFFFF));
    auto playerMask2BE = (uint64)netToHost((uint16)((playerMask)       & 0xFFFF));
    memcpy(pPacket->data.GetData() + 3, &rhBE, 2);
    memcpy(pPacket->data.GetData() + 5, &playerMask0BE, 2);
    memcpy(pPacket->data.GetData() + 7, &playerMask1BE, 2);
    memcpy(pPacket->data.GetData() + 9, &playerMask2BE, 2);

    // Rest of data
    memcpy(pPacket->data.GetData() + 11, in_data, in_size);

    // Send
    send(pPacket->data.GetData(), (int)pPacket->data.Num());

    // UDP, store reliable in send map
    if (in_reliable)
    {
        pPacket->id = packetId;
        pPacket->lastResendTime = FPlatformTime::Seconds();
        pPacket->timeSinceFirstSend = pPacket->lastResendTime;
        pPacket->resendInterval = RELIABLE_RESEND_INTERVALS[(int)in_channel];
        uint64 ackId = *(uint64*)(pPacket->data.GetData() + 3);
        m_reliables.Add(ackId, pPacket);
    }
    else
    {
        m_packetPool.free(pPacket);
    }
}

void BrainCloudRelayComms::sendPing()
{
    m_lastPingTime = FPlatformTime::Seconds();

    uint8 data[5];
    *(uint16*)(data) = (uint16)hostToNet((uint16)5);
    data[2] = CL2RS_PING;
    *(uint16*)(data + 3) = (uint16)hostToNet((uint16)m_ping);
    send(data, 5);
}

void BrainCloudRelayComms::send(int netId, const TSharedRef<FJsonObject>& json)
{
	FString jsonStr;
	TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&jsonStr);
	FJsonSerializer::Serialize(json, writer);

    send(netId, jsonStr);
}

void BrainCloudRelayComms::send(int netId, const FString& text)
{
#if VERBOSE_LOG
    if (m_client->isLoggingEnabled())
    {
        UE_LOG(LogBrainCloudRelayComms, Log, TEXT("RELAY SEND: %s"), *text);
    }
#endif

    uint8 bytes[1024];
    int32 bytesLen = ConvertUtilities::BCStringToBytes(text, bytes, 1024);

    auto totalSize = bytesLen + 3;
    TArray<uint8> buffer;
    buffer.SetNum(totalSize);
    auto len = hostToNet((uint16)totalSize);
    memcpy(buffer.GetData(), &len, 2);
    buffer[2] = (uint8)netId;
    memcpy(buffer.GetData() + 3, bytes, bytesLen);
    send(buffer.GetData(), (int)buffer.Num());
}

void BrainCloudRelayComms::send(const uint8* in_data, int in_size)
{
    if (m_pSocket)
    {
        m_pSocket->send(in_data, in_size);
    }
}

void BrainCloudRelayComms::onRecv(const uint8* in_data, int in_size)
{
    m_lastRecvTime = FPlatformTime::Seconds();

    if (in_size < 3)
    {
        disconnect();
        queueErrorEvent("Relay Recv Error: packet cannot be smaller than 3 bytes");
        return;
    }

    int size = (int)netToHost(*(uint16*)in_data);
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
        if (m_connectionType == BCRelayConnectionType::UDP)
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
        queueErrorEvent("Relay Recv Error: Unknown control byte: " + FString::FromInt(controlByte));
    }
}

void BrainCloudRelayComms::sendRSMGAck(int rsmgPacketId)
{
#if VERBOSE_LOG
    if (m_client->isLoggingEnabled())
    {
        UE_LOG(LogBrainCloudRelayComms, Log, TEXT("#RELAY SEND: RSMG ACK"));
    }
#endif

    uint8 data[5];
    *(uint16*)(data) = (uint16)hostToNet((uint16)5);
    data[2] = CL2RS_RSMG_ACK;
    *(uint16*)(data + 3) = (uint16)hostToNet((uint16)rsmgPacketId);
    send(data, 5);
}

void BrainCloudRelayComms::sendAck(const uint8* in_data)
{
    uint8 data[11];
    *(uint16*)(data) = (uint16)hostToNet((uint16)11);
    data[2] = CL2RS_ACK;
    memcpy(data + 3, in_data, 8);
    send(data, 11);
}

void BrainCloudRelayComms::onRSMG(const uint8* in_data, int in_size)
{
    int rsmgPacketId = (int)netToHost(*(uint16*)in_data);

    FString jsonString = ConvertUtilities::BCBytesToString(in_data + 2, in_size - 2);
    if (m_client->isLoggingEnabled())
    {
        UE_LOG(LogBrainCloudRelayComms, Log, TEXT("RELAY System Msg: %s"), *jsonString);
    }

    if (m_connectionType == BCRelayConnectionType::UDP)
    {
        // Send ack, always. Even if we already received it
        sendRSMGAck(rsmgPacketId);

        // If already received, we ignore
        for (int packetId : m_rsmgHistory)
        {
            if (packetId == rsmgPacketId)
            {
#if VERBOSE_LOG
                if (m_client->isLoggingEnabled())
                {
                    UE_LOG(LogBrainCloudRelayComms, Log, TEXT("RELAY Duplicated System Msg"));
                }
#endif
                return;
            }
        }

        // Add to history
        m_rsmgHistory.Add(rsmgPacketId);

        // Crop to max history
        while ((int)m_rsmgHistory.Num() > MAX_RSMG_HISTORY)
        {
            m_rsmgHistory.RemoveAt(0);
        }
    }

	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(jsonString);
	TSharedPtr<FJsonObject> json = MakeShareable(new FJsonObject());
    if (!FJsonSerializer::Deserialize(reader, json))
    {
        disconnect();
        queueErrorEvent("Invalid Json in RSMG packet");
        return;
    }

    auto op = json->Values["op"]->AsString();
    if (op == "CONNECT")
    {
        int32 netId;
        json->Values["netId"]->TryGetNumber(netId);
        auto cxId = json->Values["cxId"]->AsString();
        auto profileId = extractProfileIdFromCxId(cxId);
        UE_LOG(LogBrainCloudRelayComms, Log, TEXT("m_netIdToCxId.Add(%i, %s)"), netId, *cxId);
        m_netIdToCxId.Add(netId, cxId);
        m_cxIdToNetId.Add(cxId, netId);
        m_netIdToProfileId.Add(netId, profileId);
        m_profileIdToNetId.Add(profileId, netId);
        if (cxId == m_cxId)
        {
            m_netId = netId;
            m_ownerCxId = json->Values["ownerCxId"]->AsString();
            m_ownerProfileId = extractProfileIdFromCxId(m_ownerCxId);
            m_lastPingTime = FPlatformTime::Seconds();
            m_isConnected = true;
            m_resendConnectRequest = false;
            queueConnectSuccessEvent(jsonString);
        }
    }
    else if (op == "NET_ID")
    {
        int32 netId;
        json->Values["netId"]->TryGetNumber(netId);
        auto cxId = json->Values["cxId"]->AsString();
        auto profileId = extractProfileIdFromCxId(cxId);

        m_netIdToCxId.Add(netId, cxId);
        m_cxIdToNetId.Add(cxId, netId);
        m_netIdToProfileId.Add(netId, profileId);
        m_profileIdToNetId.Add(profileId, netId);
    }
    else if (op == "MIGRATE_OWNER")
    {
        auto cxId = json->Values["cxId"]->AsString();
        m_ownerCxId = cxId;
        m_ownerProfileId = extractProfileIdFromCxId(m_ownerCxId);
    }
    else if (op == "DISCONNECT")
    {
        auto cxId = json->Values["cxId"]->AsString();
        if (m_cxId == cxId)
        {
            // We are the one that got disconnected!
            disconnect();
            queueErrorEvent("Disconnected by server");
            return;
        }
    }

    queueSystemEvent(jsonString);
}

void BrainCloudRelayComms::onPONG()
{
    m_ping = (int)((FPlatformTime::Seconds() - m_lastPingTime) * 1000.0);
    if (m_ping > 999 || m_ping < 0) m_ping = 999;
#if VERBOSE_LOG
    if (m_client->isLoggingEnabled())
    {
        UE_LOG(LogBrainCloudRelayComms, Log, TEXT("RELAY PONG: %s"), *FString::FromInt(m_ping));
    }
#endif
}

void BrainCloudRelayComms::onAck(const uint8* in_data)
{
    auto ackId = *(uint64*)in_data;
    auto it = m_reliables.Find(ackId);
    if (it)
    {
        auto pPacket = *it;
#if VERBOSE_LOG
        if (m_client->isLoggingEnabled())
        {
            auto rh = (int)netToHost(*(uint16*)in_data);
            auto packetId = rh & 0xFFF;
            UE_LOG(LogBrainCloudRelayComms, Log, TEXT("Acked packet id: %s"), *FString::FromInt(packetId)));
        }
#endif
        m_packetPool.free(pPacket);
        m_reliables.FindAndRemoveChecked(ackId);
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

void BrainCloudRelayComms::onRelay(const uint8* in_data, int in_size)
{
    auto rh = (int)netToHost(*(uint16*)in_data);
    auto playerMask0 = (uint64)netToHost(*(uint16*)(in_data + 2));
    auto playerMask1 = (uint64)netToHost(*(uint16*)(in_data + 4));
    auto playerMask2 = (uint64)netToHost(*(uint16*)(in_data + 6));
    auto ackId = 
        (((uint64)rh << 48)          & 0xFFFF000000000000) |
        (((uint64)playerMask0 << 32) & 0x0000FFFF00000000) |
        (((uint64)playerMask1 << 16) & 0x00000000FFFF0000) |
        (((uint64)playerMask2)       & 0x000000000000FFFF);
    uint64 ackIdWithoutPacketId = ackId & 0xF000FFFFFFFFFFFF;
    auto reliable = rh & RELIABLE_BIT ? true : false;
    auto ordered = rh & ORDERED_BIT ? true : false;
    auto channel = (rh >> 12) & 0x3;
    auto packetId = rh & 0xFFF;
    auto netId = (uint8)(playerMask2 & 0x00FF);

    // Reconstruct ack id without packet id
    if (m_connectionType == BCRelayConnectionType::UDP)
    {
        // Ack reliables, always. An ack might have been previously dropped.
        if (reliable)
        {
            sendAck(in_data);
        }

        if (ordered)
        {
            int prevPacketId = MAX_PACKET_ID;
            auto it = m_recvPacketId.Find(ackIdWithoutPacketId);
            if (it)
            {
                prevPacketId = *it;
            }

            if (reliable)
            {
                if (packetLE(packetId, prevPacketId))
                {
                    // We already received that packet if it's lower than the last confirmed
                    // packetId. This must be a duplicate
#if VERBOSE_LOG
                    if (m_client->isLoggingEnabled())
                    {
                        UE_LOG(LogBrainCloudRelayComms, Log, TEXT("Duplicated packet from %s. got %s"), 
                            *FString::FromInt(netId), 
                            *FString::FromInt(packetId));
                    }
#endif
                    return;
                }

                // Check if it's out of order, then save it for later
                auto& orderedReliablePackets = m_orderedReliablePackets[ackIdWithoutPacketId];
                if (packetId != ((prevPacketId + 1) & MAX_PACKET_ID))
                {
                    if ((int)orderedReliablePackets.Num() > MAX_PACKET_ID_HISTORY)
                    {
                        disconnect();
                        queueErrorEvent("Relay disconnected, too many queued out of order packets.");
                        return;
                    }

                    int insertIdx = 0;
                    for (; insertIdx < (int)orderedReliablePackets.Num(); ++insertIdx)
                    {
                        auto pPacket = orderedReliablePackets[insertIdx];
                        if (pPacket->id == packetId)
                        {
#if VERBOSE_LOG
                            if (m_client->isLoggingEnabled())
                            {
                                UE_LOG(LogBrainCloudRelayComms, Log, TEXT("Duplicated packet from %s. got %s"), 
                                    *FString::FromInt(netId), 
                                    *FString::FromInt(packetId));
                            }
#endif
                            return;
                        }
                        if (packetLE(packetId, pPacket->id)) break;
                    }
                    auto pNewPacket = m_packetPool.alloc();
                    pNewPacket->id = packetId;
                    pNewPacket->netId = netId;
                    pNewPacket->data.SetNum(in_size - 8);
                    memcpy(pNewPacket->data.GetData(), in_data + 8, in_size - 8);
                    orderedReliablePackets.Insert(pNewPacket, insertIdx);
#if VERBOSE_LOG
                    if (m_client->isLoggingEnabled())
                    {
                        UE_LOG(LogBrainCloudRelayComms, Log, TEXT("Queuing out of order reliable from %s. got %s"), 
                            *FString::FromInt(netId), 
                            *FString::FromInt(packetId));
                    }
#endif
                    return;
                }

                // It's in order, queue event
                m_recvPacketId.Add(ackIdWithoutPacketId, packetId);
                queueRelayEvent(netId, in_data + 8, in_size - 8);

                // Empty previously queued packets if they follow this one
                while (orderedReliablePackets.Num() > 0)
                {
                    auto pPacket = orderedReliablePackets[0];
                    if (pPacket->id == ((packetId + 1) & MAX_PACKET_ID))
                    {
                        queueRelayEvent(pPacket->netId, pPacket->data.GetData(), (int)pPacket->data.Num());
                        orderedReliablePackets.RemoveAt(0);
                        packetId = pPacket->id;
                        m_recvPacketId.Add(ackIdWithoutPacketId, packetId);
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
                    if (m_client->isLoggingEnabled())
                    {
                        UE_LOG(LogBrainCloudRelayComms, Log, TEXT("Out of order packet from %s. Expecting %s, got %s"),
                            *FString::FromInt(netId),
                            *FString::FromInt((prevPacketId + 1) & MAX_PACKET_ID),
                            *FString::FromInt(packetId));
                    }
#endif
                    return;
                }
                m_recvPacketId.Add(ackIdWithoutPacketId, packetId);
            }
        }
    }

    queueRelayEvent(netId, in_data + 8, in_size - 8);
}

void BrainCloudRelayComms::RunCallbacks()
{
    auto now = FPlatformTime::Seconds();

    // Update socket
    if (m_pSocket)
    {
        m_pSocket->update();

        if (m_pSocket->isConnected())
        {
            // Peek messages
            int packetSize;
            const uint8* pPacketData;
            pPacketData = m_pSocket->peek(packetSize);
            while (m_pSocket && pPacketData)
            {
                onRecv(pPacketData, packetSize);
                pPacketData = m_pSocket->peek(packetSize);
            }

            // Check for connect request resend
            if (m_connectionType == BCRelayConnectionType::UDP &&
                m_resendConnectRequest &&
                now - m_lastConnectResendTime > ((double)CONNECT_RESEND_INTERVAL_MS / 1000.0))
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
            if (m_connectionType == BCRelayConnectionType::UDP)
            {
                for (const auto& it : m_reliables)
                {
                    auto pPacket = it.Value;
                    if (pPacket->timeSinceFirstSend - now > 10.0)
                    {
                        disconnect();
                        queueErrorEvent("Relay disconnected, too many packet lost");
                        break;
                    }
                    if (now - pPacket->lastResendTime >= pPacket->resendInterval)
                    {
                        pPacket->lastResendTime = now;
                        pPacket->resendInterval = FMath::Min((double)pPacket->resendInterval * 1.25, (double)(MAX_RELIABLE_RESEND_INTERVAL_MS / 1000.0));
                        send(pPacket->data.GetData(), (int)pPacket->data.Num());
#if VERBOSE_LOG
                        if (m_client->isLoggingEnabled())
                        {
                            UE_LOG(LogBrainCloudRelayComms, Log, TEXT("Resend reliable (%sms)"),
                                *FString::FromInt((uint64)((pPacket->timeSinceFirstSend - now) * 1000.0)));
                        }
#endif
                    }
                }
            }

            // Check if we timeout
            if (m_connectionType == BCRelayConnectionType::UDP && 
                m_pSocket && 
                now - m_lastRecvTime > (double)TIMEOUT_SECONDS)
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
                if (m_client->isLoggingEnabled())
                {
                    UE_LOG(LogBrainCloudRelayComms, Log, TEXT("Relay Socket Connected"));
                }
                send(CL2RS_CONNECT, buildConnectionRequest());
                if (m_connectionType == BCRelayConnectionType::UDP)
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
        m_events.Reset(0);
        for (auto pEvent : m_eventsCopy)
        {
            switch (pEvent->type)
            {
                case EventType::ConnectSuccess:
                    if (m_pRelayConnectCallback)
                    {
                        m_pRelayConnectCallback->relayConnectSuccess(pEvent->message);
                    }
                    if (m_pRelayConnectCallbackBP)
                    {
                        m_pRelayConnectCallbackBP->relayConnectSuccess(pEvent->message);
                    }
                    break;
                case EventType::ConnectFailure:
                    if (m_pRelayConnectCallback)
                    {
                        if (m_client->isLoggingEnabled())
                        {
                            UE_LOG(LogBrainCloudRelayComms, Log, TEXT("Relay: %s"), *pEvent->message);
                        }
                        m_pRelayConnectCallback->relayConnectFailure(pEvent->message);
                    }
                    if (m_pRelayConnectCallbackBP)
                    {
                        if (m_client->isLoggingEnabled())
                        {
                            UE_LOG(LogBrainCloudRelayComms, Log, TEXT("Relay: %s"), *pEvent->message);
                        }
                        m_pRelayConnectCallbackBP->relayConnectFailure(pEvent->message);
                    }
                    break;
                case EventType::System:
                    if (m_pSystemCallback)
                    {
                        m_pSystemCallback->relaySystemCallback(pEvent->message);
                    }
                    if (m_pSystemCallbackBP)
                    {
                        m_pSystemCallbackBP->relaySystemCallback(pEvent->message);
                    }
                    break;
                case EventType::Relay:
                    if (m_pRelayCallback)
                    {
                        m_pRelayCallback->relayCallback(pEvent->netId, pEvent->data);
                    }
                    if (m_pRelayCallbackBP)
                    {
                        m_pRelayCallbackBP->relayCallback(pEvent->netId, pEvent->data);
                    }
                    break;
            }
            m_eventPool.free(pEvent);
        }
    }

    // Report debug info on memory (Lets only do that when connected)
#if VERBOSE_LOG
    if (m_isConnected && m_client->isLoggingEnabled())
    {
        static auto lastPoolReportingTime = now;
        if (now - lastPoolReportingTime > 5.0)
        {
            lastPoolReportingTime = now;
            UE_LOG(LogBrainCloudRelayComms, Log, TEXT("Relay Pool sizes: (Events = %s,%s\"Packets = %s,%s\""),
                *FString::FromInt(m_eventPool.size()),
                *FString::FromInt(Event::allocCount),
                *FString::FromInt(m_packetPool.size()),
                *FString::FromInt(Packet::allocCount));
        }
    }
#endif
}

void BrainCloudRelayComms::queueConnectSuccessEvent(const FString& jsonString)
{
    auto pEvent = m_eventPool.alloc();
    pEvent->type = EventType::ConnectSuccess;
    pEvent->message = jsonString;
    m_events.Add(pEvent);
}

void BrainCloudRelayComms::queueErrorEvent(const FString& message)
{
    auto pEvent = m_eventPool.alloc();
    pEvent->type = EventType::ConnectFailure;
    pEvent->message = message;
    m_events.Add(pEvent);
}

void BrainCloudRelayComms::queueSystemEvent(const FString& jsonString)
{
    auto pEvent = m_eventPool.alloc();
    pEvent->type = EventType::System;
    pEvent->message = jsonString;
    m_events.Add(pEvent);
}

void BrainCloudRelayComms::queueRelayEvent(int netId, const uint8* pData, int size)
{
    auto pEvent = m_eventPool.alloc();
    pEvent->type = EventType::Relay;
    pEvent->netId = netId;
    pEvent->data.SetNum(size);
    memcpy(pEvent->data.GetData(), pData, size);
    m_events.Add(pEvent);
}
