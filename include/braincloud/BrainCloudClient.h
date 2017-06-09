//  BrainCloudClient.h
//  BrainCloudLib
//  Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#ifdef WIN32
#include <WinSock2.h>
#include <windows.h>
#endif

#include <string>
#include "braincloud/IEventCallback.h"
#include "braincloud/IFileUploadCallback.h"
#include "braincloud/IGlobalErrorCallback.h"
#include "braincloud/INetworkErrorCallback.h"
#include "braincloud/IRewardCallback.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/reason_codes.h"
#include "braincloud/http_codes.h"

#include "braincloud/internal/IBrainCloudComms.h"
#include "braincloud/BrainCloudTypes.h"
#include "braincloud/BrainCloudPlayerStatistics.h"
#include "braincloud/BrainCloudGlobalStatistics.h"
#include "braincloud/BrainCloudIdentity.h"
#include "braincloud/BrainCloudProduct.h"
#include "braincloud/BrainCloudEntity.h"
#include "braincloud/BrainCloudGlobalEntity.h"
#include "braincloud/BrainCloudMatchmaking.h"
#include "braincloud/BrainCloudOneWayMatch.h"
#include "braincloud/BrainCloudPlaybackStream.h"
#include "braincloud/BrainCloudAsyncMatch.h"
#include "braincloud/BrainCloudScript.h"
#include "braincloud/BrainCloudPlayerState.h"
#include "braincloud/BrainCloudFriend.h"
#include "braincloud/BrainCloudEvent.h"
#include "braincloud/BrainCloudSocialLeaderboard.h"
#include "braincloud/BrainCloudGamification.h"
#include "braincloud/BrainCloudTime.h"
#include "braincloud/BrainCloudTournament.h"
#include "braincloud/BrainCloudAuthentication.h"
#include "braincloud/BrainCloudPushNotification.h"
#include "braincloud/BrainCloudPlayerStatisticsEvent.h"
#include "braincloud/BrainCloudSteam.h"
#include "braincloud/BrainCloudGlobalApp.h"
#include "braincloud/BrainCloudS3Handling.h"
#include "braincloud/BrainCloudRedemptionCode.h"
#include "braincloud/BrainCloudDataStream.h"
#include "braincloud/BrainCloudProfanity.h"
#include "braincloud/BrainCloudFile.h"
#include "braincloud/BrainCloudGroup.h"
#include "braincloud/BrainCloudMail.h"

namespace Json {
	class Value;
}

namespace BrainCloud
{
	/**
	 * This class is responsible for accumulating client requests, bundling
	 * them together and sending them off to the server...
	 *
	 * This class uses the ServerCall class to communicate with the server.
	 * Retrieve all outstanding calls, send them to the server, and callback
	 * any registered callbacks.
	 *
	 * The BrainCloudClient will have only one HTTP connection to a game server at a
	 * time (to make sure that data doesn't arrive out of order, and to make
	 * recovery of communication problems more simple).
	 */
	class BrainCloudClient
	{
	public:
		/**
		 * Destructor
		 */
		virtual ~BrainCloudClient() { };

		/**
		 * BrainCloudClient is a singleton object. This method gives the caller access
		 * to the singleton object in order to use the class.
		 *
		 * @return BrainCloudClient * - pointer to the singleton BrainCloudClient object
		 */
		static BrainCloudClient * getInstance();
		
		/**
		 * Method initializes the BrainCloudClient.
		 *
		 * @param in_serverURL The url to the brainCloud server
		 *     Currently this should be:  https://sharedprod.braincloudservers.com/dispatcherv2
		 * @param in_secretKey The secret key for your game
		 * @param in_appId The app id
		 * @param in_appVersion The version
		 */
		void initialize(const char * in_serverURL, const char * in_secretKey, const char * in_appId, const char * in_appVersion);

		/**
		* Initialize - initializes the identity service with the saved
		* anonymous installation id and most recently used profile id
		*
		* @param in_profileId The id of the profile id that was most recently used by the app (on this device)
		* @param in_anonymousId  The anonymous installation id that was generated for this device
		*/
		void initializeIdentity(const char * in_profileId, const char * in_anonymousId);

		/**
		 * Return a reference to the game client manager.
		 * Not meant to be called by external clients, just for internal testing and use.
		 */
		IBrainCloudComms * getBrainCloudComms() const { return _brainCloudComms; }

