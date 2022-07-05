// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCRelayProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "ServerCall.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
	
UBCRelayProxy::UBCRelayProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCRelayProxy *UBCRelayProxy::Connect(UBrainCloudWrapper *brainCloudWrapper, BCRelayConnectionType in_connectionType, const FString &host, int port, const FString &passcode, const FString &lobbyId)
{
	UBCRelayProxy *Proxy = NewObject<UBCRelayProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->connect(in_connectionType, host, port, passcode, lobbyId, Proxy);
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

int64 UBCRelayProxy::GetPing(UBrainCloudWrapper *brainCloudWrapper)
{
    return UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->getPing();
}

const FString &UBCRelayProxy::GetOwnerProfileId(UBrainCloudWrapper *brainCloudWrapper)
{
    return UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->getOwnerProfileId();
}

const FString &UBCRelayProxy::GetOwnerCxId(UBrainCloudWrapper *brainCloudWrapper)
{
    return UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->getOwnerCxId();
}

const FString &UBCRelayProxy::GetProfileIdForNetId(UBrainCloudWrapper *brainCloudWrapper, int in_netId)
{
    return UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->getProfileIdForNetId(in_netId);
}

int UBCRelayProxy::GetNetIdForProfileId(UBrainCloudWrapper *brainCloudWrapper, const FString &in_profileId)
{
    return UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->getNetIdForProfileId(in_profileId);
}

const FString &UBCRelayProxy::GetCxIdForNetId(UBrainCloudWrapper *brainCloudWrapper, int in_netId)
{
    return UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->getCxIdForNetId(in_netId);
}

int UBCRelayProxy::GetNetIdForCxId(UBrainCloudWrapper *brainCloudWrapper, const FString &in_profileId)
{
    return UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->getNetIdForCxId(in_profileId);
}

void UBCRelayProxy::DeregisterRelayCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->deregisterRelayCallback();
}

void UBCRelayProxy::DeregisterSystemCallback(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->deregisterSystemCallback();
}

void UBCRelayProxy::Send(UBrainCloudWrapper *brainCloudWrapper, const TArray<uint8> &data, int toNetId, bool reliable, bool ordered, BCRelayChannel channel)
{
	uint64 to_netId = (uint64)toNetId;
	if (toNetId == -1) 
		to_netId = BrainCloudRelay::TO_ALL_PLAYERS;
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->send(data, to_netId, reliable, ordered, channel);
}

// void UBCRelayProxy::SendToPlayers(UBrainCloudWrapper *brainCloudWrapper, const TArray<uint8> &data, uint32 in_playerMaskLow, uint32 in_playerMaskHi, bool reliable, bool ordered, BCRelayChannel channel)
// {
//     uint64 playerMask = (uint64)in_playerMaskLow | ((uint64)in_playerMaskHi << 32);
//     UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->sendToPlayers(data, playerMask, reliable, ordered, channel);
// }

void UBCRelayProxy::SendToAll(UBrainCloudWrapper *brainCloudWrapper, const TArray<uint8> &data, bool reliable, bool ordered, BCRelayChannel channel)
{
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRelayService()->sendToAll(data, reliable, ordered, channel);
}
