// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCGlobalErrorCallbackProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCGlobalErrorCallbackProxy::UBCGlobalErrorCallbackProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCGlobalErrorCallbackProxy *UBCGlobalErrorCallbackProxy::RegisterGlobalErrorCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCGlobalErrorCallbackProxy *Proxy = NewObject<UBCGlobalErrorCallbackProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getBCClient()->registerGlobalErrorCallback(Proxy);
	return Proxy;
}

void UBCGlobalErrorCallbackProxy::DeregisterGlobalErrorCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getBCClient()->deregisterGlobalErrorCallback();
}
