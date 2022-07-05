// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintRelayConnectCallProxyBase.h"
#include "BrainCloudRelayComms.h"
#include "BrainCloudWrapper.h"
#include "BCRelayProxy.generated.h"

UCLASS(MinimalAPI)
class UBCRelayProxy : public UBCBlueprintRelayConnectCallProxyBase
{
	GENERATED_BODY()

public:
	UBCRelayProxy(const FObjectInitializer &ObjectInitializer);

	/** 
     * Start a connection, based on connection type to 
     * brainClouds Relay Servers. Connect options come in
     * from ROOM_ASSIGNED lobby callback.
     * 
     * @param connectionType
     * @param host
     * @param port
     * @param passcode
     * @param lobbyId
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Relay")
	static UBCRelayProxy *Connect(UBrainCloudWrapper *brainCloudWrapper, BCRelayConnectionType in_connectionType, const FString &host, int port, const FString &passcode, const FString &lobbyId);

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
     * Get the current ping for our user.
     * Note: Pings are not distributed among other members. Your game will
     * have to bundle it inside a packet and distribute to other peers.
	 */
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static int64 GetPing(UBrainCloudWrapper *brainCloudWrapper);

	/**
	 * Get the lobby's owner profile Id.
	 */
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static const FString &GetOwnerProfileId(UBrainCloudWrapper *brainCloudWrapper);
    
	/**
	 * Get the lobby's owner Connection Id.
	 */
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static const FString &GetOwnerCxId(UBrainCloudWrapper *brainCloudWrapper);

	/**
	 * Returns the profileId associated with a netId.
	 */
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static const FString &GetProfileIdForNetId(UBrainCloudWrapper *brainCloudWrapper, int in_netId);

	/**
	 * Returns the netId associated with a profileId.
	 */
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static int GetNetIdForProfileId(UBrainCloudWrapper *brainCloudWrapper, const FString &in_profileId);

	/**
	 * Returns the connection Id associated with a netId.
	 */
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static const FString &GetCxIdForNetId(UBrainCloudWrapper *brainCloudWrapper, int in_netId);

	/**
	 * Returns the netId associated with a connection Id.
	 */
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static int GetNetIdForCxId(UBrainCloudWrapper *brainCloudWrapper, const FString &in_profileId);

	/** 
	*  Deregister the relay callback
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static void DeregisterRelayCallback(UBrainCloudWrapper *brainCloudWrapper);

	/** 
	*  Deregister the system callback
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static void DeregisterSystemCallback(UBrainCloudWrapper *brainCloudWrapper);

	/**
	* Send byte array representation of data
    * @param data Byte array for the data to send
    * @param toNetId The net id to send to, -1 to relay to all.
    * @param reliable Send this reliable or not.
    * @param ordered Receive this ordered or not.
    * @param channel One of: (CHANNEL_HIGH_PRIORITY_1, CHANNEL_HIGH_PRIORITY_2, CHANNEL_NORMAL_PRIORITY, CHANNEL_LOW_PRIORITY)
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static void Send(UBrainCloudWrapper *brainCloudWrapper, const TArray<uint8> &data, int toNetId, bool reliable, bool ordered, BCRelayChannel channel);

	/**
     * Send a packet to any players by using a mask
     *
     * @param data Byte array for the data to send
     * @param playerMask Mask of the players to send to. 0001 = netId 0, 0010 = netId 1, etc. If you pass ALL_PLAYER_MASK you will be included and you will get an echo for your message. Use sendToAll instead, you will be filtered out. You can manually filter out by : ALL_PLAYER_MASK &= ~(1 << myNetId)
     * @param reliable Send this reliable or not.
     * @param ordered Receive this ordered or not.
     * @param channel One of: (CHANNEL_HIGH_PRIORITY_1, CHANNEL_HIGH_PRIORITY_2, CHANNEL_NORMAL_PRIORITY, CHANNEL_LOW_PRIORITY)
	*/
	// UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	// static void SendToPlayers(UBrainCloudWrapper *brainCloudWrapper, const TArray<uint8> &data, uint32 in_playerMaskLow, uint32 in_playerMaskHi, bool reliable, bool ordered, BCRelayChannel channel);

	/**
     * Send a packet to all except yourself
     *
     * @param data Byte array for the data to send
     * @param reliable Send this reliable or not.
     * @param ordered Receive this ordered or not.
     * @param channel One of: (CHANNEL_HIGH_PRIORITY_1, CHANNEL_HIGH_PRIORITY_2, CHANNEL_NORMAL_PRIORITY, CHANNEL_LOW_PRIORITY)
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud|Relay")
	static void SendToAll(UBrainCloudWrapper *brainCloudWrapper, const TArray<uint8> &data, bool reliable, bool ordered, BCRelayChannel channel);
};
