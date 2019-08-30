// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BCUserInventoryManagementProxy.h"
#include "BrainCloudWrapper.h"

UBCUserInventoryManagementProxy::UBCUserInventoryManagementProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

	UBCUserInventoryManagementProxy *UBCUserInventoryManagementProxy::AwardUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &defId, int quantity, bool includeDef)
	{
		UBCUserInventoryManagementProxy *Proxy = NewObject<UBCUserInventoryManagementProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserInventoryManagementService()->awardUserItem(defId, quantity, includeDef, Proxy);
		return Proxy;
	}

	UBCUserInventoryManagementProxy *UBCUserInventoryManagementProxy::DropUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &defId, int quantity, bool includeDef)
	{
		UBCUserInventoryManagementProxy *Proxy = NewObject<UBCUserInventoryManagementProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserInventoryManagementService()->dropUserItem(defId, quantity, includeDef, Proxy);
		return Proxy;
	}

	UBCUserInventoryManagementProxy *UBCUserInventoryManagementProxy::GetUserInventory(UBrainCloudWrapper *brainCloudWrapper, const FString &criteria, bool includeDef)
	{
		UBCUserInventoryManagementProxy *Proxy = NewObject<UBCUserInventoryManagementProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserInventoryManagementService()->getUserInventory(criteria, includeDef, Proxy);
		return Proxy;
	}

	UBCUserInventoryManagementProxy *UBCUserInventoryManagementProxy::GetUserInventoryPage(UBrainCloudWrapper *brainCloudWrapper, const FString &context, bool includeDef)
	{
		UBCUserInventoryManagementProxy *Proxy = NewObject<UBCUserInventoryManagementProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserInventoryManagementService()->getUserInventoryPage(context, includeDef, Proxy);
		return Proxy;
	}

	UBCUserInventoryManagementProxy *UBCUserInventoryManagementProxy::GetUserInventoryPageOffset(UBrainCloudWrapper *brainCloudWrapper, const FString &context, int pageOffset, bool includeDef)
	{
		UBCUserInventoryManagementProxy *Proxy = NewObject<UBCUserInventoryManagementProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserInventoryManagementService()->getUserInventoryPageOffset(context, pageOffset, includeDef, Proxy);
		return Proxy;
	}

	UBCUserInventoryManagementProxy *UBCUserInventoryManagementProxy::GetUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, bool includeDef)
	{
		UBCUserInventoryManagementProxy *Proxy = NewObject<UBCUserInventoryManagementProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserInventoryManagementService()->getUserItem(itemId, includeDef, Proxy);
		return Proxy;
	}

	UBCUserInventoryManagementProxy *UBCUserInventoryManagementProxy::GiveUserItemTo(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId, const FString &itemId, int version, bool immediate)
	{
		UBCUserInventoryManagementProxy *Proxy = NewObject<UBCUserInventoryManagementProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserInventoryManagementService()->giveUserItemTo(profileId, itemId, version, immediate, Proxy);
		return Proxy;
	}

	UBCUserInventoryManagementProxy *UBCUserInventoryManagementProxy::PurchaseUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &defId, int quantity, const FString &shopId, bool includeDef)
	{
		UBCUserInventoryManagementProxy *Proxy = NewObject<UBCUserInventoryManagementProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserInventoryManagementService()->purchaseUserItem(defId, quantity, shopId, includeDef, Proxy);
		return Proxy;
	}

	UBCUserInventoryManagementProxy *UBCUserInventoryManagementProxy::ReceiveUserItemFrom(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId, const FString &itemId)
	{
		UBCUserInventoryManagementProxy *Proxy = NewObject<UBCUserInventoryManagementProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserInventoryManagementService()->receiveUserItemFrom(profileId, itemId, Proxy);
		return Proxy;
	}

	UBCUserInventoryManagementProxy *UBCUserInventoryManagementProxy::SellUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, int version, int quantity, const FString &shopId, bool includeDef)
	{
		UBCUserInventoryManagementProxy *Proxy = NewObject<UBCUserInventoryManagementProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserInventoryManagementService()->sellUserItem(itemId, version, quantity, shopId, includeDef, Proxy);
		return Proxy;
	}

	UBCUserInventoryManagementProxy *UBCUserInventoryManagementProxy::UpdateUserItemData(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, int version, const FString &newItemData)
	{
		UBCUserInventoryManagementProxy *Proxy = NewObject<UBCUserInventoryManagementProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserInventoryManagementService()->updateUserItemData(itemId, version, newItemData, Proxy);
		return Proxy;
	}

	UBCUserInventoryManagementProxy *UBCUserInventoryManagementProxy::UseUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, int version, const FString &newItemData, bool includeDef)
	{
		UBCUserInventoryManagementProxy *Proxy = NewObject<UBCUserInventoryManagementProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserInventoryManagementService()->useUserItem(itemId, version, newItemData, includeDef, Proxy);
		return Proxy;
	}

	UBCUserInventoryManagementProxy *UBCUserInventoryManagementProxy::PublishUserItemToBlockchain(UBrainCloudWrapper *brainCloudWrapper, const FString &itemId, int version)
	{
		UBCUserInventoryManagementProxy *Proxy = NewObject<UBCUserInventoryManagementProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserInventoryManagementService()->publishUserItemToBlockchain(itemId, version, Proxy);
		return Proxy;
	}

	UBCUserInventoryManagementProxy *UBCUserInventoryManagementProxy::RefreshBlockchainUserItems(UBrainCloudWrapper *brainCloudWrapper)
	{
		UBCUserInventoryManagementProxy *Proxy = NewObject<UBCUserInventoryManagementProxy>();
		UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUserInventoryManagementService()->refreshBlockchainUserItems(Proxy);
		return Proxy;
	}