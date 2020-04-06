// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudOneWayMatch.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudOneWayMatch::BrainCloudOneWayMatch(BrainCloudClient *client) : _client(client){};

void BrainCloudOneWayMatch::startMatch(const FString &otherPlayerId, int32 rangeDelta, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::OneWayMatchServicePlayerId.getValue(), otherPlayerId);
    message->SetNumberField(OperationParam::OneWayMatchServiceRangeDelta.getValue(), rangeDelta);

    ServerCall *sc = new ServerCall(ServiceName::OneWayMatch, ServiceOperation::StartMatch, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudOneWayMatch::cancelMatch(const FString &playbackStreamId, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::OneWayMatchServicePlaybackStreamId.getValue(), playbackStreamId);

    ServerCall *sc = new ServerCall(ServiceName::OneWayMatch, ServiceOperation::CancelMatch, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudOneWayMatch::completeMatch(const FString &playbackStreamId, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::OneWayMatchServicePlaybackStreamId.getValue(), playbackStreamId);

    ServerCall *sc = new ServerCall(ServiceName::OneWayMatch, ServiceOperation::CompleteMatch, message, callback);
    _client->sendRequest(sc);
}