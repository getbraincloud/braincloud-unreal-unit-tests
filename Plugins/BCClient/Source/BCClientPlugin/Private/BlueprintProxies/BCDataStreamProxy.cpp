// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCDataStreamProxy.h"

UBCDataStreamProxy::UBCDataStreamProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCDataStreamProxy* UBCDataStreamProxy::CustomPageEvent(const FString& eventName, const FString& jsonEventProperties)
{
    UBCDataStreamProxy* Proxy = NewObject<UBCDataStreamProxy>();
    BrainCloudClient::getInstance()->getDataStreamService()->customPageEvent(eventName, jsonEventProperties, Proxy);
    return Proxy;
}

UBCDataStreamProxy* UBCDataStreamProxy::CustomScreenEvent(const FString& eventName, const FString& jsonEventProperties)
{
    UBCDataStreamProxy* Proxy = NewObject<UBCDataStreamProxy>();
    BrainCloudClient::getInstance()->getDataStreamService()->customScreenEvent(eventName, jsonEventProperties, Proxy);
    return Proxy;
}

UBCDataStreamProxy* UBCDataStreamProxy::CustomTrackEvent(const FString& eventName, const FString& jsonEventProperties)
{
    UBCDataStreamProxy* Proxy = NewObject<UBCDataStreamProxy>();
    BrainCloudClient::getInstance()->getDataStreamService()->customTrackEvent(eventName, jsonEventProperties, Proxy);
    return Proxy;
}

//callbacks
void UBCDataStreamProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
}

void UBCDataStreamProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
}

