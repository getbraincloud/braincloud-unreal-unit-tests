#include <string>

namespace BrainCloud
{
    namespace Device
    {
        const std::string& getPlatformName();
        void getLocale(float* out_timezoneOffset, std::string* out_languageCode, std::string* out_countryCode);
    }
}
