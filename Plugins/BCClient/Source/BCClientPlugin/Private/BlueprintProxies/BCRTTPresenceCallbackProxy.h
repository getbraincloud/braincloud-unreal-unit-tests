// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintRTTCallProxyBase.h"
#include "BCRTTPresenceCallbackProxy.generated.h"

UCLASS(MinimalAPI)
class UBCRTTPresenceCallbackProxy : public UBCBlueprintRTTCallProxyBase
{
	GENERATED_BODY()

  public:
	UBCRTTPresenceCallbackProxy(const FObjectInitializer &ObjectInitializer);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|RTT")
	static UBCRTTPresenceCallbackProxy *RegisterRTTPresenceCallback(UBrainCloudWrapper *brainCloudWrapper);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|RTT")
	static void DeregisterRTTPresenceCallback(UBrainCloudWrapper *brainCloudWrapper);
};
