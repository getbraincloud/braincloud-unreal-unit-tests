// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCPlayerStatisticsProxy.h"

UBCPlayerStatisticsProxy::UBCPlayerStatisticsProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::ReadAllPlayerStats()
{
    UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
    BrainCloudClient::getInstance()->getPlayerStatisticsService()->readAllPlayerStats(Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::ReadPlayerStatsSubset(const TArray<FString>& playerStats)
{
    UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
    BrainCloudClient::getInstance()->getPlayerStatisticsService()->readPlayerStatsSubset(playerStats, Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::ReadPlayerStatisticsByCategory(FString category)
{
    UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
    BrainCloudClient::getInstance()->getPlayerStatisticsService()->readPlayerStatisticsByCategory(category, Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::ResetAllPlayerStats()
{
    UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
    BrainCloudClient::getInstance()->getPlayerStatisticsService()->resetAllPlayerStats(Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::IncrementPlayerStats(FString jsonData)
{
    UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
    BrainCloudClient::getInstance()->getPlayerStatisticsService()->incrementPlayerStats(jsonData, Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::GetNextExperienceLevel()
{
    UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
    BrainCloudClient::getInstance()->getPlayerStatisticsService()->getNextExperienceLevel(Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::IncrementExperiencePoints(int32 xpValue)
{
    UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
    BrainCloudClient::getInstance()->getPlayerStatisticsService()->incrementExperiencePoints(xpValue, Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::SetExperiencePoints(int32 xpValue)
{
    UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
    BrainCloudClient::getInstance()->getPlayerStatisticsService()->setExperiencePoints(xpValue, Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy* UBCPlayerStatisticsProxy::ProcessStatistics(FString jsonData)
{
	UBCPlayerStatisticsProxy* Proxy = NewObject<UBCPlayerStatisticsProxy>();
	BrainCloudClient::getInstance()->getPlayerStatisticsService()->processStatistics(jsonData, Proxy);
	return Proxy;
}

//callbacks
void UBCPlayerStatisticsProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
}

void UBCPlayerStatisticsProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
}
