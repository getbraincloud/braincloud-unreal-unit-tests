//
//  Platform.h
//  BrainCloud
//
//  Created by brainCloud Team on 2015-09-10.
//
//

#pragma once

#include <string>

namespace BrainCloud
{
    class Platform
    {
    public:
        static const Platform & AppleTVOS;
        static const Platform & BlackBerry;
        static const Platform & Facebook;
        static const Platform & Oculus;
        static const Platform & GooglePlayAndroid;
        static const Platform & iOS;
        static const Platform & Linux;
        static const Platform & Mac;
        static const Platform & Web;
        static const Platform & Windows;
        static const Platform & WindowsPhone;
        static const Platform & Xbox360;
        static const Platform & PS3;
        static const Platform & XboxOne;
        static const Platform & PS4;
        static const Platform & Wii;
        static const Platform & PSVita;
        static const Platform & Tizen;
        static const Platform & Roku;
        static const Platform & WatchOS;
        static const Platform & Unknown;

        const std::string & toString() const;
        static const Platform & fromString(const std::string & in_platform);

    private:
        Platform(const std::string & in_platform);
        std::string m_value;
    };

    inline bool operator== (const Platform& a, const Platform& b) {
        return a.toString() == b.toString();
    }

    inline bool operator== (const Platform& a, const std::string& s) {
        return a.toString() == s;
    }

    inline bool operator== (const std::string& s, const Platform& a) {
        return a.toString() == s;
    }

    inline bool operator== (const Platform& a, const char * s) {
        return a.toString() == s;
    }

    inline bool operator== (const char * s, const Platform& a) {
        return a.toString() == s;
    }
}