// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCAuthType.h"
#include "BCItemCatalogProxy.generated.h"

UCLASS(MinimalAPI)
class UBCItemCatalogProxy : public UBCBlueprintCallProxyBase
{
	GENERATED_BODY()

  public:
	UBCItemCatalogProxy(const FObjectInitializer &ObjectInitializer);

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
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|ItemCatalog")
	static UBCItemCatalogProxy *GetCatalogItemDefinition(UBrainCloudWrapper *brainCloudWrapper, const FString &defId);


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
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|ItemCatalog")
	static UBCItemCatalogProxy *GetCatalogItemsPage(UBrainCloudWrapper *brainCloudWrapper, const FString &context);

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
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|ItemCatalog")
	static UBCItemCatalogProxy *GetCatalogItemsPageOffset(UBrainCloudWrapper *brainCloudWrapper, const FString &context, int pageOffset);
};
