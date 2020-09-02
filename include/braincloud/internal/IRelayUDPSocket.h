#ifndef _IRELAYUDPSOCKET_H_
#define _IRELAYUDPSOCKET_H_

#include "IRelaySocket.h"
#include <string>

namespace BrainCloud
{
    class IRelayUDPSocket : public IRelaySocket
    {
    public:
        static IRelayUDPSocket* create(const std::string& address, int port, int maxPacketSize = 1400);

        virtual ~IRelayUDPSocket() {}

    protected:
        IRelayUDPSocket() {}
    };
};

#endif /* _IRELAYUDPSOCKET_H_ */
