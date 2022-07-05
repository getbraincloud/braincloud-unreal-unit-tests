// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCTimeProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCTimeProxy::UBCTimeProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCTimeProxy *UBCTimeProxy::ReadServerTime(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCTimeProxy *Proxy = NewObject<UBCTimeProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getTimeService()->readServerTime(Proxy);
    return Proxy;
}
