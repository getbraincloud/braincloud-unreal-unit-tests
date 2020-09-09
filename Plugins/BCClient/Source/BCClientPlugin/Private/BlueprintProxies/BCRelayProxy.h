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

	/** 
 	* Use SetPingInterval() in order to set the interval for which Ping is calculated
	* does not average over the last N calls.  This is the value of the most recent Ping result
 	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static int64 Ping(UBrainCloudWrapper *brainCloudWrapper);

	/** 
 	* NetId retrieved from the connected call
 	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static uint8 NetId(UBrainCloudWrapper *brainCloudWrapper);

	/**
	 * Get the lobby's owner profile Id.
	 */
	// const FString &getOwnerProfileId(UBrainCloudWrapper *brainCloudWrapper) const;

	/**
	 * Returns the profileId associated with a netId.
	 */
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	const FString &GetProfileIdForNetId(UBrainCloudWrapper *brainCloudWrapper, int in_netId) const;

	/**
	 * Returns the netId associated with a profileId.
	 */
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	int GetNetIdForProfileId(UBrainCloudWrapper *brainCloudWrapper, const FString &in_profileId) const;

	/** 
 	* Start off a connection, based off connection type to brainClouds Relay Servers.  
	* Connect options come in from "ROOM_ASSIGNED" | "ROOM_READY" lobby callback
	* @param in_connectionType 
    * @param in_options
    * 	     in_options["ssl"] = false;
    * 	     in_options["host"] = "168.0.1.192";
    * 	     in_options["port"] = 9000;
    * 	     in_options["passcode"] = "somePasscode"
    * 	     in_options["lobbyId"] = "55555:v5v:001";
	* 
    * @param callback
 	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Relay")
	static UBCRelayProxy *Connect(UBrainCloudWrapper *brainCloudWrapper, BCRelayConnectionType in_connectionType, const FString &in_connectOptionsJson);

	/** 
 	* Disables relay event for this session.
 	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static void Disconnect(UBrainCloudWrapper *brainCloudWrapper);
	/** 
 	* Is Connected
 	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static bool IsConnected(UBrainCloudWrapper *brainCloudWrapper);

	/** 
 	*  Deregister the data callback
 	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static void DeregisterDataCallback(UBrainCloudWrapper *brainCloudWrapper);

	/** 	
 	* Send byte array representation of data
	* @param in_message : message to be sent
    * @param to_netId : the net id to send to, -1 to relay to all
	* @param in_reliable : send this reliably or not
	* @param in_ordered : received this ordered or not
	* @param in_channel : 0,1,2,3 (max of four channels)
 	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static void Send(UBrainCloudWrapper *brainCloudWrapper, const TArray<uint8> &in_message, const int32 to_netId, bool in_reliable = true, bool in_ordered = true, int in_channel = 0);

	/**
	 * Send a packet to any players by using a mask
	 *
	 * @param in_data : message to be sent
	 * @param playerMask Mask of the players to send to. 0001 = netId 0, 0010 = netId 1, etc. If you pass ALL_PLAYER_MASK you will be included and you will get an echo for your message. Use sendToAll instead, you will be filtered out. You can manually filter out by : ALL_PLAYER_MASK &= ~(1 << myNetId)
	 * @param reliable Send this reliable or not.
	 * @param ordered Receive this ordered or not.
	 * @param channel One of: (CHANNEL_HIGH_PRIORITY_1, CHANNEL_HIGH_PRIORITY_2, CHANNEL_NORMAL_PRIORITY, CHANNEL_LOW_PRIORITY)
	 */
	// UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	// bool SendToPlayers(UBrainCloudWrapper *brainCloudWrapper, const TArray<uint8> &in_data, const uint64 in_playerMask, bool in_reliable = true, bool in_ordered = true, int in_channel = 0);

	/**
	 * Send a packet to all except yourself
	 *
	 * @param in_data : message to be sent
	 * @param reliable Send this reliable or not.
	 * @param ordered Receive this ordered or not.
	 * @param channel One of: (CHANNEL_HIGH_PRIORITY_1, CHANNEL_HIGH_PRIORITY_2, CHANNEL_NORMAL_PRIORITY, CHANNEL_LOW_PRIORITY)
	 */
	// UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	// bool SendToAll(UBrainCloudWrapper *brainCloudWrapper, const TArray<uint8> &in_data, bool in_reliable = true, bool in_ordered = true, int in_channel = 0);

	/** 
 	* Set the ping interval.
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
