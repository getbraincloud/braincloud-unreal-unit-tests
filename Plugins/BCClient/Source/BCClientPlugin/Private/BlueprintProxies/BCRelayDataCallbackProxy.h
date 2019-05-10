// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintRelayCallProxyBase.h"
#include "BCRelayDataCallbackProxy.generated.h"

UCLASS(MinimalAPI)
class UBCRelayDataCallbackProxy : public UBCBlueprintRelayCallProxyBase
{
	GENERATED_BODY()

  public:
	UBCRelayDataCallbackProxy(const FObjectInitializer &ObjectInitializer);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Relay")
	static UBCRelayDataCallbackProxy *RegisterDataCallback(UBrainCloudWrapper *brainCloudWrapper);
};
