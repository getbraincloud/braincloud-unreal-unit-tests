// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <string>

namespace BrainCloud
{
	class IServerCallback;
	class BrainCloudClient;
	class AuthenticationType;

	class BrainCloudIdentity
	{
	public:
		BrainCloudIdentity(BrainCloudClient* in_client);

		/**
		 * Updates univeral id of the current profile.
		 *
		 * Service Name - identity
		 * Service Operation - UpdateUniversalIdLogin
		 *
		 * @param in_externalId the id that's been connected with
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void updateUniversalIdLogin(const char * in_externalId, IServerCallback * in_callback = NULL);

		/**
		 * Attaches a univeral id to the current profile with no login capability.
		 *
		 * Service Name - identity
		 * Service Operation - AttachNonLoginUniversalId
		 *
		 * @param in_externalId the id that's been connected with
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void attachNonLoginUniversalId(const char * in_externalId, IServerCallback * in_callback = NULL);

		/**
		 * Attach the user's Facebook credentials to the current profile.
		 *
		 * Service Name - identity
		 * Service Operation - Attach
		 *
		 * @param in_facebookId The facebook id of the user
		 * @param in_authenticationToken The validated token from the Facebook SDK
		 *   (that will be further validated when sent to the bC service)
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Errors to watch for:  SWITCHING_PROFILES - this means that the Facebook identity you provided
		 * already points to a different profile.  You will likely want to offer the user the
		 * choice to *SWITCH* to that profile, or *MERGE* the profiles.
		 *
		 * To switch profiles, call ClearSavedProfileID() and call AuthenticateFacebook().
		 */
		void attachFacebookIdentity(const char * in_facebookId, const char * in_authenticationToken, IServerCallback * in_callback = NULL);

		/**
		 * Merge the profile associated with the provided Facebook credentials with the
		 * current profile.
		 *
		 * Service Name - identity
		 * Service Operation - Merge
		 *
		 * @param in_facebookId The facebook id of the user
		 * @param in_authenticationToken The validated token from the Facebook SDK
		 *   (that will be further validated when sent to the bC service)
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 */
		void mergeFacebookIdentity(const char * in_facebookId, const char * in_authenticationToken, IServerCallback * in_callback = NULL);

		/**
		 * Detach the Facebook identity from this profile.
		 *
		 * Service Name - identity
		 * Service Operation - Detach
		 *
		 * @param in_facebookId The facebook id of the user
		 * @param in_continueAnon Proceed even if the profile will revert to anonymous?
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set in_continueAnon to false, and
		 * disconnecting this identity would result in the profile being anonymous (which means that
		 * the profile wouldn't be retrievable if the user loses their device)
		 */
		void detachFacebookIdentity(const char * in_facebookId, bool in_continueAnon, IServerCallback * in_callback = NULL);

			/**
		 * Attach the user's Apple credentials to the current profile.
		 *
		 * Service Name - identity
		 * Service Operation - Attach
		 *
		 * @param in_appleId The appleid of the user
		 * @param in_authenticationToken The validated token from the Apple SDK
		 *   (that will be further validated when sent to the bC service)
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Errors to watch for:  SWITCHING_PROFILES - this means that the Apple identity you provided
		 * already points to a different profile.  You will likely want to offer the user the
		 * choice to *SWITCH* to that profile, or *MERGE* the profiles.
		 *
		 * To switch profiles, call ClearSavedProfileID() and call AuthenticateApple().
		 */
		void attachAppleIdentity(const char * in_appleId, const char * in_authenticationToken, IServerCallback * in_callback = NULL);

		/**
		 * Merge the profile associated with the provided Apple credentials with the
		 * current profile.
		 *
		 * Service Name - identity
		 * Service Operation - Merge
		 *
		 * @param in_appleId The apple id of the user
		 * @param in_authenticationToken The validated token from the Apple SDK
		 *   (that will be further validated when sent to the bC service)
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 */
		void mergeAppleIdentity(const char * in_appleId, const char * in_authenticationToken, IServerCallback * in_callback = NULL);

		/**
		 * Detach the Apple identity from this profile.
		 *
		 * Service Name - identity
		 * Service Operation - Detach
		 *
		 * @param in_appleId The apple id of the user
		 * @param in_continueAnon Proceed even if the profile will revert to anonymous?
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set in_continueAnon to false, and
		 * disconnecting this identity would result in the profile being anonymous (which means that
		 * the profile wouldn't be retrievable if the user loses their device)
		 */
		void detachAppleIdentity(const char * in_appleId, bool in_continueAnon, IServerCallback * in_callback = NULL);

