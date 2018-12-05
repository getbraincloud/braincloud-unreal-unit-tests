// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#ifndef _BRAINCLOUDMESSAGING_H_
#define _BRAINCLOUDMESSAGING_H_

#include "braincloud/BrainCloudTypes.h"

#include <string>
#include <vector>

namespace BrainCloud
{
	class IServerCallback;
	class BrainCloudClient;

	class BrainCloudMessaging
	{
	public:
		BrainCloudMessaging(BrainCloudClient* in_client);

		/**
		 * Deletes specified user messages on the server.
		 *
		 * Service Name - Messaging
		 * Service Operation - DeleteMessages
		 *
		 * @param msgIds Arrays of message ids to delete.
		 * @param callback The method to be invoked when the server response is received
		 */
		void deleteMessages(const std::string& in_msgbox, const std::vector<std::string>& in_msgIds, IServerCallback* in_callback = NULL);

		/**
		 * Retrieve user's message boxes, including 'inbox', 'sent', etc.
		 *
		 * Service Name - Messaging
		 * Service Operation - GetMessageboxes
		 *
		 * @param callback The method to be invoked when the server response is received
		 */	
		void getMessageboxes(IServerCallback* in_callback = NULL);

		/**
		 * Retrieve user's message boxes, including 'inbox', 'sent', etc.
		 *
		 * Service Name - Messaging
		 * Service Operation - GetMessageCounts
		 *
		 * @param callback The method to be invoked when the server response is received
		 */	
		void getMessageCounts(IServerCallback* in_callback = NULL);

		/**
		 * Retrieves list of specified messages.
		 *
		 * Service Name - Messaging
		 * Service Operation - GetMessages
		 *
		 * @param msgIds Arrays of message ids to get.
		 * @param callback The method to be invoked when the server response is received
		 */
		void getMessages(const std::string& in_msgbox, const std::vector<std::string>& in_msgIds, IServerCallback* in_callback = NULL);

		/**
		 * Retrieves a page of messages.
		 *
		 * Service Name - Messaging
		 * Service Operation - GetMessagesPage
		 *
		 * @param context
		 * @param callback The method to be invoked when the server response is received
		 */
		void getMessagesPage(const std::string& in_context, IServerCallback* in_callback = NULL);

		/**
		 * Gets the page of messages from the server based on the encoded context and specified page offset.
		 *
		 * Service Name - Messaging
		 * Service Operation - GetMessagesPageOffset
		 *
		 * @param context
		 * @param pageOffset
		 * @param callback The method to be invoked when the server response is received
		 */
		void getMessagesPageOffset(const std::string& in_context, int in_pageOffset, IServerCallback* in_callback = NULL);

		/**
		 * Sends a message with specified 'subject' and 'text' to list of users.
		 *
		 * Service Name - Messaging
		 * Service Operation - SendMessage
		 *
		 * @param toProfileIds
		 * @param contentJson the message you are sending
		 * @param callback The method to be invoked when the server response is received
		 */
		void sendMessage(const std::vector<std::string>& in_toProfileIds, std::string in_contentJson, IServerCallback* in_callback = NULL);

		/**
		 * Sends a simple message to specified list of users.
		 *
		 * Service Name - Messaging
		 * Service Operation - SendMessageSimple
		 *
		 * @param toProfileIds
		 * @param messageText
		 * @param callback The method to be invoked when the server response is received
		 */
		void sendMessageSimple(const std::vector<std::string>& in_toProfileIds, const std::string& in_messageText, IServerCallback* in_callback = NULL);

		/**
		 * Marks list of user messages as read on the server.
		 *
		 * Service Name - Messaging
		 * Service Operation - MarkMessagesRead
		 *
		 * @param msgbox
		 * @param msgIds
		 * @param callback The method to be invoked when the server response is received
		 */
		void markMessagesRead(const std::string& in_msgbox, const std::vector<std::string>& in_msgIds, IServerCallback* in_callback = NULL);

	private:
		BrainCloudClient* m_client;
	};
};

#endif /* _BRAINCLOUDMESSAGING_H_ */
