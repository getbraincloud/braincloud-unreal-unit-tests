// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BCGlobalAppProxy.generated.h"

class ABrainCloud;

UCLASS(MinimalAPI)
class UBCGlobalAppProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
    GENERATED_BODY()

public:
    UBCGlobalAppProxy(const FObjectInitializer& ObjectInitializer);

    /**
    * Read game's global properties
    *
    * Service Name - GlobalApp
    * Service Operation - ReadProperties
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global App")
        static UBCGlobalAppProxy* ReadProperties(ABrainCloud *brainCloud);

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
