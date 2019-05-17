// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudRelayComms.h"

#include "Serialization/JsonTypes.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#include "JsonUtil.h"
#include "BCBlueprintRelayCallProxyBase.h"
#include "IServerCallback.h"
#include "ServerCall.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "BrainCloudClient.h"
#include "BCFileUploader.h"
#include "ReasonCodes.h"
#include "HttpCodes.h"

#include "BCRelayCommsProxy.h"
#include "WebSocketBase.h"
#include <iostream>

#if PLATFORM_UWP
#elif PLATFORM_HTML5
#else
static struct lws_protocols protocolsRS[] = {
	/* first protocol must always be HTTP handler */

	{
		"bcrs",
		&BrainCloudRelayComms::callback_echo,
		MAX_PAYLOAD,
		MAX_PAYLOAD,
	},
	{
		NULL, NULL, 0 /* End of list */
	} };

static const struct lws_extension extsRS[] = {
	{"permessage-deflate",
	 lws_extension_callback_pm_deflate,
	 "permessage-deflate; client_no_context_takeover"},
	{"deflate-frame",
	 lws_extension_callback_pm_deflate,
	 "deflate_frame"},
	{NULL, NULL, NULL /* terminator */} };
#endif

BrainCloudRelayComms::BrainCloudRelayComms(BrainCloudClient *client)
	: m_client(client)
	, m_appCallback(nullptr)
	, m_commsPtr(nullptr)
	, m_registeredRelayCallbacks(nullptr)
	, m_registeredRelayBluePrintCallbacks(nullptr)
	, m_connectedSocket(nullptr)
	, m_bIsConnected(false)
	, m_pingInterval(10000000.0f)
	, m_timeSinceLastPingRequest(0)
	, m_lastNowMS(FPlatformTime::Cycles64())
	, m_sentPing(FPlatformTime::Cycles64())
	, m_ping(99999L)
	, m_netId(-1)
	, m_lwsContext(nullptr)
{
}

BrainCloudRelayComms::~BrainCloudRelayComms()
{
	disconnectImpl();
	deregisterDataCallback();
}

void BrainCloudRelayComms::connect(BCRelayConnectionType in_connectionType, const FString &in_connectOptionsJson, IServerCallback *callback)
{
	if (!isConnected())
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
			// append the local profile ID
			m_connectOptions.Add(TEXT("profileId"), m_client->getProfileId());
		}
		// connection type
		m_connectionType = in_connectionType;
		// now connect
		startReceivingRSConnectionAsync();
	}
}

void BrainCloudRelayComms::disconnect()
{
	if (isConnected())
		processRegisteredListeners(ServiceName::Relay.getValue().ToLower(), "disconnect", buildRSRequestError("DisableRS Called"), TArray<uint8>() );
}

bool BrainCloudRelayComms::isConnected()
{
	return m_bIsConnected;
}

void BrainCloudRelayComms::registerDataCallback(IRelayCallback *callback)
{
	// must ensure data callbacks are all removed first, since a blueprint one may be added without being removed properly
	deregisterDataCallback();
	m_registeredRelayCallbacks = callback;
}

void BrainCloudRelayComms::registerDataCallback(UBCBlueprintRelayCallProxyBase *callback)
{
	// must ensure data callbacks are all removed first, since a blueprint one may be added without being removed properly
	deregisterDataCallback();
	m_registeredRelayBluePrintCallbacks = callback;
}

void BrainCloudRelayComms::deregisterDataCallback()
{
	m_registeredRelayCallbacks = nullptr;
	if (m_registeredRelayBluePrintCallbacks->IsValidLowLevel())
	{
		m_registeredRelayBluePrintCallbacks->RemoveFromRoot();
		m_registeredRelayBluePrintCallbacks->ConditionalBeginDestroy();
	}
	m_registeredRelayBluePrintCallbacks = nullptr;
}

void BrainCloudRelayComms::RunCallbacks()
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

	// run ping 
	if (isConnected())
    {
        uint64 nowMS = FPlatformTime::Cycles64();
        // the heart beat
        m_timeSinceLastPingRequest += (nowMS - m_lastNowMS);
        m_lastNowMS = nowMS;

        if (m_timeSinceLastPingRequest >= m_pingInterval)
        {
            m_timeSinceLastPingRequest = 0;
            sendPing();
        }

        //processReliableQueue();
    }
}

