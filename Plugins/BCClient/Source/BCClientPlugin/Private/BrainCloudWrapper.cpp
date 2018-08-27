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
#include "BrainCloudComms.h"

UBrainCloudWrapper *UBrainCloudWrapper::_instance = nullptr;

UBrainCloudWrapper::UBrainCloudWrapper()
{
    _client = new BrainCloudClient();
}

UBrainCloudWrapper::UBrainCloudWrapper(FString wrapperName)
{
    _client = new BrainCloudClient();
    _wrapperName = wrapperName;
}

UBrainCloudWrapper::UBrainCloudWrapper(BrainCloudClient *client)
{
    _createdWithClient = true;
    _client = client;
}

void UBrainCloudWrapper::BeginDestroy()
{
    Super::BeginDestroy();
    if (_createdWithClient)
        _client = nullptr;
    else
        delete _client;
}

UBrainCloudWrapper *UBrainCloudWrapper::getInstance()
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
        _instance = NewObject<UBrainCloudWrapper>();
    }
    return _instance;
}

void UBrainCloudWrapper::initialize(FString url, FString secretKey, FString appId, FString appVersion)
{
    // initialize the client with our app info
    _client->initialize(url, secretKey, appId, appVersion);

    loadData();
}

void UBrainCloudWrapper::initializeIdentity(bool isAnonymousAuth)
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

void UBrainCloudWrapper::reauthenticate()
{
    // send our saved game info to brainCloud
    // company and game name can be nullptr since they are already set
    initialize(_client->getBrainCloudComms()->GetServerUrl(), _client->getBrainCloudComms()->GetSecretKey(), _client->getAppId(), _client->getAppVersion());
    authenticateAnonymous();
}

// authenticate the player with an anonymous id
void UBrainCloudWrapper::authenticateAnonymous(IServerCallback *callback)
{
    _authenticateCallback = callback;
    initializeIdentity(true);
    _client->getAuthenticationService()->authenticateAnonymous(true, this);
}

void UBrainCloudWrapper::authenticateEmailPassword(FString email, FString password, bool forceCreate, IServerCallback *callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateEmailPassword(email, password, forceCreate, this);
}

void UBrainCloudWrapper::authenticateExternal(FString userid, FString token, FString externalAuthName, bool forceCreate, IServerCallback *callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateExternal(userid, token, externalAuthName, forceCreate, this);
}

void UBrainCloudWrapper::authenticateFacebook(FString fbUserId, FString fbAuthToken, bool forceCreate, IServerCallback *callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateFacebook(fbUserId, fbAuthToken, forceCreate, this);
}

void UBrainCloudWrapper::authenticateGameCenter(FString gameCenterId, bool forceCreate, IServerCallback *callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateGameCenter(gameCenterId, forceCreate, this);
}

void UBrainCloudWrapper::authenticateGoogle(FString userid, FString token, bool forceCreate, IServerCallback *callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateGoogle(userid, token, forceCreate, this);
}

void UBrainCloudWrapper::authenticateSteam(FString userid, FString sessionticket, bool forceCreate, IServerCallback *callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateSteam(userid, sessionticket, forceCreate, this);
}

void UBrainCloudWrapper::authenticateTwitter(FString userid, FString token, FString secret, bool forceCreate, IServerCallback *callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateTwitter(userid, token, secret, forceCreate, this);
}

void UBrainCloudWrapper::authenticateUniversal(FString userid, FString password, bool forceCreate, IServerCallback *callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateUniversal(userid, password, forceCreate, this);
}

void UBrainCloudWrapper::smartSwitchAuthenticateEmailPassword(const FString &in_email, const FString &in_password, bool in_forceCreate, IServerCallback *in_callback)
{
    SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, EBCAuthType::Email, in_email, in_password, in_forceCreate, in_callback);
    getIdentitiesCallback(smartCallback);
}

