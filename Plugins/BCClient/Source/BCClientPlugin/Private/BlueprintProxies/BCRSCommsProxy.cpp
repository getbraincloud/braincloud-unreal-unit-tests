// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudRSComms.h"
#include "BCRSCommsProxy.h"

UBCRSCommsProxy::UBCRSCommsProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UBCRSCommsProxy::BeginDestroy()
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

void UBCRSCommsProxy::SetRSComms(BrainCloudRSComms *in_comms)
{
    m_commsPtr = in_comms;
}

void UBCRSCommsProxy::WebSocket_OnClose()
{
    m_commsPtr->webSocket_OnClose();
}

void UBCRSCommsProxy::Websocket_OnOpen()
{
    m_commsPtr->websocket_OnOpen();
}

void UBCRSCommsProxy::WebSocket_OnMessage(const FString &in_data)
{
    m_commsPtr->webSocket_OnMessage(in_data);
}

void UBCRSCommsProxy::WebSocket_OnError(const FString &in_error)
{
    m_commsPtr->webSocket_OnError(in_error);
}
