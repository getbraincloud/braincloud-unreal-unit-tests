// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCRTTProxy.generated.h"

UCLASS(MinimalAPI)
class UBCRTTProxy : public UBCBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UBCRTTProxy(const FObjectInitializer &ObjectInitializer);
	
	/*
	* Enables Real Time event for this session.
	* Real Time events are disabled by default. Usually events
	* need to be polled using GET_EVENTS. By enabling this, events will
	* be received instantly when they happen through a TCP connection to an Event Server.
	*
	* This function will first call requestClientConnection, then connect to the address
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|RTT")
	static UBCRTTProxy *EnableRTT(UBrainCloudWrapper *brainCloudWrapper, BCRTTConnectionType in_type);

	/*
	* Disables Real Time event for this session.
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|RTT")
	static void DisableRTT(UBrainCloudWrapper *brainCloudWrapper);

	/*
	* Disables Real Time event for this session.
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|RTT")
	static bool IsRTTEnabled(UBrainCloudWrapper *brainCloudWrapper);

	/**
	* 
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|RTT")
	static void SetRTTHeartBeatSeconds(UBrainCloudWrapper *brainCloudWrapper, int32 in_value);

	/**
	* 
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|RTT")
	static void DeregisterAllRTTCallbacks(UBrainCloudWrapper *brainCloudWrapper);

	UFUNCTION(BlueprintCallable, Category = "BrainCloud|RTT")
	static const FString &GetRTTConnectionId(UBrainCloudWrapper *brainCloudWrapper);

};
