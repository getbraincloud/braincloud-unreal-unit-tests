// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "IServerCallback.h"

#pragma once

#if PLATFORM_UWP
#elif PLATFORM_HTML5
#else
class libwebsockets;
struct lws_context;
struct lws;
enum lws_callback_reasons : int;
#endif

enum class eBCRTTConnectionType : uint8;
class IRTTCallback;
class ServiceOperation;
class ServiceName;
class INetworkErrorCallback;
class ServerCall;
class BCFileUploader;
class BrainCloudClient;
class FJsonObject;
class UWebSocketBase;
class UBCRTTCommsProxy;
class UBCBlueprintRTTCallProxyBase;

class BrainCloudRTTComms : public IServerCallback
{
  public:
	BrainCloudRTTComms(BrainCloudClient *client);
	~BrainCloudRTTComms();

	void enableRTT(eBCRTTConnectionType in_connectionType, IServerCallback *callback);
	void disableRTT();
	bool isRTTEnabled();
	void RunCallbacks();

	void registerRTTCallback(ServiceName in_serviceName, UBCBlueprintRTTCallProxyBase *callback);
	void registerRTTCallback(ServiceName in_serviceName, IRTTCallback *callback);
	void deregisterRTTCallback(ServiceName in_serviceName);
	void deregisterAllRTTCallbacks();

	void setRTTHeartBeatSeconds(int32 in_value);

	const FString &getConnectionId() { return m_cxId; }
	const FString &getEventServer() { return m_eventServer; }

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
	void connectWebSocket();
	void disconnect();
	void connect();

	FString buildConnectionRequest();
	FString buildHeartbeatRequest();
	bool send(const FString &in_message);

	void startReceivingWebSocket();

	void processRegisteredListeners(const FString &in_service, const FString &in_operation, const FString &in_jsonMessage);

	FString getUrlQueryParameters();
	void setupWebSocket(const FString &in_url);

	void setEndpointFromType(TArray<TSharedPtr<FJsonValue>> in_endpoints, FString in_socketType);
	void onRecv(const FString &in_message);
	// IServerCallback
	void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString &jsonData);
	void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString &jsonError);

	// private vars
	BrainCloudClient *m_client = nullptr;
	IServerCallback *m_appCallback;

	TMap<FString, IRTTCallback *> m_registeredRTTCallbacks;
	TMap<FString, UBCBlueprintRTTCallProxyBase *> m_registeredRTTBluePrintCallbacks;

	UWebSocketBase *m_connectedSocket;
	UBCRTTCommsProxy *m_commsPtr;

	FString m_cxId; // connectionID
	FString m_eventServer;

	TMap<FString, FString> m_rttHeadersMap;
	TSharedPtr<FJsonObject> m_rttHeaders;
	TSharedPtr<FJsonObject> m_endpoint;

	float m_heartBeatSecs;
	float m_timeSinceLastRequest;
	float m_lastNowMS;

	eBCRTTConnectionType m_connectionType;
	bool m_bIsConnected;

	struct lws_context *m_lwsContext;
};