#if PLATFORM_UWP
#elif PLATFORM_HTML5
#else
int BrainCloudRelayComms::callback_echo(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
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


void BrainCloudRelayComms::connectWebSocket(FString in_host, int in_port, bool in_sslEnabled)
{
	FString url = (in_sslEnabled ? "wss://" : "ws://") + in_host + ":" + FString::FromInt(in_port);
	
	setupWebSocket(url);
}

void BrainCloudRelayComms::disconnectImpl()
{
	// clear everything
	if (m_connectedSocket != nullptr && m_commsPtr != nullptr)
	{
		m_commsPtr->RemoveFromRoot();
		m_connectedSocket->RemoveFromRoot();
		m_connectedSocket->OnConnectError.RemoveDynamic(m_commsPtr, &UBCRelayCommsProxy::WebSocket_OnError);
		m_connectedSocket->OnClosed.RemoveDynamic(m_commsPtr, &UBCRelayCommsProxy::WebSocket_OnClose);
		m_connectedSocket->OnConnectComplete.RemoveDynamic(m_commsPtr, &UBCRelayCommsProxy::Websocket_OnOpen);
		m_connectedSocket->OnReceiveData.RemoveDynamic(m_commsPtr, &UBCRelayCommsProxy::WebSocket_OnMessage);
	}

	delete m_commsPtr;
	m_commsPtr = nullptr;

	delete m_connectedSocket;
	m_connectedSocket = nullptr;

	lws_context_destroy(m_lwsContext);
	m_lwsContext = nullptr;

	m_bIsConnected = false;
	
	m_appCallback = nullptr;

	m_sentPing = 99999.0f;
	m_netId = -1;
	m_ping = 999999L;
}

// sends pure in_data
bool BrainCloudRelayComms::send(TArray<uint8> in_message, const uint8 in_target, 
								bool in_reliable /*= true*/, bool in_ordered/* = true*/, int in_channel/* = 0*/)
{
	bool bMessageSent = false;
	// early return
	if (m_connectedSocket == nullptr)
	{
		return bMessageSent;
	}

	// add control header to message
	TArray<uint8> header;
	header.Add(in_target);
	if (in_target == CL2RS_RELAY)
    {
        uint8 data1 = 0;
        uint8 data2 = 0;
		/*
        if (m_connectionType == RelayConnectionType.UDP)
        {
            constructReliableHeader(out data1, out data2, in_reliable, in_ordered, in_channel);
        }
		*/
		header.Add(data1);
		header.Add(data2);
    }

	// append header to message (HEADER|MESSAGE)
    TArray<uint8> toReturn = concatenateByteArrays(header, in_message);

	// append the size (SIZE|HEADER|MESSAGE)
	TArray<uint8> toSendData = appendSizeBytes(toReturn);

	// SEND IT
	bMessageSent = m_connectedSocket->SendData(toSendData);

	if (in_target != CL2RS_PING && bMessageSent && m_client->isLoggingEnabled())
	{
		FString parsedMessage = BrainCloudRelay::BCBytesToString(toSendData.GetData(), toSendData.Num());
		UE_LOG(LogBrainCloudComms, Log, TEXT("toSendData %d, %d, %d, %s"), toSendData[0], toSendData[1], toSendData[2], *parsedMessage);
	}

	return bMessageSent;
}

void BrainCloudRelayComms::setPingInterval(float in_interval)
{
    m_pingInterval = in_interval * 10000000.0f;
}

int64 BrainCloudRelayComms::ping()
{
	return m_ping / 1000;
}

uint8 BrainCloudRelayComms::netId()
{
	return (uint8)m_netId;
}

void BrainCloudRelayComms::startReceivingRSConnectionAsync()
{
	bool sslEnabled = m_connectOptions["ssl"] == "true";
	FString host = m_connectOptions["host"];
	int port = FCString::Atoi(*m_connectOptions["port"]);
	switch (m_connectionType)
	{
	case BCRelayConnectionType::WEBSOCKET:
	{
		connectWebSocket(host, port, sslEnabled);
	}
	break;
	case BCRelayConnectionType::TCP:
	{
		//connectTCPAsync(host, port);
	}
	break;
	case BCRelayConnectionType::UDP:
	{
		//connectUDPAsync(host, port);
	}
	break;
	default: break;
	}
}

TArray<uint8> BrainCloudRelayComms::concatenateByteArrays(TArray<uint8> in_bufferA, TArray<uint8> in_bufferB)
{
	TArray<uint8> toReturn;
	for (int i = 0; i < in_bufferA.Num(); ++i)
	{
		toReturn.Add(in_bufferA[i]);
	}

	for (int i = 0; i < in_bufferB.Num(); ++i)
	{
		toReturn.Add(in_bufferB[i]);
	}
	return toReturn;
}

TArray<uint8> BrainCloudRelayComms::stripByteArray(TArray<uint8> in_data, int in_numFromLeft)
{
	// take off the 
	TArray<uint8> data;
	for (int i = in_numFromLeft; i < in_data.Num(); ++i)
	{
		data.Add(in_data[i]);
	}

	return data;
}

TArray<uint8> BrainCloudRelayComms::buildConnectionRequest()
{
	TSharedRef<FJsonObject> json = MakeShareable(new FJsonObject());

	json->SetStringField("profileId", m_client->getProfileId());//"b09994cb-d91d-4060-876c-5430756ead7d"); // 
	json->SetStringField("lobbyId", m_connectOptions["lobbyId"]);
	json->SetStringField("passcode", m_connectOptions["passcode"]);

	FString response;
	TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&response);
	FJsonSerializer::Serialize(json, writer);

	TArray<uint8> in_data;
	in_data.AddUninitialized(response.Len());
	BrainCloudRelay::BCStringToBytes(response, in_data.GetData(), response.Len());

	return in_data;
}

