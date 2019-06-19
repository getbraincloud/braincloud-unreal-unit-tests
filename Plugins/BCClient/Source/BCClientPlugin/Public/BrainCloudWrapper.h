// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IServerCallback.h"

class BrainCloudClient;
#include "BrainCloudClient.h"
#include "BrainCloudAuthentication.h"
#include "BrainCloudLeaderboard.h"
#include "BrainCloudPlayerState.h"
#include "BrainCloudGamification.h"
#include "BrainCloudGlobalEntity.h"
#include "BrainCloudGlobalStatistics.h"
#include "BrainCloudEntity.h"
#include "BrainCloudPlayerStatistics.h"
#include "BrainCloudTime.h"
#include "BrainCloudPlayerStatisticsEvent.h"
#include "BrainCloudProduct.h"
#include "BrainCloudIdentity.h"
#include "BrainCloudEvent.h"
#include "BrainCloudS3Handling.h"
#include "BrainCloudScript.h"
#include "BrainCloudAsyncMatch.h"
#include "BrainCloudFriend.h"
#include "BrainCloudGlobalApp.h"
#include "BrainCloudMatchmaking.h"
#include "BrainCloudOneWayMatch.h"
#include "BrainCloudPlaybackStream.h"
#include "BrainCloudPushNotification.h"
#include "BrainCloudRedemptionCode.h"
#include "BrainCloudDataStream.h"
#include "BrainCloudProfanity.h"
#include "BrainCloudFile.h"
#include "BrainCloudGroup.h"
#include "BrainCloudMail.h"
#include "BrainCloudTournament.h"
#include "BrainCloudPresence.h"
#include "BrainCloudVirtualCurrency.h"
#include "BrainCloudAppStore.h"
#include "BrainCloudRelay.h"
#include "BrainCloudWrapper.generated.h"

class ServiceName;
class ServiceOperation;

/**
 * The UBrainCloudWrapper provides some convenience functionality to developers when they are
 * getting started with the authentication system.
 *
 * By using the wrapper authentication methods, the anonymous and profile ids will be automatically
 * persisted upon successful authentication. When authenticating, any stored anonymous/profile ids will
 * be sent to the server. This strategy is useful when using anonymous authentication.
 */
UCLASS(BlueprintType)
class BCCLIENTPLUGIN_API UBrainCloudWrapper : public UObject, public IServerCallback
{
    GENERATED_BODY()

  public:
    UBrainCloudWrapper();
    UBrainCloudWrapper(FString wrapperName);
    virtual void BeginDestroy() override;

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
     * Method initializes the BrainCloudClient with multiple app/secret
     * Used when needed to switch between child and parent apps
     *
     * @param serverURL The url to the brainCloud server
     * @param appIdSecretMap The map of <appid, secretKey>
     * @param defaultAppId the default app id we start with
     * @param version The app's version
     * @param companyName company name used in the keycheain for storing anonymous and profile ids. Pick anything
     * @param appName app name used in the keychain for storing anonymous and profile ids. Pick anything
     * 
     */
    void initializeWithApps(FString serverUrl, FString appId, TMap<FString, FString> secretMap, FString appVersion, FString companyName, FString appName);

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
    void authenticateAnonymous(IServerCallback *callback = nullptr);

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
    void authenticateEmailPassword(FString email, FString password, bool forceCreate, IServerCallback *callback = nullptr);

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
     * @param callback The method to be invoked when the server response is received
     */
    void authenticateExternal(FString userid, FString token, FString externalAuthName, bool forceCreate, IServerCallback *callback = nullptr);

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
    void authenticateFacebook(FString fbUserId, FString fbAuthToken, bool forceCreate, IServerCallback *callback = nullptr);

