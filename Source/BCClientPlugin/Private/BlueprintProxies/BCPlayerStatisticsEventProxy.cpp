// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCPlayerStatisticsEventProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCPlayerStatisticsEventProxy::UBCPlayerStatisticsEventProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCPlayerStatisticsEventProxy *UBCPlayerStatisticsEventProxy::TriggerStatsEvent(UBrainCloudWrapper *brainCloudWrapper, FString eventName, int32 eventMultiplier)
{
    UBCPlayerStatisticsEventProxy *Proxy = NewObject<UBCPlayerStatisticsEventProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStatisticsEventService()->triggerStatsEvent(eventName, eventMultiplier, Proxy);
    return Proxy;
}

UBCPlayerStatisticsEventProxy *UBCPlayerStatisticsEventProxy::TriggerStatsEvents(UBrainCloudWrapper *brainCloudWrapper, FString jsonData)
{
    UBCPlayerStatisticsEventProxy *Proxy = NewObject<UBCPlayerStatisticsEventProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStatisticsEventService()->triggerStatsEvents(jsonData, Proxy);
    return Proxy;
}
