// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCRTTLobbyCallbackProxy.h"

UBCRTTLobbyCallbackProxy::UBCRTTLobbyCallbackProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCRTTLobbyCallbackProxy *UBCRTTLobbyCallbackProxy::RegisterRTTLobbyCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCRTTLobbyCallbackProxy *Proxy = NewObject<UBCRTTLobbyCallbackProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRTTService()->registerRTTLobbyCallback(Proxy);
	return Proxy;
}

void UBCRTTLobbyCallbackProxy::DeregisterRTTLobbyCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRTTService()->deregisterRTTLobbyCallback();
}