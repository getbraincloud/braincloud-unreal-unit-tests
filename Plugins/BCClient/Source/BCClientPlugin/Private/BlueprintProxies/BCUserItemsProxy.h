// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCAuthType.h"
#include "BCUserItemsProxy.generated.h"

UCLASS(MinimalAPI)
class UBCUserItemsProxy : public UBCBlueprintCallProxyBase
{
	GENERATED_BODY()

  public:
	UBCUserItemsProxy(const FObjectInitializer &ObjectInitializer);

	/*
    * Allows item(s) to be awarded to a user without collecting
	* the purchase amount. If includeDef is true, response 
	* includes associated itemDef with language fields limited
	* to the current or default language.
    *
    * Service Name - UserItems
    * Service Operation - AWARD_USER_ITEM
    *
    * @param defId
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserItems")
	static UBCUserItemsProxy *AwardUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &defId, int quantity, bool includeDef);

    /*
    * Allows a quantity of a specified user item to be dropped, 
    * without any recovery of the money paid for the item. If any 
    * quantity of the user item remains, it will be returned, potentially 
    * with the associated itemDef (with language fields limited to the 
    * current or default language).
    *
    * Service Name - UserItems
    * Service Operation - DROP_USER_ITEM
    *
    * @param itemId
    * @param quantity
    * @param includeDef
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserItems")
	static UBCUserItemsProxy *DropUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, int quantity, bool includeDef);

  /*
    * Retrieves the page of user's inventory from the server 
    * based on the context. If includeDef is true, response includes
    * associated itemDef with each user item, with language fields 
    * limited to the current or default language.
    *
    * Service Name - UserItems
    * Service Operation - GET_USER_ITEMS_PAGE
    *
    * @param criteria
    * @param includeDef
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserItems")
	static UBCUserItemsProxy *GetUserItemsPage(UBrainCloudWrapper *brainCloudWrapper, const FString &context, bool includeDef);

  /*
    * Retrieves the page of user's inventory 
    * from the server based on the encoded context. 
    * If includeDef is true, response includes associated 
    * itemDef with each user item, with language fields limited 
    * to the current or default language.
    *
    * Service Name - UserItems
    * Service Operation - GET_USER_ITEMS_PAGE_OFFSET
    *
    * @param criteria
    * @param pageOffset
    * @param includeDef
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserItems")
	static UBCUserItemsProxy *GetUserItemsPageOffset(UBrainCloudWrapper *brainCloudWrapper, const FString &context, int pageOffset, bool includeDef);
    
	/*
    * Retrieves the identified user item from the server.
    * If includeDef is true, response includes associated
    * itemDef with language fields limited to the current 
    * or default language.
    *
    * Service Name - UserItems
    * Service Operation - GET_USER_ITEM
    *
    * @param itemId
    * @param includeDef
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserItems")
	static UBCUserItemsProxy *GetUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, bool includeDef);

    /*
    * Gifts item to the specified player.
    *
    * Service Name - UserItems
    * Service Operation - GIVE_USER_ITEM_TO
    *
    * @param itemId
    * @param includeDef
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserItems")
	static UBCUserItemsProxy *GiveUserItemTo(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId, const FString &itemId, int version, int quantity, bool immediate);
    
	/*
    * Gifts item to the specified player.
    *
    * Service Name - UserItems
    * Service Operation - PURCHASE_USER_ITEM
    *
    * @param itemId
    * @param includeDef
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserItems")
	static UBCUserItemsProxy *PurchaseUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &defId, int quantity, const FString &shopId, bool includeDef);
   
    /*
    * Retrieves and transfers the gift item from the specified player, 
    * who must have previously called giveUserItemTo.
    *
    * Service Name - UserItems
    * Service Operation - RECEIVE_USER_ITEM_FROM
    *
    * @param profileId
    * @param itemId
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserItems")
	static UBCUserItemsProxy *ReceiveUserItemFrom(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId, const FString &itemId);
   
    /*
    * Allows a quantity of a specified user item to be sold. 
    * If any quantity of the user item remains, 
    * it will be returned, potentially with the associated 
    * itemDef (with language fields limited to the current 
    * or default language), along with the currency refunded 
    * and currency balances.
    *
    * Service Name - UserItems
    * Service Operation - SELL_USER_ITEM
    *
    * @param itemId
    * @param version
    * @param quantity
    * @param shopId
    * @param includeDef
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserItems")
	static UBCUserItemsProxy *SellUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, int version, int quantity,const FString &shopId, bool includeDef);
    
	/*
    * Updates the item data on the specified user item.
    *
    * Service Name - UserItems
    * Service Operation - UPDATE_USER_ITEM_DATA
    *
    * @param itemId
    * @param version
    * @param newItemData
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserItems")
	static UBCUserItemsProxy *UpdateUserItemData(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, int version, const FString &newItemData);
    
	/*
    * Uses the specified item, potentially consuming it.
    *
    * Service Name - UserItems
    * Service Operation - USE_USER_ITEM
    *
    * @param itemId
    * @param version
    * @param newItemData
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserItems")
	static UBCUserItemsProxy *UseUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, int version, const FString &newItemData, bool includeDef);

    /*
    * Publishes the specified item to the item management attached blockchain. Results are reported asynchronously via an RTT event.
    *
    * Service Name - UserItems
    * Service Operation - PUBLISH_USER_ITEM_TO_BLOCKCHAIN
    *
    * @param itemId
    * @param version
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserItems")
	static UBCUserItemsProxy *PublishUserItemToBlockchain(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, int version);
    
    /*
    * Syncs the caller's user items with the item management attached blockchain. Results are reported asynchronously via an RTT event.
    *
    * Service Name - UserItems
    * Service Operation - REFRESH_BLOCKCHAIN_USER_ITEMS
    *
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserItems")
	static UBCUserItemsProxy *RefreshBlockchainUserItems(UBrainCloudWrapper *brainCloudWrapper);

    /*
    * Removes the specified item from the item management attached blockchain. Results are reported asynchronously via an RTT event.    *
    * Service Name - UserItems
    * Service Operation - REMOVE_USER_ITEM_FROM_BLOCKCHAIN
    *
    * @param itemId
    * @param version
    * @param callback The method to be invoked when the server response is received
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserItems")
	static UBCUserItemsProxy *RemoveUserItemFromBlockchain(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, int version);

};
