// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudProduct.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

#include "braincloud/internal/StringUtil.h"

namespace BrainCloud
{
    BrainCloudProduct::BrainCloudProduct(BrainCloudClient* in_client) : m_client(in_client) { }

    void BrainCloudProduct::getCurrency(const char* in_currencyType, IServerCallback * in_callback)
    {
        Json::Value message = Json::nullValue;
        if (StringUtil::IsOptionalParameterValid(in_currencyType)) {
            message[OperationParam::ProductServiceVCId.getValue()] = in_currencyType;
        }

        ServerCall * sc = new ServerCall(ServiceName::Product, ServiceOperation::GetPlayerVC, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudProduct::awardCurrency(const char* in_currencyType, int32_t in_amount, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::ProductServiceVCId.getValue()] = in_currencyType;
        message[OperationParam::ProductServiceVCAmount.getValue()] = (Json::Int)in_amount;

        ServerCall * sc = new ServerCall(ServiceName::Product, ServiceOperation::AwardVC, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudProduct::consumeCurrency(const char* in_currencyType, int32_t in_amount, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::ProductServiceVCId.getValue()] = in_currencyType;
        message[OperationParam::ProductServiceVCAmount.getValue()] = (Json::Int)in_amount;
        ServerCall * sc = new ServerCall(ServiceName::Product, ServiceOperation::ConsumeVC, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudProduct::resetCurrency(IServerCallback * in_callback)
    {
        Json::Value message = Json::nullValue;
        ServerCall * sc = new ServerCall(ServiceName::Product, ServiceOperation::ResetPlayerVC, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudProduct::getSalesInventory(const char * in_platform, const char * in_userCurrency, IServerCallback * in_callback)
    {
        getSalesInventoryByCategory(in_platform, in_userCurrency, NULL, in_callback);
    }

    void BrainCloudProduct::getSalesInventoryByCategory(const char * in_platform, const char * in_userCurrency, const char * in_category, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::ProductServiceGetInventoryPlatform.getValue()] = in_platform;
        message[OperationParam::ProductServiceGetInventoryUserCurrency.getValue()] = in_userCurrency;

        if (StringUtil::IsOptionalParameterValid(in_category)) {
            message[OperationParam::ProductServiceGetInventoryCategory.getValue()] = in_category;
        }

        ServerCall * sc = new ServerCall(ServiceName::Product, ServiceOperation::GetInventory, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudProduct::verifyItunesReceipt(const std::string& in_base64EncReceiptData, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::ProductServiceOpCashInReceiptReceipt.getValue()] = in_base64EncReceiptData;

        ServerCall * sc = new ServerCall(ServiceName::Product, ServiceOperation::CashInReceipt, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudProduct::startSteamTransaction(const char* in_language, const char* in_itemId, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::ProductServiceLanguage.getValue()] = in_language;
        message[OperationParam::ProductServiceItemId.getValue()] = in_itemId;

        ServerCall * sc = new ServerCall(ServiceName::Product, ServiceOperation::StartSteamTransaction, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudProduct::finalizeSteamTransaction(const char* in_transId, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::ProductServiceTransId.getValue()] = in_transId;

        ServerCall * sc = new ServerCall(ServiceName::Product, ServiceOperation::FinalizeSteamTransaction, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudProduct::verifyMicrosoftReceipt(const char* in_receipt, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::ProductServiceReceipt.getValue()] = in_receipt;

        ServerCall * sc = new ServerCall(ServiceName::Product, ServiceOperation::VerifyMicrosoftReceipt, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudProduct::confirmGooglePlayPurchase(
        const char * in_orderId,
        const char * in_productId,
        const char * in_token,
        IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::ProductServiceOrderId.getValue()] = in_orderId;
        message[OperationParam::ProductServiceProductId.getValue()] = in_productId;
        message[OperationParam::ProductServiceToken.getValue()] = in_token;

        ServerCall * sc = new ServerCall(ServiceName::Product, ServiceOperation::ConfirmGooglePlayPurchase, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudProduct::getEligiblePromotions(IServerCallback * in_callback)
    {
        Json::Value message = Json::nullValue;
        ServerCall * sc = new ServerCall(ServiceName::Product, ServiceOperation::EligiblePromotions, message, in_callback);
        m_client->sendRequest(sc);
    }
}
