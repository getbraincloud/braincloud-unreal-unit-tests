#ifndef _WIN32RELAYUDPSOCKET_H_
#define _WIN32RELAYUDPSOCKET_H_

#include "braincloud/internal/IRelayUDPSocket.h"

#include <winsock2.h>
#include <windows.h>
#include <thread>
#include <atomic>

namespace BrainCloud
{
    class Win32RelayUDPSocket final : public IRelayUDPSocket
    {
    public:
        ~Win32RelayUDPSocket();

        void updateConnection() override;

        bool isConnected() override;
        bool isValid() override;

        void send(const uint8_t* pData, int size) override;
        const uint8_t* peek(int& size) override; // Returns null if nothing to read

        void close() override;

    protected:
        friend class IRelayUDPSocket;

        Win32RelayUDPSocket(const std::string& address, int port, int maxPacketSize);

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

#endif /* _WIN32RELAYUDPSOCKET_H_ */
