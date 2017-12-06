// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloud.h"
#include "BCWrapperProxy.h"
#include "BCPlaybackStreamProxy.h"
#include "BrainCloudWrapper.h"

UBCPlaybackStreamProxy::UBCPlaybackStreamProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::StartStream(ABrainCloud *brainCloud, const FString& targetPlayerId, bool includeSharedData)
{
    UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlaybackStreamService()->startStream(targetPlayerId, includeSharedData, Proxy);
    return Proxy;
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::ReadStream(ABrainCloud *brainCloud, const FString& playbackStreamId)
{
    UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlaybackStreamService()->readStream(playbackStreamId, Proxy);
    return Proxy;
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::EndStream(ABrainCloud *brainCloud, const FString& playbackStreamId)
{
    UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlaybackStreamService()->endStream(playbackStreamId, Proxy);
    return Proxy;
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::DeleteStream(ABrainCloud *brainCloud, const FString& playbackStreamId)
{
    UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlaybackStreamService()->deleteStream(playbackStreamId, Proxy);
    return Proxy;
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::AddEvent(ABrainCloud *brainCloud, const FString& playbackStreamId, const FString& jsonEventData, const FString& jsonSummary)

{
    UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlaybackStreamService()->addEvent(playbackStreamId, jsonEventData, jsonSummary, Proxy);
    return Proxy;
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::GetStreamSummariesForInitiatingPlayer(ABrainCloud *brainCloud, const FString& targetPlayerId)
{
    UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlaybackStreamService()->getStreamSummariesForInitiatingPlayer(targetPlayerId, Proxy);
    return Proxy;
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::GetStreamSummariesForTargetPlayer(ABrainCloud *brainCloud, const FString& targetPlayerId)
{
    UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlaybackStreamService()->getStreamSummariesForTargetPlayer(targetPlayerId, Proxy);
    return Proxy;
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::GetRecentStreamsForInitiatingPlayer(ABrainCloud *brainCloud, const FString& targetPlayerId, int32 maxNumStreams)
{
	UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlaybackStreamService()->getRecentStreamsForInitiatingPlayer(targetPlayerId, maxNumStreams, Proxy);
	return Proxy;
}

UBCPlaybackStreamProxy* UBCPlaybackStreamProxy::GetRecentStreamsForTargetPlayer(ABrainCloud *brainCloud, const FString& targetPlayerId, int32 maxNumStreams)
{
	UBCPlaybackStreamProxy* Proxy = NewObject<UBCPlaybackStreamProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getPlaybackStreamService()->getRecentStreamsForTargetPlayer(targetPlayerId, maxNumStreams, Proxy);
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

