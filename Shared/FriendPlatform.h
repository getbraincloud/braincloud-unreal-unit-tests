//
//  FriendPlatform.h
//  BrainCloud
//
//  Created by Brad Hill on 2016-03-22.
//
//

#pragma once

#include <string>

namespace BrainCloud
{
    class FriendPlatform
    {
    public:
        static const FriendPlatform & All;
        static const FriendPlatform & BrainCloud;
        static const FriendPlatform & Facebook;
        static const FriendPlatform & Unknown;

        const std::string & toString() const;
        static const FriendPlatform & fromString(const std::string & in_friendPlatform);

    private:
        FriendPlatform(const std::string & in_friendPlatform);
        std::string m_value;
    };

    inline bool operator== (const FriendPlatform& a, const FriendPlatform& b) {
        return a.toString() == b.toString();
    }

    inline bool operator== (const FriendPlatform& a, const std::string& s) {
        return a.toString() == s;
    }

    inline bool operator== (const std::string& s, const FriendPlatform& a) {
        return a.toString() == s;
    }

    inline bool operator== (const FriendPlatform& a, const char * s) {
        return a.toString() == s;
    }

    inline bool operator== (const char * s, const FriendPlatform& a) {
        return a.toString() == s;
    }
}
