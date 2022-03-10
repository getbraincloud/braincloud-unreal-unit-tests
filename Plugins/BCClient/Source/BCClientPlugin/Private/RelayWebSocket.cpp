#include "RelayWebSocket.h"
#include "WebSocketBase.h"

#define MAX_PAYLOAD 1024

#if PLATFORM_UWP
#if ENGINE_MINOR_VERSION <24
#if PLATFORM_HTML5
#endif
#endif
#else
static struct lws_protocols protocolsRS[] = {
	/* first protocol must always be HTTP handler */

	{
		"bcrs",
		&BrainCloud::RelayWebSocket::callback_echo,
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

namespace BrainCloud
{
#if PLATFORM_UWP
#if ENGINE_MINOR_VERSION <24
#if PLATFORM_HTML5
#endif
#endif
#else
    int RelayWebSocket::callback_echo(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
    {
        void *pUser = lws_wsi_user(wsi);
        UWebSocketBase *pWebSocketBase = (UWebSocketBase *)pUser;

        switch (reason)
        {
            case LWS_CALLBACK_WSI_DESTROY:
            case LWS_CALLBACK_CLOSED_CLIENT_HTTP:
            case LWS_CALLBACK_CLOSED:
            {
                if (!pWebSocketBase)
                    return -1;
                pWebSocketBase->Cleanlws();
                if (pWebSocketBase->mWebSocketBaseCallbacks) pWebSocketBase->mWebSocketBaseCallbacks->OnClosed();
                pWebSocketBase->OnClosed.Broadcast();
                break;
            }
            case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
            {
                if (!pWebSocketBase || !in) return -1;
                FString strError = ANSI_TO_TCHAR(in);
                pWebSocketBase->Cleanlws();
                if (pWebSocketBase->mWebSocketBaseCallbacks) pWebSocketBase->mWebSocketBaseCallbacks->OnConnectError(strError);
                pWebSocketBase->OnConnectError.Broadcast(strError);
                break;
            }
            case LWS_CALLBACK_CLIENT_ESTABLISHED:
            {
                if (!pWebSocketBase)
                    return -1;
                if (pWebSocketBase->mWebSocketBaseCallbacks) pWebSocketBase->mWebSocketBaseCallbacks->OnConnectComplete();
                pWebSocketBase->OnConnectComplete.Broadcast();
                break;
            }
            case LWS_CALLBACK_CLIENT_RECEIVE:
            {
                if (!pWebSocketBase || !in)
                    return -1;
                pWebSocketBase->ProcessRead((const char *)in, (int)len);
                break;
            }
            case LWS_CALLBACK_CLIENT_WRITEABLE:
            {
                if (!pWebSocketBase)
                    return -1;
                pWebSocketBase->ProcessWriteable();
                break;
            }
            default:
                break;
        }

        return 0;
    }
#endif

    RelayWebSocket::RelayWebSocket(const FString &host, int port, bool sslEnabled)
    {
        FString url = (sslEnabled ? "wss://" : "ws://") + host + ":" + FString::FromInt(port);

#if PLATFORM_UWP
#if ENGINE_MINOR_VERSION <24
#if PLATFORM_HTML5
#endif
#endif
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
            m_connectedSocket->mWebSocketBaseCallbacks = this;
            m_connectedSocket->AddToRoot();
        }

#if PLATFORM_UWP
#if ENGINE_MINOR_VERSION <24
#if PLATFORM_HTML5
#endif
#endif
#else
        m_connectedSocket->mlwsContext = m_lwsContext;
#endif

        // no headers at the moment
        TMap<FString, FString> headersMap;
        m_connectedSocket->Connect(url, headersMap);
    }

    RelayWebSocket::~RelayWebSocket()
    {
        close();

        FScopeLock Lock(&m_mutex);
        if (m_connectedSocket != nullptr)
        {
            m_connectedSocket->RemoveFromRoot();
            m_connectedSocket = nullptr;
        }
    }

    bool RelayWebSocket::isConnected()
    {
        return m_isConnected;
    }
    
    bool RelayWebSocket::isValid()
    {
        return m_isValid;
    }

    void RelayWebSocket::updateConnection()
    {
        FScopeLock Lock(&m_mutex);
        m_isConnected = m_isSocketConnected;
    }

    void RelayWebSocket::send(const uint8* pData, int size)
    {
        FScopeLock Lock(&m_mutex);
        if (m_connectedSocket)
        {
            TArray<uint8> data;
            data.SetNum(size, false);
            memcpy(data.GetData(), pData, size);
            m_connectedSocket->SendData(data);
        }
    }

    const uint8* RelayWebSocket::peek(int& size)
    {
        {
            FScopeLock Lock(&m_mutex);
            if (m_packetQueue.Num() == 0) return nullptr;

            m_currentPacket = m_packetQueue[0];
            m_packetQueue.RemoveAt(0);
        }

        size = (int)m_currentPacket.Num();
        return m_currentPacket.GetData();
    }

    void RelayWebSocket::close()
    {
        FScopeLock Lock(&m_mutex);
        m_isConnected = false;
        m_isSocketConnected = false;
        m_isValid = false;
        m_packetQueue.Empty(0);
    }

    void RelayWebSocket::OnConnectError(const FString &error)
    {
        UE_LOG(LogBrainCloudRelayComms, Log, TEXT("RelayWebScoket OnConnectError: %s"), *error);
        close();

        FScopeLock Lock(&m_mutex);
        if (!m_connectedSocket) return;
        m_isValid = false;
    }

    void RelayWebSocket::OnClosed()
    {
        UE_LOG(LogBrainCloudRelayComms, Log, TEXT("RelayWebScoket OnClosed"));
        close();
    }

    void RelayWebSocket::OnConnectComplete()
    {
        UE_LOG(LogBrainCloudRelayComms, Log, TEXT("RelayWebScoket OnConnectComplete"));
        FScopeLock Lock(&m_mutex);
        if (!m_connectedSocket) return;
        m_isSocketConnected = true;
    }

    void RelayWebSocket::OnReceiveData(const TArray<uint8> &data)
    {
        UE_LOG(LogBrainCloudRelayComms, Log, TEXT("RelayWebScoket OnReceiveData"));
        FScopeLock Lock(&m_mutex);
        if (!m_connectedSocket) return;
        m_packetQueue.Add(data);
    }

    void RelayWebSocket::update()
    {
#if PLATFORM_UWP
#if ENGINE_MINOR_VERSION <24
#if PLATFORM_HTML5
#endif
#endif
#else
		if (m_lwsContext != nullptr)
		{
			lws_callback_on_writable_all_protocol(m_lwsContext, &protocolsRS[0]);
			lws_service(m_lwsContext, 0);
		}
#endif
    }
};
