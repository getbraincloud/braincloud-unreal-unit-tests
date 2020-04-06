// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudItemCatalog.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudIdentity.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudItemCatalog::BrainCloudItemCatalog(BrainCloudClient *client) : _client(client){};

	void BrainCloudItemCatalog::getCatalogItemDefinition(const FString &defId, IServerCallback *callback)
	{
		TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

		message->SetStringField(OperationParam::ItemCatalogServiceDefId.getValue(), defId);
		
		ServerCall *sc = new ServerCall(ServiceName::ItemCatalog, ServiceOperation::GetCatalogItemDefinition, message, callback);
		_client->sendRequest(sc);
	}

	void BrainCloudItemCatalog::getCatalogItemsPage(const FString &context, IServerCallback *callback)
	{
		TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
		
		message->SetObjectField(OperationParam::ItemCatalogServiceContext.getValue(), JsonUtil::jsonStringToValue(context));
		
		ServerCall *sc = new ServerCall(ServiceName::ItemCatalog, ServiceOperation::GetCatalogItemsPage, message, callback);
		_client->sendRequest(sc);
	}

	void BrainCloudItemCatalog::getCatalogItemsPageOffset(const FString &context, int pageOffset, IServerCallback *callback)
	{
		TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

		message->SetStringField(OperationParam::ItemCatalogServiceContext.getValue(), context);
		message->SetNumberField(OperationParam::ItemCatalogServicePageOffset.getValue(), pageOffset);
		
		ServerCall *sc = new ServerCall(ServiceName::ItemCatalog, ServiceOperation::GetCatalogItemsPageOffset, message, callback);
		_client->sendRequest(sc);
	}

