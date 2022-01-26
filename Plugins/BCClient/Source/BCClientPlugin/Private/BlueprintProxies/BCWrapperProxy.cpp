// Copyright 2015 bitHeads, Inc. All Rights Reserved.

#include "BCWrapperProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "ServerCall.h"

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
	else if (DefaultBrainCloudInstance != nullptr)
	{
		return DefaultBrainCloudInstance;
	}
	// nullptr! wrapper isn't set!
	else
	{
		return nullptr;
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

UBCWrapperProxy *UBCWrapperProxy::AuthenticateFacebookLimited(UBrainCloudWrapper *brainCloudWrapper, FString fbLimitedUserId, FString fbAuthToken, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->authenticateFacebookLimited(fbLimitedUserId, fbAuthToken, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::AuthenticateOculus(UBrainCloudWrapper *brainCloudWrapper, FString oculusUserId, FString oculusNonce, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->authenticateOculus(oculusUserId, oculusNonce, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::AuthenticatePlaystationNetwork(UBrainCloudWrapper *brainCloudWrapper, FString psnAccountId, FString psnAuthToken, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->authenticatePlaystationNetwork(psnAccountId, psnAuthToken, forceCreate, Proxy);
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

UBCWrapperProxy *UBCWrapperProxy::AuthenticateGoogleOpenId(UBrainCloudWrapper *brainCloudWrapper, FString googleUserAccountEmail, FString IdToken, bool forceCreate)
{
    UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->authenticateGoogleOpenId(googleUserAccountEmail, IdToken, forceCreate, Proxy);
    return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::AuthenticateApple(UBrainCloudWrapper *brainCloudWrapper, FString appleUserId, FString identityToken, bool forceCreate)
{
    UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->authenticateApple(appleUserId, identityToken, forceCreate, Proxy);
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

UBCWrapperProxy *UBCWrapperProxy::AuthenticateHandoff(UBrainCloudWrapper *brainCloudWrapper, FString handoffId, FString securityToken, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->authenticateHandoff(handoffId, securityToken, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::AuthenticateSettopHandoff(UBrainCloudWrapper *brainCloudWrapper, FString handoffCode)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->authenticateSettopHandoff(handoffCode, Proxy);
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

UBCWrapperProxy *UBCWrapperProxy::SmartSwitchAuthenticateFacebookLimited(UBrainCloudWrapper *brainCloudWrapper, const FString &fbLimitedUserId, const FString &fbAuthToken, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->smartSwitchAuthenticateFacebookLimited(fbLimitedUserId, fbAuthToken, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::SmartSwitchAuthenticateOculus(UBrainCloudWrapper *brainCloudWrapper, const FString &oculusUserId, const FString &oculusNonce, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->smartSwitchAuthenticateOculus(oculusUserId, oculusNonce, forceCreate, Proxy);
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

UBCWrapperProxy *UBCWrapperProxy::SmartSwitchAuthenticateGoogleOpenId(UBrainCloudWrapper *brainCloudWrapper, const FString &googleUserAccountEmail, const FString &IdToken, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->smartSwitchAuthenticateGoogleOpenId(googleUserAccountEmail, IdToken, forceCreate, Proxy);
	return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::SmartSwitchAuthenticateApple(UBrainCloudWrapper *brainCloudWrapper, const FString &appleUserId, const FString &identityToken, bool forceCreate)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->smartSwitchAuthenticateGoogleOpenId(appleUserId, identityToken, forceCreate, Proxy);
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

UBCWrapperProxy* UBCWrapperProxy::SmartSwitchAuthenticateAdvanced(UBrainCloudWrapper* brainCloudWrapper, EBCAuthType in_authenticationType,
	const FAuthenticateAdvancedIds& in_ids, bool in_forceCreate, const FString& in_extraJson)
{
	UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
	GetBrainCloudInstance(brainCloudWrapper)->authenticateAdvanced(in_authenticationType, in_ids, in_forceCreate, in_extraJson, Proxy);
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
/////////////////////////
UBCWrapperProxy *UBCWrapperProxy::ResetEmailPasswordWithExpiry(UBrainCloudWrapper *brainCloudWrapper, const FString &email, int32 in_tokenTtlInMinutes)
{
    UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->resetEmailPasswordWithExpiry(email, in_tokenTtlInMinutes, Proxy);
    return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::ResetEmailPasswordAdvancedWithExpiry(UBrainCloudWrapper *brainCloudWrapper, const FString &email, const FString &in_serviceParams, int32 in_tokenTtlInMinutes)
{
    UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->resetEmailPasswordAdvancedWithExpiry(email, in_serviceParams, in_tokenTtlInMinutes, Proxy);
    return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::ResetUniversalIdPassword(UBrainCloudWrapper *brainCloudWrapper, const FString &in_universalId)
{
    UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->resetUniversalIdPassword(in_universalId, Proxy);
    return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::ResetUniversalIdPasswordAdvanced(UBrainCloudWrapper *brainCloudWrapper, const FString &in_universalId, const FString &in_serviceParams)
{
    UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->resetUniversalIdPasswordAdvanced(in_universalId, in_serviceParams, Proxy);
    return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::ResetUniversalIdPasswordWithExpiry(UBrainCloudWrapper *brainCloudWrapper, const FString &in_universalId, int32 in_tokenTtlInMinutes)
{
    UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->resetUniversalIdPasswordWithExpiry(in_universalId, in_tokenTtlInMinutes, Proxy);
    return Proxy;
}

UBCWrapperProxy *UBCWrapperProxy::ResetUniversalIdPasswordAdvancedWithExpiry(UBrainCloudWrapper *brainCloudWrapper, const FString &in_universalId, const FString &in_serviceParams, int32 in_tokenTtlInMinutes)
{
    UBCWrapperProxy *Proxy = NewObject<UBCWrapperProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getClient()->getAuthenticationService()->resetUniversalIdPasswordAdvancedWithExpiry(in_universalId, in_serviceParams, in_tokenTtlInMinutes, Proxy);
    return Proxy;
}
/////////////////////////

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
