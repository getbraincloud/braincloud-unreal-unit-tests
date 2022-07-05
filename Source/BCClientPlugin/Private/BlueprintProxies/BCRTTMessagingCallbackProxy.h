// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintRTTCallProxyBase.h"
#include "BCRTTMessagingCallbackProxy.generated.h"

UCLASS(MinimalAPI)
class UBCRTTMessagingCallbackProxy : public UBCBlueprintRTTCallProxyBase
{
	GENERATED_BODY()

  public:
	UBCRTTMessagingCallbackProxy(const FObjectInitializer &ObjectInitializer);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|RTT")
	static UBCRTTMessagingCallbackProxy *RegisterRTTMessagingCallback(UBrainCloudWrapper *brainCloudWrapper);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|RTT")
	static void DeregisterRTTMessagingCallback(UBrainCloudWrapper *brainCloudWrapper);
};
