#pragma once

#include <map>
#include <string>
#include <list>
#include <algorithm>

#include "braincloud/BrainCloudClient.h"

#include "json/json.h"

namespace BrainCloud {

    /**
     * The BrainCloudWrapper provides some convenience functionality to developers when they are
     * getting started with the authentication system.
     *
     * By using the wrapper authentication methods, the anonymous and profile ids will be automatically
     * persisted upon successful authentication. When authenticating, any stored anonymous/profile ids will
     * be sent to the server. This strategy is useful when using anonymous authentication.
     */
    class BrainCloudWrapper : public BrainCloud::IServerCallback
    {
    public:

        BrainCloud::BrainCloudClient* client;

        /* Service getter methods */
        BrainCloudPlayerStatistics * getPlayerStatisticsService() { return client->getPlayerStatisticsService(); }
        BrainCloudGlobalStatistics * getGlobalStatisticsService() { return client->getGlobalStatisticsService(); }
        BrainCloudIdentity * getIdentityService() { return client->getIdentityService(); }
        BrainCloudVirtualCurrency * getVirtualCurrencyService() { return client->getVirtualCurrencyService(); }
        BrainCloudAppStore * getAppStoreService() { return client->getAppStoreService(); }
        BrainCloudEntity * getEntityService() { return client->getEntityService(); }
        BrainCloudGlobalEntity * getGlobalEntityService() { return client->getGlobalEntityService(); }
        BrainCloudMatchmaking * getMatchmakingService() { return client->getMatchmakingService(); }
        BrainCloudOneWayMatch * getOneWayMatchService() { return client->getOneWayMatchService(); }
        BrainCloudPlaybackStream * getPlaybackStreamService() { return client->getPlaybackStreamService(); }
        BrainCloudAsyncMatch * getAsyncMatchService() { return client->getAsyncMatchService(); }
        BrainCloudScript * getScriptService() { return client->getScriptService(); }
        BrainCloudPlayerState * getPlayerStateService() { return client->getPlayerStateService(); }
        BrainCloudFriend * getFriendService() { return client->getFriendService(); }
        BrainCloudEvent * getEventService() { return client->getEventService(); }
        BrainCloudSocialLeaderboard * getSocialLeaderboardService() { return client->getSocialLeaderboardService(); }
         BrainCloudSocialLeaderboard * getLeaderboardService() { return client->getLeaderboardService(); }
        BrainCloudGamification * getGamificationService() { return client->getGamificationService(); }
        BrainCloudTime * getTimeService() { return client->getTimeService(); }
        BrainCloudTournament * getTournamentService() { return client->getTournamentService(); }
        BrainCloudCustomEntity * getCustomEntityService() { return client->getCustomEntityService(); }
        BrainCloudItemCatalog* getItemCatalogService() { return client->getItemCatalogService(); }
        BrainCloudUserItems* getUserItemsService() { return client->getUserItemsService(); }
        BrainCloudPushNotification * getPushNotificationService() { return client->getPushNotificationService(); }
        BrainCloudPlayerStatisticsEvent * getPlayerStatisticsEventService() { return client->getPlayerStatisticsEventService(); }
        BrainCloudGlobalApp * getGlobalAppService() { return client->getGlobalAppService(); }
        BrainCloudS3Handling * getS3HandlingService() { return client->getS3HandlingService(); }
        BrainCloudRedemptionCode * getRedemptionCodeService() { return client->getRedemptionCodeService(); }
        BrainCloudDataStream * getDataStreamService() { return client->getDataStreamService(); }
        BrainCloudProfanity * getProfanityService() { return client->getProfanityService(); }
        BrainCloudFile * getFileService() { return client->getFileService(); }
        BrainCloudGlobalFile* getGlobalFileService() { return client->getGlobalFileService(); }
        BrainCloudGroup * getGroupService() { return client->getGroupService(); }
        BrainCloudMail * getMailService() { return client->getMailService(); }
        BrainCloudChat * getChatService() { return client->getChatService(); }
        BrainCloudMessaging * getMessagingService() { return client->getMessagingService(); }
        BrainCloudLobby * getLobbyService() { return client->getLobbyService(); }
        BrainCloudPresence * getPresenceService() { return client->getPresenceService(); }
		BrainCloudRelay * getRelayService() { return client->getRelayService(); }
		BrainCloudRTT * getRTTService() { return client->getRTTService(); }

