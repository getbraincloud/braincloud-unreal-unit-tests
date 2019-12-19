// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#ifndef _BRAINCLOUDLOBBY_H_
#define _BRAINCLOUDLOBBY_H_

#include "braincloud/BrainCloudTypes.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "json/json.h"

#include <atomic>
#include <condition_variable>
#include <map>
#include <string>
#include <thread>
#include <vector>

namespace BrainCloud
{
	class BrainCloudClient;

	class BrainCloudLobby
	{
	public:
		BrainCloudLobby(BrainCloudClient* in_client);

		/**
		 * Set to true to enable logging ping requests to std::out
		 */
		void enableLogging(bool shouldEnable);

		/* Retrieves the region settings for each of the given lobby types. Upon success or afterwards, call pingRegions to start retrieving appropriate data.
		 *
		 * Service Name - Lobby
		 * Service Operation - GetRegionsForLobbies
		 *
		 * @param roomTypes Ids of the lobby types.
		 */
		void getRegionsForLobbies(const std::vector<std::string> &in_roomTypes, IServerCallback *in_callback = NULL);

		/* Retrieves associated Ping Data averages to be used with all associated <>WithPingData APIs.
		 * Call anytime after GetRegionsForLobbies before proceeding.
		 * Once that completes, the associated region Ping Data is retrievable via getPingData and all associated <>WithPingData APIs are useable
		 */
		void pingRegions(IServerCallback* in_callback);

		/* Returns the Ping Data collected after calling pingRegions
		 */
		const std::map<std::string, int>& getPingData() const;

		/**
		 * Creates a new lobby.
		 * 
		 * Sends LOBBY_JOIN_SUCCESS message to the user, with full copy of lobby data Sends LOBBY_MEMBER_JOINED to all lobby members, with copy of member data
		 *
		 * Service Name - Lobby
		 * Service Operation - CreateLobby
		 *
		 * @param lobbyType The type of lobby to look for. Lobby types are defined in the portal.
		 * @param rating The skill rating to use for finding the lobby. Provided as a separate parameter because it may not exactly match the user's rating (especially in cases where parties are involved).
		 * @param otherUserCxIds Array of other users (i.e. party members) to add to the lobby as well. Will constrain things so that only lobbies with room for all players will be considered.
		 * @param isReady Initial ready-status of this user.
		 * @param extraJson Initial extra-data about this user.
		 * @param teamCode Preferred team for this user, if applicable. Send "" or null for automatic assignment.
		 * @param settings Configuration data for the room.
		 */
		void createLobby(const std::string& in_lobbyType, int in_rating, const std::vector<std::string>& in_otherUserCxIds, bool in_isReady, const std::string& in_extraJson, const std::string& in_teamCode, const std::string& in_jsonSettings, IServerCallback* in_callback = NULL);

		/**
		 * Creates a new lobby. Uses attached ping data to resolve best location. GetRegionsForLobbies and PingRegions must be successfully responded to.
		 * 
		 * Sends LOBBY_JOIN_SUCCESS message to the user, with full copy of lobby data Sends LOBBY_MEMBER_JOINED to all lobby members, with copy of member data
		 *
		 * Service Name - Lobby
		 * Service Operation - CreateLobbyWithPingData
		 *
		 * @param lobbyType The type of lobby to look for. Lobby types are defined in the portal.
		 * @param rating The skill rating to use for finding the lobby. Provided as a separate parameter because it may not exactly match the user's rating (especially in cases where parties are involved).
		 * @param otherUserCxIds Array of other users (i.e. party members) to add to the lobby as well. Will constrain things so that only lobbies with room for all players will be considered.
		 * @param isReady Initial ready-status of this user.
		 * @param extraJson Initial extra-data about this user.
		 * @param teamCode Preferred team for this user, if applicable. Send "" or null for automatic assignment.
		 * @param settings Configuration data for the room.
		 */
		void createLobbyWithPingData(const std::string& in_lobbyType, int in_rating, const std::vector<std::string>& in_otherUserCxIds, bool in_isReady, const std::string& in_extraJson, const std::string& in_teamCode, const std::string& in_jsonSettings, IServerCallback* in_callback = NULL);

