// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudPlayerStatisticsEvent.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudPlayerStatisticsEvent::BrainCloudPlayerStatisticsEvent(BrainCloudClient *client) : _client(client){};

void BrainCloudPlayerStatisticsEvent::triggerStatsEvent(const FString &eventName, int32 eventMultiplier, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    message->SetStringField(OperationParam::PlayerStatisticEventServiceEventName.getValue(), eventName);
    message->SetNumberField(OperationParam::PlayerStatisticEventServiceEventMultiplier.getValue(), eventMultiplier);

    ServerCall *sc = new ServerCall(ServiceName::PlayerStatisticsEvent, ServiceOperation::Trigger, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlayerStatisticsEvent::triggerStatsEvents(const FString &jsonData, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    message->SetField(OperationParam::PlayerStatisticEventServiceEvents.getValue(), JsonUtil::jsonStringToActualValue(jsonData));

    ServerCall *sc = new ServerCall(ServiceName::PlayerStatisticsEvent, ServiceOperation::TriggerMultiple, message, callback);
    _client->sendRequest(sc);
}