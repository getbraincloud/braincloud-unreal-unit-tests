//
//  BrainCloudMatchmaking.cpp
//  GameClientLib
//
//  Created by Venables, Tyler on 2014-03-11.
//
//

#include "BrainCloudMatchmaking.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "StringUtil.h"

namespace BrainCloud {

	void BrainCloudMatchmaking::read(IServerCallback * in_callback)
	{
        ServerCall * sc = new ServerCall( ServiceName::MatchMaking, ServiceOperation::Read, Json::nullValue, in_callback );
		BrainCloudClient::getInstance()->sendRequest(sc);
	}

	void BrainCloudMatchmaking::setPlayerRating(int32_t in_playerRating, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::MatchMakingServicePlayerRating.getValue()] = Json::Value(in_playerRating);
		
		ServerCall * sc = new ServerCall( ServiceName::MatchMaking, ServiceOperation::SetPlayerRating, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest(sc);
	}
	
	void BrainCloudMatchmaking::resetPlayerRating(IServerCallback * in_callback)
	{
		ServerCall * sc = new ServerCall( ServiceName::MatchMaking, ServiceOperation::ResetPlayerRating, Json::nullValue, in_callback );
		BrainCloudClient::getInstance()->sendRequest(sc);
	}
	
	void BrainCloudMatchmaking::incrementPlayerRating(int32_t in_increment, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::MatchMakingServicePlayerRating.getValue()] = in_increment;
		
		ServerCall * sc = new ServerCall( ServiceName::MatchMaking, ServiceOperation::IncrementPlayerRating, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest(sc);
	}
	
	void BrainCloudMatchmaking::decrementPlayerRating(int32_t in_decrement, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::MatchMakingServicePlayerRating.getValue()] = in_decrement;
		
		ServerCall * sc = new ServerCall( ServiceName::MatchMaking, ServiceOperation::DecrementPlayerRating, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest(sc);
	}
	
	void BrainCloudMatchmaking::turnShieldOn(IServerCallback * in_callback)
	{
        ServerCall * sc = new ServerCall( ServiceName::MatchMaking, ServiceOperation::ShieldOn, Json::nullValue, in_callback );
		BrainCloudClient::getInstance()->sendRequest(sc);
	}

	void BrainCloudMatchmaking::turnShieldOnFor(int32_t in_minutes, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::MatchMakingServiceMinutes.getValue()] = in_minutes;
		
		ServerCall * sc = new ServerCall( ServiceName::MatchMaking, ServiceOperation::ShieldOnFor, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest(sc);
	}
	
	void BrainCloudMatchmaking::turnShieldOff(IServerCallback * in_callback)
	{
        ServerCall * sc = new ServerCall( ServiceName::MatchMaking, ServiceOperation::ShieldOff, Json::nullValue, in_callback );
		BrainCloudClient::getInstance()->sendRequest(sc);
	}
    
    void BrainCloudMatchmaking::getShieldExpiry(const char *in_playerId, IServerCallback * in_callback)
    {
        Json::Value message;
        if (StringUtil::IsOptionalParameterValid(in_playerId))
        {
            message[OperationParam::MatchMakingServicePlayerId.getValue()] = in_playerId;
        }
        
        ServerCall * sc = new ServerCall( ServiceName::MatchMaking, ServiceOperation::GetShieldExpiry, message, in_callback );
        BrainCloudClient::getInstance()->sendRequest(sc);
    }
    
	void BrainCloudMatchmaking::findPlayers(int32_t in_rangeDelta, int32_t in_numMatches, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::MatchMakingServiceRangeDelta.getValue()] = in_rangeDelta;
		message[OperationParam::MatchMakingServiceNumMatches.getValue()] = in_numMatches;
		
		ServerCall * sc = new ServerCall( ServiceName::MatchMaking, ServiceOperation::FindPlayers, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest(sc);
	}
    
    void BrainCloudMatchmaking::getOneWayPlayers(int32_t in_rangeDelta, int32_t in_numMatches, IServerCallback * in_callback)
    {
        findPlayers(in_rangeDelta, in_numMatches, in_callback);
    }
	
	void BrainCloudMatchmaking::findPlayersUsingFilter(int32_t in_rangeDelta, int32_t in_numMatches, std::string in_jsonExtraParms, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::MatchMakingServiceRangeDelta.getValue()] = in_rangeDelta;
		message[OperationParam::MatchMakingServiceNumMatches.getValue()] = in_numMatches;
		
		if (!in_jsonExtraParms.empty())
		{
			Json::Value jsonData = BrainCloudClient::getInstance()->jsonStringToValue(in_jsonExtraParms);
			message[OperationParam::MatchMakingServiceExtraParams.getValue()] = jsonData;
		}
		
		ServerCall * sc = new ServerCall( ServiceName::MatchMaking, ServiceOperation::FindPlayersUsingFilter, message, in_callback );
		BrainCloudClient::getInstance()->sendRequest(sc);
	}
    
    void BrainCloudMatchmaking::getOneWayPlayersWithFilter(int32_t in_rangeDelta, int32_t in_numMatches, std::string in_jsonExtraParms, IServerCallback * in_callback)
    {
        findPlayersUsingFilter(in_rangeDelta, in_numMatches, in_jsonExtraParms, in_callback);
    }
	
	void BrainCloudMatchmaking::enableMatchMaking(IServerCallback * in_callback)
	{
        ServerCall * sc = new ServerCall( ServiceName::MatchMaking, ServiceOperation::EnableMatchMaking, Json::nullValue, in_callback );
		BrainCloudClient::getInstance()->sendRequest(sc);
	}
}