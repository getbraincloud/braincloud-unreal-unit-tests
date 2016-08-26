// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudPlayerState.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudPlayerState::BrainCloudPlayerState(BrainCloudClient* client) : _client(client) {};

void BrainCloudPlayerState::readPlayerState(IServerCallback * callback, const FString& entityTypeFilter)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    if (entityTypeFilter.Len() > 0)
    {
        message->SetStringField(OperationParam::PlayerStateServiceReadEntitySubtype.getValue(), entityTypeFilter);
    }

    ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::Read, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::deletePlayer(IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::FullReset, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::resetPlayerState(IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::DataReset, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::logout(IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::Logout, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::updatePlayerName(const FString& name, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    if (name.Len() > 0)
    {
        message->SetStringField(OperationParam::PlayerStateServiceUpdateNameData.getValue(), name);
    }

    ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::UpdateName, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::updateSummaryFriendData(const FString& jsonSummaryData, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetObjectField(OperationParam::PlayerStateServiceUpdateSummaryFriendData.getValue(), JsonUtil::jsonStringToValue(jsonSummaryData));

    ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::UpdateSummary, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::getAttributes(IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::GetAttributes, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::updateAttributes(const FString& jsonAttributes, bool wipeExisting, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetField(OperationParam::PlayerStateServiceAttributes.getValue(), JsonUtil::jsonStringToActualValue(jsonAttributes));
    message->SetBoolField(OperationParam::PlayerStateServiceWipeExisting.getValue(), wipeExisting);

    ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::UpdateAttributes, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::removeAttributes(const TArray<FString>& attributeNames, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetArrayField(OperationParam::PlayerStateServiceAttributes.getValue(), JsonUtil::arrayToJsonArray(attributeNames));

    ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::RemoveAttributes, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::updatePlayerPictureUrl(const FString & pictureUrl, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PlayerStateServicePictureUrl.getValue(), pictureUrl);

    ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::UpdatePlayerPicture, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::updateContactEmail(const FString & contactEmail, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PlayerStateServiceContactEmail.getValue(), contactEmail);

    ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::UpdateContactEmail, message, callback);
    _client->sendRequest(sc);
}

const FString& BrainCloudPlayerState::getPlayerName()
{
    return _playerName;
}

void BrainCloudPlayerState::setPlayerName(const FString& name)
{
    _playerName = name;
}