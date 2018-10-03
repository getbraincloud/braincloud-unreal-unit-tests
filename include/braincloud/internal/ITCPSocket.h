#ifndef _ITCPSOCKET_H_
#define _ITCPSOCKET_H_

#include "ISocket.h"

namespace BrainCloud
{
	class ITCPSocket : public ISocket
	{
	public:
		static ITCPSocket* create(const std::string& address, int port);

		virtual ~ITCPSocket() {}

	protected:
		ITCPSocket() {}
	};
};

#endif /* _ITCPSOCKET_H_ */
