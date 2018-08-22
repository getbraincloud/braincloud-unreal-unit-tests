// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#ifndef _BRAINCLOUDCHAT_H_
#define _BRAINCLOUDCHAT_H_

#include "braincloud/BrainCloudTypes.h"

#include <string>

namespace BrainCloud
{
	class IServerCallback;
	class BrainCloudClient;

	class BrainCloudChat
	{
	public:
		BrainCloudChat(BrainCloudClient* in_client);

		/**
		 * Registers a listener for incoming events from <channelId>.
		 * Also returns a list of <maxReturn> recent messages from history.
		 *
		 * Service Name - Chat
		 * Service Operation - ChannelConnect
		 *
		 * @param channelId The id of the chat channel to return history from.
		 * @param maxReturn Maximum number of messages to return.
		 * @param callback The method to be invoked when the server response is received
		 */
		void channelConnect(const std::string& in_channelId, int in_maxReturn, IServerCallback* in_callback = NULL);

		/**
		 * Unregisters a listener for incoming events from <channelId>.
		 *
		 * Service Name - Chat
		 * Service Operation - ChannelDisconnect
		 *
		 * @param channelId The id of the chat channel to unsubscribed from.
		 * @param callback The method to be invoked when the server response is received
		 */
		void channelDisconnect(const std::string& in_channelId, IServerCallback* in_callback = NULL);

		/**
		 * Delete a chat message. <version> must match the latest or pass -1 to bypass version check.
		 *
		 * Service Name - Chat
		 * Service Operation - DeleteChatMessage
		 *
		 * @param channelId The id of the chat channel that contains the message to delete.
		 * @param msgId The message id to delete.
		 * @param version Version of the message to delete. Must match latest or pass -1 to bypass version check.
		 * @param callback The method to be invoked when the server response is received
		 */
		void deleteChatMessage(const std::string& in_channelId, const std::string& in_msgId, int version, IServerCallback* in_callback = NULL);

		/**
		 * Gets the channelId for the given <channelType> and <channelSubId>. Channel type must be one of "gl" or "gr".
		 *
		 * Service Name - Chat
		 * Service Operation - GetChannelId
		 *
		 * @param channelType Channel type must be one of "gl" or "gr". For (global) or (group) respectively.
		 * @param channelSubId The sub id of the channel.
		 * @param callback The method to be invoked when the server response is received
		 */
		void getChannelId(const std::string& in_channelType, const std::string& in_channelSubId, IServerCallback* in_callback = NULL);

		/**
		 * Gets description info and activity stats for channel <channelId>.
		 * Note that numMsgs and listeners only returned for non-global groups.
		 * Only callable for channels the user is a member of.
		 *
		 * Service Name - Chat
		 * Service Operation - GetChannelInfo
		 *
		 * @param channelId Id of the channel to receive the info from.
		 * @param callback The method to be invoked when the server response is received.
		 */
		void getChannelInfo(const std::string& in_channelId, IServerCallback* in_callback = NULL);

		/**
		 * Gets a populated chat object (normally for editing).
		 *
		 * Service Name - Chat
		 * Service Operation - GetChatMessage
		 *
		 * @param channelId Id of the channel to receive the message from.
		 * @param msgId Id of the message to read.
		 * @param callback The method to be invoked when the server response is received.
		 */
		void getChatMessage(const std::string& in_channelId, const std::string& in_msgId, IServerCallback* in_callback = NULL);

		/**
		 * Get a list of <maxReturn> messages from history of channel <channelId>.
		 *
		 * Service Name - Chat
		 * Service Operation - GetRecentChatMessages
		 *
		 * @param channelId Id of the channel to receive the info from.
		 * @param maxReturn Maximum message count to return.
		 * @param callback The method to be invoked when the server response is received.
		 */
		void getRecentChatMessages(const std::string& in_channelId, int in_maxReturn, IServerCallback* in_callback = NULL);

		/**
		 * Gets a list of the channels of type <channelType> that the user has access to.
		 * Channel type must be one of "gl", "gr" or "all".
		 *
		 * Service Name - Chat
		 * Service Operation - GetSubscribedChannels
		 *
		 * @param channelType Type of channels to get back. "gl" for global, "gr" for group or "all" for both.
		 * @param callback The method to be invoked when the server response is received.
		 */
		void getSubscribedChannels(const std::string& in_channelType, IServerCallback* in_callback = NULL);

		/**
		 * Send a potentially rich chat message.
		 * <content> must contain at least a "text" field for text messaging.
		 *
		 * Service Name - Chat
		 * Service Operation - PostChatMessage
		 *
		 * @param channelId Channel id to post message to.
		 * @param content Object containing "text" for the text message. Can also has rich content for custom data.
		 * @param callback The method to be invoked when the server response is received.
		 */
		void postChatMessage(const std::string& in_channelId, const std::string& in_jsonContent, bool in_recordInHistory, IServerCallback* in_callback = NULL);

		/**
		 * Send a chat message with text only
		 *
		 * Service Name - Chat
		 * Service Operation - PostChatMessage
		 *
		 * @param channelId Channel id to post message to.
		 * @param text The text message.
		 * @param callback The method to be invoked when the server response is received.
		 */
		void postChatMessageSimple(const std::string& in_channelId, const std::string& in_text, bool in_recordInHistory, IServerCallback* in_callback = NULL);

		/**
		 * Update a chat message.
		 * <content> must contain at least a "text" field for text-text messaging.
		 * <version> must match the latest or pass -1 to bypass version check.
		 *
		 * Service Name - Chat
		 * Service Operation - UpdateChatMessage
		 *
		 * @param channelId Channel id where the message to update is.
		 * @param msgId Message id to update.
		 * @param version Version of the message to update. Must match latest or pass -1 to bypass version check.
		 * @param content Data to update. Object containing "text" for the text message. Can also has rich content for custom data.
		 * @param callback The method to be invoked when the server response is received.
		 */
		void updateChatMessage(const std::string& in_channelId, const std::string& in_msgId, int version, const std::string& in_jsonContent, IServerCallback* in_callback = NULL);

	private:
		BrainCloudClient* m_client;
	};
};

#endif /* _BRAINCLOUDCHAT_H_ */