		/**
		 * Run callbacks, to be called once per frame from your main thread
		 */
		void runCallbacks();

		/**
  		 * The brainCloud client considers itself reauthenticated
  		 * with the given session
  		 *
  		 * Warning: ensure the user is within your session expiry (set on the dashboard)
  		 * before using this call. This optional method exists to reduce
  		 * authentication calls, in event the user needs to restart the app
  		 * in rapid succession.
  		 *
  		 * @param in_sessionId A recently returned session Id
  		 */
		void restoreRecentSession(const char * in_sessionId);

		/**
		 * Sets a callback handler for any out of band event messages that come from
		 * brainCloud.
		 *
		 * @param in_eventCallback A function which takes a json string as it's only parameter.
		 * The json format looks like the following:
		 * {
		 *   "events": [{
		 *      "fromPlayerId": "178ed06a-d575-4591-8970-e23a5d35f9df",
		 *      "eventId": 3967,
		 *      "createdAt": 1441742105908,
		 *      "gameId": "123",
		 *      "toPlayerId": "178ed06a-d575-4591-8970-e23a5d35f9df",
		 *      "eventType": "test",
		 *      "eventData": {"testData": 117}
		 *    }],
		 *    ]
		 *  }
		 */
		void registerEventCallback(IEventCallback *in_eventCallback);

		/**
		 * Deregisters the event callback
		 */
		void deregisterEventCallback();

		/**
		 * Sets a reward handler for any api call results that return rewards.
		 *
		 * @param in_rewardCallback The reward callback handler.
		 * @see The brainCloud apidocs site for more information on the return JSON
		 */
		void registerRewardCallback(IRewardCallback * in_rewardCallback);

		/**
		 * Deregisters the reward callback
		 */
		void deregisterRewardCallback();

		/**
		 * Registers a file upload callback handler to listen for status updates on uploads
		 *
		 * @param in_fileUploadCallback The file upload callback handler.
		 */
		void registerFileUploadCallback(IFileUploadCallback * in_fileUploadCallback);

		/**
		 * Deregisters the file upload callback
		 */
		void deregisterFileUploadCallback();

		/**
		 * Registers a callback that is invoked for all errors generated
		 *
		 * @param in_globalErrorCallback The global error callback handler.
		 */
		void registerGlobalErrorCallback(IGlobalErrorCallback * in_globalErrorCallback);

		/**
		 * Deregisters the global error callback
		 */
		void deregisterGlobalErrorCallback();

		/**
		 * Registers a callback that is invoked for network errors.
		 * Note this is only called if enableNetworkErrorMessageCaching
		 * has been set to true.
		 *
		 * @param in_networkErrorCallback The network error callback handler.
		 */
		void registerNetworkErrorCallback(INetworkErrorCallback * in_networkErrorCallback);

		/**
		 * Deregisters the network error callback
		 */
		void deregisterNetworkErrorCallback();

		/**
		 * Set to true to enable logging packets to std::out
		 */
		void enableLogging(bool shouldEnable);

		/**
		 * Send an empty message to the server, which essentially polls the
		 * server for any new events to send to this client.
		 */
		void heartbeat();

		/**
		 * Sends a service request message to the server. This will most likely be placed
		 * in a queue...
		 *
		 * @param in_serviceMessage
		 */
		void sendRequest(ServerCall * in_serviceMessage);

		/**
		 * Clears any pending messages from communication library.
		 */
		void resetCommunication();

		/**
		 * Shuts the brainCloud client down.
		 */
		void shutdown();

		/**
		 * Returns whether the client is authenticated with the brainCloud server.
		 * @return True if authenticated, false otherwise.
		 */
		bool isAuthenticated();

		/**
		 * Returns whether the client is initialized.
		 * @return True if initialized, false otherwise.
		 */
		bool isInitialized();

		/**
		 * If true, tells the comms library to immediately retry a packet
		 * when an error is received.
		 *
		 * If false, comms will wait until the retry timeout is hit before
		 * resending a packet. Although slower, this allows a bit of time
		 * before discarding the packet in case the user is on a lossy
		 * wifi etc network.
		 *
		 * Defaults to false
		 */
		void setImmediateRetryOnError(bool value);


		// ---------------------------------------------------------------------
		//  Getter methods
		// ---------------------------------------------------------------------

