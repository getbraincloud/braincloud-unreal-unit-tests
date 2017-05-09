// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudPlayerStatistics.h"

#if defined(__APPLE__) && !defined(HG_PLATFORM_BB)
#include "TargetConditionals.h"
#endif

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
    BrainCloudPlayerStatistics::BrainCloudPlayerStatistics(BrainCloudClient* in_client) : m_client(in_client) { }

    void BrainCloudPlayerStatistics::readAllPlayerStats(IServerCallback *in_callback)
    {
        Json::Value message;
        ServerCall * sc = new ServerCall(ServiceName::PlayerStatistics, ServiceOperation::Read, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudPlayerStatistics::readAllUserStats(IServerCallback *in_callback)
    {
        Json::Value message;
        ServerCall * sc = new ServerCall(ServiceName::PlayerStatistics, ServiceOperation::Read, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudPlayerStatistics::readPlayerStatsSubset(const std::vector<std::string> &in_statistics,
                                                         IServerCallback *in_callback)
    {
        Json::Value message;
        message[OperationParam::PlayerStatisticsServiceStats.getValue()] = JsonUtil::stringVectorToJson(in_statistics);
        ServerCall * sc = new ServerCall(ServiceName::PlayerStatistics, ServiceOperation::ReadSubset, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudPlayerStatistics::readUserStatsSubset(const std::vector<std::string> &in_statistics,
                                                         IServerCallback *in_callback)
    {
        Json::Value message;
        message[OperationParam::PlayerStatisticsServiceStats.getValue()] = JsonUtil::stringVectorToJson(in_statistics);
        ServerCall * sc = new ServerCall(ServiceName::PlayerStatistics, ServiceOperation::ReadSubset, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudPlayerStatistics::readPlayerStatsForCategory(const char *in_category, IServerCallback *in_callback)
    {
        Json::Value message;
        message[OperationParam::GamificationServiceCategory.getValue()] = in_category;

        ServerCall * sc = new ServerCall(ServiceName::PlayerStatistics, ServiceOperation::ReadForCategory, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudPlayerStatistics::readUserStatsForCategory(const char *in_category, IServerCallback *in_callback)
    {
        Json::Value message;
        message[OperationParam::GamificationServiceCategory.getValue()] = in_category;

        ServerCall * sc = new ServerCall(ServiceName::PlayerStatistics, ServiceOperation::ReadForCategory, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudPlayerStatistics::resetAllPlayerStats(IServerCallback *in_callback)
    {
        Json::Value message;
        ServerCall * sc = new ServerCall(ServiceName::PlayerStatistics, ServiceOperation::Reset, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudPlayerStatistics::resetAllUserStats(IServerCallback *in_callback)
    {
        Json::Value message;
        ServerCall * sc = new ServerCall(ServiceName::PlayerStatistics, ServiceOperation::Reset, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudPlayerStatistics::incrementPlayerStats(const std::string &in_jsonData, IServerCallback *in_callback)
    {
        Json::Value message;
        message[OperationParam::PlayerStatisticsServiceStats.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);

        ServerCall * sc = new ServerCall(ServiceName::PlayerStatistics, ServiceOperation::Update, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudPlayerStatistics::incrementUserStats(const std::string &in_jsonData, IServerCallback *in_callback)
    {
        Json::Value message;
        message[OperationParam::PlayerStatisticsServiceStats.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);

        ServerCall * sc = new ServerCall(ServiceName::PlayerStatistics, ServiceOperation::Update, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudPlayerStatistics::getNextExperienceLevel(IServerCallback* in_callback)
    {
        Json::Value message;
        ServerCall * sc = new ServerCall(ServiceName::PlayerStatistics, ServiceOperation::ReadNextXplevel, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudPlayerStatistics::incrementExperiencePoints(int in_xpValue, IServerCallback* in_callback)
    {
        Json::Value message;
        message[OperationParam::PlayerStatisticsExperiencePoints.getValue()] = in_xpValue;
        ServerCall * sc = new ServerCall(ServiceName::PlayerStatistics, ServiceOperation::Update, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudPlayerStatistics::setExperiencePoints(int in_xpValue, IServerCallback* in_callback)
    {
        Json::Value message;
        message[OperationParam::PlayerStatisticsExperiencePoints.getValue()] = in_xpValue;
        ServerCall * sc = new ServerCall(ServiceName::PlayerStatistics, ServiceOperation::SetXpPoints, message, in_callback);
        m_client->sendRequest(sc);
    }

	void BrainCloudPlayerStatistics::processStatistics(const std::string & in_jsonData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::PlayerStatisticsServiceStats.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);

		ServerCall * sc = new ServerCall(ServiceName::PlayerStatistics, ServiceOperation::ProcessStatistics, message, in_callback);
		m_client->sendRequest(sc);
	}
}
