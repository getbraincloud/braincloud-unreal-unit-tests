// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <string>
#include "braincloud/BrainCloudTypes.h"

namespace BrainCloud
{
	class BrainCloudClient;
	class IServerCallback;
	class AuthenticationType;

	class BrainCloudAuthentication
	{
	public:
		static const char * AUTH_FACEBOOK;

		BrainCloudAuthentication(BrainCloudClient* in_client);

		// internal use only
		void setClientLib(const char* lib);

		/**
		 * Initialize - initializes the identity service with a saved
		 * anonymous installation id and most recently used profile id
		 *
		 * @param in_anonymousId  The anonymous installation id that was generated for this device
		 * @param in_profileId The id of the profile id that was most recently used by the app (on this device)
		 */
		void initialize(const char * in_profileId, const char * in_anonymousId);

		/**
		* Used to create the anonymous installation id for the brainCloud profile.
		* @returns A unique Anonymous ID
		*/
		std::string generateAnonymousId();

		/**
		 * Used to clear the saved profile id - to use in cases when the user is
		 * attempting to switch to a different game profile.
		 */
		void clearSavedProfileId();

		/**
		 * Authenticate a user anonymously with brainCloud - used for apps that don't want to bother
		 * the user to login, or for users who are sensitive to their privacy
		 *
		 * Service Name - Authenticate
		 * Service Operation - Authenticate
		 *
		 * @param in_forceCreate  Should a new profile be created if it does not exist?
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 */
		void authenticateAnonymous(bool in_forceCreate, IServerCallback * in_callback = NULL);

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
		 * Authenticate the user using their Game Center id
		 *
		 * Service Name - Authenticate
		 * Service Operation - Authenticate
		 *
		 * @param in_gameCenterId The player's game center id  (use the playerID property from the local GKPlayer object)
		 * @param in_forceCreate Should a new profile be created for this user if the account does not exist?
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void authenticateGameCenter(const char * in_gameCenterId, bool in_forceCreate, IServerCallback * in_callback = NULL);

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
		 */
		void authenticateUniversal(const char * in_userId, const char * in_password, bool in_forceCreate, IServerCallback * in_callback = NULL);

		/*
		 * Authenticate the user using a steam userid and session ticket (without any validation on the userid).
		 *
		 * Service Name - Authenticate
		 * Service Operation - Authenticate
		 *
		 * @param in_userId  String representation of 64 bit steam id
		 * @param in_sessionticket  The session ticket of the user (hex encoded)
		 * @param in_forceCreate Should a new profile be created for this user if the account does not exist?
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void authenticateSteam(const char * in_userId, const char * in_sessionticket, bool in_forceCreate, IServerCallback * in_callback = NULL);

		/*
		* Authenticate the user using a google userid(email address) and google authentication token.
		*
		* Service Name - Authenticate
		* Service Operation - Authenticate
		*
		* @param in_userId  String representation of google+ userid (email)
		* @param in_token  The authentication token derived via the google apis.
		* @param in_forceCreate Should a new profile be created for this user if the account does not exist?
		* @param in_callback The method to be invoked when the server response is received
		*/
		void authenticateGoogle(const char * in_userId, const char * in_token, bool in_forceCreate, IServerCallback * in_callback = NULL);

		/*
		 * Authenticate the user using a Twitter userid, authentication token, and secret from Twitter.
		 *
		 * Service Name - Authenticate
		 * Service Operation - Authenticate
		 *
		 * @param in_userId  String representation of Twitter userid
		 * @param in_token  The authentication token derived via the Twitter apis.
		 * @param in_secret  The secret given when attempting to link with Twitter
		 * @param in_forceCreate Should a new profile be created for this user if the account does not exist?
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void authenticateTwitter(const char * in_userId, const char * in_token, const char * in_secret, bool in_forceCreate, IServerCallback * in_callback = NULL);

		/*
		* Authenticate the user using a Pase userid and authentication token
		*
		* Service Name - Authenticate
		* Service Operation - Authenticate
		*
		* @param in_userId String representation of Parse userid
		* @param in_token The authentication token
		* @param in_forceCreate Should a new profile be created for this user if the account does not exist?
		* @param in_callback The method to be invoked when the server response is received
		*/
		void authenticateParse(const char * in_userId, const char * in_token, bool in_forceCreate, IServerCallback * in_callback = NULL);

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

		/**
		 * Authenticate the user via cloud code (which in turn validates the supplied credentials against an external system).
		 * This allows the developer to extend brainCloud authentication to support other backend authentication systems.
		 *
		 * Service Name - Authenticate
		 * Server Operation - Authenticate
		 *
		 * @param in_userId The user id
		 * @param in_token The user token (password etc)
		 * @param in_externalAuthName The name of the cloud script to call for external authentication
		 * @param in_force Should a new profile be created for this user if the account does not exist?
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void authenticateExternal(const char * in_userId, const char * in_token, const char * in_externalAuthName, bool in_forceCreate, IServerCallback * in_callback = NULL);

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

		const std::string & getAnonymousId() const { return _anonymousId; }
		const std::string & getProfileId() const { return _profileId; }

		void setAnonymousId(const char * anonymousId) { _anonymousId = anonymousId; }
		void setProfileId(const char * profileId) { _profileId = profileId; }

	protected:
		BrainCloudClient * m_client;
		std::string _anonymousId;
		std::string _profileId;
		std::string _clientLib;

		void authenticate(const char * in_externalId, const char * in_authenticationToken, AuthenticationType in_authenticationType, const char * in_externalAuthName, bool in_forceCreate, IServerCallback * in_callback = NULL);
	};
}