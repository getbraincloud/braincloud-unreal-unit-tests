
#if defined(__APPLE__) && !defined(HG_PLATFORM_BB)
#include "TargetConditionals.h"
#endif

#include "BrainCloudGamification.h"

#include "BrainCloudTypes.h"
#include "BrainCloudClient.h"
#include "IServerCallback.h"
#include "json/json.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "OperationParam.h"
#include "JsonUtil.h"


namespace BrainCloud {
	
	BrainCloudGamification::BrainCloudGamification()
	{
		
	}

	void BrainCloudGamification::readAllGamification(bool in_includeMetaData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GamificationServiceIncludeMetaData.getValue()] = in_includeMetaData;

		ServerCall * sc = new ServerCall( ServiceName::Gamification, ServiceOperation::Read, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest( sc );
	}

	void BrainCloudGamification::readQuests(bool in_includeMetaData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GamificationServiceIncludeMetaData.getValue()] = in_includeMetaData;

		ServerCall * sc = new ServerCall( ServiceName::Gamification, ServiceOperation::ReadQuests, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest( sc );
	}

	void BrainCloudGamification::readMilestones(bool in_includeMetaData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GamificationServiceIncludeMetaData.getValue()] = in_includeMetaData;

		ServerCall * sc = new ServerCall( ServiceName::Gamification, ServiceOperation::ReadMilestones, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest( sc );
	}
	
	void BrainCloudGamification::readAchievements(bool in_includeMetaData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GamificationServiceIncludeMetaData.getValue()] = in_includeMetaData;

		ServerCall * sc = new ServerCall( ServiceName::Gamification, ServiceOperation::ReadAchievements, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest( sc );
	}
	
