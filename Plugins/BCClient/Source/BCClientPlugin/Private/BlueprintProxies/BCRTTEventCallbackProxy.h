// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintRTTCallProxyBase.h"
#include "BCRTTEventCallbackProxy.generated.h"

UCLASS(MinimalAPI)
class UBCRTTEventCallbackProxy : public UBCBlueprintRTTCallProxyBase
{
	GENERATED_BODY()

  public:
	UBCRTTEventCallbackProxy(const FObjectInitializer &ObjectInitializer);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|RTT")
	static UBCRTTEventCallbackProxy *RegisterRTTEventCallback(UBrainCloudWrapper *brainCloudWrapper);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|RTT")
	static void DeregisterRTTEventCallback(UBrainCloudWrapper *brainCloudWrapper);
};
