// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BCDataStreamProxy.generated.h"

class ABrainCloud;

UCLASS(MinimalAPI)
class UBCDataStreamProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
    GENERATED_BODY()

public:
    UBCDataStreamProxy(const FObjectInitializer& ObjectInitializer);

    /**
    * Creates custom data stream page event
    *
    * Param - eventName Name of event
    * Param - eventProperties Properties of event
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|DataStream")
        static UBCDataStreamProxy* CustomPageEvent(ABrainCloud *brainCloud, const FString& eventName, const FString& jsonEventProperties);

    /**
    * Creates custom data stream screen event
    *
    * Param - eventName Name of event
    * Param - eventProperties Properties of event
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|DataStream")
        static UBCDataStreamProxy* CustomScreenEvent(ABrainCloud *brainCloud, const FString& eventName, const FString& jsonEventProperties);

    /**
    * Creates custom data stream track event
    *
    * Param - eventName Name of event
    * Param - eventProperties Properties of event
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|DataStream")
        static UBCDataStreamProxy* CustomTrackEvent(ABrainCloud *brainCloud, const FString& eventName, const FString& jsonEventProperties);

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
