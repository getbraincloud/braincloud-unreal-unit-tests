// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BCPlayerStatisticsEventProxy.generated.h"

class ABrainCloud;

UCLASS(MinimalAPI)
class UBCPlayerStatisticsEventProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
    GENERATED_BODY()

public:
    UBCPlayerStatisticsEventProxy(const FObjectInitializer& ObjectInitializer);

	/**
	* @deprecated Use TriggerStatsEvent instead
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player Statistics Event")
		static UBCPlayerStatisticsEventProxy* TriggerPlayerStatisticsEvent(ABrainCloud *brainCloud, FString eventName, int32 eventMultiplier);

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
        static UBCPlayerStatisticsEventProxy* TriggerStatsEvent(ABrainCloud *brainCloud, FString eventName, int32 eventMultiplier);

	/**
	* @deprecated Use TriggerStatsEvents instead
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player Statistics Event")
		static UBCPlayerStatisticsEventProxy* TriggerPlayerStatisticsEvents(ABrainCloud *brainCloud, FString jsonData);

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
        static UBCPlayerStatisticsEventProxy* TriggerStatsEvents(ABrainCloud *brainCloud, FString jsonData);

    //Response delegates
    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnFailure;

protected:
    // IServerCallback interface
    void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
    void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
    // End of IServerCallback interface
};
