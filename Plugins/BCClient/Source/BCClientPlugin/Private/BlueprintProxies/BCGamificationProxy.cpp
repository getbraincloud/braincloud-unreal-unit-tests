// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloudActor.h"
#include "BCWrapperProxy.h"
#include "BCGamificationProxy.h"
#include "BrainCloudWrapper.h"

UBCGamificationProxy::UBCGamificationProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCGamificationProxy* UBCGamificationProxy::ReadAllGamification(ABrainCloudActor *brainCloud, bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGamificationService()->readAllGamification(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadMilestones(ABrainCloudActor *brainCloud, bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGamificationService()->readMilestones(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadAchievements(ABrainCloudActor *brainCloud, bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGamificationService()->readAchievements(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadXpLevelsMetaData(ABrainCloudActor *brainCloud)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGamificationService()->readXpLevelsMetaData(Proxy);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadAchievedAchievements(ABrainCloudActor *brainCloud, bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGamificationService()->readAchievedAchievements(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadCompletedMilestones(ABrainCloudActor *brainCloud, bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGamificationService()->readCompletedMilestones(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadInProgressMilestones(ABrainCloudActor *brainCloud, bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGamificationService()->readInProgressMilestones(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadMilestonesByCategory(ABrainCloudActor *brainCloud, FString category, bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGamificationService()->readMilestonesByCategory(category, Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::AwardAchievements(ABrainCloudActor *brainCloud, const TArray<FString>& achievements)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGamificationService()->awardAchievements(achievements, Proxy);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ResetMilestones(ABrainCloudActor *brainCloud, const TArray<FString>& milestoneIds)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGamificationService()->resetMilestones(milestoneIds, Proxy);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadQuests(ABrainCloudActor *brainCloud, bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGamificationService()->readQuests(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadCompletedQuests(ABrainCloudActor *brainCloud, bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGamificationService()->readCompletedQuests(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadInProgressQuests(ABrainCloudActor *brainCloud, bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGamificationService()->readInProgressQuests(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadNotStartedQuests(ABrainCloudActor *brainCloud, bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGamificationService()->readNotStartedQuests(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadQuestsWithStatus(ABrainCloudActor *brainCloud, bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGamificationService()->readQuestsWithStatus(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadQuestsWithBasicPercentage(ABrainCloudActor *brainCloud, bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGamificationService()->readQuestsWithBasicPercentage(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadQuestsWithComplexPercentage(ABrainCloudActor *brainCloud, bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGamificationService()->readQuestsWithComplexPercentage(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadQuestsByCategory(ABrainCloudActor *brainCloud, FString category, bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGamificationService()->readQuestsByCategory(category, Proxy, includeMetaData);
    return Proxy;
}

//callbacks
void UBCGamificationProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCGamificationProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

