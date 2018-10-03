#include "braincloud/internal/GUID.h"

#include <uuid/uuid.h>

namespace BrainCloud
{
    std::string GUID::generateGUID()
    {
		uuid_t buffer;
		uuid_generate(buffer);
        return GUIDToString(buffer);
    }
}