        /**
         * Method returns a singleton instance of the BrainCloudWrapper.
         * @return A singleton instance of the BrainCloudWrapper.
         *
		 * @deprecated Use of the *singleton* has been deprecated. We recommend that you create your own *variable* to hold an instance of the brainCloudWrapper. Explanation here: http://getbraincloud.com/apidocs/wrappers-clients-and-inconvenient-singletons/
		 */
        DEPRECATED static BrainCloudWrapper* getInstance();

        /**
         * Instantiate a copy of the brainCloud wrapper. Don't use getInstance if creating your own copy.
         *
         * @param in_wrapperName
         */
        BrainCloudWrapper(const char * in_wrapperName = "");

        ~BrainCloudWrapper();


        /**
         * Method initializes the BrainCloudClient.
         *
         * @param in_serverURL The url to the brainCloud server
         * @param in_secretKey The secret key for your app
         * @param in_appId The app id
         * @param in_version The app version
         * @param in_companyName The company name used in the keychain for storing anonymous and profile ids.
         * You are free to pick anything you want.
         * @param in_appName The app name used in the keychain for storing anonymous and profile ids.
         * You are free to pick anything you want.
         */
        void initialize(const char * in_serverUrl, const char * in_secretKey, const char * in_appId, const char * in_version, const char * in_companyName, const char * in_appName);

        /**
         * Method initializes the BrainCloudClient with multiple app/secret.
         * Used when needed to switch between child and parent apps.
         *
         * @param in_serverURL The url to the brainCloud server
         *     Currently this should be:  https://sharedprod.braincloudservers.com/dispatcherv2
         * @param in_defaultAppId The default app id that we start with
         * @param in_secretMap A map of <appId, secretKey>
         * @param in_version The app version
         * @param in_companyName The company name used in the keychain for storing anonymous and profile ids.
         * You are free to pick anything you want.
         * @param in_appName The app name used in the keychain for storing anonymous and profile ids.
         * You are free to pick anything you want.
         */
        void initializeWithApps(const char * in_serverURL, const char * in_defaultAppId, const std::map<std::string, std::string>& in_secretMap, const char * in_version, const char * in_companyName, const char * in_appName);

        /**
         * Authenticate a user anonymously with brainCloud - used for apps that don't want to bother
         * the user to login, or for users who are sensitive to their privacy
         *
         * Service Name - Authenticate
         * Service Operation - Authenticate
         *
         * @param in_callback The method to be invoked when the server response is received
         *
         */
        void authenticateAnonymous(IServerCallback * in_callback = NULL);

        /*
         * Authenticate the user with a custom Email and Password.  Note that the client app
         * is responsible for collecting (and storing) the e-mail and potentially password
         * (for convenience) in the client data.  For the greatest security,
         * force the user to re-enter their * password at each login.
         * (Or at least give them that option).
         *
         * Note that the password sent from the client to the server is protected via SSL.
         *
         * Service Name - Authenticate
         * Service Operation - Authenticate
         *
         * @param in_email  The e-mail address of the user
         * @param in_password  The password of the user
         * @param forceCreate Should a new profile be created for this user if the account does not exist?
         * @param in_callback The method to be invoked when the server response is received
         *
         */
        void authenticateEmailPassword(const char * in_email, const char * in_password, bool in_forceCreate, IServerCallback * in_callback = NULL);

        /**
         * Authenticate the user via cloud code (which in turn validates the supplied credentials against an external system).
         * This allows the developer to extend brainCloud authentication to support other backend authentication systems.
         *
         * Service Name - Authenticate
         * Server Operation - Authenticate
         *
         * @param in_userid The user id
         * @param in_token The user token (password etc)
         * @param in_externalAuthName The name of the cloud script to call for external authentication
         * @param in_force Should a new profile be created for this user if the account does not exist?
         *
         * @returns   performs the in_success callback on success, in_failure callback on failure
         */
        void authenticateExternal(const char * in_userid, const char * in_token, const char * in_externalAuthName, bool in_forceCreate, IServerCallback * in_callback = NULL);
        		
