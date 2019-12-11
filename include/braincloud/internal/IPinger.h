#ifndef _IPINGER_H_
#define _IPINGER_H_

#include <string>

namespace BrainCloud
{
    class BrainCloudClient;
    
    class IPinger
    {
    public:
        static IPinger* create(BrainCloudClient* pClient);

        virtual ~IPinger() {}

        virtual int ping(const std::string& url) = 0;
    };
}

#endif /* _IPINGER_H_ */
