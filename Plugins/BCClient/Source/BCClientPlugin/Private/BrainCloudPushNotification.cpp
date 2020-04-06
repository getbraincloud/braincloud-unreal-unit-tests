// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudPushNotification.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"
#include "BCPlatform.h"

BrainCloudPushNotification::BrainCloudPushNotification(BrainCloudClient *client) : _client(client) {}

void BrainCloudPushNotification::deregisterAllPushNotificationDeviceTokens(IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	ServerCall *sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::DeregisterAll, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPushNotification::deregisterPushNotificationDeviceToken(EBCPlatform platform, const FString &token, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::PushNotificationRegisterParamDeviceType.getValue(), BCPlatform::EnumToString(platform));
	message->SetStringField(OperationParam::PushNotificationRegisterParamDeviceToken.getValue(), token);

	ServerCall *sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::Deregister, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPushNotification::registerPushNotificationDeviceToken(EBCPlatform platform, const FString &deviceToken, IServerCallback *callback)
{
	registerPushNotificationDeviceToken(BCPlatform::EnumToString(platform), deviceToken, callback);
}

void BrainCloudPushNotification::registerPushNotificationDeviceToken(const FString &type, const FString &token, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::PushNotificationRegisterParamDeviceType.getValue(), type);
	message->SetStringField(OperationParam::PushNotificationRegisterParamDeviceToken.getValue(), token);

	ServerCall *sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::Register, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPushNotification::sendSimplePushNotification(const FString &toProfileId, const FString &message, IServerCallback *callback)
{
	TSharedRef<FJsonObject> messageObj = MakeShareable(new FJsonObject());
	messageObj->SetStringField(OperationParam::PushNotificationSendParamToPlayerId.getValue(), toProfileId);
	messageObj->SetStringField(OperationParam::PushNotificationSendParamMessage.getValue(), message);

	ServerCall *sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendSimple, messageObj, callback);
	_client->sendRequest(sc);
}

void BrainCloudPushNotification::sendRichPushNotification(const FString &toProfileId, int32 notificationTemplateId, IServerCallback *callback)
{
	sendRichPushNotificationWithParams(toProfileId, notificationTemplateId, "", callback);
}

