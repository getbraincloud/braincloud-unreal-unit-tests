// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloudActor.h"
#include "BCWrapperProxy.h"
#include "BCGlobalStatisticsProxy.h"
#include "BrainCloudWrapper.h"

UBCGlobalStatisticsProxy::UBCGlobalStatisticsProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCGlobalStatisticsProxy* UBCGlobalStatisticsProxy::ReadAllGlobalStats(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCGlobalStatisticsProxy* Proxy = NewObject<UBCGlobalStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalStatisticsService()->readAllGlobalStats(Proxy);
    return Proxy;
}

UBCGlobalStatisticsProxy* UBCGlobalStatisticsProxy::ReadGlobalStatsSubset(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString>& globalStats)
{
    UBCGlobalStatisticsProxy* Proxy = NewObject<UBCGlobalStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalStatisticsService()->readGlobalStatsSubset(globalStats, Proxy);
    return Proxy;
}

UBCGlobalStatisticsProxy* UBCGlobalStatisticsProxy::ReadGlobalStatsForCategory(UBrainCloudWrapper *brainCloudWrapper, FString category)
{
    UBCGlobalStatisticsProxy* Proxy = NewObject<UBCGlobalStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalStatisticsService()->readGlobalStatsForCategory(category, Proxy);
    return Proxy;
}

UBCGlobalStatisticsProxy* UBCGlobalStatisticsProxy::IncrementGlobalGameStat(UBrainCloudWrapper *brainCloudWrapper, FString jsonData)
{
    UBCGlobalStatisticsProxy* Proxy = NewObject<UBCGlobalStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalStatisticsService()->incrementGlobalGameStat(jsonData, Proxy);
    return Proxy;
}

UBCGlobalStatisticsProxy* UBCGlobalStatisticsProxy::ProcessStatistics(UBrainCloudWrapper *brainCloudWrapper, FString jsonData)
{
	UBCGlobalStatisticsProxy* Proxy = NewObject<UBCGlobalStatisticsProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalStatisticsService()->processStatistics(jsonData, Proxy);
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