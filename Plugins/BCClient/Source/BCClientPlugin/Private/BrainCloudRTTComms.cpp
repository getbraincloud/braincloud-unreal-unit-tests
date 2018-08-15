// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudRTTComms.h"

#include "Serialization/JsonTypes.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#include "IServerCallback.h"
#include "ServerCall.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "BrainCloudClient.h"
#include "BCFileUploader.h"
#include "ReasonCodes.h"
#include "HttpCodes.h"

#include "BCRTTCommsProxy.h"
#include "WebSocketBase.h"

BrainCloudRTTComms::BrainCloudRTTComms(BrainCloudClient *client) : m_client(client),
																   m_rttHeaders(nullptr),
																   m_endpoint(nullptr)
{
	m_commsPtr = NewObject<UBCRTTCommsProxy>();
	m_commsPtr->SetRTTComms(this);
}

BrainCloudRTTComms::~BrainCloudRTTComms()
{
}

void BrainCloudRTTComms::enableRTT(eBCRTTConnectionType in_connectionType, IServerCallback *callback)
{
	if (!m_bIsConnected)
	{
		m_connectionType = in_connectionType;
		m_appCallback = callback;
		m_client->getRTTService()->requestClientConnection(this);
	}
}

void BrainCloudRTTComms::disableRTT()
{
}

void BrainCloudRTTComms::RunCallbacks()
{
}

void BrainCloudRTTComms::registerRTTCallback(ServiceName in_serviceName, IRTTCallback *callback)
{
	m_registeredRTTCallbacks[in_serviceName.getValue()] = callback;
}

void BrainCloudRTTComms::deregisterRTTCallback(ServiceName in_serviceName)
{
	m_registeredRTTCallbacks[in_serviceName.getValue()] = nullptr;
}

void BrainCloudRTTComms::deregisterAllRTTCallbacks()
{
	m_registeredRTTCallbacks.Empty();
}

void BrainCloudRTTComms::setRTTHeartBeatSeconds(int32 in_value)
{
}

void BrainCloudRTTComms::connectWebSocket()
{
	if (!m_bIsConnected)
	{
		startReceivingWebSocket();
	}
}

void BrainCloudRTTComms::disconnect()
{
	// clear everything
}

void BrainCloudRTTComms::connect()
{
}

FString BrainCloudRTTComms::buildConnectionRequest()
{
	FString toReturn = TEXT("");

	return toReturn;
}

FString BrainCloudRTTComms::buildHeartbeatRequest()
{
	FString toReturn = TEXT("");

	return toReturn;
}

bool BrainCloudRTTComms::send(const FString &in_message)
{
	return false;
}

void BrainCloudRTTComms::startReceivingWebSocket()
{
	bool sslEnabled = m_endpoint->GetBoolField(TEXT("ssl"));
	FString url = (sslEnabled ? TEXT("wss://") : TEXT("ws://"));
	url += m_endpoint->GetStringField(TEXT("host"));
	url += ":";
	url += FString::Printf(TEXT("%d"), m_endpoint->GetIntegerField(TEXT("port")));
	url += getUrlQueryParameters();
	setupWebSocket(url);
}

void BrainCloudRTTComms::setupWebSocket(const FString &in_url)
{
	if (m_client->isLoggingEnabled())
		UE_LOG(LogBrainCloudComms, Warning, TEXT("Connection Request Started %s"), *in_url);

	if (m_connectedSocket == nullptr)
		m_connectedSocket = NewObject<UWebSocketBase>();

	m_connectedSocket->Connect(in_url, m_rttHeadersMap);

	m_connectedSocket->OnConnectError.AddDynamic(m_commsPtr, &UBCRTTCommsProxy::WebSocket_OnError);
	m_connectedSocket->OnClosed.AddDynamic(m_commsPtr, &UBCRTTCommsProxy::WebSocket_OnClose);
	m_connectedSocket->OnConnectComplete.AddDynamic(m_commsPtr, &UBCRTTCommsProxy::Websocket_OnOpen);
	m_connectedSocket->OnReceiveData.AddDynamic(m_commsPtr, &UBCRTTCommsProxy::WebSocket_OnMessage);
}

