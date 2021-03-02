#include "braincloud/AuthenticationType.h"

namespace BrainCloud
{
    const AuthenticationType & AuthenticationType::Anonymous = AuthenticationType("Anonymous");
    const AuthenticationType & AuthenticationType::Universal = AuthenticationType("Universal");
    const AuthenticationType & AuthenticationType::Email = AuthenticationType("Email");
    const AuthenticationType & AuthenticationType::Facebook = AuthenticationType("Facebook");
    const AuthenticationType & AuthenticationType::Oculus = AuthenticationType("Oculus");
    const AuthenticationType & AuthenticationType::GameCenter = AuthenticationType("GameCenter");
    const AuthenticationType & AuthenticationType::Steam = AuthenticationType("Steam");
    const AuthenticationType & AuthenticationType::Apple = AuthenticationType("Apple");
    const AuthenticationType & AuthenticationType::Google = AuthenticationType("Google");
    const AuthenticationType & AuthenticationType::GoogleOpenId = AuthenticationType("GoogleOpenId");
    const AuthenticationType & AuthenticationType::Twitter = AuthenticationType("Twitter");
    const AuthenticationType & AuthenticationType::Parse = AuthenticationType("Parse");
    const AuthenticationType & AuthenticationType::Handoff = AuthenticationType("Handoff");
    const AuthenticationType & AuthenticationType::SettopHandoff = AuthenticationType("SettopHandoff");
    const AuthenticationType & AuthenticationType::External = AuthenticationType("External");
    const AuthenticationType & AuthenticationType::Unknown = AuthenticationType("Unknown");

    AuthenticationType::AuthenticationType(const std::string & in_AuthenticationType)
    {
        m_value = in_AuthenticationType;
    }

    const std::string & AuthenticationType::toString() const
    {
        return m_value;
    }

    const AuthenticationType & AuthenticationType::fromString(const std::string &in_AuthenticationType)
    {
        // this is a bit slow but not used often
        if (in_AuthenticationType == Anonymous)
        {
            return AuthenticationType::Anonymous;
        }
        if (in_AuthenticationType == Universal)
        {
            return AuthenticationType::Universal;
        }
        if (in_AuthenticationType == Email)
        {
            return AuthenticationType::Email;
        }
        if (in_AuthenticationType == Facebook)
        {
            return AuthenticationType::Facebook;
        }
        if (in_AuthenticationType == GameCenter)
        {
            return AuthenticationType::GameCenter;
        }
        if (in_AuthenticationType == Steam)
        {
            return AuthenticationType::Steam;
        }
        if (in_AuthenticationType == Apple)
        {
            return AuthenticationType::Apple;
        }
        if (in_AuthenticationType == Google)
        {
            return AuthenticationType::Google;
        }
        if (in_AuthenticationType == GoogleOpenId)
        {
            return AuthenticationType::GoogleOpenId;
        }
        if (in_AuthenticationType == Twitter)
        {
            return AuthenticationType::Twitter;
        }
        if (in_AuthenticationType == Parse)
        {
            return AuthenticationType::Parse;
        }
        if (in_AuthenticationType == Handoff)
        {
            return AuthenticationType::Handoff;
        }
        if (in_AuthenticationType == External)
        {
            return AuthenticationType::External;
        }

        return AuthenticationType::Unknown;
    }
}
