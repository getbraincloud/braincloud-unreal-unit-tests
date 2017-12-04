// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudMatchmaking.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

#include "braincloud/internal/StringUtil.h"
#include "braincloud/internal/JsonUtil.h"

namespace BrainCloud
{
    BrainCloudMatchmaking::BrainCloudMatchmaking(BrainCloudClient* in_client) : m_client(in_client) { }

    void BrainCloudMatchmaking::read(IServerCallback * in_callback)
    {
        ServerCall * sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::Read, Json::nullValue, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudMatchmaking::setPlayerRating(int32_t in_playerRating, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::MatchMakingServicePlayerRating.getValue()] = Json::Value(in_playerRating);

        ServerCall * sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::SetPlayerRating, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudMatchmaking::resetPlayerRating(IServerCallback * in_callback)
    {
        ServerCall * sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::ResetPlayerRating, Json::nullValue, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudMatchmaking::incrementPlayerRating(int32_t in_increment, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::MatchMakingServicePlayerRating.getValue()] = in_increment;

        ServerCall * sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::IncrementPlayerRating, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudMatchmaking::decrementPlayerRating(int32_t in_decrement, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::MatchMakingServicePlayerRating.getValue()] = in_decrement;

        ServerCall * sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::DecrementPlayerRating, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudMatchmaking::turnShieldOn(IServerCallback * in_callback)
    {
        ServerCall * sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::ShieldOn, Json::nullValue, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudMatchmaking::turnShieldOnFor(int32_t in_minutes, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::MatchMakingServiceMinutes.getValue()] = in_minutes;

        ServerCall * sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::ShieldOnFor, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudMatchmaking::incrementShieldOnFor(int32_t in_minutes, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::MatchMakingServiceMinutes.getValue()] = in_minutes;

        ServerCall * sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::IncrementShieldOnFor, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudMatchmaking::turnShieldOff(IServerCallback * in_callback)
    {
        ServerCall * sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::ShieldOff, Json::nullValue, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudMatchmaking::getShieldExpiry(const char *in_playerId, IServerCallback * in_callback)
    {
        Json::Value message;
        if (StringUtil::IsOptionalParameterValid(in_playerId))
        {
            message[OperationParam::MatchMakingServicePlayerId.getValue()] = in_playerId;
        }

        ServerCall * sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::GetShieldExpiry, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudMatchmaking::findPlayers(int32_t in_rangeDelta, int32_t in_numMatches, IServerCallback * in_callback)
    {
        findPlayersWithAttributes(in_rangeDelta, in_numMatches, "", in_callback);
    }

    void BrainCloudMatchmaking::findPlayersWithAttributes(int32_t in_rangeDelta, int32_t in_numMatches, std::string in_jsonAttributes, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::MatchMakingServiceRangeDelta.getValue()] = in_rangeDelta;
        message[OperationParam::MatchMakingServiceNumMatches.getValue()] = in_numMatches;

        if (StringUtil::IsOptionalParameterValid(in_jsonAttributes))
        {
            Json::Value jsonData = JsonUtil::jsonStringToValue(in_jsonAttributes);
            message[OperationParam::MatchMakingServiceAttributes.getValue()] = jsonData;
        }

        ServerCall * sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::FindPlayers, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudMatchmaking::findPlayersUsingFilter(int32_t in_rangeDelta, int32_t in_numMatches, std::string in_jsonExtraParms, IServerCallback * in_callback)
    {
        findPlayersWithAttributesUsingFilter(in_rangeDelta, in_numMatches, "", in_jsonExtraParms, in_callback);
    }

    void BrainCloudMatchmaking::findPlayersWithAttributesUsingFilter(
        int32_t in_rangeDelta,
        int32_t in_numMatches,
        std::string in_jsonAttributes,
        std::string in_jsonExtraParms,
        IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::MatchMakingServiceRangeDelta.getValue()] = in_rangeDelta;
        message[OperationParam::MatchMakingServiceNumMatches.getValue()] = in_numMatches;

        if (StringUtil::IsOptionalParameterValid(in_jsonAttributes))
        {
            Json::Value jsonData = JsonUtil::jsonStringToValue(in_jsonAttributes);
            message[OperationParam::MatchMakingServiceAttributes.getValue()] = jsonData;
        }

        if (StringUtil::IsOptionalParameterValid(in_jsonExtraParms))
        {
            Json::Value jsonData = JsonUtil::jsonStringToValue(in_jsonExtraParms);
            message[OperationParam::MatchMakingServiceExtraParams.getValue()] = jsonData;
        }

        ServerCall * sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::FindPlayersUsingFilter, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudMatchmaking::enableMatchMaking(IServerCallback * in_callback)
    {
        ServerCall * sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::EnableMatchMaking, Json::nullValue, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudMatchmaking::disableMatchMaking(IServerCallback * in_callback)
    {
        ServerCall * sc = new ServerCall(ServiceName::MatchMaking, ServiceOperation::DisableMatchMaking, Json::nullValue, in_callback);
        m_client->sendRequest(sc);
    }
}