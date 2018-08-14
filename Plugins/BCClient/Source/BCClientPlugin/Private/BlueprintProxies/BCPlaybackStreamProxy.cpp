// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloudActor.h"
#include "BCWrapperProxy.h"
#include "BCPlaybackStreamProxy.h"
#include "BrainCloudWrapper.h"

UBCPlaybackStreamProxy::UBCPlaybackStreamProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::StartStream(UBrainCloudWrapper *brainCloudWrapper, const FString& targetPlayerId, bool includeSharedData)
{
    UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlaybackStreamService()->startStream(targetPlayerId, includeSharedData, Proxy);
    return Proxy;
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::ReadStream(UBrainCloudWrapper *brainCloudWrapper, const FString& playbackStreamId)
{
    UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlaybackStreamService()->readStream(playbackStreamId, Proxy);
    return Proxy;
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::EndStream(UBrainCloudWrapper *brainCloudWrapper, const FString& playbackStreamId)
{
    UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlaybackStreamService()->endStream(playbackStreamId, Proxy);
    return Proxy;
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::DeleteStream(UBrainCloudWrapper *brainCloudWrapper, const FString& playbackStreamId)
{
    UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlaybackStreamService()->deleteStream(playbackStreamId, Proxy);
    return Proxy;
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::AddEvent(UBrainCloudWrapper *brainCloudWrapper, const FString& playbackStreamId, const FString& jsonEventData, const FString& jsonSummary)

{
    UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlaybackStreamService()->addEvent(playbackStreamId, jsonEventData, jsonSummary, Proxy);
    return Proxy;
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::GetStreamSummariesForInitiatingPlayer(UBrainCloudWrapper *brainCloudWrapper, const FString& targetPlayerId)
{
    UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlaybackStreamService()->getStreamSummariesForInitiatingPlayer(targetPlayerId, Proxy);
    return Proxy;
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::GetStreamSummariesForTargetPlayer(UBrainCloudWrapper *brainCloudWrapper, const FString& targetPlayerId)
{
    UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlaybackStreamService()->getStreamSummariesForTargetPlayer(targetPlayerId, Proxy);
    return Proxy;
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::GetRecentStreamsForInitiatingPlayer(UBrainCloudWrapper *brainCloudWrapper, const FString& targetPlayerId, int32 maxNumStreams)
{
	UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlaybackStreamService()->getRecentStreamsForInitiatingPlayer(targetPlayerId, maxNumStreams, Proxy);
	return Proxy;
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::GetRecentStreamsForTargetPlayer(UBrainCloudWrapper *brainCloudWrapper, const FString& targetPlayerId, int32 maxNumStreams)
{
	UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getPlaybackStreamService()->getRecentStreamsForTargetPlayer(targetPlayerId, maxNumStreams, Proxy);
	return Proxy;
}

//callbacks
void UBCPlaybackStreamProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCPlaybackStreamProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

