// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudTournament.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudTournament::BrainCloudTournament(BrainCloudClient* client) : _client(client) {}

void BrainCloudTournament::claimTournamentReward(const FString & leaderboardId, int32 versionId, IServerCallback * callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardId.getValue(), leaderboardId);
	message->SetNumberField(OperationParam::VersionId.getValue(), versionId);

	ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::ClaimTournamentReward, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudTournament::getTournamentStatus(const FString & leaderboardId, int32 versionId, IServerCallback * callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardId.getValue(), leaderboardId);
	message->SetNumberField(OperationParam::VersionId.getValue(), versionId);

	ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::GetTournamentStatus, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudTournament::getDivisionInfo(const FString & divSetId, IServerCallback * callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::DivSetId.getValue(), divSetId);

	ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::GetDivisionInfo, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudTournament::getMyDivisions(IServerCallback * callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

	ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::GetMyDivisions, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudTournament::joinTournament(const FString & leaderboardId, const FString & tournamentCode, int32 initialScore, IServerCallback * callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardId.getValue(), leaderboardId);
	message->SetStringField(OperationParam::TournamentCode.getValue(), tournamentCode);
	message->SetNumberField(OperationParam::InitialScore.getValue(), initialScore);

	ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::JoinTournament, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudTournament::joinDivision(const FString & divSetId, const FString & tournamentCode, int32 initialScore, IServerCallback * callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::DivSetId.getValue(), divSetId);
	message->SetStringField(OperationParam::TournamentCode.getValue(), tournamentCode);
	message->SetNumberField(OperationParam::InitialScore.getValue(), initialScore);

	ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::JoinDivision, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudTournament::leaveTournament(const FString & leaderboardId, IServerCallback * callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardId.getValue(), leaderboardId);

	ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::LeaveTournament, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudTournament::leaveDivisionInstance(const FString & leaderboardId, IServerCallback * callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardId.getValue(), leaderboardId);

	ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::LeaveDivisionInstance, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudTournament::postTournamentScore(const FString & leaderboardId, int32 score, const FString & jsonData, const FDateTime roundStartedTime, IServerCallback * callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardId.getValue(), leaderboardId);
	message->SetNumberField(OperationParam::Score.getValue(), score);
	message->SetNumberField(OperationParam::RoundStartedEpoch.getValue(), roundStartedTime.ToUnixTimestamp() * 1000);

	if (OperationParam::isOptionalParamValid(jsonData)) {
		message->SetObjectField(OperationParam::Data.getValue(), JsonUtil::jsonStringToValue(jsonData));
	}

	ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::PostTournamentScore, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudTournament::viewCurrentReward(const FString & leaderboardId, IServerCallback * callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardId.getValue(), leaderboardId);

	ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::ViewCurrentReward, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudTournament::viewReward(const FString & leaderboardId, int32 versionId, IServerCallback * callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardId.getValue(), leaderboardId);
	message->SetNumberField(OperationParam::VersionId.getValue(), versionId);

	ServerCall * sc = new ServerCall(ServiceName::Tournament, ServiceOperation::ViewReward, message, callback);
	_client->sendRequest(sc);
}