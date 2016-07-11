// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudGlobalStatistics.h"

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

	void BrainCloudGlobalStatistics::processStatistics(const std::string & in_jsonData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::PlayerStatisticsServiceStats.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);

		ServerCall * sc = new ServerCall(ServiceName::GlobalGameStatistics, ServiceOperation::ProcessStatistics, message, in_callback);
		m_client->sendRequest(sc);
	}
}