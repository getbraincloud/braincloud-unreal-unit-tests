// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCAuthType.h"

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudAuthentication
{
public:
  BrainCloudAuthentication(BrainCloudClient *client);

  /**
     * Initialize - initializes the identity service with the saved
     * anonymous installation id and most recently used profile id
     *
     * @param profileId The id of the profile id that was most recently used by the app (on this device)
     * @param anonymousId  The anonymous installation id that was generated for this device
     */
  void initialize(const FString &profileId, const FString &anonymousId);

  /**
	* Used to create the anonymous installation id for the brainCloud profile.
	* @returns A unique Anonymous ID
	*/
  FString generateAnonymousId();

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
     * @param forceCreate  Should a new profile be created if it does not exist?
     * @param callback The method to be invoked when the server response is received
     */
  void authenticateAnonymous(bool forceCreate, IServerCallback *callback);

  /*
     * Authenticate the user with brainCloud using their Facebook Credentials
     *
     * Service Name - Authenticate
     * Service Operation - Authenticate
     *
     * @param externalId The facebook id of the user
     * @param authenticationToken The validated token from the Facebook SDK
     *   (that will be further validated when sent to the bC service)
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     * @param callback The method to be invoked when the server response is received
     */
  void authenticateFacebook(const FString &externalId, const FString &authenticationToken, bool forceCreate, IServerCallback *callback);

  /*
     * Authenticate the user using their Game Center id
     *
     * Service Name - Authenticate
     * Service Operation - Authenticate
     *
     * @param gameCenterId The player's game center id  (use the playerID property from the local GKPlayer object)
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     * @param callback The method to be invoked when the server response is received
     */
  void authenticateGameCenter(const FString &gameCenterId, bool forceCreate, IServerCallback *callback);

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
     * @param email  The e-mail address of the user
     * @param password  The password of the user
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     * @param callback The method to be invoked when the server response is received
     */
  void authenticateEmailPassword(const FString &email, const FString &password, bool forceCreate, IServerCallback *callback);

  /*
     * Authenticate the user using a userid and password (without any validation on the userid).
     * Similar to AuthenticateEmailPassword - except that that method has additional features to
     * allow for e-mail validation, password resets, etc.
     *
     * Service Name - Authenticate
     * Service Operation - Authenticate
     *
     * @param email  The e-mail address of the user
     * @param password  The password of the user
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     * @param callback The method to be invoked when the server response is received
     */
  void authenticateUniversal(const FString &userid, const FString &password, bool forceCreate, IServerCallback *callback);

  //UFUNCTION(BlueprintCallable, meta = (HidePin = "callback", DefaultToSelf = "callback"), Category = "BrainCloud|Authentication")
  //  void authenticateUniversal(const FString& userid, const FString& password, bool forceCreate, IServerCallback * callback = nullptr);

  /*
     * Authenticate the user using a steam userid and session ticket (without any validation on the userid).
     *
     * Service Name - Authenticate
     * Service Operation - Authenticate
     *
     * @param userid  String representation of 64 bit steam id
     * @param sessionticket  The session ticket of the user (hex encoded)
     * @param callback The method to be invoked when the server response is received
     */
  void authenticateSteam(const FString &userid, const FString &sessionticket, bool forceCreate, IServerCallback *callback);

  /*
    * Authenticate the user using a google userId and google server authentication code.
    *
    * Service Name - Authenticate
    * Service Operation - Authenticate
    *
    * @param googleUserId String representation of google+ userid (email)
    * @param serverAuthCode  The server authentication token derived via the google apis. Gotten with calls like RequestServerAuthCode
    * @param forceCreate Should a new profile be created for this user if the account does not exist?
    * @param callback The method to be invoked when the server response is received
    */
  void authenticateGoogle(const FString &googleUserId, const FString &serverAuthCode, bool forceCreate, IServerCallback *callback);

    /*
    * Authenticate the user using a google userId and google server authentication code.
    *
    * Service Name - Authenticate
    * Service Operation - Authenticate
    *
    * @param googleUserAccountEmail The email associated with the google user
    * @param IdToken  The Id token of the google account. Can get with calls like requestIdToken
    * @param forceCreate Should a new profile be created for this user if the account does not exist?
    * @param callback The method to be invoked when the server response is received
    */
  void authenticateGoogleOpenId(const FString &googleUserAccountEmail, const FString &IdToken, bool forceCreate, IServerCallback *callback);

    /*
    * Authenticate the user using a google userId and google server authentication code.
    *
    * Service Name - Authenticate
    * Service Operation - Authenticate
    *
    * @param googleUserAccountEmail The email associated with the google user
    * @param IdToken  The Id token of the google account. Can get with calls like requestIdToken
    * @param forceCreate Should a new profile be created for this user if the account does not exist?
    * @param callback The method to be invoked when the server response is received
    */
  void authenticateAppleOpenId(const FString &googleUserAccountEmail, const FString &IdToken, bool forceCreate, IServerCallback *callback);

  /*
    * Authenticate the user using a Twitter userid, authentication token, and secret from Twitter.
    *
    * Service Name - Authenticate
    * Service Operation - Authenticate
    *
    * @param userid  String representation of Twitter userid
    * @param token  The authentication token derived via the Twitter apis.
    * @param secret  The secret given when attempting to link with Twitter
    * @param forceCreate Should a new profile be created for this user if the account does not exist?
    * @param callback The method to be invoked when the server response is received
    */
  void authenticateTwitter(const FString &userid, const FString &token, const FString &secret, bool forceCreate, IServerCallback *callback);

  /*
    * Authenticate the user using a Pase userid and authentication token
    *
    * Service Name - Authenticate
    * Service Operation - Authenticate
    *
    * @param userId String representation of Parse userid
    * @param token The authentication token
    * @param forceCreate Should a new profile be created for this user if the account does not exist?
    * @param callback The method to be invoked when the server response is received
    */
  void authenticateParse(const FString &userid, const FString &token, bool forceCreate, IServerCallback *callback);

  /*
    * Authenticate the user using a handoffId and a token 
    *
    * Service Name - Authenticate
    * Service Operation - Authenticate
    *
    * @param handoffId braincloud handoff id generated from cloud script
    * @param securityToken The security token entered byt the user
    * @param callback The method to be invoked when the server response is received
    */
  void authenticateHandoff(const FString &handoffId, const FString &securityToken, bool forceCreate, IServerCallback *callback);

  /**
    * Authenticate the user via cloud code (which in turn validates the supplied credentials against an external system).
    * This allows the developer to extend brainCloud authentication to support other backend authentication systems.
    *
    * Service Name - Authenticate
    * Server Operation - Authenticate
    *
    * @param userid The user id
    * @param token The user token (password etc)
    * @param externalAuthName The name of the cloud script to call for external authentication
    * @param force Should a new profile be created for this user if the account does not exist?
    */
  void authenticateExternal(const FString &userid, const FString &token, const FString &externalAuthName, bool forceCreate, IServerCallback *callback);

  /**
    * Reset Email password - Sends a password reset email to the specified address
    *
    * Service Name - Authenticate
    * Operation - ResetEmailPassword
    *
    * @param email The email address to send the reset email to.
    * @param callback The method to be invoked when the server response is received
    * @return The JSON returned in the callback is as follows:
    * {
    *   "status": 200,
    *   "data": {}
    * }
    *
    * Note the follow error reason codes:
    *
    * SECURITY_ERROR (40209) - If the email address cannot be found.
    */
  void resetEmailPassword(const FString &in_email, IServerCallback *in_callback);

  /**
    * Reset Email password with service parameters- Sends a password reset email to the specified address
    *
    * Service Name - Authenticate
    * Operation - ResetEmailPasswordAdvanced
    *
    * @param appId the application id
    * @param emailAddress The email address to send the reset email to.
    * @param serviceParams parameters to send to the email service see the doc for a full 
    * list. http://getbraincloud.com/apidocs/apiref/#capi-mail
    * @param callback The method to be invoked when the server response is received
    * @return The JSON returned in the callback is as follows:
    * {
    *   "status": 200,
    *   "data": {}
    * }
    *
    * Note the follow error reason codes:
    *
    * SECURITY_ERROR (40209) - If the email address cannot be found.
    */
  void resetEmailPasswordAdvanced(const FString &in_emailAddress, const FString &in_serviceParams, IServerCallback *in_callback);

  const FString &getAnonymousId() const;
  const FString &getProfileId() const;
  void setAnonymousId(const FString &anonymousId);
  void setProfileId(const FString &profileId);

private:
  BrainCloudClient *_client = nullptr;

  FString _anonymousId;
  FString _profileId;

  void authenticate(const FString &externalId, const FString &authenticationToken, EBCAuthType authenticationType, const FString &externalAuthName, bool forceCreate, IServerCallback *callback);
};