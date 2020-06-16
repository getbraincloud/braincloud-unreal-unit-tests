#ifndef _IRELAYTCPSOCKET_H_
#define _IRELAYTCPSOCKET_H_

#include "IRelaySocket.h"
#include <string>

namespace BrainCloud
{
    class IRelayTCPSocket : public IRelaySocket
    {
    public:
        static IRelayTCPSocket* create(const std::string& address, int port, int maxPacketSize = 1400);

        virtual ~IRelayTCPSocket() {}

    protected:
        IRelayTCPSocket() {}
    };
};

#endif /* _IRELAYTCPSOCKET_H_ */
