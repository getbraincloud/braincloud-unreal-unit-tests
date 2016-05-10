// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudOneWayMatch.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

namespace BrainCloud
{
    BrainCloudOneWayMatch::BrainCloudOneWayMatch(BrainCloudClient* in_client) : m_client(in_client) { }

    void BrainCloudOneWayMatch::startMatch(const char * in_otherPlayerId, int32_t in_rangeDelta, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::OneWayMatchServicePlayerId.getValue()] = in_otherPlayerId;
        message[OperationParam::OneWayMatchServiceRangeDelta.getValue()] = in_rangeDelta;

        ServerCall * sc = new ServerCall(ServiceName::OneWayMatch, ServiceOperation::StartMatch, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudOneWayMatch::cancelMatch(const char * in_playbackStreamId, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::OneWayMatchServicePlaybackStreamId.getValue()] = in_playbackStreamId;

        ServerCall * sc = new ServerCall(ServiceName::OneWayMatch, ServiceOperation::CancelMatch, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudOneWayMatch::completeMatch(const char * in_playbackStreamId, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::OneWayMatchServicePlaybackStreamId.getValue()] = in_playbackStreamId;

        ServerCall * sc = new ServerCall(ServiceName::OneWayMatch, ServiceOperation::CompleteMatch, message, in_callback);
        m_client->sendRequest(sc);
    }
}