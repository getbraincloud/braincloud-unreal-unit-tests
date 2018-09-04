#ifndef _WIN32TCPSOCKER_H_
#define _WIN32TCPSOCKER_H_

#include "braincloud/internal/ITCPSocket.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <vector>

namespace BrainCloud
{
	class Win32TCPSocket : public ITCPSocket
	{
	public:
		virtual ~Win32TCPSocket();

		virtual bool isValid();

		virtual void send(const std::string& message);
		virtual std::string recv();

		virtual void close();

	protected:
		friend class ITCPSocket;

		Win32TCPSocket(const std::string& address, int port);

	private:
		SOCKET _socket;

		bool _isValid;
		char _readBuf[512];
		int _sizeOnBuf;
		std::string _message;
		std::vector<char> _sendBuf;
	};
};

#endif /* _WIN32TCPSOCKER_H_ */
