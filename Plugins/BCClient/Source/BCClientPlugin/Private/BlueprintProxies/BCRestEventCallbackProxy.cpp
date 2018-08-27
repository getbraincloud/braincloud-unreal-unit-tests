// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCRestEventCallbackProxy.h"

UBCRestEventCallbackProxy::UBCRestEventCallbackProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCRestEventCallbackProxy *UBCRestEventCallbackProxy::RegisterEventCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCRestEventCallbackProxy *Proxy = NewObject<UBCRestEventCallbackProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getBCClient()->registerEventCallback(Proxy);
	return Proxy;
}

void UBCRestEventCallbackProxy::DeregisterEventCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getBCClient()->deregisterEventCallback();
}
