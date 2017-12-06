// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloud.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCDataStreamProxy.h"

UBCDataStreamProxy::UBCDataStreamProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCDataStreamProxy* UBCDataStreamProxy::CustomPageEvent(ABrainCloud *brainCloud, const FString& eventName, const FString& jsonEventProperties)
{
    UBCDataStreamProxy* Proxy = NewObject<UBCDataStreamProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getDataStreamService()->customPageEvent(eventName, jsonEventProperties, Proxy);
    return Proxy;
}

UBCDataStreamProxy* UBCDataStreamProxy::CustomScreenEvent(ABrainCloud *brainCloud, const FString& eventName, const FString& jsonEventProperties)
{
    UBCDataStreamProxy* Proxy = NewObject<UBCDataStreamProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getDataStreamService()->customScreenEvent(eventName, jsonEventProperties, Proxy);
    return Proxy;
}

UBCDataStreamProxy* UBCDataStreamProxy::CustomTrackEvent(ABrainCloud *brainCloud, const FString& eventName, const FString& jsonEventProperties)
{
    UBCDataStreamProxy* Proxy = NewObject<UBCDataStreamProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getDataStreamService()->customTrackEvent(eventName, jsonEventProperties, Proxy);
    return Proxy;
}

//callbacks
void UBCDataStreamProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCDataStreamProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

