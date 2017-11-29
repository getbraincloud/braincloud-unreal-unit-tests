// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloud.h"
#include "BCWrapperProxy.h"
#include "BCPlayerStatisticsEventProxy.h"
#include "BrainCloudWrapper.h"

UBCPlayerStatisticsEventProxy::UBCPlayerStatisticsEventProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCPlayerStatisticsEventProxy* UBCPlayerStatisticsEventProxy::TriggerPlayerStatisticsEvent(ABrainCloud *brainCloud, FString eventName, int32 eventMultiplier)
{
	UBCPlayerStatisticsEventProxy* Proxy = NewObject<UBCPlayerStatisticsEventProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStatisticsEventService()->triggerStatsEvent(eventName, eventMultiplier, Proxy);
	return Proxy;
}

UBCPlayerStatisticsEventProxy* UBCPlayerStatisticsEventProxy::TriggerStatsEvent(ABrainCloud *brainCloud, FString eventName, int32 eventMultiplier)
{
    UBCPlayerStatisticsEventProxy* Proxy = NewObject<UBCPlayerStatisticsEventProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStatisticsEventService()->triggerStatsEvent(eventName, eventMultiplier, Proxy);
    return Proxy;
}

UBCPlayerStatisticsEventProxy* UBCPlayerStatisticsEventProxy::TriggerPlayerStatisticsEvents(ABrainCloud *brainCloud, FString jsonData)
{
	UBCPlayerStatisticsEventProxy* Proxy = NewObject<UBCPlayerStatisticsEventProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStatisticsEventService()->triggerStatsEvents(jsonData, Proxy);
	return Proxy;
}

UBCPlayerStatisticsEventProxy* UBCPlayerStatisticsEventProxy::TriggerStatsEvents(ABrainCloud *brainCloud, FString jsonData)
{
    UBCPlayerStatisticsEventProxy* Proxy = NewObject<UBCPlayerStatisticsEventProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStatisticsEventService()->triggerStatsEvents(jsonData, Proxy);
    return Proxy;
}

//callbacks
void UBCPlayerStatisticsEventProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCPlayerStatisticsEventProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

