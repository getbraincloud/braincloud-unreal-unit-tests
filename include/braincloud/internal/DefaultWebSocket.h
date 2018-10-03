#if (TARGET_OS_WATCH != 1)

#ifndef _DEFAULTWEBSOCKER_H_
#define _DEFAULTWEBSOCKER_H_

#include "braincloud/internal/IWebSocket.h"

#include <libwebsockets.h>

#include <atomic>
#include <condition_variable>
#include <map>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

namespace BrainCloud
{
    class DefaultWebSocket;

    class DefaultWebSocket : public IWebSocket
    {
    public:
        static int libWebsocketsCallback(struct lws* wsi, enum lws_callback_reasons reason, void* user, void* in, size_t len);

        virtual ~DefaultWebSocket();

        virtual bool isValid();

        virtual void send(const std::string& message);
        virtual std::string recv();

        virtual void close();

    protected:
        friend class IWebSocket;

        DefaultWebSocket(const std::string& address, int port, const std::map<std::string, std::string>& headers);

    private:
        void onClose();
        void onError(const char* msg);
        void onConnect();
        void onRecv(const char* buffer, int len);
        bool onProcessHeaders(unsigned char** ppBuffer, unsigned char* pEnd);
        void processSendQueue();

        // State
        bool _isValid;
        bool _isConnecting;

        // Update and send queue
        std::mutex _mutex;
        std::queue<std::string> _sendQueue;
        std::vector<uint8_t> _sendBuffer;
        std::thread _updateThread;

        // Connection
        std::condition_variable _connectionCondition;

        // Receiving queue
        std::mutex _recvMutex;
        std::queue<std::string> _recvQueue;
        std::condition_variable _recvCondition;

        // Context
        static struct lws_context* s_pLwsContext;
        struct lws* _pLws;
        std::map<std::string, std::string> _authHeaders;
    };
};

#endif /* _DEFAULTTCPSOCKER_H_ */

#endif