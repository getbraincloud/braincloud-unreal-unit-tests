// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudUserItems.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudUserItems::BrainCloudUserItems(BrainCloudClient *client) : _client(client) {};

    void BrainCloudUserItems::awardUserItem(const FString &defId, int quantity, bool includeDef, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserItemsDefId.getValue(), defId);
        message->SetNumberField(OperationParam::UserItemsQuantity.getValue(), quantity);
        message->SetBoolField(OperationParam::UserItemsIncludeDef.getValue(), includeDef);

        ServerCall *sc = new ServerCall(ServiceName::UserItems, ServiceOperation::AwardUserItem, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserItems::dropUserItem(const FString &itemId, int quantity, bool includeDef, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserItemsItemId.getValue(), itemId);
        message->SetNumberField(OperationParam::UserItemsQuantity.getValue(), quantity);
        message->SetBoolField(OperationParam::UserItemsIncludeDef.getValue(), includeDef);

        ServerCall *sc = new ServerCall(ServiceName::UserItems, ServiceOperation::DropUserItem, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserItems::getUserItemsPage(const FString &context, bool includeDef, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetObjectField(OperationParam::UserItemsContext.getValue(), JsonUtil::jsonStringToValue(context));
        message->SetBoolField(OperationParam::UserItemsIncludeDef.getValue(), includeDef);

        ServerCall *sc = new ServerCall(ServiceName::UserItems, ServiceOperation::GetUserItemsPage, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserItems::getUserItemsPageOffset(const FString &context, int pageOffest, bool includeDef, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserItemsContext.getValue(), context);
        message->SetNumberField(OperationParam::UserItemsPageOffset.getValue(), pageOffest);
        message->SetBoolField(OperationParam::UserItemsIncludeDef.getValue(), includeDef);

        ServerCall *sc = new ServerCall(ServiceName::UserItems, ServiceOperation::GetUserItemsPageOffset, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserItems::getUserItem(const FString &itemId, bool includeDef, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserItemsItemId.getValue(), itemId);
        message->SetBoolField(OperationParam::UserItemsIncludeDef.getValue(), includeDef);

        ServerCall *sc = new ServerCall(ServiceName::UserItems, ServiceOperation::GetUserItem, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserItems::giveUserItemTo(const FString &profileId, const FString &itemId, int version, int quantity, bool immediate, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserItemsProfileId.getValue(), profileId);
        message->SetStringField(OperationParam::UserItemsItemId.getValue(), itemId);
        message->SetNumberField(OperationParam::UserItemsVersion.getValue(), version);
        message->SetBoolField(OperationParam::UserItemsImmediate.getValue(), immediate);

        ServerCall *sc = new ServerCall(ServiceName::UserItems, ServiceOperation::GiveUserItemTo, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserItems::purchaseUserItem(const FString &defId, int quantity, const FString &shopId, bool includeDef, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserItemsDefId.getValue(), defId);
        message->SetNumberField(OperationParam::UserItemsQuantity.getValue(), quantity);
        message->SetStringField(OperationParam::UserItemsShopId.getValue(), shopId);
        message->SetBoolField(OperationParam::UserItemsIncludeDef.getValue(), includeDef);

        ServerCall *sc = new ServerCall(ServiceName::UserItems, ServiceOperation::PurchaseUserItem, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserItems::receiveUserItemFrom(const FString &profileId, const FString &itemId, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserItemsProfileId.getValue(), profileId);
        message->SetStringField(OperationParam::UserItemsItemId.getValue(), itemId);

        ServerCall *sc = new ServerCall(ServiceName::UserItems, ServiceOperation::ReceiveUserItemFrom, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserItems::sellUserItem(const FString &itemId, int version, int quantity, const FString &shopId, bool includeDef, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserItemsItemId.getValue(), itemId);
        message->SetNumberField(OperationParam::UserItemsVersion.getValue(), version);
        message->SetNumberField(OperationParam::UserItemsQuantity.getValue(), quantity);
        message->SetStringField(OperationParam::UserItemsShopId.getValue(), shopId);
        message->SetBoolField(OperationParam::UserItemsIncludeDef.getValue(), includeDef);

        ServerCall *sc = new ServerCall(ServiceName::UserItems, ServiceOperation::SellUserItem, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserItems::updateUserItemData(const FString &itemId, int version, const FString &newItemData, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserItemsItemId.getValue(), itemId);
        message->SetNumberField(OperationParam::UserItemsVersion.getValue(), version);
        message->SetObjectField(OperationParam::UserItemsNewItemData.getValue(), JsonUtil::jsonStringToValue(newItemData));

        ServerCall *sc = new ServerCall(ServiceName::UserItems, ServiceOperation::UpdateUserItemData, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserItems::useUserItem(const FString &itemId, int version, const FString &newItemData, bool includeDef, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserItemsItemId.getValue(), itemId);
        message->SetNumberField(OperationParam::UserItemsVersion.getValue(), version);
        message->SetObjectField(OperationParam::UserItemsNewItemData.getValue(), JsonUtil::jsonStringToValue(newItemData));
        message->SetBoolField(OperationParam::UserItemsIncludeDef.getValue(), includeDef);

        ServerCall *sc = new ServerCall(ServiceName::UserItems, ServiceOperation::UseUserItem, message, callback);
        _client->sendRequest(sc);
    }
	
	void BrainCloudUserItems::publishUserItemToBlockchain(const FString &itemId, int version, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserItemsItemId.getValue(), itemId);
        message->SetNumberField(OperationParam::UserItemsVersion.getValue(), version);

        ServerCall *sc = new ServerCall(ServiceName::UserItems, ServiceOperation::PublishUserItemToBlackchain, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserItems::refreshBlockchainUserItems(IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

        ServerCall *sc = new ServerCall(ServiceName::UserItems, ServiceOperation::RefreshBlockchainUserItems, message, callback);
        _client->sendRequest(sc);
    }

	void BrainCloudUserItems::removeUserItemFromBlockchain(const FString &itemId, int version, IServerCallback *callback)
    {
        TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
        message->SetStringField(OperationParam::UserItemsItemId.getValue(), itemId);
        message->SetNumberField(OperationParam::UserItemsVersion.getValue(), version);

        ServerCall *sc = new ServerCall(ServiceName::UserItems, ServiceOperation::RemoveUserItemFromBlockchain, message, callback);
        _client->sendRequest(sc);
    }
