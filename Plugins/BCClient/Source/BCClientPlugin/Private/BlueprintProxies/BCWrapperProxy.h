// Copyright 2015 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCAuthType.h"
#include "BCBlueprintCallProxyBase.h"
#include "BrainCloudACL.h"

#include "BCWrapperProxy.generated.h"

class UBrainCloudWrapper;

UCLASS(BlueprintType)
class UBCWrapperProxy : public UBCBlueprintCallProxyBase
{
  GENERATED_BODY()

public:
  static UBrainCloudWrapper *DefaultBrainCloudInstance;
  UBCWrapperProxy(const FObjectInitializer &ObjectInitializer);

  /**
	* Create an actor that contains its own instance of the brainCloud Wrapper
	*
	* @param brainCloud - The brainCloud Wrapper
	*/
  UFUNCTION(BlueprintCallable, Category = "BrainCloud")
  static UBrainCloudWrapper *CreateBrainCloudWrapper(const FString &wrapperName);

  /**
	* Set a default brainCloud instance to be used when none is provided.
	* @param brainCloud - The brainCloud Wrapper
	*/
  UFUNCTION(BlueprintCallable, Category = "BrainCloud")
  static void SetDefaultBrainCloudInstance(UBrainCloudWrapper *brainCloudWrapper);

  /**
	* Clear the default brainCloud instance
	* When not set, the brainCloud Singleton will be used
	*/
  UFUNCTION(BlueprintCallable, Category = "BrainCloud")
  static void ClearDefaultBrainCloudInstance();
  /**
     * For non-anonymous authentication methods, a profile id will be passed in
     * when this value is set to false. This will generate an error on the server
     * if the profile id passed in does not match the profile associated with the
     * authentication credentials. By default, this value is true.
     *
     * @param alwaysAllow Controls whether the profile id is passed in with
     * non-anonymous authentications.
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static void SetAlwaysAllowProfileSwitch(UBrainCloudWrapper *brainCloudWrapper, bool alwaysAllow);

  /**
     * Method initializes the BrainCloudClient.
     *
     * @param serverURL The url to the brainCloud server
     * @param secretKey The secret key for your app
     * @param appId The app's id
     * @param version The app's version
     */
  UFUNCTION(BlueprintCallable, Category = "BrainCloud|Wrapper")
  static void Initialize(UBrainCloudWrapper *brainCloudWrapper, FString serverUrl, FString secretKey, FString appId, FString version);

  /**
     * Method initializes the BrainCloudClient.
     *
     * @param serverURL The url to the brainCloud server
     * @param secretMap The map of appID to secret
     * @param appId The app's id
     * @param version The app's version
     */
  UFUNCTION(BlueprintCallable, Category = "BrainCloud|Wrapper")
  static void InitializeWithApps(UBrainCloudWrapper *brainCloudWrapper, FString serverUrl, FString appId, TMap<FString, FString> secretMap, FString version, FString company, FString appName);

