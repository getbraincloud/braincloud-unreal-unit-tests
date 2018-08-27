// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCTournamentProxy.h"

UBCTournamentProxy::UBCTournamentProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCTournamentProxy* UBCTournamentProxy::ClaimTournamentReward(UBrainCloudWrapper *brainCloudWrapper, const FString& leaderboardId, int32 versionId)
{
	UBCTournamentProxy* Proxy = NewObject<UBCTournamentProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getTournamentService()->claimTournamentReward(leaderboardId, versionId, Proxy);
	return Proxy;
}


UBCTournamentProxy* UBCTournamentProxy::GetTournamentStatus(UBrainCloudWrapper *brainCloudWrapper, const FString& leaderboardId, int32 versionId)
{
	UBCTournamentProxy* Proxy = NewObject<UBCTournamentProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getTournamentService()->getTournamentStatus(leaderboardId, versionId, Proxy);
	return Proxy;
}


UBCTournamentProxy* UBCTournamentProxy::JoinTournament(UBrainCloudWrapper *brainCloudWrapper, const FString& leaderboardId, const FString& tournamentCode, int32 initialScore)
{
	UBCTournamentProxy* Proxy = NewObject<UBCTournamentProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getTournamentService()->joinTournament(leaderboardId, tournamentCode, initialScore, Proxy);
	return Proxy;
}


UBCTournamentProxy* UBCTournamentProxy::LeaveTournament(UBrainCloudWrapper *brainCloudWrapper, const FString& leaderboardId)
{
	UBCTournamentProxy* Proxy = NewObject<UBCTournamentProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getTournamentService()->leaveTournament(leaderboardId, Proxy);
	return Proxy;
}


UBCTournamentProxy* UBCTournamentProxy::PostTournamentScore(UBrainCloudWrapper *brainCloudWrapper, const FString& leaderboardId, int32 score, const FString& jsonData, const struct FDateTime roundStartedTime)
{
	UBCTournamentProxy* Proxy = NewObject<UBCTournamentProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getTournamentService()->postTournamentScore(leaderboardId, score, jsonData, roundStartedTime, Proxy);
	return Proxy;
}


UBCTournamentProxy* UBCTournamentProxy::ViewCurrentReward(UBrainCloudWrapper *brainCloudWrapper, const FString& leaderboardId)
{
	UBCTournamentProxy* Proxy = NewObject<UBCTournamentProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getTournamentService()->viewCurrentReward(leaderboardId, Proxy);
	return Proxy;
}


UBCTournamentProxy* UBCTournamentProxy::ViewReward(UBrainCloudWrapper *brainCloudWrapper, const FString& leaderboardId, int32 versionId)
{
	UBCTournamentProxy* Proxy = NewObject<UBCTournamentProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getTournamentService()->viewReward(leaderboardId, versionId, Proxy);
	return Proxy;
}
