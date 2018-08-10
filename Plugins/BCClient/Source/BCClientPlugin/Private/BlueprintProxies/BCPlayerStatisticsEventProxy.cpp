// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloudActor.h"
#include "BCWrapperProxy.h"
#include "BCPlayerStatisticsEventProxy.h"
#include "BrainCloudWrapper.h"

UBCPlayerStatisticsEventProxy::UBCPlayerStatisticsEventProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCPlayerStatisticsEventProxy* UBCPlayerStatisticsEventProxy::TriggerPlayerStatisticsEvent(UBrainCloudWrapper *brainCloudWrapper, FString eventName, int32 eventMultiplier)
{
	UBCPlayerStatisticsEventProxy* Proxy = NewObject<UBCPlayerStatisticsEventProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStatisticsEventService()->triggerStatsEvent(eventName, eventMultiplier, Proxy);
	return Proxy;
}

UBCPlayerStatisticsEventProxy* UBCPlayerStatisticsEventProxy::TriggerStatsEvent(UBrainCloudWrapper *brainCloudWrapper, FString eventName, int32 eventMultiplier)
{
    UBCPlayerStatisticsEventProxy* Proxy = NewObject<UBCPlayerStatisticsEventProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStatisticsEventService()->triggerStatsEvent(eventName, eventMultiplier, Proxy);
    return Proxy;
}

UBCPlayerStatisticsEventProxy* UBCPlayerStatisticsEventProxy::TriggerPlayerStatisticsEvents(UBrainCloudWrapper *brainCloudWrapper, FString jsonData)
{
	UBCPlayerStatisticsEventProxy* Proxy = NewObject<UBCPlayerStatisticsEventProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStatisticsEventService()->triggerStatsEvents(jsonData, Proxy);
	return Proxy;
}

UBCPlayerStatisticsEventProxy* UBCPlayerStatisticsEventProxy::TriggerStatsEvents(UBrainCloudWrapper *brainCloudWrapper, FString jsonData)
{
    UBCPlayerStatisticsEventProxy* Proxy = NewObject<UBCPlayerStatisticsEventProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStatisticsEventService()->triggerStatsEvents(jsonData, Proxy);
    return Proxy;
}
