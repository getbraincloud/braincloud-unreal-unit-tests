// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCOneWayMatchProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCOneWayMatchProxy::UBCOneWayMatchProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCOneWayMatchProxy *UBCOneWayMatchProxy::StartMatch(UBrainCloudWrapper *brainCloudWrapper, const FString &otherPlayerId, int32 rangeDelta)
{
    UBCOneWayMatchProxy *Proxy = NewObject<UBCOneWayMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getOneWayMatchService()->startMatch(otherPlayerId, rangeDelta, Proxy);
    return Proxy;
}

UBCOneWayMatchProxy *UBCOneWayMatchProxy::CancelMatch(UBrainCloudWrapper *brainCloudWrapper, const FString &playbackStreamId)
{
    UBCOneWayMatchProxy *Proxy = NewObject<UBCOneWayMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getOneWayMatchService()->cancelMatch(playbackStreamId, Proxy);
    return Proxy;
}

UBCOneWayMatchProxy *UBCOneWayMatchProxy::CompleteMatch(UBrainCloudWrapper *brainCloudWrapper, const FString &playbackStreamId)
{
    UBCOneWayMatchProxy *Proxy = NewObject<UBCOneWayMatchProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getOneWayMatchService()->completeMatch(playbackStreamId, Proxy);
    return Proxy;
}
