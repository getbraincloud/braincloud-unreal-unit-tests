// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudGlobalStatistics
{
  public:
	BrainCloudGlobalStatistics(BrainCloudClient *client);

	/**
	 * Method returns all of the global statistics.
	 *
	 * Service Name - GlobalStatistics
	 * Service Operation - Read
	 *
	 * @param callback Method to be invoked when the server response is received.
	 */
	void readAllGlobalStats(IServerCallback *callback = nullptr);

	/**
	 * Reads a subset of global statistics.
	 *
	 * Service Name - GlobalStatistics
	 * Service Operation - ReadSubset
	 *
	 * @param globalStats An array of statistics to read.
	 * @param callback Method to be invoked when the server response is received.
	 */
	void readGlobalStatsSubset(const TArray<FString> &globalStats, IServerCallback *callback = nullptr);

	/**
	* Method retrieves the game (aka global) statistics for the given category.
	*
	* Service Name - GlobalStatistics
	* Service Operation - ReadGameStatisticsByCategory
	*
	* @param category The game statistics category
	* @param callback Method to be invoked when the server response is received.
	*/
	void readGlobalStatsForCategory(const FString &category, IServerCallback *callback = nullptr);

	/**
	 * Atomically increment (or decrement) global statistics.
	 * Global statistics are defined through the brainCloud portal.
	 *
	 * Service Name - GlobalStatistics
	 * Service Operation - UpdateIncrement
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
	 * @param callback Method to be invoked when the server response is received.
	 */
	void incrementGlobalGameStat(const FString &jsonData, IServerCallback *callback = nullptr);

	/**
	* Apply statistics grammar to a partial set of statistics.
	*
	* Service Name - GlobalStatistics
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
	void processStatistics(const FString &jsonData, IServerCallback *callback = nullptr);

  private:
	BrainCloudClient *_client = nullptr;
};
