// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BrainCloudLeaderboard.h"
#include "BCLeaderboardProxy.generated.h"

class ABrainCloud;

UCLASS(MinimalAPI)
class UBCLeaderboardProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
	GENERATED_BODY()

public:
	UBCLeaderboardProxy(const FObjectInitializer& ObjectInitializer);

	/**
	* Method returns the social leaderboard. A player's social leaderboard is
	* comprised of players who are recognized as being your friend.
	* For now, this applies solely to Facebook connected players who are
	* friends with the logged in player (who also must be Facebook connected).
	* In the future this will expand to other identification means (such as
	* Game Centre, Google circles etc).
	*
	* Leaderboards entries contain the player's score and optionally, some user-defined
	* data associated with the score. The currently logged in player will also
	* be returned in the social leaderboard.
	*
	* Note: If no friends have played the game, the bestScore, createdAt, updatedAt
	* will contain NULL.
	*
	* Param - leaderboardId The id of the leaderboard to retrieve
	* Param - replaceName If true, the currently logged in player's name will be replaced
	* by the string "You".
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
		static UBCLeaderboardProxy* GetSocialLeaderboard(ABrainCloudActor *brainCloud, FString leaderboardId, bool replaceName);

	/**
	* Reads multiple social leaderboards.
	*
	* Param - leaderboardIds Collection of leaderboard IDs.
	* Param - leaderboardResultCount Maximum count of entries to return for each leaderboard.
	* Param - replaceName If true, the currently logged in player's name will be replaced
	* by the string "You".
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
		static UBCLeaderboardProxy* GetMultiSocialLeaderboard(ABrainCloudActor *brainCloud, const TArray<FString>& leaderboardIds, int32 leaderboardResultCount, bool replaceName);

	/**
	* Method returns a page of global leaderboard results.
	*
	* Leaderboards entries contain the player's score and optionally, some user-defined
	* data associated with the score.
	*
	* Note: This method allows the client to retrieve pages from within the global leaderboard list
	*
	* Service Name - SocialLeaderboard
	* Service Operation - GetGlobalLeaderboardPage
	*
	* Param - leaderboardId The id of the leaderboard to retrieve.
	* Param - sort Sort key Sort order of page.
	* Param - startIndex The index at which to start the page.
	* Param - endIndex The index at which to end the page.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
		static UBCLeaderboardProxy* GetGlobalLeaderboardPage(ABrainCloudActor *brainCloud, FString leaderboardId, ESortOrder sortOrder, int32 startIndex, int32 endIndex);

	/**
	* Method returns a page of global leaderboard results.
	* By using a non-current version id, the user can retrieve a historial leaderboard.
	* See GetGlobalLeaderboardVersions method to retrieve the version id.
	*
	* Service Name - SocialLeaderboard
	* Service Operation - GetGlobalLeaderboardPage
	*
	* Param - leaderboardId The id of the leaderboard to retrieve.
	* Param - sort Sort key Sort order of page.
	* Param - startIndex The index at which to start the page.
	* Param - endIndex The index at which to end the page.
	* Param - versionId The historical version to retrieve.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
		static UBCLeaderboardProxy* GetGlobalLeaderboardPageByVersion(ABrainCloudActor *brainCloud, FString leaderboardId, ESortOrder sortOrder, int32 startIndex, int32 endIndex, int32 versionId);

	/**
	* Method returns a view of global leaderboard results that centers on the current player.
	*
	* Leaderboards entries contain the player's score and optionally, some user-defined
	* data associated with the score.
	*
	* Service Name - SocialLeaderboard
	* Service Operation - GetGlobalLeaderboardView
	*
	* Param - leaderboardId The id of the leaderboard to retrieve.
	* Param - sort Sort key Sort order of page.
	* Param - beforeCount The count of number of players before the current player to include.
	* Param - afterCount The count of number of players after the current player to include.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
		static UBCLeaderboardProxy* GetGlobalLeaderboardView(ABrainCloudActor *brainCloud, FString leaderboardId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount);

	/**
	* Method returns a view of global leaderboard results that centers on the current player.
	* By using a non-current version id, the user can retrieve a historial leaderboard.
	* See GetGlobalLeaderboardVersions method to retrieve the version id.
	*
	* Service Name - SocialLeaderboard
	* Service Operation - GetGlobalLeaderboardView
	*
	* Param - leaderboardId The id of the leaderboard to retrieve.
	* Param - sort Sort key Sort order of page.
	* Param - beforeCount The count of number of players before the current player to include.
	* Param - afterCount The count of number of players after the current player to include.
	* Param - versionId The historical version to retrieve.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
		static UBCLeaderboardProxy* GetGlobalLeaderboardViewByVersion(ABrainCloudActor *brainCloud, FString leaderboardId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount, int32 versionId);

	/**
	* Gets the number of entries in a global leaderboard
	*
	* Param - leaderboardId The id of the leaderboard to retrieve.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
		static UBCLeaderboardProxy* GetGlobalLeaderboardEntryCount(ABrainCloudActor *brainCloud, FString leaderboardId);

	/** Gets the global leaderboard versions.
	*
	* Service Name - SocialLeaderboard
	* Service Operation - GetGlobalLeaderboardVersions
	*
	* Param - leaderboardId The leaderboard
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
		static UBCLeaderboardProxy* GetGlobalLeaderboardVersions(ABrainCloudActor *brainCloud, FString leaderboardId);

	/**
	* Post the players score to the given social leaderboard.
	* You can optionally send a user-defined json string of data
	* with the posted score. This string could include information
	* relevant to the posted score.
	*
	* Note that the behaviour of posting a score can be modified in
	* the brainCloud portal. By default, the server will only keep
	* the player's best score.
	*
	* Param - leaderboardId The leaderboard to post to
	* Param - score The score to post
	* Param - data Optional user-defined data to post with the score
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
		static UBCLeaderboardProxy* PostScore(ABrainCloudActor *brainCloud, FString leaderboardId, int32 score, FString jsonData);

	/**
	* Post the players score to the given social leaderboard.
	* Pass leaderboard config data to dynamically create if necessary.
	* You can optionally send a user-defined json string of data
	* with the posted score. This string could include information
	* relevant to the posted score.
	*
	* Service Name - SocialLeaderboard
	* Service Operation - PostScoreDynamic
	*
	* Param - leaderboardId The leaderboard to post to
	* Param - score The score to post
	* Param - data Optional user-defined data to post with the score
	* Param - leaderboardType leaderboard type
	* Param - rotationType Type of rotation
	* Param - rotationStart Date to start rotation calculations (Date is converted to "dd-mm-yyyy hh:mm" format)
	* Param - retainedCount How many rotations to keep
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
		static UBCLeaderboardProxy* PostScoreToDynamicLeaderboard(ABrainCloudActor *brainCloud, FString leaderboardId, int32 score, FString jsonData,
			ESocialLeaderboardType leaderboardType, ERotationType rotationType, FDateTime rotationStart, int32 retainedCount);

	/**
	* Post the players score to the given social leaderboard.
	* Pass leaderboard config data to dynamically create if necessary.
	* You can optionally send a user-defined json string of data
	* with the posted score. This string could include information
	* relevant to the posted score.
	*
	* Service Name - SocialLeaderboard
	* Service Operation - PostScoreDynamic
	*
	* Param - leaderboardId The leaderboard to post to
	* Param - score The score to post
	* Param - data Optional user-defined data to post with the score
	* Param - leaderboardType leaderboard type
	* Param - rotationType Type of rotation
	* Param - rotationStart Date to start rotation calculations (Date is converted to "dd-mm-yyyy hh:mm" format)
	* Param - retainedCount How many rotations to keep
	* Param - numDaysToRotate How many days between each rotation
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
		static UBCLeaderboardProxy* PostScoreToDynamicLeaderboardDays(ABrainCloudActor *brainCloud, FString leaderboardId, int32 score, FString jsonData,
			ESocialLeaderboardType leaderboardType, FDateTime rotationStart, int32 retainedCount, int32 numDaysToRotate);

	/**
	* Removes a player's score from the leaderboard
	*
	* Service Name - leaderboard
	* Service Operation - REMOVE_PLAYER_SCORE
	*
	* Param - leaderboardId The leaderboard ID
	* Param - versionId The version of the leaderboard
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
		static UBCLeaderboardProxy* RemovePlayerScore(ABrainCloudActor *brainCloud, const FString& leaderboardId, int32 versionId);

    /**
	* Retrieve the social leaderboard for a group.
	*
	* Param - leaderboardId The leaderboard to retrieve
	* Param - groupId The ID of the group
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
		static UBCLeaderboardProxy* GetGroupSocialLeaderboard(ABrainCloudActor *brainCloud, const FString& leaderboardId, const FString& groupId);

	/**
	* Retrieve the social leaderboard for a list of players.
	*
	* Param - leaderboardId The leaderboard to retrieve
	* Param - profileIds The IDs of the players
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
		static UBCLeaderboardProxy* GetPlayersSocialLeaderboard(ABrainCloudActor *brainCloud, const FString& leaderboardId, const TArray<FString> profileIds);

	/**
	* Retrieve a list of all leaderboards
	*
	* Service Name - leaderboard
	* Service Operation - LIST_ALL_LEADERBOARDS
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
		static UBCLeaderboardProxy* ListAllLeaderboards(ABrainCloudActor *brainCloud);

	/**
	* Gets a player's score from a leaderboard
	*
	* Service Name - leaderboard
	* Service Operation - GET_PLAYER_SCORE
	*
	* Param - leaderboardId The leaderboard ID
	* Param - versionId The version of the leaderboard. Use -1 for current.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
		static UBCLeaderboardProxy* GetPlayerScore(ABrainCloudActor *brainCloud, const FString& leaderboardId, int32 versionId);

	/**
	* Gets a player's score from multiple leaderboards
	*
	* Service Name - leaderboard
	* Service Operation - GET_PLAYER_SCORES_FROM_LEADERBOARDS
	*
	* @Param - leaderboardIds A collection of leaderboardIds to retrieve scores from
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
		static UBCLeaderboardProxy* GetPlayerScoresFromLeaderboards(ABrainCloudActor *brainCloud, const TArray<FString> leaderboardIds);

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
