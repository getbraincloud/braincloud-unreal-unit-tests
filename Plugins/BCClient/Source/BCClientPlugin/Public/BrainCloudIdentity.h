// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCAuthType.h"

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudIdentity
{
  public:
	BrainCloudIdentity(BrainCloudClient *client);

	/*
	 * Attaches the given block chain public key identity to the current profile.
	 *
	 * Service Name - Identity
	 * Service Operation - AttachBlockchainIdentity
	 *
	 * @param blockchainConfig The block chains configuration
	 * @param publicKey The key associated with the config
	 * @param callback The method to be invoked when the server response is received
	 */
	void attachBlockchainIdentity(const FString &blockchainConfig, const FString &publicKey, IServerCallback *callback = nullptr);

	/*
	 * Detach the Facebook identity from this profile.
	 *
	 * Service Name - Identity
	 * Service Operation - DetachBlockchainIdentity
	 *
	 * @param blockchainId The facebook id of the user
	 * @param callback The method to be invoked when the server response is received
	 */
	void detachBlockchainIdentity(const FString &blockchainId, IServerCallback *callback = nullptr);

	/*
	 * Attach the user's Facebook credentials to the current profile.
	 *
	 * Service Name - Identity
	 * Service Operation - Attach
	 *
	 * @param externalId The facebook id of the user
	 * @param authenticationToken The validated token from the Facebook SDK
	 *   (that will be further validated when sent to the bC service)
	 * @param callback The method to be invoked when the server response is received
	 *
	 * Errors to watch for:  SWITCHING_PROFILES - this means that the Facebook identity you provided
	 * already points to a different profile.  You will likely want to offer the player the
	 * choice to *SWITCH* to that profile, or *MERGE* the profiles.
	 *
	 * To switch profiles, call ClearSavedProfileID() and call AuthenticateFacebook().
	 */
	void attachFacebookIdentity(const FString &facebookId, const FString &authenticationToken, IServerCallback *callback = nullptr);

	/*
	 * Merge the profile associated with the provided Facebook credentials with the
	 * current profile.
	 *
	 * Service Name - Identity
	 * Service Operation - Merge
	 *
	 * @param externalId The facebook id of the user
	 * @param authenticationToken The validated token from the Facebook SDK
	 *   (that will be further validated when sent to the bC service)
	 * @param callback The method to be invoked when the server response is received
	 *
	 */
	void mergeFacebookIdentity(const FString &facebookId, const FString &authenticationToken, IServerCallback *callback = nullptr);

	/*
	 * Detach the Facebook identity from this profile.
	 *
	 * Service Name - Identity
	 * Service Operation - Detach
	 *
	 * @param externalId The facebook id of the user
	 * @param continueAnon Proceed even if the profile will revert to anonymous?
	 * @param callback The method to be invoked when the server response is received
	 *
	 * Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set continueAnon to false, and
	 * disconnecting this identity would result in the profile being anonymous (which means that
	 * the profile wouldn't be retrievable if the user loses their device)
	 */
	void detachFacebookIdentity(const FString &facebookId, bool continueAnon, IServerCallback *callback = nullptr);

	/*
	 * Attach the user's FacebookLimited credentials to the current profile.
	 *
	 * Service Name - Identity
	 * Service Operation - Attach
	 *
	 * @param externalId The facebookLimited id of the user
	 * @param authenticationToken The validated token from the Facebook SDK
	 *   (that will be further validated when sent to the bC service)
	 * @param callback The method to be invoked when the server response is received
	 *
	 * Errors to watch for:  SWITCHING_PROFILES - this means that the FacebookLimited identity you provided
	 * already points to a different profile.  You will likely want to offer the player the
	 * choice to *SWITCH* to that profile, or *MERGE* the profiles.
	 *
	 * To switch profiles, call ClearSavedProfileID() and call AuthenticateFacebookLimited().
	 */
	void attachFacebookLimitedIdentity(const FString &facebookLimitedId, const FString &authenticationToken, IServerCallback *callback = nullptr);

	/*
	 * Merge the profile associated with the provided FacebookLimited credentials with the
	 * current profile.
	 *
	 * Service Name - Identity
	 * Service Operation - Merge
	 *
	 * @param externalId The facebookLimited id of the user
	 * @param authenticationToken The validated token from the Facebook SDK
	 *   (that will be further validated when sent to the bC service)
	 * @param callback The method to be invoked when the server response is received
	 *
	 */
	void mergeFacebookLimitedIdentity(const FString &facebookLimitedId, const FString &authenticationToken, IServerCallback *callback = nullptr);

	/*
	 * Detach the FacebookLimited identity from this profile.
	 *
	 * Service Name - Identity
	 * Service Operation - Detach
	 *
	 * @param externalId The facebookLimited id of the user
	 * @param continueAnon Proceed even if the profile will revert to anonymous?
	 * @param callback The method to be invoked when the server response is received
	 *
	 * Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set continueAnon to false, and
	 * disconnecting this identity would result in the profile being anonymous (which means that
	 * the profile wouldn't be retrievable if the user loses their device)
	 */
	void detachFacebookLimitedIdentity(const FString &facebookLimitedId, bool continueAnon, IServerCallback *callback = nullptr);


	/*
	 * Attach the user's Oculus credentials to the current profile.
	 *
	 * Service Name - Identity
	 * Service Operation - Attach
	 *
	 * @param oculusId The oculus id of the user
	 * @param oculusNonce token from the Oculus SDK
	 * @param callback The method to be invoked when the server response is received
	 *
	 * Errors to watch for:  SWITCHING_PROFILES - this means that the Oculus identity you provided
	 * already points to a different profile.  You will likely want to offer the player the
	 * choice to *SWITCH* to that profile, or *MERGE* the profiles.
	 *
	 * To switch profiles, call ClearSavedProfileID() and call AuthenticateOculus().
	 */
	void attachOculusIdentity(const FString &oculusId, const FString &oculusNonce, IServerCallback *callback = nullptr);

	/*
	 * Merge the profile associated with the provided Oculus credentials with the
	 * current profile.
	 *
	 * Service Name - Identity
	 * Service Operation - Merge
	 *
	 * @param externalId The oculus id of the user
	 * @param oculusNonce token from the Oculus SDK
	 * @param callback The method to be invoked when the server response is received
	 *
	 */
	void mergeOculusIdentity(const FString &oculusId, const FString &oculusNonce, IServerCallback *callback = nullptr);

	/*
	 * Detach the Oculus identity from this profile.
	 *
	 * Service Name - Identity
	 * Service Operation - Detach
	 *
	 * @param externalId The oculus id of the user
	 * @param continueAnon Proceed even if the profile will revert to anonymous?
	 * @param callback The method to be invoked when the server response is received
	 *
	 * Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set continueAnon to false, and
	 * disconnecting this identity would result in the profile being anonymous (which means that
	 * the profile wouldn't be retrievable if the user loses their device)
	 */
	void detachOculusIdentity(const FString &oculusId, bool continueAnon, IServerCallback *callback = nullptr);


	/*
	 * Attach the user's PSN credentials to the current profile.
	 *
	 * Service Name - Identity
	 * Service Operation - Attach
	 *
	 * @param psnAccountId The psn account id of the user
	 * @param authenticationToken The validated token from the Playstation SDK
	 *   (that will be further validated when sent to the bC service)
	 * @param callback The method to be invoked when the server response is received
	 *
	 * Errors to watch for:  SWITCHING_PROFILES - this means that the Facebook identity you provided
	 * already points to a different profile.  You will likely want to offer the player the
	 * choice to *SWITCH* to that profile, or *MERGE* the profiles.
	 *
	 * To switch profiles, call ClearSavedProfileID() and call AuthenticatePlaystationNetwork().
	 */
	void attachPlaystationNetworkIdentity(const FString &psnAccountId, const FString &authenticationToken, IServerCallback *callback = nullptr);

	/*
	 * Merge the profile associated with the provided PSN credentials with the
	 * current profile.
	 *
	 * Service Name - Identity
	 * Service Operation - Merge
	 *
	 * @param psnAccountId The psn account id of the user
	 * @param authenticationToken The validated token from the Playstation SDK
	 *   (that will be further validated when sent to the bC service)
	 * @param callback The method to be invoked when the server response is received
	 *
	 */
	void mergePlaystationNetworkIdentity(const FString &psnAccountId, const FString &authenticationToken, IServerCallback *callback = nullptr);

	/*
	 * Detach the PSN identity from this profile.
	 *
	 * Service Name - Identity
	 * Service Operation - Detach
	 *
	 * @param psnAccountId The psn account id of the user
	 * @param continueAnon Proceed even if the profile will revert to anonymous?
	 * @param callback The method to be invoked when the server response is received
	 *
	 * Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set continueAnon to false, and
	 * disconnecting this identity would result in the profile being anonymous (which means that
	 * the profile wouldn't be retrievable if the user loses their device)
	 */
	void detachPlaystationNetworkIdentity(const FString &psnAccountId, bool continueAnon, IServerCallback *callback = nullptr);

	/*
	 * Attach a Game Center identity to the current profile.
	 *
	 * Service Name - Identity
	 * Service Operation - Attach
	 *
	 * @param gameCenterId The player's game center id  (use the playerID property from the local GKPlayer object)
	 * @param callback The method to be invoked when the server response is received
	 *
	 * Errors to watch for:  SWITCHING_PROFILES - this means that the Facebook identity you provided
	 * already points to a different profile.  You will likely want to offer the player the
	 * choice to *SWITCH* to that profile, or *MERGE* the profiles.
	 *
	 * To switch profiles, call ClearSavedProfileID() and call this method again.
	 *
	 */
	void attachGameCenterIdentity(const FString &gameCenterId, IServerCallback *callback = nullptr);

	/*
	 * Merge the profile associated with the specified Game Center identity with the current profile.
	 *
	 * Service Name - Identity
	 * Service Operation - Merge
	 *
	 * @param gameCenterId The player's game center id  (use the playerID property from the local GKPlayer object)
	 * @param callback The method to be invoked when the server response is received
	 */
	void mergeGameCenterIdentity(const FString &gameCenterId, IServerCallback *callback = nullptr);

	/*
	 * Detach the Game Center identity from the current profile.
	 *
	 * Service Name - Identity
	 * Service Operation - Detach
	 *
	 * @param gameCenterId The player's game center id  (use the playerID property from the local GKPlayer object)
	 * @param continueAnon Proceed even if the profile will revert to anonymous?
	 * @param callback The method to be invoked when the server response is received
	 *
	 * Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set continueAnon to false, and
	 * disconnecting this identity would result in the profile being anonymous (which means that
	 * the profile wouldn't be retrievable if the user loses their device)
	 */
	void detachGameCenterIdentity(const FString &gameCenterId, bool continueAnon, IServerCallback *callback = nullptr);

	/*
	 * Attach a Email and Password identity to the current profile.
	 *
	 * Service Name - Identity
	 * Service Operation - Attach
	 *
	 * @param email The player's e-mail address
	 * @param password The player's password
	 * @param callback The method to be invoked when the server response is received
	 *
	 * Errors to watch for:  SWITCHING_PROFILES - this means that the email address you provided
	 * already points to a different profile.  You will likely want to offer the player the
	 * choice to *SWITCH* to that profile, or *MERGE* the profiles.
	 *
	 * To switch profiles, call ClearSavedProfileID() and then call AuthenticateEmailPassword().
	 */
	void attachEmailIdentity(const FString &email, const FString &password, IServerCallback *callback = nullptr);

	/*
	 * Merge the profile associated with the provided e=mail with the current profile.
	 *
	 * Service Name - Identity
	 * Service Operation - Merge
	 *
	 * @param email The player's e-mail address
	 * @param password The player's password
	 * @param callback The method to be invoked when the server response is received
	 */
	void mergeEmailIdentity(const FString &email, const FString &password, IServerCallback *callback = nullptr);

	/*
	 * Detach the e-mail identity from the current profile
	 *
	 * Service Name - Identity
	 * Service Operation - Detach
	 *
	 * @param email The player's e-mail address
	 * @param continueAnon Proceed even if the profile will revert to anonymous?
	 * @param callback The method to be invoked when the server response is received
	 *
	 * Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set continueAnon to false, and
	 * disconnecting this identity would result in the profile being anonymous (which means that
	 * the profile wouldn't be retrievable if the user loses their device)
	 */
	void detachEmailIdentity(const FString &email, bool continueAnon, IServerCallback *callback = nullptr);

	/*
	 * Attach a Universal (userid + password) identity to the current profile.
	 *
	 * Service Name - Identity
	 * Service Operation - Attach
	 *
	 * @param userId The player's userid
	 * @param password The player's password
	 * @param callback The method to be invoked when the server response is received
	 *
	 * Errors to watch for:  SWITCHING_PROFILES - this means that the email address you provided
	 * already points to a different profile.  You will likely want to offer the player the
	 * choice to *SWITCH* to that profile, or *MERGE* the profiles.
	 *
	 * To switch profiles, call ClearSavedProfileID() and then call AuthenticateEmailPassword().
	 */
	void attachUniversalIdentity(const FString &userId, const FString &password, IServerCallback *callback = nullptr);

	/*
	 * Merge the profile associated with the provided e=mail with the current profile.
	 *
	 * Service Name - Identity
	 * Service Operation - Merge
	 *
	 * @param userId The player's userid
	 * @param password The player's password
	 * @param callback The method to be invoked when the server response is received
	 */
	void mergeUniversalIdentity(const FString &userId, const FString &password, IServerCallback *callback = nullptr);

	/*
	 * Detach the universal identity from the current profile
	 *
	 * Service Name - Identity
	 * Service Operation - Detach
	 *
	 * @param userId The player's userid
	 * @param continueAnon Proceed even if the profile will revert to anonymous?
	 * @param callback The method to be invoked when the server response is received
	 *
	 * Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set continueAnon to false, and
	 * disconnecting this identity would result in the profile being anonymous (which means that
	 * the profile wouldn't be retrievable if the user loses their device)
	 */
	void detachUniversalIdentity(const FString &userId, bool continueAnon, IServerCallback *callback = nullptr);

	/*
	 * Attach a Steam (userid + steamsessionticket) identity to the current profile.
	 *
	 * Service Name - Identity
	 * Service Operation - Attach
	 *
	 * @param steamId String representation of 64 bit steam id
	 * @param sessionTicket The player's session ticket (hex encoded)
	 * @param callback The method to be invoked when the server response is received
	 *
	 * Errors to watch for:  SWITCHING_PROFILES - this means that the email address you provided
	 * already points to a different profile.  You will likely want to offer the player the
	 * choice to *SWITCH* to that profile, or *MERGE* the profiles.
	 *
	 * To switch profiles, call ClearSavedProfileID() and then call AuthenticateSteam().
	 */
	void attachSteamIdentity(const FString &steamId, const FString &sessionTicket, IServerCallback *callback = nullptr);

	/*
	 * Merge the profile associated with the provided steam userid with the current profile.
	 *
	 * Service Name - Identity
	 * Service Operation - Merge
	 *
	 * @param steamId String representation of 64 bit steam id
	 * @param sessionTicket The player's session ticket (hex encoded)
	 * @param callback The method to be invoked when the server response is received
	 */
	void mergeSteamIdentity(const FString &steamId, const FString &sessionTicket, IServerCallback *callback = nullptr);

	/*
	 * Detach the steam identity from the current profile
	 *
	 * Service Name - Identity
	 * Service Operation - Detach
	 *
	 * @param steamId String representation of 64 bit steam id
	 * @param continueAnon Proceed even if the profile will revert to anonymous?
	 * @param callback The method to be invoked when the server response is received
	 *
	 * Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set continueAnon to false, and
	 * disconnecting this identity would result in the profile being anonymous (which means that
	 * the profile wouldn't be retrievable if the user loses their device)
	 */
	void detachSteamIdentity(const FString &steamId, bool continueAnon, IServerCallback *callback = nullptr);

	/**
	* Attach the user's Google credentials to the current profile.
	*
    * Service Name - Identity
    * Service Operation - Attach
    *
    * @param googleUserId String representation of google+ userid (email)
    * @param serverAuthCode  The server authentication token derived via the google apis. Gotten with calls like RequestServerAuthCode
    * @param forceCreate Should a new profile be created for this user if the account does not exist?
    * @param callback The method to be invoked when the server response is received
	*
	* Errors to watch for:  SWITCHING_PROFILES - this means that the Google identity you provided
	* already points to a different profile.  You will likely want to offer the player the
	* choice to *SWITCH* to that profile, or *MERGE* the profiles.
	*
	* To switch profiles, call ClearSavedProfileID() and call AuthenticateGoogle().
	*/
	void attachGoogleIdentity(const FString &googleUserId, const FString &serverAuthCode, IServerCallback *callback = nullptr);

	/**
	* Merge the profile associated with the provided Google credentials with the
	* current profile.
	*
    * Service Name - Identity
    * Service Operation - Merge
    *
    * @param googleUserId String representation of google+ userid (email)
    * @param serverAuthCode  The server authentication token derived via the google apis. Gotten with calls like RequestServerAuthCode
    * @param forceCreate Should a new profile be created for this user if the account does not exist?
    * @param callback The method to be invoked when the server response is received
	*
	*/
	void mergeGoogleIdentity(const FString &googleUserId, const FString &serverAuthCode, IServerCallback *callback = nullptr);

	/*
	* Detach the Google identity from this profile.
	*
    * Service Name - Identity
    * Service Operation - Detach
    *
    * @param googleUserId String representation of google+ userid (email)
    * @param serverAuthCode  The server authentication token derived via the google apis. Gotten with calls like RequestServerAuthCode
    * @param forceCreate Should a new profile be created for this user if the account does not exist?
    * @param callback The method to be invoked when the server response is received
	*
	* Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set continueAnon to false, and
	* disconnecting this identity would result in the profile being anonymous (which means that
	* the profile wouldn't be retrievable if the user loses their device)
	*/
	void detachGoogleIdentity(const FString &googleUserId, bool continueAnon, IServerCallback *callback = nullptr);

	/**
	* Attach the user's GoogleOpenId credentials to the current profile.
    * Service Name - Identity
    * Service Operation - Attach
    *
    * @param googleUserAccountEmail The email associated with the google user
    * @param IdToken  The Id token of the google account. Can get with calls like requestIdToken
    * @param forceCreate Should a new profile be created for this user if the account does not exist?
    * @param callback The method to be invoked when the server response is received
	* Errors to watch for:  SWITCHING_PROFILES - this means that the Google identity you provided
	* already points to a different profile.  You will likely want to offer the player the
	* choice to *SWITCH* to that profile, or *MERGE* the profiles.
	*
	* To switch profiles, call ClearSavedProfileID() and call AuthenticateGoogle().
	*/
	void attachGoogleOpenIdIdentity(const FString &googleUserAccountEmail, const FString &IdToken, IServerCallback *callback = nullptr);

	/**
	* Merge the profile associated with the provided GoogleOpenId credentials with the
	* current profile.
    * Service Name - Identity
    * Service Operation - merge
    *
    * @param googleUserAccountEmail The email associated with the google user
    * @param IdToken  The Id token of the google account. Can get with calls like requestIdToken
    * @param forceCreate Should a new profile be created for this user if the account does not exist?
    * @param callback The method to be invoked when the server response is received
	*
	*/
	void mergeGoogleOpenIdIdentity(const FString &googleUserAccountEmail, const FString &IdToken, IServerCallback *callback = nullptr);

	/*
	* Detach the GoogleOpenId identity from this profile.
	*
    * Service Name - Identity
    * Service Operation - merge
    *
    * @param googleUserAccountEmail The email associated with the google user
    * @param IdToken  The Id token of the google account. Can get with calls like requestIdToken
    * @param forceCreate Should a new profile be created for this user if the account does not exist?
    * @param callback The method to be invoked when the server response is received
	*
	* Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set continueAnon to false, and
	* disconnecting this identity would result in the profile being anonymous (which means that
	* the profile wouldn't be retrievable if the user loses their device)
	*/
	void detachGoogleOpenIdIdentity(const FString &googleUserAccountEmail, bool continueAnon, IServerCallback *callback = nullptr);

	/**
	* Attach the user's Apple credentials to the current profile.
    * Service Name - Identity
    * Service Operation - attach
    *
    * @param appleUserId this can be user id OR the email of the user account
    * @param identityToken  the token confirming the user's identity
    * @param forceCreate Should a new profile be created for this user if the account does not exist?
    * @param callback The method to be invoked when the server response is received
	* Errors to watch for:  SWITCHING_PROFILES - this means that the Google identity you provided
	* already points to a different profile.  You will likely want to offer the player the
	* choice to *SWITCH* to that profile, or *MERGE* the profiles.
	*
	* To switch profiles, call ClearSavedProfileID() and call AuthenticateGoogle().
	*/
	void attachAppleIdentity(const FString &appleUserId, const FString &identityToken, IServerCallback *callback = nullptr);

	/**
	* Merge the profile associated with the provided Apple credentials with the
	* current profile.
    * Service Name - Identity
    * Service Operation - merge
    *
    * @param appleUserId this can be user id OR the email of the user account
    * @param identityToken  the token confirming the user's identity
    * @param forceCreate Should a new profile be created for this user if the account does not exist?
    * @param callback The method to be invoked when the server response is received
	*
	*/
	void mergeAppleIdentity(const FString &appleUserId, const FString &identityToken, IServerCallback *callback = nullptr);

	/*
	* Detach the Apple identity from this profile.
	*
    * Service Name - Identity
    * Service Operation - detach
    *
    * @param appleUserId this can be user id OR the email of the user account
    * @param identityToken  the token confirming the user's identity
    * @param forceCreate Should a new profile be created for this user if the account does not exist?
    * @param callback The method to be invoked when the server response is received
	*
	* Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set continueAnon to false, and
	* disconnecting this identity would result in the profile being anonymous (which means that
	* the profile wouldn't be retrievable if the user loses their device)
	*/
	void detachAppleIdentity(const FString &appleUserId, bool continueAnon, IServerCallback *callback = nullptr);

	/**
	* Attach the user's Twitter credentials to the current profile.
	*
	* Service Name - Identity
	* Service Operation - Attach
	*
	* @param twitterId The Twitter id of the user
	* @param authenticationToken The authentication token derrived from the twitter APIs
	* @param secret The secret given when attempting to link with Twitter
	* @param callback The method to be invoked when the server response is received
	*
	* Errors to watch for:  SWITCHING_PROFILES - this means that the Twitter identity you provided
	* already points to a different profile.  You will likely want to offer the player the
	* choice to *SWITCH* to that profile, or *MERGE* the profiles.
	*
	* To switch profiles, call ClearSavedProfileID() and call AuthenticateTwitter().
	*/
	void attachTwitterIdentity(const FString &twitterId, const FString &authenticationToken, const FString &secret, IServerCallback *callback = nullptr);

	/**
	* Merge the profile associated with the provided Twitter credentials with the
	* current profile.
	*
	* Service Name - Identity
	* Service Operation - Merge
	*
	* @param twitterId The Twitter id of the user
	* @param authenticationToken The authentication token derrived from the twitter APIs
	* @param secret The secret given when attempting to link with Twitter
	* @param callback The method to be invoked when the server response is received
	*
	*/
	void mergeTwitterIdentity(const FString &twitterId, const FString &authenticationToken, const FString &secret, IServerCallback *callback = nullptr);

	/**
	* Detach the Twitter identity from this profile.
	*
	* Service Name - Identity
	* Service Operation - Detach
	*
	* @param twitterId The Twitter id of the user
	* @param continueAnon Proceed even if the profile will revert to anonymous?
	* @param callback The method to be invoked when the server response is received
	*
	* Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set continueAnon to false, and
	* disconnecting this identity would result in the profile being anonymous (which means that
	* the profile wouldn't be retrievable if the user loses their device)
	*/
	void detachTwitterIdentity(const FString &twitterId, bool continueAnon, IServerCallback *callback = nullptr);

	/**
	* Attach the user's Parse credentials to the current profile.
	*
	* Service Name - Identity
	* Service Operation - Attach
	*
	* @param parseId The Parse id of the user
	* @param authenticationToken The validated token from Parse
	*   (that will be further validated when sent to the bC service)
	* @param callback The method to be invoked when the server response is received
	*
	* Errors to watch for:  SWITCHING_PROFILES - this means that the Google identity you provided
	* already points to a different profile.  You will likely want to offer the player the
	* choice to *SWITCH* to that profile, or *MERGE* the profiles.
	*
	* To switch profiles, call ClearSavedProfileID() and call AuthenticateParse().
	*/
	void attachParseIdentity(const FString &parseId, const FString &authenticationToken, IServerCallback *callback = nullptr);

	/**
	* Merge the profile associated with the provided Parse credentials with the
	* current profile.
	*
	* Service Name - Identity
	* Service Operation - Merge
	*
	* @param parseId The Parse id of the user
	* @param authenticationToken The validated token from Parse
	*   (that will be further validated when sent to the bC service)
	* @param callback The method to be invoked when the server response is received
	*
	*/
	void mergeParseIdentity(const FString &parseId, const FString &authenticationToken, IServerCallback *callback = nullptr);

	/*
	* Detach the Google identity from this profile.
	*
	* Service Name - Identity
	* Service Operation - Detach
	*
	* @param parseId The Parse id of the user
	* @param continueAnon Proceed even if the profile will revert to anonymous?
	* @param callback The method to be invoked when the server response is received
	*
	* Watch for DOWNGRADING_TO_ANONYMOUS_ERROR - occurs if you set continueAnon to false, and
	* disconnecting this identity would result in the profile being anonymous (which means that
	* the profile wouldn't be retrievable if the user loses their device)
	*/
	void detachParseIdentity(const FString &parseId, bool continueAnon, IServerCallback *callback = nullptr);

	/**
	* Switch to a Child Profile
	*
	* Service Name - Identity
	* Service Operation - SWITCH_TO_CHILD_PROFILE
	*
	* @param childProfileId The profileId of the child profile to switch to
	* If null and forceCreate is true a new profile will be created
	* @param childGameId The appId of the child game to switch to
	* @param forceCreate Should a new profile be created if it does not exist?
	* @param callback The method to be invoked when the server response is received
	*/
	void switchToChildProfile(const FString &childProfileId, const FString &childGameId, bool forceCreate, IServerCallback *callback = nullptr);

	/**
	* Switches to a child profile of an app when only one profile exists
	* If multiple profiles exist this returns an error
	*
	* Service Name - Identity
	* Service Operation - SWITCH_TO_CHILD_PROFILE
	*
	* @param childGameId The App ID of the child game to switch to
	* @param forceCreate Should a new profile be created if it does not exist?
	* @param callback The method to be invoked when the server response is received
	*/
	void switchToSingletonChildProfile(const FString &childGameId, bool forceCreate, IServerCallback *callback = nullptr);

	/**
	* Switch to a Parent Profile
	*
	* Service Name - Identity
	* Service Operation - SWITCH_TO_PARENT_PROFILE
	*
	* @param parentLevelName The level of the parent to switch to
	* If null and forceCreate is true a new profile will be created
	* @param callback The method to be invoked when the server response is received
	*/
	void switchToParentProfile(const FString &parentLevelName, IServerCallback *callback = nullptr);

	/**
	* Returns a list of all child profiles in child Apps
	*
	* Service Name - Identity
	* Service Operation - GET_CHILD_PROFILES
	*
	* @param includeSummaryData Whether to return the summary friend data along with this call
	* @param callback The method to be invoked when the server response is received
	*/
	void getChildProfiles(bool includeSummaryData, IServerCallback *callback = nullptr);

	/**
	* Retrieve list of identities
	*
	* Service Name - identity
	* Service Operation - GET_IDENTITIES
	*
	* @param callback The method to be invoked when the server response is received
	*/
	void getIdentities(IServerCallback *callback = nullptr);

	/**
	* Retrieve list of expired identities
	*
	* Service Name - identity
	* Service Operation - GET_EXPIRED_IDENTITIES
	*
	* @param callback The method to be invoked when the server response is received
	*/
	void getExpiredIdentities(IServerCallback *callback = nullptr);

	/**
	* Refreshes an identity for this player
	*
	* Service Name - identity
	* Service Operation - REFRESH_IDENTITY
	*
	* @param externalId User ID
	* @param authenticationToken Password or client side token
	* @param authenticationType Type of authentication
	* @param callback The method to be invoked when the server response is received
	*/
	void refreshIdentity(const FString &externalId, const FString &authenticationToken, EBCAuthType authenticationType, IServerCallback *callback = nullptr);

	/**
     * Allows email identity email address to be changed
     *
     * Service Name - identity
     * Service Operation - CHANGE_EMAIL_IDENTITY
     *
     * @param oldEmailAddress Old email address
     * @param password Password for identity
     * @param newEmailAddress New email address
     * @param updateContactEmail Whether to update contact email in profile
     * @param callback The method to be invoked when the server response is received
     */
	void changeEmailIdentity(const FString &oldEmailAddress, const FString &password, const FString &newEmailAddress,
							 bool updateContactEmail, IServerCallback *callback = nullptr);

	/**
	* Attach a new identity to a parent app
	*
	* Service Name - identity
	* Service Operation - ATTACH_PARENT_WITH_IDENTITY
	*
	* @param externalId The users id for the new credentials
	* @param authenticationToken The password/token
	* @param forceCreate Should a new profile be created if it does not exist?
	* @param authenticationType Type of identity
	* @param externalAuthName Optional - if attaching an external identity
	* @param callback The method to be invoked when the server response is received
	*/
	void attachParentWithIdentity(const FString &externalId, const FString &authenticationToken, EBCAuthType authenticationType,
								  const FString &externalAuthName, bool forceCreate, IServerCallback *callback = nullptr);

	/**
	* Detaches parent from this player's profile
	*
	* Service Name - identity
	* Service Operation - DETACH_PARENT
	*
	* @param callback The method to be invoked when the server response is received
	*/
	void detachParent(IServerCallback *callback);

	/**
	* Attaches a peer identity to this player's profile
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
	* @param callback The method to be invoked when the server response is received
	*/
	void attachPeerProfile(const FString &peer, const FString &externalId, const FString &authenticationToken, EBCAuthType authenticationType,
						   const FString &externalAuthName, bool forceCreate, IServerCallback *callback);

	/**
	* Detaches a peer identity from this player's profile
	*
	* Service Name - identity
	* Service Operation - DETACH_PEER
	*
	* @param peer Name of the peer to connect to
	* @param callback The method to be invoked when the server response is received
	*/
	void detachPeer(const FString &peer, IServerCallback *callback);

	/**
	* Returns a list of peer profiles attached to this user
	*
	* Service Name - identity
	* Service Operation - GET_PEER_PROFILES
	*
	* @param callback The method to be invoked when the server response is received
	*/
	void getPeerProfiles(IServerCallback *callback);

	/**
	* Attachs universal id to current profile with no login
	*
	* Service Name - identity
	* Service Operation - ATTACH_NON_LOGIN_UNIVERSAL_ID
	*
	* @param externalId the id connected with 
	* @param callback The method to be invoked when the server response is received
	*/
	void attachNonLoginUniversalId(const FString &externalId, IServerCallback *callback);

	/**
	* update universal id of current profile
	*
	* Service Name - identity
	* Service Operation - UPDATE_UNIVERSAL_ID_LOGIN
	*
	* @param externalId the id connected with 
	* @param callback The method to be invoked when the server response is received
	*/
	void updateUniversalIDLogin(const FString &externalId, IServerCallback *callback);


  private:
	BrainCloudClient *_client = nullptr;

	void attachIdentity(const FString &externalId, const FString &authenticationToken, EBCAuthType authenticationType, IServerCallback *callback = nullptr);
	void mergeIdentity(const FString &externalId, const FString &authenticationToken, EBCAuthType authenticationType, IServerCallback *callback = nullptr);
	void detachIdentity(const FString &externalId, EBCAuthType authenticationType, bool continueAnon, IServerCallback *callback = nullptr);

	void switchToChildProfile(const FString &childProfileId, const FString &childGameId, bool forceCreate, bool forceSingleton, IServerCallback *callback = nullptr);
};