		/**
		 * Finds a lobby matching the specified parameters. Asynchronous - returns 200 to indicate that matchmaking has started.
		 *
		 * Service Name - Lobby
		 * Service Operation - FindLobby
		 *
		 * @param lobbyType The type of lobby to look for. Lobby types are defined in the portal.
		 * @param rating The skill rating to use for finding the lobby. Provided as a separate parameter because it may not exactly match the user's rating (especially in cases where parties are involved).
		 * @param maxSteps The maximum number of steps to wait when looking for an applicable lobby. Each step is ~5 seconds.
		 * @param algo The algorithm to use for increasing the search scope.
		 * @param filterJson Used to help filter the list of rooms to consider. Passed to the matchmaking filter, if configured.
		 * @param otherUserCxIds Array of other users (i.e. party members) to add to the lobby as well. Will constrain things so that only lobbies with room for all players will be considered.
		 * @param isReady Initial ready-status of this user.
		 * @param extraJson Initial extra-data about this user.
		 * @param teamCode Preferred team for this user, if applicable. Send "" or null for automatic assignment
		 */
		void findLobby(const std::string& in_lobbyType, int in_rating, int in_maxSteps, const std::string& in_jsonAlgo, const std::string& in_jsonFilter, const std::vector<std::string>& in_otherUserCxIds, bool in_isReady, const std::string& in_extraJson, const std::string& in_teamCode, IServerCallback* in_callback = NULL);

		/**
		 * Finds a lobby matching the specified parameters. Asynchronous - returns 200 to indicate that matchmaking has started. Uses attached ping data to resolve best location. GetRegionsForLobbies and PingRegions must be successfully responded to.
		 *
		 * Service Name - Lobby
		 * Service Operation - FindLobbyWithPingData
		 *
		 * @param lobbyType The type of lobby to look for. Lobby types are defined in the portal.
		 * @param rating The skill rating to use for finding the lobby. Provided as a separate parameter because it may not exactly match the user's rating (especially in cases where parties are involved).
		 * @param maxSteps The maximum number of steps to wait when looking for an applicable lobby. Each step is ~5 seconds.
		 * @param algo The algorithm to use for increasing the search scope.
		 * @param filterJson Used to help filter the list of rooms to consider. Passed to the matchmaking filter, if configured.
		 * @param otherUserCxIds Array of other users (i.e. party members) to add to the lobby as well. Will constrain things so that only lobbies with room for all players will be considered.
		 * @param isReady Initial ready-status of this user.
		 * @param extraJson Initial extra-data about this user.
		 * @param teamCode Preferred team for this user, if applicable. Send "" or null for automatic assignment
		 */
		void findLobbyWithPingData(const std::string& in_lobbyType, int in_rating, int in_maxSteps, const std::string& in_jsonAlgo, const std::string& in_jsonFilter, const std::vector<std::string>& in_otherUserCxIds, bool in_isReady, const std::string& in_extraJson, const std::string& in_teamCode, IServerCallback* in_callback = NULL);

		/**
		 * Adds the caller to the lobby entry queue and will create a lobby if none are found.
		 *
		 * Service Name - Lobby
		 * Service Operation - FindOrCreateLobby
		 *
		 * @param lobbyType The type of lobby to look for. Lobby types are defined in the portal.
		 * @param rating The skill rating to use for finding the lobby. Provided as a separate parameter because it may not exactly match the user's rating (especially in cases where parties are involved).
		 * @param maxSteps The maximum number of steps to wait when looking for an applicable lobby. Each step is ~5 seconds.
		 * @param algo The algorithm to use for increasing the search scope.
		 * @param filterJson Used to help filter the list of rooms to consider. Passed to the matchmaking filter, if configured.
		 * @param otherUserCxIds Array of other users (i.e. party members) to add to the lobby as well. Will constrain things so that only lobbies with room for all players will be considered.
		 * @param settings Configuration data for the room.
		 * @param isReady Initial ready-status of this user.
		 * @param extraJson Initial extra-data about this user.
		 * @param teamCode Preferred team for this user, if applicable. Send "" or null for automatic assignment.
		 */
		void findOrCreateLobby(const std::string& in_lobbyType, int in_rating, int in_maxSteps, const std::string& in_jsonAlgo, const std::string& in_jsonFilter, const std::vector<std::string>& in_otherUserCxIds, const std::string& in_jsonSettings, bool in_isReady, const std::string& in_extraJson, const std::string& in_teamCode, IServerCallback* in_callback = NULL);

