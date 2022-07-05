// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintRTTCallProxyBase.h"
#include "BCRTTChatCallbackProxy.generated.h"

UCLASS(MinimalAPI)
class UBCRTTChatCallbackProxy : public UBCBlueprintRTTCallProxyBase
{
	GENERATED_BODY()

  public:
	UBCRTTChatCallbackProxy(const FObjectInitializer &ObjectInitializer);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|RTT")
	static UBCRTTChatCallbackProxy *RegisterRTTChatCallback(UBrainCloudWrapper *brainCloudWrapper);

	/**
	* 	
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|RTT")
	static void DeregisterRTTChatCallback(UBrainCloudWrapper *brainCloudWrapper);
};
