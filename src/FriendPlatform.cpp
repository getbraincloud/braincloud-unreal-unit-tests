#include "braincloud/FriendPlatform.h"

namespace BrainCloud
{
    const FriendPlatform & FriendPlatform::All = FriendPlatform("All");
    const FriendPlatform & FriendPlatform::BrainCloud = FriendPlatform("brainCloud");
    const FriendPlatform & FriendPlatform::Facebook = FriendPlatform("Facebook");
    const FriendPlatform & FriendPlatform::Unknown = FriendPlatform("Unknown");

    FriendPlatform::FriendPlatform(const std::string & in_friendPlatform)
    {
        m_value = in_friendPlatform;
    }

    const std::string & FriendPlatform::toString() const
    {
        return m_value;
    }

    const FriendPlatform & FriendPlatform::fromString(const std::string &in_friendPlatform)
    {
        // this is a bit slow but not used often
        if (in_friendPlatform == All) {
            return FriendPlatform::All;
        }
        if (in_friendPlatform == BrainCloud) {
            return FriendPlatform::BrainCloud;
        }
        if (in_friendPlatform == Facebook) {
            return FriendPlatform::Facebook;
        }

        return FriendPlatform::Unknown;
    }
}
