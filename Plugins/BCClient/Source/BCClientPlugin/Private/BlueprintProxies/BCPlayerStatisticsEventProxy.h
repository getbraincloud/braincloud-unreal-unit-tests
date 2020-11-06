// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCPlayerStatisticsEventProxy.generated.h"

UCLASS(MinimalAPI)
class UBCPlayerStatisticsEventProxy : public UBCBlueprintCallProxyBase
{
    GENERATED_BODY()

  public:
    UBCPlayerStatisticsEventProxy(const FObjectInitializer &ObjectInitializer);

    /**
    * Trigger an event server side that will increase the users statistics.
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
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player Statistics Event")
    static UBCPlayerStatisticsEventProxy *TriggerStatsEvent(UBrainCloudWrapper *brainCloudWrapper, FString eventName, int32 eventMultiplier);

    /**
    * See documentation for TriggerStatsEvent for more
    * documentation.
    *
    * Service Name - PlayerStatisticsEvent
    * Service Operation - TriggerMultiple
    *
    * Param - jsonData
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
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player Statistics Event")
    static UBCPlayerStatisticsEventProxy *TriggerStatsEvents(UBrainCloudWrapper *brainCloudWrapper, FString jsonData);
};
