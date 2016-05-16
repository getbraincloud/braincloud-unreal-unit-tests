// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <stddef.h>

namespace BrainCloud {

    class IServerCallback;
    class BrainCloudClient;

    class BrainCloudDataStream
    {
    public:
        BrainCloudDataStream(BrainCloudClient* in_client);

        /**
         * Creates custom data stream page event
         *
         * @param eventName Name of event
         * @param eventProperties Properties of event
         */
        void customPageEvent(const char * in_eventName, const char * in_jsonEventProperties, IServerCallback * in_callback = NULL);

        /**
         * Creates custom data stream screen event
         *
         * @param eventName Name of event
         * @param eventProperties Properties of event
         */
        void customScreenEvent(const char * in_eventName, const char * in_jsonEventProperties, IServerCallback * in_callback = NULL);

        /**
         * Creates custom data stream track event
         *
         * @param eventName Name of event
         * @param eventProperties Properties of event
         */
        void customTrackEvent(const char * in_eventName, const char * in_jsonEventProperties, IServerCallback * in_callback = NULL);

    private:
        BrainCloudClient * m_client;
    };
}