		/**
		 * Returns the sessionId or empty string if no session present.
		 *
		 * @returns The sessionId or empty string if no session present.
		 */
		const char * getSessionId() const;

		/* Service getter methods */
		BrainCloudPlayerStatistics * getPlayerStatisticsService() { return _playerStatisticsService; }
		BrainCloudGlobalStatistics * getGlobalStatisticsService() { return _globalStatisticsService; }
		BrainCloudIdentity * getIdentityService() { return _identityService; }
		BrainCloudProduct * getProductService() { return _productService; }
		BrainCloudEntity * getEntityService() { return _entityService; }
		BrainCloudGlobalEntity * getGlobalEntityService() { return _globalEntityService; }
		BrainCloudMatchmaking * getMatchmakingService() { return _matchmakingService; }
		BrainCloudOneWayMatch * getOneWayMatchService() { return _oneWayMatchService; }
		BrainCloudPlaybackStream * getPlaybackStreamService() { return _playbackStreamService; }
		BrainCloudAsyncMatch * getAsyncMatchService() { return _asyncMatchService; }
		BrainCloudScript * getScriptService() { return _scriptService; }
		BrainCloudPlayerState * getPlayerStateService() { return _playerStateService; }
		BrainCloudFriend * getFriendService() { return _friendService; }
		BrainCloudEvent * getEventService() { return _eventService; }
		BrainCloudSocialLeaderboard * getSocialLeaderboardService() { return _socialLeaderboardService; }
		BrainCloudGamification * getGamificationService() { return _gamificationService; }
		BrainCloudTime * getTimeService() { return _timeService; }
		BrainCloudTournament * getTournamentService() { return _tournamentService; }
		BrainCloudAuthentication * getAuthenticationService() { return _authenticationService; }
		BrainCloudPushNotification * getPushNotificationService() { return _pushNotificationService; }
		BrainCloudPlayerStatisticsEvent * getPlayerStatisticsEventService() { return _playerStatisticsEventService; }
		BrainCloudSteam * getSteamService() { return _steamService; }
		BrainCloudGlobalApp * getGlobalAppService() { return _globalAppService; }
		BrainCloudS3Handling * getS3HandlingService() { return _s3HandlingService; }
		BrainCloudRedemptionCode * getRedemptionCodeService() { return _redemptionCodeService; }
		BrainCloudDataStream * getDataStreamService() { return _dataStreamService; }
		BrainCloudProfanity * getProfanityService() { return _profanityService; }
		BrainCloudFile * getFileService() { return _fileService; }
		BrainCloudGroup * getGroupService() { return _groupService; }
		BrainCloudMail * getMailService() { return _mailService; }

		/**
		* @deprecated Use getAppId() instead - Removal after September 1 2017
		*/
		DEPRECATED
		const std::string & getGameId() const
		{
			if (_brainCloudComms != NULL) {
				return _brainCloudComms->getAppId();
			}
			static std::string noAppId;
			return noAppId;
		}

		const std::string & getAppId() const
		{
			if (_brainCloudComms != NULL) {
				return _brainCloudComms->getAppId();
			}
			static std::string noAppId;
			return noAppId;
		}

		const std::string & getReleasePlatform() const { return _releasePlatform; };

		/**
		* @deprecated Use getAppVersion() instead - Removal after September 1 2017
		*/
		DEPRECATED
		const std::string & getGameVersion() const { return _appVersion; }

		const std::string & getAppVersion() const { return _appVersion; };
		

		const std::string & getBrainCloudClientVersion() const { return s_brainCloudClientVersion; };

		const std::string& getCountryCode() const { return _countryCode; }
		const std::string& getLanguageCode() const { return _languageCode; }
		float getTimezoneOffset() { return _timezoneOffset; }

#ifdef __ANDROID__
		// we provide setters for Android as these values need to come from
		// the java side
		void setCountryCode(const char * countryCode) { _countryCode = countryCode; }
		void setLanguageCode(const char * languageCode) { _languageCode = languageCode; }
		void setTimezoneOffset(float timezoneOffset) { _timezoneOffset = timezoneOffset; }
#endif

		// ---------------------------------------------------------------------
		//  Setter methods
		// ---------------------------------------------------------------------

		/**
		* THIH METHOD IS FOR DEBUGGING USE ONLY
		* Hearbeat interval is automatically set based on the session timeout setting
		* in the brainCloud portal.
		*
		* @param intervalInMilliseconds The time between heartbeats in milliseconds
		*/
		void setHeartbeatInterval(int in_intervalInMilliseconds);

