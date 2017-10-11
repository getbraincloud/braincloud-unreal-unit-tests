// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCTournamentProxy.h"

UBCTournamentProxy::UBCTournamentProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCTournamentProxy* UBCTournamentProxy::ClaimTournamentReward(const FString& leaderboardId, int32 versionId)
{
	UBCTournamentProxy* Proxy = NewObject<UBCTournamentProxy>();
	BrainCloudClient::getInstance()->getTournamentService()->claimTournamentReward(leaderboardId, versionId, Proxy);
	return Proxy;
}


UBCTournamentProxy* UBCTournamentProxy::GetTournamentStatus(const FString& leaderboardId, int32 versionId)
{
	UBCTournamentProxy* Proxy = NewObject<UBCTournamentProxy>();
	BrainCloudClient::getInstance()->getTournamentService()->getTournamentStatus(leaderboardId, versionId, Proxy);
	return Proxy;
}


UBCTournamentProxy* UBCTournamentProxy::JoinTournament(const FString& leaderboardId, const FString& tournamentCode, int32 initialScore)
{
	UBCTournamentProxy* Proxy = NewObject<UBCTournamentProxy>();
	BrainCloudClient::getInstance()->getTournamentService()->joinTournament(leaderboardId, tournamentCode, initialScore, Proxy);
	return Proxy;
}


UBCTournamentProxy* UBCTournamentProxy::LeaveTournament(const FString& leaderboardId)
{
	UBCTournamentProxy* Proxy = NewObject<UBCTournamentProxy>();
	BrainCloudClient::getInstance()->getTournamentService()->leaveTournament(leaderboardId, Proxy);
	return Proxy;
}


UBCTournamentProxy* UBCTournamentProxy::PostTournamentScore(const FString& leaderboardId, int32 score, const FString& jsonData, const struct FDateTime roundStartedTime)
{
	UBCTournamentProxy* Proxy = NewObject<UBCTournamentProxy>();
	BrainCloudClient::getInstance()->getTournamentService()->postTournamentScore(leaderboardId, score, jsonData, roundStartedTime, Proxy);
	return Proxy;
}


UBCTournamentProxy* UBCTournamentProxy::ViewCurrentReward(const FString& leaderboardId)
{
	UBCTournamentProxy* Proxy = NewObject<UBCTournamentProxy>();
	BrainCloudClient::getInstance()->getTournamentService()->viewCurrentReward(leaderboardId, Proxy);
	return Proxy;
}


UBCTournamentProxy* UBCTournamentProxy::ViewReward(const FString& leaderboardId, int32 versionId)
{
	UBCTournamentProxy* Proxy = NewObject<UBCTournamentProxy>();
	BrainCloudClient::getInstance()->getTournamentService()->viewReward(leaderboardId, versionId, Proxy);
	return Proxy;
}

//callbacks
void UBCTournamentProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCTournamentProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

