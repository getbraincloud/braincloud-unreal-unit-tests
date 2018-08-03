// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloudActor.h"
#include "BCWrapperProxy.h"
#include "BCIdentityProxy.h"
#include "BrainCloudWrapper.h"

UBCIdentityProxy::UBCIdentityProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCIdentityProxy* UBCIdentityProxy::AttachFacebookIdentity(ABrainCloudActor *brainCloud, const FString& facebookId, const FString& authenticationToken)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->attachFacebookIdentity(facebookId, authenticationToken, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::MergeFacebookIdentity(ABrainCloudActor *brainCloud, const FString& facebookId, const FString& authenticationToken)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->mergeFacebookIdentity(facebookId, authenticationToken, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::DetachFacebookIdentity(ABrainCloudActor *brainCloud, const FString& facebookId, bool continueAnon)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->detachFacebookIdentity(facebookId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::AttachGameCenterIdentity(ABrainCloudActor *brainCloud, const FString& gameCenterId)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->attachGameCenterIdentity(gameCenterId, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::MergeGameCenterIdentity(ABrainCloudActor *brainCloud, const FString& gameCenterId)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->mergeGameCenterIdentity(gameCenterId, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::DetachGameCenterIdentity(ABrainCloudActor *brainCloud, const FString& gameCenterId, bool continueAnon)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->detachGameCenterIdentity(gameCenterId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::AttachEmailIdentity(ABrainCloudActor *brainCloud, const FString& email, const FString& password)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->attachEmailIdentity(email, password, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::MergeEmailIdentity(ABrainCloudActor *brainCloud, const FString& email, const FString& password)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->mergeEmailIdentity(email, password, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::DetachEmailIdentity(ABrainCloudActor *brainCloud, const FString& email, bool continueAnon)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->detachEmailIdentity(email, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::AttachUniversalIdentity(ABrainCloudActor *brainCloud, const FString& userId, const FString& password)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->attachUniversalIdentity(userId, password, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::MergeUniversalIdentity(ABrainCloudActor *brainCloud, const FString& userId, const FString& password)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->mergeUniversalIdentity(userId, password, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::DetachUniversalIdentity(ABrainCloudActor *brainCloud, const FString& userId, bool continueAnon)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->detachUniversalIdentity(userId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::AttachSteamIdentity(ABrainCloudActor *brainCloud, const FString& steamId, const FString& sessionTicket)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->attachSteamIdentity(steamId, sessionTicket, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::MergeSteamIdentity(ABrainCloudActor *brainCloud, const FString& steamId, const FString& sessionTicket)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->mergeSteamIdentity(steamId, sessionTicket, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::DetachSteamIdentity(ABrainCloudActor *brainCloud, const FString& steamId, bool continueAnon)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->detachSteamIdentity(steamId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::AttachGoogleIdentity(ABrainCloudActor *brainCloud, const FString& googleId, const FString& authenticationToken)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->attachGoogleIdentity(googleId, authenticationToken, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::MergeGoogleIdentity(ABrainCloudActor *brainCloud, const FString& googleId, const FString& authenticationToken)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->mergeGoogleIdentity(googleId, authenticationToken, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::DetachGoogleIdentity(ABrainCloudActor *brainCloud, const FString& googleId, bool continueAnon)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->detachGoogleIdentity(googleId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::AttachTwitterIdentity(ABrainCloudActor *brainCloud, const FString& twitterId, const FString& authenticationToken, const FString& secret)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->attachTwitterIdentity(twitterId, authenticationToken, secret, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::MergeTwitterIdentity(ABrainCloudActor *brainCloud, const FString& twitterId, const FString& authenticationToken, const FString& secret)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->mergeTwitterIdentity(twitterId, authenticationToken, secret, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::DetachTwitterIdentity(ABrainCloudActor *brainCloud, const FString& twitterId, bool continueAnon)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->detachTwitterIdentity(twitterId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::AttachParseIdentity(ABrainCloudActor *brainCloud, const FString& parseId, const FString& authenticationToken)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->attachParseIdentity(parseId, authenticationToken, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::MergeParseIdentity(ABrainCloudActor *brainCloud, const FString& parseId, const FString& authenticationToken)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->mergeParseIdentity(parseId, authenticationToken, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::DetachParseIdentity(ABrainCloudActor *brainCloud, const FString& parseId, bool continueAnon)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->detachParseIdentity(parseId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::SwitchToChildProfile(ABrainCloudActor *brainCloud, const FString& childProfileId, const FString& childAppId, bool forceCreate)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->switchToChildProfile(childProfileId, childAppId, forceCreate, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::SwitchToSingletonChildProfile(ABrainCloudActor *brainCloud, const FString& childAppId, bool forceCreate)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->switchToSingletonChildProfile(childAppId, forceCreate, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::SwitchToParentProfile(ABrainCloudActor *brainCloud, const FString& parentLevelName)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->switchToParentProfile(parentLevelName, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::GetChildProfiles(ABrainCloudActor *brainCloud, bool includeSummaryData)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->getChildProfiles(includeSummaryData, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::GetIdentities(ABrainCloudActor *brainCloud)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->getIdentities(Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::GetExpiredIdentities(ABrainCloudActor *brainCloud)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->getExpiredIdentities(Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::RefreshIdentity(ABrainCloudActor *brainCloud, const FString& externalId, const FString& authenticationToken, EBCAuthType authenticationType)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->refreshIdentity(externalId, authenticationToken, authenticationType, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::ChangeEmailIdentity(ABrainCloudActor *brainCloud, const FString& oldEmailAddress, const FString& password, const FString& newEmailAddress, bool updateContactEmail)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->changeEmailIdentity(oldEmailAddress, password, newEmailAddress, updateContactEmail, Proxy);
	return Proxy;
}

UBCIdentityProxy * UBCIdentityProxy::AttachParentWithIdentity(ABrainCloudActor *brainCloud, const FString & externalId, const FString & authenticationToken, EBCAuthType authenticationType,
	const FString & externalAuthName, bool forceCreate)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->attachParentWithIdentity(externalId, authenticationToken, authenticationType,
		externalAuthName, forceCreate, Proxy);
	return Proxy;
}

UBCIdentityProxy * UBCIdentityProxy::DetachParent(ABrainCloudActor *brainCloud)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->detachParent(Proxy);
	return Proxy;
}

UBCIdentityProxy * UBCIdentityProxy::AttachPeerProfile(ABrainCloudActor *brainCloud, const FString & peer, const FString & externalId, const FString & authenticationToken, EBCAuthType authenticationType,
	const FString & externalAuthName, bool forceCreate)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->attachPeerProfile(peer, externalId, authenticationToken, authenticationType,
		externalAuthName, forceCreate, Proxy);
	return Proxy;
}

UBCIdentityProxy*  UBCIdentityProxy::DetachPeer(ABrainCloudActor *brainCloud, const FString& peer)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->detachPeer(peer, Proxy);
	return Proxy;
}

UBCIdentityProxy*  UBCIdentityProxy::GetPeerProfiles(ABrainCloudActor *brainCloud)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getIdentityService()->getPeerProfiles(Proxy);
	return Proxy;
}

//callbacks
void UBCIdentityProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
	OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCIdentityProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
	OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

