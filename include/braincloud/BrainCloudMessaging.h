// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#ifndef _BRAINCLOUDMESSAGING_H_
#define _BRAINCLOUDMESSAGING_H_

#include "braincloud/BrainCloudTypes.h"

#include <string>

namespace BrainCloud
{
	class IServerCallback;
	class BrainCloudClient;

	class BrainCloudMessaging
	{
	public:
		BrainCloudMessaging(BrainCloudClient* in_client);

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
		// void channelConnect(const std::string& in_channelId, int in_maxReturn, IServerCallback* in_callback = NULL);

	private:
		BrainCloudClient* m_client;
	};
};

#endif /* _BRAINCLOUDMESSAGING_H_ */
