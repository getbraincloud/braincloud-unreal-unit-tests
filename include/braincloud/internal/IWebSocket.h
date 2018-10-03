#ifndef _IWEBSOCKET_H_
#define _IWEBSOCKET_H_

#include "ISocket.h"

#include <map>
#include <string>

namespace BrainCloud
{
    class IWebSocket : public ISocket
    {
    public:
        static IWebSocket* create(const std::string& address, int port, const std::map<std::string, std::string>& headers);

        virtual ~IWebSocket() {}

    protected:
        IWebSocket() {}
    };
};

#endif /* _IWEBSOCKET_H_ */
