// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudMessaging.h"
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
	BrainCloudMessaging::BrainCloudMessaging(BrainCloudClient* in_client)
		: m_client(in_client)
	{
	}

	void BrainCloudMessaging::deleteMessages(const std::string& in_msgbox, const std::vector<std::string>& in_msgIds, IServerCallback* in_callback)
    {
		Json::Value message;
		message[OperationParam::MessagingMsgbox.getValue()] = in_msgbox;
		message[OperationParam::MessagingMsgIds.getValue()] = JsonUtil::stringVectorToJson(in_msgIds);

		ServerCall* sc = new ServerCall(ServiceName::Messaging, ServiceOperation::DeleteMessages, message, in_callback);
		m_client->sendRequest(sc);
    }

	void BrainCloudMessaging::getMessageboxes(IServerCallback* in_callback)
    {
		Json::Value message;

		ServerCall* sc = new ServerCall(ServiceName::Messaging, ServiceOperation::GetMessageboxes, message, in_callback);
		m_client->sendRequest(sc);
    }

	void BrainCloudMessaging::getMessageCounts(IServerCallback* in_callback)
    {
		Json::Value message;

		ServerCall* sc = new ServerCall(ServiceName::Messaging, ServiceOperation::GetMessageCounts, message, in_callback);
		m_client->sendRequest(sc);
    }

	void BrainCloudMessaging::getMessages(const std::string& in_msgbox, const std::vector<std::string>& in_msgIds, IServerCallback* in_callback)
    {
			getMessages(in_msgbox, in_msgIds, false, in_callback);
    }

		void BrainCloudMessaging::getMessages(const std::string& in_msgbox, const std::vector<std::string>& in_msgIds, bool markAsRead, IServerCallback* in_callback)
    {
		Json::Value message;
		message[OperationParam::MessagingMsgbox.getValue()] = in_msgbox;
		message[OperationParam::MessagingMsgIds.getValue()] = JsonUtil::stringVectorToJson(in_msgIds);
		message[OperationParam::MessagingMarkAsRead.getValue()] = markAsRead;

		ServerCall* sc = new ServerCall(ServiceName::Messaging, ServiceOperation::GetMessages, message, in_callback);
		m_client->sendRequest(sc);
    }

	void BrainCloudMessaging::getMessagesPage(const std::string& in_context, IServerCallback* in_callback)
    {
		Json::Value message;
		message[OperationParam::MessagingContext.getValue()] = JsonUtil::jsonStringToValue(in_context.c_str());

		ServerCall* sc = new ServerCall(ServiceName::Messaging, ServiceOperation::GetMessagesPage, message, in_callback);
		m_client->sendRequest(sc);
    }

	void BrainCloudMessaging::getMessagesPageOffset(const std::string& in_context, int in_pageOffset, IServerCallback* in_callback)
    {
		Json::Value message;
		message[OperationParam::MessagingContext.getValue()] = in_context;
		message[OperationParam::MessagingPageOffset.getValue()] = in_pageOffset;

		ServerCall* sc = new ServerCall(ServiceName::Messaging, ServiceOperation::GetMessagesPageOffset, message, in_callback);
		m_client->sendRequest(sc);
    }

	void BrainCloudMessaging::sendMessage(const std::vector<std::string>& in_toProfileIds, std::string in_contentJson, IServerCallback* in_callback)
    {
		Json::Value message;
		message[OperationParam::MessagingToProfileIds.getValue()] = JsonUtil::stringVectorToJson(in_toProfileIds);
		message[OperationParam::MessagingContentJson.getValue()] = JsonUtil::jsonStringToValue(in_contentJson.c_str());

		ServerCall* sc = new ServerCall(ServiceName::Messaging, ServiceOperation::MessagingSendMessage, message, in_callback);
		m_client->sendRequest(sc);
    }

	void BrainCloudMessaging::sendMessageSimple(const std::vector<std::string>& in_toProfileIds, const std::string& in_messageText, IServerCallback* in_callback)
    {
		Json::Value message;
		message[OperationParam::MessagingToProfileIds.getValue()] = JsonUtil::stringVectorToJson(in_toProfileIds);
		message[OperationParam::MessagingText.getValue()] = in_messageText;

		ServerCall* sc = new ServerCall(ServiceName::Messaging, ServiceOperation::SendMessageSimple, message, in_callback);
		m_client->sendRequest(sc);
    }

	void BrainCloudMessaging::markMessagesRead(const std::string& in_msgbox, const std::vector<std::string>& in_msgIds, IServerCallback* in_callback)
    {
		Json::Value message;
		message[OperationParam::MessagingMsgbox.getValue()] = in_msgbox;
		message[OperationParam::MessagingMsgIds.getValue()] = JsonUtil::stringVectorToJson(in_msgIds);

		ServerCall* sc = new ServerCall(ServiceName::Messaging, ServiceOperation::MarkMessagesRead, message, in_callback);
		m_client->sendRequest(sc);
    }
};
