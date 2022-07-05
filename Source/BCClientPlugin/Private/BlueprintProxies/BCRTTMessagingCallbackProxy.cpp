// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCRTTMessagingCallbackProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCRTTMessagingCallbackProxy::UBCRTTMessagingCallbackProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCRTTMessagingCallbackProxy *UBCRTTMessagingCallbackProxy::RegisterRTTMessagingCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCRTTMessagingCallbackProxy *Proxy = NewObject<UBCRTTMessagingCallbackProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRTTService()->registerRTTMessagingCallback(Proxy);
	return Proxy;
}

void UBCRTTMessagingCallbackProxy::DeregisterRTTMessagingCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRTTService()->deregisterRTTMessagingCallback();
}