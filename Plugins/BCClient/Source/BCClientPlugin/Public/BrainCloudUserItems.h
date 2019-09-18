// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudUserItems
{
  public:
    BrainCloudUserItems(BrainCloudClient *client);

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
	void awardUserItem(const FString &defId, int quantity, bool includeDef, IServerCallback *callback = nullptr);

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
	void dropUserItem(const FString &itemId, int quantity, bool includeDef, IServerCallback *callback = nullptr);

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
	void getUserItemsPage(const FString &context, bool includeDef, IServerCallback *callback = nullptr);

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
	void getUserItemsPageOffset(const FString &context, int pageOffest, bool includeDef, IServerCallback *callback = nullptr);

    /*
    * Retrieves the identified user item from the server.
    * If includeDef is true, response includes associated
    * itemDef with language fields limited to the current 
    * or default language.
    *
    * Service Name - UserIItems
    * Service Operation - GET_USER_ITEM
    *
    * @param itemId
    * @param includeDef
    * @param callback The method to be invoked when the server response is received
    */
	void getUserItem(const FString &itemId, bool includeDef, IServerCallback *callback = nullptr);

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
	void giveUserItemTo(const FString &profileId, const FString &itemId, int version, int quantity, bool immediate, IServerCallback *callback = nullptr);

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
	void purchaseUserItem(const FString &defId, int quantity, const FString &shopId, bool includeDef, IServerCallback *callback = nullptr);

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
	void receiveUserItemFrom(const FString &profileId, const FString &itemId, IServerCallback *callback = nullptr);

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
	void sellUserItem(const FString &itemId, int version, int quantity, const FString &shopId, bool includeDef, IServerCallback *callback = nullptr);

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
	void updateUserItemData(const FString &itemId, int version, const FString &newItemData, IServerCallback *callback = nullptr);

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
	void useUserItem(const FString &itemId, int version, const FString &newItemData, bool includeDef, IServerCallback *callback = nullptr);

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
	void publishUserItemToBlockchain(const FString &itemId, int version, IServerCallback *callback = nullptr);

    /*
    * Syncs the caller's user items with the item management attached blockchain. Results are reported asynchronously via an RTT event.
    *
    * Service Name - UserItems
    * Service Operation - REFRESH_BLOCKCHAIN_USER_ITEMS
    *
    * @param callback The method to be invoked when the server response is received
    */
	void refreshBlockchainUserItems(IServerCallback *callback = nullptr);

    /*
    * Removes the specified item from the item management attached blockchain. Results are reported asynchronously via an RTT event.    *
    * Service Name - UserItems
    * Service Operation - REMOVE_USER_ITEM_FROM_BLOCKCHAIN
    *
    * @param itemId
    * @param version
    * @param callback The method to be invoked when the server response is received
    */
	void removeUserItemFromBlockchain(const FString &itemId, int version, IServerCallback *callback = nullptr);

  private:
	BrainCloudClient *_client = nullptr;
};
