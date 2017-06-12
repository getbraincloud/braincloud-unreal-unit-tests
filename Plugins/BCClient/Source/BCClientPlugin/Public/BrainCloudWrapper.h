// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "IServerCallback.h"

class BrainCloudClient;
class ServiceName;
class ServiceOperation;

/**
 * The BrainCloudWrapper provides some convenience functionality to developers when they are
 * getting started with the authentication system.
 *
 * By using the wrapper authentication methods, the anonymous and profile ids will be automatically
 * persisted upon successful authentication. When authenticating, any stored anonymous/profile ids will
 * be sent to the server. This strategy is useful when using anonymous authentication.
 */
class BCCLIENTPLUGIN_API BrainCloudWrapper : public IServerCallback
{
public:

    /**
     * Method returns a singleton instance of the BrainCloudWrapper.
     * @return A singleton instance of the BrainCloudWrapper.
     */
    static BrainCloudWrapper* getInstance();

    /**
     * Method initializes the BrainCloudClient.
     *
     * @param serverURL The url to the brainCloud server
     * @param secretKey The secret key for your app
     * @param appId The app's id
     * @param version The app's version
     */
    void initialize(FString serverUrl, FString secretKey, FString appId, FString version);

    /**
     * Authenticate a user anonymously with brainCloud - used for apps that don't want to bother
     * the user to login, or for users who are sensitive to their privacy
     *
     * Service Name - Authenticate
     * Service Operation - Authenticate
     *
     * @param callback The method to be invoked when the server response is received
     *
     */
    void authenticateAnonymous(IServerCallback * callback = nullptr);

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
     *
     */
    void authenticateEmailPassword(FString email, FString password, bool forceCreate, IServerCallback * callback = nullptr);

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
     *
     * @returns   performs the success callback on success, failure callback on failure
     */
    void authenticateExternal(FString userid, FString token, FString externalAuthName, bool forceCreate, IServerCallback * callback = nullptr);

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
     * @param callback The method to be invoked when the server response is received
     *
     */
    void authenticateFacebook(FString fbUserId, FString fbAuthToken, bool forceCreate, IServerCallback * callback = nullptr);

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
     *
     * @returns   performs the success callback on success, failure callback on failure
     *
     */
    void authenticateGameCenter(FString gameCenterId, bool forceCreate, IServerCallback * callback = nullptr);

    /*
     * Authenticate the user using a google userid(email address) and google authentication token.
     *
     * Service Name - Authenticate
     * Service Operation - Authenticate
     *
     * @param userid  String representation of google+ userid (email)
     * @param token  The authentication token derived via the google apis.
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     * @param callback The method to be invoked when the server response is received
     *
     * @returns   performs the success callback on success, failure callback on failure
     *
     */
    void authenticateGoogle(FString userid, FString token, bool forceCreate, IServerCallback * callback = nullptr);

    /*
     * Authenticate the user using a steam userid and session ticket (without any validation on the userid).
     *
     * Service Name - Authenticate
     * Service Operation - Authenticate
     *
     * @param userid  String representation of 64 bit steam id
     * @param sessionticket  The session ticket of the user (hex encoded)
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     * @param callback The method to be invoked when the server response is received
     *
     * @returns   performs the success callback on success, failure callback on failure
     *
     */
    void authenticateSteam(FString userid, FString sessionticket, bool forceCreate, IServerCallback * callback = nullptr);

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
     *
     * @returns   performs the success callback on success, failure callback on failure
     *
     */
    void authenticateTwitter(FString userid, FString token, FString secret, bool forceCreate, IServerCallback * callback = nullptr);

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
     *
     */
    void authenticateUniversal(FString userid, FString password, bool forceCreate, IServerCallback * callback = nullptr);

	/*
	* Re-authenticates the user with brainCloud
	* 
	* @param callback The method to be invoked when the server response is received
	*
	*/
	void reconnect(IServerCallback * callback = nullptr);

    /**
     * Run callbacks, to be called once per frame from your main thread
     */
    void runCallbacks();

    /**
     * Returns a singleton instance of the BrainCloudClient.
     * @return A singleton instance of the BrainCloudClient.
     */
    static BrainCloudClient* getBC() { return getInstance()->_client; }

    /**
     * Returns a singleton instance of the BrainCloudClient.
     * @return A singleton instance of the BrainCloudClient.
     */
    BrainCloudClient* getBCClient() { return _client; }

    /**
     * Returns the stored profile id
     * @return The stored profile id
     */
    FString getStoredProfileId() { return _profileId; }

    /**
     * Sets the stored profile id
     * @param profileId The profile id to set
     */
    void setStoredProfileId(FString profileId) { _profileId = profileId; saveData(); }

    /**
     * Resets the profile id to empty string
     */
    void resetStoredProfileId() { _profileId = TEXT(""); saveData(); }

    /**
     * Returns the stored anonymous id
     * @return The stored anonymous id
     */
    FString getStoredAnonymousId() { return _anonymousId; }

    /**
     * Sets the stored anonymous id
     * @param anonymousId The anonymous id to set
     */
    void setStoredAnonymousId(FString anonymousId) { _anonymousId = anonymousId; saveData(); }

    /**
     * Resets the anonymous id to empty string
     */
    void resetStoredAnonymousId() { _anonymousId = TEXT(""); saveData(); }

    /**
     * For non-anonymous authentication methods, a profile id will be passed in
     * when this value is set to false. This will generate an error on the server
     * if the profile id passed in does not match the profile associated with the
     * authentication credentials. By default, this value is true.
     *
     * @param alwaysAllow Controls whether the profile id is passed in with
     * non-anonymous authentications.
     */
    void setAlwaysAllowProfileSwitch(bool alwaysAllow);

    /**
     * Returns the value for always allow profile switch
     * @return Whether to always allow profile switches
     */
    bool getAlwaysAllowProfileSwitch();

    virtual void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, FString const & jsonData);
    virtual void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString & message);

protected:
    BrainCloudWrapper();

    void loadData();
    void saveData();

    static BrainCloudWrapper* _instance;
    BrainCloudClient* _client = nullptr;

    FString _profileId;
    FString _anonymousId;
    FString _authenticationType;

    IServerCallback* _authenticateCallback = nullptr;

    FString _lastUrl;
    FString _lastSecretKey;
    FString _lastAppId;
    FString _lastAppVersion;

    bool _alwaysAllowProfileSwitch = true;

    void initializeIdentity(bool isAnonymousAuth = false);
    void reauthenticate();

    // these methods are not really used
    FString getStoredAuthenticationType() { return _authenticationType; }
    void setStoredAuthenticationType(FString authenticationType) { _authenticationType = authenticationType; saveData(); }
    void resetStoredAuthenticationType() { _authenticationType = TEXT(""); saveData(); }
};
