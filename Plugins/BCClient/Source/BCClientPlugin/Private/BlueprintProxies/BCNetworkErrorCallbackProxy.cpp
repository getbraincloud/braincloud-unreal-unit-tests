// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCNetworkErrorCallbackProxy.h"

UBCNetworkErrorCallbackProxy::UBCNetworkErrorCallbackProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCNetworkErrorCallbackProxy *UBCNetworkErrorCallbackProxy::RegisterNetworkErrorCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCNetworkErrorCallbackProxy *Proxy = NewObject<UBCNetworkErrorCallbackProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getBCClient()->registerNetworkErrorCallback(Proxy);
	return Proxy;
}

void UBCNetworkErrorCallbackProxy::DeregisterNetworkErrorCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getBCClient()->deregisterNetworkErrorCallback();
}
