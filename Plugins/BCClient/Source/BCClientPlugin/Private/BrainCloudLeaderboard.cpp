// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudLeaderboard.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudLeaderboard::BrainCloudLeaderboard(BrainCloudClient *client) : _client(client){};

void BrainCloudLeaderboard::getSocialLeaderboard(const FString &leaderboardId, bool replaceName, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetBoolField(OperationParam::LeaderboardServiceReplaceName.getValue(), replaceName);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetSocialLeaderboard, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::getSocialLeaderboardByVersion(const FString &leaderboardId, bool replaceName, int32 versionId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetBoolField(OperationParam::LeaderboardServiceReplaceName.getValue(), replaceName);
	message->SetNumberField(OperationParam::LeaderboardServiceVersionId.getValue(), versionId);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetSocialLeaderboardByVersion, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::getMultiSocialLeaderboard(const TArray<FString> &leaderboardIds, int32 leaderboardResultCount, bool replaceName, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetArrayField(OperationParam::LeaderboardServiceLeaderboardIds.getValue(), JsonUtil::arrayToJsonArray(leaderboardIds));
	message->SetNumberField(OperationParam::LeaderboardServiceLeaderboardResultCount.getValue(), leaderboardResultCount);
	message->SetBoolField(OperationParam::LeaderboardServiceReplaceName.getValue(), replaceName);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetMultiSocialLeaderboard, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::getGlobalLeaderboardPage(const FString &leaderboardId, ESortOrder sortOrder, int32 startIndex, int32 endIndex, IServerCallback *callback)
{
	getGlobalLeaderboardPageByVersion(leaderboardId, sortOrder, startIndex, endIndex, -1, callback);
}

void BrainCloudLeaderboard::getGlobalLeaderboardPageByVersion(const FString &leaderboardId, ESortOrder sortOrder, int32 startIndex, int32 endIndex, int32 versionId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetStringField(OperationParam::LeaderboardServiceSortOrder.getValue(), leaderboardSortOrderToString(sortOrder));
	message->SetNumberField(OperationParam::LeaderboardServiceStartIndex.getValue(), startIndex);
	message->SetNumberField(OperationParam::LeaderboardServiceEndIndex.getValue(), endIndex);

	if (versionId != -1)
		message->SetNumberField(OperationParam::LeaderboardServiceVersionId.getValue(), versionId);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGlobalLeaderboardPage, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::getGlobalLeaderboardView(const FString &leaderboardId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount, IServerCallback *callback)
{
	getGlobalLeaderboardViewByVersion(leaderboardId, sortOrder, beforeCount, afterCount, -1, callback);
}

void BrainCloudLeaderboard::getGlobalLeaderboardViewByVersion(const FString &leaderboardId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount, int32 versionId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetStringField(OperationParam::LeaderboardServiceSortOrder.getValue(), leaderboardSortOrderToString(sortOrder));
	message->SetNumberField(OperationParam::LeaderboardServiceBeforeCount.getValue(), beforeCount);
	message->SetNumberField(OperationParam::LeaderboardServiceAfterCount.getValue(), afterCount);

	if (versionId != -1)
		message->SetNumberField(OperationParam::LeaderboardServiceVersionId.getValue(), versionId);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGlobalLeaderboardView, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::getGlobalLeaderboardEntryCount(const FString &leaderboardId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGlobalLeaderboardEntryCount, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::getGlobalLeaderboardVersions(const FString &leaderboardId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGlobalLeaderboardVersions, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::postScore(const FString &leaderboardId, int32 score, const FString &jsonOtherData, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetNumberField(OperationParam::LeaderboardServiceScore.getValue(), score);
	message->SetObjectField(OperationParam::LeaderboardServiceData.getValue(), JsonUtil::jsonStringToValue(jsonOtherData));

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::PostScore, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::postScoreToDynamicLeaderboard(const FString &leaderboardId, int32 score, const FString &jsonData,
														  ESocialLeaderboardType leaderboardType, ERotationType rotationType, const FDateTime &rotationStart,
														  int32 retainedCount, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetNumberField(OperationParam::LeaderboardServiceScore.getValue(), score);
	message->SetObjectField(OperationParam::LeaderboardServiceData.getValue(), JsonUtil::jsonStringToValue(jsonData));

	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardType.getValue(), *leaderboardTypeToString(leaderboardType));
	message->SetStringField(OperationParam::LeaderboardServiceRotationType.getValue(), *leaderboardRotationTypeToString(rotationType));

	if (rotationStart > FDateTime::Now())
		message->SetNumberField(OperationParam::LeaderboardServiceRotationResetTime.getValue(), rotationStart.ToUnixTimestamp() * 1000);

	message->SetNumberField(OperationParam::LeaderboardServiceRetainedCount.getValue(), retainedCount);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::PostScoreDynamic, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::postScoreToDynamicLeaderboardDays(const FString &leaderboardId, int32 score, const FString &jsonData,
															  ESocialLeaderboardType leaderboardType, const FDateTime &rotationStart, int32 retainedCount, int32 numDaysToRotate, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetNumberField(OperationParam::LeaderboardServiceScore.getValue(), score);
	message->SetObjectField(OperationParam::LeaderboardServiceData.getValue(), JsonUtil::jsonStringToValue(jsonData));
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardType.getValue(), *leaderboardTypeToString(leaderboardType));
	message->SetStringField(OperationParam::LeaderboardServiceRotationType.getValue(), "DAYS");
	message->SetNumberField(OperationParam::NumDaysToRotate.getValue(), numDaysToRotate);

	if (rotationStart > FDateTime::Now())
		message->SetNumberField(OperationParam::LeaderboardServiceRotationResetTime.getValue(), rotationStart.ToUnixTimestamp() * 1000);

	message->SetNumberField(OperationParam::LeaderboardServiceRetainedCount.getValue(), retainedCount);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::PostScoreDynamic, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::postScoreToDynamicLeaderboardUTC(const FString &leaderboardId, int32 score, const FString &jsonData,
														  ESocialLeaderboardType leaderboardType, ERotationType rotationType, const int64 &rotationStart,
														  int32 retainedCount, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetNumberField(OperationParam::LeaderboardServiceScore.getValue(), score);
	message->SetObjectField(OperationParam::LeaderboardServiceData.getValue(), JsonUtil::jsonStringToValue(jsonData));

	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardType.getValue(), *leaderboardTypeToString(leaderboardType));
	message->SetStringField(OperationParam::LeaderboardServiceRotationType.getValue(), *leaderboardRotationTypeToString(rotationType));

//	if (rotationStart > FDateTime::Now())
		message->SetNumberField(OperationParam::LeaderboardServiceRotationResetTime.getValue(), rotationStart);

	message->SetNumberField(OperationParam::LeaderboardServiceRetainedCount.getValue(), retainedCount);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::PostScoreDynamic, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::postScoreToDynamicLeaderboardDaysUTC(const FString &leaderboardId, int32 score, const FString &jsonData,
															  ESocialLeaderboardType leaderboardType, const int64 &rotationStart, int32 retainedCount, int32 numDaysToRotate, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetNumberField(OperationParam::LeaderboardServiceScore.getValue(), score);
	message->SetObjectField(OperationParam::LeaderboardServiceData.getValue(), JsonUtil::jsonStringToValue(jsonData));
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardType.getValue(), *leaderboardTypeToString(leaderboardType));
	message->SetStringField(OperationParam::LeaderboardServiceRotationType.getValue(), "DAYS");
	message->SetNumberField(OperationParam::NumDaysToRotate.getValue(), numDaysToRotate);

	//if (rotationStart > FDateTime::Now())
		message->SetNumberField(OperationParam::LeaderboardServiceRotationResetTime.getValue(), rotationStart);

	message->SetNumberField(OperationParam::LeaderboardServiceRetainedCount.getValue(), retainedCount);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::PostScoreDynamic, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::postScoreToDynamicGroupLeaderboardDaysUTC(const FString& leaderboardId,
	const FString& groupId, int32 score, const FString& jsonData, ESocialLeaderboardType leaderboardType,
	const FDateTime &rotationStart, int32 retainedCount, int32 numDaysToRotate, IServerCallback* callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetStringField(OperationParam::GroupId.getValue(),groupId);
	message->SetNumberField(OperationParam::LeaderboardServiceScore.getValue(), score);
	message->SetObjectField(OperationParam::LeaderboardServiceData.getValue(), JsonUtil::jsonStringToValue(jsonData));
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardType.getValue(), *leaderboardTypeToString(leaderboardType));
	message->SetStringField(OperationParam::LeaderboardServiceRotationType.getValue(), "DAYS");
	message->SetNumberField(OperationParam::NumDaysToRotate.getValue(), numDaysToRotate);
	message->SetNumberField(OperationParam::LeaderboardServiceRotationResetTime.getValue(), rotationStart.ToUnixTimestamp() * -1000);
	message->SetNumberField(OperationParam::LeaderboardServiceRetainedCount.getValue(), retainedCount);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::PostScoreToDynamicGroupLeaderboard, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::removePlayerScore(const FString &leaderboardId, int32 versionId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetNumberField(OperationParam::ProfileIds.getValue(), versionId);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::RemovePlayerScore, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::playerTournamentReward(const FString &eventName, uint64 multiplier, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceEventName.getValue(), eventName);
	message->SetNumberField(OperationParam::LeaderboardServiceEventMultiplier.getValue(), multiplier);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::RewardTournament, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::getGroupSocialLeaderboard(const FString &leaderboardId, const FString &groupId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGroupSocialLeaderboard, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::getGroupSocialLeaderboardByVersion(const FString &leaderboardId, const FString &groupId, int32 versionId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetNumberField(OperationParam::LeaderboardServiceVersionId.getValue(), versionId);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGroupSocialLeaderboardByVersion, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::getPlayersSocialLeaderboard(const FString &leaderboardId, const TArray<FString> profileIds, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetArrayField(OperationParam::ProfileIds.getValue(), JsonUtil::arrayToJsonArray(profileIds));

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetPlayersSocialLeaderboard, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::getPlayersSocialLeaderboardByVersion(const FString &leaderboardId, const TArray<FString> profileIds, int32 versionId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetArrayField(OperationParam::ProfileIds.getValue(), JsonUtil::arrayToJsonArray(profileIds));
	message->SetNumberField(OperationParam::LeaderboardServiceVersionId.getValue(), versionId);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetPlayersSocialLeaderboardByVersion, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::listAllLeaderboards(IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::ListAllLeaderboards, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::getPlayerScore(const FString &leaderboardId, int32 versionId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetNumberField(OperationParam::ProfileIds.getValue(), versionId);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetPlayerScore, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::getPlayerScores(const FString &leaderboardId, int32 versionId, int32 maxResults, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetNumberField(OperationParam::ProfileIds.getValue(), versionId);
	message->SetNumberField(OperationParam::LeaderboardServiceMaxResults.getValue(), maxResults);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetPlayerScores, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::getPlayerScoresFromLeaderboards(const TArray<FString> leaderboardIds, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetArrayField(OperationParam::LeaderboardServiceLeaderboardIds.getValue(), JsonUtil::arrayToJsonArray(leaderboardIds));

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetPlayerScoresFromLeaderboards, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::postScoreToGroupLeaderboard(const FString &leaderboardId, const FString &groupId, int32 score, const FString &jsonOtherData, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetNumberField(OperationParam::LeaderboardServiceScore.getValue(), score);
	message->SetObjectField(OperationParam::LeaderboardServiceData.getValue(), JsonUtil::jsonStringToValue(jsonOtherData));

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::PostScoreToGroupLeaderboard, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::postScoreToDynamicGroupLeaderboard(const FString &leaderboardId, const FString &groupId, int32 score, const FString &jsonOtherData,ESocialLeaderboardType leaderboardType, 
																ERotationType rotationType, const FDateTime &rotationStart, int32 retainedCount, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetNumberField(OperationParam::LeaderboardServiceScore.getValue(), score);
	message->SetObjectField(OperationParam::LeaderboardServiceData.getValue(), JsonUtil::jsonStringToValue(jsonOtherData));
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardType.getValue(), *leaderboardTypeToString(leaderboardType));

	if (rotationStart > FDateTime::Now())
	message->SetStringField(OperationParam::LeaderboardServiceRotationType.getValue(), *leaderboardRotationTypeToString(rotationType));

	message->SetNumberField(OperationParam::LeaderboardServiceRotationResetTime.getValue(), rotationStart.ToUnixTimestamp() * 1000);
	message->SetNumberField(OperationParam::LeaderboardServiceScore.getValue(), retainedCount);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::PostScoreToDynamicGroupLeaderboard, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::postScoreToDynamicGroupLeaderboardUTC(const FString &leaderboardId, const FString &groupId, int32 score, const FString &jsonOtherData,ESocialLeaderboardType leaderboardType, 
																ERotationType rotationType, const int64 &rotationStart, int32 retainedCount, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetNumberField(OperationParam::LeaderboardServiceScore.getValue(), score);
	message->SetObjectField(OperationParam::LeaderboardServiceData.getValue(), JsonUtil::jsonStringToValue(jsonOtherData));
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardType.getValue(), *leaderboardTypeToString(leaderboardType));

	// if (rotationStart > FDateTime::Now())
	// message->SetStringField(OperationParam::LeaderboardServiceRotationType.getValue(), *leaderboardRotationTypeToString(rotationType));

	message->SetNumberField(OperationParam::LeaderboardServiceRotationResetTime.getValue(), rotationStart);
	message->SetNumberField(OperationParam::LeaderboardServiceScore.getValue(), retainedCount);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::PostScoreToDynamicGroupLeaderboard, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::removeGroupScore(const FString &leaderboardId, const FString &groupId, int32 score, int32 versionId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetNumberField(OperationParam::LeaderboardServiceScore.getValue(), score);
	message->SetNumberField(OperationParam::LeaderboardServiceVersionId.getValue(), versionId);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::RemoveGroupScore, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::getGroupLeaderboardView(const FString &leaderboardId, const FString &groupId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetStringField(OperationParam::LeaderboardServiceSortOrder.getValue(), leaderboardSortOrderToString(sortOrder));
	message->SetNumberField(OperationParam::LeaderboardServiceBeforeCount.getValue(), beforeCount);
	message->SetNumberField(OperationParam::LeaderboardServiceAfterCount.getValue(), afterCount);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGroupLeaderboardView, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::getGroupLeaderboardViewByVersion(const FString &leaderboardId, const FString &groupId, int32 versionId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetNumberField(OperationParam::LeaderboardServiceVersionId.getValue(), versionId);
	message->SetStringField(OperationParam::LeaderboardServiceSortOrder.getValue(), leaderboardSortOrderToString(sortOrder));
	message->SetNumberField(OperationParam::LeaderboardServiceBeforeCount.getValue(), beforeCount);
	message->SetNumberField(OperationParam::LeaderboardServiceAfterCount.getValue(), afterCount);

	ServerCall *sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGroupLeaderboardView, message, callback);
	_client->sendRequest(sc);
}

FString BrainCloudLeaderboard::leaderboardTypeToString(ESocialLeaderboardType type)
{
	switch (type)
	{
	case ESocialLeaderboardType::HIGH_VALUE:
		return "HIGH_VALUE";
	case ESocialLeaderboardType::CUMULATIVE:
		return "CUMULATIVE";
	case ESocialLeaderboardType::LOW_VALUE:
		return "LOW_VALUE";
	case ESocialLeaderboardType::LAST_VALUE:
		return "LAST_VALUE";
	}
	return "TYPE_NOT_FOUND";
}

FString BrainCloudLeaderboard::leaderboardRotationTypeToString(ERotationType type)
{
	switch (type)
	{
	case ERotationType::NEVER:
		return "NEVER";
	case ERotationType::DAILY:
		return "DAILY";
	case ERotationType::WEEKLY:
		return "WEEKLY";
	case ERotationType::MONTHLY:
		return "MONTHLY";
	case ERotationType::YEARLY:
		return "YEARLY";
	}
	return "TYPE_NOT_FOUND";
}

FString BrainCloudLeaderboard::leaderboardSortOrderToString(ESortOrder type)
{
	switch (type)
	{
	case ESortOrder::HIGH_TO_LOW:
		return "HIGH_TO_LOW";
	case ESortOrder::LOW_TO_HIGH:
		return "LOW_TO_HIGH";
	}
	return "TYPE_NOT_FOUND";
}
