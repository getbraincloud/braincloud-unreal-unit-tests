// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudPushNotification.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"
#include "BCPlatform.h"

BrainCloudPushNotification::BrainCloudPushNotification(BrainCloudClient* client) : _client(client) {}

void BrainCloudPushNotification::deregisterAllPushNotificationDeviceTokens(IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::DeregisterAll, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPushNotification::deregisterPushNotificationDeviceToken(EBCPlatform platform, const FString & token, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PushNotificationRegisterParamDeviceType.getValue(), BCPlatform::EnumToString(platform));
    message->SetStringField(OperationParam::PushNotificationRegisterParamDeviceToken.getValue(), token);

    ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::Deregister, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPushNotification::registerPushNotificationDeviceToken(EBCPlatform platform, const FString& deviceToken, IServerCallback * callback)
{
    registerPushNotificationDeviceToken(BCPlatform::EnumToString(platform), deviceToken, callback);
}

void BrainCloudPushNotification::registerPushNotificationDeviceToken(const FString& type, const FString& token, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PushNotificationRegisterParamDeviceType.getValue(), type);
    message->SetStringField(OperationParam::PushNotificationRegisterParamDeviceToken.getValue(), token);

    ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::Register, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPushNotification::sendSimplePushNotification(const FString& toProfileId, const FString& message, IServerCallback * callback)
{
    TSharedRef<FJsonObject> messageObj = MakeShareable(new FJsonObject());
    messageObj->SetStringField(OperationParam::PushNotificationSendParamToPlayerId.getValue(), toProfileId);
    messageObj->SetStringField(OperationParam::PushNotificationSendParamMessage.getValue(), message);

    ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendSimple, messageObj, callback);
    _client->sendRequest(sc);
}

void BrainCloudPushNotification::sendRichPushNotification(const FString& toProfileId, int32 notificationTemplateId, IServerCallback * callback)
{
    sendRichPushNotificationWithParams(toProfileId, notificationTemplateId, "", callback);
}

void BrainCloudPushNotification::sendRichPushNotificationWithParams(const FString& toProfileId, int32 notificationTemplateId, const FString& substitutionJson, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PushNotificationSendParamToPlayerId.getValue(), toProfileId);
    message->SetNumberField(OperationParam::PushNotificationSendParamNotificationTemplateId.getValue(), notificationTemplateId);

    if (OperationParam::isOptionalParamValid(substitutionJson))
    {
        message->SetObjectField(OperationParam::PushNotificationSendParamSubstitution.getValue(), JsonUtil::jsonStringToValue(substitutionJson));
    }

    ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendRich, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPushNotification::sendTemplatedPushNotificationToGroup(const FString& groupId, int32 notificationTemplateId, const FString& substitutionsJson, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::GroupId.getValue(), groupId);
    message->SetNumberField(OperationParam::PushNotificationSendParamNotificationTemplateId.getValue(), notificationTemplateId);

    if (OperationParam::isOptionalParamValid(substitutionsJson))
    {
        message->SetObjectField(OperationParam::PushNotificationSendParamSubstitution.getValue(), JsonUtil::jsonStringToValue(substitutionsJson));
    }

    ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendTemplatedToGroup, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPushNotification::sendNormalizedPushNotificationToGroup(const FString& groupId, const FString& alertContentJson, const FString& customDataJson, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::GroupId.getValue(), groupId);
    message->SetObjectField(OperationParam::AlertContent.getValue(), JsonUtil::jsonStringToValue(alertContentJson));

    if (OperationParam::isOptionalParamValid(customDataJson))
    {
        message->SetObjectField(OperationParam::CustomData.getValue(), JsonUtil::jsonStringToValue(customDataJson));
    }

    ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendNormalizedToGroup, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPushNotification::sendNormalizedPushNotification(const FString& toProfileId, const FString& alertContentJson, const FString& customDataJson, IServerCallback * callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::PushNotificationSendParamToPlayerId.getValue(), toProfileId);
	message->SetObjectField(OperationParam::AlertContent.getValue(), JsonUtil::jsonStringToValue(alertContentJson));

	if (OperationParam::isOptionalParamValid(customDataJson))
	{
		message->SetObjectField(OperationParam::CustomData.getValue(), JsonUtil::jsonStringToValue(customDataJson));
	}

	ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendNormalized, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPushNotification::sendNormalizedPushNotificationBatch(const TArray<FString> profileIds, const FString& alertContentJson, const FString& customDataJson, IServerCallback * callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetArrayField(OperationParam::ProfileIds.getValue(), JsonUtil::arrayToJsonArray(profileIds));
	message->SetObjectField(OperationParam::AlertContent.getValue(), JsonUtil::jsonStringToValue(alertContentJson));

	if (OperationParam::isOptionalParamValid(customDataJson))
	{
		message->SetObjectField(OperationParam::CustomData.getValue(), JsonUtil::jsonStringToValue(customDataJson));
	}

	ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendNormalizedBatch, message, callback);
	_client->sendRequest(sc);
}