// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCRestRewardCallbackProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCRestRewardCallbackProxy::UBCRestRewardCallbackProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCRestRewardCallbackProxy *UBCRestRewardCallbackProxy::RegisterRewardCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCRestRewardCallbackProxy *Proxy = NewObject<UBCRestRewardCallbackProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getBCClient()->registerRewardCallback(Proxy);
	return Proxy;
}

void UBCRestRewardCallbackProxy::DeregisterRewardCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getBCClient()->deregisterRewardCallback();
}
