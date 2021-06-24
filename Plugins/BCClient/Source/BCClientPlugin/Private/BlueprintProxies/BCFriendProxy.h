// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BrainCloudFriend.h"
#include "BCFriendProxy.generated.h"

UCLASS(MinimalAPI)
class UBCFriendProxy : public UBCBlueprintCallProxyBase
{
	GENERATED_BODY()

  public:
	UBCFriendProxy(const FObjectInitializer &ObjectInitializer);

	/**
	* Retrieves profile information for the specified user.
	*
	* Service Name - friend
	* Service Operation - GET_PROFILE_INFO_FOR_CREDENTIAL
	*
	* Param - externalId The users's external ID
	* Param - authenticationType The authentication type of the user ID
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
	static UBCFriendProxy *GetProfileInfoForCredential(UBrainCloudWrapper *brainCloudWrapper, const FString &externalId, EBCAuthType authenticationType);

	/**
	* Retrieves profile information for the specified external auth user.
	*
	* Service Name - friend
	* Service Operation - GET_PROFILE_INFO_FOR_EXTERNAL_AUTH_ID
	*
	* Param - externalId External ID of the user to find
	* Param - externalAuthType The external authentication type used for this users's external ID
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
	static UBCFriendProxy *GetProfileInfoForExternalAuthId(UBrainCloudWrapper *brainCloudWrapper, const FString &externalId, const FString &externalAuthType);

	/**
	* Retrieves the external ID for the specified user profile ID on the specified social platform.
	*
	* Param - profileId Profile ID.
	* Param - authenticationType Associated authentication type.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
	static UBCFriendProxy *GetExternalIdForProfileId(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId, const FString &authenticationType);

	/**
	* Returns user state of a particular user.
	*
	* Service Name - Friend
	* Service Operation - GET_SUMMARY_DATA_FOR_PROFILE_ID
	*
	* Param - profileId Profile Id of user to retrieve user state for.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
	static UBCFriendProxy *GetSummaryDataForProfileId(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId);

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
	static UBCFriendProxy *ReadFriendEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId, const FString &friendId);

	/**
	* Returns entities of all friends optionally based on type.
	*
	* Service Name - Friend
	* Service Operation - ReadFriendsEntities
	*
	* Param - entityType Types of entities to retrieve.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
	static UBCFriendProxy *ReadFriendsEntities(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType);

	/**
	* @deprecated Use readAllUserStats instead
	*/

	/**
	* Finds a list of users matching the search text by performing an exact match search
	*
	* Service Name - friend
	* Service Operation - FIND_USERS_BY_EXACT_NAME
	*
	* Param - searchText The string to search for.
	* Param - maxResults  Maximum number of results to return.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
	static UBCFriendProxy *FindUsersByExactName(UBrainCloudWrapper *brainCloudWrapper, const FString &searchText, int32 maxResults);

	/**
	* Finds a list of users matching the search text by performing a substring
	* search of all user names.
	*
	* Service Name - friend
	* Service Operation - FIND_USERS_BY_SUBSTR_NAME
	*
	* Param - searchText The string to search for.
	* Param - maxResults  Maximum number of results to return.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
	static UBCFriendProxy *FindUsersBySubstrName(UBrainCloudWrapper *brainCloudWrapper, const FString &searchText, int32 maxResults);

	/**
	* Retrieves profile information for the partial matches of the specified text.
	*
	* Service Name - Friend
	* Service Operation - FIND_USER_BY_EXACT_UNIVERSAL_ID
	*
	* Param - searchText Universal ID text on which to search.
	* Param - maxResults Maximum number of results to return. If there are more the message
	*                    "Too many results to return." is sent back instead of the users.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
	static UBCFriendProxy *FindUserByExactUniversalId(UBrainCloudWrapper *brainCloudWrapper, const FString &searchText);

	/**
	* Retrieves profiles for the partial matches of the specified Universal Id text.
	*
	* Service Name - Friend
	* Service Operation - FIND_USERS_BY_NAME_STARTING_WITH
	*
	* Param - searchText Universal ID text on which to search.
	* Param - maxResults Maximum number of results to return. If there are more the message
	*                    "Too many results to return." is sent back instead of the users.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
	static UBCFriendProxy *FindUsersByNameStartingWith(UBrainCloudWrapper *brainCloudWrapper, const FString &searchText, int32 maxResults);

	/**
	* Retrieves profiles for the partial matches of the specified Universal Id text.
	*
	* Service Name - Friend
	* Service Operation - FIND_USERS_BY_UNIVERSAL_ID_STARTING_WITH
	*
	* Param - searchText Universal ID text on which to search.
	* Param - maxResults Maximum number of results to return. If there are more the message
	*                    "Too many results to return." is sent back instead of the users.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
	static UBCFriendProxy *FindUsersByUniversalIdStartingWith(UBrainCloudWrapper *brainCloudWrapper, const FString &searchText, int32 maxResults);

	/**
	* Retrieves a list of user and friend platform information for all friends of the current user.
	*
	* Service Name - Friend
	* Service Operation - LIST_FRIENDS
	*
	* Param - friendPlatform Friend platform to query.
	* Param - includeSummaryData  True if including summary data; false otherwise.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
	static UBCFriendProxy *ListFriends(UBrainCloudWrapper *brainCloudWrapper, EFriendPlatform friendPlatform, bool includeSummaryData);

	/**
	* Retrieves the social information associated with the logged in user. Includes summary data if includeSummaryData is true.
	*
	* Service Name - Friend
	* Service Operation - GET_MY_SOCIAL_INFO
	*
	* Param - friendPlatform Friend platform to query.
	* Param - includeSummaryData  True if including summary data; false otherwise.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
	static UBCFriendProxy *GetMySocialInfo(UBrainCloudWrapper *brainCloudWrapper, EFriendPlatform friendPlatform, bool includeSummaryData);


	/**
	* Links the current user and the specified users as brainCloud friends.
	*
	* Service Name - Friend
	* Service Operation - ADD_FRIENDS
	*
	* Param - profileIds Collection of profile IDs.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
	static UBCFriendProxy *AddFriends(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &profileIds);

	/**
	* Links the profiles for the specified externalIds for the given friend platform as internal friends.
	*
	* Service Name - Friend
	* Service Operation - ADD_FRIENDS_FROM_PLATFORM
	*
	* Param - friendPlatform Platform to add from (i.e: FriendPlatform::Facebook)
	* Param - mode ADD or SYNC
	* Param - externalIds Collection of external IDs from the friend platform.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
    static UBCFriendProxy *AddFriendsFromPlatform(UBrainCloudWrapper *brainCloudWrapper,EFriendPlatform friendPlatform, FString mode, const TArray<FString> &externalIds);

	/**
	* Unlinks the current user and the specified users as brainCloud friends.
	*
	* Service Name - Friend
	* Service Operation - REMOVE_FRIENDS
	*
	* Param - profileIds Collection of profile IDs.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
	static UBCFriendProxy *RemoveFriends(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &profileIds);

	/**
	* Get users online status
	*
	* Service Name - Friend
	* Service Operation - GET_USERS_ONLINE_STATUS
	*
	* Param - profileIds Collection of profile IDs.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
	static UBCFriendProxy *GetUsersOnlineStatus(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &profileIds); 

	/**
	* Read a friend's user state.
	*
	* Service Name - PlayerState
	* Service Operation - ReadFriendsPlayerState
	*
	* @param friendId Target friend
	* @param callback Method to be invoked when the server response is received.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Friend")
	static UBCFriendProxy *ReadFriendUserState(UBrainCloudWrapper *brainCloudWrapper, const FString &friendId); 
};
