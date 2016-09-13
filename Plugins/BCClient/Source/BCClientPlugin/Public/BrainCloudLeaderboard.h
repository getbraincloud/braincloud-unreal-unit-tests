// Copyright 2016 bitHeads, Inc. All Rights Reserved.

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
	BrainCloudLeaderboard(BrainCloudClient* client);

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
	 * @param leaderboardId The id of the leaderboard to retrieve
	 * @param replaceName If true, the currently logged in player's name will be replaced
	 * by the string "You".
	 * @param callback The method to be invoked when the server response is received
	 *
	 */
	void getSocialLeaderboard(const FString& leaderboardId, bool replaceName, IServerCallback * callback = nullptr);

	/**
	* Reads multiple social leaderboards.
	*
	* @param leaderboardIds Collection of leaderboard IDs.
	* @param leaderboardResultCount Maximum count of entries to return for each leaderboard.
	* @param replaceName If true, the currently logged in player's name will be replaced
	* by the string "You".
	* @param callback The method to be invoked when the server response is received
	*/
	void getMultiSocialLeaderboard(const TArray<FString>& leaderboardIds, int32 leaderboardResultCount, bool replaceName, IServerCallback * callback = nullptr);

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
	* @param includeLeaderboardSize Whether to return the leaderboard size
	* @param callback The method to be invoked when the server response is received
	*/
	void getGlobalLeaderboardPage(const FString& leaderboardId, ESortOrder sortOrder, int32 startIndex, int32 endIndex, bool includeLeaderboardSize, IServerCallback * callback = nullptr);

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
	* @param includeLeaderboardSize Whether to return the leaderboard size
	* @param versionId The historical version to retrieve.
	* @param callback The method to be invoked when the server response is received
	*/
	void getGlobalLeaderboardPageByVersion(const FString& leaderboardId, ESortOrder sortOrder, int32 startIndex, int32 endIndex, bool includeLeaderboardSize, int32 versionId, IServerCallback * callback = nullptr);

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
	* @param includeLeaderboardSize Whether to return the leaderboard size
	* @param callback The method to be invoked when the server response is received
	*/
	void getGlobalLeaderboardView(const FString& leaderboardId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount, bool includeLeaderboardSize, IServerCallback * callback = nullptr);

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
	* @param includeLeaderboardSize Whether to return the leaderboard size
	* @param versionId The historical version to retrieve.
	* @param callback The method to be invoked when the server response is received
	*/
	void getGlobalLeaderboardViewByVersion(const FString& leaderboardId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount, bool includeLeaderboardSize, int32 versionId, IServerCallback * callback = nullptr);

	/** Gets the global leaderboard versions.
	*
	* Service Name - SocialLeaderboard
	* Service Operation - GetGlobalLeaderboardVersions
	*
	* @param leaderboardId The leaderboard
	* @param callback The method to be invoked when the server response is received
	*/
	void getGlobalLeaderboardVersions(const FString& leaderboardId, IServerCallback * callback = nullptr);

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
	void postScore(const FString& leaderboardId, int32 score, const FString& jsonOtherData, IServerCallback * callback = nullptr);

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
	void postScoreToDynamicLeaderboard(const FString& leaderboardId, int32 score, const FString& jsonData,
		ESocialLeaderboardType leaderboardType, ERotationType rotationType, const FDateTime& rotationStart, int32 retainedCount, IServerCallback * callback = nullptr);

	/**
	 * Reset the player's score for the given social leaderboard id.
	 *
	 * @param leaderboardId The leaderboard to post to
	 * @param callback The method to be invoked when the server response is received
	 */
	void resetLeaderboardScore(const FString& leaderBoardName, IServerCallback * callback = nullptr);

	/**
	 * If a social leaderboard has been configured to reset periodically, each period
	 * can be considered to be a tournament. When the leaderboard resets, the tournament
	 * has ended and participants can be ranked based on their final scores.
	 *
	 * This API method will return the sorted leaderboard including:
	 * the player
	 * the game's pacers
	 * all friends who participated in the tournament
	 *
	 * This API method will return the leaderboard results for a particular
	 * tournament only once. If the method is called twice, the second call
	 * will yield an empty result.
	 *
	 * Note that if the leaderboard has not been configured to reset, the concept of a
	 * tournament does not apply.
	 *
	 * @param leaderboardId The id of the leaderboard
	 * @param replaceName True if the player's name should be replaced with "You"
	 * @param callback The method to be invoked when the server response is received
	 */
	void getCompletedLeaderboardTournament(const FString& leaderboardId, bool replaceName, IServerCallback * callback = nullptr);

	/**
	 * This method triggers a reward (via a player statistics event)
	 * to the currently logged in player for ranking at the
	 * completion of a tournament.
	 *
	 * @param eventName The player statistics event name to trigger
	 * @param eventMultiplier The multiplier to associate with the event
	 * @param callback The method to be invoked when the server response is received
	 */
	void triggerSocialLeaderboardTournamentReward(const FString& leaderboardId, const FString& eventName, uint64 eventMultiplier, IServerCallback * callback = nullptr);

	/**
	 * Method to retrieve the player's completed tournaments for the game.
	 * Arguments:
	 *  leaderboardId: Name of the leaderboard
	 *  replaceName: True to replace the player's name with "You"; false otherwise.
	 *  callback: client-side callback for the results
	 */
	void playerTournamentReward(const FString& eventName, uint64 multiplier, IServerCallback * callback = nullptr);

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
	void getGroupSocialLeaderboard(const FString& leaderboardId, const FString& groupId, IServerCallback * callback = nullptr);

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
	void getPlayersSocialLeaderboard(const FString& leaderboardId, const TArray<FString> profileIds, IServerCallback * callback = nullptr);

private:
	BrainCloudClient* _client = nullptr;

	FString leaderboardTypeToString(ESocialLeaderboardType type);
	FString leaderboardRotationTypeToString(ERotationType type);
	FString leaderboardSortOrderToString(ESortOrder type);
};