// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudPushNotification.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

#include "braincloud/internal/StringUtil.h"
#include "braincloud/internal/JsonUtil.h"
#include "braincloud/Platform.h"

namespace BrainCloud
{
	BrainCloudPushNotification::BrainCloudPushNotification(BrainCloudClient* in_client) : m_client(in_client) { }

	void BrainCloudPushNotification::deregisterAllPushNotificationDeviceTokens(IServerCallback * in_callback)
	{
		Json::Value message = Json::nullValue;
		ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::DeregisterAll, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudPushNotification::deregisterPushNotificationDeviceToken(const Platform & in_platform, const char * in_token, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::PushNotificationRegisterParamDeviceType.getValue()] = in_platform.toString().c_str();
		message[OperationParam::PushNotificationRegisterParamDeviceToken.getValue()] = in_token;

		ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::Deregister, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudPushNotification::registerPushNotificationDeviceToken(const Platform & in_platform, const char * in_token, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::PushNotificationRegisterParamDeviceType.getValue()] = in_platform.toString().c_str();
		message[OperationParam::PushNotificationRegisterParamDeviceToken.getValue()] = in_token;

		ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::Register, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudPushNotification::sendSimplePushNotification(const char * in_toProfileId, const char * in_message, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::PushNotificationSendParamToPlayerId.getValue()] = in_toProfileId;
		message[OperationParam::PushNotificationSendParamMessage.getValue()] = in_message;

		ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendSimple, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}


	void BrainCloudPushNotification::sendRichPushNotification(const char * in_toProfileId, int32_t in_notificationTemplateId, IServerCallback * in_callback)
	{
		sendRichPushNotification(in_toProfileId, in_notificationTemplateId, NULL, in_callback);
	}

	void BrainCloudPushNotification::sendRichPushNotificationWithParams(const char * in_toProfileId, int32_t in_notificationTemplateId, const char * in_substitutionJson, IServerCallback * in_callback)
	{
		sendRichPushNotification(in_toProfileId, in_notificationTemplateId, in_substitutionJson, in_callback);
	}

	void BrainCloudPushNotification::sendTemplatedPushNotificationToGroup(const char * in_groupId, int32_t in_notificationTemplateId, std::string in_substitutionsJson, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::PushNotificationSendParamNotificationTemplateId.getValue()] = in_notificationTemplateId;

		if (StringUtil::IsOptionalParameterValid(in_substitutionsJson)) {
			message[OperationParam::PushNotificationSendParamSubstitution.getValue()] = JsonUtil::jsonStringToValue(in_substitutionsJson);
		}

		ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendTemplatedToGroup, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudPushNotification::sendNormalizedPushNotificationToGroup(const char * in_groupId, std::string in_alertContentJson, std::string in_customDataJson, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::AlertContent.getValue()] = JsonUtil::jsonStringToValue(in_alertContentJson);

		if (StringUtil::IsOptionalParameterValid(in_customDataJson)) {
			message[OperationParam::CustomData.getValue()] = JsonUtil::jsonStringToValue(in_customDataJson);
		}

		ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendNormalizedToGroup, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudPushNotification::scheduleRawPushNotificationUTC(const char * in_profileId, std::string in_fcmContent, std::string in_iosContent, std::string in_facebookContent, int32_t in_startTime, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::ProfileId.getValue()] = in_profileId;

		if (StringUtil::IsOptionalParameterValid(in_fcmContent)) {
			message[OperationParam::FcmContent.getValue()] = JsonUtil::jsonStringToValue(in_fcmContent);
		}

		if (StringUtil::IsOptionalParameterValid(in_iosContent)) {
			message[OperationParam::IosContent.getValue()] = JsonUtil::jsonStringToValue(in_iosContent);
		}

		if (StringUtil::IsOptionalParameterValid(in_facebookContent)) {
			message[OperationParam::FacebookContent.getValue()] = JsonUtil::jsonStringToValue(in_facebookContent);
		}

