// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCFriendProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BCWrapperProxy.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BrainCloudWrapper.h"

UBCFriendProxy::UBCFriendProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCFriendProxy *UBCFriendProxy::GetProfileInfoForCredential(UBrainCloudWrapper *brainCloudWrapper, const FString &externalId, EBCAuthType authenticationType)
{
	UBCFriendProxy *Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFriendService()->getProfileInfoForCredential(externalId, authenticationType, Proxy);
	return Proxy;
}

UBCFriendProxy *UBCFriendProxy::GetProfileInfoForExternalAuthId(UBrainCloudWrapper *brainCloudWrapper, const FString &externalId, const FString &externalAuthType)
{
	UBCFriendProxy *Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFriendService()->getProfileInfoForExternalAuthId(externalId, externalAuthType, Proxy);
	return Proxy;
}

UBCFriendProxy *UBCFriendProxy::GetExternalIdForProfileId(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId, const FString &authenticationType)
{
	UBCFriendProxy *Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFriendService()->getExternalIdForProfileId(profileId, authenticationType, Proxy);
	return Proxy;
}

UBCFriendProxy *UBCFriendProxy::GetSummaryDataForProfileId(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId)
{
	UBCFriendProxy *Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFriendService()->getSummaryDataForProfileId(profileId, Proxy);
	return Proxy;
}

UBCFriendProxy *UBCFriendProxy::ReadFriendEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId, const FString &friendId)
{
	UBCFriendProxy *Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFriendService()->readFriendEntity(entityId, friendId, Proxy);
	return Proxy;
}

UBCFriendProxy *UBCFriendProxy::ReadFriendsEntities(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType)
{
	UBCFriendProxy *Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFriendService()->readFriendsEntities(entityType, Proxy);
	return Proxy;
}

UBCFriendProxy *UBCFriendProxy::FindUsersByExactName(UBrainCloudWrapper *brainCloudWrapper, const FString &searchText, int32 maxResults)
{
	UBCFriendProxy *Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFriendService()->findUsersByExactName(searchText, maxResults, Proxy);
	return Proxy;
}

UBCFriendProxy *UBCFriendProxy::FindUsersBySubstrName(UBrainCloudWrapper *brainCloudWrapper, const FString &searchText, int32 maxResults)
{
	UBCFriendProxy *Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFriendService()->findUsersBySubstrName(searchText, maxResults, Proxy);
	return Proxy;
}

UBCFriendProxy *UBCFriendProxy::FindUserByExactUniversalId(UBrainCloudWrapper *brainCloudWrapper, const FString &searchText)
{
	UBCFriendProxy *Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFriendService()->findUserByExactUniversalId(searchText, Proxy);
	return Proxy;
}

UBCFriendProxy *UBCFriendProxy::FindUsersByUniversalIdStartingWith(UBrainCloudWrapper *brainCloudWrapper, const FString &searchText, int32 maxResults)
{
	UBCFriendProxy *Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFriendService()->findUsersByUniversalIdStartingWith(searchText, maxResults, Proxy);
	return Proxy;
}

UBCFriendProxy *UBCFriendProxy::FindUsersByNameStartingWith(UBrainCloudWrapper *brainCloudWrapper, const FString &searchText, int32 maxResults)
{
	UBCFriendProxy *Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFriendService()->findUsersByNameStartingWith(searchText, maxResults, Proxy);
	return Proxy;
}

UBCFriendProxy *UBCFriendProxy::ListFriends(UBrainCloudWrapper *brainCloudWrapper, EFriendPlatform friendPlatform, bool includeSummaryData)
{
	UBCFriendProxy *Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFriendService()->listFriends(friendPlatform, includeSummaryData, Proxy);
	return Proxy;
}

UBCFriendProxy *UBCFriendProxy::GetMySocialInfo(UBrainCloudWrapper *brainCloudWrapper, EFriendPlatform friendPlatform, bool includeSummaryData)
{
	UBCFriendProxy *Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFriendService()->getMySocialInfo(friendPlatform, includeSummaryData, Proxy);
	return Proxy;
}

UBCFriendProxy *UBCFriendProxy::AddFriends(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &profileIds)
{
	UBCFriendProxy *Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFriendService()->addFriends(profileIds, Proxy);
	return Proxy;
}

UBCFriendProxy* UBCFriendProxy::AddFriendsFromPlatform(UBrainCloudWrapper* brainCloudWrapper,
	EFriendPlatform friendPlatform, FString mode, const TArray<FString>& externalIds)
{
	UBCFriendProxy *Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFriendService()->addFriendsFromPlatform(friendPlatform, mode, externalIds, Proxy);
	return Proxy;
}

UBCFriendProxy *UBCFriendProxy::RemoveFriends(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &profileIds)
{
	UBCFriendProxy *Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFriendService()->removeFriends(profileIds, Proxy);
	return Proxy;
}

UBCFriendProxy *UBCFriendProxy::GetUsersOnlineStatus(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &profileIds)
{
	UBCFriendProxy *Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFriendService()->getUsersOnlineStatus(profileIds, Proxy);
	return Proxy;
}

UBCFriendProxy *UBCFriendProxy::ReadFriendUserState(UBrainCloudWrapper *brainCloudWrapper, const FString &friendId)
{
	UBCFriendProxy *Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFriendService()->readFriendUserState(friendId, Proxy);
	return Proxy;
}
