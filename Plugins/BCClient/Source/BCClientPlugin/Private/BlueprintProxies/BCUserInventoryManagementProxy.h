// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCAuthType.h"
#include "BCUserInventoryManagementProxy.generated.h"

UCLASS(MinimalAPI)
class UBCUserInventoryManagementProxy : public UBCBlueprintCallProxyBase
{
	GENERATED_BODY()

  public:
	UBCUserInventoryManagementProxy(const FObjectInitializer &ObjectInitializer);

	/*
    * Allows item(s) to be awarded to a user without collecting
	* the purchase amount. If includeDef is true, response 
	* includes associated itemDef with language fields limited
	* to the current or default language.
    *
    * Service Name - UserInventoryManagement
    * Service Operation - AWARD_USER_ITEM
    *
    * @param defId
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserInventoryManagement")
	static UBCUserInventoryManagementProxy *AwardUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &defId, int quantity, bool includeDef);

    /*
    * Allows a quantity of a specified user item to be dropped, 
    * without any recovery of the money paid for the item. If any 
    * quantity of the user item remains, it will be returned, potentially 
    * with the associated itemDef (with language fields limited to the 
    * current or default language).
    *
    * Service Name - UserInventoryManagement
    * Service Operation - DROP_USER_ITEM
    *
    * @param itemId
    * @param quantity
    * @param includeDef
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserInventoryManagement")
	static UBCUserInventoryManagementProxy *DropUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, int quantity, bool includeDef);

  /*
    * Retrieves the user's inventory from the server (or inventory specified by criteria). 
    * If includeDef is true, response includes associated itemDef with each user item, with
    * language fields limited to the current or default language.
    *
    * Service Name - UserInventoryManagement
    * Service Operation - GET_USER_INVENTORY
    *
    * @param criteria
    * @param includeDef
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserInventoryManagement")
	static UBCUserInventoryManagementProxy *GetUserInventory(UBrainCloudWrapper *brainCloudWrapper, const FString &criteria, bool includeDef);

  /*
    * Retrieves the page of user's inventory from the server 
    * based on the context. If includeDef is true, response includes
    * associated itemDef with each user item, with language fields 
    * limited to the current or default language.
    *
    * Service Name - UserInventoryManagement
    * Service Operation - GET_USER_INVENTORY_PAGE
    *
    * @param criteria
    * @param includeDef
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserInventoryManagement")
	static UBCUserInventoryManagementProxy *GetUserInventoryPage(UBrainCloudWrapper *brainCloudWrapper, const FString &context, bool includeDef);

  /*
    * Retrieves the page of user's inventory 
    * from the server based on the encoded context. 
    * If includeDef is true, response includes associated 
    * itemDef with each user item, with language fields limited 
    * to the current or default language.
    *
    * Service Name - UserInventoryManagement
    * Service Operation - GET_USER_INVENTORY_PAGE_OFFSET
    *
    * @param criteria
    * @param pageOffset
    * @param includeDef
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserInventoryManagement")
	static UBCUserInventoryManagementProxy *GetUserInventoryPageOffset(UBrainCloudWrapper *brainCloudWrapper, const FString &context, int pageOffset, bool includeDef);
    
	/*
    * Retrieves the identified user item from the server.
    * If includeDef is true, response includes associated
    * itemDef with language fields limited to the current 
    * or default language.
    *
    * Service Name - UserInventoryManagement
    * Service Operation - GET_USER_ITEM
    *
    * @param itemId
    * @param includeDef
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserInventoryManagement")
	static UBCUserInventoryManagementProxy *GetUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, bool includeDef);

    /*
    * Gifts item to the specified player.
    *
    * Service Name - UserInventoryManagement
    * Service Operation - GIVE_USER_ITEM_TO
    *
    * @param itemId
    * @param includeDef
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserInventoryManagement")
	static UBCUserInventoryManagementProxy *GiveUserItemTo(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId, const FString &itemId, int version, bool immediate);
    
	/*
    * Gifts item to the specified player.
    *
    * Service Name - UserInventoryManagement
    * Service Operation - PURCHASE_USER_ITEM
    *
    * @param itemId
    * @param includeDef
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserInventoryManagement")
	static UBCUserInventoryManagementProxy *PurchaseUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &defId, int quantity, const FString &shopId, bool includeDef);
   
    /*
    * Retrieves and transfers the gift item from the specified player, 
    * who must have previously called giveUserItemTo.
    *
    * Service Name - UserInventoryManagement
    * Service Operation - RECEIVE_USER_ITEM_FROM
    *
    * @param profileId
    * @param itemId
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserInventoryManagement")
	static UBCUserInventoryManagementProxy *ReceiveUserItemFrom(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId, const FString &itemId);
   
    /*
    * Allows a quantity of a specified user item to be sold. 
    * If any quantity of the user item remains, 
    * it will be returned, potentially with the associated 
    * itemDef (with language fields limited to the current 
    * or default language), along with the currency refunded 
    * and currency balances.
    *
    * Service Name - UserInventoryManagement
    * Service Operation - SELL_USER_ITEM
    *
    * @param itemId
    * @param version
    * @param quantity
    * @param shopId
    * @param includeDef
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserInventoryManagement")
	static UBCUserInventoryManagementProxy *SellUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, int version, int quantity,const FString &shopId, bool includeDef);
    
	/*
    * Updates the item data on the specified user item.
    *
    * Service Name - UserInventoryManagement
    * Service Operation - UPDATE_USER_ITEM_DATA
    *
    * @param itemId
    * @param version
    * @param newItemData
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserInventoryManagement")
	static UBCUserInventoryManagementProxy *UpdateUserItemData(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, int version, const FString &newItemData);
    
	/*
    * Uses the specified item, potentially consuming it.
    *
    * Service Name - UserInventoryManagement
    * Service Operation - USE_USER_ITEM
    *
    * @param itemId
    * @param version
    * @param newItemData
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserInventoryManagement")
	static UBCUserInventoryManagementProxy *UseUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, int version, const FString &newItemData);
};
