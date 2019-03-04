// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCPlayerStatisticsProxy.h"

UBCPlayerStatisticsProxy::UBCPlayerStatisticsProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCPlayerStatisticsProxy *UBCPlayerStatisticsProxy::ReadAllPlayerStats(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCPlayerStatisticsProxy *Proxy = NewObject<UBCPlayerStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStatisticsService()->readAllUserStats(Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy *UBCPlayerStatisticsProxy::ReadAllUserStats(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCPlayerStatisticsProxy *Proxy = NewObject<UBCPlayerStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStatisticsService()->readAllUserStats(Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy *UBCPlayerStatisticsProxy::ReadPlayerStatsSubset(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &playerStats)
{
    UBCPlayerStatisticsProxy *Proxy = NewObject<UBCPlayerStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStatisticsService()->readUserStatsSubset(playerStats, Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy *UBCPlayerStatisticsProxy::ReadUserStatsSubset(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &playerStats)
{
    UBCPlayerStatisticsProxy *Proxy = NewObject<UBCPlayerStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStatisticsService()->readUserStatsSubset(playerStats, Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy *UBCPlayerStatisticsProxy::ReadPlayerStatisticsByCategory(UBrainCloudWrapper *brainCloudWrapper, FString category)
{
    UBCPlayerStatisticsProxy *Proxy = NewObject<UBCPlayerStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStatisticsService()->readUserStatisticsByCategory(category, Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy *UBCPlayerStatisticsProxy::ReadUserStatisticsByCategory(UBrainCloudWrapper *brainCloudWrapper, FString category)
{
    UBCPlayerStatisticsProxy *Proxy = NewObject<UBCPlayerStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStatisticsService()->readUserStatisticsByCategory(category, Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy *UBCPlayerStatisticsProxy::ResetAllPlayerStats(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCPlayerStatisticsProxy *Proxy = NewObject<UBCPlayerStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStatisticsService()->resetAllUserStats(Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy *UBCPlayerStatisticsProxy::ResetAllUserStats(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCPlayerStatisticsProxy *Proxy = NewObject<UBCPlayerStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStatisticsService()->resetAllUserStats(Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy *UBCPlayerStatisticsProxy::IncrementPlayerStats(UBrainCloudWrapper *brainCloudWrapper, FString jsonData)
{
    UBCPlayerStatisticsProxy *Proxy = NewObject<UBCPlayerStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStatisticsService()->incrementUserStats(jsonData, Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy *UBCPlayerStatisticsProxy::IncrementUserStats(UBrainCloudWrapper *brainCloudWrapper, FString jsonData)
{
    UBCPlayerStatisticsProxy *Proxy = NewObject<UBCPlayerStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStatisticsService()->incrementUserStats(jsonData, Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy *UBCPlayerStatisticsProxy::GetNextExperienceLevel(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCPlayerStatisticsProxy *Proxy = NewObject<UBCPlayerStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStatisticsService()->getNextExperienceLevel(Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy *UBCPlayerStatisticsProxy::IncrementExperiencePoints(UBrainCloudWrapper *brainCloudWrapper, int32 xpValue)
{
    UBCPlayerStatisticsProxy *Proxy = NewObject<UBCPlayerStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStatisticsService()->incrementExperiencePoints(xpValue, Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy *UBCPlayerStatisticsProxy::SetExperiencePoints(UBrainCloudWrapper *brainCloudWrapper, int32 xpValue)
{
    UBCPlayerStatisticsProxy *Proxy = NewObject<UBCPlayerStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStatisticsService()->setExperiencePoints(xpValue, Proxy);
    return Proxy;
}

UBCPlayerStatisticsProxy *UBCPlayerStatisticsProxy::ProcessStatistics(UBrainCloudWrapper *brainCloudWrapper, FString jsonData)
{
    UBCPlayerStatisticsProxy *Proxy = NewObject<UBCPlayerStatisticsProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlayerStatisticsService()->processStatistics(jsonData, Proxy);
    return Proxy;
}
