// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BCOneWayMatchProxy.generated.h"

class ABrainCloud;

UCLASS(MinimalAPI)
class UBCOneWayMatchProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
    GENERATED_BODY()

public:
    UBCOneWayMatchProxy(const FObjectInitializer& ObjectInitializer);

    /**
    * Starts a match
    *
    * Service Name - OneWayMatch
    * Service Operation - StartMatch
    *
    * Param - otherPlayerId The player to start a match with
    * Param - rangeDelta The range delta used for the initial match search
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|One Way Match")
        static UBCOneWayMatchProxy* StartMatch(ABrainCloud *brainCloud, const FString& otherPlayerId, int32 rangeDelta);

    /**
    * Cancels a match
    *
    * Service Name - OneWayMatch
    * Service Operation - CancelMatch
    *
    * Param - playbackStreamId The playback stream id returned in the start match
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|One Way Match")
        static UBCOneWayMatchProxy* CancelMatch(ABrainCloud *brainCloud, const FString& playbackStreamId);

    /**
    * Completes a match
    *
    * Service Name - OneWayMatch
    * Service Operation - CompleteMatch
    *
    * Param - playbackStreamId The playback stream id returned in the initial start match
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|One Way Match")
        static UBCOneWayMatchProxy* CompleteMatch(ABrainCloud *brainCloud, const FString& playbackStreamId);

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