        /*
		* Authenticate the user using a handoffId and authentication token
		*
		* Service Name - Authenticate
		* Service Operation - Authenticate
		*
		* @param in_handoffId braincloud handoff id generated from cloud script
		* @param in_securityToken The authentication token
		* @param in_callback The method to be invoked when the server response is received
		*/
		void authenticateHandoff(const char * in_handoffId, const char * in_securityToken, IServerCallback * in_callback = NULL);

		/*
		* Authenticate the user using a handoffCode 
		*
		* Service Name - Authenticate
		* Service Operation - Authenticate
		*
		* @param in_handoffCode the code we generate in cloudcode
		* @param in_callback The method to be invoked when the server response is received
		*/
		void authenticateSettopHandoff(const char * in_handoffCode, IServerCallback * in_callback = NULL);

        /*
         * Authenticate the user with brainCloud using their Facebook Credentials
         *
         * Service Name - Authenticate
         * Service Operation - Authenticate
         *
         * @param in_fbUserId The facebook id of the user
         * @param in_fbAuthToken The validated token from the Facebook SDK
         *   (that will be further validated when sent to the bC service)
         * @param in_forceCreate Should a new profile be created for this user if the account does not exist?
         * @param in_callback The method to be invoked when the server response is received
         *
         */
        void authenticateFacebook(const char * in_fbUserId, const char * in_fbAuthToken, bool in_forceCreate, IServerCallback * in_callback = NULL);

        /*
         * Authenticate the user with brainCloud using their Oculus Credentials
         *
         * Service Name - Authenticate
         * Service Operation - Authenticate
         *
         * @param in_oculusUserId The oculus id of the user
         * @param in_oculusNonce oculus token from the Oculus SDK
         * @param in_forceCreate Should a new profile be created for this user if the account does not exist?
         * @param in_callback The method to be invoked when the server response is received
         *
         */
        void authenticateOculus(const char * in_oculusUserId, const char * in_oculusNonce, bool in_forceCreate, IServerCallback * in_callback = NULL);


        /*
         * Authenticate the user using their Game Center id
         *
         * Service Name - Authenticate
         * Service Operation - Authenticate
         *
         * @param in_gameCenterId The player's game center id  (use the playerID property from the local GKPlayer object)
         * @param in_forceCreate Should a new profile be created for this user if the account does not exist?
         * @param in_success The method to call in event of successful login
         * @param in_failure The method to call in the event of an error during authentication
         *
         * @returns   performs the in_success callback on success, in_failure callback on failure
         *
         */
        void authenticateGameCenter(const char * in_gameCenterId, bool in_forceCreate, IServerCallback * in_callback = NULL);

		/*
		* Authenticate the user using a google userid(email address) and google authentication token.
		*
		* Service Name - Authenticate
		* Service Operation - Authenticate
		*
		* @param in_appleUserId  String of the apple accounts user Id OR email
		* @param in_identityToken  The authentication token confirming users identity
		* @param in_forceCreate Should a new profile be created for this user if the account does not exist?
		* @param in_callback The method to be invoked when the server response is received
		*/
		void authenticateApple(const char * in_appleUserId, const char * in_identityToken, bool in_forceCreate, IServerCallback * in_callback = NULL);

        /*
         * Authenticate the user using a google userid(email address) and google authentication token.
         *
         * Service Name - Authenticate
         * Service Operation - Authenticate
         *
         * @param in_googleUserId  String representation of google+ userid (email)
         * @param in_serverAuthCode The authentication token derived via the google apis.
         * @param in_forceCreate Should a new profile be created for this user if the account does not exist?
         * @param in_callback The method to be invoked when the server response is received
         *
         * @returns   performs the in_success callback on success, in_failure callback on failure
         *
         */
        void authenticateGoogle(const char * in_googleUserId, const char * in_serverAuthCode, bool in_forceCreate, IServerCallback * in_callback = NULL);\

