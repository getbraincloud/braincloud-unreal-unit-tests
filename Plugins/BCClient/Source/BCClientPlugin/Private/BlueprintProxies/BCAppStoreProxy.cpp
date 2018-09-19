// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCAppStoreProxy.h"

UBCAppStoreProxy::UBCAppStoreProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCAppStoreProxy* UBCAppStoreProxy::VerifyPurchase(UBrainCloudWrapper *brainCloudWrapper, const FString &storeId, const FString &jsonReceiptData)
{
    UBCAppStoreProxy* Proxy = NewObject<UBCAppStoreProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getAppStoreService()->verifyPurchase(storeId, jsonReceiptData, Proxy);
    return Proxy;
}

UBCAppStoreProxy* UBCAppStoreProxy::GetEligiblePromotions(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCAppStoreProxy* Proxy = NewObject<UBCAppStoreProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getAppStoreService()->getEligiblePromotions(Proxy);
    return Proxy;
}

UBCAppStoreProxy* UBCAppStoreProxy::GetSalesInventory(UBrainCloudWrapper *brainCloudWrapper, const FString &storeId, const FString &userCurrency)
{
    UBCAppStoreProxy* Proxy = NewObject<UBCAppStoreProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getAppStoreService()->getSalesInventory(storeId, userCurrency, Proxy);
    return Proxy;
}

UBCAppStoreProxy* UBCAppStoreProxy::GetSalesInventoryByCategory(UBrainCloudWrapper *brainCloudWrapper, const FString &storeId, const FString &userCurrency, const FString& category)
{
    UBCAppStoreProxy* Proxy = NewObject<UBCAppStoreProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getAppStoreService()->getSalesInventoryByCategory(storeId, userCurrency, category, Proxy);
    return Proxy;
}

UBCAppStoreProxy* UBCAppStoreProxy::StartPurchase(UBrainCloudWrapper *brainCloudWrapper, const FString &storeId, const FString &jsonPurchaseData)
{
    UBCAppStoreProxy* Proxy = NewObject<UBCAppStoreProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getAppStoreService()->startPurchase(storeId, jsonPurchaseData, Proxy);
    return Proxy;
}

UBCAppStoreProxy* UBCAppStoreProxy::FinalizePurchase(UBrainCloudWrapper *brainCloudWrapper, const FString &storeId, const FString &transactionId, const FString& jsonTransactionData)
{
    UBCAppStoreProxy* Proxy = NewObject<UBCAppStoreProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getAppStoreService()->finalizePurchase(storeId, transactionId, jsonTransactionData, Proxy);
    return Proxy;
}