		/**
		 * Attach a Game Center identity to the current profile.
		 *
		 * Service Name - identity
		 * Service Operation - Attach
		 *
		 * @param in_gameCenterId The player's game center id  (use the playerID property from the local GKPlayer object)
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Errors to watch for:  SWITCHING_PROFILES - this means that the Game Center identity you provided
		 * already points to a different profile.  You will likely want to offer the player the
		 * choice to *SWITCH* to that profile, or *MERGE* the profiles.
		 *
		 * To switch profiles, call ClearSavedProfileID() and call this method again.
		 *
		 */
		void attachGameCenterIdentity(const char * in_gameCenterId, IServerCallback * in_callback = NULL);

		/**
		 * Merge the profile associated with the specified Game Center identity with the current profile.
		 *
		 * Service Name - identity
		 * Service Operation - Merge
		 *
		 * @param in_gameCenterId The player's game center id  (use the playerID property from the local GKPlayer object)
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void mergeGameCenterIdentity(const char * in_gameCenterId, IServerCallback * in_callback = NULL);

		/**
		 * Detach the Game Center identity from the current profile.
		 *
		 * Service Name - identity
		 * Service Operation - Detach
		 *
		 * @param in_gameCenterId The player's game center id  (use the playerID property from the local GKPlayer object)
		 * @param in_continueAnon Proceed even if the profile will revert to anonymous?
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set in_continueAnon to false, and
		 * disconnecting this identity would result in the profile being anonymous (which means that
		 * the profile wouldn't be retrievable if the user loses their device)
		 */
		void detachGameCenterIdentity(const char * in_gameCenterId, bool in_continueAnon, IServerCallback * in_callback = NULL);

		/**
		 * Attach a Email and Password identity to the current profile.
		 *
		 * Service Name - identity
		 * Service Operation - Attach
		 *
		 * @param in_email The user's e-mail address
		 * @param in_password The user's password
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Errors to watch for:  SWITCHING_PROFILES - this means that the email address you provided
		 * already points to a different profile.  You will likely want to offer the user the
		 * choice to *SWITCH* to that profile, or *MERGE* the profiles.
		 *
		 * To switch profiles, call ClearSavedProfileID() and then call AuthenticateEmailPassword().
		 */
		void attachEmailIdentity(const char * in_email, const char * in_password, IServerCallback * in_callback = NULL);

		/**
		 * Merge the profile associated with the provided e=mail with the current profile.
		 *
		 * Service Name - identity
		 * Service Operation - Merge
		 *
		 * @param in_email The user's e-mail address
		 * @param in_password The user's password
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 */
		void mergeEmailIdentity(const char * in_email, const char * in_password, IServerCallback * in_callback = NULL);

		/**
		 * Detach the e-mail identity from the current profile
		 *
		 * Service Name - identity
		 * Service Operation - Detach
		 *
		 * @param in_email The user's e-mail address
		 * @param in_continueAnon Proceed even if the profile will revert to anonymous?
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set in_continueAnon to false, and
		 * disconnecting this identity would result in the profile being anonymous (which means that
		 * the profile wouldn't be retrievable if the user loses their device)
		 */
		void detachEmailIdentity(const char * in_email, bool in_continueAnon, IServerCallback * in_callback = NULL);

		/**
		 * Attach a Universal (userid + password) identity to the current profile.
		 *
		 * Service Name - identity
		 * Service Operation - Attach
		 *
		 * @param in_userId The user's userid
		 * @param in_password The user's password
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Errors to watch for:  SWITCHING_PROFILES - this means that the email address you provided
		 * already points to a different profile.  You will likely want to offer the user the
		 * choice to *SWITCH* to that profile, or *MERGE* the profiles.
		 *
		 * To switch profiles, call ClearSavedProfileID() and then call AuthenticateEmailPassword().
		 */
		void attachUniversalIdentity(const char * in_userId, const char * in_password, IServerCallback * in_callback = NULL);

