// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCRelayDataCallbackProxy.h"

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
