// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <string>

namespace BrainCloud
{
	class IServerCallback;
	class BrainCloudClient;
	class AuthenticationType;

	class BrainCloudUserInventoryManagement
	{
	public:
		BrainCloudUserInventoryManagement(BrainCloudClient* in_client);
	/**
	 * Allows item(s) to be awarded to a user without collecting
	 *  the purchase amount. If includeDef is true, response 
	 * includes associated itemDef with language fields limited
	 *  to the current or default language.
	 *
	 * Service Name - userInventoryManagement
	 * Service Operation - AWARD_USER_ITEM
	 *
	 * @param defId 
	 * @param quantity
	 * @param includeDef 
	 */
        void awardUserItem(const std::string& in_defId, int32_t in_quantity, bool in_includeDef, IServerCallback * in_callback = NULL);

	/**
	 * Allows a quantity of a specified user item to be dropped, 
	 * without any recovery of the money paid for the item. 
	 * If any quantity of the user item remains, it will be returned,
	 * potentially with the associated itemDef (with language fields 
	 * limited to the current or default language).
	 *
	 * Service Name - userInventoryManagement
	 * Service Operation - DROP_USER_ITEM
	 *
	 * @param defId 
	 * @param quantity
	 * @param includeDef 
	 */
        void dropUserItem(const std::string& in_defId, int32_t in_quantity, bool in_includeDef, IServerCallback * in_callback = NULL);

	/**
	 * Retrieves the user's inventory from the 
	 * server (or inventory specified by criteria). 
	 * If includeDef is true, response includes associated 
	 * itemDef with each user item, with language fields 
	 * limited to the current or default language.
	 *
	 * Service Name - userInventoryManagement
	 * Service Operation - GET_USER_INVENTORY
	 *
	 * @param criteria 
	 * @param includeDef 
	 */
        void getUserInventory(const std::string& in_criteria, bool in_includeDef, IServerCallback * in_callback = NULL);
	
    /**
	 * Retrieves the page of user's inventory from the server 
	 * based on the context. If includeDef is true, response
	 *  includes associated itemDef with each user item, with 
	 * language fields limited to the current or default language.
	 *
	 * Service Name - userInventoryManagement
	 * Service Operation - GET_USER_INVENTORY_PAGE
	 *
	 * @param context
	 * @param includeDef 
	 */
        void getUserInventoryPage(const std::string& in_context, bool in_includeDef, IServerCallback * in_callback = NULL);

	/**
	 * Retrieves the page of user's inventory from the server
	 *  based on the encoded context. If includeDef is true, 
	 * response includes associated itemDef with each user item, 
	 * with language fields limited to the current or default
	 * language.
	 *
	 * Service Name - userInventoryManagement
	 * Service Operation - GET_USER_INVENTORY_PAGE_OFFSET
	 *
	 * @param context
	 * @param pageOffset
	 * @param includeDef 
	 */
        void getUserInventoryPageOffset(const std::string& in_context, int32_t in_pageOffset, bool in_includeDef, IServerCallback * in_callback = NULL);

	/**
	 * Retrieves the identified user item from the server. 
	 * If includeDef is true, response includes associated
	 * itemDef with language fields limited to the current 
	 * or default language.
	 *
	 * Service Name - userInventoryManagement
	 * Service Operation - GET_USER_ITEM
	 *
	 * @param itemId
	 * @param includeDef 
	 * @param callback The method to be invoked when the server response is received
	 */
        void getUserItem(const std::string& in_itemId, bool in_includeDef, IServerCallback * in_callback = NULL);

	/**
	 * Gifts item to the specified player.
	 *
	 * Service Name - userInventoryManagement
	 * Service Operation - GIVE_USER_ITEM_TO
	 *
	 * @param profileId
	 * @param itemId
	 * @param version
	 * @param immediate 
	 */
        void giveUserItemTo(const std::string& in_profileId, const std::string& in_itemId, int32_t in_version, bool in_immediate, IServerCallback * in_callback = NULL);

	/**
	 * Retrieves the identified user item from the server. 
	 * If includeDef is true, response includes associated
	 * itemDef with language fields limited to the current 
	 * or default language.
	 *
	 * Service Name - userInventoryManagement
	 * Service Operation - PURCHASE_USER_ITEM
	 *
	 * @param defId
	 * @param quantity
	 * @param shopId
	 * @param includeDef 
	 */
        void purchaseUserItem(const std::string& in_defId, int32_t in_quantity, const std::string& in_shopId, bool in_includeDef, IServerCallback * in_callback = NULL);

	/**
	 * Retrieves and transfers the gift item from 
	 * the specified player, who must have previously 
	 * called giveUserItemTo.
	 *
	 * Service Name - userInventoryManagement
	 * Service Operation - RECEVIE_USER_ITEM_FROM
	 *
	 * @param profileId
	 * @param itemId
	 */
        void receiveUserItemFrom(const std::string& in_profileId, const std::string& in_itemId, IServerCallback * in_callback = NULL);

	/**
	 * Allows a quantity of a specified user item to be sold. 
	 * If any quantity of the user item remains, it will be returned, 
	 * potentially with the associated itemDef (with language fields 
	 * limited to the current or default language), along with the 
	 * currency refunded and currency balances.
	 *
	 * Service Name - userInventoryManagement
	 * Service Operation - SELL_USER_ITEM
	 *
	 * @param itemId
	 * @param version
	 * @param quantity
	 * @param shopId
	 * @param includeDef 
	 */
        void sellUserItem(const std::string& in_itemId, int32_t in_version, int32_t in_quantity, const std::string& in_shopId, bool in_includeDef, IServerCallback * in_callback = NULL);

	/**
	 * Updates the item data on the specified user item.
	 *
	 * Service Name - userInventoryManagement
	 * Service Operation - UPDATE_USER_ITEM_DATA
	 *
	 * @param itemId
	 * @param version
	 * @param newItemData
	 */
        void updateUserItemData(const std::string& in_itemId, int32_t in_version, const std::string&  in_newItemData, IServerCallback * in_callback = NULL);

	/**
	 * Uses the specified item, potentially consuming it.
	 *
	 * Service Name - userInventoryManagement
	 * Service Operation - USE_USER_ITEM
	 *
	 * @param itemId
	 * @param version
	 * @param newItemData
	 * @param includeDef 
	 */
        void useUserItem(const std::string& in_itemId, int32_t in_version, const std::string&  in_newItemData, bool in_includeDef, IServerCallback * in_callback = NULL);

			/**
	 * Publishes the specified item to the item management attached blockchain. Results are reported asynchronously via an RTT event.
	 *
	 * Service Name - userInventoryManagement
	 * Service Operation - PUBLISH_USER_ITEM_TO_BLOCKCHAIN
	 *
	 * @param itemId
	 * @param version
	 * @param newItemData
	 */
        void publishUserItemToBlockchain(const std::string& in_itemId, int32_t in_version, IServerCallback * in_callback = NULL);

	/**
	 * Syncs the caller's user items with the item management attached blockchain. Results are reported asynchronously via an RTT event.
	 *
	 * Service Name - userInventoryManagement
	 * Service Operation - REFRESH_BLOCKCHAIN_USER_ITEMS
	 */
        void refreshBlockchainUserItems(IServerCallback * in_callback = NULL);

    private:
        BrainCloudClient * m_client;
    };
}