void BrainCloudRTTComms::webSocket_OnClose()
{
	if (m_client->isLoggingEnabled())
		UE_LOG(LogBrainCloudComms, Warning, TEXT("Connection closed"));
}

void BrainCloudRTTComms::websocket_OnOpen()
{
	if (m_client->isLoggingEnabled())
		UE_LOG(LogBrainCloudComms, Warning, TEXT("Connection established."));
}

void BrainCloudRTTComms::webSocket_OnMessage(const FString &in_message)
{
	onRecv(in_message);
}

void BrainCloudRTTComms::webSocket_OnError(const FString &in_message)
{
	if (m_client->isLoggingEnabled())
		UE_LOG(LogBrainCloudComms, Warning, TEXT("Error: %s"), *in_message);
}

void BrainCloudRTTComms::onRecv(const FString &in_message)
{
	// deserialize and push broadcast to the correct m_registeredRTTCallbacks
	if (m_client->isLoggingEnabled())
		UE_LOG(LogBrainCloudComms, Warning, TEXT("RTT RECV:: %s"), *in_message);
}

void BrainCloudRTTComms::setEndpointFromType(TArray<TSharedPtr<FJsonValue>> in_endpoints, FString in_socketType)
{
	TSharedPtr<FJsonObject> tempObj = nullptr;
	bool isSocketType = in_socketType == TEXT("ws");
	for (int32 i = 0; i != in_endpoints.Num(); ++i)
	{
		tempObj = in_endpoints[i]->AsObject();
		if (tempObj->GetStringField(TEXT("protocol")) == in_socketType)
		{
			// try SSL by default for "ws"
			m_endpoint = isSocketType && tempObj->GetBoolField(TEXT("ssl")) ? tempObj : nullptr;

			// try the inverse
			if (!m_endpoint.IsValid())
			{
				m_endpoint = !isSocketType && !tempObj->GetBoolField(TEXT("ssl")) ? tempObj : nullptr;
			}
			break;
		}
	}
}

FString BrainCloudRTTComms::getUrlQueryParameters()
{
	FString toReturn = TEXT("?");
	int32 count = 0;

	// clear this, since we add them within the iterator
	m_rttHeadersMap.Empty();

	// Iterate over Json Values
	for (auto currJsonValue = m_rttHeaders->Values.CreateConstIterator(); currJsonValue; ++currJsonValue)
	{
		// construct params
		if (count > 0)
			toReturn += TEXT("&");

		toReturn += (*currJsonValue).Key;
		toReturn += TEXT("=");
		TSharedPtr<FJsonValue> Value = (*currJsonValue).Value;
		toReturn += Value->AsString();

		m_rttHeadersMap.Add((*currJsonValue).Key, Value->AsString());

		++count;
	}

	return toReturn;
}

// server callback -> initial connect
void BrainCloudRTTComms::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString &in_jsonData)
{
	// read json
	//  --- data
	//      --- endpoints (endpoints for connection)
	///     --- auth (headers)
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(in_jsonData);
	TSharedPtr<FJsonObject> jsonPacket = MakeShareable(new FJsonObject());

	bool res = FJsonSerializer::Deserialize(reader, jsonPacket);
	if (res)
	{
		TSharedPtr<FJsonObject> jsonData = jsonPacket->GetObjectField(TEXT("data"));
		TArray<TSharedPtr<FJsonValue>> endpoints = jsonData->GetArrayField(TEXT("endpoints"));
		m_rttHeaders = jsonData->GetObjectField(TEXT("auth"));

		if (m_connectionType == eBCRTTConnectionType::WEBSOCKET)
		{
			setEndpointFromType(endpoints, TEXT("ws"));
			connectWebSocket();
		}
		else
		{
			setEndpointFromType(endpoints, TEXT("tcp"));
			connect();
		}
	}

	/*
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
	OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
	*/
}

void BrainCloudRTTComms::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString &jsonError)
{
	m_bIsConnected = false;
	/*
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
	OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
	*/
}
