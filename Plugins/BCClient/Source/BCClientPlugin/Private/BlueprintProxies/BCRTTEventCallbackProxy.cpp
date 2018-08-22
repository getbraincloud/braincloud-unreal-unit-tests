// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCRTTEventCallbackProxy.h"

UBCRTTEventCallbackProxy::UBCRTTEventCallbackProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCRTTEventCallbackProxy *UBCRTTEventCallbackProxy::RegisterRTTEventCallbackSimple(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCRTTEventCallbackProxy *Proxy = NewObject<UBCRTTEventCallbackProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getBCClient()->registerRTTEventCallback(Proxy);
	return Proxy;
}