		/**
		 * Merge the profile associated with the provided userId with the current profile.
		 *
		 * Service Name - identity
		 * Service Operation - Merge
		 *
		 * @param in_userId The user's userid
		 * @param in_password The user's password
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void mergeUniversalIdentity(const char * in_userId, const char * in_password, IServerCallback * in_callback = NULL);

		/**
		 * Detach the universal identity from the current profile
		 *
		 * Service Name - identity
		 * Service Operation - Detach
		 *
		 * @param in_userId The user's userid
		 * @param in_continueAnon Proceed even if the profile will revert to anonymous?
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set in_continueAnon to false, and
		 * disconnecting this identity would result in the profile being anonymous (which means that
		 * the profile wouldn't be retrievable if the user loses their device)
		 */
		void detachUniversalIdentity(const char * in_userId, bool in_continueAnon, IServerCallback * in_callback = NULL);

		/**
		 * Attach a Steam (userid + steamsessionticket) identity to the current profile.
		 *
		 * Service Name - identity
		 * Service Operation - Attach
		 *
		 * @param in_steamId String representation of 64 bit steam id
		 * @param in_sessionTicket The user's session ticket (hex encoded)
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Errors to watch for:  SWITCHING_PROFILES - this means that the email address you provided
		 * already points to a different profile.  You will likely want to offer the user the
		 * choice to *SWITCH* to that profile, or *MERGE* the profiles.
		 *
		 * To switch profiles, call ClearSavedProfileID() and then call AuthenticateSteam().
		 */
		void attachSteamIdentity(const char * in_steamId, const char * in_sessionTicket, IServerCallback * in_callback = NULL);

		/**
		 * Merge the profile associated with the provided steam userid with the current profile.
		 *
		 * Service Name - identity
		 * Service Operation - Merge
		 *
		 * @param in_steamId String representation of 64 bit steam id
		 * @param in_sessionTicket The user's session ticket (hex encoded)
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 */
		void mergeSteamIdentity(const char * in_steamId, const char * in_sessionTicket, IServerCallback * in_callback = NULL);

		/**
		 * Detach the steam identity from the current profile
		 *
		 * Service Name - identity
		 * Service Operation - Detach
		 *
		 * @param in_steamId String representation of 64 bit steam id
		 * @param in_continueAnon Proceed even if the profile will revert to anonymous?
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set in_continueAnon to false, and
		 * disconnecting this identity would result in the profile being anonymous (which means that
		 * the profile wouldn't be retrievable if the user loses their device)
		 */
		void detachSteamIdentity(const char * in_steamId, bool in_continueAnon, IServerCallback * in_callback = NULL);

		/**
		 * Attach the user's Google credentials to the current profile.
		 *
		 * Service Name - identity
		 * Service Operation - Attach
		 *
		 * @param in_googleId The Google id of the user
		 * @param in_authenticationToken The validated token from the Google SDK
		 *   (that will be further validated when sent to the bC service)
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Errors to watch for:  SWITCHING_PROFILES - this means that the Google identity you provided
		 * already points to a different profile.  You will likely want to offer the user the
		 * choice to *SWITCH* to that profile, or *MERGE* the profiles.
		 *
		 * To switch profiles, call ClearSavedProfileID() and call AuthenticateGoogle().
		 */
		void attachGoogleIdentity(const char * in_googleId, const char * in_authenticationToken, IServerCallback * in_callback = NULL);

		/**
		 * Merge the profile associated with the provided Google credentials with the
		 * current profile.
		 *
		 * Service Name - identity
		 * Service Operation - Merge
		 *
		 * @param in_googleId The Google id of the user
		 * @param in_authenticationToken The validated token from the Google SDK
		 *   (that will be further validated when sent to the bC service)
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 */
		void mergeGoogleIdentity(const char * in_googleId, const char * in_authenticationToken, IServerCallback * in_callback = NULL);

		/*
		 * Detach the Google identity from this profile.
		 *
		 * Service Name - identity
		 * Service Operation - Detach
		 *
		 * @param in_googleId The Google id of the user
		 * @param in_continueAnon Proceed even if the profile will revert to anonymous?
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set in_continueAnon to false, and
		 * disconnecting this identity would result in the profile being anonymous (which means that
		 * the profile wouldn't be retrievable if the user loses their device)
		 */
		void detachGoogleIdentity(const char * in_googleId, bool in_continueAnon, IServerCallback * in_callback = NULL);