		/**
		 * Adds the caller to the lobby entry queue and will create a lobby if none are found. Uses attached ping data to resolve best location. GetRegionsForLobbies and PingRegions must be successfully responded to.
		 *
		 * Service Name - Lobby
		 * Service Operation - FindOrCreateLobbyWithPingData
		 *
		 * @param lobbyType The type of lobby to look for. Lobby types are defined in the portal.
		 * @param rating The skill rating to use for finding the lobby. Provided as a separate parameter because it may not exactly match the user's rating (especially in cases where parties are involved).
		 * @param maxSteps The maximum number of steps to wait when looking for an applicable lobby. Each step is ~5 seconds.
		 * @param algo The algorithm to use for increasing the search scope.
		 * @param filterJson Used to help filter the list of rooms to consider. Passed to the matchmaking filter, if configured.
		 * @param otherUserCxIds Array of other users (i.e. party members) to add to the lobby as well. Will constrain things so that only lobbies with room for all players will be considered.
		 * @param settings Configuration data for the room.
		 * @param isReady Initial ready-status of this user.
		 * @param extraJson Initial extra-data about this user.
		 * @param teamCode Preferred team for this user, if applicable. Send "" or null for automatic assignment.
		 */
		void findOrCreateLobbyWithPingData(const std::string& in_lobbyType, int in_rating, int in_maxSteps, const std::string& in_jsonAlgo, const std::string& in_jsonFilter, const std::vector<std::string>& in_otherUserCxIds, const std::string& in_jsonSettings, bool in_isReady, const std::string& in_extraJson, const std::string& in_teamCode, IServerCallback* in_callback = NULL);

		/**
		 * Returns the data for the specified lobby, including member data.
		 *
		 * Service Name - Lobby
		 * Service Operation - GetLobbyData
		 *
		 * @param lobbyId Id of chosen lobby.
		 */
		void getLobbyData(const std::string& in_lobbyId, IServerCallback* in_callback = NULL);

		/**
		 * Causes the caller to leave the specified lobby. If the user was the owner, a new owner will be chosen. If user was the last member, the lobby will be deleted.
		 *
		 * Service Name - Lobby
		 * Service Operation - LeaveLobby
		 *
		 * @param lobbyId Id of chosen lobby.
		 */
		void leaveLobby(const std::string& in_lobbyId, IServerCallback* in_callback = NULL);

		/**
		 * Evicts the specified user from the specified lobby. The caller must be the owner of the lobby.
		 *
		 * Service Name - Lobby
		 * Service Operation - RemoveMember
		 *
		 * @param lobbyId Id of chosen lobby.
		 * @param cxId Specified member to be removed from the lobby.
		 */
		void removeMember(const std::string& in_lobbyId, const std::string& in_cxId, IServerCallback* in_callback = NULL);

		/**
		 * Sends LOBBY_SIGNAL_DATA message to all lobby members.
		 *
		 * Service Name - Lobby
		 * Service Operation - SendSignal
		 *
		 * @param lobbyId Id of chosen lobby.
		 * @param signalData Signal data to be sent.
		 */
		void sendSignal(const std::string& in_lobbyId, const std::string& in_jsonSignalData, IServerCallback* in_callback = NULL);

		/**
		 * Switches to the specified team (if allowed.)
		 * 
		 * Sends LOBBY_MEMBER_UPDATED to all lobby members, with copy of member data
		 *
		 * Service Name - Lobby
		 * Service Operation - SwitchTeam
		 *
		 * @param lobbyId Id of chosen lobby.
		 * @param toTeamCode Specified team code.
		 */
		void switchTeam(const std::string& in_lobbyId, const std::string& in_toTeamCode, IServerCallback* in_callback = NULL);

		/**
		 * Updates the ready status and extra json for the given lobby member.
		 *
		 * Service Name - Lobby
		 * Service Operation - UpdateReady
		 *
		 * @param lobbyId The type of lobby to look for. Lobby types are defined in the portal.
		 * @param isReady Initial ready-status of this user.
		 * @param extraJson Initial extra-data about this user.
		 */
		void updateReady(const std::string& in_lobbyId, bool in_isReady, const std::string& in_extraJson, IServerCallback* in_callback = NULL);

