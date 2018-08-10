// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCDataStreamProxy.generated.h"

class ABrainCloud;

UCLASS(MinimalAPI)
class UBCDataStreamProxy : public UBCBlueprintCallProxyBase
{
    GENERATED_BODY()

  public:
    UBCDataStreamProxy(const FObjectInitializer &ObjectInitializer);

    /**
    * Creates custom data stream page event
    *
    * Param - eventName Name of event
    * Param - eventProperties Properties of event
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|DataStream")
    static UBCDataStreamProxy *CustomPageEvent(UBrainCloudWrapper *brainCloudWrapper, const FString &eventName, const FString &jsonEventProperties);

    /**
    * Creates custom data stream screen event
    *
    * Param - eventName Name of event
    * Param - eventProperties Properties of event
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|DataStream")
    static UBCDataStreamProxy *CustomScreenEvent(UBrainCloudWrapper *brainCloudWrapper, const FString &eventName, const FString &jsonEventProperties);

    /**
    * Creates custom data stream track event
    *
    * Param - eventName Name of event
    * Param - eventProperties Properties of event
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|DataStream")
    static UBCDataStreamProxy *CustomTrackEvent(UBrainCloudWrapper *brainCloud, const FString &eventName, const FString &jsonEventProperties);
};
