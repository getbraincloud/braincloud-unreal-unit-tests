#ifndef _DEFAULTRELAYTCPSOCKER_H_
#define _DEFAULTRELAYTCPSOCKER_H_

#include "braincloud/internal/IRelayTCPSocket.h"

#include <thread>
#include <atomic>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h> 
#include <unistd.h>
#include <strings.h>
#include <memory.h>
#include <fcntl.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
using SOCKET = int;

namespace BrainCloud
{
    class DefaultRelayTCPSocket final : public IRelayTCPSocket
    {
    public:
        ~DefaultRelayTCPSocket();

        void updateConnection() override;

        bool isConnected() override;
        bool isValid() override;

        void send(const uint8_t* pData, int size) override;
        const uint8_t* peek(int& size) override; // Returns null if nothing to read

        void close() override;

    protected:
        friend class IRelayTCPSocket;

        DefaultRelayTCPSocket(const std::string& address, int port, int maxPacketSize);

    private:
        enum class State
        {
            FetchingRemotes,
            Connecting,
            Connected,
            Error
        };

        void connect(addrinfo* pAddress);
        bool poll();

        SOCKET m_socket = INVALID_SOCKET;
        std::atomic<State> m_state;

        struct addrinfo* m_pRemoteAddresses = nullptr;
        struct addrinfo* m_pRemoteAddress = nullptr;
        std::thread m_getAddrInfoThread;

        fd_set m_fdsSet;
        fd_set m_fdsRead;
        fd_set m_fdsWrite;

        int m_maxPacketSize;
        int m_read = 0;
        uint8_t* m_buffer;
    };
};

#endif /* _DEFAULTRELAYTCPSOCKER_H_ */
