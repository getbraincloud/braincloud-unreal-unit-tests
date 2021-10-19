// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BrainCloudLeaderboard.h"
#include "BCLeaderboardProxy.generated.h"

UCLASS(MinimalAPI)
class UBCLeaderboardProxy : public UBCBlueprintCallProxyBase
{
	GENERATED_BODY()

  public:
	UBCLeaderboardProxy(const FObjectInitializer &ObjectInitializer);

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
	static UBCLeaderboardProxy *GetSocialLeaderboard(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, bool replaceName);

	/**
	* Method returns the social leaderboard by its version. A player's social leaderboard is
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
	* Param - versionId the version
	* by the string "You".
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
	static UBCLeaderboardProxy *GetSocialLeaderboardByVersion(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, bool replaceName, int32 versionId);

	/**
	* Reads multiple social leaderboards.
	*
	* Param - leaderboardIds Collection of leaderboard IDs.
	* Param - leaderboardResultCount Maximum count of entries to return for each leaderboard.
	* Param - replaceName If true, the currently logged in player's name will be replaced
	* by the string "You".
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
	static UBCLeaderboardProxy *GetMultiSocialLeaderboard(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &leaderboardIds, int32 leaderboardResultCount, bool replaceName);

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
	static UBCLeaderboardProxy *GetGlobalLeaderboardPage(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, ESortOrder sortOrder, int32 startIndex, int32 endIndex);

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
	static UBCLeaderboardProxy *GetGlobalLeaderboardPageByVersion(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, ESortOrder sortOrder, int32 startIndex, int32 endIndex, int32 versionId);

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
	static UBCLeaderboardProxy *GetGlobalLeaderboardView(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount);

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
	static UBCLeaderboardProxy *GetGlobalLeaderboardViewByVersion(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount, int32 versionId);

	/**
	* Gets the number of entries in a global leaderboard
	*
	* Param - leaderboardId The id of the leaderboard to retrieve.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
	static UBCLeaderboardProxy *GetGlobalLeaderboardEntryCount(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId);

	/** Gets the global leaderboard versions.
	*
	* Service Name - SocialLeaderboard
	* Service Operation - GetGlobalLeaderboardVersions
	*
	* Param - leaderboardId The leaderboard
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
	static UBCLeaderboardProxy *GetGlobalLeaderboardVersions(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId);

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
	static UBCLeaderboardProxy *PostScore(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, int32 score, FString jsonData);

	/**
	 * @deprecated Please use PostScoreToDynamicLeaderboardUTC instead. Will be removed March 2021
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
	static UBCLeaderboardProxy *PostScoreToDynamicLeaderboard(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, int32 score, FString jsonData,
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
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
	static UBCLeaderboardProxy *PostScoreToDynamicLeaderboardUTC(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, int32 score, FString jsonData,
															  ESocialLeaderboardType leaderboardType, ERotationType rotationType, int64 rotationStart, int32 retainedCount);

	/**
	 * @deprecated Please use PostScoreToDynamicGroupLeaderboardUTC instead. Will be removed March 2021
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
	static UBCLeaderboardProxy *PostScoreToDynamicGroupLeaderboard(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, const FString &groupId, int32 score, FString jsonData,
															  ESocialLeaderboardType leaderboardType, ERotationType rotationType, FDateTime rotationStart, int32 retainedCount);

	/**
	* Posts score to group leaderbopard and dynamically creates if necessary.
	* leaderboardType, rotationReset, retainedCount and rotationType are required.
	* uses UTC time in milliseconds since epoch
	*
	* Service Name - SocialLeaderboard
	* Service Operation - POST_GROUP_SCORE_DYNAMIC
	*
	* Param - leaderboardId The leaderboard to post to
	* Param - in_groupId the groups Id
	* Param - score The score to post
	* Param - data Optional user-defined data to post with the score
	* Param - leaderboardType leaderboard type
	* Param - rotationType Type of rotation
	* Param - rotationStart Date to start rotation calculations (Date is converted to "dd-mm-yyyy hh:mm" format)
	* Param - retainedCount How many rotations to keep
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
	static UBCLeaderboardProxy *PostScoreToDynamicGroupLeaderboardUTC(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, const FString &groupId, int32 score, FString jsonData,
															  ESocialLeaderboardType leaderboardType, ERotationType rotationType, int64 rotationStart, int32 retainedCount);
	
	/**
	 * @deprecated Please use PostScoreToDynamicLeaderboardDaysUTC instead. Will be removed March 2021
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
	static UBCLeaderboardProxy *PostScoreToDynamicLeaderboardDays(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, int32 score, FString jsonData,
																  ESocialLeaderboardType leaderboardType, FDateTime rotationStart, int32 retainedCount, int32 numDaysToRotate);

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
	static UBCLeaderboardProxy *PostScoreToDynamicLeaderboardDaysUTC(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, int32 score, FString jsonData,
																  ESocialLeaderboardType leaderboardType, int64 rotationStart, int32 retainedCount, int32 numDaysToRotate);

	/**
	* Post the players score to the given social group leaderboard with a
	* rotation type of DAYS. You can optionally send a user-defined
	* JSON string of data with the posted score.
	* This string could include information relevant to the posted score.
	*
	* Service Name - SocialLeaderboard
	* Service Operation - PostScoreDynamic
	*
	* Param leaderboardId The leaderboard to post to
	* Param groupId The ID of the group
	* Param score The score to post
	* Param data Optional user-defined data to post with the score
	* Param leaderboardType leaderboard type
	* Param rotationResetUTC Date to start rotation calculations (Date is converted to "dd-mm-yyyy" format)
	* Param retainedCount How many rotations to keep
	* Param numDaysToRotate How many days between each rotation
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
    static UBCLeaderboardProxy *PostScoreToDynamicGroupLeaderboardDaysUTC(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, FString groupId, int32 score, FString jsonData,
                                                                  ESocialLeaderboardType leaderboardType, FDateTime rotationResetUTC, int32 retainedCount, int32 numDaysToRotate);

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
	static UBCLeaderboardProxy *RemovePlayerScore(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, int32 versionId);

	/**
	* Retrieve the social leaderboard for a group.
	*
	* Param - leaderboardId The leaderboard to retrieve
	* Param - groupId The ID of the group
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
	static UBCLeaderboardProxy *GetGroupSocialLeaderboard(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, const FString &groupId);

	/**
	* Retrieve the social leaderboard for a group by its version.
	*
	* Param - leaderboardId The leaderboard to retrieve
	* Param - groupId The ID of the group
	* Param - versionId the version
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
	static UBCLeaderboardProxy *GetGroupSocialLeaderboardByVersion(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, const FString &groupId, int32 versionId);

	/**
	* Retrieve the social leaderboard for a list of players.
	*
	* Param - leaderboardId The leaderboard to retrieve
	* Param - profileIds The IDs of the players
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
	static UBCLeaderboardProxy *GetPlayersSocialLeaderboard(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, const TArray<FString> profileIds);

	/**
	* Retrieve the social leaderboard for a list of players.
	*
	* Param - leaderboardId The leaderboard to retrieve
	* Param - profileIds The IDs of the players
	* Param - versionId the version
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
	static UBCLeaderboardProxy *GetPlayersSocialLeaderboardByVersion(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, const TArray<FString> profileIds, int32 versionId);

	/**
	* Retrieve a list of all leaderboards
	*
	* Service Name - leaderboard
	* Service Operation - LIST_ALL_LEADERBOARDS
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
	static UBCLeaderboardProxy *ListAllLeaderboards(UBrainCloudWrapper *brainCloudWrapper);

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
	static UBCLeaderboardProxy *GetPlayerScore(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, int32 versionId);

	/**
	* Gets a player's beat scores from a leaderboard
	*
	* Service Name - leaderboard
	* Service Operation - GET_PLAYER_SCORES
	*
	* Param - leaderboardId The leaderboard ID
	* Param - versionId The version of the leaderboard. Use -1 for current.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
	static UBCLeaderboardProxy *GetPlayerScores(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, int32 versionId, int32 maxResults);


	/**
	* Gets a player's score from multiple leaderboards
	*
	* Service Name - leaderboard
	* Service Operation - GET_PLAYER_SCORES_FROM_LEADERBOARDS
	*
	* @Param - leaderboardIds A collection of leaderboardIds to retrieve scores from
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
	static UBCLeaderboardProxy *GetPlayerScoresFromLeaderboards(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> leaderboardIds);

		/**
	* Posts score to groups leaderboard - Note the user must be a member of the group
	*
	* Service Name - leaderboard
	* Service Operation - POST_GROUP_SCORE
	*
	* @param in_leaderboardId A collection of leaderboardIds to retrieve scores from
	* @param in_groupId the groups Id
	* @param in_score the score you wish to post
	* @param in_jsonData extra json Data
	* @param in_callback The method to be invoked when the server response is received
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
	static UBCLeaderboardProxy *PostScoreToGroupLeaderboard(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, const FString &groupId, int32 score, const FString &jsonOtherData);

	/**
	* Removes score from group leaderboard
	*
	* Service Name - leaderboard
	* Service Operation - REMOVE_GROUP_SCORE
	*
	* @param in_leaderboardId A collection of leaderboardIds to retrieve scores from
	* @param in_groupId the groups Id
	* @param in_versionId the score you wish to post
	* @param in_callback The method to be invoked when the server response is received
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
	static UBCLeaderboardProxy *RemoveGroupScore(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, const FString &groupId, int32 score, int32 versionId);

	/**
	* Retrieve a view of the group leaderboardsurrounding the current group.
	*
	* Service Name - leaderboard
	* Service Operation - GET_GROUP_LEADERBOARD_VIEW
	*
	* @param in_leaderboardId A collection of leaderboardIds to retrieve scores from
	* @param in_groupId the groups Id
	* @param in_sortOrder the sort order
	* @param in_beforeCount count of players before current player to include
	* @param in_afterCount count of players after current player to include
	* @param in_callback The method to be invoked when the server response is received
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
	static UBCLeaderboardProxy *GetGroupLeaderboardView(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, const FString &groupId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount);

	/**
	* Retrieve a view of the group leaderboard surrounding the current group by the version
	*
	* Service Name - leaderboard
	* Service Operation - GET_GROUP_LEADERBOARD_VIEW
	*
	* @param in_leaderboardId A collection of leaderboardIds to retrieve scores from
	* @param in_groupId the groups Id
	* @param in_versionId the version
	* @param in_sortOrder the sort order
	* @param in_beforeCount count of players before current player to include
	* @param in_afterCount count of players after current player to include
	* @param in_callback The method to be invoked when the server response is received
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Leaderboard")
	static UBCLeaderboardProxy *GetGroupLeaderboardViewByVersion(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, const FString &groupId, int32 versionId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount);

};
