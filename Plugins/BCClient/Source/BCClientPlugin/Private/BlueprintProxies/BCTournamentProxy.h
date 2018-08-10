// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCTournamentProxy.generated.h"

class ABrainCloud;

UCLASS(MinimalAPI)
class UBCTournamentProxy : public UBCBlueprintCallProxyBase
{
	GENERATED_BODY()

  public:
	UBCTournamentProxy(const FObjectInitializer &ObjectInitializer);

	/**
	* Processes any outstanding rewards for the given player
	*
	* Service Name - tournament
	* Service Operation - CLAIM_TOURNAMENT_REWARD
	*
	* Param - leaderboardId The leaderboard for the tournament
	* Param - versionId Version of the tournament. Use -1 for the latest version.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Tournament")
	static UBCTournamentProxy *ClaimTournamentReward(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, int32 versionId);

	/**
	* Get tournament status associated with a leaderboard
	*
	* Service Name - tournament
	* Service Operation - GET_TOURNAMENT_STATUS
	*
	* Param - leaderboardId The leaderboard for the tournament
	* Param - versionId Version of the tournament. Use -1 for the latest version.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Tournament")
	static UBCTournamentProxy *GetTournamentStatus(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, int32 versionId);

	/**
	* Join the specified tournament.
	* Any entry fees will be automatically collected.
	*
	* Service Name - tournament
	* Service Operation - JOIN_TOURNAMENT
	*
	* Param - leaderboardId The leaderboard for the tournament
	* Param - tournamentCode Tournament to join
	* Param - initialScore Initial score for the user
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Tournament")
	static UBCTournamentProxy *JoinTournament(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, const FString &tournamentCode, int32 initialScore);

	/**
	* Removes player's score from tournament leaderboard
	*
	* Service Name - tournament
	* Service Operation - LEAVE_TOURNAMENT
	*
	* Param - leaderboardId The leaderboard for the tournament
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Tournament")
	static UBCTournamentProxy *LeaveTournament(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId);

	/**
	* Post the users score to the leaderboard
	*
	* Service Name - tournament
	* Service Operation - POST_TOURNAMENT_SCORE
	*
	* Param - leaderboardId The leaderboard for the tournament
	* Param - score The score to post
	* Param - jsonData Optional data attached to the leaderboard entry
	* Param - roundStartedTime Time the user started the match resulting in the score being posted in UTC.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Tournament")
	static UBCTournamentProxy *PostTournamentScore(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, int32 score, const FString &jsonData, const struct FDateTime roundStartedTime);

	/**
	* Returns the user's expected reward based on the current scores
	*
	* Service Name - tournament
	* Service Operation - VIEW_CURRENT_REWARD
	*
	* Param - leaderboardId The leaderboard for the tournament
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Tournament")
	static UBCTournamentProxy *ViewCurrentReward(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId);

	/**
	* Returns the user's reward from a finished tournament
	*
	* Service Name - tournament
	* Service Operation - VIEW_REWARD
	*
	* Param - leaderboardId The leaderboard for the tournament
	* Param - versionId Version of the tournament. Use -1 for the latest version.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Tournament")
	static UBCTournamentProxy *ViewReward(UBrainCloudWrapper *brainCloud, const FString &leaderboardId, int32 versionId);
};
