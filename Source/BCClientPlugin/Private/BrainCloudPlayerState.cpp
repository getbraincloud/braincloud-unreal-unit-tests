// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudPlayerState.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudPlayerState::BrainCloudPlayerState(BrainCloudClient *client) : _client(client){};

void BrainCloudPlayerState::readUserState(IServerCallback *callback, const FString &entityTypeFilter)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    if (entityTypeFilter.Len() > 0)
    {
        message->SetStringField(OperationParam::PlayerStateServiceReadEntitySubtype.getValue(), entityTypeFilter);
    }

    ServerCall *sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::Read, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::deleteUser(IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    ServerCall *sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::FullReset, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::resetUserState(IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    ServerCall *sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::DataReset, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::logout(IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    ServerCall *sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::Logout, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::updateUserName(const FString &name, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    if (name.Len() > 0)
    {
        message->SetStringField(OperationParam::PlayerStateServiceUpdateNameData.getValue(), name);
    }

    ServerCall *sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::UpdateName, message, callback);
    _client->sendRequest(sc);   
}

void BrainCloudPlayerState::updateName(const FString &name, IServerCallback *callback)
{
    updateUserName(name, callback);
}

void BrainCloudPlayerState::updateSummaryFriendData(const FString &jsonSummaryData, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetObjectField(OperationParam::PlayerStateServiceUpdateSummaryFriendData.getValue(), JsonUtil::jsonStringToValue(jsonSummaryData));

    ServerCall *sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::UpdateSummary, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::getAttributes(IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    ServerCall *sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::GetAttributes, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::updateAttributes(const FString &jsonAttributes, bool wipeExisting, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetField(OperationParam::PlayerStateServiceAttributes.getValue(), JsonUtil::jsonStringToActualValue(jsonAttributes));
    message->SetBoolField(OperationParam::PlayerStateServiceWipeExisting.getValue(), wipeExisting);

    ServerCall *sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::UpdateAttributes, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::removeAttributes(const TArray<FString> &attributeNames, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetArrayField(OperationParam::PlayerStateServiceAttributes.getValue(), JsonUtil::arrayToJsonArray(attributeNames));

    ServerCall *sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::RemoveAttributes, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::updateUserPictureUrl(const FString &pictureUrl, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PlayerStateServicePictureUrl.getValue(), pictureUrl);

    ServerCall *sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::UpdatePlayerPicture, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::updateContactEmail(const FString &contactEmail, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PlayerStateServiceContactEmail.getValue(), contactEmail);

    ServerCall *sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::UpdateContactEmail, message, callback);
    _client->sendRequest(sc);
}


void BrainCloudPlayerState::clearUserStatus(const FString &statusName, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PlayerStateServiceStatusName.getValue(), statusName);

    ServerCall *sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::ClearUserStatus, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::extendUserStatus(const FString &statusName, int additionalSecs, const FString &details, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PlayerStateServiceStatusName.getValue(), statusName);
    message->SetNumberField(OperationParam::PlayerStateServiceAdditionalSecs.getValue(), additionalSecs);
    message->SetObjectField(OperationParam::PlayerStateServiceDetails.getValue(), JsonUtil::jsonStringToValue(details));

    ServerCall *sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::ExtendUserStatus, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::getUserStatus(const FString &statusName, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PlayerStateServiceStatusName.getValue(), statusName);

    ServerCall *sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::GetUserStatus, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::setUserStatus(const FString &statusName, int durationSecs, const FString &details, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PlayerStateServiceStatusName.getValue(), statusName);
    message->SetNumberField(OperationParam::PlayerStateServiceDurationSecs.getValue(), durationSecs);
    message->SetObjectField(OperationParam::PlayerStateServiceDetails.getValue(), JsonUtil::jsonStringToValue(details));

    ServerCall *sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::SetUserStatus, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::updateTimeZoneOffset(int32 timeZoneOffset, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetNumberField(OperationParam::PlayerStateServiceTimeZoneOffset.getValue(), timeZoneOffset);

    ServerCall *sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::UpdateTimeZoneOffset, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerState::updateLanguageCode(const FString &languageCode, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PlayerStateServiceLanguageCode.getValue(), languageCode);

    ServerCall *sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::UpdateLanguageCode, message, callback);
    _client->sendRequest(sc);
}


const FString &BrainCloudPlayerState::getPlayerName()
{
    return _userName;
}

const FString &BrainCloudPlayerState::getUserName()
{
    return _userName;
}

void BrainCloudPlayerState::setUserName(const FString &name)
{
    _userName = name;
}