// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
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
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|RTT Callback")
	static UBCRTTEventCallbackProxy *RegisterRTTEventCallbackSimple(UBrainCloudWrapper *brainCloudWrapper);
};
