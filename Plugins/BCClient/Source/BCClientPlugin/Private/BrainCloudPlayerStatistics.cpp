// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudPlayerStatistics.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudPlayerStatistics::BrainCloudPlayerStatistics(BrainCloudClient *client) : _client(client){};

void BrainCloudPlayerStatistics::readAllUserStats(IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	ServerCall *sc = new ServerCall(ServiceName::PlayerStatistics, ServiceOperation::Read, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPlayerStatistics::readUserStatsSubset(const TArray<FString> &playerStats, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetArrayField(OperationParam::PlayerStatisticsServiceStats.getValue(), JsonUtil::arrayToJsonArray(playerStats));
	ServerCall *sc = new ServerCall(ServiceName::PlayerStatistics, ServiceOperation::ReadSubset, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPlayerStatistics::readUserStatisticsByCategory(const FString &category, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GamificationServiceCategory.getValue(), category);

	ServerCall *sc = new ServerCall(ServiceName::Gamification, ServiceOperation::ReadPlayerStatisticsByCategory, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPlayerStatistics::resetAllUserStats(IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	ServerCall *sc = new ServerCall(ServiceName::PlayerStatistics, ServiceOperation::Reset, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPlayerStatistics::incrementUserStats(const FString &jsonData, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetObjectField(OperationParam::PlayerStatisticsServiceStats.getValue(), JsonUtil::jsonStringToValue(jsonData));
	ServerCall *sc = new ServerCall(ServiceName::PlayerStatistics, ServiceOperation::Update, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPlayerStatistics::getNextExperienceLevel(IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	ServerCall *sc = new ServerCall(ServiceName::PlayerStatistics, ServiceOperation::ReadNextXplevel, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPlayerStatistics::incrementExperiencePoints(int32 xpValue, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetNumberField(OperationParam::PlayerStatisticsExperiencePoints.getValue(), xpValue);
	ServerCall *sc = new ServerCall(ServiceName::PlayerStatistics, ServiceOperation::Update, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPlayerStatistics::setExperiencePoints(int32 xpValue, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetNumberField(OperationParam::PlayerStatisticsExperiencePoints.getValue(), xpValue);
	ServerCall *sc = new ServerCall(ServiceName::PlayerStatistics, ServiceOperation::SetXpPoints, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudPlayerStatistics::processStatistics(const FString &jsonData, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetObjectField(OperationParam::PlayerStatisticsServiceStats.getValue(), JsonUtil::jsonStringToValue(jsonData));
	ServerCall *sc = new ServerCall(ServiceName::PlayerStatistics, ServiceOperation::ProcessStatistics, message, callback);
	_client->sendRequest(sc);
}