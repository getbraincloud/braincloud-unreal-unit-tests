// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudPlaybackStream.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

#include "braincloud/internal/JsonUtil.h"

namespace BrainCloud
{
    BrainCloudPlaybackStream::BrainCloudPlaybackStream(BrainCloudClient* in_client) : m_client(in_client) { }

    void BrainCloudPlaybackStream::startStream(const char * in_targetPlayerId, bool in_includeSharedData, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::PlaybackStreamServiceTargetPlayerId.getValue()] = in_targetPlayerId;
        message[OperationParam::PlaybackStreamServiceIncludeSharedData.getValue()] = in_includeSharedData;

        ServerCall * sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::StartStream, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudPlaybackStream::readStream(const char * in_playbackStreamId, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::PlaybackStreamServicePlaybackStreamId.getValue()] = in_playbackStreamId;

        ServerCall * sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::ReadStream, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudPlaybackStream::endStream(const char * in_playbackStreamId, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::PlaybackStreamServicePlaybackStreamId.getValue()] = in_playbackStreamId;

        ServerCall * sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::EndStream, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudPlaybackStream::deleteStream(const char * in_playbackStreamId, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::PlaybackStreamServicePlaybackStreamId.getValue()] = in_playbackStreamId;

        ServerCall * sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::DeleteStream, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudPlaybackStream::addEvent(const char * in_playbackStreamId, const char * in_jsonEventData, const char * in_jsonSummary, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::PlaybackStreamServicePlaybackStreamId.getValue()] = in_playbackStreamId;
        message[OperationParam::PlaybackStreamServiceEventData.getValue()] = JsonUtil::jsonStringToValue(in_jsonEventData);
        message[OperationParam::PlaybackStreamServiceSummary.getValue()] = JsonUtil::jsonStringToValue(in_jsonSummary);

        ServerCall * sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::AddEvent, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudPlaybackStream::getStreamSummariesForInitiatingPlayer(const char * in_initiatingPlayerId, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::PlaybackStreamServiceInitiatingPlayerId.getValue()] = in_initiatingPlayerId;

        ServerCall * sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::GetStreamSummariesForInitiatingPlayer, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudPlaybackStream::getStreamSummariesForTargetPlayer(const char * in_targetPlayerId, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::PlaybackStreamServiceTargetPlayerId.getValue()] = in_targetPlayerId;

        ServerCall * sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::GetStreamSummariesForTargetPlayer, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudPlaybackStream::getRecentStreamsForInitiatingPlayer(const char * in_initiatingPlayerId, int in_maxNumStreams, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::PlaybackStreamServiceInitiatingPlayerId.getValue()] = in_initiatingPlayerId;
        message[OperationParam::PlaybackMaxNumberOfStreams.getValue()] = in_maxNumStreams;

        ServerCall * sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::GetRecentStreamsForInitiatingPlayer, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudPlaybackStream::getRecentStreamsForTargetPlayer(const char * in_targetPlayerId, int in_maxNumStreams, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::PlaybackStreamServiceTargetPlayerId.getValue()] = in_targetPlayerId;
        message[OperationParam::PlaybackMaxNumberOfStreams.getValue()] = in_maxNumStreams;

        ServerCall * sc = new ServerCall(ServiceName::PlaybackStream, ServiceOperation::GetRecentStreamsForTargetPlayer, message, in_callback);
        m_client->sendRequest(sc);
    }
}
