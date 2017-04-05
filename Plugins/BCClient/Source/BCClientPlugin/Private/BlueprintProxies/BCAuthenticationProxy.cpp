// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCAuthenticationProxy.h"

UBCAuthenticationProxy::UBCAuthenticationProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UBCAuthenticationProxy::Initialize(const FString& profileId, const FString& anonymousId)
{
    return BrainCloudClient::getInstance()->getAuthenticationService()->initialize(profileId, anonymousId);
}

FString UBCAuthenticationProxy::GenerateAnonymousId()
{
	return BrainCloudClient::getInstance()->getAuthenticationService()->generateAnonymousId();
}

void UBCAuthenticationProxy::ClearSavedProfileId()
{
    BrainCloudClient::getInstance()->getAuthenticationService()->clearSavedProfileId();
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateAnonymous(bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
    BrainCloudClient::getInstance()->getAuthenticationService()->authenticateAnonymous(forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateFacebook(FString facebookId, FString password, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
    BrainCloudClient::getInstance()->getAuthenticationService()->authenticateFacebook(facebookId, password, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateGameCenter(FString gameCenterId, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
    BrainCloudClient::getInstance()->getAuthenticationService()->authenticateGameCenter(gameCenterId, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateEmailPassword(FString email, FString password, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
    BrainCloudClient::getInstance()->getAuthenticationService()->authenticateEmailPassword(email, password, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateUniversal(FString userId, FString password, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
    BrainCloudClient::getInstance()->getAuthenticationService()->authenticateUniversal(userId, password, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateSteam(FString steamId, FString sessionTicket, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
    BrainCloudClient::getInstance()->getAuthenticationService()->authenticateSteam(steamId, sessionTicket, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateGoogle(FString googleId, FString token, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
    BrainCloudClient::getInstance()->getAuthenticationService()->authenticateGoogle(googleId, token, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateTwitter(FString twitterId, FString token, FString secret, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
    BrainCloudClient::getInstance()->getAuthenticationService()->authenticateTwitter(twitterId, token, secret, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateParse(FString parseId, FString token, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
    BrainCloudClient::getInstance()->getAuthenticationService()->authenticateParse(parseId, token, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateExternal(FString userId, FString token, FString externalAuthName, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
    BrainCloudClient::getInstance()->getAuthenticationService()->authenticateExternal(userId, token, externalAuthName, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::ResetEmailPassword(const FString& email)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
    BrainCloudClient::getInstance()->getAuthenticationService()->resetEmailPassword(email, Proxy);
    return Proxy;
}

//Getters
const FString & UBCAuthenticationProxy::GetAnonymousId()
{
    return BrainCloudClient::getInstance()->getAuthenticationService()->getAnonymousId();
}

const FString & UBCAuthenticationProxy::GetProfileId()
{
    return BrainCloudClient::getInstance()->getAuthenticationService()->getProfileId();
}

//Setters
void UBCAuthenticationProxy::SetAnonymousId(FString anonymousId)
{
    BrainCloudClient::getInstance()->getAuthenticationService()->setAnonymousId(anonymousId);
}

void UBCAuthenticationProxy::SetProfileId(FString profileId)
{
    BrainCloudClient::getInstance()->getAuthenticationService()->setProfileId(profileId);
}

//callbacks
void UBCAuthenticationProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
}

void UBCAuthenticationProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
}

