// Copyright 2021 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "IRelayConnectCallback.h"
#include "BCBlueprintRelayConnectCallProxyBase.generated.h"

//Delegates for interface
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBrainCloudRelayConnectCallbackDelegate, const FString&, response);

UCLASS(MinimalAPI)
class UBCBlueprintRelayConnectCallProxyBase : public UObject, public IRelayConnectCallback
{
    GENERATED_BODY()

public:
    UBCBlueprintRelayConnectCallProxyBase(const FObjectInitializer &ObjectInitializer) { this->AddToRoot(); }
    
    //Response delegates
    UPROPERTY(BlueprintAssignable)
    FBrainCloudRelayConnectCallbackDelegate OnRelayConnectSuccessCallback;

    UPROPERTY(BlueprintAssignable)
    FBrainCloudRelayConnectCallbackDelegate OnRelayConnectFailureCallback;

    //callbacks
    void relayConnectSuccess(const FString &response)
    {
        OnRelayConnectSuccessCallback.Broadcast(response);
    }

    void relayConnectFailure(const FString &response)
    {
        OnRelayConnectFailureCallback.Broadcast(response);
    }
};
