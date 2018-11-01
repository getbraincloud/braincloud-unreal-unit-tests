#ifndef _UWPWEBSOCKER_H_
#define _UWPWEBSOCKER_H_

#include "braincloud/internal/IWebSocket.h"

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
    class UWPWebSocket : public IWebSocket
    {
    public:
        static int libWebsocketsCallback(struct lws* wsi, enum lws_callback_reasons reason, void* user, void* in, size_t len);

        virtual ~UWPWebSocket();

        virtual bool isValid();

        virtual void send(const std::string& message);
        virtual std::string recv();

        virtual void close();

    protected:
        friend class IWebSocket;

        UWPWebSocket(const std::string& address, int port, const std::map<std::string, std::string>& headers);

    private:
    };
};

#endif /* _UWPWEBSOCKER_H_ */