		/**
		 * Attach the user's Google credentials to the current profile.
		 *
		 * Service Name - identity
		 * Service Operation - Attach
		 *
		 * @param in_googleId The Google id of the user
		 * @param in_authenticationToken The validated token from the Google SDK
		 *   (that will be further validated when sent to the bC service)
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Errors to watch for:  SWITCHING_PROFILES - this means that the Google identity you provided
		 * already points to a different profile.  You will likely want to offer the user the
		 * choice to *SWITCH* to that profile, or *MERGE* the profiles.
		 *
		 * To switch profiles, call ClearSavedProfileID() and call AuthenticateGoogle().
		 */
		void attachGoogleOpenIdentity(const char * in_googleId, const char * in_authenticationToken, IServerCallback * in_callback = NULL);

		/**
		 * Merge the profile associated with the provided Google credentials with the
		 * current profile.
		 *
		 * Service Name - identity
		 * Service Operation - Merge
		 *
		 * @param in_googleId The Google id of the user
		 * @param in_authenticationToken The validated token from the Google SDK
		 *   (that will be further validated when sent to the bC service)
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 */
		void mergeGoogleOpenIdentity(const char * in_googleId, const char * in_authenticationToken, IServerCallback * in_callback = NULL);

		/*
		 * Detach the Google identity from this profile.
		 *
		 * Service Name - identity
		 * Service Operation - Detach
		 *
		 * @param in_googleId The Google id of the user
		 * @param in_continueAnon Proceed even if the profile will revert to anonymous?
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set in_continueAnon to false, and
		 * disconnecting this identity would result in the profile being anonymous (which means that
		 * the profile wouldn't be retrievable if the user loses their device)
		 */
		void detachGoogleOpenIdentity(const char * in_googleId, bool in_continueAnon, IServerCallback * in_callback = NULL);

		/**
		 * Attach the user's Twitter credentials to the current profile.
		 *
		 * Service Name - identity
		 * Service Operation - Attach
		 *
		 * @param in_twitterId The Twitter id of the user
		 * @param in_authenticationToken The authentication token derived from the twitter APIs
		 * @param in_secret The secret given when attempting to link with Twitter
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Errors to watch for:  SWITCHING_PROFILES - this means that the Twitter identity you provided
		 * already points to a different profile.  You will likely want to offer the user the
		 * choice to *SWITCH* to that profile, or *MERGE* the profiles.
		 *
		 * To switch profiles, call ClearSavedProfileID() and call AuthenticateTwitter().
		 */
		void attachTwitterIdentity(const char * in_twitterId, const char * in_authenticationToken, const char * in_secret, IServerCallback * in_callback = NULL);

		/**
		 * Merge the profile associated with the provided Twitter credentials with the
		 * current profile.
		 *
		 * Service Name - identity
		 * Service Operation - Merge
		 *
		 * @param in_twitterId The Twitter id of the user
		 * @param in_authenticationToken The authentication token derived from the twitter APIs
		 * @param in_secret The secret given when attempting to link with Twitter
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 */
		void mergeTwitterIdentity(const char * in_twitterId, const char * in_authenticationToken, const char * in_secret, IServerCallback * in_callback = NULL);

		/**
		 * Detach the Twitter identity from this profile.
		 *
		 * Service Name - identity
		 * Service Operation - Detach
		 *
		 * @param in_twitterId The Twitter id of the user
		 * @param in_continueAnon Proceed even if the profile will revert to anonymous?
		 * @param in_callback The method to be invoked when the server response is received
		 *
		 * Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set in_continueAnon to false, and
		 * disconnecting this identity would result in the profile being anonymous (which means that
		 * the profile wouldn't be retrievable if the user loses their device)
		 */
		void detachTwitterIdentity(const char * in_twitterId, bool in_continueAnon, IServerCallback * in_callback = NULL);

		/**
		* Attach the user's Parse credentials to the current profile.
		*
		* Service Name - identity
		* Service Operation - Attach
		*
		* @param in_parseId The Parse id of the user
		* @param in_authenticationToken The validated token from Parse
		*   (that will be further validated when sent to the bC service)
		* @param in_callback The method to be invoked when the server response is received
		*
		* Errors to watch for:  SWITCHING_PROFILES - this means that the Google identity you provided
		* already points to a different profile.  You will likely want to offer the user the
		* choice to *SWITCH* to that profile, or *MERGE* the profiles.
		*
		* To switch profiles, call ClearSavedProfileID() and call AuthenticateParse().
		*/
		void attachParseIdentity(const char * in_parseId, const char * in_authenticationToken, IServerCallback * in_callback = NULL);

