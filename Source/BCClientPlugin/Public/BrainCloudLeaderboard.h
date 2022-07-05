// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

UENUM(BlueprintType)
enum class ESocialLeaderboardType : uint8
{
	HIGH_VALUE UMETA(DisplayName = "High Value"),
	CUMULATIVE UMETA(DisplayName = "Cumulative"),
	LAST_VALUE UMETA(DisplayName = "Last Value"),
	LOW_VALUE UMETA(DisplayName = "Low Value")
};

UENUM(BlueprintType)
enum class ERotationType : uint8
{
	NEVER UMETA(DisplayName = "Never"),
	DAILY UMETA(DisplayName = "Daily"),
	WEEKLY UMETA(DisplayName = "Weekly"),
	MONTHLY UMETA(DisplayName = "Monthly"),
	YEARLY UMETA(DisplayName = "Yearly")
};

UENUM(BlueprintType)
enum class ESortOrder : uint8
{
	HIGH_TO_LOW UMETA(DisplayName = "High to Low"),
	LOW_TO_HIGH UMETA(DisplayName = "Low to High")
};

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudLeaderboard
{
  public:
	BrainCloudLeaderboard(BrainCloudClient *client);

	/**
	 * Method returns the social leaderboard. A player's social leaderboard is
	 * comprised of players who are recognized as being your friend.
     * 
     * The getSocialLeaderboard will retrieve all friends from all friend platforms, so
     * - all external friends (Facebook, Steam, PlaystationNetwork)
     * - all internal friends (brainCloud)
     * - plus "self".
	 *
	 * Leaderboards entries contain the player's score and optionally, some user-defined
	 * data associated with the score. The currently logged in player will also
	 * be returned in the social leaderboard.
	 *
	 * Note: If no friends have played the game, the bestScore, createdAt, updatedAt
	 * will contain NULL.
	 *
	 * @param leaderboardId The id of the leaderboard to retrieve
	 * @param replaceName If true, the currently logged in player's name will be replaced
	 * by the string "You".
	 * @param callback The method to be invoked when the server response is received
	 *
	 */
	void getSocialLeaderboard(const FString &leaderboardId, bool replaceName, IServerCallback *callback = nullptr);

	/**
	 * Method returns the social leaderboard by its version. A player's social leaderboard is
	 * comprised of players who are recognized as being your friend.
     * 
     * The getSocialLeaderboard will retrieve all friends from all friend platforms, so
     * - all external friends (Facebook, Steam, PlaystationNetwork)
     * - all internal friends (brainCloud)
     * - plus "self".
	 *
	 * Leaderboards entries contain the player's score and optionally, some user-defined
	 * data associated with the score. The currently logged in player will also
	 * be returned in the social leaderboard.
	 *
	 * Note: If no friends have played the game, the bestScore, createdAt, updatedAt
	 * will contain NULL.
	 *
	 * @param leaderboardId The id of the leaderboard to retrieve
	 * @param replaceName If true, the currently logged in player's name will be replaced
	 * @param versionId the version
	 * by the string "You".
	 * @param callback The method to be invoked when the server response is received
	 *
	 */
	void getSocialLeaderboardByVersion(const FString &leaderboardId, bool replaceName, int32 version, IServerCallback *callback = nullptr);

	/**
	* Reads multiple social leaderboards.
	*
	* @param leaderboardIds Collection of leaderboard IDs.
	* @param leaderboardResultCount Maximum count of entries to return for each leaderboard.
	* @param replaceName If true, the currently logged in player's name will be replaced
	* by the string "You".
	* @param callback The method to be invoked when the server response is received
	*/
	void getMultiSocialLeaderboard(const TArray<FString> &leaderboardIds, int32 leaderboardResultCount, bool replaceName, IServerCallback *callback = nullptr);

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
	* @param leaderboardId The id of the leaderboard to retrieve.
	* @param sort Sort key Sort order of page.
	* @param startIndex The index at which to start the page.
	* @param endIndex The index at which to end the page.
	* @param callback The method to be invoked when the server response is received
	*/
	void getGlobalLeaderboardPage(const FString &leaderboardId, ESortOrder sortOrder, int32 startIndex, int32 endIndex, IServerCallback *callback = nullptr);

	/**
	* Method returns a page of global leaderboard results.
	* By using a non-current version id, the user can retrieve a historical leaderboard.
	* See GetGlobalLeaderboardVersions method to retrieve the version id.
	*
	* Service Name - SocialLeaderboard
	* Service Operation - GetGlobalLeaderboardPage
	*
	* @param leaderboardId The id of the leaderboard to retrieve.
	* @param sort Sort key Sort order of page.
	* @param startIndex The index at which to start the page.
	* @param endIndex The index at which to end the page.
	* @param versionId The historical version to retrieve.
	* @param callback The method to be invoked when the server response is received
	*/
	void getGlobalLeaderboardPageByVersion(const FString &leaderboardId, ESortOrder sortOrder, int32 startIndex, int32 endIndex, int32 versionId, IServerCallback *callback = nullptr);

	/**
	* Method returns a view of global leaderboard results that centers on the current player.
	*
	* Leaderboards entries contain the player's score and optionally, some user-defined
	* data associated with the score.
	*
	* Service Name - SocialLeaderboard
	* Service Operation - GetGlobalLeaderboardView
	*
	* @param leaderboardId The id of the leaderboard to retrieve.
	* @param sort Sort key Sort order of page.
	* @param beforeCount The count of number of players before the current player to include.
	* @param afterCount The count of number of players after the current player to include.
	* @param callback The method to be invoked when the server response is received
	*/
	void getGlobalLeaderboardView(const FString &leaderboardId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount, IServerCallback *callback = nullptr);

	/**
	* Method returns a view of global leaderboard results that centers on the current player.
	* By using a non-current version id, the user can retrieve a historical leaderboard.
	* See GetGlobalLeaderboardVersions method to retrieve the version id.
	*
	* Service Name - SocialLeaderboard
	* Service Operation - GetGlobalLeaderboardView
	*
	* @param leaderboardId The id of the leaderboard to retrieve.
	* @param sort Sort key Sort order of page.
	* @param beforeCount The count of number of players before the current player to include.
	* @param afterCount The count of number of players after the current player to include.
	* @param versionId The historical version to retrieve.
	* @param callback The method to be invoked when the server response is received
	*/
	void getGlobalLeaderboardViewByVersion(const FString &leaderboardId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount,
										   int32 versionId, IServerCallback *callback = nullptr);

	/**
	* Gets the number of entries in a global leaderboard
	*
	* Service Name - leaderboard
	* Service Operation - GET_GLOBAL_LEADERBOARD_ENTRY_COUNT
	*
	* @param leaderboardId The leaderboard ID
	* @param callback The method to be invoked when the server response is received
	*/
	void getGlobalLeaderboardEntryCount(const FString &leaderboardId, IServerCallback *callback = nullptr);

	/** Gets the global leaderboard versions.
	*
	* Service Name - SocialLeaderboard
	* Service Operation - GetGlobalLeaderboardVersions
	*
	* @param leaderboardId The leaderboard
	* @param callback The method to be invoked when the server response is received
	*/
	void getGlobalLeaderboardVersions(const FString &leaderboardId, IServerCallback *callback = nullptr);

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
	 * @param leaderboardId The leaderboard to post to
	 * @param score The score to post
	 * @param data Optional user-defined data to post with the score
	 * @param callback The method to be invoked when the server response is received
	 */
	void postScore(const FString &leaderboardId, int32 score, const FString &jsonOtherData, IServerCallback *callback = nullptr);


	/**
	 * @deprecated Please use PostScoreToDynamicLeaderboardUTC instead. Will be removed March 2021
	 */
	void postScoreToDynamicLeaderboard(const FString &leaderboardId, int32 score, const FString &jsonData,
									   ESocialLeaderboardType leaderboardType, ERotationType rotationType, const FDateTime &rotationStart, int32 retainedCount, IServerCallback *callback = nullptr);


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
	 * @param leaderboardId The leaderboard to post to
	 * @param score The score to post
	 * @param data Optional user-defined data to post with the score
	 * @param leaderboardType leaderboard type
	 * @param rotationType Type of rotation
	 * @param rotationStart Date to start rotation calculations (Date is converted to "dd-mm-yyyy" format)
	 * @param retainedCount How many rotations to keep
	 * @param callback The method to be invoked when the server response is received
	 */
	void postScoreToDynamicLeaderboardUTC(const FString &leaderboardId, int32 score, const FString &jsonData,
									   ESocialLeaderboardType leaderboardType, ERotationType rotationType, const int64 &rotationStart, int32 retainedCount, IServerCallback *callback = nullptr);

	/**
	 * @deprecated Please use PostScoreToDynamicLeaderboardDaysUTC instead. Will be removed March 2021
	 */
	void postScoreToDynamicLeaderboardDays(const FString &leaderboardId, int32 score, const FString &jsonData,
										   ESocialLeaderboardType leaderboardType, const FDateTime &rotationStart, int32 retainedCount, int32 numDaysToRotate, IServerCallback *callback = nullptr);

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
	* @param leaderboardId The leaderboard to post to
	* @param score The score to post
	* @param data Optional user-defined data to post with the score
	* @param leaderboardType leaderboard type
	* @param rotationStart Date to start rotation calculations (Date is converted to "dd-mm-yyyy" format)
	* @param retainedCount How many rotations to keep
	* @param numDaysToRotate How many days between each rotation
	* @param callback The method to be invoked when the server response is received/
	*/
	void postScoreToDynamicLeaderboardDaysUTC(const FString &leaderboardId, int32 score, const FString &jsonData,
										   ESocialLeaderboardType leaderboardType, const int64 &rotationStart, int32 retainedCount, int32 numDaysToRotate, IServerCallback *callback = nullptr);
	
	/**
	* Post the players score to the given social group leaderboard with a
	* rotation type of DAYS. You can optionally send a user-defined
	* JSON string of data with the posted score.
	* This string could include information relevant to the posted score.
	*
	* Service Name - SocialLeaderboard
	* Service Operation - PostScoreDynamic
	*
	* @param leaderboardId The leaderboard to post to
	* @param groupId The ID of the group
	* @param score The score to post
	* @param data Optional user-defined data to post with the score
	* @param leaderboardType leaderboard type
	* @param rotationResetUTC Date to start rotation calculations (Date is converted to "dd-mm-yyyy" format)
	* @param retainedCount How many rotations to keep
	* @param numDaysToRotate How many days between each rotation
	* @param callback The method to be invoked when the server response is received/
	*/
	void postScoreToDynamicGroupLeaderboardDaysUTC(const FString &leaderboardId, const FString &groupId, int32 score, const FString &jsonData,
                                           ESocialLeaderboardType leaderboardType, const FDateTime &rotationStart, int32 retainedCount, int32 numDaysToRotate, IServerCallback *callback = nullptr);

	/**
	* Removes a player's score from the leaderboard
	*
	* Service Name - leaderboard
	* Service Operation - REMOVE_PLAYER_SCORE
	*
	* @param leaderboardId The leaderboard ID
	* @param versionId The version of the leaderboard
	* @param callback The method to be invoked when the server response is received
	*/
	void removePlayerScore(const FString &leaderboardId, int32 versionId, IServerCallback *callback = nullptr);

	/**
	 * Method to retrieve the player's completed tournaments for the game.
	 * Arguments:
	 *  leaderboardId: Name of the leaderboard
	 *  replaceName: True to replace the player's name with "You"; false otherwise.
	 *  callback: client-side callback for the results
	 */
	void playerTournamentReward(const FString &eventName, uint64 multiplier, IServerCallback *callback = nullptr);

	/**
	* Retrieve the social leaderboard for a group.
	*
	* Service Name - leaderboard
	* Service Operation - GET_GROUP_SOCIAL_LEADERBOARD
	*
	* @param leaderboardId The leaderboard to retrieve
	* @param groupId The ID of the group
	* @param callback The method to be invoked when the server response is received
	*/
	void getGroupSocialLeaderboard(const FString &leaderboardId, const FString &groupId, IServerCallback *callback = nullptr);

	/**
	* Retrieve the social leaderboard for a group by its version.
	*
	* Service Name - leaderboard
	* Service Operation - GET_GROUP_SOCIAL_LEADERBOARD_BY_VERSION
	*
	* @param leaderboardId The leaderboard to retrieve
	* @param groupId The ID of the group
	* @param versionId the version
	* @param callback The method to be invoked when the server response is received
	*/
	void getGroupSocialLeaderboardByVersion(const FString &leaderboardId, const FString &groupId, int32 versionId, IServerCallback *callback = nullptr);

	/**
	* Retrieve the social leaderboard for a list of players.
	*
	* Service Name - leaderboard
	* Service Operation - GET_PLAYERS_SOCIAL_LEADERBOARD
	*
	* @param leaderboardId The leaderboard to retrieve
	* @param profileIds The IDs of the players
	* @param callback The method to be invoked when the server response is received
	*/
	void getPlayersSocialLeaderboard(const FString &leaderboardId, const TArray<FString> profileIds, IServerCallback *callback = nullptr);

	/**
	* Retrieve the social leaderboard for a list of players by the version of the leaderboard.
	*
	* Service Name - leaderboard
	* Service Operation - GET_PLAYERS_SOCIAL_LEADERBOARD_BY_VERSION
	*
	* @param leaderboardId The leaderboard to retrieve
	* @param profileIds The IDs of the players
	* @param versionId the version
	* @param callback The method to be invoked when the server response is received
	*/
	void getPlayersSocialLeaderboardByVersion(const FString &leaderboardId, const TArray<FString> profileIds, int32 versionId, IServerCallback *callback = nullptr);

	/**
	* Retrieve a list of all leaderboards
	*
	* Service Name - leaderboard
	* Service Operation - LIST_ALL_LEADERBOARDS
	*
	* @param callback The method to be invoked when the server response is received
	*/
	void listAllLeaderboards(IServerCallback *callback = nullptr);

	/**
	* Gets a player's score from a leaderboard
	*
	* Service Name - leaderboard
	* Service Operation - GET_PLAYER_SCORE
	*
	* @param leaderboardId The leaderboard ID
	* @param versionId The version of the leaderboard. Use -1 for current.
	* @param callback The method to be invoked when the server response is received
	*/
	void getPlayerScore(const FString &leaderboardId, int32 versionId, IServerCallback *callback = nullptr);

		/**
	* Gets a player's top scores from a leaderboard
	*
	* Service Name - leaderboard
	* Service Operation - GET_PLAYER_SCORES
	*
	* @param leaderboardId The leaderboard ID
	* @param versionId The version of the leaderboard. Use -1 for current.
	* @param maxResults the maximum number of returned results
	* @param callback The method to be invoked when the server response is received
	*/
	void getPlayerScores(const FString &leaderboardId, int32 versionId, int32 maxResults, IServerCallback *callback = nullptr);

	/**
	* Gets a player's score from multiple leaderboards
	*
	* Service Name - leaderboard
	* Service Operation - GET_PLAYER_SCORES_FROM_LEADERBOARDS
	*
	* @param leaderboardIds A collection of leaderboardIds to retrieve scores from
	* @param callback The method to be invoked when the server response is received
	*/
	void getPlayerScoresFromLeaderboards(const TArray<FString> leaderboardIds, IServerCallback *callback = nullptr);

	
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
	void postScoreToGroupLeaderboard(const FString &leaderboardId, const FString &groupId, int32 score, const FString &jsonOtherData, IServerCallback *callback = nullptr);
	
	/**
	 * @deprecated Please use PostScoreToDynamicGroupLeaderboardUTC instead. Will be removed March 2021
	 */
	void postScoreToDynamicGroupLeaderboard(const FString &leaderboardId, const FString &groupId, int32 score, const FString &jsonOtherData,ESocialLeaderboardType leaderboardType, ERotationType rotationType, const FDateTime &rotationStart, int32 retainedCount, IServerCallback *callback = nullptr);

	/**
	* Post the group score to the given group leaderboard and dynamically create if necessary. LeaderboardType, rotationType, rotationReset, and retainedCount are required.
	*
	* Service Name - leaderboard
	* Service Operation - POST_GROUP_SCORE
	*
	* @param in_leaderboardId A collection of leaderboardIds to retrieve scores from
	* @param in_groupId the groups Id
	* @param in_score the score you wish to post
	* @param rotationType Type of rotation
	* @param rotationStart Date to start rotation calculations (Date is converted to "dd-mm-yyyy" format)
	* @param retainedCount How many rotations to keep
	* @param callback The method to be invoked when the server response is received
	* @param in_jsonData extra json Data
	* @param in_callback The method to be invoked when the server response is received
	*/
	void postScoreToDynamicGroupLeaderboardUTC(const FString &leaderboardId, const FString &groupId, int32 score, const FString &jsonOtherData,ESocialLeaderboardType leaderboardType, ERotationType rotationType, const int64 &rotationStart, int32 retainedCount, IServerCallback *callback = nullptr);


	//void postScoreToDynamicLeaderboard(const FString &leaderboardId, int32 score, const FString &jsonData,
									   //ESocialLeaderboardType leaderboardType, ERotationType rotationType, const FDateTime &rotationStart, int32 retainedCount, IServerCallback *callback = nullptr);

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
	void removeGroupScore(const FString &leaderboardId, const FString &groupId, int32 score, int32 versionId, IServerCallback *callback = nullptr);

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
	void getGroupLeaderboardView(const FString &leaderboardId, const FString &groupId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount, IServerCallback *callback = nullptr);

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
	void getGroupLeaderboardViewByVersion(const FString &leaderboardId, const FString &groupId, int32 versionId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount, IServerCallback *callback = nullptr);

  private:
	BrainCloudClient *_client = nullptr;

	FString leaderboardTypeToString(ESocialLeaderboardType type);
	FString leaderboardRotationTypeToString(ERotationType type);
	FString leaderboardSortOrderToString(ESortOrder type);
};
