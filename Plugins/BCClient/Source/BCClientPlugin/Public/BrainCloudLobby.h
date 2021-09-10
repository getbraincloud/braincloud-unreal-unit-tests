// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "IServerCallback.h"
#include "Runtime/Online/HTTP/Public/Http.h"
class BrainCloudClient;
class ServiceOperation;
class FPThreadsCriticalSection;

class BCCLIENTPLUGIN_API BrainCloudLobby : public IServerCallback
{
  public:
	static const uint8 MAX_PING_CALLS = 4;
    static const uint8 NUM_PING_CALLS_IN_PARALLEL = 2;
    BrainCloudLobby(BrainCloudClient *client);

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
	* @param in_callback Method to be invoked when the server response is received.
    */
    void findLobby(const FString &in_roomType, int32 in_rating, int32 in_maxSteps,
                   const FString &in_algoJson, const FString &in_filterJson, int32 in_timeoutSecs,
                   bool in_isReady, const FString &in_extraJson, const FString &in_teamCode, const TArray<FString> &in_otherUserCxIds,
                   IServerCallback *in_callback);

  /**
    * Finds a lobby matching the specified parameters WITH PING DATA.  GetRegionsForLobbies and PingRegions must be successfully responded to prior to calling.
    * 
    * Service Name - lobby
	* Service Operation - FIND_LOBBY_WITH_PING_DATA
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
	* @param in_callback Method to be invoked when the server response is received.
    */
    void findLobbyWithPingData(const FString &in_roomType, int32 in_rating, int32 in_maxSteps,
                   const FString &in_algoJson, const FString &in_filterJson, int32 in_timeoutSecs,
                   bool in_isReady, const FString &in_extraJson, const FString &in_teamCode, const TArray<FString> &in_otherUserCxIds,
                   IServerCallback *in_callback);

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
	* @param in_callback Method to be invoked when the server response is received.
    */
    void createLobby(const FString &in_roomType, int32 in_rating, int32 in_maxSteps,
                     bool in_isReady, const FString &in_extraJson, const FString &in_teamCode,
                     const FString &in_configJson, const TArray<FString> &in_otherUserCxIds, IServerCallback *in_callback);
                     
  /**
    * Like findLobby, but geared towards creating new lobbies WITH PING DATA.  GetRegionsForLobbies and PingRegions must be successfully responded to prior to calling.
    * 
    * Service Name - lobby
	* Service Operation - CREATE_LOBBY_WITH_PING_DATA
    *
    * @param in_roomType type of room
	* @param in_rating rating of the room
    * @param in_maxSteps max iterations to search for a lobby
    * @param in_isReady when lobby is found, place this user as "Ready"
    * @param in_extraJson json string for extra customization 
    * @param in_teamCode team code
    * @param in_configJson json string of the lobby config
    * @param in_otherUserCxIds array of other user Connection Ids to bring when the lobby is found
	* @param in_callback Method to be invoked when the server response is received.
    */
    void createLobbyWithPingData(const FString &in_roomType, int32 in_rating, int32 in_maxSteps,
                     bool in_isReady, const FString &in_extraJson, const FString &in_teamCode,
                     const FString &in_configJson, const TArray<FString> &in_otherUserCxIds, IServerCallback *in_callback);

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
	* @param in_callback Method to be invoked when the server response is received.
    */
    void findOrCreateLobby(const FString &in_roomType, int32 in_rating, int32 in_maxSteps,
                           const FString &in_algoJson, const FString &in_filterJson, int32 in_timeoutSecs,
                           bool in_isReady, const FString &in_extraJson, const FString &in_teamCode,
                           const FString &in_configJson, const TArray<FString> &in_otherUserCxIds, IServerCallback *in_callback);

    /**
    * Finds a lobby matching the specified parameters, or creates one WITH PING DATA.  GetRegionsForLobbies and PingRegions must be successfully responded to prior to calling.
    * 
    * Service Name - lobby
	* Service Operation - FIND_OR_CREATE_LOBBY_WITH_PING_DATA
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
	* @param in_callback Method to be invoked when the server response is received.
    */
    void findOrCreateLobbyWithPingData(const FString &in_roomType, int32 in_rating, int32 in_maxSteps,
                           const FString &in_algoJson, const FString &in_filterJson, int32 in_timeoutSecs,
                           bool in_isReady, const FString &in_extraJson, const FString &in_teamCode,
                           const FString &in_configJson, const TArray<FString> &in_otherUserCxIds, IServerCallback *in_callback);

                           

    /**
    * Finds a lobby matching the specified parameters, or creates one
    * 
    * Service Name - lobby
	* Service Operation - GET_LOBBY_DATA
    *
    * @param in_lobbyID the lobbyId
	* @param in_callback Method to be invoked when the server response is received.
    */
    void getLobbyData(const FString &in_lobbyID, IServerCallback *in_callback);

    /**
    * Updates the ready state of the player
    * 
    * Service Name - lobby
	* Service Operation - UPDATE_READY
    *
    * @param in_lobbyID the lobbyId
    * @param in_isReady when lobby is found, place this user as "Ready"
    * @param in_extraJson json string for extra customization 
	* @param in_callback Method to be invoked when the server response is received.
    */
    void updateReady(const FString &in_lobbyID, bool in_isReady, const FString &in_extraJson, IServerCallback *in_callback);

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
    void updateSettings(const FString &in_lobbyID, const FString &in_configJson, IServerCallback *in_callback);

