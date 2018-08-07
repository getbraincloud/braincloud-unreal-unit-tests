// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudWrapper.h"

#include "BCAuthType.h"
#include "BrainCloudClient.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "OperationParam.h"

#include "BrainCloudSave.h"
#include "Kismet/GameplayStatics.h"

#include "SmartSwitchAuthenticateCallback.h"

BrainCloudWrapper *BrainCloudWrapper::_instance = nullptr;

BrainCloudWrapper::BrainCloudWrapper()
{
    _client = new BrainCloudClient();
}

BrainCloudWrapper::BrainCloudWrapper(FString wrapperName)
{
    _client = new BrainCloudClient();
    _wrapperName = wrapperName;
}

BrainCloudWrapper::BrainCloudWrapper(BrainCloudClient *client)
{
    _client = client;
}

BrainCloudWrapper *BrainCloudWrapper::getInstance()
{
    if (BrainCloudClient::EnableSingletonMode == false)
    {
        if (BrainCloudClient::EnableSoftErrorMode)
        {
            UE_LOG(LogTemp, Warning, TEXT("%s"), BrainCloudClient::SINGLETON_USE_ERROR_MESSAGE);
        }
        else
        {
            UE_LOG(LogTemp, Fatal, TEXT("%s"), BrainCloudClient::SINGLETON_USE_ERROR_MESSAGE);
        }
    }

    if (_instance == nullptr)
    {
        _instance = new BrainCloudWrapper();
    }
    return _instance;
}

void BrainCloudWrapper::initialize(FString url, FString secretKey, FString appId, FString appVersion)
{
    // initialize the client with our app info
    _client->initialize(url, secretKey, appId, appVersion);

    loadData();
}

void BrainCloudWrapper::initializeIdentity(bool isAnonymousAuth)
{
    // create an anonymous ID if necessary
    FString profileId = getStoredProfileId();
    FString anonId = getStoredAnonymousId();

    if ((!anonId.IsEmpty() && profileId.IsEmpty()) || anonId.IsEmpty())
    {
        setStoredAnonymousId(_client->getAuthenticationService()->generateAnonymousId());
        setStoredProfileId(TEXT(""));
    }

    if (!isAnonymousAuth && _alwaysAllowProfileSwitch)
    {
        profileId = TEXT("");
    }
    setStoredAuthenticationType(isAnonymousAuth ? OperationParam::AuthenticateServiceAuthenticateAuthAnonymous.getValue() : TEXT(""));

    // send our IDs to brainCloud
    _client->initializeIdentity(profileId, anonId);
}

void BrainCloudWrapper::reauthenticate()
{
    // send our saved game info to brainCloud
    // company and game name can be nullptr since they are already set
    initialize(_client->getBrainCloudComms()->GetServerUrl(), _client->getBrainCloudComms()->GetSecretKey(), _client->getAppId(), _client->getAppVersion());
    authenticateAnonymous();
}

// authenticate the player with an anonymous id
void BrainCloudWrapper::authenticateAnonymous(IServerCallback *callback)
{
    _authenticateCallback = callback;
    initializeIdentity(true);
    _client->getAuthenticationService()->authenticateAnonymous(true, this);
}

void BrainCloudWrapper::authenticateEmailPassword(FString email, FString password, bool forceCreate, IServerCallback *callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateEmailPassword(email, password, forceCreate, this);
}

void BrainCloudWrapper::authenticateExternal(FString userid, FString token, FString externalAuthName, bool forceCreate, IServerCallback *callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateExternal(userid, token, externalAuthName, forceCreate, this);
}

void BrainCloudWrapper::authenticateFacebook(FString fbUserId, FString fbAuthToken, bool forceCreate, IServerCallback *callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateFacebook(fbUserId, fbAuthToken, forceCreate, this);
}

void BrainCloudWrapper::authenticateGameCenter(FString gameCenterId, bool forceCreate, IServerCallback *callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateGameCenter(gameCenterId, forceCreate, this);
}

void BrainCloudWrapper::authenticateGoogle(FString userid, FString token, bool forceCreate, IServerCallback *callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateGoogle(userid, token, forceCreate, this);
}

void BrainCloudWrapper::authenticateSteam(FString userid, FString sessionticket, bool forceCreate, IServerCallback *callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateSteam(userid, sessionticket, forceCreate, this);
}

void BrainCloudWrapper::authenticateTwitter(FString userid, FString token, FString secret, bool forceCreate, IServerCallback *callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateTwitter(userid, token, secret, forceCreate, this);
}

void BrainCloudWrapper::authenticateUniversal(FString userid, FString password, bool forceCreate, IServerCallback *callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateUniversal(userid, password, forceCreate, this);
}

void BrainCloudWrapper::smartSwitchAuthenticateEmailPassword(const FString &in_email, const FString &in_password, bool in_forceCreate, IServerCallback *in_callback)
{
    SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, EBCAuthType::Email, in_email, in_password, in_forceCreate, in_callback);
    getIdentitiesCallback(smartCallback);
}

void BrainCloudWrapper::smartSwitchAuthenticateExternal(const FString &userid, const FString &token, const FString &externalAuthName, bool in_forceCreate, IServerCallback *in_callback)
{
    SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, EBCAuthType::External, userid, token, externalAuthName, in_forceCreate, in_callback);
    getIdentitiesCallback(smartCallback);
}

