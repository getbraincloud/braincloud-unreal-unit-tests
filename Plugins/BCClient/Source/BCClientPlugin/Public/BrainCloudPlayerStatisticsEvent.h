// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudPlayerStatisticsEvent
{
public:
    BrainCloudPlayerStatisticsEvent(BrainCloudClient* client);

    /**
     * Trigger an event server side that will increase the players statistics.
     * This may cause one or more awards to be sent back to the player -
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
     * @param callback The method to be invoked when the server response is received
     */
    void triggerPlayerStatisticsEvent(const FString& eventName, int32 eventMultiplier, IServerCallback* callback);

    /**
     * See documentation for TriggerPlayerStatisticsEvent for more
     * documentation.
     *
     * Service Name - PlayerStatisticsEvent
     * Service Operation - TriggerMultiple
     *
     * @param jsonData
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
    void triggerPlayerStatisticsEvents(const FString& jsonData, IServerCallback* callback);

private:
    BrainCloudClient* _client = nullptr;
};
