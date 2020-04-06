// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCRTTEventCallbackProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCRTTEventCallbackProxy::UBCRTTEventCallbackProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCRTTEventCallbackProxy *UBCRTTEventCallbackProxy::RegisterRTTEventCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCRTTEventCallbackProxy *Proxy = NewObject<UBCRTTEventCallbackProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRTTService()->registerRTTEventCallback(Proxy);
	return Proxy;
}

void UBCRTTEventCallbackProxy::DeregisterRTTEventCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRTTService()->deregisterRTTEventCallback();
}
