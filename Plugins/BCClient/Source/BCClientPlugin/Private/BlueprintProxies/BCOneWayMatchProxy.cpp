// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCOneWayMatchProxy.h"

UBCOneWayMatchProxy::UBCOneWayMatchProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCOneWayMatchProxy* UBCOneWayMatchProxy::StartMatch(const FString& otherPlayerId, int32 rangeDelta)
{
    UBCOneWayMatchProxy* Proxy = NewObject<UBCOneWayMatchProxy>();
    BrainCloudClient::getInstance()->getOneWayMatchService()->startMatch(otherPlayerId, rangeDelta, Proxy);
    return Proxy;
}

UBCOneWayMatchProxy* UBCOneWayMatchProxy::CancelMatch(const FString& playbackStreamId)
{
    UBCOneWayMatchProxy* Proxy = NewObject<UBCOneWayMatchProxy>();
    BrainCloudClient::getInstance()->getOneWayMatchService()->cancelMatch(playbackStreamId, Proxy);
    return Proxy;
}

UBCOneWayMatchProxy* UBCOneWayMatchProxy::CompleteMatch(const FString& playbackStreamId)
{
    UBCOneWayMatchProxy* Proxy = NewObject<UBCOneWayMatchProxy>();
    BrainCloudClient::getInstance()->getOneWayMatchService()->completeMatch(playbackStreamId, Proxy);
    return Proxy;
}

//callbacks
void UBCOneWayMatchProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCOneWayMatchProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

