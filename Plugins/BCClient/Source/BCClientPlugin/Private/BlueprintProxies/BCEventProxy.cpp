// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCEventProxy.h"

UBCEventProxy::UBCEventProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCEventProxy* UBCEventProxy::SendEvent(FString toPlayerId, FString eventType, FString jsonEventData, bool recordLocally)
{
    UBCEventProxy* Proxy = NewObject<UBCEventProxy>();
    BrainCloudClient::getInstance()->getEventService()->sendEvent(toPlayerId, eventType, jsonEventData, recordLocally, Proxy);
    return Proxy;
}

UBCEventProxy* UBCEventProxy::UpdateIncomingEventData(FString fromPlayerId, int32 eventId, FString jsonEventData)
{
    UBCEventProxy* Proxy = NewObject<UBCEventProxy>();
    BrainCloudClient::getInstance()->getEventService()->updateIncomingEventData(fromPlayerId, eventId, jsonEventData, Proxy);
    return Proxy;
}

UBCEventProxy* UBCEventProxy::DeleteIncomingEvent(FString fromPlayerId, int32 eventId)
{
    UBCEventProxy* Proxy = NewObject<UBCEventProxy>();
    BrainCloudClient::getInstance()->getEventService()->deleteIncomingEvent(fromPlayerId, eventId, Proxy);
    return Proxy;
}

UBCEventProxy* UBCEventProxy::DeleteSentEvent(FString toPlayerId, int32 eventId)
{
    UBCEventProxy* Proxy = NewObject<UBCEventProxy>();
    BrainCloudClient::getInstance()->getEventService()->deleteSentEvent(toPlayerId, eventId, Proxy);
    return Proxy;
}

UBCEventProxy* UBCEventProxy::GetEvents(bool includeIncomingEvents, bool includeSentEvents)
{
    UBCEventProxy* Proxy = NewObject<UBCEventProxy>();
    BrainCloudClient::getInstance()->getEventService()->getEvents(includeIncomingEvents, includeSentEvents, Proxy);
    return Proxy;
}

//callbacks
void UBCEventProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
}

void UBCEventProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
}

