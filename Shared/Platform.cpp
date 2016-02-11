#include "Platform.h"

namespace BrainCloud
{
    const Platform & Platform::AppleTVOS = Platform("APPLE_TV_OS");
    const Platform & Platform::BlackBerry = Platform("BB");
    const Platform & Platform::Facebook = Platform("FB");
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
        if (in_platform.compare("APPLE_TV_OS") == 0)
        {
            return Platform::AppleTVOS;
        }
        if (in_platform.compare("BB") == 0)
        {
            return Platform::BlackBerry;
        }
        if (in_platform.compare("FB") == 0)
        {
            return Platform::Facebook;
        }
        if (in_platform.compare("ANG") == 0)
        {
            return Platform::GooglePlayAndroid;
        }
        if (in_platform.compare("IOS") == 0)
        {
            return Platform::iOS;
        }
        if (in_platform.compare("LINUX") == 0)
        {
            return Platform::Linux;
        }
        if (in_platform.compare("MAC") == 0)
        {
            return Platform::Mac;
        }
        if (in_platform.compare("WEB") == 0)
        {
            return Platform::Web;
        }
        if (in_platform.compare("WINDOWS") == 0)
        {
            return Platform::Windows;
        }
        if (in_platform.compare("WINP") == 0)
        {
            return Platform::WindowsPhone;
        }
        if (in_platform.compare("XBOX_360") == 0)
        {
            return Platform::Xbox360;
        }
        if (in_platform.compare("PS3") == 0)
        {
            return Platform::PS3;
        }
        if (in_platform.compare("XBOX_ONE") == 0)
        {
            return Platform::XboxOne;
        }
        if (in_platform.compare("PS4") == 0)
        {
            return Platform::PS4;
        }
        if (in_platform.compare("WII") == 0)
        {
            return Platform::Wii;
        }
        if (in_platform.compare("PS_VITA") == 0)
        {
            return Platform::PSVita;
        }
        if (in_platform.compare("TIZEN") == 0)
        {
            return Platform::Tizen;
        }
        if (in_platform.compare("ROKU") == 0)
        {
            return Platform::Roku;
        }
        
        return Platform::Unknown;
    }
}
