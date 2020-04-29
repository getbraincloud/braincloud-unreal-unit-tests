// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <string>

#include "braincloud/IServerCallback.h"

namespace BrainCloud
{
	class IServerCallback;
	class BrainCloudClient;

	class BrainCloudScript
	{
	public:
		BrainCloudScript(BrainCloudClient* in_client);

		/**
		 * Executes a script on the server.
		 *
		 * Service Name - Script
		 * Service Operation - Run
		 *
		 * @param in_scriptName The name of the script to be run
		 * @param in_jsonScriptData Data to be sent to the script in json format
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void runScript(const char * in_scriptName, const std::string & in_jsonScriptData, IServerCallback * in_callback = NULL);

		/**
		 * Allows cloud script executions to be scheduled - CONVERTS time to LOCAL
		 *
		 * Service Name - Script
		 * Service Operation - ScheduleCloudScript
		 *
		 * @param in_scriptName The name of the script to be run
		 * @param in_jsonScriptData Data to be sent to the script in json format
		 * @param in_startDateInLocal The start date, time is converted to LOCAL
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void scheduleRunScriptUTC(const char * in_scriptName, const char * in_jsonScriptData, const struct tm* in_startDateInLocal, IServerCallback * in_callback = NULL);

		/**
		 * Allows cloud script executions to be scheduled - UTC time
		 *
		 * Service Name - Script
		 * Service Operation - ScheduleCloudScript
		 *
		 * @param in_scriptName The name of the script to be run
		 * @param in_jsonScriptData Data to be sent to the script in json format
		 * @param in_startDateInUTC The start date in UTC
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void scheduleRunScriptMillisUTC(const char * in_scriptName, const char * in_jsonScriptData, int64_t in_startDateInUTC, IServerCallback * in_callback = NULL);

		/**
		 * Allows cloud script executions to be scheduled
		 *
		 * Service Name - Script
		 * Service Operation - ScheduleCloudScript
		 *
		 * @param in_scriptName The name of the script to be run
		 * @param in_jsonScriptData Data to be sent to the script in json format
		 * @param in_minutesFromNow Number of minutes from now to run script
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void scheduleRunScriptMinutes(const char * in_scriptName, const char * in_jsonScriptData, int in_minutesFromNow, IServerCallback * in_callback = NULL);

		/**
		 * Run a cloud script in a parent app
		 *
		 * Service Name - Script
		 * Service Operation - RUN_PARENT_SCRIPT
		 *
		 * @param in_scriptName The name of the script to be run
		 * @param in_scriptData Data to be sent to the script in json format
		 * @param in_parentLevel The level name of the parent to run the script from
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void runParentScript(const char * in_scriptName, const char * in_jsonScriptData, const char * in_parentLevel, IServerCallback * in_callback = NULL);

		/**
		* Cancels a scheduled cloud code script
		*
		* Service Name - Script
		* Service Operation - CANCEL_SCHEDULED_SCRIPT
		*
		* @param in_jobId ID of script job to cancel
		* @param in_callback The method to be invoked when the server response is received
		*/
		void cancelScheduledScript(const char * in_jobId, IServerCallback * in_callback = NULL);

		/**
		* Cancels a scheduled cloud code script
		*
		* Service Name - Script
		* Service Operation - CANCEL_SCHEDULED_SCRIPT
		*
		* @param in_callback The method to be invoked when the server response is received
		*/
		void getRunningOrQueuedCloudScripts(IServerCallback * in_callback = NULL);

		/**
		* Cancels a scheduled cloud code script
		*
		* Service Name - Script
		* Service Operation - CANCEL_SCHEDULED_SCRIPT
		*
		* @param in_jobId ID of script job to cancel
		* @param in_callback The method to be invoked when the server response is received
		*/
		void getScheduledCloudScripts(const struct tm* in_startDateInUTC, IServerCallback * in_callback = NULL);

		/**
		* Runs a script from the context of a peer
		*
		* Service Name - Script
		* Service Operation - RUN_PEER_SCRIPT
		*
		* @param in_scriptName The name of the script to be run
		* @param in_jsonScriptData Data to be sent to the script in json format
		* @param in_callback The method to be invoked when the server response is received
		*/
		void runPeerScript(const char * in_scriptName, const std::string & in_jsonScriptData, const char * in_peer, IServerCallback * in_callback = NULL);

		/**
		* Runs a script asynchronously from the context of a peer
		* This method does not wait for the script to complete before returning
		*
		* Service Name - Script
		* Service Operation - RUN_PEER_SCRIPT_ASYNC
		*
		* @param in_scriptName The name of the script to be run
		* @param in_jsonScriptData Data to be sent to the script in json format
		* @param in_callback The method to be invoked when the server response is received
		*/
		void runPeerScriptAsync(const char * in_scriptName, const std::string & in_jsonScriptData, const char * in_peer, IServerCallback * in_callback = NULL);

	private:
		BrainCloudClient * m_client;
	};
}