// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintRelayCallProxyBase.h"
#include "BCRelayCallbackProxy.generated.h"

UCLASS(MinimalAPI)
class UBCRelayCallbackProxy : public UBCBlueprintRelayCallProxyBase
{
	GENERATED_BODY()

  public:
	UBCRelayCallbackProxy(const FObjectInitializer &ObjectInitializer);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Relay")
	static UBCRelayCallbackProxy *RegisterRelayCallback(UBrainCloudWrapper *brainCloudWrapper);
};