		/**
		* Merge the profile associated with the provided Parse credentials with the
		* current profile.
		*
		* Service Name - identity
		* Service Operation - Merge
		*
		* @param in_parseId The Parse id of the user
		* @param in_authenticationToken The validated token from Parse
		*   (that will be further validated when sent to the bC service)
		* @param in_callback The method to be invoked when the server response is received
		*
		*/
		void mergeParseIdentity(const char * in_parseId, const char * in_authenticationToken, IServerCallback * in_callback = NULL);

		/*
		* Detach the Google identity from this profile.
		*
		* Service Name - identity
		* Service Operation - Detach
		*
		* @param in_parseId The Parse id of the user
		* @param in_continueAnon Proceed even if the profile will revert to anonymous?
		* @param in_callback The method to be invoked when the server response is received
		*
		* Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set in_continueAnon to false, and
		* disconnecting this identity would result in the profile being anonymous (which means that
		* the profile wouldn't be retrievable if the user loses their device)
		*/
		void detachParseIdentity(const char * in_parseId, bool in_continueAnon, IServerCallback * in_callback = NULL);

		/**
		 * Switch to a Child Profile
		 *
		 * Service Name - identity
		 * Service Operation - SWITCH_TO_CHILD_PROFILE
		 *
		 * @param in_childProfileId The profileId of the child profile to switch to
		 * If null and forceCreate is true a new profile will be created
		 * @param in_childAppId The appId of the child app to switch to
		 * @param in_forceCreate Should a new profile be created if it does not exist?
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void switchToChildProfile(const char * in_childProfileId, const char * in_childAppId, bool in_forceCreate, IServerCallback * in_callback = NULL);

		/**
		 * Switches to a child profile of an app when only one profile exists
		 * If multiple profiles exist this returns an error
		 *
		 * Service Name - identity
		 * Service Operation - SWITCH_TO_CHILD_PROFILE
		 *
		 * @param in_childAppId The App ID of the child app to switch to
		 * @param in_forceCreate Should a new profile be created if it does not exist?
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void switchToSingletonChildProfile(const char * in_childAppId, bool in_forceCreate, IServerCallback * in_callback = NULL);

		/**
		 * Switch to a Parent Profile
		 *
		 * Service Name - identity
		 * Service Operation - SWITCH_TO_PARENT_PROFILE
		 *
		 * @param in_parentLevelName The level of the parent to switch to
		 * If null and forceCreate is true a new profile will be created
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void switchToParentProfile(const char * in_parentLevelName, IServerCallback * in_callback = NULL);

		/**
		 * Returns a list of all child profiles in child Apps
		 *
		 * Service Name - identity
		 * Service Operation - GET_CHILD_PROFILES
		 *
		 * @param in_includeSummaryData Whether to return the summary friend data along with this call
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void getChildProfiles(bool in_includeSummaryData, IServerCallback * in_callback = NULL);

		/**
		* Retrieve list of identities
		*
		* Service Name - identity
		* Service Operation - GET_IDENTITIES
		*
		* @param in_callback The method to be invoked when the server response is received
		*/
		void getIdentities(IServerCallback * in_callback = NULL);

		/**
		* Retrieve list of expired identities
		*
		* Service Name - identity
		* Service Operation - GET_EXPIRED_IDENTITIES
		*
		* @param in_callback The method to be invoked when the server response is received
		*/
		void getExpiredIdentities(IServerCallback * in_callback = NULL);

		/**
		* Refreshes an identity for this user
		*
		* Service Name - identity
		* Service Operation - REFRESH_IDENTITY
		*
		* @param in_externalId User ID
		* @param in_authenticationToken Password or client side token
		* @param in_authenticationType Type of authentication
		* @param in_callback The method to be invoked when the server response is received
		*/
		void refreshIdentity(const char * in_externalId, const char * in_authenticationToken, AuthenticationType in_authenticationType, IServerCallback * in_callback = NULL);

		/**
		* Allows email identity email address to be changed
		*
		* Service Name - identity
		* Service Operation - CHANGE_EMAIL_IDENTITY
		*
		* @param in_oldEmailAddress Old email address
	    * @param in_password Password for identity
	    * @param in_newEmailAddress New email address
	    * @param in_updateContactEmail Whether to update contact email in profile
	    * @param in_callback The method to be invoked when the server response is received
	    *
		*/
		void changeEmailIdentity(const char * in_oldEmailAddress, const char * in_password, const char * in_newEmailAddress, bool in_updateContactEmail,  IServerCallback * in_callback = NULL);

