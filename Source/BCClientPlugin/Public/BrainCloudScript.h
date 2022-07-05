// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudScript
{
  public:
    BrainCloudScript(BrainCloudClient *client);

    /**
     * Executes a script on the server.
     *
     * Service Name - Script
     * Service Operation - Run
     *
     * @param scriptName The name of the script to be run
     * @param jsonScriptData Data to be sent to the script in json format
     * @param callback The method to be invoked when the server response is received
     * @see The API documentation site for more details on cloud code
     */
    void runScript(const FString &scriptName, const FString &jsonScriptData, IServerCallback *callback = nullptr);

    /**
    * Allows cloud script executions to be scheduled
    *
    * Service Name - Script
    * Service Operation - ScheduleCloudScript
    *
    * @param scriptName The name of the script to be run
    * @param jsonScriptData Data to be sent to the script in json format
    * @param startDateInUTC The start date as a time struct
    * @param callback The method to be invoked when the server response is received
    * @see The API documentation site for more details on cloud code
    */
    void scheduleRunScriptMillisUTC(const FString &scriptName, const FString &jsonScriptData, int64 startDateInUTC, IServerCallback *callback = nullptr);


    /**
    * Allows cloud script executions to be scheduled
    *
    * Service Name - Script
    * Service Operation - ScheduleCloudScript
    *
    * @param scriptName The name of the script to be run
    * @param jsonScriptData Data to be sent to the script in json format
    * @param minutesFromNow Number of minutes from now to run script
    * @param callback The method to be invoked when the server response is received
    * @see The API documentation site for more details on cloud code
    */
    void scheduleRunScriptMinutes(const FString &scriptName, const FString &jsonScriptData, int32 minutesFromNow, IServerCallback *callback = nullptr);

    /**
    * Run a cloud script in a parent app
    *
    * Service Name - Script
    * Service Operation - RUN_PARENT_SCRIPT
    *
    * @param scriptName The name of the script to be run
    * @param scriptData Data to be sent to the script in json format
    * @param parentLevel The level name of the parent to run the script from
    * @param callback The method to be invoked when the server response is received
    * @see The API documentation site for more details on cloud code
    */
    void runParentScript(const FString &scriptName, const FString &jsonScriptData, const FString &parentLevel, IServerCallback *callback = nullptr);

    /**
	* Cancels a scheduled cloud code script
	*
	* Service Name - Script
	* Service Operation - CANCEL_SCHEDULED_SCRIPT
	*
	* @param jobId ID of script job to cancel
	* @param callback The method to be invoked when the server response is received
	*/
    void cancelScheduledScript(const FString &jobId, IServerCallback *callback = nullptr);

    /**
	* Runs a script from the context of a peer
	*
	* Service Name - Script
	* Service Operation - RUN_PEER_SCRIPT
	*
	* @param scriptName The name of the script to be run
	* @param jsonScriptData Data to be sent to the script in json format
	* @param peer Peer the script belongs to
	* @param callback The method to be invoked when the server response is received
	*/
    void runPeerScript(const FString &scriptName, const FString &jsonScriptData, const FString &peer, IServerCallback *callback = nullptr);

    /**
	* Runs a script asynchronously from the context of a peer
	* This method does not wait for the script to complete before returning
	*
	* Service Name - Script
	* Service Operation - RUN_PEER_SCRIPT_ASYNC
	*
	* @param scriptName The name of the script to be run
	* @param jsonScriptData Data to be sent to the script in json format
	* @param peer Peer the script belongs to
	* @param callback The method to be invoked when the server response is received
	*/
    void runPeerScriptAsync(const FString &scriptName, const FString &jsonScriptData, const FString &peer, IServerCallback *callback = nullptr);

  /**
	* Retrieves scripts currently running or queued.
	*
	* Service Name - Script
	* Service Operation - GET_RUNNING_OR_QUEUED_CLOUD_SCRIPTS
	*
	* @param callback The method to be invoked when the server response is received
	*/
    void getRunningOrQueuedCloudScripts(IServerCallback *callback = nullptr);

  /**
	* Retrieves scripts scheduled to run up to and including the specified start time (UTC in ms).
	*
	* Service Name - Script
	* Service Operation - GET_SCHEDULED_CLOUD_SCRIPTS
	* @param startDateUTC 
	* @param callback The method to be invoked when the server response is received
	*/
    void getScheduledCloudScripts(const struct FDateTime startDateInUTC, IServerCallback *callback = nullptr);

  private:
    BrainCloudClient *_client = nullptr;
};