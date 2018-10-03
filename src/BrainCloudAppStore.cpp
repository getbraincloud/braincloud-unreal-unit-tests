// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudAppStore.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

#include "braincloud/internal/StringUtil.h"
#include "braincloud/internal/JsonUtil.h"

namespace BrainCloud
{
    BrainCloudAppStore::BrainCloudAppStore(BrainCloudClient* in_client) : m_client(in_client) { }

    void BrainCloudAppStore::verifyPurchase(const std::string& in_storeId, const std::string& in_jsonReceiptData, IServerCallback* in_callback )
    {
        Json::Value message;
        message[OperationParam::AppStoreStoreId.getValue()] = in_storeId;
        message[OperationParam::AppStoreReceiptData.getValue()] = JsonUtil::jsonStringToValue(in_jsonReceiptData.c_str());

        ServerCall* sc = new ServerCall(ServiceName::AppStore, ServiceOperation::AppStoreVerifyPurchase, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudAppStore::getEligiblePromotions(IServerCallback* in_callback)
    {
        Json::Value message;

        ServerCall* sc = new ServerCall(ServiceName::AppStore, ServiceOperation::AppStoreGetEligiblePromotions, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudAppStore::getSalesInventory(const std::string& in_storeId, const std::string& in_userCurrency, IServerCallback* in_callback)
    {
        getSalesInventoryByCategory(in_storeId, in_userCurrency, "", in_callback);
    }

    void BrainCloudAppStore::getSalesInventoryByCategory(const std::string& in_storeId, const std::string& in_userCurrency, const std::string& in_category, IServerCallback* in_callback)
    {
        Json::Value message;
        message[OperationParam::AppStoreStoreId.getValue()] = in_storeId;
        if (!in_category.empty())
        {
            message[OperationParam::AppStoreCategory.getValue()] = in_category;
        }

        Json::Value priceInfoCriteria;
        if (!in_userCurrency.empty())
        {
            priceInfoCriteria[OperationParam::AppStoreUserCurrency.getValue()] = in_userCurrency;
        }
        message[OperationParam::AppStorePriceInfoCriteria.getValue()] = priceInfoCriteria;

        ServerCall* sc = new ServerCall(ServiceName::AppStore, ServiceOperation::AppStoreGetSalesInventory, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudAppStore::startPurchase(const std::string& in_storeId, const std::string& in_jsonPurchaseData, IServerCallback* in_callback)
    {
        Json::Value message;
        message[OperationParam::AppStoreStoreId.getValue()] = in_storeId;
        message[OperationParam::AppStorePurchaseData.getValue()] = JsonUtil::jsonStringToValue(in_jsonPurchaseData.c_str());

        ServerCall* sc = new ServerCall(ServiceName::AppStore, ServiceOperation::AppStoreStartPurchase, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudAppStore::finalizePurchase(const std::string& in_storeId, const std::string& in_transactionId, const std::string& in_jsonTransactionData, IServerCallback* in_callback)
    {
        Json::Value message;
        message[OperationParam::AppStoreStoreId.getValue()] = in_storeId;
        message[OperationParam::AppStoreTransactionId.getValue()] = in_transactionId;
        message[OperationParam::AppStoreTransactionData.getValue()] = JsonUtil::jsonStringToValue(in_jsonTransactionData.c_str());

        ServerCall* sc = new ServerCall(ServiceName::AppStore, ServiceOperation::AppStoreFinalizePurchase, message, in_callback);
        m_client->sendRequest(sc);
    }
}
