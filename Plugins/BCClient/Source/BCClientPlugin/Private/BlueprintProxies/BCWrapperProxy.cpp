// Copyright 2015 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "ServerCall.h"
#include "BrainCloudActor.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBrainCloudWrapper *UBCWrapperProxy::DefaultBrainCloudInstance = nullptr;

UBCWrapperProxy::UBCWrapperProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

ABrainCloudActor *UBCWrapperProxy::CreateBrainCloudActor(const FString &wrapperName)
{
	ABrainCloudActor *brainCloudActor = NewObject<ABrainCloudActor>(NewObject<UBrainCloudWrapper>());
	brainCloudActor->AddToRoot();
	brainCloudActor->BCWrapper->setWrapperName(wrapperName);
	return brainCloudActor;
}

UBrainCloudWrapper *UBCWrapperProxy::GetBrainCloudWrapper(ABrainCloudActor *brainCloudActor)
{
	return brainCloudActor->BCWrapper;
}


void UBCWrapperProxy::SetDefaultBrainCloudInstance(UBrainCloudWrapper *brainCloudWrapper)
{
	DefaultBrainCloudInstance = brainCloudWrapper;
}

void UBCWrapperProxy::ClearDefaultBrainCloudInstance()
{
	DefaultBrainCloudInstance = nullptr;
}

UBrainCloudWrapper *UBCWrapperProxy::GetBrainCloudInstance(UBrainCloudWrapper *brainCloudWrapper)
{
	// Using a passed in instance of brainCloud
	if (brainCloudWrapper != nullptr)
	{
		return brainCloudWrapper;
	}
	// Using a default state instance of brainCloud
	else if (DefaultBrainCloudInstance != nullptr)
	{
		return DefaultBrainCloudInstance;
	}
	// Using the brainCloud singleton (not recommended)
	else
	{
		return UBrainCloudWrapper::getInstance();
	}
}

UBCWrapperProxy *UBCWrapperProxy::SetAlwaysAllowProfileSwitch(UBrainCloudWrapper *brainCloudWrapper, bool alwaysAllow)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->setAlwaysAllowProfileSwitch(alwaysAllow);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::Initialize(UBrainCloudWrapper *brainCloudWrapper, FString serverUrl, FString secretKey, FString appId, FString version)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->initialize(serverUrl, secretKey, appId, version);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::AuthenticateAnonymous(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->authenticateAnonymous(Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::AuthenticateEmailPassword(UBrainCloudWrapper *brainCloudWrapper, FString email, FString password, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->authenticateEmailPassword(email, password, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::AuthenticateExternal(UBrainCloudWrapper *brainCloudWrapper, FString userid, FString token, FString externalAuthName, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->authenticateExternal(userid, token, externalAuthName, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::AuthenticateFacebook(UBrainCloudWrapper *brainCloudWrapper, FString fbUserId, FString fbAuthToken, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->authenticateFacebook(fbUserId, fbAuthToken, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::AuthenticateGameCenter(UBrainCloudWrapper *brainCloudWrapper, FString gameCenterId, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->authenticateGameCenter(gameCenterId, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::AuthenticateGoogle(UBrainCloudWrapper *brainCloudWrapper, FString userid, FString token, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->authenticateGoogle(userid, token, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::AuthenticateSteam(UBrainCloudWrapper *brainCloudWrapper, FString userid, FString sessionticket, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->authenticateSteam(userid, sessionticket, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::AuthenticateTwitter(UBrainCloudWrapper *brainCloudWrapper, FString userid, FString token, FString secret, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->authenticateTwitter(userid, token, secret, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::AuthenticateUniversal(UBrainCloudWrapper *brainCloudWrapper, FString userid, FString password, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->authenticateUniversal(userid, password, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::SmartSwitchAuthenticateEmailPassword(UBrainCloudWrapper *brainCloudWrapper, const FString &email, const FString &password, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->smartSwitchAuthenticateEmailPassword(email, password, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::SmartSwitchAuthenticateExternal(UBrainCloudWrapper *brainCloudWrapper, const FString &userid, const FString &token, const FString &externalAuthName, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->smartSwitchAuthenticateExternal(userid, token, externalAuthName, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::SmartSwitchAuthenticateFacebook(UBrainCloudWrapper *brainCloudWrapper, const FString &fbUserId, const FString &fbAuthToken, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->smartSwitchAuthenticateFacebook(fbUserId, fbAuthToken, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::SmartSwitchAuthenticateGameCenter(UBrainCloudWrapper *brainCloudWrapper, const FString &gameCenterId, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->smartSwitchAuthenticateGameCenter(gameCenterId, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::SmartSwitchAuthenticateGoogle(UBrainCloudWrapper *brainCloudWrapper, const FString &userid, const FString &token, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->smartSwitchAuthenticateGoogle(userid, token, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::SmartSwitchAuthenticateSteam(UBrainCloudWrapper *brainCloudWrapper, const FString &userid, const FString &sessionticket, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->smartSwitchAuthenticateSteam(userid, sessionticket, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::SmartSwitchAuthenticateTwitter(UBrainCloudWrapper *brainCloudWrapper, const FString &userid, const FString &token, const FString &secret, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->smartSwitchAuthenticateTwitter(userid, token, secret, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::SmartSwitchAuthenticateUniversal(UBrainCloudWrapper *brainCloudWrapper, const FString &userid, const FString &password, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->smartSwitchAuthenticateUniversal(userid, password, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::SetStoredProfileId(UBrainCloudWrapper *brainCloudWrapper, FString profileId)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->setStoredProfileId(profileId);
	return Proxy;
}

FString UBCWrapperProxy::GetStoredProfileId(UBrainCloudWrapper *brainCloudWrapper)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getStoredProfileId();
}

UBCWrapperProxy *UBCWrapperProxy::SetStoredAnonymousId(UBrainCloudWrapper *brainCloudWrapper, FString anonymousId)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->setStoredAnonymousId(anonymousId);
	return Proxy;
}

FString UBCWrapperProxy::GetStoredAnonymousId(UBrainCloudWrapper *brainCloudWrapper)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getStoredAnonymousId();
}

//callbacks
void UBCWrapperProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString &jsonData)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
	OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCWrapperProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString &jsonError)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
	OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}