    /**
    * Switches to the specified team (if allowed). Note - may be blocked by cloud code script
    * 
    * Service Name - lobby
	* Service Operation - SWITCH_TEAM
    *
    * @param in_lobbyID the lobbyId
    * @param in_teamCode team code
	* @param in_callback Method to be invoked when the server response is received.
    */
    void switchTeam(const FString &in_lobbyID, const FString &in_teamCode, IServerCallback *in_callback);

    /**
    * Sends LOBBY_SIGNAL_DATA message to all lobby members
    * 
    * Service Name - lobby
	* Service Operation - SEND_SIGNAL
    *
    * @param in_lobbyID the lobbyId
    * @param in_signalJson customizeable json string attached to signal to lobby members
	* @param in_callback Method to be invoked when the server response is received.
    */
    void sendSignal(const FString &in_lobbyID, const FString &in_signalJson, IServerCallback *in_callback);

    /**
    * User joins the specified lobby
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
    void joinLobby(const FString &in_lobbyID, bool in_isReady, const FString &in_extraJson, const FString &in_teamCode, const TArray<FString> &in_otherUserCxIds, IServerCallback *in_callback);

    /**
    * User joins the specified lobby WITH PING DATA.  GetRegionsForLobbies and PingRegions must be successfully responded to prior to calling.
    * Service Name - lobby
	* Service Operation - JOIN_LOBBY_WITH_PING_DATA
    *
    * @param in_lobbyID the lobbyId
    * @param in_isReady status of user joining
    * @param in_extraJson is the extra constraints
    * @param in_teamCode team code
    * @param in_otherUserCxIds is a list of other players who re part of the lobby
	* @param in_callback Method to be invoked when the server response is received.
    */
    void joinLobbyWithPingData(const FString &in_lobbyID, bool in_isReady, const FString &in_extraJson, const FString &in_teamCode, const TArray<FString> &in_otherUserCxIds, IServerCallback *in_callback);

    /**
    * User leaves the specified lobby. if the user was the owner, a new owner will be chosen
    * 
    * Service Name - lobby
	* Service Operation - LEAVE_LOBBY
    *
    * @param in_lobbyID the lobbyId
	* @param in_callback Method to be invoked when the server response is received.
    */
    void leaveLobby(const FString &in_lobbyID, IServerCallback *in_callback);

    /**
    *  Only valid from the owner of the lobby -- removes the specified member from the lobby
    * 
    * Service Name - lobby
	* Service Operation - REMOVE_MEMBER
    *
    * @param in_lobbyID the lobbyId
    * @param in_connectionId connectionId (cxId) of member to remove
	* @param in_callback Method to be invoked when the server response is received.
    */
    void removeMember(const FString &in_lobbyID, const FString &in_connectionId, IServerCallback *in_callback);

    /**
    * Cancel this members Find, Join and Searching of Lobbies
    * 
    * Service Name - lobby
	* Service Operation - CANCEL_FIND_REQUEST
    * 
    * @param in_lobbyType the lobby type to cancel a find request for
	* @param in_callback Method to be invoked when the server response is received.
    */
    void cancelFindRequest(const FString& in_lobbyType, IServerCallback* in_callback);

    /**
    * Retrieves the region settings for each of the given lobby types. Upon SuccessCallback or afterwards, call PingRegions to start retrieving appropriate data.  
    * Once that completes, the associated region Ping Data is retrievable via PingData and all associated <>WithPingData APIs are useable
    * Service Name - lobby
	* Service Operation - GET_REGIONS_FOR_LOBBIES
    * 
    * @param in_roomTypes List of roomtypes to request the ping regions
	* @param in_callback Method to be invoked when the server response is received.
    */
    void getRegionsForLobbies(const TArray<FString> &in_roomTypes, IServerCallback *in_callback);

    /**
    * Retrieves associated PingData averages to be used with all associated <>WithPingData APIs.
    * Call anytime after GetRegionsForLobbies before proceeding. 
    * 
	* @param in_callback Method to be invoked when the server response is received.
    */
    void pingRegions( IServerCallback *in_callback);
	
	/**
	* Gets a map keyed by rating of the visible lobby instances matching the given type and rating range.
	*
	* Service Name - Lobby
	* Service Operation - GetVisibleLobbyInstances
	*
	* @param lobbyType The type of lobby to look for.
	* @param minRating Minimum lobby rating.
	* @param maxRating Maximum lobby rating.
	*/
	void getVisibleLobbyInstances(const FString &in_lobbyType, int in_minRating, int in_maxRating, IServerCallback* in_callback);
	
    virtual void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString &jsonData);
    virtual void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString &message);

  private:
    void attachPingDataAndSend(TSharedRef<FJsonObject> message, ServiceOperation serviceOperation, IServerCallback *in_callback);
    void pingHost(FString in_region, FString in_target, int in_index);
    void onPingResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
    void pingNextItemToProcess();
    
    FHttpModule*_http;

    BrainCloudClient *_client = nullptr;
    IServerCallback *_regionsForLobbiesCallback;
    IServerCallback *_pingRegionsCallback;

    TSharedPtr<FJsonObject> _regionPingData;
    TSharedPtr<FJsonObject> _pingData;
    TMap<FString, TArray<double>> _cachedPingResponses;
    TArray<TPair<FString, FString>> m_regionTargetsToProcess;
    
    FCriticalSection Mutex;
};
