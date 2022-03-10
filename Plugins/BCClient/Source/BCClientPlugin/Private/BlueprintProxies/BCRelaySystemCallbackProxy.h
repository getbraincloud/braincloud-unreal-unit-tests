// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintRelaySystemCallProxyBase.h"
#include "BCRelaySystemCallbackProxy.generated.h"

UCLASS(MinimalAPI)
class UBCRelaySystemCallbackProxy : public UBCBlueprintRelaySystemCallProxyBase
{
	GENERATED_BODY()

  public:
	UBCRelaySystemCallbackProxy(const FObjectInitializer &ObjectInitializer);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Relay")
	static UBCRelaySystemCallbackProxy *RegisterSystemCallback(UBrainCloudWrapper *brainCloudWrapper);
};
