// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintRestCallProxyBase.h"
#include "BCNetworkErrorCallbackProxy.generated.h"

UCLASS(MinimalAPI)
class UBCNetworkErrorCallbackProxy : public UBCBlueprintRestCallProxyBase
{
	GENERATED_BODY()

  public:
	UBCNetworkErrorCallbackProxy(const FObjectInitializer &ObjectInitializer);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Client")
	static UBCNetworkErrorCallbackProxy *RegisterNetworkErrorCallback(UBrainCloudWrapper *brainCloudWrapper);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Client")
	static void DeregisterNetworkErrorCallback(UBrainCloudWrapper *brainCloudWrapper);
};