		/**
		 * Attach a new identity to a parent app
		 *
		 * Service Name - identity
		 * Service Operation - ATTACH_PARENT_WITH_IDENTITY
		 *
		 * @param externalId The users id for the new credentials
		 * @param authenticationToken The password/token
		 * @param authenticationType Type of identity
		 * @param externalAuthName Optional - if attaching an external identity
		 * @param forceCreate Should a new profile be created if it does not exist?
		 * @param successCallback The success callback
		 * @param errorCallback The failure callback.
		 * @param cbObject The user object sent to the callback
		 */
		void attachParentWithIdentity(const char * in_externalId, const char * in_authenticationToken, AuthenticationType in_authenticationType,
			const char * in_externalAuthName, bool in_forceCreate, IServerCallback * in_callback = NULL);

		/**
		 * Detaches parent from this user's profile
		 *
		 * Service Name - identity
		 * Service Operation - DETACH_PARENT
		 *
		 * @param successCallback The success callback
		 * @param errorCallback The failure callback.
		 * @param cbObject The user object sent to the callback
		 */
		void detachParent(IServerCallback * in_callback = NULL);

		/**
		 * Attaches a peer identity to this user's profile
		 *
		 * Service Name - identity
		 * Service Operation - ATTACH_PEER_PROFILE
		 *
		 * @param peer Name of the peer to connect to
		 * @param externalId The users id for the new credentials
		 * @param authenticationToken The password/token
		 * @param authenticationType Type of identity
		 * @param externalAuthName Optional - if attaching an external identity
		 * @param forceCreate Should a new profile be created if it does not exist?
		 * @param successCallback The success callback
		 * @param errorCallback The failure callback.
		 * @param cbObject The user object sent to the callback
		 */
		void attachPeerProfile(const char * in_peer, const char * in_externalId, const char * in_authenticationToken, AuthenticationType in_authenticationType,
			const char * in_externalAuthName, bool in_forceCreate, IServerCallback * in_callback = NULL);

		/**
		 * Detaches a peer identity from this user's profile
		 *
		 * Service Name - identity
		 * Service Operation - DETACH_PEER
		 *
		 * @param peer Name of the peer to connect to
		 * @param successCallback The success callback
		 * @param errorCallback The failure callback.
		 * @param cbObject The user object sent to the callback
		 */
		void detachPeer(const char * in_peer, IServerCallback * in_callback = NULL);

		/**
		 * Returns a list of peer profiles attached to this user
		 *
		 * Service Name - identity
		 * Service Operation - GET_PEER_PROFILES
		 *
		 * @param successCallback The success callback
		 * @param errorCallback The failure callback.
		 * @param cbObject The user object sent to the callback
		 */
		void getPeerProfiles(IServerCallback * in_callback = NULL);

		/**
		 * Attaches the given block chain public key identity to the current profile.
		 *
		 * Service Name - identity
		 * Service Operation - ATTACH_BLOCKCHAIN_IDENTITY
		 *
		 * @param blockchainConfig
		 * @param publicKey
		 * @param successCallback The success callback
		 * @param errorCallback The failure callback.
		 * @param cbObject The user object sent to the callback
		 */
		void attachBlockchainIdentity(const char* in_blockchainConfig, const char* in_publicKey, IServerCallback * in_callback = NULL);

		/**
		 * Detaches the blockchain identity to the current profile.
		 *
		 * Service Name - identity
		 * Service Operation - ATTACH_BLOCKCHAIN_IDENTITY
		 *
		 * @param blockchainConfig
		 * @param successCallback The success callback
		 * @param errorCallback The failure callback.
		 * @param cbObject The user object sent to the callback
		 */
		void detachBlockchainIdentity(const char* in_blockchainConfig, IServerCallback * in_callback = NULL);

	private:
		BrainCloudClient * m_client;

		void switchToChildProfile(const char * in_childProfileId, const char * in_childAppId, bool in_forceCreate, bool in_forceSingleton, IServerCallback * in_callback = NULL);

		void attachIdentity(const char * in_externalId, const char * in_authenticationToken, AuthenticationType in_authenticationType, IServerCallback * in_callback = NULL);
		void mergeIdentity(const char * in_externalId, const char * in_authenticationToken, AuthenticationType in_authenticationType, IServerCallback * in_callback = NULL);
		void detachIdentity(const char * in_externalId, AuthenticationType in_authenticationType, bool in_continueAnon, IServerCallback * in_callback = NULL);
	};
}
