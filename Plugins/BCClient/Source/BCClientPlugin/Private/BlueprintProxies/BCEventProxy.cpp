// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloud.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCEventProxy.h"

UBCEventProxy::UBCEventProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCEventProxy* UBCEventProxy::SendEvent(ABrainCloud *brainCloud, const FString& toPlayerId, const FString& eventType, const FString& jsonEventData)
{
    UBCEventProxy* Proxy = NewObject<UBCEventProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getEventService()->sendEvent(toPlayerId, eventType, jsonEventData, Proxy);
    return Proxy;
}

UBCEventProxy* UBCEventProxy::UpdateIncomingEventData(ABrainCloud *brainCloud, const FString& evId, const FString& jsonEventData)
{
    UBCEventProxy* Proxy = NewObject<UBCEventProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getEventService()->updateIncomingEventData(evId, jsonEventData, Proxy);
    return Proxy;
}

UBCEventProxy* UBCEventProxy::DeleteIncomingEvent(ABrainCloud *brainCloud, const FString& evId)
{
    UBCEventProxy* Proxy = NewObject<UBCEventProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getEventService()->deleteIncomingEvent(evId, Proxy);
    return Proxy;
}

UBCEventProxy* UBCEventProxy::GetEvents(ABrainCloud *brainCloud)
{
    UBCEventProxy* Proxy = NewObject<UBCEventProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getEventService()->getEvents(Proxy);
    return Proxy;
}

//callbacks
void UBCEventProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCEventProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

