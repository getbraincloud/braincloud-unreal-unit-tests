// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BrainCloudRelayComms.h"
#include "BCRelayProxy.generated.h"

UCLASS(MinimalAPI)
class UBCRelayProxy : public UBCBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UBCRelayProxy(const FObjectInitializer &ObjectInitializer);
	
    /*
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Relay")
	static int64 Ping(UBrainCloudWrapper *brainCloudWrapper);

    /*
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Relay")
	static uint8 NetId(UBrainCloudWrapper *brainCloudWrapper);

	/*
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Relay")
	static UBCRelayProxy *Connect(UBrainCloudWrapper *brainCloudWrapper, BCRelayConnectionType in_connectionType, const FString &in_connectOptionsJson);

	/*
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static void Disconnect(UBrainCloudWrapper *brainCloudWrapper);

	/*
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static void DeregisterDataCallback(UBrainCloudWrapper *brainCloudWrapper);

	/**
	* @param in_target: BrainCloudRelayComms::TO_ALL_PLAYERS, to relay to all, otherwise use target netId
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
    void Send(UBrainCloudWrapper *brainCloudWrapper, TArray<uint8> in_message, const uint8 in_target, bool in_reliable = true, bool in_ordered = true, int in_channel = 0);

	/**
	* 
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static void SetPingInterval(UBrainCloudWrapper *brainCloudWrapper, float in_value);

};
