// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudRSComms.h"

#include "Serialization/JsonTypes.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#include "JsonUtil.h"
#include "BCBlueprintRSCallProxyBase.h"
#include "IServerCallback.h"
#include "ServerCall.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "BrainCloudClient.h"
#include "BCFileUploader.h"
#include "ReasonCodes.h"
#include "HttpCodes.h"

#include "BCRSCommsProxy.h"
#include "WebSocketBase.h"
#include <iostream>

#define MAX_PAYLOAD 64 * 1024
#define INITIAL_HEARTBEAT_TIME 10

#if PLATFORM_UWP
#elif PLATFORM_HTML5
#else
static struct lws_protocols protocolsRS[] = {
	/* first protocol must always be HTTP handler */

	{
		"", /* name - can be overridden with -e */
		&BrainCloudRSComms::callback_echo,
		MAX_PAYLOAD,
		MAX_PAYLOAD,
	},
	{
		NULL, NULL, 0 /* End of list */
	}};

static const struct lws_extension extsRS[] = {
	{"permessage-deflate",
	 lws_extension_callback_pm_deflate,
	 "permessage-deflate; client_no_context_takeover"},
	{"deflate-frame",
	 lws_extension_callback_pm_deflate,
	 "deflate_frame"},
	{NULL, NULL, NULL /* terminator */}};
#endif

BrainCloudRSComms::BrainCloudRSComms(BrainCloudClient *client) 
: m_client(client)
, m_appCallback(nullptr)
, m_commsPtr(nullptr)
, m_registeredRSCallbacks(nullptr)
, m_registeredRSBluePrintCallbacks(nullptr)
, m_bIsConnected(false)
{
}

BrainCloudRSComms::~BrainCloudRSComms()
{
	disconnectImpl();
	deregisterDataCallback();
}

void BrainCloudRSComms::connect(eBCRSConnectionType in_connectionType, IServerCallback *callback)
{
	if (!m_bIsConnected)
	{
		m_connectionType = in_connectionType;
		m_appCallback = callback;
	}
}

void BrainCloudRSComms::disconnect()
{
	if (m_bIsConnected)
		processRegisteredListeners(ServiceName::RTTRegistration.getValue().ToLower(), "disconnect", buildRSRequestError("DisableRS Called"));
}

void BrainCloudRSComms::registerDataCallback(IRSCallback *callback)
{
	m_registeredRSCallbacks = callback;
}

void BrainCloudRSComms::registerDataCallback(UBCBlueprintRSCallProxyBase *callback)
{
	m_registeredRSBluePrintCallbacks = callback;
}

void BrainCloudRSComms::deregisterDataCallback()
{
	m_registeredRSCallbacks = nullptr;
	if (m_registeredRSBluePrintCallbacks->IsValidLowLevel())
	{
		m_registeredRSBluePrintCallbacks->RemoveFromRoot();
		m_registeredRSBluePrintCallbacks->ConditionalBeginDestroy();
	}
	m_registeredRSBluePrintCallbacks = nullptr;
}

void BrainCloudRSComms::RunCallbacks()
{
#if PLATFORM_UWP
#elif PLATFORM_HTML5
#else
	if (m_lwsContext != nullptr)
	{
		lws_callback_on_writable_all_protocol(m_lwsContext, &protocolsRS[0]);
		lws_service(m_lwsContext, 0);
	}
#endif
}

#if PLATFORM_UWP
#elif PLATFORM_HTML5
#else
int BrainCloudRSComms::callback_echo(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
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


void BrainCloudRSComms::connectWebSocket()
{
	if (!m_bIsConnected)
	{
		//startReceivingWebSocket();
	}
}

void BrainCloudRSComms::disconnectImpl()
{
	// clear everything
	if (m_connectedSocket != nullptr && m_commsPtr != nullptr)
	{
		m_commsPtr->RemoveFromRoot();
		m_connectedSocket->RemoveFromRoot();
		m_connectedSocket->OnConnectError.RemoveDynamic(m_commsPtr, &UBCRSCommsProxy::WebSocket_OnError);
		m_connectedSocket->OnClosed.RemoveDynamic(m_commsPtr, &UBCRSCommsProxy::WebSocket_OnClose);
		m_connectedSocket->OnConnectComplete.RemoveDynamic(m_commsPtr, &UBCRSCommsProxy::Websocket_OnOpen);
		m_connectedSocket->OnReceiveData.RemoveDynamic(m_commsPtr, &UBCRSCommsProxy::WebSocket_OnMessage);
	}

	delete m_commsPtr;
	m_commsPtr = nullptr;

	delete m_connectedSocket;
	m_connectedSocket = nullptr;

	lws_context_destroy(m_lwsContext);
	m_lwsContext = nullptr;
	m_bIsConnected = false;
}

bool BrainCloudRSComms::send(const FString &in_message)
{
	bool bMessageSent = false;
	// early return
	if (m_connectedSocket == nullptr)
	{
		return bMessageSent;
	}

	bMessageSent = m_connectedSocket->SendText(in_message);
	if (bMessageSent && m_client->isLoggingEnabled())
		UE_LOG(LogBrainCloudComms, Log, TEXT("RTT SEND:  %s"), *in_message);

	return bMessageSent;
}

void BrainCloudRSComms::processRegisteredListeners(const FString &in_service, const FString &in_operation, const FString &in_jsonMessage)
{
	// does this go to one of our registered service listeners?
	if (m_registeredRSBluePrintCallbacks != nullptr)
	{
		m_registeredRSBluePrintCallbacks->rsCallback(in_jsonMessage);
	}
	else if (m_registeredRSCallbacks != nullptr)
	{
		m_registeredRSCallbacks->rsCallback(in_jsonMessage);
	}
	// are we actually connected? only pump this back, when the server says we've connected
	else if (in_operation == TEXT("connect"))
	{
		m_bIsConnected = true;

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
			disconnectImpl();
		}

		// error callback!
		if (m_appCallback != nullptr)
		{
			m_appCallback->serverError(ServiceName::RTTRegistration, ServiceOperation::Connect, 400, -1, in_jsonMessage);
		}
	}
}

