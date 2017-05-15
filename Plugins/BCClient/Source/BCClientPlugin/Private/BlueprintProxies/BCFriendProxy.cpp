// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCFriendProxy.h"

UBCFriendProxy::UBCFriendProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCFriendProxy* UBCFriendProxy::GetProfileInfoForCredential(const FString& externalId, EBCAuthType authenticationType)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	BrainCloudClient::getInstance()->getFriendService()->getProfileInfoForCredential(externalId, authenticationType, Proxy);
	return Proxy;
}

UBCFriendProxy* UBCFriendProxy::GetProfileInfoForExternalAuthId(const FString& externalId, const FString& externalAuthType)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	BrainCloudClient::getInstance()->getFriendService()->getProfileInfoForExternalAuthId(externalId, externalAuthType, Proxy);
	return Proxy;
}

UBCFriendProxy* UBCFriendProxy::GetExternalIdForProfileId(const FString& profileId, const FString& authenticationType)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	BrainCloudClient::getInstance()->getFriendService()->getExternalIdForProfileId(profileId, authenticationType, Proxy);
	return Proxy;
}

UBCFriendProxy* UBCFriendProxy::GetSummaryDataForProfileId(const FString& profileId)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	BrainCloudClient::getInstance()->getFriendService()->getSummaryDataForProfileId(profileId, Proxy);
	return Proxy;
}

UBCFriendProxy* UBCFriendProxy::ReadFriendEntity(const FString& entityId, const FString& friendId)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	BrainCloudClient::getInstance()->getFriendService()->readFriendEntity(entityId, friendId, Proxy);
	return Proxy;
}

UBCFriendProxy* UBCFriendProxy::ReadFriendsEntities(const FString& entityType)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	BrainCloudClient::getInstance()->getFriendService()->readFriendsEntities(entityType, Proxy);
	return Proxy;
}

UBCFriendProxy* UBCFriendProxy::ReadFriendPlayerState(const FString& friendId)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	BrainCloudClient::getInstance()->getFriendService()->readFriendUserState(friendId, Proxy);
	return Proxy;
}

UBCFriendProxy* UBCFriendProxy::FindUsersByExactName(const FString& searchText, int32 maxResults)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	BrainCloudClient::getInstance()->getFriendService()->findUsersByExactName(searchText, maxResults, Proxy);
	return Proxy;
}

UBCFriendProxy* UBCFriendProxy::FindUsersBySubstrName(const FString& searchText, int32 maxResults)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	BrainCloudClient::getInstance()->getFriendService()->findUsersBySubstrName(searchText, maxResults, Proxy);
	return Proxy;
}

UBCFriendProxy * UBCFriendProxy::FindPlayerByUniversalId(const FString & searchText, int32 maxResults)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	BrainCloudClient::getInstance()->getFriendService()->findUserByUniversalId(searchText, maxResults, Proxy);
	return Proxy;
}

UBCFriendProxy * UBCFriendProxy::FindUserByUniversalId(const FString & searchText, int32 maxResults)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	BrainCloudClient::getInstance()->getFriendService()->findUserByUniversalId(searchText, maxResults, Proxy);
	return Proxy;
}

UBCFriendProxy * UBCFriendProxy::ListFriends(EFriendPlatform friendPlatform, bool includeSummaryData)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	BrainCloudClient::getInstance()->getFriendService()->listFriends(friendPlatform, includeSummaryData, Proxy);
	return Proxy;
}

UBCFriendProxy * UBCFriendProxy::AddFriends(const TArray<FString>& profileIds)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	BrainCloudClient::getInstance()->getFriendService()->addFriends(profileIds, Proxy);
	return Proxy;
}

UBCFriendProxy * UBCFriendProxy::RemoveFriends(const TArray<FString>& profileIds)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	BrainCloudClient::getInstance()->getFriendService()->removeFriends(profileIds, Proxy);
	return Proxy;
}

UBCFriendProxy * UBCFriendProxy::GetUsersOnlineStatus(const TArray<FString>& profileIds)
{
	UBCFriendProxy* Proxy = NewObject<UBCFriendProxy>();
	BrainCloudClient::getInstance()->getFriendService()->getUsersOnlineStatus(profileIds, Proxy);
	return Proxy;
}


//callbacks
void UBCFriendProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
	OnSuccess.Broadcast(jsonData, returnData);
}

void UBCFriendProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
	OnFailure.Broadcast(jsonError, returnData);
}

