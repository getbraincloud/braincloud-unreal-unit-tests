// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "IServerCallback.h"

#if PLATFORM_UWP
#elif PLATFORM_HTML5
#else
 #define UI UI_ST
 THIRD_PARTY_INCLUDES_START
 #include "libwebsockets.h"
 THIRD_PARTY_INCLUDES_END
 #undef UI
#endif

enum class eBCRSConnectionType : uint8;
class IRSCallback;
class ServiceOperation;
class ServiceName;
class INetworkErrorCallback;
class ServerCall;
class BCFileUploader;
class BrainCloudClient;
class FJsonObject;
class UWebSocketBase;
class UBCRSCommsProxy;
class UBCBlueprintRSCallProxyBase;

class BrainCloudRSComms
{
  public:
	BrainCloudRSComms(BrainCloudClient *client);
	~BrainCloudRSComms();

	void connect(eBCRSConnectionType in_connectionType, IServerCallback *callback);
	void disconnect();
	void registerDataCallback(IRSCallback *callback);
	void registerDataCallback(UBCBlueprintRSCallProxyBase *callback);
	void deregisterDataCallback();
	void RunCallbacks();

	bool send(const FString &in_message);

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
  void processRegisteredListeners(const FString &in_service, const FString &in_operation, const FString &in_jsonMessage);
	void connectWebSocket();
	void disconnectImpl();
	void onRecv(const FString &in_message);
	FString buildRSRequestError(FString in_statusMessage);
	void setupWebSocket(const FString &in_url);

	BrainCloudClient *m_client;
	IServerCallback *m_appCallback;

	UBCRSCommsProxy *m_commsPtr;

	IRSCallback * m_registeredRSCallbacks;
	UBCBlueprintRSCallProxyBase * m_registeredRSBluePrintCallbacks;

	UWebSocketBase *m_connectedSocket;

	bool m_bIsConnected;
	eBCRSConnectionType m_connectionType;

	struct lws_context *m_lwsContext;
};