  /**
     * Authenticate a user anonymously with brainCloud
     *
     * Service Name - Authenticate
     * Service Operation - Authenticate
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *AuthenticateAnonymous(UBrainCloudWrapper *brainCloudWrapper);

  /*
     * Authenticate the user with a custom Email and Password.  
     *
     * Note that the password sent from the client to the server is protected via SSL.
     *
     * Service Name - Authenticate
     * Service Operation - Authenticate
     *
     * @param email  The e-mail address of the user
     * @param password  The password of the user
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *AuthenticateEmailPassword(UBrainCloudWrapper *brainCloudWrapper, FString email, FString password, bool forceCreate);

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
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *AuthenticateExternal(UBrainCloudWrapper *brainCloudWrapper, FString userid, FString token, FString externalAuthName, bool forceCreate);

  /*
     * Authenticate the user with brainCloud using their Facebook Credentials
     *
     * Service Name - Authenticate
     * Service Operation - Authenticate
     *
     * @param fbUserId The facebook id of the user
     * @param fbAuthToken The validated token from the Facebook SDK
     *   (that will be further validated when sent to the bC service)
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *AuthenticateFacebook(UBrainCloudWrapper *brainCloudWrapper, FString fbUserId, FString fbAuthToken, bool forceCreate);

    /*
     * Authenticate the user with brainCloud using their FacebookLimited Credentials
     *
     * Service Name - Authenticate
     * Service Operation - Authenticate
     *
     * @param fbUserId The facebookLimited id of the user
     * @param fbAuthToken The validated token from the Facebook SDK
     *   (that will be further validated when sent to the bC service)
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *AuthenticateFacebookLimited(UBrainCloudWrapper *brainCloudWrapper, FString fbLimitedUserId, FString fbAuthToken, bool forceCreate);

   /*
     * Authenticate the user with brainCloud using their Oculus Credentials
     *
     * Service Name - Authenticate
     * Service Operation - Authenticate
     *
     * @param oculusUserId The oculus id of the user
     * @param oculusNonce token from the Oculus SDK
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *AuthenticateOculus(UBrainCloudWrapper *brainCloudWrapper, FString oculusUserId, FString oculusNonce, bool forceCreate);


  /*
     * Authenticate the user with brainCloud using their psn account Id and auth token
     *
     * Service Name - Authenticate
     * Service Operation - Authenticate
     *
     * @param psnAccountId The account id of the user
     * @param psnAuthToken The validated token from the Playstation SDK
     *   (that will be further validated when sent to the bC service)
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *AuthenticatePlaystationNetwork(UBrainCloudWrapper *brainCloudWrapper, FString psnAccountId, FString psnAuthToken, bool forceCreate);


  /*
     * Authenticate the user using their Game Center id
     *
     * Service Name - Authenticate
     * Service Operation - Authenticate
     *
     * @param gameCenterId The player's game center id  (use the playerID property from the local GKPlayer object)
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     * @param success The method to call in event of successful login
     * @param failure The method to call in the event of an error during authentication
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *AuthenticateGameCenter(UBrainCloudWrapper *brainCloudWrapper, FString gameCenterId, bool forceCreate);

  /*
     * Authenticate the user using a google userid(email address) and google authentication token.
     *
     * Service Name - Authenticate
     * Service Operation - Authenticate
     *
     * @param userid  String representation of google+ userid (email)
     * @param token  The authentication token derived via the google apis.
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *AuthenticateGoogle(UBrainCloudWrapper *brainCloudWrapper, FString userid, FString token, bool forceCreate);

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
   UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
   static UBCWrapperProxy *AuthenticateGoogleOpenId(UBrainCloudWrapper *brainCloudWrapper, FString googleUserAccountEmail, FString IdToken, bool forceCreate);

    /*
    * Authenticate the user using a google userId and google server authentication code.
    *
    * Service Name - Authenticate
    * Service Operation - Authenticate
    *
    * @param appleUserId this can be user id OR the email of the user account
    * @param identityToken  the token confirming the user's identity
    * @param forceCreate Should a new profile be created for this user if the account does not exist?
    * @param callback The method to be invoked when the server response is received
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *AuthenticateApple(UBrainCloudWrapper *brainCloudWrapper, FString appleUserId, FString identityToken, bool forceCreate);

  /*
     * Authenticate the user using a steam userid and session ticket (without any validation on the userid).
     *
     * Service Name - Authenticate
     * Service Operation - Authenticate
     *
     * @param userid  String representation of 64 bit steam id
     * @param sessionticket  The session ticket of the user (hex encoded)
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *AuthenticateSteam(UBrainCloudWrapper *brainCloudWrapper, FString userid, FString sessionticket, bool forceCreate);

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
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *AuthenticateTwitter(UBrainCloudWrapper *brainCloudWrapper, FString userid, FString token, FString secret, bool forceCreate);

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
     *
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *AuthenticateUniversal(UBrainCloudWrapper *brainCloudWrapper, FString userid, FString password, bool forceCreate);

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
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
    static UBCWrapperProxy *AuthenticateHandoff(UBrainCloudWrapper *brainCloudWrapper, FString handoffId, FString securityToken, bool forceCreate);

        /*
    * Authenticate the user using a handoffId and a token 
    *
    * Service Name - Authenticate
    * Service Operation - Authenticate
    *
    * @param handoffCode braincloud handoff id generated from cloud script
    * @param securityToken The security token entered byt the user
    * @param callback The method to be invoked when the server response is received
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
    static UBCWrapperProxy *AuthenticateSettopHandoff(UBrainCloudWrapper *brainCloudWrapper, FString handoffCode);


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
     * @param email  The e-mail address of the user
     * @param password  The password of the user
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *SmartSwitchAuthenticateEmailPassword(UBrainCloudWrapper *brainCloudWrapper, const FString &email, const FString &password, bool forceCreate);

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
     * @param userid The user id
     * @param token The user token (password etc)
     * @param externalAuthName The name of the cloud script to call for external authentication
     * @param force Should a new profile be created for this user if the account does not exist?
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *SmartSwitchAuthenticateExternal(UBrainCloudWrapper *brainCloudWrapper, const FString &userid, const FString &token, const FString &externalAuthName, bool forceCreate);

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
     * @param fbUserId The facebook id of the user
     * @param fbAuthToken The validated token from the Facebook SDK
     *   (that will be further validated when sent to the bC service)
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     *
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *SmartSwitchAuthenticateFacebook(UBrainCloudWrapper *brainCloudWrapper, const FString &fbUserId, const FString &fbAuthToken, bool forceCreate);

    /*
     * Smart Switch Authenticate will logout of the current profile, and switch to the new authentication type.
     * In event the current session was previously an anonymous account, the smart switch will delete that profile.
     * Use this function to keep a clean designflow from anonymous to signed profiles
     *
     * Authenticate the user with brainCloud using their FacebookLIMITED Credentials
     *
     * Service Name - Authenticate
     * Service Operation - Authenticate
     *
     * @param fbUserId The facebooklIMITED id of the user
     * @param fbAuthToken The validated token from the Facebook SDK
     *   (that will be further validated when sent to the bC service)
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     *
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *SmartSwitchAuthenticateFacebookLimited(UBrainCloudWrapper *brainCloudWrapper, const FString &fbLimitedUserId, const FString &fbAuthToken, bool forceCreate);

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
     * @param oculusUserId The Oculus id of the user
     * @param oculusNonce token from the Oculus SDK
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     *
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *SmartSwitchAuthenticateOculus(UBrainCloudWrapper *brainCloudWrapper, const FString &oculusUserId, const FString &oculusNonce, bool forceCreate);


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
     * @param gameCenterId The player's game center id  (use the playerID property from the local GKPlayer object)
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *SmartSwitchAuthenticateGameCenter(UBrainCloudWrapper *brainCloudWrapper, const FString &gameCenterId, bool forceCreate);

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
     * @param userid  String representation of google+ userid (email)
     * @param token  The authentication token derived via the google apis.
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *SmartSwitchAuthenticateGoogle(UBrainCloudWrapper *brainCloudWrapper, const FString &userid, const FString &token, bool forceCreate);

    /*
    * Smart Switch Authenticate will logout of the current profile, and switch to the new authentication type.
    * In event the current session was previously an anonymous account, the smart switch will delete that profile.
    * Use this function to keep a clean designflow from anonymous to signed profiles
    *
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
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *SmartSwitchAuthenticateGoogleOpenId(UBrainCloudWrapper *brainCloudWrapper, const FString &googleUserAccountEmail, const FString &IdToken, bool forceCreate);

    /*
    * Smart Switch Authenticate will logout of the current profile, and switch to the new authentication type.
    * In event the current session was previously an anonymous account, the smart switch will delete that profile.
    * Use this function to keep a clean designflow from anonymous to signed profiles
    * Authenticate the user using a google userId and google server authentication code.
    *
    * Service Name - Authenticate
    * Service Operation - Authenticate
    *
    * @param appleUserId this can be user id OR the email of the user account
    * @param identityToken  the token confirming the user's identity
    * @param forceCreate Should a new profile be created for this user if the account does not exist?
    * @param callback The method to be invoked when the server response is received
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *SmartSwitchAuthenticateApple(UBrainCloudWrapper *brainCloudWrapper, const FString &appleUserId, const FString &identityToken, bool forceCreate);

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
     * @param userid  String representation of 64 bit steam id
     * @param sessionticket  The session ticket of the user (hex encoded)
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *SmartSwitchAuthenticateSteam(UBrainCloudWrapper *brainCloudWrapper, const FString &userid, const FString &sessionticket, bool forceCreate);

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
     * @param userid  String representation of Twitter userid
     * @param token  The authentication token derived via the Twitter apis.
     * @param secret  The secret given when attempting to link with Twitter
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     * @param callback The method to be invoked when the server response is received
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *SmartSwitchAuthenticateTwitter(UBrainCloudWrapper *brainCloudWrapper, const FString &userid, const FString &token, const FString &secret, bool forceCreate);

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
     * @param email  The e-mail address of the user
     * @param password  The password of the user
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *SmartSwitchAuthenticateUniversal(UBrainCloudWrapper *brainCloudWrapper, const FString &userid, const FString &password, bool forceCreate);

   /*
    * Smart Switch Authenticate will logout of the current profile, and switch to the new authentication type.
    * In event the current session was previously an anonymous account, the smart switch will delete that profile.
    * Use this function to keep a clean design flow from anonymous to signed profiles
    *
    * A generic Authenticate method that translates to the same as calling a specific one, except it takes an extraJson
    * that will be passed along to pre- or post- hooks.
    *
    * Service Name - Authenticate
    * Service Operation - Authenticate
    *
    * @param in_authenticationType Universal, Email, Facebook, etc
    * @param in_ids Auth IDs structure
    * @param in_forceCreate Should a new profile be created for this user if the account does not exist?
    * @param in_extraJson Additional to piggyback along with the call, to be picked up by pre- or post- hooks. Leave empty string for no extraJson.
    * @param in_callback The method to be invoked when the server response is received
    */
   UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
   static UBCWrapperProxy *SmartSwitchAuthenticateAdvanced(UBrainCloudWrapper *brainCloudWrapper, EBCAuthType in_authenticationType, const FAuthenticateAdvancedIds& in_ids, bool in_forceCreate, const FString& in_extraJson);
  /**
    * Reset Email password - Sends a password reset email to the specified address
    *
    * Service Name - Authenticate
    * Operation - ResetEmailPassword
    *
    * Param - externalId The email address to send the reset email to.
    * Param - callback The method to be invoked when the server response is received
    *
    * Note the follow error reason codes:
    * SECURITY_ERROR (40209) - If the email address cannot be found.
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
  static UBCWrapperProxy *ResetEmailPassword(UBrainCloudWrapper *brainCloudWrapper, const FString &email);

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
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
    static UBCWrapperProxy *ResetEmailPasswordAdvanced(UBrainCloudWrapper *brainCloudWrapper, const FString &email, const FString &serviceParams);

  /**
    * Reset Email password with a token expiry - Sends a password reset email to the specified address
    *
    * Service Name - Authenticate
    * Operation - ResetEmailPassword
    *
    * @param email The email address to send the reset email to.
    * @param in_tokenTtlInMinutes the token expiry value
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
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
    static UBCWrapperProxy *ResetEmailPasswordWithExpiry(UBrainCloudWrapper *brainCloudWrapper, const FString &email, int32 in_tokenTtlInMinutes);

    /**
    * Reset Email password with service parameters with token expiry- Sends a password reset email to the specified address
    *
    * Service Name - Authenticate
    * Operation - ResetEmailPasswordAdvanced
    *
    * @param appId the application id
    * @param emailAddress The email address to send the reset email to.
    * @param serviceParams parameters to send to the email service see the doc for a full 
    * @param in_tokenTtlInMinutes the expiry token value
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
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
    static UBCWrapperProxy *ResetEmailPasswordAdvancedWithExpiry(UBrainCloudWrapper *brainCloudWrapper, const FString &email, const FString &in_serviceParams, int32 in_tokenTtlInMinutes);

    /**
    * Reset Universal Id password with service parameters 
    *
    * Service Name - Authenticate
    * Operation - ResetEmailPasswordAdvanced
    *
    * @param appId the application id
    * @param universalId The email address to send the reset email to.
    * @param in_tokenTtlInMinutes the expiry token value
    * list. http://getbraincloud.com/apidocs/apiref/#capi-mail
    * @param callback The method to be invoked when the server response is received
    * @return The JSON returned in the callback is as follows:
    * {
    *   "status": 200,
    *   "data": {}
    * }
    *
    */ 
     UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
    static UBCWrapperProxy *ResetUniversalIdPassword(UBrainCloudWrapper *brainCloudWrapper, const FString &in_universalId);
    
