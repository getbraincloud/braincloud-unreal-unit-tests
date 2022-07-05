// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintRTTCallProxyBase.h"
#include "BCRTTLobbyCallbackProxy.generated.h"

UCLASS(MinimalAPI)
class UBCRTTLobbyCallbackProxy : public UBCBlueprintRTTCallProxyBase
{
	GENERATED_BODY()

  public:
	UBCRTTLobbyCallbackProxy(const FObjectInitializer &ObjectInitializer);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|RTT")
	static UBCRTTLobbyCallbackProxy *RegisterRTTLobbyCallback(UBrainCloudWrapper *brainCloudWrapper);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|RTT")
	static void DeregisterRTTLobbyCallback(UBrainCloudWrapper *brainCloudWrapper);
};
