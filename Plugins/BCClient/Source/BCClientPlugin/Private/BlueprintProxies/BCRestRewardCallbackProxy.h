// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintRestCallProxyBase.h"
#include "BCRestRewardCallbackProxy.generated.h"

UCLASS(MinimalAPI)
class UBCRestRewardCallbackProxy : public UBCBlueprintRestCallProxyBase
{
	GENERATED_BODY()

  public:
	UBCRestRewardCallbackProxy(const FObjectInitializer &ObjectInitializer);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Client")
	static UBCRestRewardCallbackProxy *RegisterRewardCallback(UBrainCloudWrapper *brainCloudWrapper);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
	static void DeregisterRewardCallback(UBrainCloudWrapper *brainCloudWrapper);
};
