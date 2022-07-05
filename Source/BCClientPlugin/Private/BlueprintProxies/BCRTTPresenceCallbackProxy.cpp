// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCRTTPresenceCallbackProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCRTTPresenceCallbackProxy::UBCRTTPresenceCallbackProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCRTTPresenceCallbackProxy *UBCRTTPresenceCallbackProxy::RegisterRTTPresenceCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCRTTPresenceCallbackProxy *Proxy = NewObject<UBCRTTPresenceCallbackProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRTTService()->registerRTTPresenceCallback(Proxy);
	return Proxy;
}

void UBCRTTPresenceCallbackProxy::DeregisterRTTPresenceCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRTTService()->deregisterRTTPresenceCallback();
}
