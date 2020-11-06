// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudFriend.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

#include "braincloud/internal/StringUtil.h"
#include "braincloud/internal/JsonUtil.h"
#include "braincloud/FriendPlatform.h"
#include "braincloud/AuthenticationType.h"

namespace BrainCloud
{
	BrainCloudFriend::BrainCloudFriend(BrainCloudClient* in_client) : m_client(in_client) { }

	void BrainCloudFriend::findUserByExactUniversalId(const char * in_searchText, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::FriendServiceSearchText.getValue()] = in_searchText;

		ServerCall * sc = new ServerCall(ServiceName::Friend, ServiceOperation::FindUserByExactUniversalId, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}


	void BrainCloudFriend::findUsersByNameStartingWith(const char * in_searchText, int32_t in_maxResults, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::FriendServiceSearchText.getValue()] = in_searchText;
		message[OperationParam::FriendServiceMaxResults.getValue()] = in_maxResults;

		ServerCall * sc = new ServerCall(ServiceName::Friend, ServiceOperation::FindUsersByUniversalIdStartingWith, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}


	void BrainCloudFriend::findUsersByUniversalIdStartingWith(const char * in_searchText, int32_t in_maxResults, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::FriendServiceSearchText.getValue()] = in_searchText;
		message[OperationParam::FriendServiceMaxResults.getValue()] = in_maxResults;

		ServerCall * sc = new ServerCall(ServiceName::Friend, ServiceOperation::FindUsersByNameStartingWith, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudFriend::getProfileInfoForCredential(const char * in_externalId, AuthenticationType in_authenticationType, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::FriendServiceExternalId.getValue()] = in_externalId;
		message[OperationParam::FriendServiceAuthenticationType.getValue()] = in_authenticationType.toString();

		ServerCall * sc = new ServerCall(ServiceName::Friend, ServiceOperation::GetProfileInfoForCredential, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudFriend::getProfileInfoForExternalAuthId(const char * in_externalId, const char * in_externalAuthType, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::FriendServiceExternalId.getValue()] = in_externalId;
		message[OperationParam::ExternalAuthType.getValue()] = in_externalAuthType;

		ServerCall * sc = new ServerCall(ServiceName::Friend, ServiceOperation::GetProfileInfoForExternalAuthId, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudFriend::getExternalIdForProfileId(const char * in_profileId, const char * in_authenticationType, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::FriendServiceProfileId.getValue()] = in_profileId;
		message[OperationParam::FriendServiceAuthenticationType.getValue()] = in_authenticationType;

		ServerCall * sc = new ServerCall(ServiceName::Friend, ServiceOperation::GetExternalIdForProfileId, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudFriend::readFriendEntity(const char* in_entityId, const char*  in_friendId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::FriendServiceEntityId.getValue()] = in_entityId;
		message[OperationParam::FriendServiceFriendId.getValue()] = in_friendId;

		ServerCall * sc = new ServerCall(ServiceName::Friend, ServiceOperation::ReadFriendEntity, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudFriend::readFriendsEntities(const char* in_entityType, IServerCallback * in_callback)
	{
		Json::Value message;
		if (StringUtil::IsOptionalParameterValid(in_entityType))
		{
			message[OperationParam::FriendServiceEntityType.getValue()] = in_entityType;
		}

		ServerCall * sc = new ServerCall(ServiceName::Friend, ServiceOperation::ReadFriendsEntities, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudFriend::readFriendUserState(const char * in_friendId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::FriendServiceReadPlayerStateFriendId.getValue()] = in_friendId;

		ServerCall * sc = new ServerCall(ServiceName::Friend, ServiceOperation::ReadFriendsPlayerState, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudFriend::getSummaryDataForProfileId(const char * in_profileId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::FriendServiceProfileId.getValue()] = in_profileId;

		ServerCall * sc = new ServerCall(ServiceName::Friend, ServiceOperation::GetSummaryDataForProfileId, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudFriend::findUsersByExactName(const char * in_searchText, int32_t in_maxResults, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::FriendServiceSearchText.getValue()] = in_searchText;
		message[OperationParam::FriendServiceMaxResults.getValue()] = in_maxResults;

		ServerCall * sc = new ServerCall(ServiceName::Friend, ServiceOperation::FindUsersByExactName, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudFriend::findUsersBySubstrName(const char * in_searchText, int32_t in_maxResults, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::FriendServiceSearchText.getValue()] = in_searchText;
		message[OperationParam::FriendServiceMaxResults.getValue()] = in_maxResults;

		ServerCall * sc = new ServerCall(ServiceName::Friend, ServiceOperation::FindUsersBySubstrName, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudFriend::listFriends(const FriendPlatform& in_friendPlatform, bool in_includeSummaryData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::FriendServiceFriendPlatform.getValue()] = in_friendPlatform.toString();
		message[OperationParam::FriendServiceIncludeSummaryData.getValue()] = in_includeSummaryData;

		ServerCall * sc = new ServerCall(ServiceName::Friend, ServiceOperation::ListFriends, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudFriend::addFriends(const std::vector<std::string>& in_profileIds, IServerCallback * in_callback)
	{
		Json::Value message;
		Json::Value profileArray = JsonUtil::stringVectorToJson(in_profileIds);
		message[OperationParam::FriendServiceProfileIds.getValue()] = profileArray;

		ServerCall * sc = new ServerCall(ServiceName::Friend, ServiceOperation::AddFriends, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudFriend::removeFriends(const std::vector<std::string>& in_profileIds, IServerCallback * in_callback)
	{
		Json::Value message;
		Json::Value profileArray = JsonUtil::stringVectorToJson(in_profileIds);
		message[OperationParam::FriendServiceProfileIds.getValue()] = profileArray;

		ServerCall * sc = new ServerCall(ServiceName::Friend, ServiceOperation::RemoveFriends, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudFriend::getUsersOnlineStatus(const std::vector<std::string>& in_profileIds, IServerCallback * in_callback)
	{
		Json::Value message;
		Json::Value profileArray = JsonUtil::stringVectorToJson(in_profileIds);
		message[OperationParam::FriendServiceProfileIds.getValue()] = profileArray;

		ServerCall * sc = new ServerCall(ServiceName::Friend, ServiceOperation::GetUsersOnlineStatus, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}
}
