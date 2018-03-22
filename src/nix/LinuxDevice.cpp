#include "braincloud/internal/Device.h"

static const std::string PLATFORM_NAME("LINUX");

namespace BrainCloud
{
    namespace Device
    {
        const std::string& getPlatformName()
        {
            return PLATFORM_NAME;
        }

        void getLocale(float* out_timezoneOffset, std::string* out_languageCode, std::string* out_countryCode)
        {
        }
    }
}