TArray<uint8> BrainCloudRelayComms::appendSizeBytes(TArray<uint8> in_message)
{
    // size of in_data is the incoming in_data, plus the two that we're adding
	int sizeOfMessage = in_message.Num() + SIZE_OF_LENGTH_PREFIX_BYTE_ARRAY;

	TArray<uint8> lengthPrefix;
	lengthPrefix.Add(sizeOfMessage >> 8);
	lengthPrefix.Add(sizeOfMessage);

	TArray<uint8> toSend = concatenateByteArrays(lengthPrefix, in_message);
	return toSend;
}

// should be add registered listeners
void BrainCloudRelayComms::processRegisteredListeners(const FString &in_service, const FString &in_operation, const FString &in_jsonMessage, TArray<uint8> in_data)
{
	// process connect callback to app
	bool connected = isConnected();
	if (in_operation == TEXT("connect") && connected && m_appCallback != nullptr)
	{
		m_appCallback->serverCallback(ServiceName::Relay, ServiceOperation::Connect, in_jsonMessage);
		return;
	}
	// process disconnect / errors to app
	else if (in_operation == TEXT("error") || in_operation == TEXT("disconnect"))
	{
		// error callback!
		if (m_appCallback != nullptr)
		{
			m_appCallback->serverError(ServiceName::Relay, ServiceOperation::Connect, 400, -1, in_jsonMessage);
		}

		if (in_operation == TEXT("disconnect"))
			disconnectImpl();
	}

	if (!connected && in_operation == TEXT("connect"))
	{
		send(buildConnectionRequest(), CL2RS_CONNECTION);
	}

	if (in_data.Num() > 0)
	{
		// does this go to one of our registered service listeners?
		if (m_registeredRelayBluePrintCallbacks != nullptr)
		{
			m_registeredRelayBluePrintCallbacks->relayCallback(in_data);
		}
		else if (m_registeredRelayCallbacks != nullptr)
		{
			m_registeredRelayCallbacks->relayCallback(in_data);
		}
	}
}

