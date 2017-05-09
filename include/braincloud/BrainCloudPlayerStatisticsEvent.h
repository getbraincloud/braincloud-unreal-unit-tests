// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <string>
#include "braincloud/BrainCloudTypes.h"

namespace BrainCloud
{
    class IServerCallback;
    class BrainCloudClient;

    class BrainCloudPlayerStatisticsEvent
    {
    public:
        BrainCloudPlayerStatisticsEvent(BrainCloudClient* in_client);


        /**
		* @deprecated Use triggerStatsEvent() instead - Removal after September 1 2017
		*/
        DEPRECATED
        void triggerPlayerStatisticsEvent(const char * in_eventName, int32_t in_eventMultiplier, IServerCallback * in_callback = NULL);


        /**
         * Trigger an event server side that will increase the user's statistics.
         * This may cause one or more awards to be sent back to the user -
         * could be achievements, experience, etc. Achievements will be sent by this
         * client library to the appropriate awards service (Apple Game Center, etc).
         *
         * This mechanism supercedes the PlayerStatisticsService API methods, since
         * PlayerStatisticsService API method only update the raw statistics without
         * triggering the rewards.
         *
         * Service Name - PlayerStatisticsEvent
         * Service Operation - Trigger
         *
         * @see BrainCloudPlayerStatistics
         *
         * @param in_callback The method to be invoked when the server response is received
         */
        void triggerStatsEvent(const char *in_eventName, int32_t in_eventMultiplier,
                               IServerCallback *in_callback = NULL);


        /**
		* @deprecated Use triggerStatsEvents() instead - Removal after September 1 2017
		*/
        DEPRECATED
        void triggerPlayerStatisticsEvents(const std::string& in_jsonData, IServerCallback * in_callback = NULL);

        /**
         * See documentation for TriggerPlayerStatisticsEvent for more
         * documentation.
         *
         * Service Name - PlayerStatisticsEvent
         * Service Operation - TriggerMultiple
         *
         * @param in_jsonData
         *   [
         *     {
         *       "eventName": "event1",
         *       "eventMultiplier": 1
         *     },
         *     {
         *       "eventName": "event2",
         *       "eventMultiplier": 1
         *     }
         *   ]
         */
        void triggerStatsEvents(const std::string &in_jsonData, IServerCallback *in_callback = NULL);

    private:
        BrainCloudClient * m_client;
    };
}