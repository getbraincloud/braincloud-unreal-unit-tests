#ifndef _ITCPSOCKET_H_
#define _ITCPSOCKET_H_

#include <string>

namespace BrainCloud
{
	class ITCPSocket
	{
	public:
		static ITCPSocket* create(const std::string& address, int port);

		virtual ~ITCPSocket() {}

		virtual bool isValid() const = 0;

		virtual void send(const std::string& message) = 0;
		virtual std::string recv() = 0;

		virtual void close() = 0;

	protected:
		ITCPSocket() {}
	};
};

#endif /* _ITCPSOCKET_H_ */
