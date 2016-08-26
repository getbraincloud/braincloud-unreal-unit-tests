// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCPlaybackStreamProxy.h"

UBCPlaybackStreamProxy::UBCPlaybackStreamProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::StartStream(const FString& targetPlayerId, bool includeSharedData)
{
    UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
    BrainCloudClient::getInstance()->getPlaybackStreamService()->startStream(targetPlayerId, includeSharedData, Proxy);
    return Proxy;
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::ReadStream(const FString& playbackStreamId)
{
    UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
    BrainCloudClient::getInstance()->getPlaybackStreamService()->readStream(playbackStreamId, Proxy);
    return Proxy;
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::EndStream(const FString& playbackStreamId)
{
    UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
    BrainCloudClient::getInstance()->getPlaybackStreamService()->endStream(playbackStreamId, Proxy);
    return Proxy;
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::DeleteStream(const FString& playbackStreamId)
{
    UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
    BrainCloudClient::getInstance()->getPlaybackStreamService()->deleteStream(playbackStreamId, Proxy);
    return Proxy;
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::AddEvent(const FString& playbackStreamId, const FString& jsonEventData, const FString& jsonSummary)

{
    UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
    BrainCloudClient::getInstance()->getPlaybackStreamService()->addEvent(playbackStreamId, jsonEventData, jsonSummary, Proxy);
    return Proxy;
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::GetStreamSummariesForInitiatingPlayer(const FString& targetPlayerId)
{
    UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
    BrainCloudClient::getInstance()->getPlaybackStreamService()->getStreamSummariesForInitiatingPlayer(targetPlayerId, Proxy);
    return Proxy;
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::GetStreamSummariesForTargetPlayer(const FString& targetPlayerId)
{
    UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
    BrainCloudClient::getInstance()->getPlaybackStreamService()->getStreamSummariesForTargetPlayer(targetPlayerId, Proxy);
    return Proxy;
}

//callbacks
void UBCPlaybackStreamProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
}

void UBCPlaybackStreamProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
}

