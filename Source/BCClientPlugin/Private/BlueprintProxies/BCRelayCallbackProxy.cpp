// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCRelayCallbackProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCRelayCallbackProxy::UBCRelayCallbackProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCRelayCallbackProxy *UBCRelayCallbackProxy::RegisterRelayCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCRelayCallbackProxy *Proxy = NewObject<UBCRelayCallbackProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->registerRelayCallback(Proxy);
	return Proxy;
}
