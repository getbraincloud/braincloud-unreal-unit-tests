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
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static int64 Ping(UBrainCloudWrapper *brainCloudWrapper);

	/*
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
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
	static bool IsConnected(UBrainCloudWrapper *brainCloudWrapper);

	/*
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static void DeregisterDataCallback(UBrainCloudWrapper *brainCloudWrapper);

	/**
	* @param in_target: BrainCloudRelayComms::TO_ALL_PLAYERS, to relay to all, otherwise use target netId
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static void Send(UBrainCloudWrapper *brainCloudWrapper, const TArray<uint8> &in_message, const uint8 in_target, bool in_reliable = true, bool in_ordered = true, int in_channel = 0);

	/**
	* 
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static void SetPingInterval(UBrainCloudWrapper *brainCloudWrapper, float in_value);

	/** 
 	* Convert an array of bytes to a TCHAR
 	* @param In byte array values to convert
 	* @param Count number of bytes to convert
 	* @return Valid FString representing bytes.
 	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static FString BCBytesToString(const TArray<uint8> &in_data);

	/** 
 	* Convert FString of bytes into the byte array.
 	* @param in_string		The FString of byte values
 	* @param in_maxBufferSize	Max buffer size of the out_bytes array, to prevent overflow
 	* @return	 Valid bytes from in_string
 	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static TArray<uint8> BCStringToBytes(const FString &in_string);
};
