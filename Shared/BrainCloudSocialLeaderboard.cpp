//
//  BrainCloudLeaderboard.cpp
//  GameClientLib
//
//
//

#include "BrainCloudSocialLeaderboard.h"
#include "BrainCloudClient.h"
#include "JsonUtil.h"

#include <time.h>


namespace BrainCloud {

    
	void BrainCloudSocialLeaderboard::getSocialLeaderboard( const char * in_leaderboardId, bool in_replaceName, IServerCallback * in_callback )
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::SocialLeaderboardServiceReplaceName.getValue()] = in_replaceName;
		
		ServerCall * sc = new ServerCall( ServiceName::SocialLeaderboard, ServiceOperation::GetSocialLeaderboard, message, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}
    
    // deprecated...
    void BrainCloudSocialLeaderboard::getLeaderboard( const char * in_leaderboardId, bool in_replaceName, IServerCallback * in_callback )
    {
        getSocialLeaderboard(in_leaderboardId, in_replaceName, in_callback);
    }
	
    
    void BrainCloudSocialLeaderboard::getMultiSocialLeaderboard(const std::vector<std::string> & in_leaderboardIds, int in_leaderboardResultCount, bool in_replaceName, IServerCallback * in_callback )
    {
        Json::Value message;
        if (in_leaderboardIds.size() > 0)
        {
            message[OperationParam::SocialLeaderboardServiceLeaderboardIds.getValue()] = JsonUtil::stringVectorToJson(in_leaderboardIds);
        }
        message[OperationParam::SocialLeaderboardServiceLeaderboardResultCount.getValue()] = in_leaderboardResultCount;
        message[OperationParam::SocialLeaderboardServiceReplaceName.getValue()] = in_replaceName;
        
        ServerCall * sc = new ServerCall( ServiceName::SocialLeaderboard, ServiceOperation::GetMultiSocialLeaderboard, message, in_callback );
        BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
    }

    
    // deprecated...
	void BrainCloudSocialLeaderboard::getGlobalLeaderboard( const char * in_leaderboardId, FetchType in_fetchType, int in_maxResults, IServerCallback * in_callback )
	{
        const char * fetchType = NULL;
        if (in_fetchType == HIGHEST_RANKED)
        {
            fetchType = "HIGHEST_RANKED";
        }
        else
        {
            fetchType = "HIGHEST_RANKED";
        }
		
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::SocialLeaderboardServiceFetchType.getValue()] = fetchType;
		message[OperationParam::SocialLeaderboardServiceMaxResults.getValue()] = in_maxResults;
		
		ServerCall * sc = new ServerCall( ServiceName::SocialLeaderboard, ServiceOperation::GetGlobalLeaderboard, message, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}
	
	void BrainCloudSocialLeaderboard::getGlobalLeaderboardPage(const char * in_leaderboardId, SortOrder in_sortOrder, int in_startIndex,
		int in_endIndex, bool in_includeLeaderboardSize, IServerCallback * in_callback)
	{
        std::string sortOrder = sortOrderToString(in_sortOrder);
        
        Json::Value message;
        message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
        message[OperationParam::SocialLeaderboardServiceSortOrder.getValue()] = sortOrder;
        message[OperationParam::SocialLeaderboardServiceStartIndex.getValue()] = in_startIndex;
        message[OperationParam::SocialLeaderboardServiceEndIndex.getValue()] = in_endIndex;
        message[OperationParam::SocialLeaderboardServiceIncludeLeaderboardSize.getValue()] = in_includeLeaderboardSize;
        
        ServerCall * sc = new ServerCall(ServiceName::SocialLeaderboard, ServiceOperation::GetGlobalLeaderboardPage, message, in_callback);
        BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue(sc);
	}
    
    void BrainCloudSocialLeaderboard::getGlobalLeaderboardPageByVersion(const char * in_leaderboardId, SortOrder in_sortOrder, int in_startIndex, int in_endIndex, bool in_includeLeaderboardSize, int in_versionId, IServerCallback * in_callback)
    {
        std::string sortOrder = sortOrderToString(in_sortOrder);
        
        Json::Value message;
        message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
        message[OperationParam::SocialLeaderboardServiceSortOrder.getValue()] = sortOrder;
        message[OperationParam::SocialLeaderboardServiceStartIndex.getValue()] = in_startIndex;
        message[OperationParam::SocialLeaderboardServiceEndIndex.getValue()] = in_endIndex;
        message[OperationParam::SocialLeaderboardServiceIncludeLeaderboardSize.getValue()] = in_includeLeaderboardSize;
        message[OperationParam::SocialLeaderboardServiceVersionId.getValue()] = in_versionId;
        
        ServerCall * sc = new ServerCall(ServiceName::SocialLeaderboard, ServiceOperation::GetGlobalLeaderboardPage, message, in_callback);
        BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue(sc);
    }

	void BrainCloudSocialLeaderboard::getGlobalLeaderboardView(const char * in_leaderboardId, SortOrder in_sortOrder, int in_beforeCount,
		int in_afterCount, bool in_includeLeaderboardSize, IServerCallback * in_callback)
	{
        std::string sortOrder = sortOrderToString(in_sortOrder);
        
        Json::Value message;
        message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
        message[OperationParam::SocialLeaderboardServiceSortOrder.getValue()] = sortOrder;
        message[OperationParam::SocialLeaderboardServiceBeforeCount.getValue()] = in_beforeCount;
        message[OperationParam::SocialLeaderboardServiceAfterCount.getValue()] = in_afterCount;
        message[OperationParam::SocialLeaderboardServiceIncludeLeaderboardSize.getValue()] = in_includeLeaderboardSize;
       
        ServerCall * sc = new ServerCall(ServiceName::SocialLeaderboard, ServiceOperation::GetGlobalLeaderboardView, message, in_callback);
        BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue(sc);
	}
    
    void BrainCloudSocialLeaderboard::getGlobalLeaderboardViewByVersion(const char * in_leaderboardId, SortOrder in_sortOrder, int in_beforeCount,
                                                               int in_afterCount, bool in_includeLeaderboardSize, int in_versionId, IServerCallback * in_callback)
    {
        std::string sortOrder = sortOrderToString(in_sortOrder);
        
        Json::Value message;
        message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
        message[OperationParam::SocialLeaderboardServiceSortOrder.getValue()] = sortOrder;
        message[OperationParam::SocialLeaderboardServiceBeforeCount.getValue()] = in_beforeCount;
        message[OperationParam::SocialLeaderboardServiceAfterCount.getValue()] = in_afterCount;
        message[OperationParam::SocialLeaderboardServiceIncludeLeaderboardSize.getValue()] = in_includeLeaderboardSize;
        message[OperationParam::SocialLeaderboardServiceVersionId.getValue()] = in_versionId;
        
        ServerCall * sc = new ServerCall(ServiceName::SocialLeaderboard, ServiceOperation::GetGlobalLeaderboardView, message, in_callback);
        BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue(sc);
    }
    
    void BrainCloudSocialLeaderboard::getGlobalLeaderboardVersions(const char * in_leaderboardId, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
        
        ServerCall * sc = new ServerCall(ServiceName::SocialLeaderboard, ServiceOperation::GetGlobalLeaderboardVersions, message, in_callback);
        BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue(sc);
    }

	void BrainCloudSocialLeaderboard::postScoreToLeaderboard(const char * in_leaderboardId, int64_t in_score, const std::string& in_jsonOtherData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::SocialLeaderboardServiceScore.getValue()] = (Json::Int64) in_score;
		message[OperationParam::SocialLeaderboardServiceData.getValue()] = BrainCloudClient::getInstance()->jsonStringToValue(in_jsonOtherData);
		
		ServerCall * sc = new ServerCall( ServiceName::SocialLeaderboard, ServiceOperation::PostScore, message, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}
	
	void BrainCloudSocialLeaderboard::postScoreToDynamicLeaderboard ( const char * in_leaderboardId, int64_t in_score, const std::string& in_jsonData, SocialLeaderboardType in_leaderboardType, RotationType in_rotationType, const struct tm* in_rotationReset, int in_retainedCount, IServerCallback * in_callback )
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::SocialLeaderboardServiceScore.getValue()] = (Json::Int64) in_score;
		message[OperationParam::SocialLeaderboardServiceData.getValue()] = BrainCloudClient::getInstance()->jsonStringToValue(in_jsonData);
		
		message[OperationParam::SocialLeaderboardServiceLeaderboardType.getValue()] = leaderboardTypeToString(in_leaderboardType).c_str();
		message[OperationParam::SocialLeaderboardServiceRotationType.getValue()] = leaderboardRotationTypeToString(in_rotationType).c_str();
        
        if(in_rotationReset != NULL)
        {
            char buf[80];
            strftime(buf, 80, "%d-%m-%Y %H:%M", in_rotationReset);
            message[OperationParam::SocialLeaderboardServiceRotationReset.getValue()] = buf;
        }
		
		message[OperationParam::SocialLeaderboardServiceRetainedCount.getValue()] = in_retainedCount;
		
		ServerCall * sc = new ServerCall( ServiceName::SocialLeaderboard, ServiceOperation::PostScoreDynamic, message, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}

	void BrainCloudSocialLeaderboard::resetLeaderboardScore( const char * in_leaderboardId, IServerCallback * in_callback )
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		
		ServerCall * sc = new ServerCall( ServiceName::SocialLeaderboard, ServiceOperation::Reset, message, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}
	
	void BrainCloudSocialLeaderboard::getCompletedLeaderboardTournament( const char * in_leaderboardId, bool in_replaceName, IServerCallback * in_callback )
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::SocialLeaderboardServiceReplaceName.getValue()] = in_replaceName;
		
		ServerCall * sc = new ServerCall( ServiceName::SocialLeaderboard, ServiceOperation::GetCompletedTournament, message, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}
	
	void BrainCloudSocialLeaderboard::triggerSocialLeaderboardTournamentReward( const char * in_leaderboardId, const char * in_eventName, uint64_t in_eventMultiplier, IServerCallback * in_callback )
	{
		Json::Value message;
        message[OperationParam::SocialLeaderboardServiceLeaderboardId.getValue()] = in_leaderboardId;
		message[OperationParam::SocialLeaderboardServiceEventName.getValue()] = in_eventName;
		message[OperationParam::SocialLeaderboardServiceEventMultiplier.getValue()] = (Json::UInt64) in_eventMultiplier;
		
		ServerCall * sc = new ServerCall( ServiceName::SocialLeaderboard, ServiceOperation::RewardTournament, message, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}
	
	void BrainCloudSocialLeaderboard::playerTournamentReward( const char * in_eventName, uint64_t in_multiplier, IServerCallback * in_callback )
	{
		Json::Value message;
		message[OperationParam::SocialLeaderboardServiceEventName.getValue()] = in_eventName;
		message[OperationParam::SocialLeaderboardServiceEventMultiplier.getValue()] = (Json::UInt64) in_multiplier;
		
        ServerCall * sc = new ServerCall( ServiceName::SocialLeaderboard, ServiceOperation::RewardTournament, message, in_callback );
        BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}
	
	std::string BrainCloudSocialLeaderboard::leaderboardTypeToString(SocialLeaderboardType type)
	{
		std::string typeString = "HIGH_VALUE";
		
		if (type == CUMULATIVE)
			typeString = "CUMULATIVE";
        else if (type == LAST_VALUE)
            typeString = "LAST_VALUE";
        else if (type == LOW_VALUE)
            typeString = "LOW_VALUE";
		
		return typeString;
	}
	
	std::string BrainCloudSocialLeaderboard::leaderboardRotationTypeToString(RotationType type)
	{
		std::string typeString = "NEVER";
		
		switch (type)
		{
			case DAILY:
				typeString = "DAILY";
				break;
			case WEEKLY:
				typeString = "WEEKLY";
				break;
			case MONTHLY:
				typeString = "MONTHLY";
				break;
			case YEARLY:
				typeString = "YEARLY";
				break;
            default:
                break;
		}
		
		return typeString;
	}
    
    std::string BrainCloudSocialLeaderboard::sortOrderToString(SortOrder in_sortOrder)
    {
        std::string sortOrder = "HIGHEST_RANKED";
        
        if (in_sortOrder == HIGH_TO_LOW)
        {
            sortOrder = "HIGH_TO_LOW";
        }
        else if (in_sortOrder == LOW_TO_HIGH)
        {
            sortOrder = "LOW_TO_HIGH";
        }
        else
        {
            sortOrder = "HIGHEST_RANKED";
        }
        return sortOrder;
    }
}