void BrainCloudWrapper::smartSwitchAuthenticateFacebook(const FString &fbUserId, const FString &fbAuthToken, bool in_forceCreate, IServerCallback *in_callback)
{
    SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, EBCAuthType::Facebook, fbUserId, fbAuthToken, in_forceCreate, in_callback);
    getIdentitiesCallback(smartCallback);
}

void BrainCloudWrapper::smartSwitchAuthenticateGameCenter(const FString &gameCenterId, bool in_forceCreate, IServerCallback *in_callback)
{
    FString emptyToken = TEXT("");
    SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, EBCAuthType::GameCenter, gameCenterId, emptyToken, in_forceCreate, in_callback);
    getIdentitiesCallback(smartCallback);
}

void BrainCloudWrapper::smartSwitchAuthenticateGoogle(const FString &userid, const FString &token, bool in_forceCreate, IServerCallback *in_callback)
{
    SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, EBCAuthType::Google, userid, token, in_forceCreate, in_callback);
    getIdentitiesCallback(smartCallback);
}

void BrainCloudWrapper::smartSwitchAuthenticateSteam(const FString &userid, const FString &sessionticket, bool in_forceCreate, IServerCallback *in_callback)
{
    SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, EBCAuthType::Steam, userid, sessionticket, in_forceCreate, in_callback);
    getIdentitiesCallback(smartCallback);
}

void BrainCloudWrapper::smartSwitchAuthenticateTwitter(const FString &userid, const FString &token, const FString &secret, bool in_forceCreate, IServerCallback *in_callback)
{
    SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, EBCAuthType::Twitter, userid, token, secret, in_forceCreate, in_callback);
    getIdentitiesCallback(smartCallback);
}

void BrainCloudWrapper::smartSwitchAuthenticateUniversal(const FString &userid, const FString &password, bool in_forceCreate, IServerCallback *in_callback)
{
    SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, EBCAuthType::Universal, userid, password, in_forceCreate, in_callback);
    getIdentitiesCallback(smartCallback);
}

void BrainCloudWrapper::getIdentitiesCallback(IServerCallback *success)
{
    BCIdentityCallback *identityCallback = new BCIdentityCallback(this, success);
    if (_client->isAuthenticated())
    {
        _client->getIdentityService()->getIdentities(identityCallback);
    }
    else
    {
        success->serverCallback(ServiceName::AuthenticateV2, ServiceOperation::Authenticate, "");
    }
}

void BrainCloudWrapper::reconnect(IServerCallback *callback)
{
    authenticateAnonymous(callback);
}

void BrainCloudWrapper::runCallbacks()
{
    _client->runCallbacks();
}

void BrainCloudWrapper::setAlwaysAllowProfileSwitch(bool alwaysAllow)
{
    _alwaysAllowProfileSwitch = alwaysAllow;
}

bool BrainCloudWrapper::getAlwaysAllowProfileSwitch()
{
    return _alwaysAllowProfileSwitch;
}

void BrainCloudWrapper::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, FString const &jsonData)
{
    if (serviceName == ServiceName::AuthenticateV2 && serviceOperation == ServiceOperation::Authenticate)
    {
        FString profileId = TEXT("");
        TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(jsonData);
        TSharedPtr<FJsonObject> jsonPacket = MakeShareable(new FJsonObject());
        bool res = FJsonSerializer::Deserialize(reader, jsonPacket);

        if (res)
        {
            TSharedPtr<FJsonObject> data = jsonPacket->GetObjectField(TEXT("data"));
            profileId = data->GetStringField(TEXT("profileId"));
        }

        if (profileId != TEXT(""))
        {
            setStoredProfileId(profileId);
        }
    }

    if (_authenticateCallback != nullptr)
    {
        _authenticateCallback->serverCallback(serviceName, serviceOperation, jsonData);
    }
}

void BrainCloudWrapper::serverError(ServiceName serviceName, ServiceOperation serviceOperation,
                                    int32 statusCode, int32 reasonCode, const FString &message)
{
    if (_authenticateCallback != nullptr)
    {
        _authenticateCallback->serverError(serviceName, serviceOperation, statusCode, reasonCode, message);
    }
}

void BrainCloudWrapper::loadData()
{
    UBrainCloudSave *LoadGameInstance = Cast<UBrainCloudSave>(UGameplayStatics::CreateSaveGameObject(UBrainCloudSave::StaticClass()));

    FString slotPrefix = _wrapperName;
    FString slotName = slotPrefix + LoadGameInstance->SaveSlotName;

    LoadGameInstance = Cast<UBrainCloudSave>(UGameplayStatics::LoadGameFromSlot(slotName, LoadGameInstance->UserIndex));
    if (LoadGameInstance == nullptr)
        return;

    _client->getAuthenticationService()->setProfileId(LoadGameInstance->ProfileId);
    _client->getAuthenticationService()->setAnonymousId(LoadGameInstance->AnonymousId);
    _authenticationType = LoadGameInstance->AuthenticationType;
}

void BrainCloudWrapper::saveData()
{
    UBrainCloudSave *SaveGameInstance = Cast<UBrainCloudSave>(UGameplayStatics::CreateSaveGameObject(UBrainCloudSave::StaticClass()));
    SaveGameInstance->ProfileId = _client->getAuthenticationService()->getProfileId();
    SaveGameInstance->AnonymousId = _client->getAuthenticationService()->getAnonymousId();
    SaveGameInstance->AuthenticationType = _authenticationType;

    FString slotPrefix = _wrapperName;

    UGameplayStatics::SaveGameToSlot(SaveGameInstance, _wrapperName + SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}