    /**
    * Reset Universal Id password with service parameters 
    *
    * Service Name - Authenticate
    * Operation - ResetEmailPasswordAdvanced
    *
    * @param appId the application id
    * @param universalId The email address to send the reset email to.
    * @param serviceParams parameters to send to the email service see the doc for a full 
    * list. http://getbraincloud.com/apidocs/apiref/#capi-mail
    * @param callback The method to be invoked when the server response is received
    * @return The JSON returned in the callback is as follows:
    * {
    *   "status": 200,
    *   "data": {}
    * }
    *
    */ 
     UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
    static UBCWrapperProxy *ResetUniversalIdPasswordAdvanced(UBrainCloudWrapper *brainCloudWrapper, const FString &in_universalId, const FString &in_serviceParams);
   
    /**
    * Reset Universal Id password with service parameters and with expiry
    *
    * Service Name - Authenticate
    * Operation - ResetEmailPasswordAdvanced
    *
    * @param appId the application id
    * @param universalId The email address to send the reset email to.
    * @param in_tokenTtlInMinutes the expiry token value
    * list. http://getbraincloud.com/apidocs/apiref/#capi-mail
    * @param callback The method to be invoked when the server response is received
    * @return The JSON returned in the callback is as follows:
    * {
    *   "status": 200,
    *   "data": {}
    * }
    *
    */ 
     UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
    static UBCWrapperProxy *ResetUniversalIdPasswordWithExpiry(UBrainCloudWrapper *brainCloudWrapper, const FString &in_universalId, int32 in_tokenTtlInMinutes);
   
