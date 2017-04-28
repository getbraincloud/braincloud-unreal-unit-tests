// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCIdentityProxy.h"

UBCIdentityProxy::UBCIdentityProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCIdentityProxy* UBCIdentityProxy::AttachFacebookIdentity(const FString& facebookId, const FString& authenticationToken)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->attachFacebookIdentity(facebookId, authenticationToken, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::MergeFacebookIdentity(const FString& facebookId, const FString& authenticationToken)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->mergeFacebookIdentity(facebookId, authenticationToken, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::DetachFacebookIdentity(const FString& facebookId, bool continueAnon)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->detachFacebookIdentity(facebookId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::AttachGameCenterIdentity(const FString& gameCenterId)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->attachGameCenterIdentity(gameCenterId, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::MergeGameCenterIdentity(const FString& gameCenterId)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->mergeGameCenterIdentity(gameCenterId, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::DetachGameCenterIdentity(const FString& gameCenterId, bool continueAnon)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->detachGameCenterIdentity(gameCenterId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::AttachEmailIdentity(const FString& email, const FString& password)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->attachEmailIdentity(email, password, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::MergeEmailIdentity(const FString& email, const FString& password)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->mergeEmailIdentity(email, password, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::DetachEmailIdentity(const FString& email, bool continueAnon)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->detachEmailIdentity(email, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::AttachUniversalIdentity(const FString& userId, const FString& password)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->attachUniversalIdentity(userId, password, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::MergeUniversalIdentity(const FString& userId, const FString& password)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->mergeUniversalIdentity(userId, password, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::DetachUniversalIdentity(const FString& userId, bool continueAnon)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->detachUniversalIdentity(userId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::AttachSteamIdentity(const FString& steamId, const FString& sessionTicket)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->attachSteamIdentity(steamId, sessionTicket, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::MergeSteamIdentity(const FString& steamId, const FString& sessionTicket)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->mergeSteamIdentity(steamId, sessionTicket, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::DetachSteamIdentity(const FString& steamId, bool continueAnon)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->detachSteamIdentity(steamId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::AttachGoogleIdentity(const FString& googleId, const FString& authenticationToken)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->attachGoogleIdentity(googleId, authenticationToken, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::MergeGoogleIdentity(const FString& googleId, const FString& authenticationToken)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->mergeGoogleIdentity(googleId, authenticationToken, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::DetachGoogleIdentity(const FString& googleId, bool continueAnon)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->detachGoogleIdentity(googleId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::AttachTwitterIdentity(const FString& twitterId, const FString& authenticationToken, const FString& secret)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->attachTwitterIdentity(twitterId, authenticationToken, secret, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::MergeTwitterIdentity(const FString& twitterId, const FString& authenticationToken, const FString& secret)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->mergeTwitterIdentity(twitterId, authenticationToken, secret, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::DetachTwitterIdentity(const FString& twitterId, bool continueAnon)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->detachTwitterIdentity(twitterId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::AttachParseIdentity(const FString& parseId, const FString& authenticationToken)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->attachParseIdentity(parseId, authenticationToken, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::MergeParseIdentity(const FString& parseId, const FString& authenticationToken)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->mergeParseIdentity(parseId, authenticationToken, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::DetachParseIdentity(const FString& parseId, bool continueAnon)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->detachParseIdentity(parseId, continueAnon, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::SwitchToChildProfile(const FString& childProfileId, const FString& childAppId, bool forceCreate)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->switchToChildProfile(childProfileId, childAppId, forceCreate, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::SwitchToSingletonChildProfile(const FString& childAppId, bool forceCreate)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->switchToSingletonChildProfile(childAppId, forceCreate, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::SwitchToParentProfile(const FString& parentLevelName)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->switchToParentProfile(parentLevelName, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::GetChildProfiles(bool includeSummaryData)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->getChildProfiles(includeSummaryData, Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::GetIdentities()
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->getIdentities(Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::GetExpiredIdentities()
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->getExpiredIdentities(Proxy);
	return Proxy;
}

UBCIdentityProxy* UBCIdentityProxy::RefreshIdentity(const FString& externalId, const FString& authenticationToken, EBCAuthType authenticationType)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->refreshIdentity(externalId, authenticationToken, authenticationType, Proxy);
	return Proxy;
}

UBCIdentityProxy * UBCIdentityProxy::AttachParentWithIdentity(const FString & externalId, const FString & authenticationToken, EBCAuthType authenticationType,
	const FString & externalAuthName, bool forceCreate)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->attachParentWithIdentity(externalId, authenticationToken, authenticationType,
		externalAuthName, forceCreate, Proxy);
	return Proxy;
}

UBCIdentityProxy * UBCIdentityProxy::DetachParent()
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->detachParent(Proxy);
	return Proxy;
}

UBCIdentityProxy * UBCIdentityProxy::AttachPeerProfile(const FString & peer, const FString & externalId, const FString & authenticationToken, EBCAuthType authenticationType,
	const FString & externalAuthName, bool forceCreate)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->attachPeerProfile(peer, externalId, authenticationToken, authenticationType,
		externalAuthName, forceCreate, Proxy);
	return Proxy;
}

UBCIdentityProxy*  UBCIdentityProxy::DetachPeer(const FString& peer)
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->detachPeer(peer, Proxy);
	return Proxy;
}

UBCIdentityProxy*  UBCIdentityProxy::GetPeerProfiles()
{
	UBCIdentityProxy* Proxy = NewObject<UBCIdentityProxy>();
	BrainCloudClient::getInstance()->getIdentityService()->getPeerProfiles(Proxy);
	return Proxy;
}

//callbacks
void UBCIdentityProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
	OnSuccess.Broadcast(jsonData, returnData);
}

void UBCIdentityProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
	OnFailure.Broadcast(jsonError, returnData);
}

