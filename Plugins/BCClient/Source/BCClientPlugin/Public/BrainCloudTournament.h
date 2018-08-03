// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudTournament
{
public:
	BrainCloudTournament(BrainCloudClient* client);

	/**
	* Processes any outstanding rewards for the given player
	*
	* Service Name - tournament
	* Service Operation - CLAIM_TOURNAMENT_REWARD
	*
	* @param leaderboardId The leaderboard for the tournament
	* @param versionId Version of the tournament. Use -1 for the latest version.
	* @param callback The method to be invoked when the server response is received
	*/
	void claimTournamentReward(const FString& leaderboardId, int32 versionId, IServerCallback * callback = nullptr);

	/**
	* Get tournament status associated with a leaderboard
	*
	* Service Name - tournament
	* Service Operation - GET_TOURNAMENT_STATUS
	*
	* @param leaderboardId The leaderboard for the tournament
	* @param versionId Version of the tournament. Use -1 for the latest version.
	* @param callback The method to be invoked when the server response is received
	*/
	void getTournamentStatus(const FString& leaderboardId, int32 versionId, IServerCallback * callback = nullptr);

	/**
	* Join the specified tournament.
	* Any entry fees will be automatically collected.
	*
	* Service Name - tournament
	* Service Operation - JOTOURNAMENT
	*
	* @param leaderboardId The leaderboard for the tournament
	* @param tournamentCode Tournament to join
	* @param initialScore Initial score for the user
	* @param callback The method to be invoked when the server response is received
	*/
	void joinTournament(const FString& leaderboardId, const FString& tournamentCode, int32 initialScore, IServerCallback * callback = nullptr);

	/**
	* Removes player's score from tournament leaderboard
	*
	* Service Name - tournament
	* Service Operation - LEAVE_TOURNAMENT
	*
	* @param leaderboardId The leaderboard for the tournament
	* @param callback The method to be invoked when the server response is received
	*/
	void leaveTournament(const FString& leaderboardId, IServerCallback * callback = nullptr);

	/**
	* Post the users score to the leaderboard
	*
	* Service Name - tournament
	* Service Operation - POST_TOURNAMENT_SCORE
	*
	* @param leaderboardId The leaderboard for the tournament
	* @param score The score to post
	* @param jsonData Optional data attached to the leaderboard entry
	* @param roundStartedTime Time the user started the match resulting in the score being posted in UTC.
	* @param callback The method to be invoked when the server response is received
	*/
	void postTournamentScore(const FString& leaderboardId, int32 score, const FString& jsonData, const struct FDateTime roundStartedTime, IServerCallback * callback = nullptr);

	/**
	* Returns the user's expected reward based on the current scores
	*
	* Service Name - tournament
	* Service Operation - VIEW_CURRENT_REWARD
	*
	* @param leaderboardId The leaderboard for the tournament
	* @param callback The method to be invoked when the server response is received
	*/
	void viewCurrentReward(const FString& leaderboardId, IServerCallback * callback = nullptr);

	/**
	* Returns the user's reward from a finished tournament
	*
	* Service Name - tournament
	* Service Operation - VIEW_REWARD
	*
	* @param leaderboardId The leaderboard for the tournament
	* @param versionId Version of the tournament. Use -1 for the latest version.
	* @param callback The method to be invoked when the server response is received
	*/
	void viewReward(const FString& leaderboardId, int32 versionId, IServerCallback * callback = nullptr);

private:
	BrainCloudClient* _client = nullptr;
};

