// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudGlobalStatistics.h"

#include "BrainCloudClient.h"
#include "IServerCallback.h"
#include "ServerCall.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "OperationParam.h"
#include "json/json.h"

#include "JsonUtil.h"

namespace BrainCloud
{
    BrainCloudGlobalStatistics::BrainCloudGlobalStatistics(BrainCloudClient* in_client) : m_client(in_client) { }

    void BrainCloudGlobalStatistics::readAllGlobalStats(IServerCallback * in_callback)
    {
        Json::Value message;
        ServerCall * sc = new ServerCall(ServiceName::GlobalGameStatistics, ServiceOperation::Read, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudGlobalStatistics::readGlobalStatsSubset(const std::vector<std::string> & in_statistics, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::PlayerStatisticsServiceStats.getValue()] = JsonUtil::stringVectorToJson(in_statistics);

        ServerCall * sc = new ServerCall(ServiceName::GlobalGameStatistics, ServiceOperation::ReadSubset, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudGlobalStatistics::readGlobalStatsForCategory(const char * in_category, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::GamificationServiceCategory.getValue()] = in_category;

        ServerCall * sc = new ServerCall(ServiceName::GlobalGameStatistics, ServiceOperation::ReadForCategory, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudGlobalStatistics::incrementGlobalGameStat(const std::string& in_jsonData, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::PlayerStatisticsServiceStats.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);

        ServerCall * sc = new ServerCall(ServiceName::GlobalGameStatistics, ServiceOperation::UpdateIncrement, message, in_callback);
        m_client->sendRequest(sc);
    }
}