        /*
         * Authenticate the user using a google openId
         *
         * Service Name - Authenticate
         * Service Operation - Authenticate
         *
         * @param in_googleUserAccountEmail  String representation of google+ userid (email)
         * @param in_IdToken  The authentication token derived via the google apis.
         * @param in_forceCreate Should a new profile be created for this user if the account does not exist?
         * @param in_callback The method to be invoked when the server response is received
         *
         * @returns   performs the in_success callback on success, in_failure callback on failure
         *
         */
        void authenticateGoogleOpenId(const char * in_googleUserAccountEmail, const char * in_IdToken, bool in_forceCreate, IServerCallback * in_callback = NULL);

        /*
         * Authenticate the user using a steam userid and session ticket (without any validation on the userid).
         *
         * Service Name - Authenticate
         * Service Operation - Authenticate
         *
         * @param in_userid  String representation of 64 bit steam id
         * @param in_sessionticket  The session ticket of the user (hex encoded)
         * @param in_forceCreate Should a new profile be created for this user if the account does not exist?
         * @param in_callback The method to be invoked when the server response is received
         *
         * @returns   performs the in_success callback on success, in_failure callback on failure
         *
         */
        void authenticateSteam(const char * in_userid, const char * in_sessionticket, bool in_forceCreate, IServerCallback * in_callback = NULL);

        /*
         * Authenticate the user using a Twitter userid, authentication token, and secret from Twitter.
         *
         * Service Name - Authenticate
         * Service Operation - Authenticate
         *
         * @param in_userid  String representation of Twitter userid
         * @param in_token  The authentication token derived via the Twitter apis.
         * @param in_secret  The secret given when attempting to link with Twitter
         * @param in_forceCreate Should a new profile be created for this user if the account does not exist?
         * @param in_callback The method to be invoked when the server response is received
         *
         * @returns   performs the in_success callback on success, in_failure callback on failure
         *
         */
        void authenticateTwitter(const char * in_userid, const char * in_token, const char * in_secret, bool in_forceCreate, IServerCallback * in_callback = NULL);

        /*
         * Authenticate the user using a userid and password (without any validation on the userid).
         * Similar to AuthenticateEmailPassword - except that that method has additional features to
         * allow for e-mail validation, password resets, etc.
         *
         * Service Name - Authenticate
         * Service Operation - Authenticate
         *
         * @param in_email  The e-mail address of the user
         * @param in_password  The password of the user
         * @param forceCreate Should a new profile be created for this user if the account does not exist?
         * @param in_callback The method to be invoked when the server response is received
         *
         */
        void authenticateUniversal(const char * in_userid, const char * in_password, bool in_forceCreate, IServerCallback * in_callback = NULL);

        /*
         * Smart Switch Authenticate will logout of the current profile, and switch to the new authentication type.
	     * In event the current session was previously an anonymous account, the smart switch will delete that profile.
	     * Use this function to keep a clean designflow from anonymous to signed profiles
         *
         * Authenticate the user with a custom Email and Password.  Note that the client app
         * is responsible for collecting (and storing) the e-mail and potentially password
         * (for convenience) in the client data.  For the greatest security,
         * force the user to re-enter their * password at each login.
         * (Or at least give them that option).
         *
         * Note that the password sent from the client to the server is protected via SSL.
         *
         * Service Name - Authenticate
         * Service Operation - Authenticate
         *
         * @param in_email  The e-mail address of the user
         * @param in_password  The password of the user
         * @param forceCreate Should a new profile be created for this user if the account does not exist?
         * @param in_callback The method to be invoked when the server response is received
         *
         */
        void smartSwitchAuthenticateEmailPassword(const char * in_email, const char * in_password, bool in_forceCreate, IServerCallback * in_callback = NULL);

        /**
         * Smart Switch Authenticate will logout of the current profile, and switch to the new authentication type.
	     * In event the current session was previously an anonymous account, the smart switch will delete that profile.
	     * Use this function to keep a clean designflow from anonymous to signed profiles
         *
         * Authenticate the user via cloud code (which in turn validates the supplied credentials against an external system).
         * This allows the developer to extend brainCloud authentication to support other backend authentication systems.
         *
         * Service Name - Authenticate
         * Server Operation - Authenticate
         *
         * @param in_userid The user id
         * @param in_token The user token (password etc)
         * @param in_externalAuthName The name of the cloud script to call for external authentication
         * @param in_force Should a new profile be created for this user if the account does not exist?
         *
         * @returns   performs the in_success callback on success, in_failure callback on failure
         */
        void smartSwitchAuthenticateExternal(const char * in_userid, const char * in_token, const char * in_externalAuthName, bool in_forceCreate, IServerCallback * in_callback = NULL);

