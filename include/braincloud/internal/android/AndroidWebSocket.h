#ifndef _ANDROIDWEBSOCKET_H_
#define _ANDROIDWEBSOCKET_H_

#include "braincloud/internal/IWebSocket.h"

namespace BrainCloud
{
    class AndroidWebSocket : public IWebSocket
    {
    public:
        virtual ~AndroidWebSocket();

        virtual bool isValid();

        virtual void send(const std::string& message);
        virtual std::string recv();

        virtual void close();

    protected:
        friend class IWebSocket;

        AndroidWebSocket(const std::string& address, int port, const std::map<std::string, std::string>& headers);
    };
};

#endif /* _ANDROIDWEBSOCKET_H_ */
