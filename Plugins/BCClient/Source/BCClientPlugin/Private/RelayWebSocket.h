#pragma once

#include "IRelaySocket.h"

#if PLATFORM_UWP
    #if ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION < 24
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

#include "WebSocketBase.h"

namespace BrainCloud
{
    class RelayWebSocket : public IRelaySocket, public IWebSocketBaseCallbacks
    {
    public:
        RelayWebSocket(const FString &host, int port, bool sslEnabled);
        virtual ~RelayWebSocket();

        bool isConnected() override;
        bool isValid() override;
        
        void update() override;
        void updateConnection() override; // Call each frame when !isConnected and isValid

        void send(const uint8* pData, int size) override;
        const uint8* peek(int& size) override; // Returns null if nothing to read

        void close() override;

        // Websocket callback, don't call this directly
        static int callback_echo(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len);

    private:
        void OnConnectError(const FString &error) override;
        void OnClosed() override;
        void OnConnectComplete() override;
        void OnReceiveData(const TArray<uint8> &data) override;

        FCriticalSection m_mutex;
        bool m_isConnected = false;
        bool m_isSocketConnected = false;
        bool m_isValid = true;
	    struct lws_context *m_lwsContext = nullptr;
	    UWebSocketBase *m_connectedSocket = nullptr;
        TArray<TArray<uint8>> m_packetQueue;
        TArray<uint8> m_currentPacket;
    };
};
