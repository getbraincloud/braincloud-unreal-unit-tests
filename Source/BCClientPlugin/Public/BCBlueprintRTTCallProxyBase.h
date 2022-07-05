// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "IRTTCallback.h"
#include "BCBlueprintRTTCallProxyBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBrainCloudRTTCallbackDelegate, FString, JsonData);

UCLASS(MinimalAPI)
class UBCBlueprintRTTCallProxyBase : public UObject, public IRTTCallback
{
    GENERATED_BODY()

  public:
    UBCBlueprintRTTCallProxyBase(const FObjectInitializer &ObjectInitializer) { this->AddToRoot(); }

    //Response delegates
    UPROPERTY(BlueprintAssignable)
    FBrainCloudRTTCallbackDelegate OnRTTCallback;

    //callbacks
    void rttCallback(const FString &jsonData)
    {
        OnRTTCallback.Broadcast(jsonData);
    }
};
