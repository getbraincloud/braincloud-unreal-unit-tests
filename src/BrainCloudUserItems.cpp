// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudUserItems.h"

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
	BrainCloudUserItems::BrainCloudUserItems(BrainCloudClient* in_client) : m_client(in_client) { }
	
  void BrainCloudUserItems::awardUserItem(const std::string& in_defId, int32_t in_quantity, bool in_includeDef, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserItemsServiceDefId.getValue()] = in_defId;
        message[OperationParam::UserItemsServiceQuantity.getValue()] = in_quantity;
        message[OperationParam::UserItemsServiceIncludeDef.getValue()] = in_includeDef;

        ServerCall * sc = new ServerCall(ServiceName::UserItems, ServiceOperation::AwardUserItem, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserItems::dropUserItem(const std::string& in_itemId, int32_t in_quantity, bool in_includeDef, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserItemsServiceItemId.getValue()] = in_itemId;
        message[OperationParam::UserItemsServiceQuantity.getValue()] = in_quantity;
        message[OperationParam::UserItemsServiceIncludeDef.getValue()] = in_includeDef;

        ServerCall * sc = new ServerCall(ServiceName::UserItems, ServiceOperation::DropUserItem, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserItems::getUserItemsPage(const std::string& in_context, bool in_includeDef, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserItemsServiceContext.getValue()] = JsonUtil::jsonStringToValue(in_context.c_str());
        message[OperationParam::UserItemsServiceIncludeDef.getValue()] = in_includeDef;

        ServerCall * sc = new ServerCall(ServiceName::UserItems, ServiceOperation::GetUserItemsPage, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserItems::getUserItemsPageOffset(const std::string& in_context, int32_t in_pageOffset, bool in_includeDef, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserItemsServiceContext.getValue()] = in_context;
        message[OperationParam::UserItemsServicePageOffset.getValue()] = in_pageOffset;
        message[OperationParam::UserItemsServiceIncludeDef.getValue()] = in_includeDef;

        ServerCall * sc = new ServerCall(ServiceName::UserItems, ServiceOperation::GetUserItemsPageOffset, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserItems::getUserItem(const std::string& in_itemId, bool in_includeDef, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserItemsServiceItemId.getValue()] = in_itemId;
        message[OperationParam::UserItemsServiceIncludeDef.getValue()] = in_includeDef;

        ServerCall * sc = new ServerCall(ServiceName::UserItems, ServiceOperation::GetUserItem, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserItems::giveUserItemTo(const std::string& in_profileId, const std::string& in_itemId, int32_t in_version, int32_t in_quantity, bool in_immediate, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserItemsServiceProfileId.getValue()] = in_profileId;
        message[OperationParam::UserItemsServiceItemId.getValue()] = in_itemId;
        message[OperationParam::UserItemsServiceVersion.getValue()] = in_version;
        message[OperationParam::UserItemsServiceQuantity.getValue()] = in_quantity;
        message[OperationParam::UserItemsServiceImmediate.getValue()] = in_immediate;

        ServerCall * sc = new ServerCall(ServiceName::UserItems, ServiceOperation::GiveUserItemTo, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserItems::purchaseUserItem(const std::string& in_defId, int32_t in_quantity, const std::string& in_shopId, bool in_includeDef, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserItemsServiceDefId.getValue()] = in_defId;
        message[OperationParam::UserItemsServiceQuantity.getValue()] = in_quantity;
        message[OperationParam::UserItemsServiceShopId.getValue()] = in_shopId;
        message[OperationParam::UserItemsServiceIncludeDef.getValue()] = in_includeDef;

        ServerCall * sc = new ServerCall(ServiceName::UserItems, ServiceOperation::PurchaseUserItem, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserItems::receiveUserItemFrom(const std::string& in_profileId, const std::string& in_itemId, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserItemsServiceProfileId.getValue()] = in_profileId;
        message[OperationParam::UserItemsServiceItemId.getValue()] = in_itemId;

        ServerCall * sc = new ServerCall(ServiceName::UserItems, ServiceOperation::ReceiveUserItemFrom, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserItems::sellUserItem(const std::string& in_itemId, int32_t in_version, int32_t in_quantity, const std::string& in_shopId, bool in_includeDef, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserItemsServiceItemId.getValue()] = in_itemId;
        message[OperationParam::UserItemsServiceVersion.getValue()] = in_version;
        message[OperationParam::UserItemsServiceQuantity.getValue()] = in_quantity;
        message[OperationParam::UserItemsServiceShopId.getValue()] = in_shopId;
        message[OperationParam::UserItemsServiceIncludeDef.getValue()] = in_includeDef;

        ServerCall * sc = new ServerCall(ServiceName::UserItems, ServiceOperation::SellUserItem, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserItems::updateUserItemData(const std::string& in_itemId, int32_t in_version, const std::string&  in_newItemData, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserItemsServiceItemId.getValue()] = in_itemId;
        message[OperationParam::UserItemsServiceVersion.getValue()] = in_version;
        message[OperationParam::UserItemsServiceNewItemData.getValue()] = JsonUtil::jsonStringToValue(in_newItemData.c_str());

        ServerCall * sc = new ServerCall(ServiceName::UserItems, ServiceOperation::UpdateUserItemData, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserItems::useUserItem(const std::string& in_itemId, int32_t in_version, const std::string&  in_newItemData, bool in_includeDef, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserItemsServiceItemId.getValue()] = in_itemId;
        message[OperationParam::UserItemsServiceVersion.getValue()] = in_version;
        message[OperationParam::UserItemsServiceNewItemData.getValue()] = JsonUtil::jsonStringToValue(in_newItemData.c_str());
        message[OperationParam::UserItemsServiceIncludeDef.getValue()] = in_includeDef;

        ServerCall * sc = new ServerCall(ServiceName::UserItems, ServiceOperation::UseUserItem, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserItems::publishUserItemToBlockchain(const std::string& in_itemId, int32_t in_version, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserItemsServiceItemId.getValue()] = in_itemId;
        message[OperationParam::UserItemsServiceVersion.getValue()] = in_version;

        ServerCall * sc = new ServerCall(ServiceName::UserItems, ServiceOperation::PublishUserItemToBlockchain, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserItems::refreshBlockchainUserItems(IServerCallback * in_callback)
    {
        Json::Value message;
        ServerCall * sc = new ServerCall(ServiceName::UserItems, ServiceOperation::RefreshBlockchainUserItems, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserItems::removeUserItemFromBlockchain(const std::string& in_itemId, int32_t in_version, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserItemsServiceItemId.getValue()] = in_itemId;
        message[OperationParam::UserItemsServiceVersion.getValue()] = in_version;

        ServerCall * sc = new ServerCall(ServiceName::UserItems, ServiceOperation::RemoveUserItemFromBlockchain, message, in_callback);
        m_client->sendRequest(sc);
    }
}
