// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCLeaderboardProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

//////////////////////////////////////////////////////////////////////////
// UBCLeaderboardProxy

UBCLeaderboardProxy::UBCLeaderboardProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCLeaderboardProxy *UBCLeaderboardProxy::GetSocialLeaderboard(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, bool replaceName)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->getSocialLeaderboard(leaderboardId, replaceName, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::GetSocialLeaderboardByVersion(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, bool replaceName, int32 versionId)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->getSocialLeaderboardByVersion(leaderboardId, replaceName, versionId, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::GetMultiSocialLeaderboard(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &leaderboardIds, int32 leaderboardResultCount, bool replaceName)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->getMultiSocialLeaderboard(leaderboardIds, leaderboardResultCount, replaceName, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::GetGlobalLeaderboardPage(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, ESortOrder sortOrder, int32 startIndex, int32 endIndex)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->getGlobalLeaderboardPage(leaderboardId, sortOrder, startIndex, endIndex, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::GetGlobalLeaderboardPageByVersion(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, ESortOrder sortOrder, int32 startIndex, int32 endIndex, int32 versionId)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->getGlobalLeaderboardPageByVersion(leaderboardId, sortOrder, startIndex, endIndex, versionId, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::GetGlobalLeaderboardView(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->getGlobalLeaderboardView(leaderboardId, sortOrder, beforeCount, afterCount, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::GetGlobalLeaderboardViewByVersion(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount, int32 versionId)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->getGlobalLeaderboardViewByVersion(leaderboardId, sortOrder, beforeCount, afterCount, versionId, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::GetGlobalLeaderboardEntryCount(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->getGlobalLeaderboardEntryCount(leaderboardId, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::GetGlobalLeaderboardVersions(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->getGlobalLeaderboardVersions(leaderboardId, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::PostScore(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, int32 score, FString jsonData)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->postScore(leaderboardId, score, jsonData, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::PostScoreToDynamicLeaderboard(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, int32 score, FString jsonData,
																		ESocialLeaderboardType leaderboardType, ERotationType rotationType, FDateTime rotationStart, int32 retainedCount)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->postScoreToDynamicLeaderboard(leaderboardId, score, jsonData, leaderboardType, rotationType, rotationStart, retainedCount, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::PostScoreToDynamicGroupLeaderboard(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, const FString &groupId, int32 score, FString jsonData,
																		ESocialLeaderboardType leaderboardType, ERotationType rotationType, FDateTime rotationStart, int32 retainedCount)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->postScoreToDynamicGroupLeaderboard(leaderboardId, groupId, score, jsonData, leaderboardType, rotationType, rotationStart, retainedCount, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::PostScoreToDynamicLeaderboardDays(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, int32 score, FString jsonData,
																			ESocialLeaderboardType leaderboardType, FDateTime rotationStart, int32 retainedCount, int32 numDaysToRotate)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->postScoreToDynamicLeaderboardDays(leaderboardId, score, jsonData, leaderboardType, rotationStart, retainedCount, numDaysToRotate, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::PostScoreToDynamicLeaderboardUTC(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, int32 score, FString jsonData,
																		ESocialLeaderboardType leaderboardType, ERotationType rotationType, int64 rotationStart, int32 retainedCount)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->postScoreToDynamicLeaderboardUTC(leaderboardId, score, jsonData, leaderboardType, rotationType, rotationStart, retainedCount, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::PostScoreToDynamicGroupLeaderboardUTC(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, const FString &groupId, int32 score, FString jsonData,
																		ESocialLeaderboardType leaderboardType, ERotationType rotationType, int64 rotationStart, int32 retainedCount)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->postScoreToDynamicGroupLeaderboardUTC(leaderboardId, groupId, score, jsonData, leaderboardType, rotationType, rotationStart, retainedCount, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::PostScoreToDynamicLeaderboardDaysUTC(UBrainCloudWrapper *brainCloudWrapper, FString leaderboardId, int32 score, FString jsonData,
																			ESocialLeaderboardType leaderboardType, int64 rotationStart, int32 retainedCount, int32 numDaysToRotate)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->postScoreToDynamicLeaderboardDaysUTC(leaderboardId, score, jsonData, leaderboardType, rotationStart, retainedCount, numDaysToRotate, Proxy);
	return Proxy;
}

UBCLeaderboardProxy* UBCLeaderboardProxy::PostScoreToDynamicGroupLeaderboardDaysUTC(
	UBrainCloudWrapper* brainCloudWrapper, FString leaderboardId, FString groupId, int32 score, FString jsonData,
	ESocialLeaderboardType leaderboardType, FDateTime rotationResetUTC, int32 retainedCount, int32 numDaysToRotate)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->postScoreToDynamicGroupLeaderboardDaysUTC(leaderboardId, groupId, score, jsonData, leaderboardType, rotationResetUTC, retainedCount, numDaysToRotate, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::RemovePlayerScore(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, int32 versionId)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->removePlayerScore(leaderboardId, versionId, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::GetGroupSocialLeaderboard(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, const FString &groupId)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->getGroupSocialLeaderboard(leaderboardId, groupId, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::GetGroupSocialLeaderboardByVersion(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, const FString &groupId, int32 versionId)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->getGroupSocialLeaderboardByVersion(leaderboardId, groupId, versionId, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::GetPlayersSocialLeaderboard(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, const TArray<FString> profileIds)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->getPlayersSocialLeaderboard(leaderboardId, profileIds, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::GetPlayersSocialLeaderboardByVersion(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, const TArray<FString> profileIds, int32 versionId)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->getPlayersSocialLeaderboardByVersion(leaderboardId, profileIds, versionId, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::ListAllLeaderboards(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->listAllLeaderboards(Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::GetPlayerScore(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, int32 versionId)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->getPlayerScore(leaderboardId, versionId, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::GetPlayerScores(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, int32 versionId, int32 maxResults)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->getPlayerScores(leaderboardId, versionId, maxResults, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::GetPlayerScoresFromLeaderboards(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> leaderboardIds)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->getPlayerScoresFromLeaderboards(leaderboardIds, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::PostScoreToGroupLeaderboard(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, const FString &groupId, int32 score, const FString &jsonOtherData)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->postScoreToGroupLeaderboard(leaderboardId, groupId, score, jsonOtherData, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::RemoveGroupScore(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, const FString &groupId, int32 score, int32 versionId)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->removeGroupScore(leaderboardId, groupId, score, versionId, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::GetGroupLeaderboardView(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, const FString &groupId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->getGroupLeaderboardView(leaderboardId, groupId, sortOrder, beforeCount, afterCount, Proxy);
	return Proxy;
}

UBCLeaderboardProxy *UBCLeaderboardProxy::GetGroupLeaderboardViewByVersion(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, const FString &groupId, int32 versionId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount)
{
	UBCLeaderboardProxy *Proxy = NewObject<UBCLeaderboardProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getLeaderboardService()->getGroupLeaderboardViewByVersion(leaderboardId, groupId, versionId, sortOrder, beforeCount, afterCount, Proxy);
	return Proxy;
}
