#ifndef __GUID__
#define __GUID__

#include <string>

namespace BrainCloud
{
    class GUID
    {
    public:
        static std::string generateGUID();

    private:
        GUID(){};

        static std::string GUIDToString(const unsigned char* buffer);
    };
}

#endif 
