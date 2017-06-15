// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BCPlaybackStreamProxy.generated.h"

UCLASS(MinimalAPI)
class UBCPlaybackStreamProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
    GENERATED_BODY()

public:
    UBCPlaybackStreamProxy(const FObjectInitializer& ObjectInitializer);

    /**
    * Starts a stream
    *
    * Service Name - PlaybackStream
    * Service Operation - StartStream
    *
    * Param - targetPlayerId The player to start a stream with
    * Param - includeSharedData Whether to include shared data in the stream
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Playback Stream")
        static UBCPlaybackStreamProxy* StartStream(const FString& targetPlayerId, bool includeSharedData);

    /**
    * Reads a stream
    *
    * Service Name - PlaybackStream
    * Service Operation - ReadStream
    *
    * Param - playbackStreamId Identifies the stream to read
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Playback Stream")
        static UBCPlaybackStreamProxy* ReadStream(const FString& playbackStreamId);

    /**
    * Ends a stream
    *
    * Service Name - PlaybackStream
    * Service Operation - EndStream
    *
    * Param - playbackStreamId Identifies the stream to read
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Playback Stream")
        static UBCPlaybackStreamProxy* EndStream(const FString& playbackStreamId);

    /**
    * Deletes a stream
    *
    * Service Name - PlaybackStream
    * Service Operation - DeleteStream
    *
    * Param - playbackStreamId Identifies the stream to delete
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Playback Stream")
        static UBCPlaybackStreamProxy* DeleteStream(const FString& playbackStreamId);

    /**
    * Adds a stream event
    *
    * Service Name - PlaybackStream
    * Service Operation - AddEvent
    *
    * Param - playbackStreamId Identifies the stream to read
    * Param - jsonEventData Describes the event
    * Param - jsonSummary Current summary data as of this event
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Playback Stream")
        static UBCPlaybackStreamProxy* AddEvent(const FString& playbackStreamId, const FString& jsonEventData, const FString& jsonSummary);

    /**
    * @deprecated Use GetRecentStreamsForInitiatingPlayer instead - removal after September 1 2017
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Playback Stream")
        static UBCPlaybackStreamProxy* GetStreamSummariesForInitiatingPlayer(const FString& targetPlayerId);

    /**
    * @deprecated Use GetRecentStreamsForTargetPlayer instead - removal after September 1 2017
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Playback Stream")
        static UBCPlaybackStreamProxy* GetStreamSummariesForTargetPlayer(const FString& targetPlayerId);

	/**
	* Gets recent stream summaries for initiating player
	*
	* Service Name - PlaybackStream
	* Service Operation - GetRecentStreamsForInitiatingPlayer
	*
	* Param - initiatingPlayerId The player that started the stream
	* Param - maxNumStreams The max number of streams to query
	* Param - callback The callback.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Playback Stream")
		static UBCPlaybackStreamProxy* GetRecentStreamsForInitiatingPlayer(const FString& initiatingPlayerId, int32 maxNumStreams);

	/**
	* Gets recent stream summaries for target player
	*
	* Service Name - PlaybackStream
	* Service Operation - GetRecentStreamsForTargetPlayer
	*
	* Param - targetPlayerId The player that was target of the stream
	* Param - maxNumStreams The max number of streams to query
	* Param - callback The callback.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Playback Stream")
		static UBCPlaybackStreamProxy* GetRecentStreamsForTargetPlayer(const FString& targetPlayerId, int32 maxNumStreams);


    //Response delegates
    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnFailure;

protected:
    // IServerCallback interface
    void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
    void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
    // End of IServerCallback interface
};
