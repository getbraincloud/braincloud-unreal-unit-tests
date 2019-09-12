// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudCustomEntity.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"
#include "IAcl.h"

BrainCloudCustomEntity::BrainCloudCustomEntity(BrainCloudClient *client) : _client(client){};

void BrainCloudCustomEntity::createEntity(const FString &entityType, const FString &jsonEntityData, IAcl *jsonEntityAcl, int64 timeToLive, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::CustomEntityServiceEntityType.getValue(), entityType);
    message->SetObjectField(OperationParam::CustomEntityServiceJsonEntityData.getValue(), JsonUtil::jsonStringToValue(jsonEntityData));
    message->SetObjectField(OperationParam::CustomEntityServiceAcl.getValue(), jsonEntityAcl->toJsonObject());
    message->SetNumberField(OperationParam::CustomEntityServiceTimeToLive.getValue(), timeToLive);

    ServerCall *sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::CreateEntity, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudCustomEntity::deleteEntity(const FString &entityType, const FString &entityId, int version, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::CustomEntityServiceEntityType.getValue(), entityType);
    message->SetStringField(OperationParam::CustomEntityServiceEntityId.getValue(), entityId);
    message->SetNumberField(OperationParam::CustomEntityServiceVersion.getValue(), version);

    ServerCall *sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::DeleteEntity, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudCustomEntity::getCount(const FString &entityType, const FString &whereJson, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::CustomEntityServiceEntityType.getValue(), entityType);
    message->SetObjectField(OperationParam::CustomEntityServiceWhereJson.getValue(), JsonUtil::jsonStringToValue(whereJson));

    ServerCall *sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::GetCount, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudCustomEntity::getPage(const FString &entityType, int rowsPerPage, const FString &searchJson, const FString &sortJson, bool doCount, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::CustomEntityServiceEntityType.getValue(), entityType);
    message->SetNumberField(OperationParam::CustomEntityServiceRowsPerPage.getValue(), rowsPerPage);
    message->SetObjectField(OperationParam::CustomEntityServiceSearchJson.getValue(), JsonUtil::jsonStringToValue(searchJson));
    message->SetObjectField(OperationParam::CustomEntityServiceSortJson.getValue(), JsonUtil::jsonStringToValue(sortJson));
    message->SetBoolField(OperationParam::CustomEntityServiceDoCount.getValue(), doCount);

    ServerCall *sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::CustomEntityGetPage, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudCustomEntity::getPageOffset(const FString &entityType, const FString &context, int pageOffset, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::CustomEntityServiceEntityType.getValue(), entityType);
    message->SetStringField(OperationParam::CustomEntityServiceContext.getValue(), context);
    message->SetNumberField(OperationParam::CustomEntityServicePageOffset.getValue(), pageOffset);

    ServerCall *sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::CustomEntityGetPageOffset, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudCustomEntity::readEntity(const FString &entityType, const FString &entityId, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::CustomEntityServiceEntityType.getValue(), entityType);
    message->SetStringField(OperationParam::CustomEntityServiceEntityId.getValue(), entityId);

    ServerCall *sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::ReadEntity, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudCustomEntity::updateEntity(const FString &entityType, const FString &entityId, int version, const FString &dataJson, IAcl *jsonEntityAcl, int64 timeToLive, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::CustomEntityServiceEntityType.getValue(), entityType);
    message->SetStringField(OperationParam::CustomEntityServiceEntityId.getValue(), entityId);
    message->SetNumberField(OperationParam::CustomEntityServiceVersion.getValue(), version);
    message->SetObjectField(OperationParam::CustomEntityServiceDataJson.getValue(), JsonUtil::jsonStringToValue(dataJson));
    message->SetObjectField(OperationParam::CustomEntityServiceAcl.getValue(), jsonEntityAcl->toJsonObject());
    message->SetNumberField(OperationParam::CustomEntityServiceTimeToLive.getValue(), timeToLive);

    ServerCall *sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::UpdateEntity, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudCustomEntity::updateEntityFields(const FString &entityType, const FString &entityId, int version, const FString &fieldsJson, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::CustomEntityServiceEntityType.getValue(), entityType);
    message->SetStringField(OperationParam::CustomEntityServiceEntityId.getValue(), entityId);
    message->SetNumberField(OperationParam::CustomEntityServiceVersion.getValue(), version);
    message->SetObjectField(OperationParam::CustomEntityServiceFieldsJson.getValue(), JsonUtil::jsonStringToValue(fieldsJson));

    ServerCall *sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::UpdateEntityFields, message, callback);
    _client->sendRequest(sc);
}
