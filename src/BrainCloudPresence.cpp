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

	// void BrainCloudPresence::channelConnect(const std::string& in_channelId, int in_maxReturn, IServerCallback* in_callback)
	// {
	// 	Json::Value message;
	// 	message[OperationParam::ChannelId.getValue()] = in_channelId;
	// 	message[OperationParam::MaxReturn.getValue()] = in_maxReturn;

	// 	ServerCall* sc = new ServerCall(ServiceName::Presence, ServiceOperation::ChannelConnect, message, in_callback);
	// 	m_client->sendRequest(sc);
	// }
};