		/**
		 * Updates the ready status and extra json for the given lobby member.
		 *
		 * Service Name - Lobby
		 * Service Operation - UpdateSettings
		 *
		 * @param lobbyId Id of the specfified lobby.
		 * @param settings Configuration data for the room.
		 */
		void updateSettings(const std::string& in_lobbyId, const std::string& in_jsonSettings, IServerCallback* in_callback = NULL);
				
		/**
		 * Join specified lobby
		 *
		 * Service Name - Lobby
		 * Service Operation - JoinLobby
		 *
		 * @param lobbyId Id of the specfified lobby.
		 * @param isReady Initial ready-status of this user.
		 * @param extraJson Initial extra-data about this user.
		 * @param toTeamCode Specified team code.
		 * @param otherUserCxIds Array of other users (i.e. party members) to add to the lobby as well. Will constrain things so that only lobbies with room for all players will be considered.

		 */
		void joinLobby(const std::string in_lobbyId, bool in_isReady, const std::string& in_extraJson, std::string in_teamCode, const std::vector<std::string>& in_otherUserCxIds, IServerCallback* in_callback);
				
		/**
		 * Join specified lobby. Uses attached ping data to resolve best location. GetRegionsForLobbies and PingRegions must be successfully responded to.
		 *
		 * Service Name - Lobby
		 * Service Operation - JoinLobbyWithPingData
		 *
		 * @param lobbyId Id of the specfified lobby.
		 * @param isReady Initial ready-status of this user.
		 * @param extraJson Initial extra-data about this user.
		 * @param toTeamCode Specified team code.
		 * @param otherUserCxIds Array of other users (i.e. party members) to add to the lobby as well. Will constrain things so that only lobbies with room for all players will be considered.

		 */
		void joinLobbyWithPingData(const std::string in_lobbyId, bool in_isReady, const std::string& in_extraJson, std::string in_teamCode, const std::vector<std::string>& in_otherUserCxIds, IServerCallback* in_callback);

		/// <summary>
		/// Cancel this members Find, Join and Searching of Lobbies
		/// </summary>
		void cancelFindRequest(const std::string& in_lobbyType, const std::string& in_cxId, IServerCallback* in_callback);

		/* Runs ping callbacks if pingRegions was called.
		 * Note: This is already called by BrainCloudClient::runCallbacks
		 */
		void runPingCallbacks();

	private:
		class GetRegionsForLobbiesCallback final : public IServerCallback
		{
		public:
			GetRegionsForLobbiesCallback(BrainCloudLobby* pBrainCloudLobby);
			void setExternalCallback(IServerCallback* in_callback);

		private:
			void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, std::string const& jsonData) override;
			void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int statusCode, int reasonCode, const std::string& jsonError) override;
			void serverWarning(ServiceName serviceName, ServiceOperation serviceOperation, int statusCode, int reasonCode, int numRetries, const std::string& statusMessage) override;

			BrainCloudLobby* m_pBrainCloudLobby;
			IServerCallback* m_pExternalCallback;
		};

		class PingRegionsThread final
		{
		public:
			PingRegionsThread(BrainCloudLobby* pBrainCloudLobby);
			~PingRegionsThread();

			bool isRunning() const;
			void stop();
			void start(const std::map<std::string, std::string>& pingRegions);

		private:
			std::atomic<bool> m_isRunning;
			BrainCloudLobby* m_pBrainCloudLobby;
			std::thread m_thread;
			std::mutex m_mutex;
			std::condition_variable m_condition;
		};

		struct ErrorCallbackEvent
		{
			IServerCallback* callback;
			ServiceName serviceName;
			ServiceOperation serviceOperation;
			int statusCode;
			int reasonCode;
			std::string jsonError;
		};

		friend class GetRegionsForLobbiesCallback;
		friend class PingRegionsThread;

		void attachPingDataAndSend(ServiceName serviceName, ServiceOperation serviceOperation, Json::Value& data, IServerCallback* callback);

		std::atomic<bool> _loggingEnabled;
		BrainCloudClient* m_client;
		GetRegionsForLobbiesCallback m_getRegionsForLobbiesCallback;
		PingRegionsThread m_pingRegionsThread;
		std::map<std::string, int> m_pingData;
		std::map<std::string, std::string> m_pingRegions;
		IServerCallback* m_pingCallback;
		std::vector<ErrorCallbackEvent> m_errorCallbackQueue;
	};
};

#endif /* _BRAINCLOUDLOBBY_H_ */
