// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCLeaderboardProxy.h"

//////////////////////////////////////////////////////////////////////////
// UBCLeaderboardProxy

UBCLeaderboardProxy::UBCLeaderboardProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCLeaderboardProxy* UBCLeaderboardProxy::GetSocialLeaderboard(FString leaderboardId, bool replaceName)
{
    UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
    BrainCloudClient::getInstance()->getLeaderboardService()->getSocialLeaderboard(leaderboardId, replaceName, Proxy);
    return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::GetMultiSocialLeaderboard(const TArray<FString>& leaderboardIds, int32 leaderboardResultCount, bool replaceName)
{
    UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
    BrainCloudClient::getInstance()->getLeaderboardService()->getMultiSocialLeaderboard(leaderboardIds, leaderboardResultCount, replaceName, Proxy);
    return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::GetGlobalLeaderboardPage(FString leaderboardId, ESortOrder sortOrder, int32 startIndex, int32 endIndex, bool includeLeaderboardSize)
{
    UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
    BrainCloudClient::getInstance()->getLeaderboardService()->getGlobalLeaderboardPage(leaderboardId, sortOrder, startIndex, endIndex, includeLeaderboardSize, Proxy);
    return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::GetGlobalLeaderboardPageByVersion(FString leaderboardId, ESortOrder sortOrder, int32 startIndex, int32 endIndex, bool includeLeaderboardSize, int32 versionId)
{
    UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
    BrainCloudClient::getInstance()->getLeaderboardService()->getGlobalLeaderboardPageByVersion(leaderboardId, sortOrder, startIndex, endIndex, includeLeaderboardSize, versionId, Proxy);
    return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::GetGlobalLeaderboardView(FString leaderboardId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount, bool includeLeaderboardSize)
{
    UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
    BrainCloudClient::getInstance()->getLeaderboardService()->getGlobalLeaderboardView(leaderboardId, sortOrder, beforeCount, afterCount, includeLeaderboardSize, Proxy);
    return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::GetGlobalLeaderboardViewByVersion(FString leaderboardId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount, bool includeLeaderboardSize, int32 versionId)
{
    UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
    BrainCloudClient::getInstance()->getLeaderboardService()->getGlobalLeaderboardViewByVersion(leaderboardId, sortOrder, beforeCount, afterCount, includeLeaderboardSize, versionId, Proxy);
    return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::GetGlobalLeaderboardVersions(FString leaderboardId)
{
    UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
    BrainCloudClient::getInstance()->getLeaderboardService()->getGlobalLeaderboardVersions(leaderboardId, Proxy);
    return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::PostScore(FString leaderboardId, int32 score, FString jsonData)
{
    UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
    BrainCloudClient::getInstance()->getLeaderboardService()->postScore(leaderboardId, score, jsonData, Proxy);
    return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::PostScoreToDynamicLeaderboard(FString leaderboardId, int32 score, FString jsonData,
    ESocialLeaderboardType leaderboardType, ERotationType rotationType, FDateTime rotationStart, int32 retainedCount)
{
    UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
    BrainCloudClient::getInstance()->getLeaderboardService()->postScoreToDynamicLeaderboard(leaderboardId, score, jsonData, leaderboardType, rotationType, rotationStart, retainedCount, Proxy);
    return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::ResetLeaderboardScore(FString leaderBoardName)
{
    UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
    BrainCloudClient::getInstance()->getLeaderboardService()->resetLeaderboardScore(leaderBoardName, Proxy);
    return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::GetCompletedLeaderboardTournament(FString leaderboardId, bool replaceName)
{
    UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
    BrainCloudClient::getInstance()->getLeaderboardService()->getCompletedLeaderboardTournament(leaderboardId, replaceName, Proxy);
    return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::TriggerSocialLeaderboardTournamentReward(FString leaderboardId, FString eventName, int32 eventMultiplier)
{
    UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
    BrainCloudClient::getInstance()->getLeaderboardService()->triggerSocialLeaderboardTournamentReward(leaderboardId, eventName, eventMultiplier, Proxy);
    return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::GetGroupSocialLeaderboard(const FString& leaderboardId, const FString& groupId)
{
    UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
    BrainCloudClient::getInstance()->getLeaderboardService()->getGroupSocialLeaderboard(leaderboardId, groupId, Proxy);
    return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::GetPlayersSocialLeaderboard(const FString& leaderboardId, const TArray<FString> profileIds)
{
	UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
	BrainCloudClient::getInstance()->getLeaderboardService()->getPlayersSocialLeaderboard(leaderboardId, profileIds, Proxy);
	return Proxy;
}

void UBCLeaderboardProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
}

void UBCLeaderboardProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
}