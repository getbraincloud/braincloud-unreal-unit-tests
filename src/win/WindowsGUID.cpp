#include "braincloud/internal/GUID.h"

#include <objbase.h>

namespace BrainCloud
{
    std::string GUID::generateGUID()
    {
        unsigned char buffer[16] = { 0 };

        UUID guid;
        CoCreateGuid(&guid);
        memcpy(buffer, &guid, 16);

        return GUIDToString(buffer);
    }
}
