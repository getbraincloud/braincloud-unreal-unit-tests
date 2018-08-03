// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloudActor.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCProductProxy.h"

UBCProductProxy::UBCProductProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCProductProxy* UBCProductProxy::GetCurrency(ABrainCloudActor *brainCloud, const FString& currencyType)
{
    UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getProductService()->getCurrency(currencyType, Proxy);
    return Proxy;
}

UBCProductProxy* UBCProductProxy::AwardCurrency(ABrainCloudActor *brainCloud, const FString& currencyType, int32 amount)
{
	UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getProductService()->awardCurrency(currencyType, amount, Proxy);
	return Proxy;
}

UBCProductProxy* UBCProductProxy::ConsumeCurrency(ABrainCloudActor *brainCloud, const FString& currencyType, int32 amount)
{
	UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getProductService()->consumeCurrency(currencyType, amount, Proxy);
	return Proxy;
}

UBCProductProxy* UBCProductProxy::ResetCurrency(ABrainCloudActor *brainCloud)
{
	UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getProductService()->resetCurrency(Proxy);
	return Proxy;
}

UBCProductProxy* UBCProductProxy::GetSalesInventory(ABrainCloudActor *brainCloud, const FString& platform, const FString& userCurrency)
{
    UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getProductService()->getSalesInventory(platform, userCurrency, Proxy);
    return Proxy;
}

UBCProductProxy* UBCProductProxy::GetSalesInventoryByCategory(ABrainCloudActor *brainCloud, const FString& platform, const FString& userCurrency, const FString& category)
{
    UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getProductService()->getSalesInventoryByCategory(platform, userCurrency, category, Proxy);
    return Proxy;
}

UBCProductProxy* UBCProductProxy::VerifyItunesReceipt(ABrainCloudActor *brainCloud, const FString& base64EncReceiptData)
{
    UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getProductService()->verifyItunesReceipt(base64EncReceiptData, Proxy);
    return Proxy;
}

UBCProductProxy* UBCProductProxy::StartSteamTransaction(ABrainCloudActor *brainCloud, const FString& language, const FString& itemId)
{
    UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getProductService()->startSteamTransaction(language, itemId, Proxy);
    return Proxy;
}

UBCProductProxy* UBCProductProxy::FinalizeSteamTransaction(ABrainCloudActor *brainCloud, const FString& transId)
{
    UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getProductService()->finalizeSteamTransaction(transId, Proxy);
    return Proxy;
}

UBCProductProxy* UBCProductProxy::VerifyMicrosoftReceipt(ABrainCloudActor *brainCloud, const FString& receipt)
{
    UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getProductService()->verifyMicrosoftReceipt(receipt, Proxy);
    return Proxy;
}

UBCProductProxy* UBCProductProxy::ConfirmGooglePlayPurchase(ABrainCloudActor *brainCloud, const FString& orderId, const FString& productId, const FString& token)
{
    UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getProductService()->confirmGooglePlayPurchase(orderId, productId, token, Proxy);
    return Proxy;
}

UBCProductProxy* UBCProductProxy::GetEligiblePromotions(ABrainCloudActor *brainCloud)
{
    UBCProductProxy* Proxy = NewObject<UBCProductProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getProductService()->getEligiblePromotions(Proxy);
    return Proxy;
}

//callbacks
void UBCProductProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCProductProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

