// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCPlayerStatisticsProxy.generated.h"

UCLASS(MinimalAPI)
class UBCPlayerStatisticsProxy : public UBCBlueprintCallProxyBase
{
    GENERATED_BODY()

  public:
    UBCPlayerStatisticsProxy(const FObjectInitializer &ObjectInitializer);

    /**
    * Read all available user statistics.
    *
    * Service Name - PlayerStatistics
    * Service Operation - Read
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player Statistics")
    static UBCPlayerStatisticsProxy *ReadAllUserStats(UBrainCloudWrapper *brainCloudWrapper);

    /**
    * Reads a subset of user statistics.
    *
    * Service Name - PlayerStatistics
    * Service Operation - ReadSubset
    *
    * Param - jsonData The json data containing the subset of statistics to read:
    * ex. [ "pantaloons", "minions" ]
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player Statistics")
    static UBCPlayerStatisticsProxy *ReadUserStatsSubset(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &userStats);

    /**
    * Reset all of the statistics for this user back to their initial value.
    *
    * Service Name - PlayerStatistics
    * Service Operation - Reset
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player Statistics")
    static UBCPlayerStatisticsProxy *ReadUserStatisticsByCategory(UBrainCloudWrapper *brainCloudWrapper, FString category);

    /**
    * Method retrieves the user statistics for the given category.
    *
    * Service Name - PlayerStatistics
    * Service Operation - ReadUserStatisticsByCategory
    *
    * Param - category The player statistics category
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player Statistics")
    static UBCPlayerStatisticsProxy *ResetAllUserStats(UBrainCloudWrapper *brainCloudWrapper);

    /**
    * Atomically increment (or decrement) user statistics.
    * Any rewards that are triggered from user statistic increments
    * will be considered. User statistics are defined through the brainCloud portal.
    * Note also that the "xpCapped" property is returned (true/false depending on whether
    * the xp cap is turned on and whether the user has hit it).
    *
    * Service Name - PlayerStatistics
    * Service Operation - Update
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
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player Statistics")
    static UBCPlayerStatisticsProxy *IncrementUserStats(UBrainCloudWrapper *brainCloudWrapper, FString jsonData);

    /**
    * Returns JSON representing the next experience level for the user.
    *
    * Service Name - PlayerStatistics
    * Service Operation - ReadNextXpLevel
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player Statistics")
    static UBCPlayerStatisticsProxy *GetNextExperienceLevel(UBrainCloudWrapper *brainCloudWrapper);

    /**
    * Increments the user's experience. If the player goes up a level,
    * the new level details will be returned along with a list of rewards.
    *
    * Service Name - PlayerStatistics
    * Service Operation - UpdateIncrement
    *
    * Param - xpValue The amount to increase the user's experience by
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player Statistics")
    static UBCPlayerStatisticsProxy *IncrementExperiencePoints(UBrainCloudWrapper *brainCloudWrapper, int32 xpValue);

    /**
    * Sets the user's experience to an absolute value. Note that this
    * is simply a set and will not reward the player if their level changes
    * as a result.
    *
    * Service Name - PlayerStatistics
    * Service Operation - SetXpPoints
    *
    * Param - xpValue The amount to set the the user's experience to
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player Statistics")
    static UBCPlayerStatisticsProxy *SetExperiencePoints(UBrainCloudWrapper *brainCloudWrapper, int32 xpValue);

    /**
	* Apply statistics grammar to a partial set of statistics.
	*
	* Service Name - PlayerStatistics
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
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player Statistics")
    static UBCPlayerStatisticsProxy *ProcessStatistics(UBrainCloudWrapper *brainCloudWrapper, FString jsonData);
};