	void BrainCloudGamification::readXpLevelsMetaData( IServerCallback * in_callback )
	{
		Json::Value message;
		
		ServerCall * sc = new ServerCall( ServiceName::Gamification, ServiceOperation::ReadXpLevels, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest( sc );
	}
	
	void BrainCloudGamification::readAchievedAchievements(bool in_includeMetaData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GamificationServiceIncludeMetaData.getValue()] = in_includeMetaData;

		ServerCall * sc = new ServerCall( ServiceName::Gamification, ServiceOperation::ReadAchievedAchievements, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest( sc );
	}
	
	void BrainCloudGamification::readCompletedQuests(bool in_includeMetaData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GamificationServiceIncludeMetaData.getValue()] = in_includeMetaData;

		ServerCall * sc = new ServerCall( ServiceName::Gamification, ServiceOperation::ReadCompletedQuests, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest( sc );
	}
	
	void BrainCloudGamification::readInProgressQuests(bool in_includeMetaData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GamificationServiceIncludeMetaData.getValue()] = in_includeMetaData;

		ServerCall * sc = new ServerCall( ServiceName::Gamification, ServiceOperation::ReadInProgressQuests, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest( sc );
	}
	
	void BrainCloudGamification::readNotStartedQuests(bool in_includeMetaData, IServerCallback * callback)
	{
		Json::Value message;
		message[OperationParam::GamificationServiceIncludeMetaData.getValue()] = in_includeMetaData;

		ServerCall * sc = new ServerCall( ServiceName::Gamification, ServiceOperation::ReadNotStartedQuests, message, callback );
		BrainCloudClient::getInstance()->sendRequest( sc );
	}
	
	void BrainCloudGamification::readQuestsWithStatus(bool in_includeMetaData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GamificationServiceIncludeMetaData.getValue()] = in_includeMetaData;

		ServerCall * sc = new ServerCall( ServiceName::Gamification, ServiceOperation::ReadQuestsWithStatus, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest( sc );
	}
	
	void BrainCloudGamification::readQuestsWithBasicPercentage(bool in_includeMetaData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GamificationServiceIncludeMetaData.getValue()] = in_includeMetaData;

		ServerCall * sc = new ServerCall( ServiceName::Gamification, ServiceOperation::ReadQuestsWithBasicPercentage, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest( sc );
	}
	
	void BrainCloudGamification::readQuestsWithComplexPercentage(bool in_includeMetaData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GamificationServiceIncludeMetaData.getValue()] = in_includeMetaData;

		ServerCall * sc = new ServerCall( ServiceName::Gamification, ServiceOperation::ReadQuestsWithComplexPercentage, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest( sc );
	}
	
	void BrainCloudGamification::readCompletedMilestones(bool in_includeMetaData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GamificationServiceIncludeMetaData.getValue()] = in_includeMetaData;

		ServerCall * sc = new ServerCall( ServiceName::Gamification, ServiceOperation::ReadCompletedMilestones, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest( sc );
	}
	
	void BrainCloudGamification::readInProgressMilestones(bool in_includeMetaData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GamificationServiceIncludeMetaData.getValue()] = in_includeMetaData;
		message[OperationParam::GamificationServiceIncludeMetaData.getValue()] = in_includeMetaData;

		ServerCall * sc = new ServerCall( ServiceName::Gamification, ServiceOperation::ReadInProgressMilestones, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest( sc );
	}
	
	void BrainCloudGamification::readQuestsByCategory(const char * in_category, bool in_includeMetaData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GamificationServiceCategory.getValue()] = in_category;
		message[OperationParam::GamificationServiceIncludeMetaData.getValue()] = in_includeMetaData;
		
		ServerCall * sc = new ServerCall( ServiceName::Gamification, ServiceOperation::ReadQuestsByCategory, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest( sc );
	}
	
	void BrainCloudGamification::readMilestonesByCategory(const char * in_category, bool in_includeMetaData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GamificationServiceCategory.getValue()] = in_category;
		message[OperationParam::GamificationServiceIncludeMetaData.getValue()] = in_includeMetaData;

		ServerCall * sc = new ServerCall( ServiceName::Gamification, ServiceOperation::ReadMilestonesByCategory, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest( sc );
	}
    
    void BrainCloudGamification::awardAchievements(const std::vector<std::string> & in_achievements, IServerCallback * in_callback)
    {
        Json::Value message;
        Json::Value achievementArray = JsonUtil::stringVectorToJson(in_achievements);
        message[OperationParam::GamificationServiceAchievementsName.getValue()] = achievementArray;
        
        ServerCall * sc = new ServerCall( ServiceName::Gamification, ServiceOperation::AwardAchievements, message, in_callback );
        BrainCloudClient::getInstance()->sendRequest( sc );
    }
	
    //Deprecated
	void BrainCloudGamification::awardAchievements( const char * in_achievements, IServerCallback * in_callback )
	{
		Json::Value message;
		Json::Value achievementArray;
		JsonUtil::commaSepStringToJsonArray(in_achievements, achievementArray);
		message[OperationParam::GamificationServiceAchievementsName.getValue()] = achievementArray;

		ServerCall * sc = new ServerCall( ServiceName::Gamification, ServiceOperation::AwardAchievements, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest( sc );
	}
    
    void BrainCloudGamification::resetMilestones(const std::vector<std::string> & in_milestoneIds, IServerCallback * in_callback)
    {
        Json::Value message;
        Json::Value milestoneArray = JsonUtil::stringVectorToJson(in_milestoneIds);
        message[OperationParam::GamificationServiceMilestonesName.getValue()] = milestoneArray;
        
        ServerCall * sc = new ServerCall(ServiceName::Gamification, ServiceOperation::ResetMilestones, message, in_callback);
        BrainCloudClient::getInstance()->sendRequest(sc);
    }
	
    //Deprecated
	void BrainCloudGamification::resetMilestones(const char * in_milestoneIds, IServerCallback * in_callback)
	{
		Json::Value message;
		Json::Value milestoneArray;
		JsonUtil::commaSepStringToJsonArray(in_milestoneIds, milestoneArray);
		message[OperationParam::GamificationServiceMilestonesName.getValue()] = milestoneArray;

		ServerCall * sc = new ServerCall(ServiceName::Gamification, ServiceOperation::ResetMilestones, message, in_callback);
		BrainCloudClient::getInstance()->sendRequest(sc);
	}

}  // end namespace
