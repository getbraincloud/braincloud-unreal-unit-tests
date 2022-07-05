// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCRestFileCallbackProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

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
