#include "braincloud/internal/DefaultTCPSocket.h"

namespace BrainCloud
{
	ITCPSocket* ITCPSocket::create(const std::string& address, int port)
	{
		return new DefaultTCPSocket(address, port);
	}

	DefaultTCPSocket::DefaultTCPSocket(const std::string& address, int port)
		: _socket(-1)
		, _isValid(true)
		, _sizeOnBuf(0)
	{
		int sockfd, portno, n;

		struct sockaddr_in serv_addr;
		struct hostent *server;
		
		_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (_socket < 0)
		{
			_socket = -1;
			_isValid = false;
			return;
		}
		
		server = gethostbyname(address.c_str());
		if (server == NULL)
		{
			_isValid = false;
			return;
		}

		bzero((char *)&serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		bcopy((char *)server->h_addr, 
			(char *)&serv_addr.sin_addr.s_addr,
			server->h_length);
		serv_addr.sin_port = htons(port);
		if (connect(_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
		{
			_isValid = false;
			return;
		}
	}

	DefaultTCPSocket::~DefaultTCPSocket()
	{
		close();
	}

	bool DefaultTCPSocket::isValid() const
	{
		return _isValid;
	}

	void DefaultTCPSocket::send(const std::string& message)
	{
		if (_socket == -1)
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

	std::string DefaultTCPSocket::recv()
	{
		if (_socket == -1)
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
				::close(_socket);
				_socket = -1;
				return "";
			}
			else
			{
				return ""; // Connection was closed
			}
		}

		return _message;
	}

	void DefaultTCPSocket::close()
	{
		if (_socket != -1)
		{
			::shutdown(_socket, SHUT_RDWR);
			::close(_socket);
			_socket = -1;
		}
	}
};