		/**
		 * Returns the list of packet timeouts.
		 */
		const std::vector<int> & getPacketTimeouts();

		/**
		 * Sets the packet timeouts using a list of integers that
		 * represent timeout values in seconds for each packet retry. The
		 * first item in the list represents the timeout for the first packet
		 * attempt, the second for the second packet attempt, and so on.
		 *
		 * The number of entries in this array determines how many packet
		 * retries will occur.
		 *
		 * By default, the packet timeout array is {10, 10, 10}.
		 *
		 * Note that this method does not change the timeout for authentication
		 * packets (use setAuthenticationPacketTimeout method).
		 *
		 * @param in_timeouts A vector of packet timeouts.
		 */
		void setPacketTimeouts(const std::vector<int> & in_packetTimeouts);

		/**
		 * Sets the packet timeouts back to the default ie {10, 10, 10}
		 */
		void setPacketTimeoutsToDefault();

		/**
		 * Gets the authentication packet timeout which is tracked separately
		 * from all other packets. Note that authentication packets are never
		 * retried and so this value represents the total time a client would
		 * wait to receive a reply to an authentication api call. By default
		 * this timeout is set to 15 seconds.
		 *
		 * @return The timeout in seconds
		 */
		int getAuthenticationPacketTimeout();

		/**
		 * Sets the authentication packet timeout which is tracked separately
		 * from all other packets. Note that authentication packets are never
		 * retried and so this value represents the total time a client would
		 * wait to receive a reply to an authentication api call. By default
		 * this timeout is set to 15 seconds.
		 *
		 * @param in_timeoutSecs The timeout in seconds
		 */
		void setAuthenticationPacketTimeout(int in_timeoutSecs);

		/**
		 * Sets the error callback to return the status message instead of the
		 * error json string. This flag is used to conform to pre-2.17 client
		 * behaviour.
		 *
		 * @param in_enabled If set to true, enable
		 */
		void setOldStyleStatusMessageErrorCallback(bool in_enabled);

		/**
		* Sets whether the error callback is triggered when a 202 status
		* is received from the server. By default this is true and should
		* only be set to false for backward compatibility.
		*
		* @param in_isError If set to true, 202 is treated as an error
		*/
		void setErrorCallbackOn202Status(bool in_isError);

		/**
		 * Returns the low transfer rate timeout in secs
		 *
		 * @returns The low transfer rate timeout in secs
		 */
		int getUploadLowTransferRateTimeout();

		/**
		 * Sets the timeout in seconds of a low speed upload
		 * (ie transfer rate which is underneath the low transfer rate threshold).
		 * By default this is set to 120 secs. Setting this value to 0 will
		 * turn off the timeout.
		 *
		 * @param in_timeoutSecs The timeout in secs
		 */
		void setUploadLowTransferRateTimeout(int in_timeoutSecs);

		/**
		 * Returns the low transfer rate threshold in bytes/sec
		 *
		 * @returns The low transfer rate threshold in bytes/sec
		 */
		int getUploadLowTransferRateThreshold();

		/**
		 * Sets the low transfer rate threshold of an upload in bytes/sec.
		 * If the transfer rate dips below the given threshold longer
		 * than the specified timeout, the transfer will fail.
		 * By default this is set to 50 bytes/sec. Note that this setting
		 * only works on platforms that use libcurl (non-windows and win32 but
		 * not windows store or phone apps).
		 *
		 * @param in_bytesPerSec The low transfer rate threshold in bytes/sec
		 */
		void setUploadLowTransferRateThreshold(int in_bytesPerSec);

		/**
		 * Enables the message caching upon network error, which is disabled by default.
		 * Once enabled, if a client side network error is encountered
		 * (i.e. brainCloud server is unreachable presumably due to the client
		 * network being down) the sdk will do the following:
		 *
		 * 1 - cache the currently queued messages to brainCloud
		 * 2 - call the network error callback
		 * 3 - then expect the app to call either:
		 *     a) retryCachedMessages() to retry sending to brainCloud
		 *     b) flushCachedMessages() to dump all messages in the queue.
		 *
		 * Between steps 2 & 3, the app can prompt the user to retry connecting
		 * to brainCloud to determine whether to follow path 3a or 3b.
		 *
		 * Note that if path 3a is followed, and another network error is encountered,
		 * the process will begin all over again from step 1.
		 *
		 * WARNING - the brainCloud sdk will cache *all* api calls sent
		 * when a network error is encountered if this mechanism is enabled.
		 * This effectively freezes all communication with brainCloud.
		 * Apps must call either retryCachedMessages() or flushCachedMessages()
		 * for the brainCloud SDK to resume sending messages.
		 * resetCommunication() will also clear the message cache.
		 *
		 * @param in_enabled True if message should be cached on timeout
		 */
		void enableNetworkErrorMessageCaching(bool in_enabled);

