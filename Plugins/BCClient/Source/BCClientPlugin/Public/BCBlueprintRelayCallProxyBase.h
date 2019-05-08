// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "IRelayCallback.h"
#include "BCBlueprintRelayCallProxyBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBrainCloudRelayCallbackDelegate, FString, JsonData);

UCLASS(MinimalAPI)
class UBCBlueprintRelayCallProxyBase : public UObject, public IRelayCallback
{
    GENERATED_BODY()

  public:
    UBCBlueprintRelayCallProxyBase(const FObjectInitializer &ObjectInitializer) {}

    //Response delegates
    UPROPERTY(BlueprintAssignable)
    FBrainCloudRelayCallbackDelegate OnRelayCallback;

    //callbacks
    void relayCallback(const FString &jsonData)
    {
        OnRelayCallback.Broadcast(jsonData);
    }
};
