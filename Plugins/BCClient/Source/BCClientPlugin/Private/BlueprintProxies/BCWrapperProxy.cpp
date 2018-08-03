// Copyright 2015 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "ServerCall.h"
#include "BrainCloudActor.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

ABrainCloudActor *UBCWrapperProxy::DefaultBrainCloudInstance = nullptr;

UBCWrapperProxy::UBCWrapperProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

ABrainCloudActor *UBCWrapperProxy::CreateBrainCloudActor(const FString &wrapperName)
{
	ABrainCloudActor *brainCloudActor = NewObject<ABrainCloudActor>(ABrainCloudActor::StaticClass());
	brainCloudActor->AddToRoot();
	brainCloudActor->BCWrapper->setWrapperName(wrapperName);
	return brainCloudActor;
}

void UBCWrapperProxy::SetDefaultBrainCloudInstance(ABrainCloudActor *brainCloud)
{
	DefaultBrainCloudInstance = brainCloud;
}

void UBCWrapperProxy::ClearDefaultBrainCloudInstance()
{
	DefaultBrainCloudInstance = nullptr;
}

BrainCloudWrapper *UBCWrapperProxy::GetBrainCloudInstance(ABrainCloudActor *brainCloud)
{
	// Using a passed in instance of brainCloud
	if (brainCloud != nullptr)
	{
		return brainCloud->BCWrapper;
	}
	// Using a default state instance of brainCloud
	else if (DefaultBrainCloudInstance != nullptr)
	{
		return DefaultBrainCloudInstance->BCWrapper;
	}
	// Using the brainCloud singleton (not recommended)
	else
	{
		return BrainCloudWrapper::getInstance();
	}
}

UBCWrapperProxy *UBCWrapperProxy::SetAlwaysAllowProfileSwitch(ABrainCloudActor *brainCloud, bool alwaysAllow)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->setAlwaysAllowProfileSwitch(alwaysAllow);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::Initialize(ABrainCloudActor *brainCloud, FString serverUrl, FString secretKey, FString appId, FString version)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->initialize(serverUrl, secretKey, appId, version);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::AuthenticateAnonymous(ABrainCloudActor *brainCloud)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->authenticateAnonymous(Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::AuthenticateEmailPassword(ABrainCloudActor *brainCloud, FString email, FString password, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->authenticateEmailPassword(email, password, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::AuthenticateExternal(ABrainCloudActor *brainCloud, FString userid, FString token, FString externalAuthName, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->authenticateExternal(userid, token, externalAuthName, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::AuthenticateFacebook(ABrainCloudActor *brainCloud, FString fbUserId, FString fbAuthToken, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->authenticateFacebook(fbUserId, fbAuthToken, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::AuthenticateGameCenter(ABrainCloudActor *brainCloud, FString gameCenterId, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->authenticateGameCenter(gameCenterId, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::AuthenticateGoogle(ABrainCloudActor *brainCloud, FString userid, FString token, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->authenticateGoogle(userid, token, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::AuthenticateSteam(ABrainCloudActor *brainCloud, FString userid, FString sessionticket, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->authenticateSteam(userid, sessionticket, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::AuthenticateTwitter(ABrainCloudActor *brainCloud, FString userid, FString token, FString secret, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->authenticateTwitter(userid, token, secret, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::AuthenticateUniversal(ABrainCloudActor *brainCloud, FString userid, FString password, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->authenticateUniversal(userid, password, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::SetStoredProfileId(ABrainCloudActor *brainCloud, FString profileId)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->setStoredProfileId(profileId);
	return Proxy;
}

FString UBCWrapperProxy::GetStoredProfileId(ABrainCloudActor *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getStoredProfileId();
}

UBCWrapperProxy *UBCWrapperProxy::SetStoredAnonymousId(ABrainCloudActor *brainCloud, FString anonymousId)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->setStoredAnonymousId(anonymousId);
	return Proxy;
}

FString UBCWrapperProxy::GetStoredAnonymousId(ABrainCloudActor *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getStoredAnonymousId();
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
