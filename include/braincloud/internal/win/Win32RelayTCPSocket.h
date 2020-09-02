#ifndef _WIN32RELAYTCPSOCKER_H_
#define _WIN32RELAYTCPSOCKER_H_

#include "braincloud/internal/IRelayTCPSocket.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <thread>
#include <atomic>

namespace BrainCloud
{
	class Win32RelayTCPSocket final : public IRelayTCPSocket
	{
	public:
		~Win32RelayTCPSocket();

		void updateConnection() override;

		bool isConnected() override;
		bool isValid() override;

		void send(const uint8_t* pData, int size) override;
		const uint8_t* peek(int& size) override; // Returns null if nothing to read

		void close() override;

	protected:
		friend class IRelayTCPSocket;

		Win32RelayTCPSocket(const std::string& address, int port, int maxPacketSize);

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

#endif /* _WIN32RELAYTCPSOCKER_H_ */
