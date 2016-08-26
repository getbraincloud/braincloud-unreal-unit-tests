// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudEvent.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudEvent::BrainCloudEvent(BrainCloudClient* client) : _client(client) {};

void BrainCloudEvent::sendEvent(const FString& toPlayerId, const FString& eventType, const FString& jsonEventData, bool recordLocally, IServerCallback* callback)
{
    // See IEventService on the server to make sure these parameter names are in sync
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    // implicitly fromId: _userId
    message->SetStringField(OperationParam::EventServiceSendToId.getValue(), toPlayerId);
    message->SetStringField(OperationParam::EventServiceSendEventType.getValue(), eventType);
    message->SetObjectField(OperationParam::EventServiceSendEventData.getValue(), JsonUtil::jsonStringToValue(jsonEventData));
    message->SetBoolField(OperationParam::EventServiceSendRecordLocally.getValue(), recordLocally);

    ServerCall * sc = new ServerCall(ServiceName::Event, ServiceOperation::Send, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudEvent::updateIncomingEventData(const FString& fromPlayerId, uint64 eventId, const FString& jsonEventData, IServerCallback* callback)
{
    // See IEventService on the server to make sure these parameter names are in sync
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    // implicitly fromId: _userId
    message->SetStringField(OperationParam::EventServiceUpdateEventDataFromId.getValue(), fromPlayerId);
    message->SetNumberField(OperationParam::EventServiceUpdateEventDataEventId.getValue(), eventId);
    message->SetObjectField(OperationParam::EventServiceUpdateEventDataData.getValue(), JsonUtil::jsonStringToValue(jsonEventData));

    ServerCall * sc = new ServerCall(ServiceName::Event, ServiceOperation::UpdateEventData, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudEvent::deleteIncomingEvent(const FString& fromPlayerId, uint64 eventId, IServerCallback* callback)
{
    // See IEventService on the server to make sure these parameter names are in sync
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::EventServiceDeleteIncomingFromId.getValue(), fromPlayerId);
    message->SetNumberField(OperationParam::EventServiceDeleteIncomingEventId.getValue(), eventId);

    ServerCall * sc = new ServerCall(ServiceName::Event, ServiceOperation::DeleteIncoming, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudEvent::deleteSentEvent(const FString& toPlayerId, uint64 eventId, IServerCallback* callback)
{
    // See IEventService on the server to make sure these parameter names are in sync
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::EventServiceDeleteSentToId.getValue(), toPlayerId);
    message->SetNumberField(OperationParam::EventServiceDeleteSentEventId.getValue(), eventId);

    ServerCall * sc = new ServerCall(ServiceName::Event, ServiceOperation::DeleteSent, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudEvent::getEvents(bool includeIncomingEvents, bool includeSentEvents, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetBoolField(OperationParam::EventServiceIncludeIncomingEvents.getValue(), includeIncomingEvents);
    message->SetBoolField(OperationParam::EventServiceIncludeSentEvents.getValue(), includeSentEvents);

    ServerCall * sc = new ServerCall(ServiceName::Event, ServiceOperation::GetEvents, message, callback);
    _client->sendRequest(sc);
}