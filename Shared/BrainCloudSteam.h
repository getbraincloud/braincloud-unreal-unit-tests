// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <stddef.h>

namespace BrainCloud
{
    class IServerCallback;
    class BrainCloudClient;

    class BrainCloudSteam
    {
    public:
        BrainCloudSteam(BrainCloudClient* in_client);

        void getUserInfo(IServerCallback * in_callback = NULL);

    private:
        BrainCloudClient * m_client;
    };
}