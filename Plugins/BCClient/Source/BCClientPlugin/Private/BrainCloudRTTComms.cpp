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
#include <iostream>

#define MAX_PAYLOAD 64 * 1024
#define INITIAL_HEARTBEAT_TIME 10

#if PLATFORM_UWP
#elif PLATFORM_HTML5
#else
#include "libwebsockets.h"

static struct lws_protocols protocols[] = {
	/* first protocol must always be HTTP handler */

	{
		"", /* name - can be overridden with -e */
		&BrainCloudRTTComms::callback_echo,
		MAX_PAYLOAD,
		MAX_PAYLOAD,
	},
	{
		NULL, NULL, 0 /* End of list */
	}};

static const struct lws_extension exts[] = {
	{"permessage-deflate",
	 lws_extension_callback_pm_deflate,
	 "permessage-deflate; client_no_context_takeover"},
	{"deflate-frame",
	 lws_extension_callback_pm_deflate,
	 "deflate_frame"},
	{NULL, NULL, NULL /* terminator */}};
#endif

BrainCloudRTTComms::BrainCloudRTTComms(BrainCloudClient *client) : m_client(client),
																   m_appCallback(nullptr),
																   m_connectedSocket(nullptr),
																   m_commsPtr(nullptr),
																   m_cxId(TEXT("")),
																   m_eventServer(TEXT("")),
																   m_rttHeaders(nullptr),
																   m_endpoint(nullptr),
																   m_heartBeatSecs(INITIAL_HEARTBEAT_TIME),
																   m_timeSinceLastRequest(0),
																   m_lastNowMS(FPlatformTime::Seconds()),
																   m_bIsConnected(false),
																   m_lwsContext(nullptr)
{
}

BrainCloudRTTComms::~BrainCloudRTTComms()
{
	disconnect();
	deregisterAllRTTCallbacks();
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
	disconnect();
}

void BrainCloudRTTComms::RunCallbacks()
{
#if PLATFORM_UWP
#elif PLATFORM_HTML5
#else
	if (m_lwsContext != nullptr)
	{
		lws_callback_on_writable_all_protocol(m_lwsContext, &protocols[0]);
		lws_service(m_lwsContext, 0);
	}
#endif

	if (m_bIsConnected)
	{
		// check to see if we need to send an RTT heartbeat to keep the connection alive
		float nowMS = FPlatformTime::Seconds();

		// the heart beat
		m_timeSinceLastRequest += (nowMS - m_lastNowMS);
		m_lastNowMS = nowMS;
		if (m_timeSinceLastRequest >= m_heartBeatSecs)
		{
			m_timeSinceLastRequest = 0;
			send(buildHeartbeatRequest());
		}
	}
}

