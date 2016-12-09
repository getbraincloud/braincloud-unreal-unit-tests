// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BrainCloudFriend.h"
#include "BCFriendProxy.generated.h"

UCLASS(MinimalAPI)
class UBCFriendProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
	GENERATED_BODY()

public:
	UBCFriendProxy(const FObjectInitializer& ObjectInitializer);

	/**
	* Retrieves profile information for the specified user.
	*
	* Service Name - Friend
	* Service Operation - GetFriendProfileInfoForExternalId
	*
	* Param - externalId The friend's external id e.g. Facebook id
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
		static UBCFriendProxy* GetFriendProfileInfoForExternalId(const FString& externalId, const FString& authenticationType);

	/**
	* Retrieves the external ID for the specified user profile ID on the specified social platform.
	*
	* Param - profileId Profile (player) ID.
	* Param - authenticationType Associated authentication type.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
		static UBCFriendProxy* GetExternalIdForProfileId(const FString& profileId, const FString& authenticationType);

	/**
	* Returns player state of a particular user.
	*
	* Service Name - Friend
	* Service Operation - GET_SUMMARY_DATA_FOR_PROFILE_ID
	*
	* Param - profileId Profile Id of player to retrieve player state for.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
		static UBCFriendProxy* GetSummaryDataForProfileId(const FString& profileId);

	/**
	* Returns a particular entity of a particular friend.
	*
	* Service Name - Friend
	* Service Operation - ReadFriendEntity
	*
	* Param - entityId Id of entity to retrieve.
	* Param - friendId Profile Id of friend who owns entity.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
		static UBCFriendProxy* ReadFriendEntity(const FString& entityId, const FString& friendId);

	/**
	* Returns entities of all friends optionally based on type.
	*
	* Service Name - Friend
	* Service Operation - ReadFriendsEntities
	*
	* Param - entityType Types of entities to retrieve.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
		static UBCFriendProxy* ReadFriendsEntities(const FString& entityType);

	/**
	* Read a friend's player state.
	*
	* Service Name - PlayerState
	* Service Operation - ReadFriendsPlayerState
	*
	* Param - friendId Target friend
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
		static UBCFriendProxy* ReadFriendPlayerState(const FString& friendId);

	/**
	* Finds a list of players matching the search text by performing an exact match search
	*
	* Service Name - friend
	* Service Operation - FIND_USERS_BY_EXACT_NAME
	*
	* Param - searchText The string to search for.
	* Param - maxResults  Maximum number of results to return.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
		static UBCFriendProxy* FindUsersByExactName(const FString& searchText, int32 maxResults);

	/**
	* Finds a list of players matching the search text by performing a substring
	* search of all player names.
	*
	* Service Name - friend
	* Service Operation - FIND_USERS_BY_SUBSTR_NAME
	*
	* Param - searchText The string to search for.
	* Param - maxResults  Maximum number of results to return.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
		static UBCFriendProxy* FindUsersBySubstrName(const FString& searchText, int32 maxResults);

	/**
	* Retrieves profile information for the partial matches of the specified text.
	*
	* Service Name - Friend
	* Service Operation - FIND_PLAYER_BY_UNIVERSAL_ID
	*
	* Param - searchText Universal ID text on which to search.
	* Param - maxResults Maximum number of results to return. If there are more the message
	*                    "Too many results to return." is sent back instead of the players.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
		static UBCFriendProxy* FindPlayerByUniversalId(const FString& searchText, int32 maxResults);

	/**
	* Retrieves a list of player and friend platform information for all friends of the current player.
	*
	* Service Name - Friend
	* Service Operation - LIST_FRIENDS
	*
	* Param - friendPlatform Friend platform to query.
	* Param - includeSummaryData  True if including summary data; false otherwise.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
		static UBCFriendProxy* ListFriends(EFriendPlatform friendPlatform, bool includeSummaryData);

	/**
	* Links the current player and the specified players as brainCloud friends.
	*
	* Service Name - Friend
	* Service Operation - ADD_FRIENDS
	*
	* Param - profileIds Collection of player IDs.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
		static UBCFriendProxy* AddFriends(const TArray<FString>& profileIds);

	/**
	* Unlinks the current player and the specified players as brainCloud friends.
	*
	* Service Name - Friend
	* Service Operation - REMOVE_FRIENDS
	*
	* Param - profileIds Collection of player IDs.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
		static UBCFriendProxy* RemoveFriends(const TArray<FString>& profileIds);

	/**
	* Get users online status
	*
	* Service Name - Friend
	* Service Operation - GET_USERS_ONLINE_STATUS
	*
	* Param - profileIds Collection of profile IDs.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
		static UBCFriendProxy* GetUsersOnlineStatus(const TArray<FString>& profileIds);

	//Response delegates
	UPROPERTY(BlueprintAssignable)
		FBrainCloudCallbackDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
		FBrainCloudCallbackDelegate OnFailure;

protected:
	// IServerCallback interface
	void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
	void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
	// End of IServerCallback interface
};
