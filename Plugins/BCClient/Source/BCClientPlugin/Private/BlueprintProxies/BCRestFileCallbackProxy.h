// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintRestCallProxyBase.h"
#include "BCRestFileCallbackProxy.generated.h"

UCLASS(MinimalAPI)
class UBCRestFileCallbackProxy : public UBCBlueprintRestCallProxyBase
{
	GENERATED_BODY()

  public:
	UBCRestFileCallbackProxy(const FObjectInitializer &ObjectInitializer);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Client")
	static UBCRestFileCallbackProxy *RegisterFileCallback(UBrainCloudWrapper *brainCloudWrapper);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
	static void DeregisterFileCallback(UBrainCloudWrapper *brainCloudWrapper);
};
