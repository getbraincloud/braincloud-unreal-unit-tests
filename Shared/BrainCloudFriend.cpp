//
//  BrainCloudFriend.cpp
//  GameClientLib
//
//  Created by Venables, Tyler on 2014-03-20.
//
//

#include "BrainCloudFriend.h"
#include "BrainCloudClient.h"
#include <sstream>

#include "StringUtil.h"

namespace BrainCloud {

    void BrainCloudFriend::getFriendProfileInfoForExternalId(
                                                const char *in_externalId,
                                                const char *in_authenticationType,
                                                IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::FriendServiceExternalId.getValue()] = in_externalId;
        message[OperationParam::FriendServiceAuthenticationType.getValue()] = in_authenticationType;
        
        ServerCall * sc = new ServerCall(ServiceName::Friend, ServiceOperation::GetFriendProfileInfoForExternalId, message, in_callback);
        BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudFriend::getExternalIdForProfileId(const char * in_profileId, const char * in_authenticationType, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::FriendServiceProfileId.getValue()] = in_profileId;
        message[OperationParam::FriendServiceAuthenticationType.getValue()] = in_authenticationType;

        ServerCall * sc = new ServerCall(ServiceName::Friend, ServiceOperation::GetExternalIdForProfileId, message, in_callback);
        BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue(sc);
    }
    
	void BrainCloudFriend::readFriendEntity(const char* in_entityId, const char*  in_friendId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::FriendServiceEntityId.getValue()] = in_entityId;
		message[OperationParam::FriendServiceFriendId.getValue()] = in_friendId;

		ServerCall * sc = new ServerCall(ServiceName::Friend, ServiceOperation::ReadFriendEntity, message, in_callback);
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudFriend::readFriendsEntities(const char* in_entityType, IServerCallback * in_callback)
	{
		Json::Value message;
		if (StringUtil::IsOptionalParameterValid(in_entityType))
        {
			message[OperationParam::FriendServiceEntityType.getValue()] = in_entityType;
        }

		ServerCall * sc = new ServerCall(ServiceName::Friend, ServiceOperation::ReadFriendsEntities, message, in_callback);
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudFriend::readFriendsWithApplication(bool in_includeSummaryData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::FriendServiceIncludeSummaryData.getValue()] = in_includeSummaryData;

		ServerCall * sc = new ServerCall(ServiceName::Friend, ServiceOperation::ReadFriendsWithApplication, message, in_callback);
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue(sc);
	}
    
	void BrainCloudFriend::readFriendPlayerState( const char * in_friendId, IServerCallback * in_callback )
	{
		Json::Value message;
		message[OperationParam::FriendServiceReadPlayerStateFriendId.getValue()] = in_friendId;
		
		ServerCall * sc = new ServerCall( ServiceName::Friend, ServiceOperation::ReadFriendsPlayerState, message, in_callback );
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}

    // deprecated
	void BrainCloudFriend::updateSummaryFriendData(const char * in_jsonSummaryData,  IServerCallback * in_callback )
	{
		Json::Value message;
		message[OperationParam::PlayerStateServiceUpdateSummaryFriendData.getValue()] = BrainCloudClient::getInstance()->jsonStringToValue(in_jsonSummaryData);
		
		ServerCall * sc = new ServerCall(ServiceName::PlayerState, ServiceOperation::UpdateSummary, message, in_callback);
		BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
	}
    
    void BrainCloudFriend::findPlayerByName( const char * in_searchText, int in_maxResults, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::FriendServiceSearchText.getValue()] = in_searchText;
        message[OperationParam::FriendServiceMaxResults.getValue()] = in_maxResults;
        
        ServerCall * sc = new ServerCall(ServiceName::Friend, ServiceOperation::FindPlayerByName, message, in_callback);
        BrainCloudClient::getInstance()->getBrainCloudComms()->addToQueue( sc );
    }
}






