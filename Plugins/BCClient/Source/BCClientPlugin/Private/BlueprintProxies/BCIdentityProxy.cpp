// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCIdentityProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCIdentityProxy::UBCIdentityProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCIdentityProxy *UBCIdentityProxy::AttachBlockchainIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &blockchainConfig, const FString &publicKey)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->attachBlockchainIdentity(blockchainConfig, publicKey, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::DetachBlockchainIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &blockchainConfig)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->detachBlockchainIdentity(blockchainConfig, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::AttachFacebookIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &facebookId, const FString &authenticationToken)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->attachFacebookIdentity(facebookId, authenticationToken, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::MergeFacebookIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &facebookId, const FString &authenticationToken)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->mergeFacebookIdentity(facebookId, authenticationToken, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::DetachFacebookIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &facebookId, bool continueAnon)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->detachFacebookIdentity(facebookId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::AttachFacebookLimitedIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &facebookLimitedId, const FString &authenticationToken)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->attachFacebookLimitedIdentity(facebookLimitedId, authenticationToken, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::MergeFacebookLimitedIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &facebookLimitedId, const FString &authenticationToken)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->mergeFacebookLimitedIdentity(facebookLimitedId, authenticationToken, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::DetachFacebookLimitedIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &facebookLimitedId, bool continueAnon)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->detachFacebookLimitedIdentity(facebookLimitedId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::AttachOculusIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &oculusId, const FString &oculusNonce)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->attachOculusIdentity(oculusId, oculusNonce, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::MergeOculusIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &oculusId, const FString &oculusNonce)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->mergeOculusIdentity(oculusId, oculusNonce, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::DetachOculusIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &oculusId, bool continueAnon)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->detachOculusIdentity(oculusId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::AttachPlaystationNetworkIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &psnAccountId, const FString &authenticationToken)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->attachPlaystationNetworkIdentity(psnAccountId, authenticationToken, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::MergePlaystationNetworkIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &psnAccountId, const FString &authenticationToken)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->mergePlaystationNetworkIdentity(psnAccountId, authenticationToken, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::DetachPlaystationNetworkIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &psnAccountId, bool continueAnon)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->detachPlaystationNetworkIdentity(psnAccountId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::AttachGameCenterIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &gameCenterId)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->attachGameCenterIdentity(gameCenterId, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::MergeGameCenterIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &gameCenterId)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->mergeGameCenterIdentity(gameCenterId, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::DetachGameCenterIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &gameCenterId, bool continueAnon)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->detachGameCenterIdentity(gameCenterId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::AttachEmailIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &email, const FString &password)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->attachEmailIdentity(email, password, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::MergeEmailIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &email, const FString &password)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->mergeEmailIdentity(email, password, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::DetachEmailIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &email, bool continueAnon)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->detachEmailIdentity(email, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::AttachUniversalIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &userId, const FString &password)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->attachUniversalIdentity(userId, password, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::MergeUniversalIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &userId, const FString &password)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->mergeUniversalIdentity(userId, password, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::DetachUniversalIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &userId, bool continueAnon)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->detachUniversalIdentity(userId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::AttachSteamIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &steamId, const FString &sessionTicket)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->attachSteamIdentity(steamId, sessionTicket, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::MergeSteamIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &steamId, const FString &sessionTicket)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->mergeSteamIdentity(steamId, sessionTicket, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::DetachSteamIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &steamId, bool continueAnon)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->detachSteamIdentity(steamId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::AttachGoogleIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &googleUserId, const FString &serverAuthCode)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->attachGoogleIdentity(googleUserId, serverAuthCode, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::MergeGoogleIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &googleUserId, const FString &serverAuthCode)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->mergeGoogleIdentity(googleUserId, serverAuthCode, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::DetachGoogleIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &googleUserId, bool continueAnon)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->detachGoogleIdentity(googleUserId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::AttachGoogleOpenIdIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &googleUserAccountEmail, const FString &IdToken)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->attachGoogleOpenIdIdentity(googleUserAccountEmail, IdToken, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::MergeGoogleOpenIdIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &googleUserAccountEmail, const FString &IdToken)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->mergeGoogleOpenIdIdentity(googleUserAccountEmail, IdToken, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::DetachGoogleOpenIdIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &googleUserAccountEmail, bool continueAnon)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->detachGoogleOpenIdIdentity(googleUserAccountEmail, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::AttachAppleIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &appleUserId, const FString &identityToken)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->attachAppleIdentity(appleUserId, identityToken, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::MergeAppleIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &appleUserId, const FString &identityToken)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->mergeAppleIdentity(appleUserId, identityToken, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::DetachAppleIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &appleUserId, bool continueAnon)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->detachAppleIdentity(appleUserId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::AttachTwitterIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &twitterId, const FString &authenticationToken, const FString &secret)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->attachTwitterIdentity(twitterId, authenticationToken, secret, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::MergeTwitterIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &twitterId, const FString &authenticationToken, const FString &secret)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->mergeTwitterIdentity(twitterId, authenticationToken, secret, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::DetachTwitterIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &twitterId, bool continueAnon)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->detachTwitterIdentity(twitterId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::AttachParseIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &parseId, const FString &authenticationToken)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->attachParseIdentity(parseId, authenticationToken, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::MergeParseIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &parseId, const FString &authenticationToken)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->mergeParseIdentity(parseId, authenticationToken, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::DetachParseIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &parseId, bool continueAnon)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->detachParseIdentity(parseId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::SwitchToChildProfile(UBrainCloudWrapper *brainCloudWrapper, const FString &childProfileId, const FString &childAppId, bool forceCreate)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->switchToChildProfile(childProfileId, childAppId, forceCreate, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::SwitchToSingletonChildProfile(UBrainCloudWrapper *brainCloudWrapper, const FString &childAppId, bool forceCreate)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->switchToSingletonChildProfile(childAppId, forceCreate, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::SwitchToParentProfile(UBrainCloudWrapper *brainCloudWrapper, const FString &parentLevelName)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->switchToParentProfile(parentLevelName, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::GetChildProfiles(UBrainCloudWrapper *brainCloudWrapper, bool includeSummaryData)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->getChildProfiles(includeSummaryData, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::GetIdentities(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->getIdentities(Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::GetExpiredIdentities(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->getExpiredIdentities(Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::RefreshIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &externalId, const FString &authenticationToken, EBCAuthType authenticationType)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->refreshIdentity(externalId, authenticationToken, authenticationType, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::ChangeEmailIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &oldEmailAddress, const FString &password, const FString &newEmailAddress, bool updateContactEmail)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->changeEmailIdentity(oldEmailAddress, password, newEmailAddress, updateContactEmail, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::AttachParentWithIdentity(UBrainCloudWrapper *brainCloudWrapper, const FString &externalId, const FString &authenticationToken, EBCAuthType authenticationType,
															 const FString &externalAuthName, bool forceCreate)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->attachParentWithIdentity(externalId, authenticationToken, authenticationType, externalAuthName, forceCreate, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::DetachParent(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->detachParent(Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::AttachPeerProfile(UBrainCloudWrapper *brainCloudWrapper, const FString &peer, const FString &externalId, const FString &authenticationToken, EBCAuthType authenticationType,
													  const FString &externalAuthName, bool forceCreate)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->attachPeerProfile(peer, externalId, authenticationToken, authenticationType, externalAuthName, forceCreate, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::DetachPeer(UBrainCloudWrapper *brainCloudWrapper, const FString &peer)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->detachPeer(peer, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::GetPeerProfiles(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->getPeerProfiles(Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::AttachNonLoginUniversalId(UBrainCloudWrapper *brainCloudWrapper, const FString &externalId)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->attachNonLoginUniversalId(externalId, Proxy);
	return Proxy;
}

UBCIdentityProxy *UBCIdentityProxy::UpdateUniversalIdLogin(UBrainCloudWrapper *brainCloudWrapper, const FString &externalId)
{
	UBCIdentityProxy *Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getIdentityService()->updateUniversalIDLogin(externalId, Proxy);
	return Proxy;
}
