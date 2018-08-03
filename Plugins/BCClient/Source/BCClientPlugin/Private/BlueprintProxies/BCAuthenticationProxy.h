// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"

#include "BCAuthenticationProxy.generated.h"

class ABrainCloud;

UCLASS(MinimalAPI)
class UBCAuthenticationProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
    GENERATED_BODY()

public:
    UBCAuthenticationProxy(const FObjectInitializer& ObjectInitializer);

    /**
    * Initializes the identity service with the saved
    * anonymous installation id and most recently used profile id
    * @param anonymousId - The anonymous installation id that was generated for this device
    * @param profileId - The id of the profile id that was most recently used by the app (on this device)
    */
    UFUNCTION(BlueprintCallable, Category = "BrainCloud|Authentication")
        static void Initialize(ABrainCloudActor *brainCloud, const FString& profileId, const FString& anonymousId);

	/**
	* Used to create the anonymous installation id for the brainCloud profile.
	* Returns - A unique Anonymous ID
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Authentication")
		static FString GenerateAnonymousId(ABrainCloudActor *brainCloud);

    /**
    * Used to clear the saved profile id - to use in cases when the user is
    * attempting to switch to a different game profile.
    */
    UFUNCTION(BlueprintCallable, Category = "BrainCloud|Authentication")
        static void ClearSavedProfileId(ABrainCloudActor *brainCloud);

    /**
    * Authenticate a user anonymously with brainCloud - used for apps that don't want to bother
    * the user to login, or for users who are sensitive to their privacy
    *
    * Service Name - Authenticate
    * Service Operation - Authenticate
    *
    * Param - forceCreate  Should a new profile be created if it does not exist?
    */
    UFUNCTION(BlueprintCallable, Category = "BrainCloud|Authentication")
        static UBCAuthenticationProxy* AuthenticateAnonymous(ABrainCloudActor *brainCloud, bool forceCreate);

    /*
    * Authenticate the user with brainCloud using their Facebook Credentials
    *
    * Service Name - Authenticate
    * Service Operation - Authenticate
    *
    * Param - externalId The facebook id of the user
    * Param - authenticationToken The validated token from the Facebook SDK
    *   (that will be further validated when sent to the bC service)
    * Param - forceCreate Should a new profile be created for this user if the account does not exist?
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Authentication")
        static UBCAuthenticationProxy* AuthenticateFacebook(ABrainCloudActor *brainCloud, FString facebookId, FString password, bool forceCreate);

    /*
    * Authenticate the user using their Game Center id
    *
    * Service Name - Authenticate
    * Service Operation - Authenticate
    *
    * Param - gameCenterId The player's game center id  (use the playerID property from the local GKPlayer object)
    * Param - forceCreate Should a new profile be created for this user if the account does not exist?
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Authentication")
        static UBCAuthenticationProxy* AuthenticateGameCenter(ABrainCloudActor *brainCloud, FString gameCenterId, bool forceCreate);

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
    * Param - email  The e-mail address of the user
    * Param - password  The password of the user
    * Param - forceCreate Should a new profile be created for this user if the account does not exist?
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Authentication")
        static UBCAuthenticationProxy* AuthenticateEmailPassword(ABrainCloudActor *brainCloud, FString email, FString password, bool forceCreate);

    /*
    * Authenticate the user using a userid and password (without any validation on the userid).
    * Similar to AuthenticateEmailPassword - except that that method has additional features to
    * allow for e-mail validation, password resets, etc.
    *
    * Service Name - Authenticate
    * Service Operation - Authenticate
    *
    * Param - email  The e-mail address of the user
    * Param - password  The password of the user
    * Param - forceCreate Should a new profile be created for this user if the account does not exist?
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Authentication")
        static UBCAuthenticationProxy* AuthenticateUniversal(ABrainCloudActor *brainCloud, FString userId, FString password, bool forceCreate);

    /*
    * Authenticate the user using a steam userid and session ticket (without any validation on the userid).
    *
    * Service Name - Authenticate
    * Service Operation - Authenticate
    *
    * Param - userid  String representation of 64 bit steam id
    * Param - sessionticket  The session ticket of the user (hex encoded)
    * Param - forceCreate Should a new profile be created for this user if the account does not exist?
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Authentication")
        static UBCAuthenticationProxy* AuthenticateSteam(ABrainCloudActor *brainCloud, FString steamId, FString sessionTicket, bool forceCreate);

    /*
    * Authenticate the user using a google userid(email address) and google authentication token.
    *
    * Service Name - Authenticate
    * Service Operation - Authenticate
    *
    * Param - userid  String representation of google+ userid (email)
    * Param - token  The authentication token derived via the google apis.
    * Param - forceCreate Should a new profile be created for this user if the account does not exist?
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Authentication")
        static UBCAuthenticationProxy* AuthenticateGoogle(ABrainCloudActor *brainCloud, FString googleId, FString token, bool forceCreate);

    /*
    * Authenticate the user using a Twitter userid, authentication token, and secret from Twitter.
    *
    * Service Name - Authenticate
    * Service Operation - Authenticate
    *
    * Param - userid  String representation of Twitter userid
    * Param - token  The authentication token derived via the Twitter apis.
    * Param - secret  The secret given when attempting to link with Twitter
    * Param - forceCreate Should a new profile be created for this user if the account does not exist?
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Authentication")
        static UBCAuthenticationProxy* AuthenticateTwitter(ABrainCloudActor *brainCloud, FString twitterId, FString token, FString secret, bool forceCreate);

    /*
    * Authenticate the user using a Parse ID and authentication token.
    *
    * Service Name - Authenticate
    * Service Operation - Authenticate
    *
    * Param - userid  String representation of Parse user ID
    * Param - token  The authentication token from Parse
    * Param - forceCreate Should a new profile be created for this user if the account does not exist?
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Authentication")
        static UBCAuthenticationProxy* AuthenticateParse(ABrainCloudActor *brainCloud, FString parseId, FString token, bool forceCreate);

    /**
    * Authenticate the user via cloud code (which in turn validates the supplied credentials against an external system).
    * This allows the developer to extend brainCloud authentication to support other backend authentication systems.
    *
    * Service Name - Authenticate
    * Server Operation - Authenticate
    *
    * Param - userid The user id
    * Param - token The user token (password etc)
    * Param - externalAuthName The name of the cloud script to call for external authentication
    * Param - force Should a new profile be created for this user if the account does not exist?
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Authentication")
        static UBCAuthenticationProxy* AuthenticateExternal(ABrainCloudActor *brainCloud, FString userId, FString token, FString externalAuthName, bool forceCreate);

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
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Authentication")
        static UBCAuthenticationProxy* ResetEmailPassword(ABrainCloudActor *brainCloud, const FString& email);

    //Getters
    UFUNCTION(BlueprintCallable, Category = "BrainCloud|Authentication")
        static const FString & GetAnonymousId(ABrainCloudActor *brainCloud);

    UFUNCTION(BlueprintCallable, Category = "BrainCloud|Authentication")
        static const FString & GetProfileId(ABrainCloudActor *brainCloud);

    //Setters
    UFUNCTION(BlueprintCallable, Category = "BrainCloud|Authentication")
        static void SetAnonymousId(ABrainCloudActor *brainCloud, FString anonymousId);

    UFUNCTION(BlueprintCallable, Category = "BrainCloud|Authentication")
        static void SetProfileId(ABrainCloudActor *brainCloud, FString profileId);

    //Response delegates
    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnFailure;

protected:
    // IServerCallback interface
    void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
    void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
    // End of IServerCallback interface
};
