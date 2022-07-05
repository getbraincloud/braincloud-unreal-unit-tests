// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCGamificationProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCGamificationProxy::UBCGamificationProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCGamificationProxy *UBCGamificationProxy::ReadAllGamification(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData)
{
    UBCGamificationProxy *Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGamificationService()->readAllGamification(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy *UBCGamificationProxy::ReadMilestones(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData)
{
    UBCGamificationProxy *Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGamificationService()->readMilestones(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy *UBCGamificationProxy::ReadAchievements(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData)
{
    UBCGamificationProxy *Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGamificationService()->readAchievements(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy *UBCGamificationProxy::ReadXpLevelsMetaData(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCGamificationProxy *Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGamificationService()->readXpLevelsMetaData(Proxy);
    return Proxy;
}

UBCGamificationProxy *UBCGamificationProxy::ReadAchievedAchievements(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData)
{
    UBCGamificationProxy *Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGamificationService()->readAchievedAchievements(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy *UBCGamificationProxy::ReadCompletedMilestones(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData)
{
    UBCGamificationProxy *Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGamificationService()->readCompletedMilestones(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy *UBCGamificationProxy::ReadInProgressMilestones(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData)
{
    UBCGamificationProxy *Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGamificationService()->readInProgressMilestones(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy *UBCGamificationProxy::ReadMilestonesByCategory(UBrainCloudWrapper *brainCloudWrapper, FString category, bool includeMetaData)
{
    UBCGamificationProxy *Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGamificationService()->readMilestonesByCategory(category, Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy *UBCGamificationProxy::AwardAchievements(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &achievements)
{
    UBCGamificationProxy *Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGamificationService()->awardAchievements(achievements, Proxy);
    return Proxy;
}

UBCGamificationProxy *UBCGamificationProxy::ReadQuests(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData)
{
    UBCGamificationProxy *Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGamificationService()->readQuests(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy *UBCGamificationProxy::ReadCompletedQuests(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData)
{
    UBCGamificationProxy *Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGamificationService()->readCompletedQuests(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy *UBCGamificationProxy::ReadInProgressQuests(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData)
{
    UBCGamificationProxy *Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGamificationService()->readInProgressQuests(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy *UBCGamificationProxy::ReadNotStartedQuests(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData)
{
    UBCGamificationProxy *Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGamificationService()->readNotStartedQuests(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy *UBCGamificationProxy::ReadQuestsWithStatus(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData)
{
    UBCGamificationProxy *Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGamificationService()->readQuestsWithStatus(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy *UBCGamificationProxy::ReadQuestsWithBasicPercentage(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData)
{
    UBCGamificationProxy *Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGamificationService()->readQuestsWithBasicPercentage(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy *UBCGamificationProxy::ReadQuestsWithComplexPercentage(UBrainCloudWrapper *brainCloudWrapper, bool includeMetaData)
{
    UBCGamificationProxy *Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGamificationService()->readQuestsWithComplexPercentage(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy *UBCGamificationProxy::ReadQuestsByCategory(UBrainCloudWrapper *brainCloudWrapper, FString category, bool includeMetaData)
{
    UBCGamificationProxy *Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGamificationService()->readQuestsByCategory(category, Proxy, includeMetaData);
    return Proxy;
}
