// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudAppStore.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudAppStore::BrainCloudAppStore(BrainCloudClient *client) : _client(client){};

void BrainCloudAppStore::verifyPurchase(const FString &in_storeId, const FString &in_jsonReceiptData, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::AppStoreId.getValue(), in_storeId);
    message->SetObjectField(OperationParam::AppStoreJsonReceiptData.getValue(), JsonUtil::jsonStringToValue(in_jsonReceiptData));

    ServerCall *sc = new ServerCall(ServiceName::AppStore, ServiceOperation::VerifyPurchase, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudAppStore::getEligiblePromotions(IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    ServerCall *sc = new ServerCall(ServiceName::AppStore, ServiceOperation::GetEligiblePromotions, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudAppStore::getSalesInventory(const FString &in_storeId, const FString &in_userCurrency, IServerCallback *callback)
{
    getSalesInventoryByCategory(in_storeId, in_userCurrency, "", callback);
}

void BrainCloudAppStore::getSalesInventoryByCategory(const FString &in_storeId, const FString &in_userCurrency, const FString &in_category, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::AppStoreId.getValue(), in_storeId);
    if (!in_category.IsEmpty())
    {
        message->SetStringField(OperationParam::AppStoreCategory.getValue(), in_category);
    }

    TSharedRef<FJsonObject> priceInfoCriteria = MakeShareable(new FJsonObject());
    if (!in_userCurrency.IsEmpty())
    {
        priceInfoCriteria->SetStringField(OperationParam::AppStoreUserCurrency.getValue(), in_userCurrency);
    }
    message->SetObjectField(OperationParam::AppStorePriceInfoCriteria.getValue(), priceInfoCriteria);

    ServerCall *sc = new ServerCall(ServiceName::AppStore, ServiceOperation::GetSalesInventory, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudAppStore::startPurchase(const FString &in_storeId, const FString &in_jsonPurchaseData, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::AppStoreId.getValue(), in_storeId);
    message->SetObjectField(OperationParam::AppStoreJsonPurchaseData.getValue(), JsonUtil::jsonStringToValue(in_jsonPurchaseData));

    ServerCall *sc = new ServerCall(ServiceName::AppStore, ServiceOperation::StartPurchase, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudAppStore::finalizePurchase(const FString &in_storeId, const FString &in_transactionId, const FString &in_jsonTransactionData, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::AppStoreId.getValue(), in_storeId);
    message->SetStringField(OperationParam::AppStoreTransactionId.getValue(), in_transactionId);
    message->SetObjectField(OperationParam::AppStoreJsonTransactionData.getValue(), JsonUtil::jsonStringToValue(in_jsonTransactionData));

    ServerCall *sc = new ServerCall(ServiceName::AppStore, ServiceOperation::FinalizePurchase, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudAppStore::refreshPromotions(IServerCallback* callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    ServerCall *sc = new ServerCall(ServiceName::AppStore, ServiceOperation::RefreshPromotions, message, callback);
    _client->sendRequest(sc);
}
