// Copyright 2021 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "IRelaySystemCallback.h"
#include "BCBlueprintRelaySystemCallProxyBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBrainCloudRelaySystemCallbackDelegate, const FString&, jsonResponse);

UCLASS(MinimalAPI)
class UBCBlueprintRelaySystemCallProxyBase : public UObject, public IRelaySystemCallback
{
    GENERATED_BODY()

public:
    UBCBlueprintRelaySystemCallProxyBase(const FObjectInitializer &ObjectInitializer) { this->AddToRoot(); }

    //Response delegates
    UPROPERTY(BlueprintAssignable)
    FBrainCloudRelaySystemCallbackDelegate OnRelaySystemCallback;

    //callbacks
    void relaySystemCallback(const FString &jsonResponse)
    {
        OnRelaySystemCallback.Broadcast(jsonResponse);
    }
};
