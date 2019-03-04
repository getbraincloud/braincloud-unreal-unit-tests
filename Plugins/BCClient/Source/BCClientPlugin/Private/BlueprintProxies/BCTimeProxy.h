// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCTimeProxy.generated.h"

UCLASS(MinimalAPI)
class UBCTimeProxy : public UBCBlueprintCallProxyBase
{
  GENERATED_BODY()

public:
  UBCTimeProxy(const FObjectInitializer &ObjectInitializer);

  /**Url
    * Method returns the server time in UTC. This is in UNIX millis time format.
    * For instance 1396378241893 represents 2014-04-01 2:50:41.893 in GMT-4.
    *
    * Service Name - Time
    * Service Operation - Read
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Time")
  static UBCTimeProxy *ReadServerTime(UBrainCloudWrapper *brainCloud);
};
