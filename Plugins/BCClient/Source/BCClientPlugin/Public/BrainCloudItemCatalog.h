// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCAuthType.h"

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudItemCatalog
{
  public:
	BrainCloudItemCatalog(BrainCloudClient *client);

	/*
	 * Reads an existing item definition from the 
     * server, with language fields limited to the
     * current or default language.
	 *
	 * Service Name - ItemCatalog
	 * Service Operation - GET_CATALOG_ITEM_DEFINITION
	 *
	 * @param defId
	 * @param callback The method to be invoked when the server response is received
	 */
	void getCatalogItemDefinition(const FString &defId, IServerCallback *callback = nullptr);

	/*
	 * Retrieves page of catalog items from the server, 
     * with language fields limited to the text for the 
     * current or default language.
	 *
	 * Service Name - ItemCatalog
	 * Service Operation - GET_CATALOG_ITEMS_PAGE
	 *
	 * @param context
	 * @param callback The method to be invoked when the server response is received
	 */
	void getCatalogItemsPage(const FString &context, IServerCallback *callback = nullptr);

	/*
     *Gets the page of catalog items from the 
     *server based on the encoded context and 
     *specified page offset, with language fields 
     *limited to the text for the current or default 
     *language.
	 *
	 * Service Name - ItemCatalog
	 * Service Operation - GET_CATALOG_ITEMS_PAGE_OFFSET
	 *
	 * @param context
	 * @param callback The method to be invoked when the server response is received
	 */
	void getCatalogItemsPageOffset(const FString &context, int pageOffset, IServerCallback *callback = nullptr);

	private:
	BrainCloudClient *_client = nullptr;
};
