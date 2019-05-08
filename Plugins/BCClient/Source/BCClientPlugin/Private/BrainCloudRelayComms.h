// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "IServerCallback.h"

#define MAX_PAYLOAD 1024

#if PLATFORM_UWP
#elif PLATFORM_HTML5
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

class BrainCloudRelayComms
{
public:
	static const int MAX_PACKETSIZE = 1024;

	static const uint8 MAX_PLAYERS = 128;
	static const uint8 INVALID_NET_ID = MAX_PLAYERS;

	static const uint8 CL2RS_CONNECTION = 129;
	static const uint8 CL2RS_DISCONNECT = 130;
	static const uint8 CL2RS_RELAY = 131;
	static const uint8 CL2RS_PING = 133;
	static const uint8 RS2CL_PONG = CL2RS_PING;
	static const uint8 CL2RS_RSMG_ACKNOWLEDGE = 134;
	static const uint8 CL2RS_ACKNOWLEDGE = 135;

	static const uint8 TO_ALL_PLAYERS = CL2RS_RELAY;

	BrainCloudRelayComms(BrainCloudClient *client);
	~BrainCloudRelayComms();

	int64 ping();
	uint8 netId();

	void connect(BCRelayConnectionType in_connectionType, const FString &in_connectOptionsJson, IServerCallback *callback);
	void disconnect();
	void registerDataCallback(IRelayCallback *callback);
	void registerDataCallback(UBCBlueprintRelayCallProxyBase *callback);
	void deregisterDataCallback();

	bool send(TArray<uint8> in_message, const uint8 in_target = TO_ALL_PLAYERS, bool in_reliable = true, bool in_ordered = true, int in_channel = 0);
	void setPingInterval(float in_interval);

	void RunCallbacks();

// expose web socket functions
#if PLATFORM_UWP
#elif PLATFORM_HTML5
#else
	static int callback_echo(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len);
#endif

	void webSocket_OnClose();
	void websocket_OnOpen();
	void webSocket_OnMessage(const FString &in_data);
	void webSocket_OnError(const FString &in_error);

private:
	void startReceivingRSConnectionAsync();
	TArray<uint8> concatenateByteArrays(TArray<uint8> in_bufferA, TArray<uint8> in_bufferB);
	TArray<uint8> appendSizeBytes(TArray<uint8> in_message);
	TArray<uint8> buildConnectionRequest();
	void processRegisteredListeners(const FString &in_service, const FString &in_operation, const FString &in_jsonMessage);
	void connectWebSocket(FString in_host, int in_port, bool in_sslEnabled);
	void disconnectImpl();
	void onRecv(const FString &in_message);
	FString buildRSRequestError(FString in_statusMessage);
	void setupWebSocket(const FString &in_url);
	void sendPing();

	BrainCloudClient *m_client;
	IServerCallback *m_appCallback;

	UBCRelayCommsProxy *m_commsPtr;

	IRelayCallback *m_registeredRelayCallbacks;
	UBCBlueprintRelayCallProxyBase *m_registeredRelayBluePrintCallbacks;

	UWebSocketBase *m_connectedSocket;

	bool m_bIsConnected;
	float m_pingInterval;
	float m_timeSinceLastPingRequest;
	float m_lastNowMS;
	float m_sentPing;

	BCRelayConnectionType m_connectionType;
	TMap<FString, FString> m_connectOptions;

	struct lws_context *m_lwsContext;
};
