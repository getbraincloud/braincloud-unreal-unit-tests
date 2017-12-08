// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "ServerCall.h"
#include "BCWrapperProxy.h"
#include "BrainCloud.h"
#include "BrainCloudClient.h"
#include "BrainCloudWrapper.h"
#include "BCAuthenticationProxy.h"

UBCAuthenticationProxy::UBCAuthenticationProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UBCAuthenticationProxy::Initialize(ABrainCloud *brainCloud, const FString& profileId, const FString& anonymousId)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getClient()->getAuthenticationService()->initialize(profileId, anonymousId);
}

FString UBCAuthenticationProxy::GenerateAnonymousId(ABrainCloud *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getClient()->getAuthenticationService()->generateAnonymousId();
}

void UBCAuthenticationProxy::ClearSavedProfileId(ABrainCloud *brainCloud)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getClient()->getAuthenticationService()->clearSavedProfileId();
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateAnonymous(ABrainCloud *brainCloud, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getClient()->getAuthenticationService()->authenticateAnonymous(forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateFacebook(ABrainCloud *brainCloud, FString facebookId, FString password, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getClient()->getAuthenticationService()->authenticateFacebook(facebookId, password, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateGameCenter(ABrainCloud *brainCloud, FString gameCenterId, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getClient()->getAuthenticationService()->authenticateGameCenter(gameCenterId, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateEmailPassword(ABrainCloud *brainCloud, FString email, FString password, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getClient()->getAuthenticationService()->authenticateEmailPassword(email, password, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateUniversal(ABrainCloud *brainCloud, FString userId, FString password, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getClient()->getAuthenticationService()->authenticateUniversal(userId, password, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateSteam(ABrainCloud *brainCloud, FString steamId, FString sessionTicket, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getClient()->getAuthenticationService()->authenticateSteam(steamId, sessionTicket, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateGoogle(ABrainCloud *brainCloud, FString googleId, FString token, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getClient()->getAuthenticationService()->authenticateGoogle(googleId, token, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateTwitter(ABrainCloud *brainCloud, FString twitterId, FString token, FString secret, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getClient()->getAuthenticationService()->authenticateTwitter(twitterId, token, secret, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateParse(ABrainCloud *brainCloud, FString parseId, FString token, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getClient()->getAuthenticationService()->authenticateParse(parseId, token, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateExternal(ABrainCloud *brainCloud, FString userId, FString token, FString externalAuthName, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getClient()->getAuthenticationService()->authenticateExternal(userId, token, externalAuthName, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::ResetEmailPassword(ABrainCloud *brainCloud, const FString& email)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getClient()->getAuthenticationService()->resetEmailPassword(email, Proxy);
    return Proxy;
}

//Getters
const FString & UBCAuthenticationProxy::GetAnonymousId(ABrainCloud *brainCloud)
{
    return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getClient()->getAuthenticationService()->getAnonymousId();
}

const FString & UBCAuthenticationProxy::GetProfileId(ABrainCloud *brainCloud)
{
    return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getClient()->getAuthenticationService()->getProfileId();
}

//Setters
void UBCAuthenticationProxy::SetAnonymousId(ABrainCloud *brainCloud, FString anonymousId)
{
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getClient()->getAuthenticationService()->setAnonymousId(anonymousId);
}

void UBCAuthenticationProxy::SetProfileId(ABrainCloud *brainCloud, FString profileId)
{
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getClient()->getAuthenticationService()->setProfileId(profileId);
}

//callbacks
void UBCAuthenticationProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCAuthenticationProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

