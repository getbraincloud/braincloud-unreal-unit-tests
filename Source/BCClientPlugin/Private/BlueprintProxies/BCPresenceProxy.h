// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCPresenceProxy.generated.h"

UCLASS(MinimalAPI)
class UBCPresenceProxy : public UBCBlueprintCallProxyBase
{
  GENERATED_BODY()

public:
  UBCPresenceProxy(const FObjectInitializer &ObjectInitializer);

  /**
* Force an RTT presence update to all listeners of the caller.
*
* Service Name - Presence
* Service Operation - FORCE_PUSH
*
*/
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Presence")
  static UBCPresenceProxy *ForcePush(UBrainCloudWrapper *brainCloudWrapper);

  /**
* Gets the presence data for the given <platform>. Can be one of "all",
* "brainCloud", or "facebook". Will not include offline profiles
* unless <includeOffline> is set to true.
*
* Service Name - Presence
* Service Operation - GET_PRESENCE_OF_FRIENDS
* 
* @param platform The store platform, valid stored: all, brainCloud, facebook
* @param includeOffline Will not include offline profiles unless includeOffline is set to true.
*/
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Presence")
  static UBCPresenceProxy *GetPresenceOfFriends(UBrainCloudWrapper *brainCloudWrapper, const FString &platform, bool includeOffline);
  /**
* Gets the presence data for the given <groupId>. Will not include
* offline profiles unless <includeOffline> is set to true.
*
* Service Name - Presence
* Service Operation - GET_PRESENCE_OF_GROUP
* 
* @param groupId th eid for the gorup
* @param includeOffline Will not include offline profiles unless includeOffline is set to true.
* @param callback The method to be invoked when the server response is received 
*/
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Presence")
  static UBCPresenceProxy *GetPresenceOfGroup(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, bool includeOffline);

  /**
* Gets the presence data for the given <profileIds>. Will not include
* offline profiles unless <includeOffline> is set to true.
*
* Service Name - Presence
* Service Operation - GET_PRESENCE_OF_USERS
* 
* @param groupId the id for the group
* @param includeOffline Will not include offline profiles unless includeOffline is set to true.
* @param callback The method to be invoked when the server response is received 
*/
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Presence")
  static UBCPresenceProxy *GetPresenceOfUsers(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &profileIds, bool includeOffline);

  /**
* Registers the caller for RTT presence updates from friends for the
* given <platform>. Can be one of "all", "brainCloud", or "facebook".
* If <bidirectional> is set to true, then also registers the targeted
* users for presence updates from the caller.
*
* Service Name - Presence
* Service Operation - REGISTER_LISTENERS_FOR_FRIENDS
* 
* @param platform The store platform, valid stored: all, brainCloud, facebook
* @param bidirectional Allows registration of target user for presence update
* @param callback The method to be invoked when the server response is received 
*/
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Presence")
  static UBCPresenceProxy *RegisterListenersForFriends(UBrainCloudWrapper *brainCloudWrapper, const FString &platform, bool biderectional);

  /**
* Registers the caller for RTT presence updates from the members of
* the given <groupId>. Caller must be a member of said group. If
* <bidirectional> is set to true, then also registers the targeted
* users for presence updates from the caller.
*
* Service Name - Presence
* Service Operation - REGISTER_LISTENERS_FOR_GROUP
* 
* @param groupId the id for the group
* @param bidirectional Allows registration of target user for presence update
* @param callback The method to be invoked when the server response is received 
*/
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Presence")
  static UBCPresenceProxy *RegisterListenersForGroup(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, bool biderectional);
  /**
* Registers the caller for RTT presence updates for the given
* <profileIds>. If <bidirectional> is set to true, then also registers
* the targeted users for presence updates from the caller.
*
* Service Name - Presence
* Service Operation - REGISTER_LISTENERS_FOR_PROFILES
* 
* @param profileIds The store platform, valid stored: all, brainCloud, facebook
* @param bidirectional Allows registration of target user for presence update
* @param callback The method to be invoked when the server response is received 
*/
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Presence")
  static UBCPresenceProxy *RegisterListenersForProfiles(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &profileIds, bool biderectional);

  /**
* Update the presence data visible field for the caller.
*
* Service Name - Presence
* Service Operation - SET_VISIBILITY
* 
* @param visible is the player visible to others.
* @param callback The method to be invoked when the server response is received 
*/
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Presence")
  static UBCPresenceProxy *SetVisibility(UBrainCloudWrapper *brainCloudWrapper, bool visible);
  /**
* Stops the caller from receiving RTT presence updates. Does not
* affect the broadcasting of *their* presence updates to other
* listeners.
*
* Service Name - Presence
* Service Operation - STOP_LISTENING
* 
* @param callback The method to be invoked when the server response is received 
*/
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Presence")
  static UBCPresenceProxy *StopListening(UBrainCloudWrapper *brainCloudWrapper);
  /**
* Update the presence data activity field for the caller.
*
* Service Name - Presence
* Service Operation - UPDATE_ACTIVITY
* 
* @param activity current activity 
* @param callback The method to be invoked when the server response is received 
*/
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Presence")
  static UBCPresenceProxy *UpdateActivity(UBrainCloudWrapper *brainCloudWrapper, const FString &activity);
};
