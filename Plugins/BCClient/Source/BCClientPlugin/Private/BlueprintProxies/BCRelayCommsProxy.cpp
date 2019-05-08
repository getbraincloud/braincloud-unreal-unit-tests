// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudRelayComms.h"
#include "BCRelayCommsProxy.h"

UBCRelayCommsProxy::UBCRelayCommsProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UBCRelayCommsProxy::BeginDestroy()
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

void UBCRelayCommsProxy::SetRelayComms(BrainCloudRelayComms *in_comms)
{
    m_commsPtr = in_comms;
}

void UBCRelayCommsProxy::WebSocket_OnClose()
{
    m_commsPtr->webSocket_OnClose();
}

void UBCRelayCommsProxy::Websocket_OnOpen()
{
    m_commsPtr->websocket_OnOpen();
}

void UBCRelayCommsProxy::WebSocket_OnMessage(const FString &in_data)
{
    m_commsPtr->webSocket_OnMessage(in_data);
}

void UBCRelayCommsProxy::WebSocket_OnError(const FString &in_error)
{
    m_commsPtr->webSocket_OnError(in_error);
}
