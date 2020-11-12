// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudPlayerStatisticsEvent.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

#include "braincloud/internal/JsonUtil.h"

namespace BrainCloud
{
    BrainCloudPlayerStatisticsEvent::BrainCloudPlayerStatisticsEvent(BrainCloudClient* in_client) : m_client(in_client) { }

    void BrainCloudPlayerStatisticsEvent::triggerStatsEvent(const char *in_eventName, int32_t in_eventMultiplier,
                                                            IServerCallback *in_callback)
    {
        Json::Value message;

        message[OperationParam::PlayerStatisticEventServiceEventName.getValue()] = in_eventName;
        message[OperationParam::PlayerStatisticEventServiceEventMultiplier.getValue()] = in_eventMultiplier;

        ServerCall * sc = new ServerCall(ServiceName::PlayerStatisticsEvent, ServiceOperation::Trigger, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudPlayerStatisticsEvent::triggerStatsEvents(const std::string &in_jsonData,
                                                             IServerCallback *in_callback)
    {
        Json::Value message;

        message[OperationParam::PlayerStatisticEventServiceEvents.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);

        ServerCall * sc = new ServerCall(ServiceName::PlayerStatisticsEvent, ServiceOperation::TriggerMultiple, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }
}