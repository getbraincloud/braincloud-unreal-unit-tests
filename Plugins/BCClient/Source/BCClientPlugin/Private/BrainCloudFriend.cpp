// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudFriend.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudFriend::BrainCloudFriend(BrainCloudClient *client) : _client(client)
{
	_platformStrings.Add(EFriendPlatform::ALL, TEXT("All"));
	_platformStrings.Add(EFriendPlatform::BRAINCLOUD, TEXT("brainCloud"));
	_platformStrings.Add(EFriendPlatform::FACEBOOK, TEXT("Facebook"));
};

void BrainCloudFriend::getProfileInfoForCredential(const FString &externalId, EBCAuthType authenticationType, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

	message->SetStringField(OperationParam::FriendServiceExternalId.getValue(), externalId);
	message->SetStringField(OperationParam::FriendServiceAuthenticationType.getValue(), BCAuthType::EnumToString(authenticationType));

	ServerCall *sc = new ServerCall(ServiceName::Friend, ServiceOperation::GetProfileInfoForCredential, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudFriend::getProfileInfoForExternalAuthId(const FString &externalId, const FString &externalAuthType, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

	message->SetStringField(OperationParam::FriendServiceExternalId.getValue(), externalId);
	message->SetStringField(OperationParam::ExternalAuthType.getValue(), externalAuthType);

	ServerCall *sc = new ServerCall(ServiceName::Friend, ServiceOperation::GetProfileInfoForExternalAuthId, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudFriend::getExternalIdForProfileId(const FString &profileId, const FString &authenticationType, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

	message->SetStringField(OperationParam::FriendServiceProfileId.getValue(), profileId);
	message->SetStringField(OperationParam::FriendServiceAuthenticationType.getValue(), authenticationType);

	ServerCall *sc = new ServerCall(ServiceName::Friend, ServiceOperation::GetExternalIdForProfileId, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudFriend::getSummaryDataForProfileId(const FString &profileId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

	message->SetStringField(OperationParam::FriendServiceProfileId.getValue(), profileId);

	ServerCall *sc = new ServerCall(ServiceName::Friend, ServiceOperation::GetSummaryDataForProfileId, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudFriend::readFriendEntity(const FString &entityId, const FString &friendId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

	message->SetStringField(OperationParam::FriendServiceEntityId.getValue(), entityId);
	message->SetStringField(OperationParam::FriendServiceFriendId.getValue(), friendId);

	ServerCall *sc = new ServerCall(ServiceName::Friend, ServiceOperation::ReadFriendEntity, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudFriend::readFriendsEntities(const FString &entityType, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

	message->SetStringField(OperationParam::FriendServiceEntityType.getValue(), entityType);

	ServerCall *sc = new ServerCall(ServiceName::Friend, ServiceOperation::ReadFriendsEntities, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudFriend::readFriendUserState(const FString &friendId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::FriendServiceReadPlayerStateFriendId.getValue(), friendId);

	ServerCall *sc = new ServerCall(ServiceName::Friend, ServiceOperation::ReadFriendsPlayerState, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudFriend::findUsersByExactName(const FString &searchText, int32 maxResults, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::FriendServiceSearchText.getValue(), searchText);
	message->SetNumberField(OperationParam::FriendServiceMaxResults.getValue(), maxResults);

	ServerCall *sc = new ServerCall(ServiceName::Friend, ServiceOperation::FindUsersByExactName, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudFriend::findUsersBySubstrName(const FString &searchText, int32 maxResults, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::FriendServiceSearchText.getValue(), searchText);
	message->SetNumberField(OperationParam::FriendServiceMaxResults.getValue(), maxResults);

	ServerCall *sc = new ServerCall(ServiceName::Friend, ServiceOperation::FindUsersBySubstrName, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudFriend::findUserByExactUniversalId(const FString &searchText, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::FriendServiceSearchText.getValue(), searchText);

	ServerCall *sc = new ServerCall(ServiceName::Friend, ServiceOperation::FindUserByExactUniversalId, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudFriend::findUsersByUniversalIdStartingWith(const FString &searchText, int32 maxResults, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::FriendServiceSearchText.getValue(), searchText);
	message->SetNumberField(OperationParam::FriendServiceMaxResults.getValue(), maxResults);

	ServerCall *sc = new ServerCall(ServiceName::Friend, ServiceOperation::FindUsersByUniversalIdStartingWith, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudFriend::findUsersByNameStartingWith(const FString &searchText, int32 maxResults, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::FriendServiceSearchText.getValue(), searchText);
	message->SetNumberField(OperationParam::FriendServiceMaxResults.getValue(), maxResults);

	ServerCall *sc = new ServerCall(ServiceName::Friend, ServiceOperation::FindUsersByNameStartingWith, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudFriend::listFriends(EFriendPlatform friendPlatform, bool includeSummaryData, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetBoolField(OperationParam::FriendServiceIncludeSummaryData.getValue(), includeSummaryData);
	message->SetStringField(OperationParam::FriendServiceFriendPlatform.getValue(), _platformStrings[friendPlatform]);

	ServerCall *sc = new ServerCall(ServiceName::Friend, ServiceOperation::ListFriends, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudFriend::getMySocialInfo(EFriendPlatform friendPlatform, bool includeSummaryData, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetBoolField(OperationParam::FriendServiceIncludeSummaryData.getValue(), includeSummaryData);
	message->SetStringField(OperationParam::FriendServiceFriendPlatform.getValue(), _platformStrings[friendPlatform]);

	ServerCall *sc = new ServerCall(ServiceName::Friend, ServiceOperation::GetMySocialInfo, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudFriend::addFriends(const TArray<FString> &profileIds, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetArrayField(OperationParam::FriendServiceProfileIds.getValue(), JsonUtil::arrayToJsonArray(profileIds));

	ServerCall *sc = new ServerCall(ServiceName::Friend, ServiceOperation::AddFriends, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudFriend::addFriendsFromPlatform(const EFriendPlatform& friendPlatform, FString mode,
	const TArray<FString>& externalIds, IServerCallback* callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

	message->SetStringField(OperationParam::FriendServiceFriendPlatform.getValue(),_platformStrings[friendPlatform]);
	message->SetStringField(OperationParam::FriendServiceMode.getValue(), mode);
	message->SetArrayField(OperationParam::FriendServiceExternalIds.getValue(), JsonUtil::arrayToJsonArray(externalIds));

	ServerCall *sc = new ServerCall(ServiceName::Friend, ServiceOperation::AddFriendsFromPlatform, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudFriend::removeFriends(const TArray<FString> &profileIds, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetArrayField(OperationParam::FriendServiceProfileIds.getValue(), JsonUtil::arrayToJsonArray(profileIds));

	ServerCall *sc = new ServerCall(ServiceName::Friend, ServiceOperation::RemoveFriends, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudFriend::getUsersOnlineStatus(const TArray<FString> &profileIds, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetArrayField(OperationParam::FriendServiceProfileIds.getValue(), JsonUtil::arrayToJsonArray(profileIds));

	ServerCall *sc = new ServerCall(ServiceName::Friend, ServiceOperation::GetUsersOnlineStatus, message, callback);
	_client->sendRequest(sc);
}
