// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCRelayDataCallbackProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCRelayDataCallbackProxy::UBCRelayDataCallbackProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCRelayDataCallbackProxy *UBCRelayDataCallbackProxy::RegisterDataCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCRelayDataCallbackProxy *Proxy = NewObject<UBCRelayDataCallbackProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->registerDataCallback(Proxy);
	return Proxy;
}
