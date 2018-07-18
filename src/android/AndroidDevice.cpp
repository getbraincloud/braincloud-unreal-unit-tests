#include "braincloud/internal/Device.h"

static const std::string PLATFORM_NAME("ANG");

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
            // do NOT set countryCode etc here as the android
            // java layer is responsible for setting it.
        }
    }
}
