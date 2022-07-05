// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudCustomEntity.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"
#include "IAcl.h"

BrainCloudCustomEntity::BrainCloudCustomEntity(BrainCloudClient *client) : _client(client){};

void BrainCloudCustomEntity::createEntity(const FString &entityType, const FString &jsonEntityData, IAcl *jsonEntityAcl, int64 timeToLive, bool isOwned, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::CustomEntityServiceEntityType.getValue(), entityType);
    message->SetObjectField(OperationParam::CustomEntityServiceJsonEntityData.getValue(), JsonUtil::jsonStringToValue(jsonEntityData));
    message->SetObjectField(OperationParam::CustomEntityServiceAcl.getValue(), jsonEntityAcl->toJsonObject());
    message->SetNumberField(OperationParam::CustomEntityServiceTimeToLive.getValue(), timeToLive);
    message->SetBoolField(OperationParam::CustomEntityServiceIsOwned.getValue(), isOwned);

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

void BrainCloudCustomEntity::getEntityPage(const FString &entityType, const FString &context, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::CustomEntityServiceEntityType.getValue(), entityType);
    message->SetObjectField(OperationParam::CustomEntityServiceContext.getValue(), JsonUtil::jsonStringToValue(context));

    ServerCall *sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::CustomEntityGetEntityPage, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudCustomEntity::getEntityPageOffset(const FString &entityType, const FString &context, int pageOffset, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::CustomEntityServiceEntityType.getValue(), entityType);
    message->SetStringField(OperationParam::CustomEntityServiceContext.getValue(), context);
    message->SetNumberField(OperationParam::CustomEntityServicePageOffset.getValue(), pageOffset);

    ServerCall *sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::CustomEntityGetEntityPageOffset, message, callback);
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

void BrainCloudCustomEntity::incrementData(const FString &entityType, const FString &entityId, const FString &fieldsJson, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::CustomEntityServiceEntityType.getValue(), entityType);
    message->SetStringField(OperationParam::CustomEntityServiceEntityId.getValue(), entityId);
    message->SetObjectField(OperationParam::CustomEntityServiceFieldsJson.getValue(), JsonUtil::jsonStringToValue(fieldsJson));

    ServerCall *sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::IncrementData, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudCustomEntity::getRandomEntitiesMatching(const FString &entityType, const FString &whereJson, const int64 &maxReturn, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::CustomEntityServiceEntityType.getValue(), entityType);
    message->SetObjectField(OperationParam::CustomEntityServiceWhereJson.getValue(), JsonUtil::jsonStringToValue(whereJson));
    message->SetNumberField(OperationParam::CustomEntityServiceMaxReturn.getValue(), maxReturn);

    ServerCall *sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::GetRandomEntitiesMatching, message, callback);
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

void BrainCloudCustomEntity::updateEntityFieldsSharded(const FString& entityType, const FString& entityId, int version, const FString& fieldsJson,
    const FString& shardKeyJson, IServerCallback* callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::CustomEntityServiceEntityType.getValue(), entityType);
    message->SetStringField(OperationParam::CustomEntityServiceEntityId.getValue(), entityId);
    message->SetNumberField(OperationParam::CustomEntityServiceVersion.getValue(), version);
    message->SetObjectField(OperationParam::CustomEntityServiceFieldsJson.getValue(), JsonUtil::jsonStringToValue(fieldsJson));
    message->SetObjectField(OperationParam::CustomEntityServiceShardKeyJson.getValue(), JsonUtil::jsonStringToValue(shardKeyJson));
    
    ServerCall *sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::UpdateEntityFieldsSharded, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudCustomEntity::deleteEntities(const FString &entityType, const FString &deleteCriteria, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::CustomEntityServiceEntityType.getValue(), entityType);
    message->SetObjectField(OperationParam::CustomEntityServiceDeleteCriteria.getValue(), JsonUtil::jsonStringToValue(deleteCriteria));

    ServerCall *sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::DeleteEntities, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudCustomEntity::readSingleton(const FString &entityType, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::CustomEntityServiceEntityType.getValue(), entityType);

    ServerCall *sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::ReadSingleton, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudCustomEntity::deleteSingleton(const FString &entityType, int version, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::CustomEntityServiceEntityType.getValue(), entityType);
    message->SetNumberField(OperationParam::CustomEntityServiceVersion.getValue(), version);

    ServerCall *sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::DeleteSingleton, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudCustomEntity::updateSingleton(const FString &entityType, int version, const FString &dataJson,  IAcl *jsonEntityAcl, int64 timeToLive, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::CustomEntityServiceEntityType.getValue(), entityType);
    message->SetNumberField(OperationParam::CustomEntityServiceEntityId.getValue(), version);
    message->SetObjectField(OperationParam::CustomEntityServiceDataJson.getValue(), JsonUtil::jsonStringToValue(dataJson));
    message->SetObjectField(OperationParam::CustomEntityServiceAcl.getValue(), jsonEntityAcl->toJsonObject());
    message->SetNumberField(OperationParam::CustomEntityServiceTimeToLive.getValue(), timeToLive);

    ServerCall *sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::UpdateSingleton, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudCustomEntity::updateSingletonFields(const FString &entityType, int version, const FString &fieldsJson, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::CustomEntityServiceEntityType.getValue(), entityType);
    message->SetNumberField(OperationParam::CustomEntityServiceEntityId.getValue(), version);
    message->SetObjectField(OperationParam::CustomEntityServiceFieldsJson.getValue(), JsonUtil::jsonStringToValue(fieldsJson));

    ServerCall *sc = new ServerCall(ServiceName::CustomEntity, ServiceOperation::UpdateSingletonFields, message, callback);
    _client->sendRequest(sc);
}
