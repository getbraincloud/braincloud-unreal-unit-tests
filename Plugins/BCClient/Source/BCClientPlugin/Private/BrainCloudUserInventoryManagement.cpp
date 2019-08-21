// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudUserInventoryManagement.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudUserInventoryManagement::BrainCloudUserInventoryManagement(BrainCloudClient *client) : _client(client) {};

    void BrainCloudUserInventoryManagement::awardUserItem(const FString &defId, int quantity, bool includeDef, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserInventoryManagementDefId.getValue(), defId);
        message->SetNumberField(OperationParam::UserInventoryManagementQuantity.getValue(), quantity);
        message->SetBoolField(OperationParam::UserInventoryManagementIncludeDef.getValue(), includeDef);

        ServerCall *sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::AwardUserItem, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserInventoryManagement::dropUserItem(const FString &itemId, int quantity, bool includeDef, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserInventoryManagementItemId.getValue(), itemId);
        message->SetNumberField(OperationParam::UserInventoryManagementQuantity.getValue(), quantity);
        message->SetBoolField(OperationParam::UserInventoryManagementIncludeDef.getValue(), includeDef);

        ServerCall *sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::DropUserItem, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserInventoryManagement::getUserInventory(const FString &criteria, bool includeDef, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserInventoryManagementCriteria.getValue(), criteria);
        message->SetBoolField(OperationParam::UserInventoryManagementIncludeDef.getValue(), includeDef);

        ServerCall *sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::GetUserInventory, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserInventoryManagement::getUserInventoryPage(const FString &context, bool includeDef, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserInventoryManagementContext.getValue(), context);
        message->SetBoolField(OperationParam::UserInventoryManagementIncludeDef.getValue(), includeDef);

        ServerCall *sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::GetUserInventoryPage, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserInventoryManagement::getUserInventoryPageOffset(const FString &context, int pageOffest, bool includeDef, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserInventoryManagementCriteria.getValue(), context);
        message->SetNumberField(OperationParam::UserInventoryManagementPageOffset.getValue(), pageOffest);
        message->SetBoolField(OperationParam::UserInventoryManagementIncludeDef.getValue(), includeDef);

        ServerCall *sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::GetUserInventoryPageOffset, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserInventoryManagement::getUserItem(const FString &itemId, bool includeDef, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserInventoryManagementItemId.getValue(), itemId);
        message->SetBoolField(OperationParam::UserInventoryManagementIncludeDef.getValue(), includeDef);

        ServerCall *sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::GetUserItem, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserInventoryManagement::giveUserItemTo(const FString &profileId, const FString &itemId, int version, bool immediate, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserInventoryManagementProfileId.getValue(), profileId);
        message->SetStringField(OperationParam::UserInventoryManagementItemId.getValue(), itemId);
        message->SetNumberField(OperationParam::UserInventoryManagementVersion.getValue(), version);
        message->SetBoolField(OperationParam::UserInventoryManagementImmediate.getValue(), immediate);

        ServerCall *sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::GiveUserItemTo, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserInventoryManagement::purchaseUserItem(const FString &defId, int quantity, const FString &shopId, bool includeDef, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserInventoryManagementDefId.getValue(), defId);
        message->SetNumberField(OperationParam::UserInventoryManagementQuantity.getValue(), quantity);
        message->SetStringField(OperationParam::UserInventoryManagementShopId.getValue(), shopId);
        message->SetBoolField(OperationParam::UserInventoryManagementIncludeDef.getValue(), includeDef);

        ServerCall *sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::PurchaseUserItem, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserInventoryManagement::receiveUserItemFrom(const FString &profileId, const FString &itemId, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserInventoryManagementProfileId.getValue(), profileId);
        message->SetStringField(OperationParam::UserInventoryManagementItemId.getValue(), itemId);

        ServerCall *sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::ReceiveUserItemFrom, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserInventoryManagement::sellUserItem(const FString &itemId, int version, int quantity, const FString &shopId, bool includeDef, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserInventoryManagementItemId.getValue(), itemId);
        message->SetNumberField(OperationParam::UserInventoryManagementVersion.getValue(), version);
        message->SetNumberField(OperationParam::UserInventoryManagementQuantity.getValue(), quantity);
        message->SetStringField(OperationParam::UserInventoryManagementShopId.getValue(), shopId);
        message->SetBoolField(OperationParam::UserInventoryManagementIncludeDef.getValue(), includeDef);

        ServerCall *sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::SellUserItem, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserInventoryManagement::updateUserItemData(const FString &itemId, int version, const FString &newItemData, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserInventoryManagementItemId.getValue(), itemId);
        message->SetNumberField(OperationParam::UserInventoryManagementVersion.getValue(), version);
        message->SetStringField(OperationParam::UserInventoryManagementNewItemData.getValue(), newItemData);

        ServerCall *sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::UpdateUserItemData, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserInventoryManagement::useUserItem(const FString &itemId, int version, const FString &newItemData, bool includeDef, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserInventoryManagementItemId.getValue(), itemId);
        message->SetNumberField(OperationParam::UserInventoryManagementVersion.getValue(), version);
        message->SetStringField(OperationParam::UserInventoryManagementNewItemData.getValue(), newItemData);
        message->SetBoolField(OperationParam::UserInventoryManagementIncludeDef.getValue(), includeDef);

        ServerCall *sc = new ServerCall(ServiceName::UserInventoryManagement, ServiceOperation::UseUserItem, message, callback);
        _client->sendRequest(sc);
    }
	
