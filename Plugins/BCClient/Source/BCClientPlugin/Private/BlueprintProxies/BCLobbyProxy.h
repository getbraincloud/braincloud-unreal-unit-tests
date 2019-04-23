// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCLobbyProxy.generated.h"

UCLASS(MinimalAPI)
class UBCLobbyProxy : public UBCBlueprintCallProxyBase
{
    GENERATED_BODY()

  public:
    UBCLobbyProxy(const FObjectInitializer &ObjectInitializer);

    /**
    * Finds a lobby matching the specified parameters
    * 
    * Service Name - lobby
	* Service Operation - FIND_LOBBY
    *
    * @param in_roomType type of room
	* @param in_rating rating of the room
    * @param in_maxSteps max iterations to search for a lobby
    * @param in_algoJson json string of the search algorithm to use
    * @param in_filterJson json string of the filter to be passed on
    * @param in_timeoutSecs numberOfseconds before timing out
    * @param in_isReady when lobby is found, place this user as "Ready"
    * @param in_extraJson json string for extra customization 
    * @param in_teamCode team code
    * @param in_otherUserCxIds array of other user Connection Ids to bring when the lobby is found
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Lobby")
    static UBCLobbyProxy *FindLobby(UBrainCloudWrapper *brainCloud, const FString &in_roomType, int32 in_rating, int32 in_maxSteps,
                                    const FString &in_algoJson, const FString &in_filterJson, int32 in_timeoutSecs,
                                    bool in_isReady, const FString &in_extraJson, const FString &in_teamCode, const TArray<FString> &in_otherUserCxIds);

    /**
    * Like findLobby, but geared towards creating new lobbies
    * 
    * Service Name - lobby
	* Service Operation - CREATE_LOBBY
    *
    * @param in_roomType type of room
	* @param in_rating rating of the room
    * @param in_maxSteps max iterations to search for a lobby
    * @param in_isReady when lobby is found, place this user as "Ready"
    * @param in_extraJson json string for extra customization 
    * @param in_teamCode team code
    * @param in_configJson json string of the lobby config
    * @param in_otherUserCxIds array of other user Connection Ids to bring when the lobby is found
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Lobby")
    static UBCLobbyProxy *CreateLobby(UBrainCloudWrapper *brainCloud, const FString &in_roomType, int32 in_rating, int32 in_maxSteps,
                                      bool in_isReady, const FString &in_extraJson, const FString &in_teamCode,
                                      const FString &in_configJson, const TArray<FString> &in_otherUserCxIds);

    /**
    * Finds a lobby matching the specified parameters, or creates one
    * 
    * Service Name - lobby
	* Service Operation - FIND_OR_CREATE_LOBBY
    *
    * @param in_roomType type of room
	* @param in_rating rating of the room
    * @param in_maxSteps max iterations to search for a lobby
    * @param in_algoJson json string of the search algorithm to use
    * @param in_filterJson json string of the filter to be passed on
    * @param in_timeoutSecs numberOfseconds before timing out
    * @param in_isReady when lobby is found, place this user as "Ready"
    * @param in_extraJson json string for extra customization 
    * @param in_teamCode team code
    * @param in_configJson json string of the lobby config
    * @param in_otherUserCxIds array of other user Connection Ids to bring when the lobby is found
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Lobby")
    static UBCLobbyProxy *FindOrCreateLobby(UBrainCloudWrapper *brainCloud, const FString &in_roomType, int32 in_rating, int32 in_maxSteps,
                                            const FString &in_algoJson, const FString &in_filterJson, int32 in_timeoutSecs,
                                            bool in_isReady, const FString &in_extraJson, const FString &in_teamCode,
                                            const FString &in_configJson, const TArray<FString> &in_otherUserCxIds);

    /**
    * Finds a lobby matching the specified parameters, or creates one
    * 
    * Service Name - lobby
	* Service Operation - GET_LOBBY_DATA
    *
    * @param in_lobbyID the lobbyId
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Lobby")
    static UBCLobbyProxy *GetLobbyData(UBrainCloudWrapper *brainCloud, const FString &in_lobbyID);

    /**
    * Updates the ready state of the player
    * 
    * Service Name - lobby
	* Service Operation - UPDATE_READY
    *
    * @param in_lobbyID the lobbyId
    * @param in_isReady when lobby is found, place this user as "Ready"
    * @param in_extraJson json string for extra customization 
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Lobby")
    static UBCLobbyProxy *UpdateReady(UBrainCloudWrapper *brainCloud, const FString &in_lobbyID, bool in_isReady,
                                      const FString &in_extraJson);

    /**
    * Switches to the specified team (if allowed). Note - may be blocked by cloud code script
    * 
    * Service Name - lobby
	* Service Operation - SWITCH_TEAM
    *
    * @param in_lobbyID the lobbyId
    * @param in_teamCode team code
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Lobby")
    static UBCLobbyProxy *SwitchTeam(UBrainCloudWrapper *brainCloud, const FString &in_lobbyID, const FString &in_teamCode);

    /**
    * Sends LOBBY_SIGNAL_DATA message to all lobby members
    * 
    * Service Name - lobby
	* Service Operation - SEND_SIGNAL
    *
    * @param in_lobbyID the lobbyId
    * @param in_signalJson customizeable json string attached to signal to lobby members
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Lobby")
    static UBCLobbyProxy *SendSignal(UBrainCloudWrapper *brainCloud, const FString &in_lobbyID, const FString &in_signalJson);

    /**
    * User leaves the specified lobby. if the user was the owner, a new owner will be chosen
    * 
    * Service Name - lobby
	* Service Operation - LEAVE_LOBBY
    *
    * @param in_lobbyID the lobbyId
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Lobby")
    static UBCLobbyProxy *LeaveLobby(UBrainCloudWrapper *brainCloud, const FString &in_lobbyID);


    /**
    * Service Name - lobby
	* Service Operation - JOIN_LOBBY
    *
    * @param in_lobbyID the lobbyId
    * @param in_isReady status of user joining
    * @param in_extraJson is the extra constraints
    * @param in_teamCode team code
    * @param in_otherUserCxIds is a list of other players who re part of the lobby
	* @param in_callback Method to be invoked when the server response is received.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Lobby")
    static UBCLobbyProxy *JoinLobby(UBrainCloudWrapper *brainCloud, const FString &in_lobbyID, bool in_isReady, const FString &in_extraJson, const FString &in_teamCode, const TArray<FString> &in_otherUserCxIds);

    /**
    *  Only valid from the owner of the lobby -- removes the specified member from the lobby
    * 
    * Service Name - lobby
	* Service Operation - REMOVE_MEMBER
    *
    * @param in_lobbyID the lobbyId
    * @param in_connectionId connectionId (cxId) of member to remove
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Lobby")
    static UBCLobbyProxy *RemoveMember(UBrainCloudWrapper *brainCloud, const FString &in_lobbyID, const FString &in_connectionId);

    /**
    *  Valid only for the owner of the group -- edits the overally lobby config data
    * 
    * Service Name - lobby
	* Service Operation - UPDATE_SETTINGS
    *
    * @param in_lobbyID the lobbyId
    * @param in_configJson json string of the lobby config
	* @param in_callback Method to be invoked when the server response is received.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Lobby")
    static UBCLobbyProxy *UpdateLobbyConfig(UBrainCloudWrapper *brainCloud, const FString &in_lobbyID, const FString &in_configJson);
};