void UBrainCloudWrapper::smartSwitchAuthenticateExternal(const FString &userid, const FString &token, const FString &externalAuthName, bool in_forceCreate, IServerCallback *in_callback)
{
    SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, EBCAuthType::External, userid, token, externalAuthName, in_forceCreate, in_callback);
    getIdentitiesCallback(smartCallback);
}

void UBrainCloudWrapper::smartSwitchAuthenticateFacebook(const FString &fbUserId, const FString &fbAuthToken, bool in_forceCreate, IServerCallback *in_callback)
{
    SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, EBCAuthType::Facebook, fbUserId, fbAuthToken, in_forceCreate, in_callback);
    getIdentitiesCallback(smartCallback);
}

void UBrainCloudWrapper::smartSwitchAuthenticateGameCenter(const FString &gameCenterId, bool in_forceCreate, IServerCallback *in_callback)
{
    FString emptyToken = TEXT("");
    SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, EBCAuthType::GameCenter, gameCenterId, emptyToken, in_forceCreate, in_callback);
    getIdentitiesCallback(smartCallback);
}

void UBrainCloudWrapper::smartSwitchAuthenticateGoogle(const FString &userid, const FString &token, bool in_forceCreate, IServerCallback *in_callback)
{
    SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, EBCAuthType::Google, userid, token, in_forceCreate, in_callback);
    getIdentitiesCallback(smartCallback);
}

void UBrainCloudWrapper::smartSwitchAuthenticateSteam(const FString &userid, const FString &sessionticket, bool in_forceCreate, IServerCallback *in_callback)
{
    SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, EBCAuthType::Steam, userid, sessionticket, in_forceCreate, in_callback);
    getIdentitiesCallback(smartCallback);
}

void UBrainCloudWrapper::smartSwitchAuthenticateTwitter(const FString &userid, const FString &token, const FString &secret, bool in_forceCreate, IServerCallback *in_callback)
{
    SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, EBCAuthType::Twitter, userid, token, secret, in_forceCreate, in_callback);
    getIdentitiesCallback(smartCallback);
}

void UBrainCloudWrapper::smartSwitchAuthenticateUniversal(const FString &userid, const FString &password, bool in_forceCreate, IServerCallback *in_callback)
{
    SmartSwitchAuthenticateCallback *smartCallback = new SmartSwitchAuthenticateCallback(this, EBCAuthType::Universal, userid, password, in_forceCreate, in_callback);
    getIdentitiesCallback(smartCallback);
}

void UBrainCloudWrapper::getIdentitiesCallback(IServerCallback *success)
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

void UBrainCloudWrapper::reconnect(IServerCallback *callback)
{
    authenticateAnonymous(callback);
}

void UBrainCloudWrapper::runCallbacks()
{
    _client->runCallbacks();
}

void UBrainCloudWrapper::setAlwaysAllowProfileSwitch(bool alwaysAllow)
{
    _alwaysAllowProfileSwitch = alwaysAllow;
}

bool UBrainCloudWrapper::getAlwaysAllowProfileSwitch()
{
    return _alwaysAllowProfileSwitch;
}

void UBrainCloudWrapper::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, FString const &jsonData)
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

void UBrainCloudWrapper::serverError(ServiceName serviceName, ServiceOperation serviceOperation,
                                     int32 statusCode, int32 reasonCode, const FString &message)
{
    if (_authenticateCallback != nullptr)
    {
        _authenticateCallback->serverError(serviceName, serviceOperation, statusCode, reasonCode, message);
    }
}

void UBrainCloudWrapper::loadData()
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

void UBrainCloudWrapper::saveData()
{
    UBrainCloudSave *SaveGameInstance = Cast<UBrainCloudSave>(UGameplayStatics::CreateSaveGameObject(UBrainCloudSave::StaticClass()));
    SaveGameInstance->ProfileId = _client->getAuthenticationService()->getProfileId();
    SaveGameInstance->AnonymousId = _client->getAuthenticationService()->getAnonymousId();
    SaveGameInstance->AuthenticationType = _authenticationType;

    FString slotPrefix = _wrapperName;

    UGameplayStatics::SaveGameToSlot(SaveGameInstance, _wrapperName + SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}
