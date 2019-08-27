// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudItemCatalog.h"

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
	BrainCloudItemCatalog::BrainCloudItemCatalog(BrainCloudClient* in_client) : m_client(in_client) { }
	
	void BrainCloudItemCatalog::getCatalogItemDefinition(const std::string& in_defId, IServerCallback * in_callback)
    {
		Json::Value message;
		message[OperationParam::ItemCatalogServiceDefId.getValue()] = in_defId;

		ServerCall* sc = new ServerCall(ServiceName::ItemCatalog, ServiceOperation::GetCatalogItemDefinition, message, in_callback);
		m_client->sendRequest(sc);
    }

    void BrainCloudItemCatalog::getCatalogItemsPage(const std::string& in_context, IServerCallback * in_callback)
    {
		Json::Value message;
		message[OperationParam::ItemCatalogServiceContext.getValue()] = JsonUtil::jsonStringToValue(in_context.c_str());

		ServerCall* sc = new ServerCall(ServiceName::ItemCatalog, ServiceOperation::GetCatalogItemsPage, message, in_callback);
		m_client->sendRequest(sc);
    }

    void BrainCloudItemCatalog::getCatalogItemsPageOffset(const std::string& in_context, int32_t in_pageOffset, IServerCallback * in_callback)
    {
		Json::Value message;
		message[OperationParam::ItemCatalogServiceContext.getValue()] = in_context;
		message[OperationParam::ItemCatalogServicePageOffset.getValue()] = in_pageOffset;

		ServerCall* sc = new ServerCall(ServiceName::ItemCatalog, ServiceOperation::GetCatalogItemsPageOffset, message, in_callback);
		m_client->sendRequest(sc);
    }
}
