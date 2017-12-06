// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudWrapper.h"

#include "BrainCloudClient.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "OperationParam.h"

#include "BrainCloudSave.h"
#include "Kismet/GameplayStatics.h"

BrainCloudWrapper * BrainCloudWrapper::_instance = nullptr;

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

BrainCloudWrapper * BrainCloudWrapper::getInstance()
{
	if (BrainCloudClient::ENABLED_SINGLETON_MODE == false)
	{
		if (BrainCloudClient::ENABLED_SOFT_ERROR_MODE)
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
    // save the game app in case we need to reauthenticate
    _lastUrl = url;
    _lastSecretKey = secretKey;
    _lastAppId = appId;
    _lastAppVersion = appVersion;

    // initialize the client with our app info
    _client->initialize(url, secretKey, appId, appVersion);

    loadData();
}

void BrainCloudWrapper::initializeIdentity(bool isAnonymousAuth)
{
    // create an anonymous ID if necessary
    if ((!_anonymousId.IsEmpty() && _profileId.IsEmpty()) || _anonymousId.IsEmpty())
    {
        setStoredAnonymousId(_client->getAuthenticationService()->generateAnonymousId());
        setStoredProfileId(TEXT(""));
    }

    FString profileIdToAuthenticateWith = _profileId;
    if (!isAnonymousAuth && _alwaysAllowProfileSwitch)
    {
        profileIdToAuthenticateWith = TEXT("");
    }
    setStoredAuthenticationType(isAnonymousAuth ? OperationParam::AuthenticateServiceAuthenticateAuthAnonymous.getValue() : TEXT(""));

    // send our IDs to brainCloud
    _client->initializeIdentity(profileIdToAuthenticateWith, _anonymousId);
}

void BrainCloudWrapper::reauthenticate()
{
    // send our saved game info to brainCloud
    // company and game name can be nullptr since they are already set
    initialize(_lastUrl, _lastSecretKey, _lastAppId, _lastAppVersion);

    if (_authenticationType == OperationParam::AuthenticateServiceAuthenticateAuthAnonymous.getValue())
    {
        authenticateAnonymous();
    }
}

// authenticate the player with an anonymous id
void BrainCloudWrapper::authenticateAnonymous(IServerCallback * callback)
{
    _authenticateCallback = callback;
    initializeIdentity(true);
    _client->getAuthenticationService()->authenticateAnonymous(true, this);
}

void BrainCloudWrapper::authenticateEmailPassword(FString email, FString password, bool forceCreate, IServerCallback * callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateEmailPassword(email, password, forceCreate, this);
}

void BrainCloudWrapper::authenticateExternal(FString userid, FString token, FString externalAuthName, bool forceCreate, IServerCallback * callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateExternal(userid, token, externalAuthName, forceCreate, this);
}

void BrainCloudWrapper::authenticateFacebook(FString fbUserId, FString fbAuthToken, bool forceCreate, IServerCallback * callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateFacebook(fbUserId, fbAuthToken, forceCreate, this);
}

void BrainCloudWrapper::authenticateGameCenter(FString gameCenterId, bool forceCreate, IServerCallback * callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateGameCenter(gameCenterId, forceCreate, this);
}

void BrainCloudWrapper::authenticateGoogle(FString userid, FString token, bool forceCreate, IServerCallback * callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateGoogle(userid, token, forceCreate, this);
}

void BrainCloudWrapper::authenticateSteam(FString userid, FString sessionticket, bool forceCreate, IServerCallback * callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateSteam(userid, sessionticket, forceCreate, this);
}

void BrainCloudWrapper::authenticateTwitter(FString userid, FString token, FString secret, bool forceCreate, IServerCallback * callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateTwitter(userid, token, secret, forceCreate, this);
}

void BrainCloudWrapper::authenticateUniversal(FString userid, FString password, bool forceCreate, IServerCallback * callback)
{
    _authenticateCallback = callback;
    initializeIdentity();
    _client->getAuthenticationService()->authenticateUniversal(userid, password, forceCreate, this);
}

void BrainCloudWrapper::reconnect(IServerCallback * callback)
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

void BrainCloudWrapper::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, FString const & jsonData)
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
    int32 statusCode, int32 reasonCode, const FString & message)
{
    if (_authenticateCallback != nullptr)
    {
        _authenticateCallback->serverError(serviceName, serviceOperation, statusCode, reasonCode, message);
    }
}

void BrainCloudWrapper::loadData()
{
    UBrainCloudSave* LoadGameInstance = Cast<UBrainCloudSave>(UGameplayStatics::CreateSaveGameObject(UBrainCloudSave::StaticClass()));
    
	FString slotPrefix = _wrapperName;

	LoadGameInstance = Cast<UBrainCloudSave>(UGameplayStatics::LoadGameFromSlot(slotPrefix + LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
    if (LoadGameInstance == nullptr) return;

    _profileId = LoadGameInstance->ProfileId;
    _anonymousId = LoadGameInstance->AnonymousId;
    _authenticationType = LoadGameInstance->AuthenticationType;
}

void BrainCloudWrapper::saveData()
{
    UBrainCloudSave* SaveGameInstance = Cast<UBrainCloudSave>(UGameplayStatics::CreateSaveGameObject(UBrainCloudSave::StaticClass()));
    SaveGameInstance->ProfileId = _profileId;
    SaveGameInstance->AnonymousId = _anonymousId;
    SaveGameInstance->AuthenticationType = _authenticationType;

	FString slotPrefix = _wrapperName;

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, _wrapperName + SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}
