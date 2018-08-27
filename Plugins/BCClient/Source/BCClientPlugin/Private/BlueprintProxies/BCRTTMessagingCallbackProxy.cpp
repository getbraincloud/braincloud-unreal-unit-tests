// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCRTTMessagingCallbackProxy.h"

UBCRTTMessagingCallbackProxy::UBCRTTMessagingCallbackProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCRTTMessagingCallbackProxy *UBCRTTMessagingCallbackProxy::RegisterRTTMessagingCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCRTTMessagingCallbackProxy *Proxy = NewObject<UBCRTTMessagingCallbackProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getBCClient()->registerRTTMessagingCallback(Proxy);
	return Proxy;
}

void UBCRTTMessagingCallbackProxy::DeregisterRTTMessagingCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getBCClient()->deregisterRTTMessagingCallback();
}