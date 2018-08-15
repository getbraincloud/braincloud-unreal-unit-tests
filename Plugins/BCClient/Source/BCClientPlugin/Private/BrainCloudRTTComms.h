// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "ServiceName.h"
#include "IServerCallback.h"
class INetworkErrorCallback;
class ServerCall;
class BCFileUploader;
class BrainCloudClient;
class FJsonObject;
class UWebSocketBase;
class UBCRTTCommsProxy;

class BrainCloudRTTComms : public IServerCallback
{
  public:
	BrainCloudRTTComms(BrainCloudClient *client);
	~BrainCloudRTTComms();

	void enableRTT(eBCRTTConnectionType in_connectionType, IServerCallback *callback);
	void disableRTT();
	void RunCallbacks();

	void registerRTTCallback(ServiceName in_serviceName, IRTTCallback *callback);
	void deregisterRTTCallback(ServiceName in_serviceName);
	void deregisterAllRTTCallbacks();

	void setRTTHeartBeatSeconds(int32 in_value);

	const FString &getConnectionId() { return m_cxId; }
	const FString &getEventServer() { return m_eventServer; }
	
	// expose web socket functions
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
	TDoubleLinkedList<TSharedRef<ServerCall>> m_messageQueue;

	UWebSocketBase *m_connectedSocket;
  	UBCRTTCommsProxy *m_commsPtr;

	FString m_cxId; // connectionID
	FString m_eventServer;

	TMap<FString, FString> m_rttHeadersMap;
	TSharedPtr<FJsonObject> m_rttHeaders;
	TSharedPtr<FJsonObject> m_endpoint;

	eBCRTTConnectionType m_connectionType;
	bool m_bIsConnected;
};
