// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudGlobalStatistics.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudGlobalStatistics::BrainCloudGlobalStatistics(BrainCloudClient *client) : _client(client){};

void BrainCloudGlobalStatistics::readAllGlobalStats(IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	ServerCall *sc = new ServerCall(ServiceName::GlobalGameStatistics, ServiceOperation::Read, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGlobalStatistics::readGlobalStatsSubset(const TArray<FString> &globalStats, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetArrayField(OperationParam::PlayerStatisticsServiceStats.getValue(), JsonUtil::arrayToJsonArray(globalStats));

	ServerCall *sc = new ServerCall(ServiceName::GlobalGameStatistics, ServiceOperation::ReadSubset, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGlobalStatistics::readGlobalStatsForCategory(const FString &category, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GamificationServiceCategory.getValue(), category);

	ServerCall *sc = new ServerCall(ServiceName::Gamification, ServiceOperation::ReadGameStatisticsByCategory, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGlobalStatistics::incrementGlobalGameStat(const FString &jsonData, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetObjectField(OperationParam::PlayerStatisticsServiceStats.getValue(), JsonUtil::jsonStringToValue(jsonData));

	ServerCall *sc = new ServerCall(ServiceName::GlobalGameStatistics, ServiceOperation::UpdateIncrement, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGlobalStatistics::processStatistics(const FString &jsonData, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetObjectField(OperationParam::PlayerStatisticsServiceStats.getValue(), JsonUtil::jsonStringToValue(jsonData));
	ServerCall *sc = new ServerCall(ServiceName::GlobalGameStatistics, ServiceOperation::ProcessStatistics, message, callback);
	_client->sendRequest(sc);
}