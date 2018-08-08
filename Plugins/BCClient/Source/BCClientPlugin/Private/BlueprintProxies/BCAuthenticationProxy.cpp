// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "ServerCall.h"
#include "BCWrapperProxy.h"
#include "BrainCloudActor.h"
#include "BrainCloudClient.h"
#include "BrainCloudWrapper.h"
#include "BCAuthenticationProxy.h"

UBCAuthenticationProxy::UBCAuthenticationProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UBCAuthenticationProxy::Initialize(UBrainCloudWrapper *brainCloudWrapper, const FString& profileId, const FString& anonymousId)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->initialize(profileId, anonymousId);
}

FString UBCAuthenticationProxy::GenerateAnonymousId(UBrainCloudWrapper *brainCloudWrapper)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->generateAnonymousId();
}

void UBCAuthenticationProxy::ClearSavedProfileId(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->clearSavedProfileId();
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateAnonymous(UBrainCloudWrapper *brainCloudWrapper, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->authenticateAnonymous(forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateFacebook(UBrainCloudWrapper *brainCloudWrapper, FString facebookId, FString password, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->authenticateFacebook(facebookId, password, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateGameCenter(UBrainCloudWrapper *brainCloudWrapper, FString gameCenterId, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->authenticateGameCenter(gameCenterId, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateEmailPassword(UBrainCloudWrapper *brainCloudWrapper, FString email, FString password, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->authenticateEmailPassword(email, password, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateUniversal(UBrainCloudWrapper *brainCloudWrapper, FString userId, FString password, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->authenticateUniversal(userId, password, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateSteam(UBrainCloudWrapper *brainCloudWrapper, FString steamId, FString sessionTicket, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->authenticateSteam(steamId, sessionTicket, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateGoogle(UBrainCloudWrapper *brainCloudWrapper, FString googleId, FString token, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->authenticateGoogle(googleId, token, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateTwitter(UBrainCloudWrapper *brainCloudWrapper, FString twitterId, FString token, FString secret, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->authenticateTwitter(twitterId, token, secret, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateParse(UBrainCloudWrapper *brainCloudWrapper, FString parseId, FString token, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->authenticateParse(parseId, token, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::AuthenticateExternal(UBrainCloudWrapper *brainCloudWrapper, FString userId, FString token, FString externalAuthName, bool forceCreate)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->authenticateExternal(userId, token, externalAuthName, forceCreate, Proxy);
    return Proxy;
}

UBCAuthenticationProxy* UBCAuthenticationProxy::ResetEmailPassword(UBrainCloudWrapper *brainCloudWrapper, const FString& email)
{
    UBCAuthenticationProxy* Proxy = NewObject<UBCAuthenticationProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->resetEmailPassword(email, Proxy);
    return Proxy;
}

//Getters
const FString & UBCAuthenticationProxy::GetAnonymousId(UBrainCloudWrapper *brainCloudWrapper)
{
    return UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->getAnonymousId();
}

const FString & UBCAuthenticationProxy::GetProfileId(UBrainCloudWrapper *brainCloudWrapper)
{
    return UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->getProfileId();
}

//Setters
void UBCAuthenticationProxy::SetAnonymousId(UBrainCloudWrapper *brainCloudWrapper, FString anonymousId)
{
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->setAnonymousId(anonymousId);
}

void UBCAuthenticationProxy::SetProfileId(UBrainCloudWrapper *brainCloudWrapper, FString profileId)
{
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->setProfileId(profileId);
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

