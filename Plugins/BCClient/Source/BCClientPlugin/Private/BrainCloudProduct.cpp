// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudProduct.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudProduct::BrainCloudProduct(BrainCloudClient* client) : _client(client) {};

void BrainCloudProduct::getCurrency(const FString& currencyType, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    if (OperationParam::isOptionalParamValid(currencyType)) {
        message->SetStringField(OperationParam::ProductServiceVCId.getValue(), currencyType);
    }

    ServerCall * sc = new ServerCall(ServiceName::Product, ServiceOperation::GetPlayerVC, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudProduct::awardCurrency(const FString& currencyType, int32 amount, IServerCallback * callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::ProductServiceVCId.getValue(), currencyType);
	message->SetNumberField(OperationParam::ProductServiceVCAmount.getValue(), amount);

	ServerCall * sc = new ServerCall(ServiceName::Product, ServiceOperation::AwardVC, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudProduct::consumeCurrency(const FString& currencyType, int32 amount, IServerCallback * callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::ProductServiceVCId.getValue(), currencyType);
	message->SetNumberField(OperationParam::ProductServiceVCAmount.getValue(), amount);
	ServerCall * sc = new ServerCall(ServiceName::Product, ServiceOperation::ConsumeVC, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudProduct::resetCurrency(IServerCallback * callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	ServerCall * sc = new ServerCall(ServiceName::Product, ServiceOperation::ResetPlayerVC, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudProduct::getSalesInventory(const FString& platform, const FString& userCurrency, IServerCallback * callback)
{
    getSalesInventoryByCategory(platform, userCurrency, "", callback);
}

void BrainCloudProduct::getSalesInventoryByCategory(const FString& platform, const FString& userCurrency, const FString& category, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ProductServiceGetInventoryPlatform.getValue(), platform);
    message->SetStringField(OperationParam::ProductServiceGetInventoryUserCurrency.getValue(), userCurrency);

    if (OperationParam::isOptionalParamValid(category)) {
        message->SetStringField(OperationParam::ProductServiceGetInventoryCategory.getValue(), category);
    }

    ServerCall * sc = new ServerCall(ServiceName::Product, ServiceOperation::GetInventory, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudProduct::verifyItunesReceipt(const FString& base64EncReceiptData, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ProductServiceOpCashInReceiptReceipt.getValue(), base64EncReceiptData);

    ServerCall * sc = new ServerCall(ServiceName::Product, ServiceOperation::CashInReceipt, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudProduct::startSteamTransaction(const FString& language, const FString& itemId, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ProductServiceLanguage.getValue(), language);
    message->SetStringField(OperationParam::ProductServiceItemId.getValue(), itemId);

    ServerCall * sc = new ServerCall(ServiceName::Product, ServiceOperation::StartSteamTransaction, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudProduct::finalizeSteamTransaction(const FString& transId, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ProductServiceTransId.getValue(), transId);

    ServerCall * sc = new ServerCall(ServiceName::Product, ServiceOperation::FinalizeSteamTransaction, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudProduct::verifyMicrosoftReceipt(const FString& receipt, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ProductServiceReceipt.getValue(), receipt);

    ServerCall * sc = new ServerCall(ServiceName::Product, ServiceOperation::VerifyMicrosoftReceipt, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudProduct::confirmGooglePlayPurchase(const FString& orderId, const FString& productId, const FString& token, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ProductServiceOrderId.getValue(), orderId);
    message->SetStringField(OperationParam::ProductServiceProductId.getValue(), productId);
    message->SetStringField(OperationParam::ProductServiceToken.getValue(), token);

    ServerCall * sc = new ServerCall(ServiceName::Product, ServiceOperation::ConfirmGooglePlayPurchase, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudProduct::getEligiblePromotions(IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    ServerCall * sc = new ServerCall(ServiceName::Product, ServiceOperation::EligiblePromotions, message, callback);
    _client->sendRequest(sc);
}
