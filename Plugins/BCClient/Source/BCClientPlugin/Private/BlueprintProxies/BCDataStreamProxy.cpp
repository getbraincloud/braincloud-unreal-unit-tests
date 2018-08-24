// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCDataStreamProxy.h"

UBCDataStreamProxy::UBCDataStreamProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCDataStreamProxy* UBCDataStreamProxy::CustomPageEvent(UBrainCloudWrapper *brainCloudWrapper, const FString& eventName, const FString& jsonEventProperties)
{
    UBCDataStreamProxy* Proxy = NewObject<UBCDataStreamProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getDataStreamService()->customPageEvent(eventName, jsonEventProperties, Proxy);
    return Proxy;
}

UBCDataStreamProxy* UBCDataStreamProxy::CustomScreenEvent(UBrainCloudWrapper *brainCloudWrapper, const FString& eventName, const FString& jsonEventProperties)
{
    UBCDataStreamProxy* Proxy = NewObject<UBCDataStreamProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getDataStreamService()->customScreenEvent(eventName, jsonEventProperties, Proxy);
    return Proxy;
}

UBCDataStreamProxy* UBCDataStreamProxy::CustomTrackEvent(UBrainCloudWrapper *brainCloudWrapper, const FString& eventName, const FString& jsonEventProperties)
{
    UBCDataStreamProxy* Proxy = NewObject<UBCDataStreamProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getDataStreamService()->customTrackEvent(eventName, jsonEventProperties, Proxy);
    return Proxy;
}
