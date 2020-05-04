// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCItemCatalogProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCItemCatalogProxy::UBCItemCatalogProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

	UBCItemCatalogProxy *UBCItemCatalogProxy::GetCatalogItemDefinition(UBrainCloudWrapper *brainCloudWrapper, const FString &defId)
	{
		UBCItemCatalogProxy *Proxy = NewObject<UBCItemCatalogProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getItemCatalogService()->getCatalogItemDefinition(defId, Proxy);
		return Proxy;
	}

	UBCItemCatalogProxy *UBCItemCatalogProxy::GetCatalogItemsPage(UBrainCloudWrapper *brainCloudWrapper, const FString &context)
	{
		UBCItemCatalogProxy *Proxy = NewObject<UBCItemCatalogProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getItemCatalogService()->getCatalogItemsPage(context, Proxy);
		return Proxy;
	}

	UBCItemCatalogProxy *UBCItemCatalogProxy::GetCatalogItemsPageOffset(UBrainCloudWrapper *brainCloudWrapper, const FString &context, int pageOffset)
	{
		UBCItemCatalogProxy *Proxy = NewObject<UBCItemCatalogProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getItemCatalogService()->getCatalogItemsPageOffset(context, pageOffset, Proxy);
		return Proxy;
	}

