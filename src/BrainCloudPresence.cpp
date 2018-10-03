// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudPresence.h"
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
	BrainCloudPresence::BrainCloudPresence(BrainCloudClient* in_client)
		: m_client(in_client)
	{
	}

	void BrainCloudPresence::forcePush(IServerCallback* in_callback)
	{
		Json::Value message;

		ServerCall* sc = new ServerCall(ServiceName::Presence, ServiceOperation::ForcePush, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudPresence::getPresenceOfFriends(const std::string& in_platform, bool in_includeOffline, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::PresencePlatform.getValue()] = in_platform;
		message[OperationParam::PresenceIncludeOffline.getValue()] = in_includeOffline;

		ServerCall* sc = new ServerCall(ServiceName::Presence, ServiceOperation::GetPresenceOfFriends, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudPresence::getPresenceOfGroup(const std::string& in_groupId, bool in_includeOffline, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::PresenceGroupId.getValue()] = in_groupId;
		message[OperationParam::PresenceIncludeOffline.getValue()] = in_includeOffline;

		ServerCall* sc = new ServerCall(ServiceName::Presence, ServiceOperation::GetPresenceOfGroup, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudPresence::getPresenceOfUsers(const std::vector<std::string>& in_profileIds, bool in_includeOffline, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::PresenceProfileIds.getValue()] = JsonUtil::stringVectorToJson(in_profileIds);
		message[OperationParam::PresenceIncludeOffline.getValue()] = in_includeOffline;

		ServerCall* sc = new ServerCall(ServiceName::Presence, ServiceOperation::GetPresenceOfUsers, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudPresence::registerListenersForFriends(const std::string& in_platform, bool in_bidirectional, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::PresencePlatform.getValue()] = in_platform;
		message[OperationParam::PresenceBidirectional.getValue()] = in_bidirectional;

		ServerCall* sc = new ServerCall(ServiceName::Presence, ServiceOperation::RegisterListenersForFriends, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudPresence::registerListenersForGroup(const std::string& in_groupId, bool in_bidirectional, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::PresenceGroupId.getValue()] = in_groupId;
		message[OperationParam::PresenceBidirectional.getValue()] = in_bidirectional;

		ServerCall* sc = new ServerCall(ServiceName::Presence, ServiceOperation::RegisterListenersForGroup, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudPresence::registerListenersForProfiles(const std::vector<std::string>& in_profileIds, bool in_bidirectional, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::PresenceProfileIds.getValue()] = JsonUtil::stringVectorToJson(in_profileIds);
		message[OperationParam::PresenceBidirectional.getValue()] = in_bidirectional;

		ServerCall* sc = new ServerCall(ServiceName::Presence, ServiceOperation::RegisterListenersForProfiles, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudPresence::setVisibility(bool in_visible, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::PresenceVisible.getValue()] = in_visible;

		ServerCall* sc = new ServerCall(ServiceName::Presence, ServiceOperation::SetVisibility, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudPresence::stopListening(IServerCallback* in_callback)
	{
		Json::Value message;

		ServerCall* sc = new ServerCall(ServiceName::Presence, ServiceOperation::StopListening, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudPresence::updateActivity(const std::string& in_jsonActivity, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::PresenceActivity.getValue()] = JsonUtil::jsonStringToValue(in_jsonActivity.c_str());

		ServerCall* sc = new ServerCall(ServiceName::Presence, ServiceOperation::UpdateActivity, message, in_callback);
		m_client->sendRequest(sc);
	}
};