void BrainCloudRelayComms::setupWebSocket(const FString &in_url)
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
        info.options = 0;//LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;

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
		m_commsPtr = NewObject<UBCRelayCommsProxy>();
		m_commsPtr->AddToRoot();
	}
	m_commsPtr->SetRelayComms(this);
	m_connectedSocket->OnConnectError.AddDynamic(m_commsPtr, &UBCRelayCommsProxy::WebSocket_OnError);
	m_connectedSocket->OnClosed.AddDynamic(m_commsPtr, &UBCRelayCommsProxy::WebSocket_OnClose);
	m_connectedSocket->OnConnectComplete.AddDynamic(m_commsPtr, &UBCRelayCommsProxy::Websocket_OnOpen);
	m_connectedSocket->OnReceiveData.AddDynamic(m_commsPtr, &UBCRelayCommsProxy::WebSocket_OnMessage);
	m_connectedSocket->mlwsContext = m_lwsContext;

	// no headers at the moment
	TMap<FString, FString> headersMap;
	m_connectedSocket->Connect(in_url, headersMap);
}

void BrainCloudRelayComms::sendPing()
{
	m_sentPing = FPlatformTime::Cycles64();
	
	int64 localPing = ping();
	// attach the local ping
	TArray<uint8> dataArr;
	dataArr.Add(localPing >> 8);
	dataArr.Add(localPing);
	
	send(dataArr, CL2RS_PING);
}

void BrainCloudRelayComms::webSocket_OnClose()
{
	if (m_client->isLoggingEnabled())
		UE_LOG(LogBrainCloudComms, Log, TEXT("Relay Connection closed"));

	processRegisteredListeners(ServiceName::Relay.getValue().ToLower(), "error", buildRSRequestError("Could not connect at this time"), TArray<uint8>() );
}

void BrainCloudRelayComms::websocket_OnOpen()
{
	if (m_client->isLoggingEnabled())
		UE_LOG(LogBrainCloudComms, Log, TEXT("Relay Connection established."));

	processRegisteredListeners(ServiceName::Relay.getValue().ToLower(), "connect", "", TArray<uint8>() );
}

void BrainCloudRelayComms::webSocket_OnMessage(TArray<uint8> in_data)
{
	// take off the length prefix
	TArray<uint8> data = stripByteArray(in_data, SIZE_OF_LENGTH_PREFIX_BYTE_ARRAY);

	onRecv(data);
}

void BrainCloudRelayComms::webSocket_OnError(const FString &in_message)
{
	if (m_client->isLoggingEnabled())
		UE_LOG(LogBrainCloudComms, Log, TEXT("Relay Error: %s"), *in_message);

	processRegisteredListeners(ServiceName::Relay.getValue().ToLower(), "disconnect", buildRSRequestError(in_message), TArray<uint8>() );
}

void BrainCloudRelayComms::onRecv(TArray<uint8> in_data)
{
	// the length prefix should be removed already 
	if (in_data.Num() > 0)
	{
		uint8 controlByte = in_data[0];
		if (controlByte == RS2CL_PONG)
        {
			m_ping = FPlatformTime::Cycles64() - m_sentPing;
        }
		else
		{
			TArray<uint8> data = stripByteArray(in_data, 1);

			// if netId is not setup yet
			if (m_netId < 0)
			{
				FString parsedMessage = BrainCloudRelay::BCBytesToString(data.GetData(), data.Num());
				
				TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(parsedMessage);
				TSharedPtr<FJsonObject> jsonPacket = MakeShareable(new FJsonObject());

				bool res = FJsonSerializer::Deserialize(reader, jsonPacket);

				if (res && jsonPacket->HasField(TEXT("netId")) && jsonPacket->HasField(TEXT("profileId")))
				{
					if (m_client->getProfileId() == jsonPacket->GetStringField(TEXT("profileId")))
					{
						m_netId = (short)jsonPacket->GetNumberField(TEXT("netId"));
						m_bIsConnected = true;
						
						processRegisteredListeners(ServiceName::Relay.getValue().ToLower(), "connect", parsedMessage, data );
					}
				}
			}
			
			// finally pass this onwards
			processRegisteredListeners(ServiceName::Relay.getValue().ToLower(), "onrecv", "", data);
		}
	}
}

FString BrainCloudRelayComms::buildRSRequestError(FString in_statusMessage)
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
