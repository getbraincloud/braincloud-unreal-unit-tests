#include "braincloud/Platform.h"

namespace BrainCloud
{
    const Platform & Platform::AppleTVOS = Platform("APPLE_TV_OS");
    const Platform & Platform::BlackBerry = Platform("BB");
    const Platform & Platform::Facebook = Platform("FB");
    const Platform & Platform::Oculus = Platform("Oculus");
    const Platform & Platform::GooglePlayAndroid = Platform("ANG");
    const Platform & Platform::iOS = Platform("IOS");
    const Platform & Platform::Linux = Platform("LINUX");
    const Platform & Platform::Mac = Platform("MAC");
    const Platform & Platform::Web = Platform("WEB");
    const Platform & Platform::Windows = Platform("WINDOWS");
    const Platform & Platform::WindowsPhone = Platform("WINP");
    const Platform & Platform::Xbox360 = Platform("XBOX_360");
    const Platform & Platform::PS3 = Platform("PS3");
    const Platform & Platform::XboxOne = Platform("XBOX_ONE");
    const Platform & Platform::PS4 = Platform("PS4");
    const Platform & Platform::Wii = Platform("WII");
    const Platform & Platform::PSVita = Platform("PS_VITA");
    const Platform & Platform::Tizen = Platform("TIZEN");
    const Platform & Platform::Roku = Platform("ROKU");
    const Platform & Platform::WatchOS = Platform("WATCH_OS");
    const Platform & Platform::Unknown = Platform("UNKNOWN");

    Platform::Platform(const std::string & in_platform)
    {
        m_value = in_platform;
    }

    const std::string & Platform::toString() const
    {
        return m_value;
    }

    const Platform & Platform::fromString(const std::string &in_platform)
    {
        // this is a bit slow but not used often
        if (in_platform == AppleTVOS)
        {
            return Platform::AppleTVOS;
        }
        if (in_platform == BlackBerry)
        {
            return Platform::BlackBerry;
        }
        if (in_platform == Facebook)
        {
            return Platform::Facebook;
        }
        if (in_platform == Oculus)
        {
            return Platform::Oculus;
        }
        if (in_platform == GooglePlayAndroid)
        {
            return Platform::GooglePlayAndroid;
        }
        if (in_platform == iOS)
        {
            return Platform::iOS;
        }
        if (in_platform == Linux)
        {
            return Platform::Linux;
        }
        if (in_platform == Mac)
        {
            return Platform::Mac;
        }
        if (in_platform == Web)
        {
            return Platform::Web;
        }
        if (in_platform == Windows)
        {
            return Platform::Windows;
        }
        if (in_platform == WindowsPhone)
        {
            return Platform::WindowsPhone;
        }
        if (in_platform == Xbox360)
        {
            return Platform::Xbox360;
        }
        if (in_platform == PS3)
        {
            return Platform::PS3;
        }
        if (in_platform == XboxOne)
        {
            return Platform::XboxOne;
        }
        if (in_platform == PS4)
        {
            return Platform::PS4;
        }
        if (in_platform == Wii)
        {
            return Platform::Wii;
        }
        if (in_platform == PSVita)
        {
            return Platform::PSVita;
        }
        if (in_platform == Tizen)
        {
            return Platform::Tizen;
        }
        if (in_platform == Roku)
        {
            return Platform::Roku;
        }
        if (in_platform == WatchOS)
        {
            return Platform::WatchOS;
        }

        return Platform::Unknown;
    }
}