      /**
    * Reset Universal Id password with service parameters and with expiry 
    *
    * Service Name - Authenticate
    * Operation - ResetEmailPasswordAdvanced
    *
    * @param appId the application id
    * @param universalId The email address to send the reset email to.
    * @param in_tokenTtlInMinutes the expiry token value
    * @param serviceParams parameters to send to the email service see the doc for a full 
    * list. http://getbraincloud.com/apidocs/apiref/#capi-mail
    * @param callback The method to be invoked when the server response is received
    * @return The JSON returned in the callback is as follows:
    * {
    *   "status": 200,
    *   "data": {}
    * }
    *
    */ 
     UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Wrapper")
    static UBCWrapperProxy *ResetUniversalIdPasswordAdvancedWithExpiry(UBrainCloudWrapper *brainCloudWrapper, const FString &in_universalId, const FString &in_serviceParams, int32 in_tokenTtlInMinutes);


  /**
     * Sets the stored profile id, saves it as well
     * @param profileId The profile id to set
     */
  UFUNCTION(BlueprintCallable, Category = "BrainCloud|Wrapper")
  static void SetStoredProfileId(UBrainCloudWrapper *brainCloudWrapper, FString profileId);

  /**
     * Returns the stored anonymous id
     * @return The stored anonymous id
     */
  UFUNCTION(BlueprintCallable, Category = "BrainCloud|Wrapper")
  static FString GetStoredProfileId(UBrainCloudWrapper *brainCloudWrapper);

  /**
     * Sets the stored anonymous id, saves it as well
     * @param anonymousId The anonymous id to set
     */
  UFUNCTION(BlueprintCallable, Category = "BrainCloud|Wrapper")
  static void SetStoredAnonymousId(UBrainCloudWrapper *brainCloudWrapper, FString anonymousId);

  /**
     * Returns the stored anonymous id
     * @return The stored anonymous id
     */
  UFUNCTION(BlueprintCallable, Category = "BrainCloud|Wrapper")
  static FString GetStoredAnonymousId(UBrainCloudWrapper *brainCloudWrapper);

  /**
	* Returns a non null reference to brainCloud
	*
	* @param brainCloud - An actor that contains its own instance of the brainCloud Wrapper
	*/
  static UBrainCloudWrapper *GetBrainCloudInstance(UBrainCloudWrapper *brainCloud);
};
