// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BCGlobalStatisticsProxy.generated.h"

class ABrainCloud;

UCLASS(MinimalAPI)
class UBCGlobalStatisticsProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
    GENERATED_BODY()

public:
    UBCGlobalStatisticsProxy(const FObjectInitializer& ObjectInitializer);

    /**
    * Method returns all of the global statistics.
    *
    * Service Name - GlobalStatistics
    * Service Operation - Read
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global Statistics")
        static UBCGlobalStatisticsProxy* ReadAllGlobalStats(ABrainCloudActor *brainCloud);

    /**
    * Reads a subset of global statistics.
    *
    * Service Name - GlobalStatistics
    * Service Operation - ReadSubset
    *
    * Param - globalStats An array of statistics to read:
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global Statistics")
        static UBCGlobalStatisticsProxy* ReadGlobalStatsSubset(ABrainCloudActor *brainCloud, const TArray<FString>& globalStats);

    /**
    * Method retrieves the game (aka global) statistics for the given category.
    *
    * Service Name - GlobalStatistics
    * Service Operation - ReadGameStatisticsByCategory
    *
    * Param - category The game statistics category
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global Statistics")
        static UBCGlobalStatisticsProxy* ReadGlobalStatsForCategory(ABrainCloudActor *brainCloud, FString category);

    /**
    * Atomically increment (or decrement) global statistics.
    * Global statistics are defined through the brainCloud portal.
    *
    * Service Name - GlobalStatistics
    * Service Operation - UpdateIncrement
    *
    * Param - jsonData The JSON encoded data to be sent to the server as follows:
    * {
    *   stat1: 10,
    *   stat2: -5.5,
    * }
    * would increment stat1 by 10 and decrement stat2 by 5.5.
    * For the full statistics grammer see the api.braincloudservers.com site.
    * There are many more complex operations supported such as:
    * {
    *   stat1:INC_TO_LIMIT#9#30
    * }
    * which increments stat1 by 9 up to a limit of 30.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global Statistics")
        static UBCGlobalStatisticsProxy* IncrementGlobalGameStat(ABrainCloudActor *brainCloud, FString jsonData);

	/**
	* Apply statistics grammar to a partial set of statistics.
	*
	* Service Name - GlobalStatistics
	* Service Operation - PROCESS_STATISTICS
	*
	* Param - jsonData The JSON format is as follows:
	* {
	*     "DEAD_CATS": "RESET",
	*     "LIVES_LEFT": "SET#9",
	*     "MICE_KILLED": "INC#2",
	*     "DOG_SCARE_BONUS_POINTS": "INC#10",
	*     "TREES_CLIMBED": 1
	* }
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global Statistics")
		static UBCGlobalStatisticsProxy* ProcessStatistics(ABrainCloudActor *brainCloud, FString jsonData);

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
