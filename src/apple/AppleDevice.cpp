#include "braincloud/internal/Device.h"

#include <CoreFoundation/CFLocale.h>
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFTimeZone.h>
#include <TargetConditionals.h>

#if TARGET_OS_IOS
static const std::string PLATFORM_NAME("IOS");
#elif  TARGET_OS_TV
static const std::string PLATFORM_NAME("APPLE_TV_OS");
#elif  TARGET_OS_MAC
static const std::string PLATFORM_NAME("MAC");
#else
#error "Unsupported __APPLE__ platform!"
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
            char charBuf[16];
            charBuf[0] = '\0';

            CFLocaleRef locale = CFLocaleCopyCurrent();
            if (locale != nil)
            {
                CFStringRef langCode = (CFStringRef)CFLocaleGetValue(locale, kCFLocaleLanguageCode);
                if (langCode != nil)
                {
                    CFStringGetCString(langCode, charBuf, 16, kCFStringEncodingUTF8);
                    *out_languageCode = std::string(charBuf);
                }

                CFStringRef countryCode = (CFStringRef)CFLocaleGetValue(locale, kCFLocaleCountryCode);
                if (countryCode != nil)
                {
                    CFStringGetCString(countryCode, charBuf, 16, kCFStringEncodingUTF8);
                    *out_countryCode = std::string(charBuf);
                }

                CFTimeZoneRef tz = CFTimeZoneCopySystem();
                if (tz != nil)
                {
                    CFTimeInterval utcOffset = CFTimeZoneGetSecondsFromGMT(tz, CFAbsoluteTimeGetCurrent());
                    *out_timezoneOffset = utcOffset / 3600.0f;
                    CFRelease(tz);
                }

                CFRelease(locale);
            }
        }
    }
}