void BrainCloudPushNotification::sendRichPushNotificationWithParams(const FString &toProfileId, int32 notificationTemplateId, const FString &substitutionJson, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::PushNotificationSendParamToPlayerId.getValue(), toProfileId);
	message->SetNumberField(OperationParam::PushNotificationSendParamNotificationTemplateId.getValue(), notificationTemplateId);

	if (OperationParam::isOptionalParamValid(substitutionJson))
	{
		message->SetObjectField(OperationParam::PushNotificationSendParamSubstitution.getValue(), JsonUtil::jsonStringToValue(substitutionJson));
	}

	ServerCall *sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendRich, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPushNotification::sendTemplatedPushNotificationToGroup(const FString &groupId, int32 notificationTemplateId, const FString &substitutionsJson, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetNumberField(OperationParam::PushNotificationSendParamNotificationTemplateId.getValue(), notificationTemplateId);

	if (OperationParam::isOptionalParamValid(substitutionsJson))
	{
		message->SetObjectField(OperationParam::PushNotificationSendParamSubstitution.getValue(), JsonUtil::jsonStringToValue(substitutionsJson));
	}

	ServerCall *sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendTemplatedToGroup, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPushNotification::sendNormalizedPushNotificationToGroup(const FString &groupId, const FString &alertContentJson, const FString &customDataJson, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetObjectField(OperationParam::AlertContent.getValue(), JsonUtil::jsonStringToValue(alertContentJson));

	if (OperationParam::isOptionalParamValid(customDataJson))
	{
		message->SetObjectField(OperationParam::CustomData.getValue(), JsonUtil::jsonStringToValue(customDataJson));
	}

	ServerCall *sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendNormalizedToGroup, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPushNotification::scheduleRawPushNotificationUTC(const FString &profileId, const FString &fcmContent, const FString &iosContent, const FString &facebookContent, int64 startTime, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::ProfileId.getValue(), profileId);

	if (OperationParam::isOptionalParamValid(fcmContent))
	{
		message->SetObjectField(OperationParam::FcmContent.getValue(), JsonUtil::jsonStringToValue(fcmContent));
	}

	if (OperationParam::isOptionalParamValid(iosContent))
	{
		message->SetObjectField(OperationParam::IosContent.getValue(), JsonUtil::jsonStringToValue(iosContent));
	}

	if (OperationParam::isOptionalParamValid(facebookContent))
	{
		message->SetObjectField(OperationParam::FacebookContent.getValue(), JsonUtil::jsonStringToValue(facebookContent));
	}

	message->SetNumberField(OperationParam::StartTimeUTC.getValue(), startTime);

	ServerCall *sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::ScheduledRawNotifcation, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPushNotification::scheduleRawPushNotificationMinutes(const FString &profileId, const FString &fcmContent, const FString &iosContent, const FString &facebookContent, int32 minutesFromNow, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::ProfileId.getValue(), profileId);

	if (OperationParam::isOptionalParamValid(fcmContent))
	{
		message->SetObjectField(OperationParam::FcmContent.getValue(), JsonUtil::jsonStringToValue(fcmContent));
	}

	if (OperationParam::isOptionalParamValid(iosContent))
	{
		message->SetObjectField(OperationParam::IosContent.getValue(), JsonUtil::jsonStringToValue(iosContent));
	}

	if (OperationParam::isOptionalParamValid(facebookContent))
	{
		message->SetObjectField(OperationParam::FacebookContent.getValue(), JsonUtil::jsonStringToValue(facebookContent));
	}

	message->SetNumberField(OperationParam::MinutesFromNow.getValue(), minutesFromNow);

	ServerCall *sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::ScheduledRawNotifcation, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPushNotification::sendRawPushNotification(const FString &profileId, const FString &fcmContent, const FString &iosContent, const FString &facebookContent, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::PushNotificationSendParamToPlayerId.getValue(), profileId);

	if (OperationParam::isOptionalParamValid(fcmContent))
	{
		message->SetObjectField(OperationParam::FcmContent.getValue(), JsonUtil::jsonStringToValue(fcmContent));
	}

	if (OperationParam::isOptionalParamValid(iosContent))
	{
		message->SetObjectField(OperationParam::IosContent.getValue(), JsonUtil::jsonStringToValue(iosContent));
	}

	if (OperationParam::isOptionalParamValid(facebookContent))
	{
		message->SetObjectField(OperationParam::FacebookContent.getValue(), JsonUtil::jsonStringToValue(facebookContent));
	}

	ServerCall *sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendRaw, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPushNotification::sendRawPushNotificationBatch(const TArray<FString> profileIds, const FString &fcmContent, const FString &iosContent, const FString &facebookContent, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetArrayField(OperationParam::ProfileIds.getValue(), JsonUtil::arrayToJsonArray(profileIds));

	if (OperationParam::isOptionalParamValid(fcmContent))
	{
		message->SetObjectField(OperationParam::FcmContent.getValue(), JsonUtil::jsonStringToValue(fcmContent));
	}

	if (OperationParam::isOptionalParamValid(iosContent))
	{
		message->SetObjectField(OperationParam::IosContent.getValue(), JsonUtil::jsonStringToValue(iosContent));
	}

	if (OperationParam::isOptionalParamValid(facebookContent))
	{
		message->SetObjectField(OperationParam::FacebookContent.getValue(), JsonUtil::jsonStringToValue(facebookContent));
	}

	ServerCall *sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendRawBatch, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPushNotification::sendRawPushNotificationToGroup(const FString &groupId, const FString &fcmContent, const FString &iosContent, const FString &facebookContent, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);

	if (OperationParam::isOptionalParamValid(fcmContent))
	{
		message->SetObjectField(OperationParam::FcmContent.getValue(), JsonUtil::jsonStringToValue(fcmContent));
	}

	if (OperationParam::isOptionalParamValid(iosContent))
	{
		message->SetObjectField(OperationParam::IosContent.getValue(), JsonUtil::jsonStringToValue(iosContent));
	}

	if (OperationParam::isOptionalParamValid(facebookContent))
	{
		message->SetObjectField(OperationParam::FacebookContent.getValue(), JsonUtil::jsonStringToValue(facebookContent));
	}

	ServerCall *sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendRawToGroup, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPushNotification::scheduleNormalizedPushNotificationUTC(const FString &profileId, const FString &alertContentJson, const FString &customDataJson, const int64 startTime, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::PushNotificationSendParamProfileId.getValue(), profileId);
	message->SetObjectField(OperationParam::AlertContent.getValue(), JsonUtil::jsonStringToValue(alertContentJson));

	if (OperationParam::isOptionalParamValid(customDataJson))
	{
		message->SetObjectField(OperationParam::CustomData.getValue(), JsonUtil::jsonStringToValue(customDataJson));
	}

	message->SetNumberField(OperationParam::StartTimeUTC.getValue(), startTime);

	ServerCall *sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::ScheduleNormalizedNotifcation, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPushNotification::scheduleNormalizedPushNotificationMinutes(const FString &profileId, const FString &alertContentJson, const FString &customDataJson, const int32 minutesFromNow, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::PushNotificationSendParamProfileId.getValue(), profileId);
	message->SetObjectField(OperationParam::AlertContent.getValue(), JsonUtil::jsonStringToValue(alertContentJson));

	if (OperationParam::isOptionalParamValid(customDataJson))
	{
		message->SetObjectField(OperationParam::CustomData.getValue(), JsonUtil::jsonStringToValue(customDataJson));
	}

	message->SetNumberField(OperationParam::MinutesFromNow.getValue(), minutesFromNow);

	ServerCall *sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::ScheduleNormalizedNotifcation, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPushNotification::scheduleRichPushNotificationUTC(const FString &profileId, const int32 notificationTemplateId, const FString &substitutionJson, const int64 startTime, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::PushNotificationSendParamProfileId.getValue(), profileId);
	message->SetNumberField(OperationParam::PushNotificationSendParamNotificationTemplateId.getValue(), notificationTemplateId);

	if (OperationParam::isOptionalParamValid(substitutionJson))
	{
		message->SetObjectField(OperationParam::PushNotificationSendParamSubstitution.getValue(), JsonUtil::jsonStringToValue(substitutionJson));
	}

	message->SetNumberField(OperationParam::StartTimeUTC.getValue(), startTime);

	ServerCall *sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::ScheduledRichNotifcation, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPushNotification::scheduleRichPushNotificationMinutes(const FString &profileId, const int32 notificationTemplateId, const FString &substitutionJson, const int32 minutesFromNow, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::PushNotificationSendParamProfileId.getValue(), profileId);
	message->SetNumberField(OperationParam::PushNotificationSendParamNotificationTemplateId.getValue(), notificationTemplateId);

	if (OperationParam::isOptionalParamValid(substitutionJson))
	{
		message->SetObjectField(OperationParam::PushNotificationSendParamSubstitution.getValue(), JsonUtil::jsonStringToValue(substitutionJson));
	}

	message->SetNumberField(OperationParam::StartTimeUTC.getValue(), minutesFromNow);

	ServerCall *sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::ScheduledRichNotifcation, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPushNotification::sendNormalizedPushNotification(const FString &toProfileId, const FString &alertContentJson, const FString &customDataJson, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::PushNotificationSendParamToPlayerId.getValue(), toProfileId);
	message->SetObjectField(OperationParam::AlertContent.getValue(), JsonUtil::jsonStringToValue(alertContentJson));

	if (OperationParam::isOptionalParamValid(customDataJson))
	{
		message->SetObjectField(OperationParam::CustomData.getValue(), JsonUtil::jsonStringToValue(customDataJson));
	}

	ServerCall *sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendNormalized, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPushNotification::sendNormalizedPushNotificationBatch(const TArray<FString> profileIds, const FString &alertContentJson, const FString &customDataJson, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetArrayField(OperationParam::ProfileIds.getValue(), JsonUtil::arrayToJsonArray(profileIds));
	message->SetObjectField(OperationParam::AlertContent.getValue(), JsonUtil::jsonStringToValue(alertContentJson));

	if (OperationParam::isOptionalParamValid(customDataJson))
	{
		message->SetObjectField(OperationParam::CustomData.getValue(), JsonUtil::jsonStringToValue(customDataJson));
	}

	ServerCall *sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendNormalizedBatch, message, callback);
	_client->sendRequest(sc);
}