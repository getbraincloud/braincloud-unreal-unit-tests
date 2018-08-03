// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloudActor.h"
#include "BCWrapperProxy.h"
#include "BCLeaderboardProxy.h"
#include "BrainCloudWrapper.h"

//////////////////////////////////////////////////////////////////////////
// UBCLeaderboardProxy

UBCLeaderboardProxy::UBCLeaderboardProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCLeaderboardProxy* UBCLeaderboardProxy::GetSocialLeaderboard(ABrainCloudActor *brainCloud, FString leaderboardId, bool replaceName)
{
	UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLeaderboardService()->getSocialLeaderboard(leaderboardId, replaceName, Proxy);
	return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::GetMultiSocialLeaderboard(ABrainCloudActor *brainCloud, const TArray<FString>& leaderboardIds, int32 leaderboardResultCount, bool replaceName)
{
	UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLeaderboardService()->getMultiSocialLeaderboard(leaderboardIds, leaderboardResultCount, replaceName, Proxy);
	return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::GetGlobalLeaderboardPage(ABrainCloudActor *brainCloud, FString leaderboardId, ESortOrder sortOrder, int32 startIndex, int32 endIndex)
{
	UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLeaderboardService()->getGlobalLeaderboardPage(leaderboardId, sortOrder, startIndex, endIndex, Proxy);
	return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::GetGlobalLeaderboardPageByVersion(ABrainCloudActor *brainCloud, FString leaderboardId, ESortOrder sortOrder, int32 startIndex, int32 endIndex, int32 versionId)
{
	UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLeaderboardService()->getGlobalLeaderboardPageByVersion(leaderboardId, sortOrder, startIndex, endIndex, versionId, Proxy);
	return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::GetGlobalLeaderboardView(ABrainCloudActor *brainCloud, FString leaderboardId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount)
{
	UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLeaderboardService()->getGlobalLeaderboardView(leaderboardId, sortOrder, beforeCount, afterCount, Proxy);
	return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::GetGlobalLeaderboardViewByVersion(ABrainCloudActor *brainCloud, FString leaderboardId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount, int32 versionId)
{
	UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLeaderboardService()->getGlobalLeaderboardViewByVersion(leaderboardId, sortOrder, beforeCount, afterCount, versionId, Proxy);
	return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::GetGlobalLeaderboardEntryCount(ABrainCloudActor *brainCloud, FString leaderboardId)
{
	UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLeaderboardService()->getGlobalLeaderboardEntryCount(leaderboardId, Proxy);
	return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::GetGlobalLeaderboardVersions(ABrainCloudActor *brainCloud, FString leaderboardId)
{
	UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLeaderboardService()->getGlobalLeaderboardVersions(leaderboardId, Proxy);
	return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::PostScore(ABrainCloudActor *brainCloud, FString leaderboardId, int32 score, FString jsonData)
{
	UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLeaderboardService()->postScore(leaderboardId, score, jsonData, Proxy);
	return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::PostScoreToDynamicLeaderboard(ABrainCloudActor *brainCloud, FString leaderboardId, int32 score, FString jsonData,
	ESocialLeaderboardType leaderboardType, ERotationType rotationType, FDateTime rotationStart, int32 retainedCount)
{
	UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLeaderboardService()->postScoreToDynamicLeaderboard(leaderboardId, score, jsonData, leaderboardType, rotationType, rotationStart, retainedCount, Proxy);
	return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::PostScoreToDynamicLeaderboardDays(ABrainCloudActor *brainCloud, FString leaderboardId, int32 score, FString jsonData,
	ESocialLeaderboardType leaderboardType, FDateTime rotationStart, int32 retainedCount, int32 numDaysToRotate)
{
	UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLeaderboardService()->postScoreToDynamicLeaderboardDays(leaderboardId, score, jsonData, leaderboardType, rotationStart, retainedCount, numDaysToRotate, Proxy);
	return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::RemovePlayerScore(ABrainCloudActor *brainCloud, const FString& leaderboardId, int32 versionId)
{
	UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLeaderboardService()->removePlayerScore(leaderboardId, versionId, Proxy);
	return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::GetGroupSocialLeaderboard(ABrainCloudActor *brainCloud, const FString& leaderboardId, const FString& groupId)
{
	UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLeaderboardService()->getGroupSocialLeaderboard(leaderboardId, groupId, Proxy);
	return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::GetPlayersSocialLeaderboard(ABrainCloudActor *brainCloud, const FString& leaderboardId, const TArray<FString> profileIds)
{
	UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLeaderboardService()->getPlayersSocialLeaderboard(leaderboardId, profileIds, Proxy);
	return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::ListAllLeaderboards(ABrainCloudActor *brainCloud)
{
	UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLeaderboardService()->listAllLeaderboards(Proxy);
	return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::GetPlayerScore(ABrainCloudActor *brainCloud, const FString& leaderboardId, int32 versionId)
{
	UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLeaderboardService()->getPlayerScore(leaderboardId, versionId, Proxy);
	return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::GetPlayerScoresFromLeaderboards(ABrainCloudActor *brainCloud, const TArray<FString> leaderboardIds)
{
	UBCLeaderboardProxy* Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getLeaderboardService()->getPlayerScoresFromLeaderboards(leaderboardIds, Proxy);
	return Proxy;
}

void UBCLeaderboardProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
	OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCLeaderboardProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
	OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}
