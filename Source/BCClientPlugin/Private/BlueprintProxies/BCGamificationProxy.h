// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCGamificationProxy.generated.h"

UCLASS(MinimalAPI)
class UBCGamificationProxy : public UBCBlueprintCallProxyBase
{
  GENERATED_BODY()

public:
  UBCGamificationProxy(const FObjectInitializer &ObjectInitializer);

  /**
    * Method retrieves all gamification data for the player.
    *
    * Service Name - Gamification
    * Service Operation - Read
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Gamification")
  static UBCGamificationProxy *ReadAllGamification(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData = false);

  /**
    * Method retrieves all milestones defined for the game.
    *
    * Service Name - Gamification
    * Service Operation - ReadMilestones
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Gamification")
  static UBCGamificationProxy *ReadMilestones(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData = false);

  /**
    * Read all of the achievements defined for the game.
    *
    * Service Name - Gamification
    * Service Operation - ReadAchievements
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Gamification")
  static UBCGamificationProxy *ReadAchievements(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData = false);

  /**
    * Method returns all defined xp levels and any rewards associated
    * with those xp levels.
    *
    * Service Name - Gamification
    * Service Operation - ReadXpLevels
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Gamification")
  static UBCGamificationProxy *ReadXpLevelsMetaData(UBrainCloudWrapper *brainCloudWrapper);

  /**
    * Method retrives the list of achieved achievements.
    *
    * Service Name - Gamification
    * Service Operation - ReadAchievedAchievements
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Gamification")
  static UBCGamificationProxy *ReadAchievedAchievements(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData = false);

  /**
    * Method retrieves the list of completed milestones.
    *
    * Service Name - Gamification
    * Service Operation - ReadCompleteMilestones
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Gamification")
  static UBCGamificationProxy *ReadCompletedMilestones(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData = false);

  /**
    * Method retrieves the list of in progress milestones
    *
    * Service Name - Gamification
    * Service Operation - ReadInProgressMilestones
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Gamification")
  static UBCGamificationProxy *ReadInProgressMilestones(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData = false);

  /**
    * Method retrieves milestones of the given category.
    *
    * Service Name - Gamification
    * Service Operation - ReadMilestonesByCategory
    *
    * Param - category The milestone category
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Gamification")
  static UBCGamificationProxy *ReadMilestonesByCategory(UBrainCloudWrapper *brainCloudWrapper, FString category, bool includeMetaData = false);

  /**
    * Method will award the achievements specified. On success, this will
    * call AwardThirdPartyAchievement to hook into the client-side Achievement
    * service (ie GameCentre, Facebook etc).
    *
    * Service Name - Gamification
    * Service Operation - AwardAchievements
    *
    * Param - achievementIds A comma separated list of achievement ids to award
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Gamification")
  static UBCGamificationProxy *AwardAchievements(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &achievements);

  /**
    * Method retrieves all of the quests defined for the game.
    *
    * Service Name - Gamification
    * Service Operation - ReadQuests
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Gamification")
  static UBCGamificationProxy *ReadQuests(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData = false);

  /**
    *  Method returns all completed quests.
    *
    * Service Name - Gamification
    * Service Operation - ReadCompletedQuests
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Gamification")
  static UBCGamificationProxy *ReadCompletedQuests(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData = false);

  /**
    *  Method returns quests that are in progress.
    *
    * Service Name - Gamification
    * Service Operation - ReadInProgressQuests
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Gamification")
  static UBCGamificationProxy *ReadInProgressQuests(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData = false);

  /**
    *  Method returns quests that have not been started.
    *
    * Service Name - Gamification
    * Service Operation - ReadNotStartedQuests
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Gamification")
  static UBCGamificationProxy *ReadNotStartedQuests(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData = false);

  /**
    *  Method returns quests with a status.
    *
    * Service Name - Gamification
    * Service Operation - ReadQuestsWithStatus
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Gamification")
  static UBCGamificationProxy *ReadQuestsWithStatus(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData = false);

  /**
    *  Method returns quests with a basic percentage.
    *
    * Service Name - Gamification
    * Service Operation - ReadQuestsWithBasicPercentage
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Gamification")
  static UBCGamificationProxy *ReadQuestsWithBasicPercentage(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData = false);

  /**
    *  Method returns quests with a complex percentage.
    *
    * Service Name - Gamification
    * Service Operation - ReadQuestsWithComplexPercentage
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Gamification")
  static UBCGamificationProxy *ReadQuestsWithComplexPercentage(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData = false);

  /**
    * Method returns quests for the given category.
    *
    * Service Name - Gamification
    * Service Operation - ReadQuestsByCategory
    *
    * Param - category The quest category
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Gamification")
  static UBCGamificationProxy *ReadQuestsByCategory(UBrainCloudWrapper *brainCloudWrapper, FString category, bool includeMetaData = false);
};
