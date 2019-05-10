// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCRelayProxy.h"
	
UBCRelayProxy::UBCRelayProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

int64 UBCRelayProxy::Ping(UBrainCloudWrapper *brainCloudWrapper)
{
    return UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->ping();
}

uint8 UBCRelayProxy::NetId(UBrainCloudWrapper *brainCloudWrapper)
{
    return UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->netId();
}

UBCRelayProxy *UBCRelayProxy::Connect(UBrainCloudWrapper *brainCloudWrapper, BCRelayConnectionType in_connectionType, const FString &in_connectOptionsJson)
{
	UBCRelayProxy *Proxy = NewObject<UBCRelayProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->connect(in_connectionType, in_connectOptionsJson, Proxy);
	return Proxy;
}

void UBCRelayProxy::Disconnect(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->disconnect();
}

void UBCRelayProxy::DeregisterDataCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->deregisterDataCallback();
}

void UBCRelayProxy::Send(UBrainCloudWrapper *brainCloudWrapper, TArray<uint8> in_message, const uint8 in_target, bool in_reliable/* = true*/, bool in_ordered/* = true*/, int in_channel/* = 0*/)
{
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->send(in_message, in_target, in_reliable, in_ordered, in_channel);
}

void UBCRelayProxy::SetPingInterval(UBrainCloudWrapper *brainCloudWrapper, float in_value)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->setPingInterval(in_value);
}


