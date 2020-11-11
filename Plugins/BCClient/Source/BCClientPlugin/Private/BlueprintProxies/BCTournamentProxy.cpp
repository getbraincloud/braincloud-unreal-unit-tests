// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCTournamentProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCTournamentProxy::UBCTournamentProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCTournamentProxy *UBCTournamentProxy::ClaimTournamentReward(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, int32 versionId)
{
	UBCTournamentProxy *Proxy = NewObject<UBCTournamentProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getTournamentService()->claimTournamentReward(leaderboardId, versionId, Proxy);
	return Proxy;
}


UBCTournamentProxy *UBCTournamentProxy::GetTournamentStatus(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, int32 versionId)
{
	UBCTournamentProxy *Proxy = NewObject<UBCTournamentProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getTournamentService()->getTournamentStatus(leaderboardId, versionId, Proxy);
	return Proxy;
}

UBCTournamentProxy *UBCTournamentProxy::GetDivisionInfo(UBrainCloudWrapper *brainCloudWrapper, const FString &divSetId)
{
	UBCTournamentProxy *Proxy = NewObject<UBCTournamentProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getTournamentService()->getDivisionInfo(divSetId, Proxy);
	return Proxy;
}

UBCTournamentProxy *UBCTournamentProxy::GetMyDivisions(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCTournamentProxy *Proxy = NewObject<UBCTournamentProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getTournamentService()->getMyDivisions(Proxy);
	return Proxy;
}

UBCTournamentProxy *UBCTournamentProxy::JoinDivision(UBrainCloudWrapper *brainCloudWrapper, const FString &divSetId, const FString &tournamentCode, int32 initialScore)
{
	UBCTournamentProxy *Proxy = NewObject<UBCTournamentProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getTournamentService()->joinDivision(divSetId, tournamentCode, initialScore, Proxy);
	return Proxy;
}

UBCTournamentProxy *UBCTournamentProxy::LeaveDivisionInstance(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId)
{
	UBCTournamentProxy *Proxy = NewObject<UBCTournamentProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getTournamentService()->leaveDivisionInstance(leaderboardId, Proxy);
	return Proxy;
}

UBCTournamentProxy *UBCTournamentProxy::JoinTournament(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, const FString &tournamentCode, int32 initialScore)
{
	UBCTournamentProxy *Proxy = NewObject<UBCTournamentProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getTournamentService()->joinTournament(leaderboardId, tournamentCode, initialScore, Proxy);
	return Proxy;
}

UBCTournamentProxy *UBCTournamentProxy::LeaveTournament(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId)
{
	UBCTournamentProxy *Proxy = NewObject<UBCTournamentProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getTournamentService()->leaveTournament(leaderboardId, Proxy);
	return Proxy;
}

UBCTournamentProxy *UBCTournamentProxy::PostTournamentScore(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, int32 score, const FString &jsonData, const struct FDateTime roundStartedTime)
{
	UBCTournamentProxy *Proxy = NewObject<UBCTournamentProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getTournamentService()->postTournamentScore(leaderboardId, score, jsonData, roundStartedTime, Proxy);
	return Proxy;
}

UBCTournamentProxy *UBCTournamentProxy::PostTournamentScoreWithResults(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, int32 score, const FString &jsonData, FDateTime roundStartedTime, ESortOrder sort, int32 beforeCount, int32 afterCount, float initialScore)
{
	UBCTournamentProxy *Proxy = NewObject<UBCTournamentProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getTournamentService()->postTournamentScoreWithResults(leaderboardId, score, jsonData, roundStartedTime, sort, beforeCount, afterCount, initialScore, Proxy);
	return Proxy;
}

UBCTournamentProxy *UBCTournamentProxy::PostTournamentScoreUTC(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, int32 score, const FString &jsonData, int64 roundStartTimeUTC)
{
	UBCTournamentProxy *Proxy = NewObject<UBCTournamentProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getTournamentService()->postTournamentScoreUTC(leaderboardId, score, jsonData, roundStartTimeUTC, Proxy);
	return Proxy;
}

UBCTournamentProxy *UBCTournamentProxy::PostTournamentScoreWithResultsUTC(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, int32 score, const FString &jsonData, int64 roundStartTimeUTC, ESortOrder sort, int32 beforeCount, int32 afterCount, float initialScore)
{
	UBCTournamentProxy *Proxy = NewObject<UBCTournamentProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getTournamentService()->postTournamentScoreWithResultsUTC(leaderboardId, score, jsonData, roundStartTimeUTC, sort, beforeCount, afterCount, initialScore, Proxy);
	return Proxy;
}

UBCTournamentProxy *UBCTournamentProxy::ViewCurrentReward(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId)
{
	UBCTournamentProxy *Proxy = NewObject<UBCTournamentProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getTournamentService()->viewCurrentReward(leaderboardId, Proxy);
	return Proxy;
}

UBCTournamentProxy *UBCTournamentProxy::ViewReward(UBrainCloudWrapper *brainCloudWrapper, const FString &leaderboardId, int32 versionId)
{
	UBCTournamentProxy *Proxy = NewObject<UBCTournamentProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getTournamentService()->viewReward(leaderboardId, versionId, Proxy);
	return Proxy;
}