#if PLATFORM_UWP
#elif PLATFORM_HTML5
#else
int BrainCloudRTTComms::callback_echo(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
{
	void *pUser = lws_wsi_user(wsi);
	UWebSocketBase *pWebSocketBase = (UWebSocketBase *)pUser;
	switch (reason)
	{
	case LWS_CALLBACK_CLOSED_CLIENT_HTTP:
	case LWS_CALLBACK_CLOSED:

		if (!pWebSocketBase)
			return -1;
		pWebSocketBase->Cleanlws();
		pWebSocketBase->OnClosed.Broadcast();
		break;

	case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
	{
		FString strError = UTF8_TO_TCHAR(in);
		if (!pWebSocketBase)
			return -1;
		pWebSocketBase->Cleanlws();
		pWebSocketBase->OnConnectError.Broadcast(strError);
	}
	break;

	case LWS_CALLBACK_CLIENT_ESTABLISHED:
		if (!pWebSocketBase)
			return -1;
		pWebSocketBase->OnConnectComplete.Broadcast();
		break;

	case LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER:
	{
		if (!pWebSocketBase)
			return -1;

		unsigned char **p = (unsigned char **)in, *end = (*p) + len;
		if (!pWebSocketBase->ProcessHeader(p, end))
		{
			return -1;
		}

		pWebSocketBase->ProcessWriteable();
	}
	break;

	case LWS_CALLBACK_CLIENT_RECEIVE:
		if (!pWebSocketBase)
			return -1;
		pWebSocketBase->ProcessRead((const char *)in, (int)len);
		break;

	case LWS_CALLBACK_CLIENT_WRITEABLE:
		if (!pWebSocketBase)
			return -1;
		pWebSocketBase->ProcessWriteable();
		break;

	default:
		break;
	}

	return 0;
}
#endif

// add blueprints
void BrainCloudRTTComms::registerRTTCallback(ServiceName in_serviceName, UBCBlueprintRTTCallProxyBase *callback)
{
	callback->AddToRoot();
	m_registeredRTTBluePrintCallbacks.Emplace(in_serviceName.getValue(), callback);	
}

// regular c++ overtyped, does nothing memory wise
void BrainCloudRTTComms::registerRTTCallback(ServiceName in_serviceName, IRTTCallback *callback)
{
	m_registeredRTTCallbacks.Emplace(in_serviceName.getValue(), callback);
}

void BrainCloudRTTComms::deregisterRTTCallback(ServiceName in_serviceName)
{
	FString serviceName = in_serviceName.getValue();
	if (m_registeredRTTBluePrintCallbacks.Contains(serviceName))
	{
		m_registeredRTTBluePrintCallbacks[serviceName]->RemoveFromRoot();
		m_registeredRTTBluePrintCallbacks.Remove(serviceName);
	}
	else if (m_registeredRTTCallbacks.Contains(serviceName))
	{
		m_registeredRTTCallbacks.Remove(serviceName);
	}
}

void BrainCloudRTTComms::deregisterAllRTTCallbacks()
{
	for (auto iterator = m_registeredRTTBluePrintCallbacks.CreateIterator(); iterator; ++iterator)
	{
		UBCBlueprintRTTCallProxyBase *pObject = iterator.Value();
		if (pObject->IsValidLowLevel())
		{
			pObject->RemoveFromRoot();
			pObject->ConditionalBeginDestroy();
		}
	}

	m_registeredRTTCallbacks.Empty();
	m_registeredRTTBluePrintCallbacks.Empty();
}

void BrainCloudRTTComms::setRTTHeartBeatSeconds(int32 in_value)
{
	m_heartBeatSecs = in_value;
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
	if (m_connectedSocket != nullptr && m_commsPtr != nullptr)
	{
		m_commsPtr->RemoveFromRoot();
		m_connectedSocket->RemoveFromRoot();
		m_connectedSocket->OnConnectError.RemoveDynamic(m_commsPtr, &UBCRTTCommsProxy::WebSocket_OnError);
		m_connectedSocket->OnClosed.RemoveDynamic(m_commsPtr, &UBCRTTCommsProxy::WebSocket_OnClose);
		m_connectedSocket->OnConnectComplete.RemoveDynamic(m_commsPtr, &UBCRTTCommsProxy::Websocket_OnOpen);
		m_connectedSocket->OnReceiveData.RemoveDynamic(m_commsPtr, &UBCRTTCommsProxy::WebSocket_OnMessage);
	}

	delete m_commsPtr;
	m_commsPtr = nullptr;

	delete m_connectedSocket;
	m_connectedSocket = nullptr;

	lws_context_destroy(m_lwsContext);
	m_lwsContext = nullptr;

	m_cxId = TEXT("");
	m_eventServer = TEXT("");
}

void BrainCloudRTTComms::connect()
{
}

FString BrainCloudRTTComms::buildConnectionRequest()
{
	TSharedRef<FJsonObject> sysJson = MakeShareable(new FJsonObject());
	sysJson->SetStringField("platform", m_client->getReleasePlatform());
	sysJson->SetStringField("protocol", "ws"); // "tcp"

	TSharedRef<FJsonObject> jsonData = MakeShareable(new FJsonObject());
	jsonData->SetStringField("appId", m_client->getAppId());
	jsonData->SetStringField("sessionId", m_client->getSessionId());
	jsonData->SetStringField("profileId", m_client->getProfileId());
	jsonData->SetObjectField("system", sysJson);
	jsonData->SetObjectField("auth", m_rttHeaders);

	TSharedRef<FJsonObject> json = MakeShareable(new FJsonObject());
	json->SetStringField("service", ServiceName::RTT.getValue());
	json->SetStringField("operation", "CONNECT");
	json->SetObjectField("data", jsonData);

	return JsonUtil::jsonValueToString(json);
}

FString BrainCloudRTTComms::buildHeartbeatRequest()
{
	TSharedRef<FJsonObject> json = MakeShareable(new FJsonObject());
	json->SetStringField("service", ServiceName::RTT.getValue());
	json->SetStringField("operation", "HEARTBEAT");
	json->SetObjectField("data", nullptr);

	return JsonUtil::jsonValueToString(json);
}

bool BrainCloudRTTComms::send(const FString &in_message)
{
	bool bMessageSent = false;
	// early return
	if ((m_connectedSocket == nullptr))
	{
		return bMessageSent;
	}
	m_timeSinceLastRequest = 0;

	bMessageSent = m_connectedSocket->SendText(in_message);
	if (bMessageSent && m_client->isLoggingEnabled())
		UE_LOG(LogBrainCloudComms, Log, TEXT("RTT SEND:  %s"), *in_message);

	return bMessageSent;
}

void BrainCloudRTTComms::processRegisteredListeners(const FString &in_service, const FString &in_operation, const FString &in_jsonMessage)
{
	// does this go to one of our registered service listeners?
	if (m_registeredRTTBluePrintCallbacks.Contains(in_service))
	{
		m_registeredRTTBluePrintCallbacks[in_service]->rttCallback(in_jsonMessage);
	}
	else if (m_registeredRTTCallbacks.Contains(in_service))
	{
		m_registeredRTTCallbacks[in_service]->rttCallback(in_jsonMessage);
	}
	// are we actually connected? only pump this back, when the server says we've connected
	else if (in_operation == TEXT("CONNECT"))
	{
		m_bIsConnected = true;
		m_lastNowMS = FPlatformTime::Seconds();

		// success callback!
		// server callback rtt connected with data!
		if (m_appCallback != nullptr)
		{
			m_appCallback->serverCallback(ServiceName::RTTRegistration, ServiceOperation::Connect, in_jsonMessage);
		}
	}
	else if (in_operation == TEXT("error") || in_operation == TEXT("disconnect"))
	{
		if (in_operation == TEXT("disconnect"))
		{
			disconnect();
		}

		// error callback!
		if (m_appCallback != nullptr)
		{
			m_appCallback->serverError(ServiceName::RTTRegistration, ServiceOperation::Connect, 400, -1, in_jsonMessage);
		}
	}
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
#if PLATFORM_UWP
#elif PLATFORM_HTML5
#else
	if (m_lwsContext == nullptr)
	{
		struct lws_context_creation_info info;
		memset(&info, 0, sizeof info);

		info.protocols = protocols;
		info.ssl_cert_filepath = NULL;
		info.ssl_private_key_filepath = NULL;

		info.port = -1;
		info.gid = -1;
		info.uid = -1;
		info.extensions = exts;
		info.options = LWS_SERVER_OPTION_VALIDATE_UTF8;
		info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;

		m_lwsContext = lws_create_context(&info);
	}
#endif

	m_timeSinceLastRequest = 0;
	// lazy load
	if (m_connectedSocket == nullptr)
	{
		m_connectedSocket = NewObject<UWebSocketBase>();
		m_connectedSocket->AddToRoot();
	}

	// lazy load
	if (m_commsPtr == nullptr)
	{
		m_commsPtr = NewObject<UBCRTTCommsProxy>();
		m_commsPtr->AddToRoot();
	}

	m_commsPtr->SetRTTComms(this);
	m_connectedSocket->OnConnectError.AddDynamic(m_commsPtr, &UBCRTTCommsProxy::WebSocket_OnError);
	m_connectedSocket->OnClosed.AddDynamic(m_commsPtr, &UBCRTTCommsProxy::WebSocket_OnClose);
	m_connectedSocket->OnConnectComplete.AddDynamic(m_commsPtr, &UBCRTTCommsProxy::Websocket_OnOpen);
	m_connectedSocket->OnReceiveData.AddDynamic(m_commsPtr, &UBCRTTCommsProxy::WebSocket_OnMessage);
	m_connectedSocket->mlwsContext = m_lwsContext;

	m_connectedSocket->Connect(in_url, m_rttHeadersMap);
}

void BrainCloudRTTComms::webSocket_OnClose()
{
	if (m_client->isLoggingEnabled())
		UE_LOG(LogBrainCloudComms, Log, TEXT("Connection closed"));

	processRegisteredListeners(ServiceName::RTTRegistration.getValue(), "error", "{\"error\":\"Could not connect at this time\"}");
}

void BrainCloudRTTComms::websocket_OnOpen()
{
	// first time connecting? send the server connection call
	send(buildConnectionRequest());
}

void BrainCloudRTTComms::webSocket_OnMessage(const FString &in_message)
{
	onRecv(in_message);
}

void BrainCloudRTTComms::webSocket_OnError(const FString &in_message)
{
	if (m_client->isLoggingEnabled())
		UE_LOG(LogBrainCloudComms, Log, TEXT("Error: %s"), *in_message);

	disconnect();
}

void BrainCloudRTTComms::onRecv(const FString &in_message)
{
	// deserialize and push broadcast to the correct m_registeredRTTCallbacks
	TSharedPtr<FJsonObject> jsonData = JsonUtil::jsonStringToValue(in_message);
	FString service = jsonData->GetStringField(TEXT("service"));
	FString operation = jsonData->GetStringField(TEXT("operation"));
	TSharedPtr<FJsonObject> innerData = nullptr;
	bool bIsInnerDataValid = jsonData->HasTypedField<EJson::Object>(TEXT("data"));
	if (bIsInnerDataValid)
		innerData = jsonData->GetObjectField(TEXT("data"));

	if (operation != "HEARTBEAT" && m_client->isLoggingEnabled())
		UE_LOG(LogBrainCloudComms, Log, TEXT("RTT RECV:: %s"), *in_message);

	if (operation == "CONNECT")
	{
		int32 heartBeat = INITIAL_HEARTBEAT_TIME;
		if (bIsInnerDataValid && innerData->HasField(TEXT("heartbeatSeconds")))
		{
			heartBeat = innerData->GetIntegerField(TEXT("heartbeatSeconds"));
		}
		else if (bIsInnerDataValid && innerData->HasField(TEXT("wsHeartbeatSecs")))
		{
			heartBeat = innerData->GetIntegerField(TEXT("wsHeartbeatSecs"));
		}
		setRTTHeartBeatSeconds(heartBeat);
	}

	if (bIsInnerDataValid)
	{
		if (innerData->HasField(TEXT("cxId")))
		{
			m_cxId = innerData->GetStringField(TEXT("cxId"));
		}

		if (innerData->HasField(TEXT("evs")))
		{
			m_eventServer = innerData->GetStringField(TEXT("evs"));
		}
	}

	processRegisteredListeners(service, operation, in_message);
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
	FString toReturn = TEXT("/?");
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
}

void BrainCloudRTTComms::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString &jsonError)
{
	// server callback rtt connected with data!
	if (m_appCallback != nullptr)
		m_appCallback->serverError(serviceName, serviceOperation, statusCode, reasonCode, jsonError);

	disconnect();
}