void BrainCloudRSComms::setupWebSocket(const FString &in_url)
{
#if PLATFORM_UWP
#elif PLATFORM_HTML5
#else
	if (m_lwsContext == nullptr)
	{
		struct lws_context_creation_info info;
		memset(&info, 0, sizeof info);

		info.protocols = protocolsRS;
		info.ssl_cert_filepath = NULL;
		info.ssl_private_key_filepath = NULL;

		info.port = -1;
		info.gid = -1;
		info.uid = -1;
		info.extensions = extsRS;
		info.options = LWS_SERVER_OPTION_VALIDATE_UTF8;
		info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;

		m_lwsContext = lws_create_context(&info);
	}
#endif

	// lazy load
	if (m_connectedSocket == nullptr)
	{
		m_connectedSocket = NewObject<UWebSocketBase>();
		m_connectedSocket->AddToRoot();
	}

	// lazy load
	if (m_commsPtr == nullptr)
	{
		m_commsPtr = NewObject<UBCRSCommsProxy>();
		m_commsPtr->AddToRoot();
	}
	m_commsPtr->SetRSComms(this);
	m_connectedSocket->OnConnectError.AddDynamic(m_commsPtr, &UBCRSCommsProxy::WebSocket_OnError);
	m_connectedSocket->OnClosed.AddDynamic(m_commsPtr, &UBCRSCommsProxy::WebSocket_OnClose);
	m_connectedSocket->OnConnectComplete.AddDynamic(m_commsPtr, &UBCRSCommsProxy::Websocket_OnOpen);
	m_connectedSocket->OnReceiveData.AddDynamic(m_commsPtr, &UBCRSCommsProxy::WebSocket_OnMessage);
	m_connectedSocket->mlwsContext = m_lwsContext;

	//m_connectedSocket->Connect(in_url, m_rttHeadersMap);
}

void BrainCloudRSComms::webSocket_OnClose()
{
	if (m_client->isLoggingEnabled())
		UE_LOG(LogBrainCloudComms, Log, TEXT("Connection closed"));

	processRegisteredListeners(ServiceName::RTTRegistration.getValue().ToLower(), "error", buildRSRequestError("Could not connect at this time"));
}

void BrainCloudRSComms::websocket_OnOpen()
{
	// first time connecting? send the server connection call
	//send(buildConnectionRequest());
}

void BrainCloudRSComms::webSocket_OnMessage(const FString &in_message)
{
	onRecv(in_message);
}

void BrainCloudRSComms::webSocket_OnError(const FString &in_message)
{
	if (m_client->isLoggingEnabled())
		UE_LOG(LogBrainCloudComms, Log, TEXT("Error: %s"), *in_message);

	processRegisteredListeners(ServiceName::RTTRegistration.getValue().ToLower(), "disconnect", buildRSRequestError(in_message));
}

void BrainCloudRSComms::onRecv(const FString &in_message)
{
	
}

FString BrainCloudRSComms::buildRSRequestError(FString in_statusMessage)
{
	TSharedRef<FJsonObject> json = MakeShareable(new FJsonObject());
	
    json->SetNumberField("status", 403);
	json->SetNumberField("reason_code", ReasonCodes::RS_CLIENT_ERROR);
	json->SetStringField("status_message", in_statusMessage);
	json->SetStringField("severity", "ERROR");

	FString response;
    TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&response);
    FJsonSerializer::Serialize(json, writer);

	return response;
}
