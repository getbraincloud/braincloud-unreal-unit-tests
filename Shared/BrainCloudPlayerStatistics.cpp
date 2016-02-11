
#if defined(__APPLE__) && !defined(HG_PLATFORM_BB)
#include "TargetConditionals.h"
#endif

#include "BrainCloudPlayerStatistics.h"

#include "BrainCloudClient.h"
#include "ServiceOperation.h"
#include "ServiceName.h"
#include "OperationParam.h"
#include "JsonUtil.h"

namespace BrainCloud
{
	void BrainCloudPlayerStatistics::readAllPlayerStats(IServerCallback * in_callback)
	{
		Json::Value message;
		ServerCall * sc = new ServerCall( ServiceName::PlayerStatistics, ServiceOperation::Read, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest(sc);
	}
    
    void BrainCloudPlayerStatistics::readPlayerStatsSubset(const std::vector<std::string> & in_statistics, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::PlayerStatisticsServiceStats.getValue()] = JsonUtil::stringVectorToJson(in_statistics);
        ServerCall * sc = new ServerCall( ServiceName::PlayerStatistics, ServiceOperation::ReadSubset, message, in_callback );
        BrainCloudClient::getInstance()->sendRequest(sc);
    }
	
    //Deprecated
	void BrainCloudPlayerStatistics::readPlayerStatsSubset(const std::string& in_jsonData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::PlayerStatisticsServiceStats.getValue()] = BrainCloudClient::getInstance()->jsonStringToValue(in_jsonData);
		ServerCall * sc = new ServerCall( ServiceName::PlayerStatistics, ServiceOperation::ReadSubset, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest(sc);
	}
    
    void BrainCloudPlayerStatistics::readPlayerStatsForCategory(const char * in_category, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::GamificationServiceCategory.getValue()] = in_category;
        
        ServerCall * sc = new ServerCall( ServiceName::PlayerStatistics, ServiceOperation::ReadForCategory, message, in_callback );
        BrainCloudClient::getInstance()->sendRequest( sc );
    }
    
	void BrainCloudPlayerStatistics::resetAllPlayerStats(IServerCallback * in_callback)
	{
		Json::Value message;
		ServerCall * sc = new ServerCall( ServiceName::PlayerStatistics, ServiceOperation::Reset, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest(sc);
	}
	
	void BrainCloudPlayerStatistics::incrementPlayerStats(const std::string& in_jsonData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::PlayerStatisticsServiceStats.getValue()] = BrainCloudClient::getInstance()->jsonStringToValue(in_jsonData);
		
		ServerCall * sc = new ServerCall( ServiceName::PlayerStatistics, ServiceOperation::Update, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest(sc);
	}
	
	void BrainCloudPlayerStatistics::getNextExperienceLevel( IServerCallback* in_callback)
    {
        Json::Value message;
        ServerCall * sc = new ServerCall( ServiceName::PlayerStatistics, ServiceOperation::ReadNextXplevel, message, in_callback );
        BrainCloudClient::getInstance()->sendRequest(sc);
    }
	
    void BrainCloudPlayerStatistics::incrementExperiencePoints(int in_xpValue, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::PlayerStatisticsExperiencePoints.getValue()] = in_xpValue;
		ServerCall * sc = new ServerCall( ServiceName::PlayerStatistics, ServiceOperation::Update, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest(sc);
	}
	
	void BrainCloudPlayerStatistics::setExperiencePoints(int in_xpValue, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::PlayerStatisticsExperiencePoints.getValue()] = in_xpValue;
		ServerCall * sc = new ServerCall( ServiceName::PlayerStatistics, ServiceOperation::SetXpPoints, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest(sc);
	}
}  // end namespace
