// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCEventProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCEventProxy::UBCEventProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCEventProxy *UBCEventProxy::SendEvent(UBrainCloudWrapper *brainCloudWrapper, const FString &toPlayerId, const FString &eventType, const FString &jsonEventData)
{
    UBCEventProxy *Proxy = NewObject<UBCEventProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getEventService()->sendEvent(toPlayerId, eventType, jsonEventData, Proxy);
    return Proxy;
}

UBCEventProxy *UBCEventProxy::UpdateIncomingEventData(UBrainCloudWrapper *brainCloudWrapper, const FString &evId, const FString &jsonEventData)
{
    UBCEventProxy *Proxy = NewObject<UBCEventProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getEventService()->updateIncomingEventData(evId, jsonEventData, Proxy);
    return Proxy;
}

UBCEventProxy *UBCEventProxy::DeleteIncomingEvent(UBrainCloudWrapper *brainCloudWrapper, const FString &evId)
{
    UBCEventProxy *Proxy = NewObject<UBCEventProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getEventService()->deleteIncomingEvent(evId, Proxy);
    return Proxy;
}

UBCEventProxy *UBCEventProxy::GetEvents(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCEventProxy *Proxy = NewObject<UBCEventProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getEventService()->getEvents(Proxy);
    return Proxy;
}
