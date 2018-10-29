// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCRestFileCallbackProxy.h"

UBCRestFileCallbackProxy::UBCRestFileCallbackProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCRestFileCallbackProxy *UBCRestFileCallbackProxy::RegisterFileCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCRestFileCallbackProxy *Proxy = NewObject<UBCRestFileCallbackProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getBCClient()->registerFileUploadCallback(Proxy);
	return Proxy;
}

void UBCRestFileCallbackProxy::DeregisterFileCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getBCClient()->deregisterFileUploadCallback();
}
