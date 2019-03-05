// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudEvent.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudEvent::BrainCloudEvent(BrainCloudClient *client) : _client(client){};

void BrainCloudEvent::sendEvent(const FString &toPlayerId, const FString &eventType, const FString &jsonEventData, IServerCallback *callback)
{
	// See IEventService on the server to make sure these parameter names are in sync
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	// implicitly fromId: _userId
	message->SetStringField(OperationParam::EventServiceSendToId.getValue(), toPlayerId);
	message->SetStringField(OperationParam::EventServiceSendEventType.getValue(), eventType);
	message->SetObjectField(OperationParam::EventServiceSendEventData.getValue(), JsonUtil::jsonStringToValue(jsonEventData));

	ServerCall *sc = new ServerCall(ServiceName::Event, ServiceOperation::Send, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudEvent::updateIncomingEventData(const FString &evId, const FString &jsonEventData, IServerCallback *callback)
{
	// See IEventService on the server to make sure these parameter names are in sync
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

	message->SetStringField(OperationParam::EvId.getValue(), evId);
	message->SetObjectField(OperationParam::EventServiceUpdateEventDataData.getValue(), JsonUtil::jsonStringToValue(jsonEventData));

	ServerCall *sc = new ServerCall(ServiceName::Event, ServiceOperation::UpdateEventData, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudEvent::deleteIncomingEvent(const FString &evId, IServerCallback *callback)
{
	// See IEventService on the server to make sure these parameter names are in sync
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::EvId.getValue(), evId);

	ServerCall *sc = new ServerCall(ServiceName::Event, ServiceOperation::DeleteIncoming, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudEvent::getEvents(IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	ServerCall *sc = new ServerCall(ServiceName::Event, ServiceOperation::GetEvents, message, callback);
	_client->sendRequest(sc);
}
