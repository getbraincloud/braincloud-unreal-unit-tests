// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudOneWayMatch.h"

#include "BrainCloudClient.h"
#include "IServerCallback.h"
#include "ServerCall.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "OperationParam.h"
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