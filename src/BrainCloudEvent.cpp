// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudEvent.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

#include "braincloud/internal/JsonUtil.h"

namespace BrainCloud
{
	BrainCloudEvent::BrainCloudEvent(BrainCloudClient* in_client) : m_client(in_client) { }

	void BrainCloudEvent::sendEvent(const char * in_toProfileId, const char * in_eventType, const std::string& in_jsonEventData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::EventServiceSendToId.getValue()] = in_toProfileId;
		message[OperationParam::EventServiceSendEventType.getValue()] = in_eventType;
		message[OperationParam::EventServiceSendEventData.getValue()] = JsonUtil::jsonStringToValue(in_jsonEventData);

		ServerCall * sc = new ServerCall(ServiceName::Event, ServiceOperation::Send, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudEvent::updateIncomingEventData(const char * in_evId, const std::string& in_jsonEventData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::EvId.getValue()] = in_evId;
		message[OperationParam::EventServiceUpdateEventDataData.getValue()] = JsonUtil::jsonStringToValue(in_jsonEventData);

		ServerCall * sc = new ServerCall(ServiceName::Event, ServiceOperation::UpdateEventData, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudEvent::deleteIncomingEvent(const char * in_evId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::EvId.getValue()] = in_evId;

		ServerCall * sc = new ServerCall(ServiceName::Event, ServiceOperation::DeleteIncoming, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudEvent::getEvents(IServerCallback * in_callback)
	{
		Json::Value message;
		ServerCall * sc = new ServerCall(ServiceName::Event, ServiceOperation::GetEvents, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

}
