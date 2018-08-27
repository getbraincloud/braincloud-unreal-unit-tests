// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintRestCallProxyBase.h"
#include "BCRestEventCallbackProxy.generated.h"

UCLASS(MinimalAPI)
class UBCRestEventCallbackProxy : public UBCBlueprintRestCallProxyBase
{
	GENERATED_BODY()

  public:
	UBCRestEventCallbackProxy(const FObjectInitializer &ObjectInitializer);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Client")
	static UBCRestEventCallbackProxy *RegisterEventCallback(UBrainCloudWrapper *brainCloudWrapper);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
	static void DeregisterEventCallback(UBrainCloudWrapper *brainCloudWrapper);
};