		message[OperationParam::StartDateUTC.getValue()] = in_startTime;

		ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::ScheduleRawNotification, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudPushNotification::scheduleRawPushNotificationMinutes(const char * in_profileId, std::string in_fcmContent, std::string in_iosContent, std::string in_facebookContent, int32_t in_minutesFromNow, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::ProfileId.getValue()] = in_profileId;

		if (StringUtil::IsOptionalParameterValid(in_fcmContent)) {
			message[OperationParam::FcmContent.getValue()] = JsonUtil::jsonStringToValue(in_fcmContent);
		}

		if (StringUtil::IsOptionalParameterValid(in_iosContent)) {
			message[OperationParam::IosContent.getValue()] = JsonUtil::jsonStringToValue(in_iosContent);
		}

		if (StringUtil::IsOptionalParameterValid(in_facebookContent)) {
			message[OperationParam::FacebookContent.getValue()] = JsonUtil::jsonStringToValue(in_facebookContent);
		}

		message[OperationParam::MinutesFromNow.getValue()] = in_minutesFromNow;

		ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::ScheduleRawNotification, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudPushNotification::sendRawPushNotification(const char * in_profileId, std::string in_fcmContent, std::string in_iosContent, std::string in_facebookContent, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::PushNotificationSendParamToPlayerId.getValue()] = in_profileId;

		if (StringUtil::IsOptionalParameterValid(in_fcmContent)) {
			message[OperationParam::FcmContent.getValue()] = JsonUtil::jsonStringToValue(in_fcmContent);
		}

		if (StringUtil::IsOptionalParameterValid(in_iosContent)) {
			message[OperationParam::IosContent.getValue()] = JsonUtil::jsonStringToValue(in_iosContent);
		}

		if (StringUtil::IsOptionalParameterValid(in_facebookContent)) {
			message[OperationParam::FacebookContent.getValue()] = JsonUtil::jsonStringToValue(in_facebookContent);
		}

		ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendRaw, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudPushNotification::sendRawPushNotificationBatch(std::vector<std::string> in_profileIds, std::string in_fcmContent, std::string in_iosContent, std::string in_facebookContent, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::ProfileIds.getValue()] = JsonUtil::stringVectorToJson(in_profileIds);

		if (StringUtil::IsOptionalParameterValid(in_fcmContent)) {
			message[OperationParam::FcmContent.getValue()] = JsonUtil::jsonStringToValue(in_fcmContent);
		}

		if (StringUtil::IsOptionalParameterValid(in_iosContent)) {
			message[OperationParam::IosContent.getValue()] = JsonUtil::jsonStringToValue(in_iosContent);
		}

