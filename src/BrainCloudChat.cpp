// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudChat.h"
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
	BrainCloudChat::BrainCloudChat(BrainCloudClient* in_client)
		: m_client(in_client)
	{
	}

	void BrainCloudChat::channelConnect(const std::string& in_channelId, int in_maxReturn, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::ChannelId.getValue()] = in_channelId;
		message[OperationParam::MaxReturn.getValue()] = in_maxReturn;

		ServerCall* sc = new ServerCall(ServiceName::Chat, ServiceOperation::ChannelConnect, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudChat::channelDisconnect(const std::string& in_channelId, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::ChannelId.getValue()] = in_channelId;

		ServerCall* sc = new ServerCall(ServiceName::Chat, ServiceOperation::ChannelDisconnect, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudChat::deleteChatMessage(const std::string& in_channelId, const std::string& in_msgId, int in_version, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::ChannelId.getValue()] = in_channelId;
		message[OperationParam::MsgId.getValue()] = in_msgId;
		message[OperationParam::Version.getValue()] = in_version;

		ServerCall* sc = new ServerCall(ServiceName::Chat, ServiceOperation::DeleteChatMessage, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudChat::getChannelId(const std::string& in_channelType, const std::string& in_channelSubId, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::ChannelType.getValue()] = in_channelType;
		message[OperationParam::ChannelSubId.getValue()] = in_channelSubId;

		ServerCall* sc = new ServerCall(ServiceName::Chat, ServiceOperation::GetChannelId, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudChat::getChannelInfo(const std::string& in_channelId, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::ChannelId.getValue()] = in_channelId;

		ServerCall* sc = new ServerCall(ServiceName::Chat, ServiceOperation::GetChannelInfo, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudChat::getChatMessage(const std::string& in_channelId, const std::string& in_msgId, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::ChannelId.getValue()] = in_channelId;
		message[OperationParam::MsgId.getValue()] = in_msgId;

		ServerCall* sc = new ServerCall(ServiceName::Chat, ServiceOperation::GetChatMessage, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudChat::getRecentChatMessages(const std::string& in_channelId, int in_maxReturn, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::ChannelId.getValue()] = in_channelId;
		message[OperationParam::MaxReturn.getValue()] = in_maxReturn;

		ServerCall* sc = new ServerCall(ServiceName::Chat, ServiceOperation::GetRecentChatMessages, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudChat::getSubscribedChannels(const std::string& in_channelType, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::ChannelType.getValue()] = in_channelType;

		ServerCall* sc = new ServerCall(ServiceName::Chat, ServiceOperation::GetSubscribedChannels, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudChat::postChatMessage(const std::string& in_channelId, const std::string& in_jsonContent, bool in_recordInHistory, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::ChannelId.getValue()] = in_channelId;
		message[OperationParam::Content.getValue()] = JsonUtil::jsonStringToValue(in_jsonContent.c_str());
		message[OperationParam::RecordInHistory.getValue()] = in_recordInHistory;

		ServerCall* sc = new ServerCall(ServiceName::Chat, ServiceOperation::PostChatMessage, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudChat::postChatMessageSimple(const std::string& in_channelId, const std::string& in_text, bool in_recordInHistory, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::ChannelId.getValue()] = in_channelId;
		Json::Value content;
		content[OperationParam::Text.getValue()] = in_text;
		message[OperationParam::Content.getValue()] = content;
		message[OperationParam::RecordInHistory.getValue()] = in_recordInHistory;

		ServerCall* sc = new ServerCall(ServiceName::Chat, ServiceOperation::PostChatMessage, message, in_callback);
		m_client->sendRequest(sc);
	}

	void BrainCloudChat::updateChatMessage(const std::string& in_channelId, const std::string& in_msgId, int version, const std::string& in_jsonContent, IServerCallback* in_callback)
	{
		Json::Value message;
		message[OperationParam::ChannelId.getValue()] = in_channelId;
		message[OperationParam::MsgId.getValue()] = in_msgId;
		message[OperationParam::Version.getValue()] = version;
		message[OperationParam::Content.getValue()] = JsonUtil::jsonStringToValue(in_jsonContent.c_str());
		
		ServerCall* sc = new ServerCall(ServiceName::Chat, ServiceOperation::UpdateChatMessage, message, in_callback);
		m_client->sendRequest(sc);
	}
};
