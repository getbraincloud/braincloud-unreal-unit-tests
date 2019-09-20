// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <stddef.h>
#include <string>

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

        /**
         * Send crash report
         *
         * @param crashType
         * @param errorMsg
         * @param crashJson
         * @param crashLog
         * @param userName
         * @param userEmail
         * @param userNotes
         * @param userSubmitted
         */
        void submitCrashReport(const char * in_crashType, const char * in_errorMsg, const std::string&  in_crashJson, const char * in_crashLog, const char * in_username, const char * in_userEmail, const char * in_userNotes, bool in_userSubmitted, IServerCallback * in_callback = NULL);

    private:
        BrainCloudClient * m_client;
    };
}