        /*
         * Smart Switch Authenticate will logout of the current profile, and switch to the new authentication type.
	     * In event the current session was previously an anonymous account, the smart switch will delete that profile.
	     * Use this function to keep a clean designflow from anonymous to signed profiles
         *
         * Authenticate the user with brainCloud using their Facebook Credentials
         *
         * Service Name - Authenticate
         * Service Operation - Authenticate
         *
         * @param in_fbUserId The facebook id of the user
         * @param in_fbAuthToken The validated token from the Facebook SDK
         *   (that will be further validated when sent to the bC service)
         * @param in_forceCreate Should a new profile be created for this user if the account does not exist?
         * @param in_callback The method to be invoked when the server response is received
         *
         */
        void smartSwitchAuthenticateFacebook(const char * in_fbUserId, const char * in_fbAuthToken, bool in_forceCreate, IServerCallback * in_callback = NULL);

        /*
         * Smart Switch Authenticate will logout of the current profile, and switch to the new authentication type.
	     * In event the current session was previously an anonymous account, the smart switch will delete that profile.
	     * Use this function to keep a clean designflow from anonymous to signed profiles
         *
         * Authenticate the user with brainCloud using their Oculus Credentials
         *
         * Service Name - Authenticate
         * Service Operation - Authenticate
         *
         * @param in_oculusUserId The oculus id of the user
         * @param in_oculusNonce oculus token from the Oculus SDK
         * @param in_forceCreate Should a new profile be created for this user if the account does not exist?
         * @param in_callback The method to be invoked when the server response is received
         *
         */
        void smartSwitchAuthenticateOculus(const char * in_oculusUserId, const char * in_oculusNonce, bool in_forceCreate, IServerCallback * in_callback = NULL);


        /*
         * Smart Switch Authenticate will logout of the current profile, and switch to the new authentication type.
	     * In event the current session was previously an anonymous account, the smart switch will delete that profile.
	     * Use this function to keep a clean designflow from anonymous to signed profiles
         *
         * Authenticate the user using their Game Center id
         *
         * Service Name - Authenticate
         * Service Operation - Authenticate
         *
         * @param in_gameCenterId The player's game center id  (use the playerID property from the local GKPlayer object)
         * @param in_forceCreate Should a new profile be created for this user if the account does not exist?
         * @param in_success The method to call in event of successful login
         * @param in_failure The method to call in the event of an error during authentication
         *
         * @returns   performs the in_success callback on success, in_failure callback on failure
         *
         */
        void smartSwitchAuthenticateGameCenter(const char * in_gameCenterId, bool in_forceCreate, IServerCallback * in_callback = NULL);

        /*
         * Smart Switch Authenticate will logout of the current profile, and switch to the new authentication type.
	     * In event the current session was previously an anonymous account, the smart switch will delete that profile.
	     * Use this function to keep a clean designflow from anonymous to signed profiles
         *
         * Authenticate the user using a google userid(email address) and google authentication token.
         *
         * Service Name - Authenticate
         * Service Operation - Authenticate
         *
         * @param in_userid  String representation of google+ userid (email)
         * @param in_token  The authentication token derived via the google apis.
         * @param in_forceCreate Should a new profile be created for this user if the account does not exist?
         * @param in_callback The method to be invoked when the server response is received
         *
         * @returns   performs the in_success callback on success, in_failure callback on failure
         *
         */
        void smartSwitchAuthenticateGoogle(const char * in_userid, const char * in_token, bool in_forceCreate, IServerCallback * in_callback = NULL);

