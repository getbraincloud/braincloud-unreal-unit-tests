#ifndef _ISOCKET_H_
#define _ISOCKET_H_

#include <string>

namespace BrainCloud
{
    class ISocket
    {
    public:
        virtual ~ISocket() {}

        virtual bool isValid() = 0;

        virtual void send(const std::string& message) = 0;
        virtual std::string recv() = 0;

        virtual void close() = 0;

    protected:
        ISocket() {}
    };
};

#endif /* _ISOCKET_H_ */
