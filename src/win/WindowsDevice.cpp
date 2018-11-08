#include "braincloud/internal/Device.h"

#include <Windows.h>

#if (defined(WINAPI_FAMILY) && WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP) || defined(BC_UWP)
static const std::string PLATFORM_NAME("WINP");
#else
static const std::string PLATFORM_NAME("WINDOWS");
#endif

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
            TIME_ZONE_INFORMATION tzi;

            wchar_t wbuf[16];
            char cbuf[16];
            size_t bytes;

            GetTimeZoneInformation(&tzi);
            *out_timezoneOffset = (float)tzi.Bias / (float)-60.0;

            GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT, LOCALE_SISO639LANGNAME, wbuf, 16);
            wcstombs_s(&bytes, cbuf, 16, wbuf, 15);
            *out_languageCode = cbuf;

            GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT, LOCALE_SISO3166CTRYNAME, wbuf, 16);
            wcstombs_s(&bytes, cbuf, 16, wbuf, 15);
            *out_countryCode = cbuf;
        }
    }
}
