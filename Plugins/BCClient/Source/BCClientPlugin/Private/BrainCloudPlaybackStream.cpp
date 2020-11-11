// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudPlaybackStream.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudPlaybackStream::BrainCloudPlaybackStream(BrainCloudClient *client) : _client(client){};

void BrainCloudPlaybackStream::startStream(const FString &targetPlayerId, bool includeSharedData, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PlaybackStreamServiceTargetPlayerId.getValue(), targetPlayerId);
    message->SetBoolField(OperationParam::PlaybackStreamServiceIncludeSharedData.getValue(), includeSharedData);

    ServerCall *sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::StartStream, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlaybackStream::readStream(const FString &playbackStreamId, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PlaybackStreamServicePlaybackStreamId.getValue(), playbackStreamId);

    ServerCall *sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::ReadStream, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlaybackStream::endStream(const FString &playbackStreamId, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PlaybackStreamServicePlaybackStreamId.getValue(), playbackStreamId);

    ServerCall *sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::EndStream, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlaybackStream::deleteStream(const FString &playbackStreamId, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PlaybackStreamServicePlaybackStreamId.getValue(), playbackStreamId);

    ServerCall *sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::DeleteStream, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlaybackStream::addEvent(const FString &playbackStreamId, const FString &jsonEventData, const FString &jsonSummary, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PlaybackStreamServicePlaybackStreamId.getValue(), playbackStreamId);
    message->SetObjectField(OperationParam::PlaybackStreamServiceEventData.getValue(), JsonUtil::jsonStringToValue(jsonEventData));
    message->SetObjectField(OperationParam::PlaybackStreamServiceSummary.getValue(), JsonUtil::jsonStringToValue(jsonSummary));

    ServerCall *sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::AddEvent, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlaybackStream::getRecentStreamsForInitiatingPlayer(const FString &initiatingPlayerId, int32 maxNumStreams, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PlaybackStreamServiceInitiatingPlayerId.getValue(), initiatingPlayerId);
    message->SetNumberField(OperationParam::PlaybackStreamServiceMaxNumberOfStreams.getValue(), maxNumStreams);

    ServerCall *sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::GetRecentStreamsForInitiatingPlayer, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudPlaybackStream::getRecentStreamsForTargetPlayer(const FString &targetPlayerId, int32 maxNumStreams, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::PlaybackStreamServiceTargetPlayerId.getValue(), targetPlayerId);
    message->SetNumberField(OperationParam::PlaybackStreamServiceMaxNumberOfStreams.getValue(), maxNumStreams);

    ServerCall *sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::GetRecentStreamsForTargetPlayer, message, callback);
    _client->sendRequest(sc);
}