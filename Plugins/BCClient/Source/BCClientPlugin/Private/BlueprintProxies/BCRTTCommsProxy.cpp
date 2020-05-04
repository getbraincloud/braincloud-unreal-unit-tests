// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCRTTCommsProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudRTTComms.h"

UBCRTTCommsProxy::UBCRTTCommsProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UBCRTTCommsProxy::BeginDestroy()
{
    Super::BeginDestroy();
    if (!this->IsValidLowLevel())
    {
        return;
    }
    this->RemoveFromRoot();
    this->ConditionalBeginDestroy();
    m_commsPtr = nullptr;
}

void UBCRTTCommsProxy::SetRTTComms(BrainCloudRTTComms *in_comms)
{
    m_commsPtr = in_comms;
}

void UBCRTTCommsProxy::WebSocket_OnClose()
{
    m_commsPtr->webSocket_OnClose();
}

void UBCRTTCommsProxy::Websocket_OnOpen()
{
    m_commsPtr->websocket_OnOpen();
}

void UBCRTTCommsProxy::WebSocket_OnMessage(TArray<uint8> in_data)
{
    m_commsPtr->webSocket_OnMessage(in_data);
}

void UBCRTTCommsProxy::WebSocket_OnError(const FString &in_error)
{
    m_commsPtr->webSocket_OnError(in_error);
}