                /*
         * Smart Switch Authenticate will logout of the current profile, and switch to the new authentication type.
	     * In event the current session was previously an anonymous account, the smart switch will delete that profile.
	     * Use this function to keep a clean designflow from anonymous to signed profiles
         *
         * Authenticate the user using a google userid(email address) and google authentication token.
         *
         * Service Name - Authenticate
         * Service Operation - Authenticate
         *
         * @param in_userid  String representation of google+ userid (email)
         * @param in_token  The authentication token derived via the google apis.
         * @param in_forceCreate Should a new profile be created for this user if the account does not exist?
         * @param in_callback The method to be invoked when the server response is received
         *
         * @returns   performs the in_success callback on success, in_failure callback on failure
         *
         */
        void smartSwitchAuthenticateGoogleOpenId(const char * in_userid, const char * in_token, bool in_forceCreate, IServerCallback * in_callback = NULL);

                /*
         * Smart Switch Authenticate will logout of the current profile, and switch to the new authentication type.
	     * In event the current session was previously an anonymous account, the smart switch will delete that profile.
	     * Use this function to keep a clean designflow from anonymous to signed profiles
         *
         * Authenticate the user using a google userid(email address) and google authentication token.
         *
         * Service Name - Authenticate
         * Service Operation - Authenticate
         *
         * @param in_userid  String representation of apple+ userid (email)
         * @param in_token  The authentication token derived via the apple apis.
         * @param in_forceCreate Should a new profile be created for this user if the account does not exist?
         * @param in_callback The method to be invoked when the server response is received
         *
         * @returns   performs the in_success callback on success, in_failure callback on failure
         *
         */
        void smartSwitchAuthenticateApple(const char * in_userid, const char * in_token, bool in_forceCreate, IServerCallback * in_callback = NULL);

        /*
         * Smart Switch Authenticate will logout of the current profile, and switch to the new authentication type.
	     * In event the current session was previously an anonymous account, the smart switch will delete that profile.
	     * Use this function to keep a clean designflow from anonymous to signed profiles
         *
         * Authenticate the user using a steam userid and session ticket (without any validation on the userid).
         *
         * Service Name - Authenticate
         * Service Operation - Authenticate
         *
         * @param in_userid  String representation of 64 bit steam id
         * @param in_sessionticket  The session ticket of the user (hex encoded)
         * @param in_forceCreate Should a new profile be created for this user if the account does not exist?
         * @param in_callback The method to be invoked when the server response is received
         *
         * @returns   performs the in_success callback on success, in_failure callback on failure
         *
         */
        void smartSwitchAuthenticateSteam(const char * in_userid, const char * in_sessionticket, bool in_forceCreate, IServerCallback * in_callback = NULL);

        /*
         * Smart Switch Authenticate will logout of the current profile, and switch to the new authentication type.
	     * In event the current session was previously an anonymous account, the smart switch will delete that profile.
	     * Use this function to keep a clean designflow from anonymous to signed profiles
         *
         * Authenticate the user using a Twitter userid, authentication token, and secret from Twitter.
         *
         * Service Name - Authenticate
         * Service Operation - Authenticate
         *
         * @param in_userid  String representation of Twitter userid
         * @param in_token  The authentication token derived via the Twitter apis.
         * @param in_secret  The secret given when attempting to link with Twitter
         * @param in_forceCreate Should a new profile be created for this user if the account does not exist?
         * @param in_callback The method to be invoked when the server response is received
         *
         * @returns   performs the in_success callback on success, in_failure callback on failure
         *
         */
        void smartSwitchAuthenticateTwitter(const char * in_userid, const char * in_token, const char * in_secret, bool in_forceCreate, IServerCallback * in_callback = NULL);

        /*
         * Smart Switch Authenticate will logout of the current profile, and switch to the new authentication type.
	     * In event the current session was previously an anonymous account, the smart switch will delete that profile.
	     * Use this function to keep a clean designflow from anonymous to signed profiles
         *
         * Authenticate the user using a userid and password (without any validation on the userid).
         * Similar to AuthenticateEmailPassword - except that that method has additional features to
         * allow for e-mail validation, password resets, etc.
         *
         * Service Name - Authenticate
         * Service Operation - Authenticate
         *
         * @param in_email  The e-mail address of the user
         * @param in_password  The password of the user
         * @param in_forceCreate Should a new profile be created for this user if the account does not exist?
         * @param in_callback The method to be invoked when the server response is received
         *
         */
        void smartSwitchAuthenticateUniversal(const char * in_userid, const char * in_password, bool in_forceCreate, IServerCallback * in_callback = NULL);

