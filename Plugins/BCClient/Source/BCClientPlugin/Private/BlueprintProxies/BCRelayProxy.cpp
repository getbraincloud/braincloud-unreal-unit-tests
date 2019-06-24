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
	_bIsOneResponse = false;
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

bool UBCRelayProxy::IsConnected(UBrainCloudWrapper *brainCloudWrapper)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->isConnected();
}

void UBCRelayProxy::DeregisterDataCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->deregisterDataCallback();
}

void UBCRelayProxy::Send(UBrainCloudWrapper *brainCloudWrapper, const TArray<uint8> &in_message, const uint8 in_netId, bool in_reliable/* = true*/, bool in_ordered/* = true*/, int in_channel/* = 0*/)
{
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->send(in_message, in_netId, in_reliable, in_ordered, in_channel);
}

void UBCRelayProxy::SetPingInterval(UBrainCloudWrapper *brainCloudWrapper, float in_value)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->setPingInterval(in_value);
}

FString UBCRelayProxy::BCBytesToString(const TArray<uint8>& in_data)
{
	FString parsedMessage = BrainCloudRelay::BCBytesToString(in_data.GetData(), in_data.Num());
	return parsedMessage;
}

TArray<uint8> UBCRelayProxy::BCStringToBytes(const FString &in_string)
{
	TArray<uint8> data;
	data.AddUninitialized(in_string.Len());
	BrainCloudRelay::BCStringToBytes(in_string, data.GetData(), in_string.Len());

	return data;
}