		/** Attempts to resend any cached messages. If no messages are in the cache,
		 * this method does nothing.
		 */
		void retryCachedMessages();

		/**
		 * Flushes the cached messages to resume api call processing. This will dump
		 * all of the cached messages in the queue.
		 *
		 * @param in_sendApiErrorCallbacks If set to true API error callbacks will
		 * be called for every cached message with statusCode CLIENT_NETWORK_ERROR
		 * and reasonCode CLIENT_NETWORK_ERROR_TIMEOUT.
		 */
		void flushCachedMessages(bool in_sendApiErrorCallbacks);

		/**
		 * Inserts a marker which will tell the brainCloud comms layer
		 * to close the message bundle off at this point. Any messages queued
		 * before this method was called will likely be bundled together in
		 * the next send to the server.
		 *
		 * To ensure that only a single message is sent to the server you would
		 * do something like this:
		 *
		 * InsertEndOfMessageBundleMarker()
		 * SomeApiCall()
		 * InsertEndOfMessageBundleMarker()
		 *
		 */
		void insertEndOfMessageBundleMarker();

		/**
		* Sets the country code sent to brainCloud when a user authenticates.
		* Will override any auto detected country.
		* @param in_countryCode ISO 3166-1 two-letter country code
		*/
		void overrideCountryCode(const char * in_countryCode) { _countryCode = in_countryCode; }

		/**
		* Sets the language code sent to brainCloud when a user authenticates.
		* If the language is set to a non-ISO 639-1 standard value the game default will be used instead.
		* Will override any auto detected language.
		* @param in_languageCode ISO 639-1 two-letter language code
		*/
		void overrideLanguageCode(const char * in_languageCode) { _languageCode = in_languageCode; }

	protected:
		BrainCloudClient();

		static BrainCloudClient * _instance;

		IBrainCloudComms * _brainCloudComms;
		BrainCloudPlayerStatistics * _playerStatisticsService;
		BrainCloudGlobalStatistics * _globalStatisticsService;
		BrainCloudIdentity * _identityService;
		BrainCloudProduct * _productService;
		BrainCloudEntity * _entityService;
		BrainCloudGlobalEntity * _globalEntityService;
		BrainCloudMatchmaking * _matchmakingService;
		BrainCloudOneWayMatch * _oneWayMatchService;
		BrainCloudPlaybackStream * _playbackStreamService;
		BrainCloudScript * _scriptService;
		BrainCloudPlayerState * _playerStateService;
		BrainCloudFriend * _friendService;
		BrainCloudEvent * _eventService;
		BrainCloudAsyncMatch * _asyncMatchService;
		BrainCloudSocialLeaderboard * _socialLeaderboardService;
		BrainCloudGamification * _gamificationService;
		BrainCloudTime * _timeService;
		BrainCloudTournament * _tournamentService;
		BrainCloudAuthentication * _authenticationService;
		BrainCloudPushNotification * _pushNotificationService;
		BrainCloudPlayerStatisticsEvent * _playerStatisticsEventService;
		BrainCloudSteam * _steamService;
		BrainCloudGlobalApp * _globalAppService;
		BrainCloudS3Handling * _s3HandlingService;
		BrainCloudRedemptionCode * _redemptionCodeService;
		BrainCloudDataStream * _dataStreamService;
		BrainCloudProfanity * _profanityService;
		BrainCloudFile * _fileService;
		BrainCloudGroup * _groupService;
		BrainCloudMail * _mailService;

		static std::string s_brainCloudClientVersion;

		std::string _releasePlatform;
		std::string _appVersion;

		std::string _countryCode;
		std::string _languageCode;
		float _timezoneOffset;

	private:
		void setupOSLocaleData();
	};  // end class
}  // end namespace
