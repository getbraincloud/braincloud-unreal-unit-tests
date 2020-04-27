// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCUtilProxy.generated.h"

UCLASS(MinimalAPI)
class UBrainCloudUtilProxy : public BCBlueprintCallProxyBase
{
	GENERATED_BODY()

  public:
	UBrainCloudUtilProxy(const FObjectInitializer &ObjectInitializer);

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Util")
	static UBrainCloudUtilProxy *ToEpochTime(UBrainCloudWrapper *brainCloudWrapper, FDateTime dateTime);

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Util")
	static UBrainCloudUtilProxy  *ToDateTimeFromEpoch(UBrainCloudWrapper *brainCloudWrapper, long utcDateTime);

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Util")
	static UBrainCloudUtilProxy  *ToDateTimeOffsetFromEpoch(UBrainCloudWrapper *brainCloudWrapper, long utcDateTime);
};
