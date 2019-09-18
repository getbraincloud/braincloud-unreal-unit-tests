// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <string>
#include "braincloud/BrainCloudTypes.h"

namespace BrainCloud
{
	class IServerCallback;
	class BrainCloudClient;
	class AuthenticationType;

	class BrainCloudItemCatalog
	{
	public:
		BrainCloudItemCatalog(BrainCloudClient* in_client);
    /**
	 * Reads an existing item definition from the server, with language fields
	 * limited to the current or default language
	 *
	 * Service Name - itemCatalog
	 * Service Operation - GET_CATALOG_ITEM_DEFINITION
	 *
	 * @param defId
	 */
        void getCatalogItemDefinition(const std::string& in_defId, IServerCallback * in_callback = NULL);


	/**
	 * Retrieve page of catalog items from the server, with language fields limited to the 
	 * text for the current or default language.
	 *
	 * Service Name - itemCatalog
	 * Service Operation - GET_CATALOG_ITEMS_PAGE
	 *
	 * @param context
	 */
        void getCatalogItemsPage(const std::string& in_context, IServerCallback * in_callback = NULL);


	/**
	 * Gets the page of catalog items from the server based ont he encoded 
	 * context and specified page offset, with language fields limited to the 
	 * text fir the current or default language
	 *
	 * Service Name - itemCatalog
	 * Service Operation - GET_CATALOG_ITEMS_PAGE_OFFSET
	 *
	 * @param context
	 * @param pageOffset
	 */
        void getCatalogItemsPageOffset(const std::string& in_context, int32_t in_pageOffset, IServerCallback * in_callback = NULL);

    private:
        BrainCloudClient * m_client;
    };
}
