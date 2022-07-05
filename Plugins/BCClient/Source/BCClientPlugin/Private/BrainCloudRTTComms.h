// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "IServerCallback.h"

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

enum class BCRTTConnectionType : uint8;
enum class BCRTTConnectionStatus : uint8;
enum class BCWebsocketStatus : uint8;
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
class UBCRTTProxy;

class BrainCloudRTTComms : public IServerCallback
{
  public:
	BrainCloudRTTComms(BrainCloudClient *client);
	~BrainCloudRTTComms();

	void enableRTT(BCRTTConnectionType in_connectionType, IServerCallback *callback);
	void enableRTT(BCRTTConnectionType in_connectionType, UBCRTTProxy *callback);
	void disableRTT();
	bool isRTTEnabled();
	BCRTTConnectionStatus getConnectionStatus();
	void RunCallbacks();

	void registerRTTCallback(ServiceName in_serviceName, IRTTCallback *callback);
	void registerRTTCallback(ServiceName in_serviceName, UBCBlueprintRTTCallProxyBase *callback);
	void deregisterRTTCallback(ServiceName in_serviceName);
	void deregisterAllRTTCallbacks();

	void setRTTHeartBeatSeconds(int32 in_value);

	const FString &getConnectionId() const { return m_cxId; }
	const FString &getEventServer() { return m_eventServer; }

// expose web socket functions
#if PLATFORM_UWP
#if ENGINGE_MINOR_VERSION <24
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
	void connectWebSocket();
	void disconnect();

	FString buildConnectionRequest();
	FString buildHeartbeatRequest();
	bool send(const FString &in_message, bool in_allowLogging = true);

	void startReceivingWebSocket();

	void processRegisteredListeners(const FString &in_service, const FString &in_operation, const FString &in_jsonMessage);

	FString getUrlQueryParameters();
	void setupWebSocket(const FString &in_url);

	void setEndpointFromType(TArray<TSharedPtr<FJsonValue>> in_endpoints, FString in_socketType);
	void onRecv(const FString &in_message);

	FString buildRTTRequestError(FString in_statusMessage);
	
	// IServerCallback
	void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString &jsonData);
	void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString &jsonError);

	// private vars
	BrainCloudClient *m_client = nullptr;
	IServerCallback *m_appCallback;
	UBCRTTProxy *m_appCallbackBP;

	TMap<FString, IRTTCallback *> m_registeredRTTCallbacks;
	TMap<FString, UBCBlueprintRTTCallProxyBase *> m_registeredRTTBluePrintCallbacks;

	UWebSocketBase *m_connectedSocket;
	UBCRTTCommsProxy *m_commsPtr;

	FString m_cxId; // connectionID
	FString m_eventServer;

	TMap<FString, FString> m_rttHeadersMap;
	TSharedPtr<FJsonObject> m_rttHeaders;
	TSharedPtr<FJsonObject> m_endpoint;
	TSharedRef<FJsonObject> m_disconnectJson = MakeShareable(new FJsonObject());

    float m_heartBeatSecs;
    float m_heartBeatIdleSecs;
	float m_timeSinceLastRequest;
	float m_lastNowMS;
    bool m_heartBeatRecv = true;
    bool m_heartBeatSent = false;

    
	BCRTTConnectionType m_connectionType;
	BCRTTConnectionStatus m_rttConnectionStatus;
	BCWebsocketStatus m_websocketStatus;
	bool m_bIsConnected;
	bool m_disconnectedWithReason = false;
    
	struct lws_context *m_lwsContext;

	FString BCBytesToString(const uint8* in, int32 count);
};