    /*
     * Authenticate the user using their Game Center id
     *
     * Service Name - Authenticate
     * Service Operation - Authenticate
     *
     * @param gameCenterId The player's game center id  (use the playerID property from the local GKPlayer object)
     * @param forceCreate Should a new profile be created for this user if the account does not exist?
     * @param callback The method to be invoked when the server response is received
     *
     */
    void authenticateGameCenter(FString gameCenterId, bool forceCreate, IServerCallback *callback = nullptr);

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
     */
    void authenticateGoogle(FString userid, FString token, bool forceCreate, IServerCallback *callback = nullptr);

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
     */
    void authenticateSteam(FString userid, FString sessionticket, bool forceCreate, IServerCallback *callback = nullptr);

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
    void authenticateTwitter(FString userid, FString token, FString secret, bool forceCreate, IServerCallback *callback = nullptr);

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
    void authenticateUniversal(FString userid, FString password, bool forceCreate, IServerCallback *callback = nullptr);

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
     * @param callback The method to be invoked when the server response is received
     */
    void smartSwitchAuthenticateEmailPassword(const FString &email, const FString &password, bool forceCreate, IServerCallback *callback = NULL);

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
     * @param callback The method to be invoked when the server response is received
     */
    void smartSwitchAuthenticateExternal(const FString &userid, const FString &token, const FString &externalAuthName, bool forceCreate, IServerCallback *callback = NULL);

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
     * @param callback The method to be invoked when the server response is received
     *
     */
    void smartSwitchAuthenticateFacebook(const FString &fbUserId, const FString &fbAuthToken, bool forceCreate, IServerCallback *callback = NULL);

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
     * @param callback The method to be invoked when the server response is received
     */
    void smartSwitchAuthenticateGameCenter(const FString &gameCenterId, bool forceCreate, IServerCallback *callback = NULL);

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
     * @param callback The method to be invoked when the server response is received
     */
    void smartSwitchAuthenticateGoogle(const FString &userid, const FString &token, bool forceCreate, IServerCallback *callback = NULL);

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
     * @param callback The method to be invoked when the server response is received
     */
    void smartSwitchAuthenticateSteam(const FString &userid, const FString &sessionticket, bool forceCreate, IServerCallback *callback = NULL);

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
    void smartSwitchAuthenticateTwitter(const FString &userid, const FString &token, const FString &secret, bool forceCreate, IServerCallback *callback = NULL);

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
     * @param callback The method to be invoked when the server response is received
     */
    void smartSwitchAuthenticateUniversal(const FString &userid, const FString &password, bool forceCreate, IServerCallback *callback = NULL);

    /**
    * Reset Email password - Sends a password reset email to the specified address
    *
    * Service Name - Wrapper
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
    void resetEmailPassword(const FString &email, IServerCallback *callback);

    /**
    * Reset Email password with service parameters- Sends a password reset email to the specified address
    *
    * Service Name - Wrapper
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
    void resetEmailPasswordAdvanced(const FString &emailAddress, const FString &in_serviceParams, IServerCallback *callback);

    const FString &getAnonymousId() const;
    const FString &getProfileId() const;
    void setAnonymousId(const FString &anonymousId);
    void setProfileId(const FString &profileId);

    /*
	* Re-authenticates the user with brainCloud
	* 
	* @param callback The method to be invoked when the server response is received
	*
	*/
    void reconnect(IServerCallback *callback = nullptr);

    /**
     * Run callbacks, to be called once per frame from your main thread
     */
    void runCallbacks();

    BrainCloudClient *getClient() { return _client; }

