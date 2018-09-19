// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudAppStore.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudAppStore::BrainCloudAppStore(BrainCloudClient* client) : _client(client) {};

void BrainCloudAppStore::verifyPurchase(const FString& in_storeId, const FString& in_jsonReceiptData, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::StoreId.getValue(), in_storeId);
    message->SetStringField(OperationParam::JsonReceiptData.getValue(), in_jsonReceiptData);

    ServerCall * sc = new ServerCall(ServiceName::AppStore, ServiceOperation::VerifyPurchase, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudAppStore::getEligiblePromotions(IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    ServerCall * sc = new ServerCall(ServiceName::AppStore, ServiceOperation::GetEligiblePromotions, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudAppStore::getSalesInventory(const FString& in_storeId, const FString& in_userCurrency, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::StoreId.getValue(), in_storeId);
    message->SetStringField(OperationParam::UserCurrency.getValue(), in_userCurrency);

    ServerCall * sc = new ServerCall(ServiceName::AppStore, ServiceOperation::GetSalesInventory, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudAppStore::getSalesInventoryByCategory(const FString& in_storeId, const FString& in_userCurrency, const FString& in_category, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::StoreId.getValue(), in_storeId);
    message->SetStringField(OperationParam::UserCurrency.getValue(), in_userCurrency);
    message->SetStringField(OperationParam::Category.getValue(), in_category);

    ServerCall * sc = new ServerCall(ServiceName::AppStore, ServiceOperation::GetSalesInventoryByCategory, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudAppStore::startPurchase(const FString& in_storeId, const FString& in_jsonPurchaseData, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::StoreId.getValue(), in_storeId);
    message->SetStringField(OperationParam::JsonPurchaseData.getValue(), in_jsonPurchaseData);

    ServerCall * sc = new ServerCall(ServiceName::AppStore, ServiceOperation::StartPurchase, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudAppStore::finalizePurchase(const FString& in_storeId, const FString& in_transactionId, const FString& in_jsonTransactionData, IServerCallback * callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::StoreId.getValue(), in_storeId);
    message->SetStringField(OperationParam::TransactionId.getValue(), in_transactionId);
    message->SetStringField(OperationParam::JsonTransactionData.getValue(), in_jsonTransactionData);

    ServerCall * sc = new ServerCall(ServiceName::AppStore, ServiceOperation::FinalizePurchase, message, callback);
    _client->sendRequest(sc);
}
