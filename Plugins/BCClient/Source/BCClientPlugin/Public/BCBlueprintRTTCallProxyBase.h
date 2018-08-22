// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "IRTTCallback.h"
#include "BCBlueprintRTTCallProxyBase.generated.h"

UCLASS(MinimalAPI)
class UBCBlueprintRTTCallProxyBase : public UObject, public IRTTCallback
{
    GENERATED_BODY()

  public:
    UBCBlueprintRTTCallProxyBase(const FObjectInitializer &ObjectInitializer)
    {
        this->AddToRoot();
    }

    //Response delegates
    UPROPERTY(BlueprintAssignable)
    FBrainCloudRTTCallbackDelegate OnRTTCallback;

  protected:
    //callbacks
    void rttCallback(const FString &jsonData)
    {
        OnRTTCallback.Broadcast(jsonData);
    }
};
