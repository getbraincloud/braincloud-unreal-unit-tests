// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCUserItemsProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCUserItemsProxy::UBCUserItemsProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

	UBCUserItemsProxy *UBCUserItemsProxy::AwardUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &defId, int quantity, bool includeDef)
	{
		UBCUserItemsProxy *Proxy = NewObject<UBCUserItemsProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserItemsService()->awardUserItem(defId, quantity, includeDef, Proxy);
		return Proxy;
	}

	UBCUserItemsProxy *UBCUserItemsProxy::DropUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &defId, int quantity, bool includeDef)
	{
		UBCUserItemsProxy *Proxy = NewObject<UBCUserItemsProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserItemsService()->dropUserItem(defId, quantity, includeDef, Proxy);
		return Proxy;
	}

	UBCUserItemsProxy *UBCUserItemsProxy::GetUserItemsPage(UBrainCloudWrapper *brainCloudWrapper, const FString &context, bool includeDef)
	{
		UBCUserItemsProxy *Proxy = NewObject<UBCUserItemsProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserItemsService()->getUserItemsPage(context, includeDef, Proxy);
		return Proxy;
	}

	UBCUserItemsProxy *UBCUserItemsProxy::GetUserItemsPageOffset(UBrainCloudWrapper *brainCloudWrapper, const FString &context, int pageOffset, bool includeDef)
	{
		UBCUserItemsProxy *Proxy = NewObject<UBCUserItemsProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserItemsService()->getUserItemsPageOffset(context, pageOffset, includeDef, Proxy);
		return Proxy;
	}

	UBCUserItemsProxy *UBCUserItemsProxy::GetUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, bool includeDef)
	{
		UBCUserItemsProxy *Proxy = NewObject<UBCUserItemsProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserItemsService()->getUserItem(itemId, includeDef, Proxy);
		return Proxy;
	}

	UBCUserItemsProxy *UBCUserItemsProxy::GiveUserItemTo(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId, const FString &itemId, int version, int quantity, bool immediate)
	{
		UBCUserItemsProxy *Proxy = NewObject<UBCUserItemsProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserItemsService()->giveUserItemTo(profileId, itemId, version, quantity, immediate, Proxy);
		return Proxy;
	}

	UBCUserItemsProxy *UBCUserItemsProxy::PurchaseUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &defId, int quantity, const FString &shopId, bool includeDef)
	{
		UBCUserItemsProxy *Proxy = NewObject<UBCUserItemsProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserItemsService()->purchaseUserItem(defId, quantity, shopId, includeDef, Proxy);
		return Proxy;
	}

	UBCUserItemsProxy *UBCUserItemsProxy::ReceiveUserItemFrom(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId, const FString &itemId)
	{
		UBCUserItemsProxy *Proxy = NewObject<UBCUserItemsProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserItemsService()->receiveUserItemFrom(profileId, itemId, Proxy);
		return Proxy;
	}

	UBCUserItemsProxy *UBCUserItemsProxy::SellUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, int version, int quantity, const FString &shopId, bool includeDef)
	{
		UBCUserItemsProxy *Proxy = NewObject<UBCUserItemsProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserItemsService()->sellUserItem(itemId, version, quantity, shopId, includeDef, Proxy);
		return Proxy;
	}

	UBCUserItemsProxy *UBCUserItemsProxy::UpdateUserItemData(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, int version, const FString &newItemData)
	{
		UBCUserItemsProxy *Proxy = NewObject<UBCUserItemsProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserItemsService()->updateUserItemData(itemId, version, newItemData, Proxy);
		return Proxy;
	}

	UBCUserItemsProxy *UBCUserItemsProxy::UseUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, int version, const FString &newItemData, bool includeDef)
	{
		UBCUserItemsProxy *Proxy = NewObject<UBCUserItemsProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserItemsService()->useUserItem(itemId, version, newItemData, includeDef, Proxy);
		return Proxy;
	}

	UBCUserItemsProxy *UBCUserItemsProxy::PublishUserItemToBlockchain(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, int version)
	{
		UBCUserItemsProxy *Proxy = NewObject<UBCUserItemsProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserItemsService()->publishUserItemToBlockchain(itemId, version, Proxy);
		return Proxy;
	}

	UBCUserItemsProxy *UBCUserItemsProxy::RefreshBlockchainUserItems(UBrainCloudWrapper *brainCloudWrapper)
	{
		UBCUserItemsProxy *Proxy = NewObject<UBCUserItemsProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserItemsService()->refreshBlockchainUserItems(Proxy);
		return Proxy;
	}

	UBCUserItemsProxy *UBCUserItemsProxy::RemoveUserItemFromBlockchain(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, int version)
	{
		UBCUserItemsProxy *Proxy = NewObject<UBCUserItemsProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserItemsService()->removeUserItemFromBlockchain(itemId, version, Proxy);
		return Proxy;
	}
	