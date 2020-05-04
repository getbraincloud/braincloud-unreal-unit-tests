// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCProductProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCProductProxy::UBCProductProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCProductProxy *UBCProductProxy::GetCurrency(UBrainCloudWrapper *brainCloudWrapper, const FString &currencyType)
{
    UBCProductProxy *Proxy = NewObject<UBCProductProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getProductService()->getCurrency(currencyType, Proxy);
    return Proxy;
}

UBCProductProxy *UBCProductProxy::AwardCurrency(UBrainCloudWrapper *brainCloudWrapper, const FString &currencyType, int32 amount)
{
    UBCProductProxy *Proxy = NewObject<UBCProductProxy>();
#pragma warning(suppress : 4996)
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getProductService()->awardCurrency(currencyType, amount, Proxy);
    return Proxy;
}

UBCProductProxy *UBCProductProxy::ConsumeCurrency(UBrainCloudWrapper *brainCloudWrapper, const FString &currencyType, int32 amount)
{
    UBCProductProxy *Proxy = NewObject<UBCProductProxy>();
#pragma warning(suppress : 4996)
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getProductService()->consumeCurrency(currencyType, amount, Proxy);
    return Proxy;
}

UBCProductProxy *UBCProductProxy::ResetCurrency(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCProductProxy *Proxy = NewObject<UBCProductProxy>();

#pragma warning(suppress : 4996)
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getProductService()->resetCurrency(Proxy);
    return Proxy;
}

UBCProductProxy *UBCProductProxy::GetSalesInventory(UBrainCloudWrapper *brainCloudWrapper, const FString &platform, const FString &userCurrency)
{
    UBCProductProxy *Proxy = NewObject<UBCProductProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getProductService()->getSalesInventory(platform, userCurrency, Proxy);
    return Proxy;
}

UBCProductProxy *UBCProductProxy::GetSalesInventoryByCategory(UBrainCloudWrapper *brainCloudWrapper, const FString &platform, const FString &userCurrency, const FString &category)
{
    UBCProductProxy *Proxy = NewObject<UBCProductProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getProductService()->getSalesInventoryByCategory(platform, userCurrency, category, Proxy);
    return Proxy;
}

UBCProductProxy *UBCProductProxy::VerifyItunesReceipt(UBrainCloudWrapper *brainCloudWrapper, const FString &base64EncReceiptData)
{
    UBCProductProxy *Proxy = NewObject<UBCProductProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getProductService()->verifyItunesReceipt(base64EncReceiptData, Proxy);
    return Proxy;
}

UBCProductProxy *UBCProductProxy::StartSteamTransaction(UBrainCloudWrapper *brainCloudWrapper, const FString &language, const FString &itemId)
{
    UBCProductProxy *Proxy = NewObject<UBCProductProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getProductService()->startSteamTransaction(language, itemId, Proxy);
    return Proxy;
}

UBCProductProxy *UBCProductProxy::FinalizeSteamTransaction(UBrainCloudWrapper *brainCloudWrapper, const FString &transId)
{
    UBCProductProxy *Proxy = NewObject<UBCProductProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getProductService()->finalizeSteamTransaction(transId, Proxy);
    return Proxy;
}

UBCProductProxy *UBCProductProxy::VerifyMicrosoftReceipt(UBrainCloudWrapper *brainCloudWrapper, const FString &receipt)
{
    UBCProductProxy *Proxy = NewObject<UBCProductProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getProductService()->verifyMicrosoftReceipt(receipt, Proxy);
    return Proxy;
}

UBCProductProxy *UBCProductProxy::ConfirmGooglePlayPurchase(UBrainCloudWrapper *brainCloudWrapper, const FString &orderId, const FString &productId, const FString &token)
{
    UBCProductProxy *Proxy = NewObject<UBCProductProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getProductService()->confirmGooglePlayPurchase(orderId, productId, token, Proxy);
    return Proxy;
}

UBCProductProxy *UBCProductProxy::GetEligiblePromotions(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCProductProxy *Proxy = NewObject<UBCProductProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getProductService()->getEligiblePromotions(Proxy);
    return Proxy;
}
