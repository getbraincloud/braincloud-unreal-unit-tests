// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloud.h"
#include "BCWrapperProxy.h"
#include "BCFriendProxy.h"
#include "BrainCloudWrapper.h"

UBCFriendProxy::UBCFriendProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCFriendProxy* UBCFriendProxy::GetProfileInfoForCredential(ABrainCloud *brainCloud, const FString& externalId, EBCAuthType authenticationType)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFriendService()->getProfileInfoForCredential(externalId, authenticationType, Proxy);
	return Proxy;
}

UBCFriendProxy* UBCFriendProxy::GetProfileInfoForExternalAuthId(ABrainCloud *brainCloud, const FString& externalId, const FString& externalAuthType)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFriendService()->getProfileInfoForExternalAuthId(externalId, externalAuthType, Proxy);
	return Proxy;
}

UBCFriendProxy* UBCFriendProxy::GetExternalIdForProfileId(ABrainCloud *brainCloud, const FString& profileId, const FString& authenticationType)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFriendService()->getExternalIdForProfileId(profileId, authenticationType, Proxy);
	return Proxy;
}

UBCFriendProxy* UBCFriendProxy::GetSummaryDataForProfileId(ABrainCloud *brainCloud, const FString& profileId)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFriendService()->getSummaryDataForProfileId(profileId, Proxy);
	return Proxy;
}

UBCFriendProxy* UBCFriendProxy::ReadFriendEntity(ABrainCloud *brainCloud, const FString& entityId, const FString& friendId)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFriendService()->readFriendEntity(entityId, friendId, Proxy);
	return Proxy;
}

UBCFriendProxy* UBCFriendProxy::ReadFriendsEntities(ABrainCloud *brainCloud, const FString& entityType)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFriendService()->readFriendsEntities(entityType, Proxy);
	return Proxy;
}

UBCFriendProxy* UBCFriendProxy::ReadFriendPlayerState(ABrainCloud *brainCloud, const FString& friendId)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFriendService()->readFriendUserState(friendId, Proxy);
	return Proxy;
}

UBCFriendProxy* UBCFriendProxy::FindUsersByExactName(ABrainCloud *brainCloud, const FString& searchText, int32 maxResults)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFriendService()->findUsersByExactName(searchText, maxResults, Proxy);
	return Proxy;
}

UBCFriendProxy* UBCFriendProxy::FindUsersBySubstrName(ABrainCloud *brainCloud, const FString& searchText, int32 maxResults)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFriendService()->findUsersBySubstrName(searchText, maxResults, Proxy);
	return Proxy;
}

UBCFriendProxy * UBCFriendProxy::FindPlayerByUniversalId(ABrainCloud *brainCloud, const FString & searchText, int32 maxResults)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFriendService()->findUserByUniversalId(searchText, maxResults, Proxy);
	return Proxy;
}

UBCFriendProxy * UBCFriendProxy::FindUserByUniversalId(ABrainCloud *brainCloud, const FString & searchText, int32 maxResults)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFriendService()->findUserByUniversalId(searchText, maxResults, Proxy);
	return Proxy;
}

UBCFriendProxy * UBCFriendProxy::ListFriends(ABrainCloud *brainCloud, EFriendPlatform friendPlatform, bool includeSummaryData)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFriendService()->listFriends(friendPlatform, includeSummaryData, Proxy);
	return Proxy;
}

UBCFriendProxy * UBCFriendProxy::AddFriends(ABrainCloud *brainCloud, const TArray<FString>& profileIds)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFriendService()->addFriends(profileIds, Proxy);
	return Proxy;
}

UBCFriendProxy * UBCFriendProxy::RemoveFriends(ABrainCloud *brainCloud, const TArray<FString>& profileIds)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFriendService()->removeFriends(profileIds, Proxy);
	return Proxy;
}

UBCFriendProxy * UBCFriendProxy::GetUsersOnlineStatus(ABrainCloud *brainCloud, const TArray<FString>& profileIds)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFriendService()->getUsersOnlineStatus(profileIds, Proxy);
	return Proxy;
}


//callbacks
void UBCFriendProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
	OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCFriendProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
	OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

