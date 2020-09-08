// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "IServerCallback.h"
#include "Runtime/Launch/Resources/Version.h"

#define MAX_PAYLOAD 1024

#if PLATFORM_UWP
#if ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION <24
#if PLATFORM_HTML5
#endif
#endif
#else
#define UI UI_ST
THIRD_PARTY_INCLUDES_START
#include "libwebsockets.h"
THIRD_PARTY_INCLUDES_END
#undef UI
#endif

enum class BCRelayConnectionType : uint8;
class IRelayCallback;
class ServiceOperation;
class ServiceName;
class INetworkErrorCallback;
class ServerCall;
class BCFileUploader;
class BrainCloudClient;
class FJsonObject;
class UWebSocketBase;
class UBCRelayCommsProxy;
class UBCBlueprintRelayCallProxyBase;
class UBCRelayProxy;
struct RelayMessage;

class BrainCloudRelayComms
{
public:
	static const int MAX_PACKETSIZE = 1024;

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

	static const int MAX_PACKET_ID = 0xFFF;

	static const uint64 TO_ALL_PLAYERS = 0x000000FFFFFFFFFF;

	BrainCloudRelayComms(BrainCloudClient *client);
	~BrainCloudRelayComms();

	int32 ping();
	uint8 netId();
	const FString &getOwnerProfileId() const;
	const FString &getProfileIdForNetId(int in_netId) const;
	int getNetIdForProfileId(const FString &in_profileId) const;

	void connect(BCRelayConnectionType in_connectionType, const FString &in_connectOptionsJson, IServerCallback *callback);
	void connect(BCRelayConnectionType in_connectionType, const FString &in_connectOptionsJson, UBCRelayProxy *callback);
	void disconnect();
	bool isConnected();
	void registerDataCallback(IRelayCallback *callback);
	void registerDataCallback(UBCBlueprintRelayCallProxyBase *callback);
	void deregisterDataCallback();

	void sendRelay(const TArray<uint8> &in_data, const uint64 in_playerMask, bool in_reliable = true, bool in_ordered = true, int in_channel = 0);
	void setPingInterval(float in_interval);

	void RunCallbacks();

// expose web socket functions
#if PLATFORM_UWP
#if ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION <24
#if PLATFORM_HTML5
#endif
#endif
#else
	static int callback_echo(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len);
#endif

	void webSocket_OnClose();
	void websocket_OnOpen();
	void webSocket_OnMessage(TArray<uint8> in_data);
	void webSocket_OnError(const FString &in_error);

private:
	void send(const TArray<uint8> &in_data, const uint8 in_controlByte);
	void connectHelper(BCRelayConnectionType in_connectionType, const FString &in_connectOptionsJson);
	void startReceivingRSConnectionAsync();
	TArray<uint8> concatenateByteArrays(TArray<uint8> in_bufferA, TArray<uint8> in_bufferB);
	TArray<uint8> stripByteArray(TArray<uint8> in_data, int in_numFromLeft);
	TArray<uint8> appendSizeBytes(TArray<uint8> in_message);
	TArray<uint8> buildConnectionRequest();
	void processRegisteredListeners(const FString &in_service, const FString &in_operation, const FString &in_jsonMessage, const TArray<uint8> &in_data);
	void connectWebSocket(FString in_host, int in_port, bool in_sslEnabled);
	void disconnectImpl();
	void onRecv(TArray<uint8> data);
	void setupWebSocket(const FString &in_url);
	void sendPing();
	TArray<uint8> appendHeaderData(uint8 in_controlByte);
	TArray<uint8> fromShortBE(int16 number);

	BrainCloudClient *m_client;
	IServerCallback *m_appCallback;
	UBCRelayProxy *m_appCallbackBP;

	UBCRelayCommsProxy *m_commsPtr;

	IRelayCallback *m_registeredRelayCallback;
	UBCBlueprintRelayCallProxyBase *m_registeredRelayBluePrintCallback;

	UWebSocketBase *m_connectedSocket;

	bool m_bIsConnected;
	float m_pingInterval;
	float m_timeSinceLastPingRequest;
	double m_lastNowMS;
	double m_sentPing;
	int16 m_ping;
	short m_netId;
	FString m_ownerProfileId;

	BCRelayConnectionType m_connectionType;
	TMap<FString, FString> m_connectOptions;

	struct lws_context *m_lwsContext;
	TArray<RelayMessage> m_relayResponse;
	FCriticalSection m_relayMutex;
	
	const int SIZE_OF_LENGTH_PREFIX_BYTE_ARRAY = 2;
    const int CONTROL_BYTE_HEADER_LENGTH = 1;

	TMap<FString, int> m_profileIdToNetId;
	TMap<int, FString> m_netIdToProfileId;
	TMap<uint64, int> m_sendPacketId;
};

struct RelayMessage
{
	RelayMessage(){}
	RelayMessage(const FString &in_service, const FString &in_operation, const FString &in_jsonMessage, const TArray<uint8> &in_data)
	{
		Service = in_service;
		Operation = in_operation;
		JsonMessage = in_jsonMessage;
		Data = in_data;
	}
	FString Service;
	FString Operation;
	FString JsonMessage;
	TArray<uint8> Data;
};
