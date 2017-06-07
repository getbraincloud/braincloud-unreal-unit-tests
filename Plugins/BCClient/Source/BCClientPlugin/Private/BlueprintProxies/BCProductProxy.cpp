// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCProductProxy.h"

UBCProductProxy::UBCProductProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCProductProxy* UBCProductProxy::GetCurrency(const FString& currencyType)
{
    UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
    BrainCloudClient::getInstance()->getProductService()->getCurrency(currencyType, Proxy);
    return Proxy;
}

UBCProductProxy* UBCProductProxy::AwardCurrency(const FString& currencyType, int32 amount)
{
	UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
	BrainCloudClient::getInstance()->getProductService()->awardCurrency(currencyType, amount, Proxy);
	return Proxy;
}

UBCProductProxy* UBCProductProxy::ConsumeCurrency(const FString& currencyType, int32 amount)
{
	UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
	BrainCloudClient::getInstance()->getProductService()->consumeCurrency(currencyType, amount, Proxy);
	return Proxy;
}

UBCProductProxy* UBCProductProxy::ResetCurrency()
{
	UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
	BrainCloudClient::getInstance()->getProductService()->resetCurrency(Proxy);
	return Proxy;
}

UBCProductProxy* UBCProductProxy::GetSalesInventory(const FString& platform, const FString& userCurrency)
{
    UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
    BrainCloudClient::getInstance()->getProductService()->getSalesInventory(platform, userCurrency, Proxy);
    return Proxy;
}

UBCProductProxy* UBCProductProxy::GetSalesInventoryByCategory(const FString& platform, const FString& userCurrency, const FString& category)
{
    UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
    BrainCloudClient::getInstance()->getProductService()->getSalesInventoryByCategory(platform, userCurrency, category, Proxy);
    return Proxy;
}

UBCProductProxy* UBCProductProxy::VerifyItunesReceipt(const FString& base64EncReceiptData)
{
    UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
    BrainCloudClient::getInstance()->getProductService()->verifyItunesReceipt(base64EncReceiptData, Proxy);
    return Proxy;
}

UBCProductProxy* UBCProductProxy::StartSteamTransaction(const FString& language, const FString& itemId)
{
    UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
    BrainCloudClient::getInstance()->getProductService()->startSteamTransaction(language, itemId, Proxy);
    return Proxy;
}

UBCProductProxy* UBCProductProxy::FinalizeSteamTransaction(const FString& transId)
{
    UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
    BrainCloudClient::getInstance()->getProductService()->finalizeSteamTransaction(transId, Proxy);
    return Proxy;
}

UBCProductProxy* UBCProductProxy::VerifyMicrosoftReceipt(const FString& receipt)
{
    UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
    BrainCloudClient::getInstance()->getProductService()->verifyMicrosoftReceipt(receipt, Proxy);
    return Proxy;
}

UBCProductProxy* UBCProductProxy::ConfirmGooglePlayPurchase(const FString& orderId, const FString& productId, const FString& token)
{
    UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
    BrainCloudClient::getInstance()->getProductService()->confirmGooglePlayPurchase(orderId, productId, token, Proxy);
    return Proxy;
}

UBCProductProxy* UBCProductProxy::GetEligiblePromotions()
{
    UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
    BrainCloudClient::getInstance()->getProductService()->getEligiblePromotions(Proxy);
    return Proxy;
}

//callbacks
void UBCProductProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
}

void UBCProductProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
}

