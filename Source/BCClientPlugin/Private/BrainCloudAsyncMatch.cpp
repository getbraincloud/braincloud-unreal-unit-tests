// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudAsyncMatch.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudAsyncMatch::BrainCloudAsyncMatch(BrainCloudClient *client) : _client(client){};

void BrainCloudAsyncMatch::createMatch(
    const FString &jsonOpponentIds,
    const FString &pushNotificationMessage,
    IServerCallback *callback)
{
    createMatchWithInitialTurn(jsonOpponentIds, TEXT(""), pushNotificationMessage, TEXT(""), TEXT(""), callback);
}

void BrainCloudAsyncMatch::createMatchWithInitialTurn(
    const FString &jsonOpponentIds,
    const FString &jsonMatchState,
    const FString &pushNotificationMessage,
    const FString &nextPlayer,
    const FString &jsonSummary,
    IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetField(OperationParam::AsyncMatchServicePlayers.getValue(), JsonUtil::jsonStringToActualValue(jsonOpponentIds));
    if (OperationParam::isOptionalParamValid(jsonMatchState))
    {
        message->SetObjectField(OperationParam::AsyncMatchServiceMatchState.getValue(), JsonUtil::jsonStringToValue(jsonMatchState));
    }

    if (OperationParam::isOptionalParamValid(nextPlayer))
    {
        TSharedRef<FJsonObject> currentPlayer = MakeShareable(new FJsonObject());
        currentPlayer->SetStringField(OperationParam::AsyncMatchServiceCurrentPlayer.getValue(), nextPlayer);

        message->SetObjectField(OperationParam::AsyncMatchServiceMatchStatus.getValue(), currentPlayer);
    }
    if (OperationParam::isOptionalParamValid(jsonSummary))
    {
        message->SetObjectField(OperationParam::AsyncMatchServiceMatchSummary.getValue(), JsonUtil::jsonStringToValue(jsonSummary));
    }
    if (OperationParam::isOptionalParamValid(pushNotificationMessage))
    {
        message->SetStringField(OperationParam::AsyncMatchServicePushMessage.getValue(), pushNotificationMessage);
    }

    ServerCall *sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::Create, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudAsyncMatch::submitTurn(
    const FString &ownerId,
    const FString &matchId,
    uint64 version,
    const FString &jsonMatchState,
    const FString &pushNotificationMessage,
    const FString &nextPlayer,
    const FString &jsonSummary,
    const FString &jsonStatistics,
    IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::AsyncMatchServiceOwnerId.getValue(), ownerId);
    message->SetStringField(OperationParam::AsyncMatchServiceMatchId.getValue(), matchId);
    message->SetNumberField(OperationParam::AsyncMatchServiceVersion.getValue(), version);
    if (OperationParam::isOptionalParamValid(jsonMatchState))
    {
        message->SetObjectField(OperationParam::AsyncMatchServiceMatchState.getValue(), JsonUtil::jsonStringToValue(jsonMatchState));
    }
    if (OperationParam::isOptionalParamValid(nextPlayer))
    {
        TSharedRef<FJsonObject> currentPlayer = MakeShareable(new FJsonObject());
        currentPlayer->SetStringField(OperationParam::AsyncMatchServiceCurrentPlayer.getValue(), nextPlayer);

        message->SetObjectField(OperationParam::AsyncMatchServiceMatchStatus.getValue(), currentPlayer);
    }
    if (OperationParam::isOptionalParamValid(jsonSummary))
    {
        message->SetObjectField(OperationParam::AsyncMatchServiceMatchSummary.getValue(), JsonUtil::jsonStringToValue(jsonSummary));
    }
    if (OperationParam::isOptionalParamValid(jsonStatistics))
    {
        message->SetObjectField(OperationParam::AsyncMatchServiceStatistics.getValue(), JsonUtil::jsonStringToValue(jsonStatistics));
    }
    if (OperationParam::isOptionalParamValid(pushNotificationMessage))
    {
        message->SetStringField(OperationParam::AsyncMatchServicePushMessage.getValue(), pushNotificationMessage);
    }

    ServerCall *sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::SubmitTurn, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudAsyncMatch::updateMatchSummaryData(const FString &ownerId, const FString &matchId, uint64 version, const FString &jsonSummary, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::AsyncMatchServiceOwnerId.getValue(), ownerId);
    message->SetStringField(OperationParam::AsyncMatchServiceMatchId.getValue(), matchId);
    message->SetNumberField(OperationParam::AsyncMatchServiceVersion.getValue(), version);

    if (jsonSummary.Len() != 0)
    {
        message->SetObjectField(OperationParam::AsyncMatchServiceMatchSummary.getValue(), JsonUtil::jsonStringToValue(jsonSummary));
    }

    ServerCall *sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::UpdateMatchSummary, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudAsyncMatch::completeMatch(const FString &ownerId, const FString &matchId, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::AsyncMatchServiceOwnerId.getValue(), ownerId);
    message->SetStringField(OperationParam::AsyncMatchServiceMatchId.getValue(), matchId);

    ServerCall *sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::Complete, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudAsyncMatch::readMatch(const FString &ownerId, const FString &matchId, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::AsyncMatchServiceOwnerId.getValue(), ownerId);
    message->SetStringField(OperationParam::AsyncMatchServiceMatchId.getValue(), matchId);

    ServerCall *sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::ReadMatch, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudAsyncMatch::readMatchHistory(const FString &ownerId, const FString &matchId, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::AsyncMatchServiceOwnerId.getValue(), ownerId);
    message->SetStringField(OperationParam::AsyncMatchServiceMatchId.getValue(), matchId);

    ServerCall *sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::ReadMatchHistory, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudAsyncMatch::findMatches(IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    ServerCall *sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::FindMatches, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudAsyncMatch::findCompleteMatches(IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    ServerCall *sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::FindMatchesCompleted, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudAsyncMatch::abandonMatch(const FString &ownerId, const FString &matchId, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::AsyncMatchServiceOwnerId.getValue(), ownerId);
    message->SetStringField(OperationParam::AsyncMatchServiceMatchId.getValue(), matchId);

    ServerCall *sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::Abandon, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudAsyncMatch::deleteMatch(const FString &ownerId, const FString &matchId, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::AsyncMatchServiceOwnerId.getValue(), ownerId);
    message->SetStringField(OperationParam::AsyncMatchServiceMatchId.getValue(), matchId);

    ServerCall *sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::DeleteMatch, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudAsyncMatch::abandonMatchWithSummaryData(const FString &ownerId, const FString &matchId, const FString &pushContent, const FString &summary, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::AsyncMatchServiceOwnerId.getValue(), ownerId);
    message->SetStringField(OperationParam::AsyncMatchServiceMatchId.getValue(), matchId);

    if (OperationParam::isOptionalParamValid(pushContent))
    {
        message->SetStringField(OperationParam::AsyncMatchServicePushMessage.getValue(), pushContent);
    }
    message->SetObjectField(OperationParam::AsyncMatchServiceMatchSummary.getValue(), JsonUtil::jsonStringToValue(summary));
    
    ServerCall *sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::AbandonMatchWithSummaryData, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudAsyncMatch::completeMatchWithSummaryData(const FString &ownerId, const FString &matchId, const FString &pushContent, const FString &summary, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::AsyncMatchServiceOwnerId.getValue(), ownerId);
    message->SetStringField(OperationParam::AsyncMatchServiceMatchId.getValue(), matchId);
    if (OperationParam::isOptionalParamValid(pushContent))
    {
        message->SetStringField(OperationParam::AsyncMatchServicePushMessage.getValue(), pushContent);
    }
    message->SetObjectField(OperationParam::AsyncMatchServiceMatchSummary.getValue(), JsonUtil::jsonStringToValue(summary));

    ServerCall *sc = new ServerCall(ServiceName::AsyncMatch, ServiceOperation::CompleteMatchWithSummaryData, message, callback);
    _client->sendRequest(sc);
}
