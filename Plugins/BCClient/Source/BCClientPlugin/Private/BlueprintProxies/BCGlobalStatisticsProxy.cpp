// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCGlobalStatisticsProxy.h"

UBCGlobalStatisticsProxy::UBCGlobalStatisticsProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCGlobalStatisticsProxy* UBCGlobalStatisticsProxy::ReadAllGlobalStats()
{
    UBCGlobalStatisticsProxy* Proxy = NewObject<UBCGlobalStatisticsProxy>();
    BrainCloudClient::getInstance()->getGlobalStatisticsService()->readAllGlobalStats(Proxy);
    return Proxy;
}

UBCGlobalStatisticsProxy* UBCGlobalStatisticsProxy::ReadGlobalStatsSubset(const TArray<FString>& globalStats)
{
    UBCGlobalStatisticsProxy* Proxy = NewObject<UBCGlobalStatisticsProxy>();
    BrainCloudClient::getInstance()->getGlobalStatisticsService()->readGlobalStatsSubset(globalStats, Proxy);
    return Proxy;
}

UBCGlobalStatisticsProxy* UBCGlobalStatisticsProxy::ReadGlobalStatsForCategory(FString category)
{
    UBCGlobalStatisticsProxy* Proxy = NewObject<UBCGlobalStatisticsProxy>();
    BrainCloudClient::getInstance()->getGlobalStatisticsService()->readGlobalStatsForCategory(category, Proxy);
    return Proxy;
}

UBCGlobalStatisticsProxy* UBCGlobalStatisticsProxy::IncrementGlobalGameStat(FString jsonData)
{
    UBCGlobalStatisticsProxy* Proxy = NewObject<UBCGlobalStatisticsProxy>();
    BrainCloudClient::getInstance()->getGlobalStatisticsService()->incrementGlobalGameStat(jsonData, Proxy);
    return Proxy;
}

UBCGlobalStatisticsProxy* UBCGlobalStatisticsProxy::ProcessStatistics(FString jsonData)
{
	UBCGlobalStatisticsProxy* Proxy = NewObject<UBCGlobalStatisticsProxy>();
	BrainCloudClient::getInstance()->getGlobalStatisticsService()->processStatistics(jsonData, Proxy);
	return Proxy;
}

//callbacks
void UBCGlobalStatisticsProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCGlobalStatisticsProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}