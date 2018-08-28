#include "braincloud/internal/win/Win32TCPSocket.h"

namespace BrainCloud
{
	ITCPSocket* ITCPSocket::create(const std::string& address, int port)
	{
		return new Win32TCPSocket(address, port);
	}

	Win32TCPSocket::Win32TCPSocket(const std::string& address, int port)
		: _socket(INVALID_SOCKET)
		, _isValid(true)
		, _sizeOnBuf(0)
	{
		struct addrinfo hints, *pAddr;
		int iResult;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		getaddrinfo(address.c_str(), std::to_string(port).c_str(), &hints, &pAddr);

		// Attempt to connect to an address until one succeeds
		for (auto ptr = pAddr; ptr != NULL; ptr = ptr->ai_next)
		{
			// Create a SOCKET for connecting to server
			_socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
			if (_socket == INVALID_SOCKET)
			{
				_isValid = false;
				freeaddrinfo(pAddr);
				return;
			}

			// Connect to server.
			iResult = ::connect(_socket, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (iResult == SOCKET_ERROR)
			{
				closesocket(_socket);
				_socket = INVALID_SOCKET;
				continue;
			}

			break;
		}

		freeaddrinfo(pAddr);

		if (_socket == INVALID_SOCKET)
		{
			_isValid = false;
			return;
		}
	}

	Win32TCPSocket::~Win32TCPSocket()
	{
		close();
	}

	bool Win32TCPSocket::isValid() const
	{
		return _isValid;
	}

	void Win32TCPSocket::send(const std::string& message)
	{
		if (_socket == INVALID_SOCKET)
		{
			return;
		}
		
		// Len encoded
		size_t msgSize = message.size();
		size_t size = msgSize + 4;
		_sendBuf.resize(size);
		char* pData = &_sendBuf[0];
		u_long len = htonl((u_long)msgSize);
		memcpy(pData, &len, 4);
		memcpy(pData + 4, &message[0], msgSize);

		int ret = 0;
		while (ret >= 0 && ret < (int)size)
		{
			ret = ::send(_socket, pData, size, 0);
			if (ret >= 0 && ret <= (int)size)
			{
				size -= ret;
				pData += ret;
				continue;
			}
			return;
		}
	}

	std::string Win32TCPSocket::recv()
	{
		if (_socket == INVALID_SOCKET)
		{
			return "";
		}
	
		u_long length = 0;
		_message.clear();
		while (true)
		{
			// Read length
			if (length == 0)
			{
				if (_sizeOnBuf >= 4)
				{
					memcpy(&length, _readBuf, 4);
					length = ntohl(length);
					_sizeOnBuf -= 4;
					for (int i = 0; i < _sizeOnBuf; ++i)
					{
						_readBuf[i] = _readBuf[i + 4];
					}
				}
			}

			// Append to string
			if (length > 0 && _sizeOnBuf > 0)
			{
				int i = 0;
				for (; i < _sizeOnBuf && (int)_message.size() < (int)length; ++i)
				{
					_message += _readBuf[i];
				}

				// Shift remaining of the buffer
				if (i > 0)
				{
					_sizeOnBuf -= i;
					for (int j = 0; j < _sizeOnBuf; ++j)
					{
						_readBuf[j] = _readBuf[j + i];
					}
				}

				if ((int)_message.size() == (int)length)
				{
					return _message;
				}
			}

			// Read more on the socket
			_sizeOnBuf += ::recv(_socket, _readBuf + _sizeOnBuf, 512 - _sizeOnBuf, 0);
			if (_sizeOnBuf > 0)
			{
				continue;
			}
			else if (_sizeOnBuf < 0)
			{
				closesocket(_socket);
				_socket = INVALID_SOCKET;
				return "";
			}
			else
			{
				return ""; // Connection was closed
			}
		}

		return _message;
	}

	void Win32TCPSocket::close()
	{
		if (_socket != INVALID_SOCKET)
		{
			::shutdown(_socket, SD_BOTH);
			closesocket(_socket);
			_socket = INVALID_SOCKET;
		}
	}
};
