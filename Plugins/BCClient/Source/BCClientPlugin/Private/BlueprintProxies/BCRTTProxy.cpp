// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCRTTProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCRTTProxy::UBCRTTProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
	_bCleanupAfterFirstResponse = false;
}

UBCRTTProxy *UBCRTTProxy::EnableRTT(UBrainCloudWrapper *brainCloudWrapper, BCRTTConnectionType in_type)
{
	UBCRTTProxy *Proxy = NewObject<UBCRTTProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRTTService()->enableRTT(in_type, Proxy);
	return Proxy;
}

void UBCRTTProxy::DisableRTT(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRTTService()->disableRTT();
}

bool UBCRTTProxy::IsRTTEnabled(UBrainCloudWrapper *brainCloudWrapper)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRTTService()->isRTTEnabled();
}

void UBCRTTProxy::SetRTTHeartBeatSeconds(UBrainCloudWrapper *brainCloudWrapper, int32 in_value)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRTTService()->setRTTHeartBeatSeconds(in_value);
}

void UBCRTTProxy::DeregisterAllRTTCallbacks(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRTTService()->deregisterAllRTTCallbacks();
}

const FString &UBCRTTProxy::GetRTTConnectionId(UBrainCloudWrapper *brainCloudWrapper)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRTTService()->getRTTConnectionId();
}