    //Service Getters
    BrainCloudLeaderboard *getLeaderboardService() { return _client->getLeaderboardService(); }
    BrainCloudPlayerState *getPlayerStateService() { return _client->getPlayerStateService(); }
    BrainCloudGamification *getGamificationService() { return _client->getGamificationService(); }
    BrainCloudGlobalEntity *getGlobalEntityService() { return _client->getGlobalEntityService(); }
    BrainCloudGlobalStatistics *getGlobalStatisticsService() { return _client->getGlobalStatisticsService(); }
    BrainCloudEntity *getEntityService() { return _client->getEntityService(); }
    BrainCloudPlayerStatistics *getPlayerStatisticsService() { return _client->getPlayerStatisticsService(); }
    BrainCloudTime *getTimeService() { return _client->getTimeService(); }
    BrainCloudPlayerStatisticsEvent *getPlayerStatisticsEventService() { return _client->getPlayerStatisticsEventService(); }
    BrainCloudProduct *getProductService() { return _client->getProductService(); }
    BrainCloudIdentity *getIdentityService() { return _client->getIdentityService(); }
    BrainCloudEvent *getEventService() { return _client->getEventService(); }
    BrainCloudS3Handling *getS3HandlingService() { return _client->getS3HandlingService(); }
    BrainCloudScript *getScriptService() { return _client->getScriptService(); }
    BrainCloudAsyncMatch *getAsyncMatchService() { return _client->getAsyncMatchService(); }
    BrainCloudFriend *getFriendService() { return _client->getFriendService(); }
    BrainCloudGlobalApp *getGlobalAppService() { return _client->getGlobalAppService(); }
    BrainCloudMatchmaking *getMatchmakingService() { return _client->getMatchmakingService(); }
    BrainCloudOneWayMatch *getOneWayMatchService() { return _client->getOneWayMatchService(); }
    BrainCloudPlaybackStream *getPlaybackStreamService() { return _client->getPlaybackStreamService(); }
    BrainCloudPushNotification *getPushNotificationService() { return _client->getPushNotificationService(); }
    BrainCloudRedemptionCode *getRedemptionCodeService() { return _client->getRedemptionCodeService(); }
    BrainCloudDataStream *getDataStreamService() { return _client->getDataStreamService(); }
    BrainCloudProfanity *getProfanityService() { return _client->getProfanityService(); }
    BrainCloudFile *getFileService() { return _client->getFileService(); }
    BrainCloudGroup *getGroupService() { return _client->getGroupService(); }
    BrainCloudMail *getMailService() { return _client->getMailService(); }
    BrainCloudTournament *getTournamentService() { return _client->getTournamentService(); }
    BrainCloudPresence *getPresenceService() { return _client->getPresenceService(); }
    BrainCloudVirtualCurrency *getVirtualCurrencyService() { return _client->getVirtualCurrencyService(); }
    BrainCloudAppStore *getAppStoreService() { return _client->getAppStoreService(); }
    BrainCloudRTT *getRTTService() { return _client->getRTTService(); }
    BrainCloudLobby *getLobbyService() { return _client->getLobbyService(); }
    BrainCloudChat *getChatService() { return _client->getChatService(); }
    BrainCloudMessaging *getMessagingService() { return _client->getMessagingService(); }
    BrainCloudRelay *getRelayService() { return _client->getRelayService(); }

    /**
     * Returns the instance of the BrainCloudClient.
     * @return The instance of the BrainCloudClient.
     */
    BrainCloudClient *getBCClient() { return _client; }

    /**
     * Returns the stored profile id
     * @return The stored profile id
     */
    FString getStoredProfileId() { return _client->getAuthenticationService()->getProfileId(); }

    /**
     * Sets the stored profile id
     * @param profileId The profile id to set
     */
    void setStoredProfileId(FString profileId)
    {
        _client->getAuthenticationService()->setProfileId(profileId);
        saveData();
    }

    /**
     * Resets the profile id to empty string
     */
    void resetStoredProfileId()
    {
        setStoredProfileId(TEXT(""));
    }

    /**
     * Returns the stored anonymous id
     * @return The stored anonymous id
     */
    const FString getStoredAnonymousId() { return _client->getAuthenticationService()->getAnonymousId(); }

    /**
     * Sets the stored anonymous id
     * @param anonymousId The anonymous id to set
     */
    void setStoredAnonymousId(FString anonymousId)
    {
        _client->getAuthenticationService()->setAnonymousId(anonymousId);
        saveData();
    }

    /**
     * Resets the anonymous id to empty string
     */
    void resetStoredAnonymousId()
    {
        setStoredAnonymousId(TEXT(""));
    }

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

    /**
	* Set the wrapper name
	* @return String used to distinguish saved wrapper data
	*/
    void setWrapperName(FString wrapperName) { _wrapperName = wrapperName; }

    virtual void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, FString const &jsonData);
    virtual void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString &message);

    static FString buildErrorJson(int32 statusCode, int32 reasonCode, const FString &message);
	static FString GetJsonString(TSharedRef<FJsonObject> jsonDataObject);

  protected:
    UBrainCloudWrapper(BrainCloudClient *client);

    void loadData();
    void saveData();

    BrainCloudClient *_client = nullptr;

    FString _lastUrl;
    FString _lastSecretKey;
    FString _lastGameId;
    FString _lastGameVersion;
    FString _company;
    FString _appName;

    FString _authenticationType;

    FString _wrapperName;

    IServerCallback *_authenticateCallback = nullptr;

    bool _alwaysAllowProfileSwitch = true;
    bool _createdWithClient = false;

    void initializeIdentity(bool isAnonymousAuth = false);
    void reauthenticate();
    void getIdentitiesCallback(IServerCallback *success);

    // these methods are not really used
    FString getStoredAuthenticationType() { return _authenticationType; }
    void setStoredAuthenticationType(FString authenticationType)
    {
        _authenticationType = authenticationType;
        saveData();
    }
    void resetStoredAuthenticationType()
    {
        _authenticationType = TEXT("");
        saveData();
    }
};
