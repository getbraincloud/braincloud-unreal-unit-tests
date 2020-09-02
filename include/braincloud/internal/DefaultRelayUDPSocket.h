#ifndef _DEFAULTRELAYUDPSOCKET_H_
#define _DEFAULTRELAYUDPSOCKET_H_

#include "braincloud/internal/IRelayUDPSocket.h"

#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <atomic>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
using SOCKET = int;

namespace BrainCloud
{
    class DefaultRelayUDPSocket final : public IRelayUDPSocket
    {
    public:
        ~DefaultRelayUDPSocket();

        void updateConnection() override;

        bool isConnected() override;
        bool isValid() override;

        void send(const uint8_t* pData, int size) override;
        const uint8_t* peek(int& size) override; // Returns null if nothing to read

        void close() override;

    protected:
        friend class IRelayUDPSocket;

        DefaultRelayUDPSocket(const std::string& address, int port, int maxPacketSize);

    private:
        enum class State
        {
            Connecting,
            Connected,
            Error
        };

        bool poll();

        SOCKET m_socket = INVALID_SOCKET;
        std::atomic<State> m_state;

        fd_set m_fdsSet;
        fd_set m_fdsRead;
        fd_set m_fdsWrite;

        sockaddr_in m_destination;
        int m_maxPacketSize;
        uint8_t* m_buffer;
    };
};

#endif /* _DEFAULTRELAYUDPSOCKET_H_ */
