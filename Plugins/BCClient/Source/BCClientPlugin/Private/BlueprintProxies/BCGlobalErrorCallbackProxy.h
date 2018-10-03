// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintRestCallProxyBase.h"
#include "BCGlobalErrorCallbackProxy.generated.h"

UCLASS(MinimalAPI)
class UBCGlobalErrorCallbackProxy : public UBCBlueprintRestCallProxyBase
{
	GENERATED_BODY()

  public:
	UBCGlobalErrorCallbackProxy(const FObjectInitializer &ObjectInitializer);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Client")
	static UBCGlobalErrorCallbackProxy *RegisterGlobalErrorCallback(UBrainCloudWrapper *brainCloudWrapper);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
	static void DeregisterGlobalErrorCallback(UBrainCloudWrapper *brainCloudWrapper);
};
