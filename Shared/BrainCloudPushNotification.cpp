// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudPushNotification.h"

#include "BrainCloudClient.h"
#include "IServerCallback.h"
#include "ServerCall.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "OperationParam.h"
#include "json/json.h"

#include "StringUtil.h"
#include "JsonUtil.h"
#include "Platform.h"

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

    void BrainCloudPushNotification::registerPushNotificationDeviceToken(const char * in_type, const char * in_token, IServerCallback * in_callback)
    {
        const Platform & platform = Platform::fromString(in_type);
        registerPushNotificationDeviceToken(platform, in_token, in_callback);
    }

    void BrainCloudPushNotification::sendSimplePushNotification(const char * in_toPlayerId, const char * in_message, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::PushNotificationSendParamToPlayerId.getValue()] = in_toPlayerId;
        message[OperationParam::PushNotificationSendParamMessage.getValue()] = in_message;

        ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendSimple, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }


    void BrainCloudPushNotification::sendRichPushNotification(const char * in_toPlayerId, int32_t in_notificationTemplateId, IServerCallback * in_callback)
    {
        sendRichPushNotification(in_toPlayerId, in_notificationTemplateId, NULL, in_callback);
    }

    void BrainCloudPushNotification::sendRichPushNotificationWithParams(const char * in_toPlayerId, int32_t in_notificationTemplateId, const char * in_substitutionJson, IServerCallback * in_callback)
    {
        sendRichPushNotification(in_toPlayerId, in_notificationTemplateId, in_substitutionJson, in_callback);
    }

    void BrainCloudPushNotification::sendRichPushNotification(const char * in_toPlayerId, int32_t in_notificationTemplateId, const char * in_substitutionJson, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::PushNotificationSendParamToPlayerId.getValue()] = in_toPlayerId;
        message[OperationParam::PushNotificationSendParamNotificationTemplateId.getValue()] = in_notificationTemplateId;

        if (StringUtil::IsOptionalParameterValid(in_substitutionJson)) {
            message[OperationParam::PushNotificationSendParamSubstitution.getValue()] = JsonUtil::jsonStringToValue(in_substitutionJson);
        }

        ServerCall * sc = new ServerCall(ServiceName::PushNotification, ServiceOperation::SendRich, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }
}