// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <stddef.h>

namespace BrainCloud
{
    class IServerCallback;
    class BrainCloudClient;

    class BrainCloudGlobalApp
    {
    public:
        BrainCloudGlobalApp(BrainCloudClient* in_client);

        /**
         * Read game's global properties
         *
         * Service Name - GlobalApp
         * Service Operation - ReadProperties
         *
         * @param in_callback The method to be invoked when the server response is received
         */
        void readProperties(IServerCallback * in_callback = NULL);

    private:
        BrainCloudClient * m_client;
    };
}