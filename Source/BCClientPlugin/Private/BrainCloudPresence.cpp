// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudPresence.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudPresence::BrainCloudPresence(BrainCloudClient *client) : _client(client){};

void BrainCloudPresence::forcePush(IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    ServerCall *sc = new ServerCall(ServiceName::Presence, ServiceOperation::ForcePush, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPresence::getPresenceOfFriends(const FString &platform, bool includeOffline, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PresenceServicePlatform.getValue(), platform);
    message->SetBoolField(OperationParam::PresenceServiceIncludeOffline.getValue(), includeOffline);

    ServerCall *sc = new ServerCall(ServiceName::Presence, ServiceOperation::GetPresenceOfFriends, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPresence::getPresenceOfGroup(const FString &groupId, bool includeOffline, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PresenceServiceGroupId.getValue(), groupId);
    message->SetBoolField(OperationParam::PresenceServiceIncludeOffline.getValue(), includeOffline);

    ServerCall *sc = new ServerCall(ServiceName::Presence, ServiceOperation::GetPresenceOfGroup, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPresence::getPresenceOfUsers(const TArray<FString> &profileIds, bool includeOffline, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetArrayField(OperationParam::PresenceServiceProfileIds.getValue(), JsonUtil::arrayToJsonArray(profileIds));
    message->SetBoolField(OperationParam::PresenceServiceIncludeOffline.getValue(), includeOffline);

    ServerCall *sc = new ServerCall(ServiceName::Presence, ServiceOperation::GetPresenceOfUsers, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPresence::registerListenersForFriends(const FString &platform, bool biderectional, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PresenceServicePlatform.getValue(), platform);
    message->SetBoolField(OperationParam::PresenceServiceBidirectional.getValue(), biderectional);

    ServerCall *sc = new ServerCall(ServiceName::Presence, ServiceOperation::RegisterListenersForFriends, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPresence::registerListenersForGroup(const FString &groupId, bool biderectional, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PresenceServiceGroupId.getValue(), groupId);
    message->SetBoolField(OperationParam::PresenceServiceBidirectional.getValue(), biderectional);

    ServerCall *sc = new ServerCall(ServiceName::Presence, ServiceOperation::RegisterListenersForGroup, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPresence::registerListenersForProfiles(const TArray<FString> &profileIds, bool bidirectional, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetArrayField(OperationParam::PresenceServiceProfileIds.getValue(), JsonUtil::arrayToJsonArray(profileIds));
    message->SetBoolField(OperationParam::PresenceServiceBidirectional.getValue(), bidirectional);

    ServerCall *sc = new ServerCall(ServiceName::Presence, ServiceOperation::RegisterListenersForProfiles, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPresence::setVisibility(bool visible, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetBoolField(OperationParam::PresenceServiceVisible.getValue(), visible);

    ServerCall *sc = new ServerCall(ServiceName::Presence, ServiceOperation::SetVisibility, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPresence::stopListening(IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    ServerCall *sc = new ServerCall(ServiceName::Presence, ServiceOperation::StopListening, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPresence::updateActivity(const FString &activity, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetObjectField(OperationParam::PresenceServiceActivity.getValue(), JsonUtil::jsonStringToValue(activity));

    ServerCall *sc = new ServerCall(ServiceName::Presence, ServiceOperation::UpdateActivity, message, callback);
    _client->sendRequest(sc);
}
