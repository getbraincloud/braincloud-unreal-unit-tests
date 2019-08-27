// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudUserInventoryManagement.h"

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
	BrainCloudUserInventoryManagement::BrainCloudUserInventoryManagement(BrainCloudClient* in_client) : m_client(in_client) { }
	
  void BrainCloudUserInventoryManagement::awardUserItem(const std::string& in_defId, int32_t in_quantity, bool in_includeDef, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserInventoryManagementServiceDefId.getValue()] = in_defId;
        message[OperationParam::UserInventoryManagementServiceQuantity.getValue()] = in_quantity;
        message[OperationParam::UserInventoryManagementServiceIncludeDef.getValue()] = in_includeDef;

        ServerCall * sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::AwardUserItem, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserInventoryManagement::dropUserItem(const std::string& in_itemId, int32_t in_quantity, bool in_includeDef, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserInventoryManagementServiceItemId.getValue()] = in_itemId;
        message[OperationParam::UserInventoryManagementServiceQuantity.getValue()] = in_quantity;
        message[OperationParam::UserInventoryManagementServiceIncludeDef.getValue()] = in_includeDef;

        ServerCall * sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::DropUserItem, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserInventoryManagement::getUserInventory(const std::string& in_criteria, bool in_includeDef, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserInventoryManagementServiceContext.getValue()] = JsonUtil::jsonStringToValue(in_criteria.c_str());
        message[OperationParam::UserInventoryManagementServiceIncludeDef.getValue()] = in_includeDef;

        ServerCall * sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::GetUserInventory, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserInventoryManagement::getUserInventoryPage(const std::string& in_context, bool in_includeDef, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserInventoryManagementServiceContext.getValue()] = JsonUtil::jsonStringToValue(in_context.c_str());
        message[OperationParam::UserInventoryManagementServiceIncludeDef.getValue()] = in_includeDef;

        ServerCall * sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::GetUserInventoryPage, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserInventoryManagement::getUserInventoryPageOffset(const std::string& in_context, int32_t in_pageOffset, bool in_includeDef, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserInventoryManagementServiceContext.getValue()] = in_context;
        message[OperationParam::UserInventoryManagementServicePageOffset.getValue()] = in_pageOffset;
        message[OperationParam::UserInventoryManagementServiceIncludeDef.getValue()] = in_includeDef;

        ServerCall * sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::GetUserInventoryPageOffset, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserInventoryManagement::getUserItem(const std::string& in_itemId, bool in_includeDef, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserInventoryManagementServiceItemId.getValue()] = in_itemId;
        message[OperationParam::UserInventoryManagementServiceIncludeDef.getValue()] = in_includeDef;

        ServerCall * sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::GetUserItem, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserInventoryManagement::giveUserItemTo(const std::string& in_profileId, const std::string& in_itemId, int32_t in_version, bool in_immediate, IServerCallback * in_callback)
    {
        Json::Value message;
         message[OperationParam::UserInventoryManagementServiceProfileId.getValue()] = in_profileId;
          message[OperationParam::UserInventoryManagementServiceItemId.getValue()] = in_itemId;
        message[OperationParam::UserInventoryManagementServiceVersion.getValue()] = in_version;
        message[OperationParam::UserInventoryManagementServiceImmediate.getValue()] = in_immediate;

        ServerCall * sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::GiveUserItemTo, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserInventoryManagement::purchaseUserItem(const std::string& in_defId, int32_t in_quantity, const std::string& in_shopId, bool in_includeDef, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserInventoryManagementServiceDefId.getValue()] = in_defId;
        message[OperationParam::UserInventoryManagementServiceQuantity.getValue()] = in_quantity;
        message[OperationParam::UserInventoryManagementServiceShopId.getValue()] = in_shopId;
        message[OperationParam::UserInventoryManagementServiceIncludeDef.getValue()] = in_includeDef;

        ServerCall * sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::PurchaseUserItem, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserInventoryManagement::receiveUserItemFrom(const std::string& in_profileId, const std::string& in_itemId, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserInventoryManagementServiceProfileId.getValue()] = in_profileId;
        message[OperationParam::UserInventoryManagementServiceItemId.getValue()] = in_itemId;

        ServerCall * sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::ReceiveUserItemFrom, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserInventoryManagement::sellUserItem(const std::string& in_itemId, int32_t in_version, int32_t in_quantity, const std::string& in_shopId, bool in_includeDef, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserInventoryManagementServiceItemId.getValue()] = in_itemId;
        message[OperationParam::UserInventoryManagementServiceVersion.getValue()] = in_version;
        message[OperationParam::UserInventoryManagementServiceQuantity.getValue()] = in_quantity;
        message[OperationParam::UserInventoryManagementServiceShopId.getValue()] = in_shopId;
        message[OperationParam::UserInventoryManagementServiceIncludeDef.getValue()] = in_includeDef;

        ServerCall * sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::SellUserItem, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserInventoryManagement::updateUserItemData(const std::string& in_itemId, int32_t in_version, const std::string&  in_newItemData, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserInventoryManagementServiceItemId.getValue()] = in_itemId;
        message[OperationParam::UserInventoryManagementServiceVersion.getValue()] = in_version;
        message[OperationParam::UserInventoryManagementServiceNewItemData.getValue()] = JsonUtil::jsonStringToValue(in_newItemData.c_str());

        ServerCall * sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::UpdateUserItemData, message, in_callback);
        m_client->sendRequest(sc);
    }

    void BrainCloudUserInventoryManagement::useUserItem(const std::string& in_itemId, int32_t in_version, const std::string&  in_newItemData, bool in_includeDef, IServerCallback * in_callback)
    {
        Json::Value message;
        message[OperationParam::UserInventoryManagementServiceItemId.getValue()] = in_itemId;
        message[OperationParam::UserInventoryManagementServiceVersion.getValue()] = in_version;
        message[OperationParam::UserInventoryManagementServiceNewItemData.getValue()] = JsonUtil::jsonStringToValue(in_newItemData.c_str());
        message[OperationParam::UserInventoryManagementServiceIncludeDef.getValue()] = in_includeDef;

        ServerCall * sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::UseUserItem, message, in_callback);
        m_client->sendRequest(sc);
    }
}
