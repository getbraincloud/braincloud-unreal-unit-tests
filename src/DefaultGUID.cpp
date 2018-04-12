#include "braincloud/internal/GUID.h"

#include <stdlib.h>

namespace BrainCloud
{
    std::string GUID::generateGUID()
    {
        unsigned char buffer[16] = { 0 };

        // This is not great. See BCLD-3069
        for (int i = 0; i < 16; ++i)
        {
            buffer[i] = (unsigned char)(rand() % 255);
        }

        return GUIDToString(buffer);
    }
}
