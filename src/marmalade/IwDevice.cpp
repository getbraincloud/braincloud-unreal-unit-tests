#include "braincloud/internal/Device.h"

#include <s3e.h>

namespace BrainCloud
{
    namespace Device
    {
        const std::string& getPlatformName()
        {
            //int deviceClass = s3eDeviceGetInt(S3E_DEVICE_CLASS);
            int deviceOs = s3eDeviceGetInt(S3E_DEVICE_OS);
            switch (deviceOs)
            {
                case S3E_OS_ID_OSX:
                    return Platform::Mac.toString();
                case S3E_OS_ID_IPHONE:
                    return Platform::iOS.toString();
                case S3E_OS_ID_ANDROID:
                    return Platform::GooglePlayAndroid.toString();
                case S3E_OS_ID_QNX: // playbook
                    return Platform::BlackBerry.toString();
                case S3E_OS_ID_ROKU: // TODO - add Roku platform!!!
                    return Platform::GooglePlayAndroid.toString();
                case S3E_OS_ID_WP8:
                case S3E_OS_ID_WP81:
                    return Platform::WindowsPhone.toString();
                case S3E_OS_ID_TIZEN:
                    return Platform::Tizen.toString();
                case S3E_OS_ID_WS8:
                case S3E_OS_ID_WS81:
                case S3E_OS_ID_WIN10:
                case S3E_OS_ID_WINDOWS:
                    return Platform::Windows.toString();
                case S3E_OS_ID_LINUX:
                    return Platform::Linux.toString();
                case S3E_OS_ID_NACL:
                case S3E_OS_ID_LG:
                case S3E_OS_ID_ARM_SEMIH:
                default:
                    return Platform::Windows.toString(); // who knows... assume windows
            }
        }

        void getLocale(float* out_timezoneOffset, std::string* out_languageCode, std::string* out_countryCode)
        {
            //[read, string] Return the current device locale as a language-country code pair using the
            // ISO 639 and ISO 3166 formats respectively. For example, if the device is set to English (UK)
            // it will return "en_GB". If the device does not support providing a locale, it will return the empty string.
            std::string locale = s3eDeviceGetString(S3E_DEVICE_LOCALE);
            size_t sep = locale.find('_');
            if (sep != std::string::npos)
            {
                *out_languageCode = locale.substr(0, sep);
                *out_countryCode = locale.substr(sep + 1, locale.length());
            }

            // the other way to get language on marmalade
            //int lang = s3eDeviceGetInt(S3E_DEVICE_LANGUAGE);
            //S3E_DEVICE_LANGUAGE_ENGLISH etc

            *out_timezoneOffset = 0.0; // not available on marmalade... have to parse the timezone string!
        }
    }
}
