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

#if PLATFORM_UWP
#elif PLATFORM_HTML5
#else
static struct lws_protocols protocolsRS[] = {
	/* first protocol must always be HTTP handler */

	{
		"bcrs",
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
	: m_client(client), m_appCallback(nullptr), m_commsPtr(nullptr), m_registeredRSCallbacks(nullptr), m_registeredRSBluePrintCallbacks(nullptr), m_connectedSocket(nullptr), m_bIsConnected(false), m_lwsContext(nullptr)
{
}

BrainCloudRSComms::~BrainCloudRSComms()
{
	disconnectImpl();
	deregisterDataCallback();
}

void BrainCloudRSComms::connect(eBCRSConnectionType in_connectionType, const FString &in_connectOptionsJson, IServerCallback *callback)
{
	if (!m_bIsConnected)
	{
		// the callback
		m_appCallback = callback;
		// read options json
		//  --- ssl
		//  --- host
		//  --- port
		//  --- passcode
		//  --- lobbyId
		TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(in_connectOptionsJson);
		TSharedPtr<FJsonObject> jsonPacket = MakeShareable(new FJsonObject());
		bool res = FJsonSerializer::Deserialize(reader, jsonPacket);
		if (res)
		{
			// clear this, since we add them within the iterator
			m_connectOptions.Empty();
			// Iterate over Json Values
			for (auto currJsonValue = jsonPacket->Values.CreateConstIterator(); currJsonValue; ++currJsonValue)
			{
				TSharedPtr<FJsonValue> Value = (*currJsonValue).Value;
				m_connectOptions.Add((*currJsonValue).Key, Value->AsString());
			}
		}
		// connection type
		m_connectionType = in_connectionType;
		// now connect
		startReceivingRSConnectionAsync();
	}
}

void BrainCloudRSComms::disconnect()
{
	if (m_bIsConnected)
		processRegisteredListeners(ServiceName::RoomServer.getValue().ToLower(), "disconnect", buildRSRequestError("DisableRS Called"));
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
		FString strError = ANSI_TO_TCHAR(in);
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

void BrainCloudRSComms::connectWebSocket(FString in_host, int in_port, bool in_sslEnabled)
{
	FString url = (in_sslEnabled ? "wss://" : "ws://") + in_host + ":" + FString::FromInt(in_port);
	UE_LOG(LogBrainCloudComms, Log, TEXT("connectWebSocket:  %s"), *url);
	setupWebSocket(url);
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

	lws_context_destroy(m_lwsContext);
	m_lwsContext = nullptr;
	m_bIsConnected = false;
}

// sends pure text
bool BrainCloudRSComms::send(const FString &in_message, uint8 in_controlHeader /*= RECV_CTRL_RSMG*/)
{
	TArray<uint8> data;
	data.AddUninitialized(in_message.Len());
	StringToBytes(in_message, data.GetData(), in_message.Len());

	return send(data, in_controlHeader);
}

// sends pure data
bool BrainCloudRSComms::send(TArray<uint8> in_message, uint8 in_controlHeader /*= RECV_CTRL_RSMG*/)
{
	bool bMessageSent = false;
	// early return
	if (m_connectedSocket == nullptr)
	{
		return bMessageSent;
	}

	//if (m_client->isLoggingEnabled())
	{
		FString parsedMessage = BytesToString(in_message.GetData(), in_message.Num());
		UE_LOG(LogBrainCloudComms, Log, TEXT("send: %s"), *parsedMessage);

		UE_LOG(LogBrainCloudComms, Log, TEXT("RTT SEND: size of message before %d"), in_message.Num());
	}

	// add control header to message
	TArray<uint8> header;
	header.Add(in_controlHeader);
	TArray<uint8> toReturn = concatenateByteArrays(header, in_message);

	// append the size
	TArray<uint8> toSendData = appendSizeBytes(toReturn);
	bMessageSent = m_connectedSocket->SendData(toSendData.GetData());

	//if (m_client->isLoggingEnabled())
	{
		UE_LOG(LogBrainCloudComms, Log, TEXT("RTT SEND: size[0] %d"), toSendData[0]);
		UE_LOG(LogBrainCloudComms, Log, TEXT("RTT SEND: size[1] %d"), toSendData[1]);
		UE_LOG(LogBrainCloudComms, Log, TEXT("RTT SEND: header %d"), toSendData[2]);

		UE_LOG(LogBrainCloudComms, Log, TEXT("RTT SEND: size of message After %d"), toSendData.Num());
	}

	return bMessageSent;
}

void BrainCloudRSComms::ping()
{
}

void BrainCloudRSComms::startReceivingRSConnectionAsync()
{
	bool sslEnabled = m_connectOptions["ssl"] == "true";
	FString host = m_connectOptions["host"];
	int port = FCString::Atoi(*m_connectOptions["port"]);
	switch (m_connectionType)
	{
	case eBCRSConnectionType::WEBSOCKET:
	{
		connectWebSocket(host, port, sslEnabled);
	}
	break;
	case eBCRSConnectionType::TCP:
	{
		//connectTCPAsync(host, port);
	}
	break;
	case eBCRSConnectionType::UDP:
	{
		//connectUDPAsync(host, port);
	}
	break;
	default:
		break;
	}
}

TArray<uint8> BrainCloudRSComms::concatenateByteArrays(TArray<uint8> in_bufferA, TArray<uint8> in_bufferB)
{
	TArray<uint8> toReturn;
	for (int i = 0; i < in_bufferA.Num(); ++i)
	{
		//if (in_bufferA[i] != 0x0)
		toReturn.Add(in_bufferA[i]);
	}

	for (int i = 0; i < in_bufferB.Num(); ++i)
	{
		//if (in_bufferB[i] != 0x0)
		toReturn.Add(in_bufferB[i]);
	}
	return toReturn;
}

FString BrainCloudRSComms::buildConnectionRequest()
{
	TSharedRef<FJsonObject> json = MakeShareable(new FJsonObject());

	json->SetStringField("profileId", "b09994cb-d91d-4060-876c-5430756ead7d"); //m_client->getProfileId());
	json->SetStringField("lobbyId", m_connectOptions["lobbyId"]);
	json->SetStringField("passcode", m_connectOptions["passcode"]);

	FString response;
	TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&response);
	FJsonSerializer::Serialize(json, writer);

	return response;
}

TArray<uint8> BrainCloudRSComms::appendSizeBytes(TArray<uint8> in_message)
{
	int sizeOfMessage = in_message.Num();

	UE_LOG(LogBrainCloudComms, Log, TEXT("appendSizeBytes: sizeOfMessage %d"), sizeOfMessage);

	TArray<uint8> lengthPrefix;
	lengthPrefix.Add(sizeOfMessage >> 8);
	lengthPrefix.Add(sizeOfMessage);

	TArray<uint8> toSend = concatenateByteArrays(lengthPrefix, in_message);
	return toSend;
}

void BrainCloudRSComms::processRegisteredListeners(const FString &in_service, const FString &in_operation, const FString &in_jsonMessage)
{
	// process connect callback to app
	if (in_operation == TEXT("connect") && m_bIsConnected && m_appCallback != nullptr)
	{
		m_appCallback->serverCallback(ServiceName::RoomServer, ServiceOperation::Connect, in_jsonMessage);
	}
	// process disconnect / errors to app
	else if (m_bIsConnected && (in_operation == TEXT("error") || in_operation == TEXT("disconnect")))
	{
		if (in_operation == TEXT("disconnect"))
			disconnectImpl();

		// error callback!
		if (m_appCallback != nullptr)
		{
			m_appCallback->serverError(ServiceName::RoomServer, ServiceOperation::Connect, 400, -1, in_jsonMessage);
		}
	}

	if (!m_bIsConnected && in_operation == TEXT("connect"))
	{
		m_bIsConnected = true;
		send(buildConnectionRequest());
	}

	// does this go to one of our registered service listeners?
	if (m_registeredRSBluePrintCallbacks != nullptr)
	{
		m_registeredRSBluePrintCallbacks->rsCallback(in_jsonMessage);
	}

	if (m_registeredRSCallbacks != nullptr)
	{
		m_registeredRSCallbacks->rsCallback(in_jsonMessage);
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
		info.options = 0; //LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;

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

	// no headers at the moment
	TMap<FString, FString> headersMap;
	m_connectedSocket->Connect(in_url, headersMap);

	send(buildConnectionRequest());
	//send(buildConnectionRequestTest());
}

void BrainCloudRSComms::webSocket_OnClose()
{
	//if (m_client->isLoggingEnabled())
	UE_LOG(LogBrainCloudComms, Log, TEXT("Connection closed"));

	processRegisteredListeners(ServiceName::RoomServer.getValue().ToLower(), "error", buildRSRequestError("Could not connect at this time"));
}

void BrainCloudRSComms::websocket_OnOpen()
{
	//if (m_client->isLoggingEnabled())
	UE_LOG(LogBrainCloudComms, Log, TEXT("Connection established."));

	processRegisteredListeners(ServiceName::RoomServer.getValue().ToLower(), "connect", "");
}

void BrainCloudRSComms::webSocket_OnMessage(const FString &in_message)
{
	onRecv(in_message);
}

void BrainCloudRSComms::webSocket_OnError(const FString &in_message)
{
	//if (m_client->isLoggingEnabled())
	UE_LOG(LogBrainCloudComms, Log, TEXT("Error: %s"), *in_message);

	processRegisteredListeners(ServiceName::RoomServer.getValue().ToLower(), "disconnect", buildRSRequestError(in_message));
}

void BrainCloudRSComms::onRecv(const FString &in_message)
{
	//if (m_client->isLoggingEnabled())
	UE_LOG(LogBrainCloudComms, Log, TEXT("%s"), * in_message);
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
