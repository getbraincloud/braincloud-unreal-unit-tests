// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCUtilProxy.generated.h"

UCLASS(MinimalAPI)
class UBCUtilProxy : public UBCBlueprintCallProxyBase
{
	GENERATED_BODY()

  public:
	UBCUtilProxy(const FObjectInitializer &ObjectInitializer);

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Util")
	static UBCUtilProxy *ToUTCEpochTime(UBrainCloudWrapper *brainCloudWrapper, FDateTime dateTime);

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Util")
	static UBCUtilProxy  *ToDateTimeFromUTCEpoch(UBrainCloudWrapper *brainCloudWrapper, int64 utcDateTime);

};
