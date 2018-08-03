// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloudActor.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCPlayerStatisticsProxy.h"

UBCPlayerStatisticsProxy::UBCPlayerStatisticsProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::ReadAllPlayerStats(ABrainCloudActor *brainCloud)
{
	UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStatisticsService()->readAllUserStats(Proxy);
	return Proxy;
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::ReadAllUserStats(ABrainCloudActor *brainCloud)
{
    UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStatisticsService()->readAllUserStats(Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::ReadPlayerStatsSubset(ABrainCloudActor *brainCloud, const TArray<FString>& playerStats)
{
	UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStatisticsService()->readUserStatsSubset(playerStats, Proxy);
	return Proxy;
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::ReadUserStatsSubset(ABrainCloudActor *brainCloud, const TArray<FString>& playerStats)
{
    UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStatisticsService()->readUserStatsSubset(playerStats, Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::ReadPlayerStatisticsByCategory(ABrainCloudActor *brainCloud, FString category)
{
	UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStatisticsService()->readUserStatisticsByCategory(category, Proxy);
	return Proxy;
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::ReadUserStatisticsByCategory(ABrainCloudActor *brainCloud, FString category)
{
    UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStatisticsService()->readUserStatisticsByCategory(category, Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::ResetAllPlayerStats(ABrainCloudActor *brainCloud)
{
	UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStatisticsService()->resetAllUserStats(Proxy);
	return Proxy;
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::ResetAllUserStats(ABrainCloudActor *brainCloud)
{
    UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStatisticsService()->resetAllUserStats(Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::IncrementPlayerStats(ABrainCloudActor *brainCloud, FString jsonData)
{
	UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStatisticsService()->incrementUserStats(jsonData, Proxy);
	return Proxy;
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::IncrementUserStats(ABrainCloudActor *brainCloud, FString jsonData)
{
    UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStatisticsService()->incrementUserStats(jsonData, Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::GetNextExperienceLevel(ABrainCloudActor *brainCloud)
{
    UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStatisticsService()->getNextExperienceLevel(Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::IncrementExperiencePoints(ABrainCloudActor *brainCloud, int32 xpValue)
{
    UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStatisticsService()->incrementExperiencePoints(xpValue, Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::SetExperiencePoints(ABrainCloudActor *brainCloud, int32 xpValue)
{
    UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStatisticsService()->setExperiencePoints(xpValue, Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::ProcessStatistics(ABrainCloudActor *brainCloud, FString jsonData)
{
	UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlayerStatisticsService()->processStatistics(jsonData, Proxy);
	return Proxy;
}

//callbacks
void UBCPlayerStatisticsProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCPlayerStatisticsProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

