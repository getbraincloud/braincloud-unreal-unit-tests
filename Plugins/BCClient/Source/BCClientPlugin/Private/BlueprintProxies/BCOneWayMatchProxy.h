// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCOneWayMatchProxy.generated.h"

UCLASS(MinimalAPI)
class UBCOneWayMatchProxy : public UBCBlueprintCallProxyBase
{
  GENERATED_BODY()

public:
  UBCOneWayMatchProxy(const FObjectInitializer &ObjectInitializer);

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
  static UBCOneWayMatchProxy *StartMatch(UBrainCloudWrapper *brainCloudWrapper, const FString &otherPlayerId, int32 rangeDelta);

  /**
    * Cancels a match
    *
    * Service Name - OneWayMatch
    * Service Operation - CancelMatch
    *
    * Param - playbackStreamId The playback stream id returned in the start match
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|One Way Match")
  static UBCOneWayMatchProxy *CancelMatch(UBrainCloudWrapper *brainCloudWrapper, const FString &playbackStreamId);

  /**
    * Completes a match
    *
    * Service Name - OneWayMatch
    * Service Operation - CompleteMatch
    *
    * Param - playbackStreamId The playback stream id returned in the initial start match
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|One Way Match")
  static UBCOneWayMatchProxy *CompleteMatch(UBrainCloudWrapper *brainCloudWrapper, const FString &playbackStreamId);
};
