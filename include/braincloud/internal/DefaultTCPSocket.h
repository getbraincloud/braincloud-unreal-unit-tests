#ifndef _DEFAULTTCPSOCKER_H_
#define _DEFAULTTCPSOCKER_H_

#include "braincloud/internal/ITCPSocket.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <unistd.h>
#include <strings.h>
#include <memory.h>
#include <vector>

namespace BrainCloud
{
	class DefaultTCPSocket : public ITCPSocket
	{
	public:
		virtual ~DefaultTCPSocket();

		virtual bool isValid();

		virtual void send(const std::string& message);
		virtual std::string recv();

		virtual void close();

	protected:
		friend class ITCPSocket;

		DefaultTCPSocket(const std::string& address, int port);

	private:
		int _socket;

		bool _isValid;
		char _readBuf[512];
		int _sizeOnBuf;
		std::string _message;
		std::vector<char> _sendBuf;
	};
};

#endif /* _DEFAULTTCPSOCKER_H_ */
