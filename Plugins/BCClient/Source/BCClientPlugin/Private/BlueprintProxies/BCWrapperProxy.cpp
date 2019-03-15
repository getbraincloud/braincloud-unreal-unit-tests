// Copyright 2015 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBrainCloudWrapper *UBCWrapperProxy::DefaultBrainCloudInstance = nullptr;

UBCWrapperProxy::UBCWrapperProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBrainCloudWrapper *UBCWrapperProxy::CreateBrainCloudWrapper(const FString &wrapperName)
{
	UBrainCloudWrapper *wrapper = NewObject<UBrainCloudWrapper>();
	wrapper->setWrapperName(wrapperName);
	return wrapper;
}

void UBCWrapperProxy::SetDefaultBrainCloudInstance(UBrainCloudWrapper *brainCloudWrapper)
{
	ClearDefaultBrainCloudInstance();

	DefaultBrainCloudInstance = brainCloudWrapper;
	DefaultBrainCloudInstance->AddToRoot();
}

void UBCWrapperProxy::ClearDefaultBrainCloudInstance()
{
	if (DefaultBrainCloudInstance != nullptr)
		DefaultBrainCloudInstance->RemoveFromRoot();
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
	// else if (DefaultBrainCloudInstance != nullptr)
	// {
	// 	return DefaultBrainCloudInstance;
	// }
	// else
	// {
    // 	#pragma warning(suppress : 4996)
    // 	return UBrainCloudWrapper::getInstance();
    // }
	else
	{
		return DefaultBrainCloudInstance;
	}
}

void UBCWrapperProxy::SetAlwaysAllowProfileSwitch(UBrainCloudWrapper *brainCloudWrapper, bool alwaysAllow)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->setAlwaysAllowProfileSwitch(alwaysAllow);
}

void UBCWrapperProxy::Initialize(UBrainCloudWrapper *brainCloudWrapper, FString serverUrl, FString secretKey, FString appId, FString version)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->initialize(serverUrl, secretKey, appId, version);
}

void UBCWrapperProxy::InitializeWithApps(UBrainCloudWrapper *brainCloudWrapper, FString serverUrl, FString appId, TMap<FString, FString> secretMap, FString version, FString company, FString appName)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->initializeWithApps(serverUrl, appId, secretMap, version, company, appName);
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

UBCWrapperProxy *UBCWrapperProxy::ResetEmailPassword(UBrainCloudWrapper *brainCloudWrapper, const FString &in_email)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->resetEmailPassword(in_email, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::ResetEmailPasswordAdvanced(UBrainCloudWrapper *brainCloudWrapper, const FString &in_email, const FString &in_serviceParams)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->resetEmailPasswordAdvanced(in_email, in_serviceParams, Proxy);
	return Proxy;
}

void UBCWrapperProxy::SetStoredProfileId(UBrainCloudWrapper *brainCloudWrapper, FString profileId)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->setStoredProfileId(profileId);
}

FString UBCWrapperProxy::GetStoredProfileId(UBrainCloudWrapper *brainCloudWrapper)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getStoredProfileId();
}

void UBCWrapperProxy::SetStoredAnonymousId(UBrainCloudWrapper *brainCloudWrapper, FString anonymousId)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->setStoredAnonymousId(anonymousId);
}

FString UBCWrapperProxy::GetStoredAnonymousId(UBrainCloudWrapper *brainCloudWrapper)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getStoredAnonymousId();
}
