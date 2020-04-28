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
	static UBCUtilProxy *ToEpochTime(UBrainCloudWrapper *brainCloudWrapper, FDateTime dateTime);

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Util")
	static UBCUtilProxy  *ToDateTimeFromEpoch(UBrainCloudWrapper *brainCloudWrapper, int64 utcDateTime);

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Util")
	static UBCUtilProxy  *ToDateTimeOffsetFromEpoch(UBrainCloudWrapper *brainCloudWrapper, int64 utcDateTime);
};
