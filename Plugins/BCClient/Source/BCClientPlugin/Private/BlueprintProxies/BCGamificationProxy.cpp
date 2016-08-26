// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCGamificationProxy.h"

UBCGamificationProxy::UBCGamificationProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCGamificationProxy* UBCGamificationProxy::ReadAllGamification(bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    BrainCloudClient::getInstance()->getGamificationService()->readAllGamification(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadMilestones(bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    BrainCloudClient::getInstance()->getGamificationService()->readMilestones(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadAchievements(bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    BrainCloudClient::getInstance()->getGamificationService()->readAchievements(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadXpLevelsMetaData()
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    BrainCloudClient::getInstance()->getGamificationService()->readXpLevelsMetaData(Proxy);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadAchievedAchievements(bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    BrainCloudClient::getInstance()->getGamificationService()->readAchievedAchievements(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadCompletedMilestones(bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    BrainCloudClient::getInstance()->getGamificationService()->readCompletedMilestones(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadInProgressMilestones(bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    BrainCloudClient::getInstance()->getGamificationService()->readInProgressMilestones(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadMilestonesByCategory(FString category, bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    BrainCloudClient::getInstance()->getGamificationService()->readMilestonesByCategory(category, Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::AwardAchievements(const TArray<FString>& achievements)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    BrainCloudClient::getInstance()->getGamificationService()->awardAchievements(achievements, Proxy);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ResetMilestones(const TArray<FString>& milestoneIds)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    BrainCloudClient::getInstance()->getGamificationService()->resetMilestones(milestoneIds, Proxy);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadQuests(bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    BrainCloudClient::getInstance()->getGamificationService()->readQuests(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadCompletedQuests(bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    BrainCloudClient::getInstance()->getGamificationService()->readCompletedQuests(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadInProgressQuests(bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    BrainCloudClient::getInstance()->getGamificationService()->readInProgressQuests(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadNotStartedQuests(bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    BrainCloudClient::getInstance()->getGamificationService()->readNotStartedQuests(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadQuestsWithStatus(bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    BrainCloudClient::getInstance()->getGamificationService()->readQuestsWithStatus(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadQuestsWithBasicPercentage(bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    BrainCloudClient::getInstance()->getGamificationService()->readQuestsWithBasicPercentage(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadQuestsWithComplexPercentage(bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    BrainCloudClient::getInstance()->getGamificationService()->readQuestsWithComplexPercentage(Proxy, includeMetaData);
    return Proxy;
}

UBCGamificationProxy* UBCGamificationProxy::ReadQuestsByCategory(FString category, bool includeMetaData)
{
    UBCGamificationProxy* Proxy = NewObject<UBCGamificationProxy>();
    BrainCloudClient::getInstance()->getGamificationService()->readQuestsByCategory(category, Proxy, includeMetaData);
    return Proxy;
}

//callbacks
void UBCGamificationProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
}

void UBCGamificationProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
}