		if (StringUtil::IsOptionalParameterValid(in_facebookContent)) {
			message[OperationParam::FacebookContent.getValue()] = JsonUtil::jsonStringToValue(in_facebookContent);
		}

		ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendRawBatch, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudPushNotification::sendRawPushNotificationToGroup(const char * in_groupId, std::string in_fcmContent, std::string in_iosContent, std::string in_facebookContent, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;

		if (StringUtil::IsOptionalParameterValid(in_fcmContent)) {
			message[OperationParam::FcmContent.getValue()] = JsonUtil::jsonStringToValue(in_fcmContent);
		}

		if (StringUtil::IsOptionalParameterValid(in_iosContent)) {
			message[OperationParam::IosContent.getValue()] = JsonUtil::jsonStringToValue(in_iosContent);
		}

		if (StringUtil::IsOptionalParameterValid(in_facebookContent)) {
			message[OperationParam::FacebookContent.getValue()] = JsonUtil::jsonStringToValue(in_facebookContent);
		}

		ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendRawToGroup, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudPushNotification::scheduleNormalizedPushNotificationUTC(const char * in_toProfileId, std::string in_alertContentJson, std::string in_customDataJson, int32_t in_minutesFromNow, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::ProfileId.getValue()] = in_toProfileId;
		message[OperationParam::AlertContent.getValue()] = JsonUtil::jsonStringToValue(in_alertContentJson);

		if (StringUtil::IsOptionalParameterValid(in_customDataJson)) {
			message[OperationParam::CustomData.getValue()] = JsonUtil::jsonStringToValue(in_customDataJson);
		}

		message[OperationParam::MinutesFromNow.getValue()] = in_minutesFromNow;

		ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::ScheduleNormalizedNotification, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

    void BrainCloudPushNotification::scheduleNormalizedPushNotificationMinutes(const char * in_toProfileId, std::string in_alertContentJson, std::string in_customDataJson, int32_t in_minutesFromNow, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::ProfileId.getValue()] = in_toProfileId;
        message[OperationParam::AlertContent.getValue()] = JsonUtil::jsonStringToValue(in_alertContentJson);

        if (StringUtil::IsOptionalParameterValid(in_customDataJson)) {
            message[OperationParam::CustomData.getValue()] = JsonUtil::jsonStringToValue(in_customDataJson);
        }

        message[OperationParam::MinutesFromNow.getValue()] = in_minutesFromNow;

        ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::ScheduleNormalizedNotification, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

	void BrainCloudPushNotification::scheduleRichPushNotificationUTC(const char * in_toProfileId, int32_t in_notificationTemplateId, std::string in_substitutionsJson, int32_t in_startTime, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::ProfileId.getValue()] = in_toProfileId;
		message[OperationParam::PushNotificationSendParamNotificationTemplateId.getValue()] = in_notificationTemplateId;

		if (StringUtil::IsOptionalParameterValid(in_substitutionsJson)) {
			message[OperationParam::PushNotificationSendParamSubstitution.getValue()] = JsonUtil::jsonStringToValue(in_substitutionsJson);
		}

		message[OperationParam::StartDateUTC.getValue()] = in_startTime;

		ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::ScheduleRichNotification, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

    void BrainCloudPushNotification::scheduleRichPushNotificationMinutes(const char * in_toProfileId, int32_t in_notificationTemplateId, std::string in_substitutionsJson, int32_t in_minutesFromNow, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::ProfileId.getValue()] = in_toProfileId;
		message[OperationParam::PushNotificationSendParamNotificationTemplateId.getValue()] = in_notificationTemplateId;

		if (StringUtil::IsOptionalParameterValid(in_substitutionsJson)) {
			message[OperationParam::PushNotificationSendParamSubstitution.getValue()] = JsonUtil::jsonStringToValue(in_substitutionsJson);
		}

		message[OperationParam::MinutesFromNow.getValue()] = in_minutesFromNow;

		ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::ScheduleRichNotification, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudPushNotification::sendNormalizedPushNotification(const char * in_toProfileId, std::string in_alertContentJson, std::string in_customDataJson, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::PushNotificationSendParamToPlayerId.getValue()] = in_toProfileId;
		message[OperationParam::AlertContent.getValue()] = JsonUtil::jsonStringToValue(in_alertContentJson);

		if (StringUtil::IsOptionalParameterValid(in_customDataJson)) {
			message[OperationParam::CustomData.getValue()] = JsonUtil::jsonStringToValue(in_customDataJson);
		}

		ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendNormalized, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudPushNotification::sendNormalizedPushNotificationBatch(std::vector<std::string> in_profileIds, std::string in_alertContentJson, std::string in_customDataJson, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::ProfileIds.getValue()] = JsonUtil::stringVectorToJson(in_profileIds);
		message[OperationParam::AlertContent.getValue()] = JsonUtil::jsonStringToValue(in_alertContentJson);

		if (StringUtil::IsOptionalParameterValid(in_customDataJson)) {
			message[OperationParam::CustomData.getValue()] = JsonUtil::jsonStringToValue(in_customDataJson);
		}

		ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendNormalizedBatch, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudPushNotification::sendRichPushNotification(const char * in_toProfileId, int32_t in_notificationTemplateId, const char * in_substitutionJson, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::PushNotificationSendParamToPlayerId.getValue()] = in_toProfileId;
		message[OperationParam::PushNotificationSendParamNotificationTemplateId.getValue()] = in_notificationTemplateId;

		if (StringUtil::IsOptionalParameterValid(in_substitutionJson)) {
			message[OperationParam::PushNotificationSendParamSubstitution.getValue()] = JsonUtil::jsonStringToValue(in_substitutionJson);
		}

		ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendRich, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}
}