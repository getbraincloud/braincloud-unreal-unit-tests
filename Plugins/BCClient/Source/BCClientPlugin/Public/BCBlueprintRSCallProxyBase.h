// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "IRSCallback.h"
#include "BCBlueprintRSCallProxyBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBrainCloudRSCallbackDelegate, FString, JsonData);

UCLASS(MinimalAPI)
class UBCBlueprintRSCallProxyBase : public UObject, public IRSCallback
{
    GENERATED_BODY()

  public:
    UBCBlueprintRSCallProxyBase(const FObjectInitializer &ObjectInitializer) {}

    //Response delegates
    UPROPERTY(BlueprintAssignable)
    FBrainCloudRSCallbackDelegate OnRSCallback;

    //callbacks
    void rsCallback(const FString &jsonData)
    {
        OnRSCallback.Broadcast(jsonData);
    }
};