	    /**
		 * Reset Email password - Sends a password reset email to the specified address
		 *
		 * Service Name - Authenticate
		 * Operation - ResetEmailPassword
		 *
		 * @param in_externalId The email address to send the reset email to.
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Note the follow error reason codes:
		 *
		 * SECURITY_ERROR (40209) - If the email address cannot be found.
		 */
		void resetEmailPassword(const char * in_externalId, IServerCallback * in_callback = NULL);

		/**
		 * Reset Email password with service parameters - Sends a password reset email to 
		 * the specified address
		 *
		 * Service Name - Authenticate
		 * Operation - ResetEmailPasswordAdvanced
		 *
		 * @param appId the applicationId
		 * @param in_emailAddress The email address to send the reset email to.
		 * @param in_serviceParams - parameters to send to the email service. See documentation for
		 * full list. http://getbraincloud.com/apidocs/apiref/#capi-mail
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Note the follow error reason codes:
		 *
		 * SECURITY_ERROR (40209) - If the email address cannot be found.
		 */
		void resetEmailPasswordAdvanced(const char * in_emailAddress, std::string in_serviceParams, IServerCallback * in_callback = NULL);

        	    /**
		 * Reset Email password - Sends a password reset email to the specified address
		 *
		 * Service Name - Authenticate
		 * Operation - ResetEmailPassword
		 *
		 * @param in_externalId The email address to send the reset email to.
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Note the follow error reason codes:
		 *
		 * SECURITY_ERROR (40209) - If the email address cannot be found.
		 */
		void resetEmailPasswordWithExpiry(const char * in_externalId, int in_tokenTtlInMinutes , IServerCallback * in_callback = NULL);

		/**
		 * Reset Email password with service parameters - Sends a password reset email to 
		 * the specified address
		 *
		 * Service Name - Authenticate
		 * Operation - ResetEmailPasswordAdvanced
		 *
		 * @param appId the applicationId
		 * @param in_emailAddress The email address to send the reset email to.
		 * @param in_serviceParams - parameters to send to the email service. See documentation for
		 * full list. http://getbraincloud.com/apidocs/apiref/#capi-mail
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Note the follow error reason codes:
		 *
		 * SECURITY_ERROR (40209) - If the email address cannot be found.
		 */
		void resetEmailPasswordAdvancedWithExpiry(const char * in_emailAddress, std::string in_serviceParams, int in_tokenTtlInMinutes , IServerCallback * in_callback = NULL);

        

	    /**
		 * Reset Email password - Sends a password reset email to the specified address
		 *
		 * Service Name - Authenticate
		 * Operation - ResetEmailPassword
		 *
		 * @param in_externalId The email address to send the reset email to.
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Note the follow error reason codes:
		 *
		 * SECURITY_ERROR (40209) - If the email address cannot be found.
		 */
		void resetUniversalIdPassword(const char * in_externalId, IServerCallback * in_callback = NULL);

		/**
		 * Reset Email password with service parameters - Sends a password reset email to 
		 * the specified address
		 *
		 * Service Name - Authenticate
		 * Operation - ResetEmailPasswordAdvanced
		 *
		 * @param appId the applicationId
		 * @param in_emailAddress The email address to send the reset email to.
		 * @param in_serviceParams - parameters to send to the email service. See documentation for
		 * full list. http://getbraincloud.com/apidocs/apiref/#capi-mail
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Note the follow error reason codes:
		 *
		 * SECURITY_ERROR (40209) - If the email address cannot be found.
		 */
		void resetUniversalIdPasswordAdvanced(const char * in_emailAddress, std::string in_serviceParams, IServerCallback * in_callback = NULL);

        	    /**
		 * Reset Email password - Sends a password reset email to the specified address
		 *
		 * Service Name - Authenticate
		 * Operation - ResetEmailPassword
		 *
		 * @param in_externalId The email address to send the reset email to.
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Note the follow error reason codes:
		 *
		 * SECURITY_ERROR (40209) - If the email address cannot be found.
		 */
		void resetUniversalIdPasswordWithExpiry(const char * in_externalId, int in_tokenTtlInMinutes , IServerCallback * in_callback = NULL);

