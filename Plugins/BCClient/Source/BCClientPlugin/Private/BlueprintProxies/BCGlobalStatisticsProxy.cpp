// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCGlobalStatisticsProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCGlobalStatisticsProxy::UBCGlobalStatisticsProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCGlobalStatisticsProxy *UBCGlobalStatisticsProxy::ReadAllGlobalStats(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCGlobalStatisticsProxy *Proxy = NewObject<UBCGlobalStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalStatisticsService()->readAllGlobalStats(Proxy);
    return Proxy;
}

UBCGlobalStatisticsProxy *UBCGlobalStatisticsProxy::ReadGlobalStatsSubset(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &globalStats)
{
    UBCGlobalStatisticsProxy *Proxy = NewObject<UBCGlobalStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalStatisticsService()->readGlobalStatsSubset(globalStats, Proxy);
    return Proxy;
}

UBCGlobalStatisticsProxy *UBCGlobalStatisticsProxy::ReadGlobalStatsForCategory(UBrainCloudWrapper *brainCloudWrapper, FString category)
{
    UBCGlobalStatisticsProxy *Proxy = NewObject<UBCGlobalStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalStatisticsService()->readGlobalStatsForCategory(category, Proxy);
    return Proxy;
}

UBCGlobalStatisticsProxy *UBCGlobalStatisticsProxy::IncrementGlobalGameStat(UBrainCloudWrapper *brainCloudWrapper, FString jsonData)
{
    UBCGlobalStatisticsProxy *Proxy = NewObject<UBCGlobalStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalStatisticsService()->incrementGlobalGameStat(jsonData, Proxy);
    return Proxy;
}

UBCGlobalStatisticsProxy *UBCGlobalStatisticsProxy::ProcessStatistics(UBrainCloudWrapper *brainCloudWrapper, FString jsonData)
{
    UBCGlobalStatisticsProxy *Proxy = NewObject<UBCGlobalStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalStatisticsService()->processStatistics(jsonData, Proxy);
    return Proxy;
}
