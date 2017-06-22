// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCEventProxy.h"

UBCEventProxy::UBCEventProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCEventProxy* UBCEventProxy::SendEvent(const FString& toPlayerId, const FString& eventType, const FString& jsonEventData)
{
    UBCEventProxy* Proxy = NewObject<UBCEventProxy>();
    BrainCloudClient::getInstance()->getEventService()->sendEvent(toPlayerId, eventType, jsonEventData, Proxy);
    return Proxy;
}

UBCEventProxy* UBCEventProxy::UpdateIncomingEventData(const FString& evId, const FString& jsonEventData)
{
    UBCEventProxy* Proxy = NewObject<UBCEventProxy>();
    BrainCloudClient::getInstance()->getEventService()->updateIncomingEventData(evId, jsonEventData, Proxy);
    return Proxy;
}

UBCEventProxy* UBCEventProxy::DeleteIncomingEvent(const FString& evId)
{
    UBCEventProxy* Proxy = NewObject<UBCEventProxy>();
    BrainCloudClient::getInstance()->getEventService()->deleteIncomingEvent(evId, Proxy);
    return Proxy;
}

UBCEventProxy* UBCEventProxy::GetEvents()
{
    UBCEventProxy* Proxy = NewObject<UBCEventProxy>();
    BrainCloudClient::getInstance()->getEventService()->getEvents(Proxy);
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
