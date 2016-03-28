// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudPlayerStatisticsEvent.h"

#include "BrainCloudClient.h"
#include "IServerCallback.h"
#include "ServerCall.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "OperationParam.h"
#include "json/json.h"

#include "JsonUtil.h"

namespace BrainCloud
{
    BrainCloudPlayerStatisticsEvent::BrainCloudPlayerStatisticsEvent(BrainCloudClient* in_client) : m_client(in_client) { }

    void BrainCloudPlayerStatisticsEvent::triggerPlayerStatisticsEvent(const char * in_eventName, int32_t in_eventMultiplier, IServerCallback * in_callback)
    {
        Json::Value message;

        message[OperationParam::PlayerStatisticEventServiceEventName.getValue()] = in_eventName;
        message[OperationParam::PlayerStatisticEventServiceEventMultiplier.getValue()] = in_eventMultiplier;

        ServerCall * sc = new ServerCall(ServiceName::PlayerStatisticsEvent, ServiceOperation::Trigger, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudPlayerStatisticsEvent::triggerPlayerStatisticsEvents(const std::string& in_jsonData, IServerCallback * in_callback)
    {
        Json::Value message;

        message[OperationParam::PlayerStatisticEventServiceEvents.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);

        ServerCall * sc = new ServerCall(ServiceName::PlayerStatisticsEvent, ServiceOperation::TriggerMultiple, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }
}