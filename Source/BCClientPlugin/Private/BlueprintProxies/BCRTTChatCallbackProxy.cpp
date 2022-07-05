// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCRTTChatCallbackProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCRTTChatCallbackProxy::UBCRTTChatCallbackProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCRTTChatCallbackProxy *UBCRTTChatCallbackProxy::RegisterRTTChatCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCRTTChatCallbackProxy *Proxy = NewObject<UBCRTTChatCallbackProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRTTService()->registerRTTChatCallback(Proxy);
	return Proxy;
}

void UBCRTTChatCallbackProxy::DeregisterRTTChatCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRTTService()->deregisterRTTChatCallback();
}
