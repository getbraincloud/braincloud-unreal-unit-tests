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
																   m_rttHeaders(nullptr),
																   m_endpoint(nullptr)
{
	m_commsPtr = NewObject<UBCRTTCommsProxy>();
	m_commsPtr->AddToRoot();
}

BrainCloudRTTComms::~BrainCloudRTTComms()
{
	disconnect();
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
#if PLATFORM_UWP
#elif PLATFORM_HTML5
#else
	if (m_lwsContext != nullptr)
	{
		lws_callback_on_writable_all_protocol(m_lwsContext, &protocols[0]);
		lws_service(m_lwsContext, 0);
	}
#endif
	/*
	if (!ListenerSocket)
		return;
	//Remote address
	TSharedRef<FInternetAddr> RemoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool Pending;

	// handle incoming connections
	if (ListenerSocket->HasPendingConnection(Pending) && Pending)
	{
		//Already have a Connection? destroy previous
		if (ConnectionSocket)
		{
			ConnectionSocket->Close();
			ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ConnectionSocket);
		}

		//New Connection receive!
		ConnectionSocket = ListenerSocket->Accept(*RemoteAddress, TEXT("RamaTCP Received Socket Connection"));

		if (ConnectionSocket != NULL)
		{
			//Global cache of current Remote
			//RemoteAddressForConnection = FIPv4Endpoint(RemoteAddress);

			//UE_LOG "Accepted Connection! WOOOHOOOO!!!";

			//can thread this too GetWorldTimerManager().SetTimer(this, &AYourClass::TCPSocketListener, 0.01, true);
		}
	}
	*/
}
/*
bool BrainCloudRTTComms::StartTCPReceiver(const FString &YourChosenSocketName, const FString &TheIP, const int32 ThePort)
{
	ListenerSocket = CreateTCPConnectionListener(YourChosenSocketName, TheIP, ThePort);
	if (!ListenerSocket)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("StartTCPReceiver>> Listen socket could not be created! ~> %s %d"), *TheIP, ThePort));
		return false;
	}

	//Start the Listener! //thread this eventually GetWorldTimerManager().SetTimer(this, &AYourClass::TCPConnectionListener, 0.01, true);

	return true;
}

bool BrainCloudRTTComms::FormatIP4ToNumber(const FString &TheIP, uint8 (&Out)[4])
{
	//IP Formatting
	TheIP.Replace(TEXT(" "), TEXT(""));

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //	IP 4 Parts
	TArray<FString> Parts;
	TheIP.ParseIntoArray(Parts, TEXT("."), true);
	if (Parts.Num() != 4)
		return false;

	for (int32 i = 0; i < 4; ++i)
	{
		Out[i] = FCString::Atoi(*Parts[i]);
	}

	return true;
}
FSocket *BrainCloudRTTComms::CreateTCPConnectionListener(const FString &YourChosenSocketName, const FString &TheIP, const int32 ThePort, const int32 ReceiveBufferSize)
{
	uint8 IP4Nums[4];
	if (!FormatIP4ToNumber(TheIP, IP4Nums))
	{
		//VShow("Invalid IP! Expecting 4 parts separated by .");
		return false;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//Create Socket
	//FIPv6Address();
	FIPv4Endpoint Endpoint(FIPv4Address(IP4Nums[0], IP4Nums[1], IP4Nums[2], IP4Nums[3]), ThePort);
	FSocket *ListenSocket = FTcpSocketBuilder(*YourChosenSocketName).AsReusable().BoundToEndpoint(Endpoint).Listening(8);

	//Set Buffer Size
	int32 NewSize = 0;
	ListenSocket->SetReceiveBufferSize(ReceiveBufferSize, NewSize);

	//Done!
	return ListenSocket;
}

/*
void BrainCloudRTTComms::TCPConnectionListener()
{
	if (!ListenerSocket)
		return;

	//Remote address
	TSharedRef<FInternetAddr> RemoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool Pending;

	// handle incoming connections
	if (ListenerSocket->HasPendingConnection(Pending) && Pending)
	{
		//Already have a Connection? destroy previous
		if (ConnectionSocket)
		{
			ConnectionSocket->Close();
			ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ConnectionSocket);
		}

		//New Connection receive!
		ConnectionSocket = ListenerSocket->Accept(*RemoteAddress, TEXT("RamaTCP Received Socket Connection"));

		if (ConnectionSocket != NULL)
		{
			//Global cache of current Remote
			Address RemoteAddressForConnection = FIPv4Endpoint(RemoteAddress);

			//UE_LOG "Accepted Connection! WOOOHOOOO!!!";

			//can thread this too GetWorldTimerManager().SetTimer(this, &AYourClass::TCPSocketListener, 0.01, true);
		}
	}
}

//Rama's String From Binary Array
FString BrainCloudRTTComms::StringFromBinaryArray(uint8 *BinaryArray)
{
	//BinaryArray.Add(0);
	// Add 0 termination. Even if the string is already 0-terminated, it doesn't change the results.
	// Create a string from a byte array. The string is expected to be 0 terminated (i.e. a byte set to 0).
	// Use UTF8_TO_TCHAR if needed.
	// If you happen to know the data is UTF-16 (USC2) formatted, you do not need any conversion to begin with.
	// Otherwise you might have to write your own conversion algorithm to convert between multilingual UTF-16 planes.
	return FString(ANSI_TO_TCHAR(reinterpret_cast<const char*>(BinaryArray)));
}
*/
#if PLATFORM_UWP
#elif PLATFORM_HTML5
#else
int BrainCloudRTTComms::callback_echo(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
{
	void *pUser = lws_wsi_user(wsi);
	UWebSocketBase *pWebSocketBase = (UWebSocketBase *)pUser;

	if (reason != 31 &&
		reason != 32 &&
		reason != 33 &&
		reason != 34 &&
		reason != 35 &&
		reason != 36)
	{
		UE_LOG(WebSocket, Warning, TEXT("lws_callback_reasons :%d"), reason);

		UWebSocketBase *pWebSocketBase2 = (UWebSocketBase *)user;

		if (!pWebSocketBase)
			UE_LOG(WebSocket, Warning, TEXT("pWebSocketBase :%d"), reason);

		if (!pWebSocketBase2)
			UE_LOG(WebSocket, Warning, TEXT("pWebSocketBase2 :%d"), reason);
	}

	switch (reason)
	{
	case LWS_CALLBACK_CLOSED_CLIENT_HTTP:
	case LWS_CALLBACK_CLOSED:

		UE_LOG(WebSocket, Warning, TEXT("web socket CLOSED -- "));
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
		UE_LOG(WebSocket, Warning, TEXT("web socket Established -- "));
		if (!pWebSocketBase)
			return -1;
		pWebSocketBase->OnConnectComplete.Broadcast();
		break;

	case LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER:
	{
		UE_LOG(WebSocket, Warning, TEXT("web socket handshake header -- "));
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
		UE_LOG(WebSocket, Warning, TEXT("web socket client receive -- "));
		if (!pWebSocketBase)
			return -1;
		pWebSocketBase->ProcessRead((const char *)in, (int)len);
		break;

	case LWS_CALLBACK_CLIENT_WRITEABLE:
		UE_LOG(WebSocket, Warning, TEXT("web socket client writable -- "));
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
	m_lwsContext = nullptr;

	// clear everything
	if (m_connectedSocket != nullptr)
	{
		m_connectedSocket->OnConnectError.RemoveDynamic(m_commsPtr, &UBCRTTCommsProxy::WebSocket_OnError);
		m_connectedSocket->OnClosed.RemoveDynamic(m_commsPtr, &UBCRTTCommsProxy::WebSocket_OnClose);
		m_connectedSocket->OnConnectComplete.RemoveDynamic(m_commsPtr, &UBCRTTCommsProxy::Websocket_OnOpen);
		m_connectedSocket->OnReceiveData.RemoveDynamic(m_commsPtr, &UBCRTTCommsProxy::WebSocket_OnMessage);
	}

	delete m_connectedSocket;
	m_connectedSocket = nullptr;
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

	//FString url = TEXT("wss://echo.websocket.org");

	setupWebSocket(url);
}

void BrainCloudRTTComms::setupWebSocket(const FString &in_url)
{
	if (m_client->isLoggingEnabled())
		UE_LOG(LogBrainCloudComms, Warning, TEXT("Connection Request Started %s"), *in_url);

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

	m_connectedSocket = NewObject<UWebSocketBase>();
	m_connectedSocket->AddToRoot();

	m_commsPtr->SetRTTComms(this);
	m_connectedSocket->OnConnectError.AddDynamic(m_commsPtr, &UBCRTTCommsProxy::WebSocket_OnError);
	m_connectedSocket->OnClosed.AddDynamic(m_commsPtr, &UBCRTTCommsProxy::WebSocket_OnClose);
	m_connectedSocket->OnConnectComplete.AddDynamic(m_commsPtr, &UBCRTTCommsProxy::Websocket_OnOpen);
	m_connectedSocket->OnReceiveData.AddDynamic(m_commsPtr, &UBCRTTCommsProxy::WebSocket_OnMessage);
	m_connectedSocket->mlwsContext = m_lwsContext;

	m_rttHeadersMap.Empty();
	m_rttHeadersMap.Add(TEXT("Authorization"), TEXT("Basic MjAwMDE6bXlzZWNyZXQx"));

	m_connectedSocket->Connect(in_url, m_rttHeadersMap);
	/*
	FString connectRequest = buildConnectionRequest();

	if (m_client->isLoggingEnabled())
		UE_LOG(LogBrainCloudComms, Warning, TEXT("connectRequest -- %s"), *connectRequest);

	m_connectedSocket->SendText(connectRequest);
	*/
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
