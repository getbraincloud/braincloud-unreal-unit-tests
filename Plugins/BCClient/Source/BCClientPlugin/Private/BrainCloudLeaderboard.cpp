// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudLeaderboard.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudLeaderboard::BrainCloudLeaderboard(BrainCloudClient* client) : _client(client) {};

void BrainCloudLeaderboard::getSocialLeaderboard(const FString& leaderboardId, bool replaceName, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
    message->SetBoolField(OperationParam::LeaderboardServiceReplaceName.getValue(), replaceName);

    ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetSocialLeaderboard, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudLeaderboard::getMultiSocialLeaderboard(const TArray<FString>& leaderboardIds, int32 leaderboardResultCount, bool replaceName, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetArrayField(OperationParam::LeaderboardServiceLeaderboardIds.getValue(), JsonUtil::arrayToJsonArray(leaderboardIds));
    message->SetNumberField(OperationParam::LeaderboardServiceLeaderboardResultCount.getValue(), leaderboardResultCount);
    message->SetBoolField(OperationParam::LeaderboardServiceReplaceName.getValue(), replaceName);

    ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetMultiSocialLeaderboard, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudLeaderboard::getGlobalLeaderboardPage(const FString& leaderboardId, ESortOrder sortOrder, int32 startIndex, int32 endIndex, bool includeLeaderboardSize, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
    message->SetStringField(OperationParam::LeaderboardServiceSortOrder.getValue(), leaderboardSortOrderToString(sortOrder));
    message->SetNumberField(OperationParam::LeaderboardServiceStartIndex.getValue(), startIndex);
    message->SetNumberField(OperationParam::LeaderboardServiceEndIndex.getValue(), endIndex);
    message->SetBoolField(OperationParam::LeaderboardServiceIncludeLeaderboardSize.getValue(), includeLeaderboardSize);

    ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGlobalLeaderboardPage, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudLeaderboard::getGlobalLeaderboardPageByVersion(const FString& leaderboardId, ESortOrder sortOrder, int32 startIndex, int32 endIndex, bool includeLeaderboardSize, int32 versionId, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
    message->SetStringField(OperationParam::LeaderboardServiceSortOrder.getValue(), leaderboardSortOrderToString(sortOrder));
    message->SetNumberField(OperationParam::LeaderboardServiceStartIndex.getValue(), startIndex);
    message->SetNumberField(OperationParam::LeaderboardServiceEndIndex.getValue(), endIndex);
    message->SetBoolField(OperationParam::LeaderboardServiceIncludeLeaderboardSize.getValue(), includeLeaderboardSize);
    message->SetNumberField(OperationParam::LeaderboardServiceVersionId.getValue(), versionId);

    ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGlobalLeaderboardPage, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudLeaderboard::getGlobalLeaderboardView(const FString& leaderboardId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount, bool includeLeaderboardSize, IServerCallback * callback)
{
	getGlobalLeaderboardViewByVersion(leaderboardId, sortOrder, beforeCount, afterCount, includeLeaderboardSize, -1, callback);
}

void BrainCloudLeaderboard::getGlobalLeaderboardViewByVersion(const FString& leaderboardId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount, bool includeLeaderboardSize, int32 versionId, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
    message->SetStringField(OperationParam::LeaderboardServiceSortOrder.getValue(), leaderboardSortOrderToString(sortOrder));
    message->SetNumberField(OperationParam::LeaderboardServiceBeforeCount.getValue(), beforeCount);
    message->SetNumberField(OperationParam::LeaderboardServiceAfterCount.getValue(), afterCount);
    message->SetBoolField(OperationParam::LeaderboardServiceIncludeLeaderboardSize.getValue(), includeLeaderboardSize);

	if(versionId != -1)
		message->SetNumberField(OperationParam::LeaderboardServiceVersionId.getValue(), versionId);

    ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGlobalLeaderboardView, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudLeaderboard::getGlobalLeaderboardView(const FString& leaderboardId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount, IServerCallback * callback)
{
	getGlobalLeaderboardViewByVersion(leaderboardId, sortOrder, beforeCount, afterCount, -1, callback);
}

void BrainCloudLeaderboard::getGlobalLeaderboardViewByVersion(const FString& leaderboardId, ESortOrder sortOrder, int32 beforeCount, int32 afterCount, int32 versionId, IServerCallback * callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetStringField(OperationParam::LeaderboardServiceSortOrder.getValue(), leaderboardSortOrderToString(sortOrder));
	message->SetNumberField(OperationParam::LeaderboardServiceBeforeCount.getValue(), beforeCount);
	message->SetNumberField(OperationParam::LeaderboardServiceAfterCount.getValue(), afterCount);

	if (versionId != -1)
		message->SetNumberField(OperationParam::LeaderboardServiceVersionId.getValue(), versionId);

	ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGlobalLeaderboardView, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::getGlobalLeaderboardEntryCount(const FString & leaderboardId, IServerCallback * callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);

	ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGlobalLeaderboardEntryCount, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::getGlobalLeaderboardVersions(const FString& leaderboardId, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);

    ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGlobalLeaderboardVersions, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudLeaderboard::postScore(const FString& leaderboardId, int32 score, const FString& jsonOtherData, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
    message->SetNumberField(OperationParam::LeaderboardServiceScore.getValue(), score);
    message->SetObjectField(OperationParam::LeaderboardServiceData.getValue(), JsonUtil::jsonStringToValue(jsonOtherData));

    ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::PostScore, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudLeaderboard::postScoreToDynamicLeaderboard(const FString& leaderboardId, int32 score, const FString& jsonData,
    ESocialLeaderboardType leaderboardType, ERotationType rotationType, const FDateTime& rotationStart,
    int32 retainedCount, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
    message->SetNumberField(OperationParam::LeaderboardServiceScore.getValue(), score);
    message->SetObjectField(OperationParam::LeaderboardServiceData.getValue(), JsonUtil::jsonStringToValue(jsonData));

    message->SetStringField(OperationParam::LeaderboardServiceLeaderboardType.getValue(), *leaderboardTypeToString(leaderboardType));

	if (rotationStart > FDateTime::Now())
		message->SetNumberField(OperationParam::LeaderboardServiceRotationResetTime.getValue(), rotationStart.ToUnixTimestamp() *  1000);

    message->SetNumberField(OperationParam::LeaderboardServiceRetainedCount.getValue(), retainedCount);

    ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::PostScoreDynamic, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudLeaderboard::resetLeaderboardScore(const FString& leaderboardId, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);

    ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::Reset, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudLeaderboard::playerTournamentReward(const FString& eventName, uint64 multiplier, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LeaderboardServiceEventName.getValue(), eventName);
    message->SetNumberField(OperationParam::LeaderboardServiceEventMultiplier.getValue(), multiplier);

    ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::RewardTournament, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudLeaderboard::getGroupSocialLeaderboard(const FString & leaderboardId, const FString & groupId, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
    message->SetStringField(OperationParam::GroupId.getValue(), groupId);

    ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetGroupSocialLeaderboard, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudLeaderboard::getPlayersSocialLeaderboard(const FString& leaderboardId, const TArray<FString> profileIds, IServerCallback * callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::LeaderboardServiceLeaderboardId.getValue(), leaderboardId);
	message->SetArrayField(OperationParam::ProfileIds.getValue(), JsonUtil::arrayToJsonArray(profileIds));

	ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::GetPlayersSocialLeaderboard, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudLeaderboard::listAllLeaderboards(IServerCallback * callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	ServerCall * sc = new ServerCall(ServiceName::Leaderboard, ServiceOperation::ListAllLeaderboards, message, callback);
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
