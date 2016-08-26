// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudPlayerStatistics
{
public:
	BrainCloudPlayerStatistics(BrainCloudClient* client);

	/**
	 * Read all available player statistics.
	 *
	 * Service Name - PlayerStatistics
	 * Service Operation - Read
	 *
	 * @param callback The method to be invoked when the server response is received
	 */
	void readAllPlayerStats(IServerCallback* callback = nullptr);

	/**
	 * Reads a subset of player statistics.
	 *
	 * Service Name - PlayerStatistics
	 * Service Operation - ReadSubset
	 *
	 * @param playerStats The array containing the subset of statistics to read.
	 * @param callback The method to be invoked when the server response is received
	 */
	void readPlayerStatsSubset(const TArray<FString>& playerStats, IServerCallback* callback = nullptr);

	/**
	 * Reset all of the statistics for this player back to their initial value.
	 *
	 * Service Name - PlayerStatistics
	 * Service Operation - Reset
	 *
	 * @param callback The method to be invoked when the server response is received
	 */
	void resetAllPlayerStats(IServerCallback* callback = nullptr);

	/**
	* Method retrieves the player statistics for the given category.
	*
	* Service Name - PlayerStatistics
	* Service Operation - ReadPlayerStatisticsByCategory
	*
	* @param category The player statistics category
	* @param callback Method to be invoked when the server response is received.
	*/
	void readPlayerStatisticsByCategory(const FString& category, IServerCallback * callback = nullptr);

	/**
	 * Atomically increment (or decrement) player statistics.
	 * Any rewards that are triggered from player statistic increments
	 * will be considered. Player statistics are defined through the brainCloud portal.
	 * Note also that the "xpCapped" property is returned (true/false depending on whether
	 * the xp cap is turned on and whether the player has hit it).
	 *
	 * Service Name - PlayerStatistics
	 * Service Operation - Update
	 *
	 * @param jsonData The JSON encoded data to be sent to the server as follows:
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
	 *
	 * @param callback The method to be invoked when the server response is received
	 */
	void incrementPlayerStats(const FString& jsonData, IServerCallback* callback = nullptr);

	/**
	 * Returns JSON representing the next experience level for the player.
	 *
	 * Service Name - PlayerStatistics
	 * Service Operation - ReadNextXpLevel
	 *
	 * @param callback The method to be invoked when the server response is received
	 */
	void getNextExperienceLevel(IServerCallback* callback = nullptr);

	/**
	 * Increments the player's experience. If the player goes up a level,
	 * the new level details will be returned along with a list of rewards.
	 *
	 * Service Name - PlayerStatistics
	 * Service Operation - UpdateIncrement
	 *
	 * @param xpValue The amount to increase the player's experience by
	 * @param callback The method to be invoked when the server response is received
	 */
	void incrementExperiencePoints(int32 xpValue, IServerCallback* callback = nullptr);

	/**
	 * Sets the player's experience to an absolute value. Note that this
	 * is simply a set and will not reward the player if their level changes
	 * as a result.
	 *
	 * Service Name - PlayerStatistics
	 * Service Operation - SetXpPoints
	 *
	 * @param xpValue The amount to set the the player's experience to
	 * @param callback The method to be invoked when the server response is received
	 */
	void setExperiencePoints(int32 xpValue, IServerCallback* callback = nullptr);

	/**
	* Apply statistics grammar to a partial set of statistics.
	*
	* Service Name - PlayerStatistics
	* Service Operation - PROCESS_STATISTICS
	*
	* @param jsonData The JSON format is as follows:
	* {
	*     "DEAD_CATS": "RESET",
	*     "LIVES_LEFT": "SET#9",
	*     "MICE_KILLED": "INC#2",
	*     "DOG_SCARE_BONUS_POINTS": "INC#10",
	*     "TREES_CLIMBED": 1
	* }
	* @param callback Method to be invoked when the server response is received.
	*/
	void processStatistics(const FString& jsonData, IServerCallback* callback = nullptr);

private:
	BrainCloudClient* _client = nullptr;
};
