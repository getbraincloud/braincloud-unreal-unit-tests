//
//  AuthenticationType.h
//  BrainCloud
//
//  Created by Brad Hill on 2016-04-11.
//
//

#ifndef _AUTHENTICATIONTYPE_H_
#define _AUTHENTICATIONTYPE_H_

#include <string>

namespace BrainCloud
{
    class AuthenticationType
    {
    public:
        static const AuthenticationType & Anonymous;
        static const AuthenticationType & Universal;
        static const AuthenticationType & Email;
        static const AuthenticationType & Facebook;
        static const AuthenticationType & Oculus;
        static const AuthenticationType & GameCenter;
        static const AuthenticationType & Steam;
        static const AuthenticationType & Apple;
        static const AuthenticationType & Google;
        static const AuthenticationType & GoogleOpenId;
        static const AuthenticationType & Twitter;
        static const AuthenticationType & Parse;
        static const AuthenticationType & Handoff;
        static const AuthenticationType & SettopHandoff;
        static const AuthenticationType & External;
        static const AuthenticationType & Unknown;

        const std::string & toString() const;
        static const AuthenticationType & fromString(const std::string & in_AuthenticationType);

    private:
        AuthenticationType(const std::string & in_AuthenticationType);
        std::string m_value;
    };

    inline bool operator== (const AuthenticationType& a, const AuthenticationType& b) {
        return a.toString() == b.toString();
    }

    inline bool operator== (const AuthenticationType& a, const std::string& s) {
        return a.toString() == s;
    }

    inline bool operator== (const std::string& s, const AuthenticationType& a) {
        return a.toString() == s;
    }

    inline bool operator== (const AuthenticationType& a, const char * s) {
        return a.toString() == s;
    }

    inline bool operator== (const char * s, const AuthenticationType& a) {
        return a.toString() == s;
    }
}

#endif /* _AUTHENTICATIONTYPE_H_ */
