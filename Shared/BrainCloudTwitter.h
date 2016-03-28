#pragma once

#include <string>
#include "BrainCloudTypes.h"

namespace BrainCloud
{
    class IServerCallback;
    class BrainCloudClient;

    class BrainCloudTwitter
    {
    public:
        BrainCloudTwitter(BrainCloudClient* in_client);

        /* DEPRECATED - Removal after June 21 2016*/
        DEPRECATED void authorizeTwitter(IServerCallback * in_callback = NULL);

        /* DEPRECATED - Removal after June 21 2016*/
        DEPRECATED void verifyTwitter(const char * in_token, const char * in_verifier, IServerCallback * in_callback = NULL);

        /* DEPRECATED - Removal after June 21 2016*/
        DEPRECATED void tweet(const char * in_token, const char * in_secret, const char * in_tweet, const char * in_picture, IServerCallback * in_callback = NULL);

    private:
        BrainCloudClient * m_client;
    };
}