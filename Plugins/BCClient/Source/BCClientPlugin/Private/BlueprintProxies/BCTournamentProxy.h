// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCTournamentProxy.generated.h"

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
	* Get the status of a division
	*
	* Service Name - tournament
	* Service Operation - GET_DIVISION_INFO
	*
	* @param divSetId The id for the division
	* @param callback The method to be invoked when the server response is received
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Tournament")
	static UBCTournamentProxy *GetDivisionInfo(UBrainCloudWrapper *brainCloudWrapper, const FString &divSetId);

	/**
	* Returns list of player's recently active divisions
	*
	* Service Name - tournament
	* Service Operation - GET_MY_DIVISIONS
	*
	* @param callback The method to be invoked when the server response is received
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Tournament")
	static UBCTournamentProxy *GetMyDivisions(UBrainCloudWrapper *brainCloudWrapper);

	/**
	* Join the specified division.
	* If joining requires a fee, it is possible to fail at joining the division
	*
	* Service Name - tournament
	* Service Operation - JOIN_DIVISION
	*
	* @param divSetId The id for the division
	* @param tournamentCode Tournament to join
	* @param initialScore The initial score for players first joining a tournament
	*						 Usually 0, unless leaderboard is LOW_VALUE
	* @param callback The method to be invoked when the server response is received
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Tournament")
	static UBCTournamentProxy *JoinDivision(UBrainCloudWrapper *brainCloudWrapper, const FString &divSetId, const FString &tournamentCode, int32 initialScore);

	/**
	* Removes player from division instance
	* Also removes division instance from player's division list
	*
	* Service Name - tournament
	* Service Operation - LEAVE_DIVISION_INSTANCE
	*
	* @param leaderboardId The leaderboard for the tournament
	* @param callback The method to be invoked when the server response is received
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Tournament")
	static UBCTournamentProxy *LeaveDivisionInstance(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId);

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
	* @deprecated will be removed March 2021, Use postTournamentScoreUTC instead
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Tournament")
	static UBCTournamentProxy *PostTournamentScore(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, int32 score, const FString &jsonData, const struct FDateTime roundStartedTime);

	/**
	* @deprecated will be removed March 2021, Use postTournamentScoreWithResultsUTC instead
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Tournament")
	static UBCTournamentProxy *PostTournamentScoreWithResults(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, int32 score, const FString &jsonData, const struct FDateTime roundStartedTime, ESortOrder sort, int32 beforeCount, int32 afterCount, float initialScore);

	/**
	* Post the users score to the leaderboard
	*
	* Service Name - tournament
	* Service Operation - POST_TOURNAMENT_SCORE
	*
	* Param - leaderboardId The leaderboard for the tournament
	* Param - score The score to post
	* Param - jsonData Optional data attached to the leaderboard entry
	* Param - roundStartTimeUTC Time the user started the match resulting in the score being posted in UTC.
	*/

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Tournament")
	static UBCTournamentProxy *PostTournamentScoreUTC(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, int32 score, const FString &jsonData, int64 roundStartTimeUTC);

	/**
	* Post the users score to the leaderboard and the result for the score
	*
	* Service Name - tournament
	* Service Operation - POST_TOURNAMENT_SCORE_WITH_RESULTS
	*
	* @param leaderboardId The leaderboard for the tournament
	* @param score The score to post
	* @param jsonData Optional data attached to the leaderboard entry
	* @param roundStartedTime Time the user started the match resulting in the score being posted in UTC.
	* @param sort the sorting type
	* @param beforeCount 
	* @param afterCount
	* @param initialScore
	* @param callback The method to be invoked when the server response is received
	*/

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Tournament")
	static UBCTournamentProxy *PostTournamentScoreWithResultsUTC(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, int32 score, const FString &jsonData, int64 roundStartedTime, ESortOrder sort, int32 beforeCount, int32 afterCount, float initialScore);


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