		/**
		 * Reset Email password with service parameters - Sends a password reset email to 
		 * the specified address
		 *
		 * Service Name - Authenticate
		 * Operation - ResetEmailPasswordAdvanced
		 *
		 * @param appId the applicationId
		 * @param in_emailAddress The email address to send the reset email to.
		 * @param in_serviceParams - parameters to send to the email service. See documentation for
		 * full list. http://getbraincloud.com/apidocs/apiref/#capi-mail
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Note the follow error reason codes:
		 *
		 * SECURITY_ERROR (40209) - If the email address cannot be found.
		 */
		void resetUniversalIdPasswordAdvancedWithExpiry(const char * in_emailAddress, std::string in_serviceParams, int in_tokenTtlInMinutes , IServerCallback * in_callback = NULL);

		/**
		* Re-authenticates the user with brainCloud
		*
		* @param in_callback The method to be invoked when the server response is received
		*
		*/
		void reconnect(IServerCallback * in_callback = NULL);

        /**
         * Run callbacks, to be called once per frame from your main thread
         */
        void runCallbacks();

        /**
         * Returns a singleton instance of the BrainCloudClient.
         * @return A singleton instance of the BrainCloudClient.
         *
		 * @deprecated Use of the *singleton* has been deprecated. We recommend that you create your own *variable* to hold an instance of the brainCloudWrapper. Explanation here: http://getbraincloud.com/apidocs/wrappers-clients-and-inconvenient-singletons/
		 */
        DEPRECATED static BrainCloud::BrainCloudClient* getBC() { return getInstance()->getBCClient(); }

        /**
         * Returns a singleton instance of the BrainCloudClient.
         * @return A singleton instance of the BrainCloudClient.
         */
        BrainCloud::BrainCloudClient* getBCClient() {
            return client;
        }

        /**
         * Returns the stored profile id
         * @return The stored profile id
         */
        std::string getStoredProfileId();

        /**
         * Sets the stored profile id
         * @param in_profileId The profile id to set
         */
        void setStoredProfileId(const char * in_profileId);

        /**
         * Resets the profile id to empty string
         */
        void resetStoredProfileId();

        /**
         * Returns the stored anonymous id
         * @return The stored anonymous id
         */
        std::string getStoredAnonymousId();

        /**
         * Sets the stored anonymous id
         * @param in_anonymousId The anonymous id to set
         */
        void setStoredAnonymousId(const char * in_anonymousId);

        /**
         * Resets the anonymous id to empty string
         */
        void resetStoredAnonymousId();

        /**
         * For non-anonymous authentication methods, a profile id will be passed in
         * when this value is set to false. This will generate an error on the server
         * if the profile id passed in does not match the profile associated with the
         * authentication credentials. By default, this value is true.
         *
         * @param in_alwaysAllow Controls whether the profile id is passed in with
         * non-anonymous authentications.
         */
        void setAlwaysAllowProfileSwitch(bool in_alwaysAllow);

        /**
         * Returns the value for always allow profile switch
         * @return Whether to always allow profile switches
         */
        bool getAlwaysAllowProfileSwitch();

        virtual void serverCallback(BrainCloud::ServiceName serviceName, BrainCloud::ServiceOperation serviceOperation, std::string const & jsonData);
        virtual void serverError(BrainCloud::ServiceName serviceName,
            BrainCloud::ServiceOperation serviceOperation,
            int statusCode, int reasonCode, const std::string & message);

    protected:

        static BrainCloudWrapper* m_instance;
        static std::string AUTHENTICATION_ANONYMOUS;

        IServerCallback* m_authenticateCallback;

        std::string m_lastUrl;
        std::string m_lastSecretKey;
        std::string m_lastGameId;
        std::string m_lastGameVersion;
        std::string m_wrapperName;

        bool m_alwaysAllowProfileSwitch;

        void initializeIdentity(bool in_isAnonymousAuth = false);
        void reauthenticate();

		void getIdentitiesCallback(IServerCallback *success);

        // these methods are not really used
        std::string getStoredAuthenticationType();
        void setStoredAuthenticationType(const char * authenticationType);
        void resetStoredAuthenticationType();
    };
}
