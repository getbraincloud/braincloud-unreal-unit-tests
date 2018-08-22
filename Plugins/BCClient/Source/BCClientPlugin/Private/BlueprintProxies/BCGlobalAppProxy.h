// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCGlobalAppProxy.generated.h"

UCLASS(MinimalAPI)
class UBCGlobalAppProxy : public UBCBlueprintCallProxyBase
{
    GENERATED_BODY()

  public:
    UBCGlobalAppProxy(const FObjectInitializer &ObjectInitializer);

    /**
    * Read game's global properties
    *
    * Service Name - GlobalApp
    * Service Operation - ReadProperties
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global App")
    static UBCGlobalAppProxy *ReadProperties(UBrainCloudWrapper *brainCloud);
};
