// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudEntity.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"
#include "IAcl.h"

BrainCloudEntity::BrainCloudEntity(BrainCloudClient *client) : _client(client){};

void BrainCloudEntity::getEntity(const FString &entityId, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::EntityServiceEntityId.getValue(), entityId);

    ServerCall *sc = new ServerCall(ServiceName::Entity, ServiceOperation::Read, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudEntity::getSingleton(const FString &entityType, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::EntityServiceEntityType.getValue(), entityType);

    ServerCall *sc = new ServerCall(ServiceName::Entity, ServiceOperation::ReadSingleton, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudEntity::createEntity(const FString &entityType, const FString &jsonEntityData, IAcl *jsonEntityAcl, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::EntityServiceEntityType.getValue(), entityType);
    message->SetObjectField(OperationParam::EntityServiceData.getValue(), JsonUtil::jsonStringToValue(jsonEntityData));
    message->SetObjectField(OperationParam::EntityServiceAcl.getValue(), jsonEntityAcl->toJsonObject());

    ServerCall *sc = new ServerCall(ServiceName::Entity, ServiceOperation::Create, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudEntity::getEntitiesByType(const FString &entityType, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::EntityServiceEntityType.getValue(), entityType);

    ServerCall *sc = new ServerCall(ServiceName::Entity, ServiceOperation::ReadByType, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudEntity::updateEntity(const FString &entityId, const FString &entityType, const FString &jsonEntityData, IAcl *jsonEntityAcl, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::EntityServiceEntityId.getValue(), entityId);
    message->SetStringField(OperationParam::EntityServiceEntityType.getValue(), entityType);
    message->SetObjectField(OperationParam::EntityServiceData.getValue(), JsonUtil::jsonStringToValue(jsonEntityData));
    message->SetObjectField(OperationParam::EntityServiceAcl.getValue(), jsonEntityAcl->toJsonObject());

    ServerCall *sc = new ServerCall(ServiceName::Entity, ServiceOperation::Update, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudEntity::updateSingleton(const FString &entityType, const FString &jsonEntityData, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::EntityServiceEntityType.getValue(), entityType);
    message->SetObjectField(OperationParam::EntityServiceData.getValue(), JsonUtil::jsonStringToValue(jsonEntityData));

    ServerCall *sc = new ServerCall(ServiceName::Entity, ServiceOperation::UpdateSingleton, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudEntity::deleteEntity(const FString &entityId, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::EntityServiceEntityId.getValue(), entityId);

    ServerCall *sc = new ServerCall(ServiceName::Entity, ServiceOperation::Delete, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudEntity::deleteSingleton(const FString &entityType, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::EntityServiceEntityType.getValue(), entityType);

    ServerCall *sc = new ServerCall(ServiceName::Entity, ServiceOperation::DeleteSingleton, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudEntity::getSharedEntityForProfileId(const FString &profileId, const FString &entityId, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::EntityServiceTargetPlayerId.getValue(), profileId);
    message->SetStringField(OperationParam::EntityServiceEntityId.getValue(), entityId);

    ServerCall *sc = new ServerCall(ServiceName::Entity, ServiceOperation::ReadSharedEntity, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudEntity::getSharedEntitiesForProfileId(const FString &profileId, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::EntityServiceTargetPlayerId.getValue(), profileId);

    ServerCall *sc = new ServerCall(ServiceName::Entity, ServiceOperation::ReadShared, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudEntity::getSharedEntitiesListForProfileId(const FString &profileId, const FString &whereJson, const FString &orderByJson, int32 maxReturn, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    message->SetStringField(OperationParam::EntityServiceTargetPlayerId.getValue(), profileId);
    if (OperationParam::isOptionalParamValid(whereJson))
        message->SetObjectField(OperationParam::GlobalEntityServiceWhere.getValue(), JsonUtil::jsonStringToValue(whereJson));

    if (OperationParam::isOptionalParamValid(orderByJson))
        message->SetObjectField(OperationParam::GlobalEntityServiceOrderBy.getValue(), JsonUtil::jsonStringToValue(orderByJson));

    message->SetNumberField(OperationParam::GlobalEntityServiceMaxReturn.getValue(), maxReturn);

    ServerCall *sc = new ServerCall(ServiceName::Entity, ServiceOperation::ReadSharedEntitesList, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudEntity::updateSharedEntity(const FString &entityId, const FString &targetProfileId, const FString &entityType, const FString &jsonEntityData, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::EntityServiceEntityId.getValue(), entityId);
    message->SetStringField(OperationParam::EntityServiceTargetPlayerId.getValue(), targetProfileId);
    message->SetStringField(OperationParam::EntityServiceEntityType.getValue(), entityType);
    message->SetObjectField(OperationParam::EntityServiceData.getValue(), JsonUtil::jsonStringToValue(jsonEntityData));

    ServerCall *sc = new ServerCall(ServiceName::Entity, ServiceOperation::UpdateShared, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudEntity::getList(const FString &whereJson, const FString &orderByJson, int32 maxReturn, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    if (OperationParam::isOptionalParamValid(whereJson))
        message->SetObjectField(OperationParam::GlobalEntityServiceWhere.getValue(), JsonUtil::jsonStringToValue(whereJson));

    if (OperationParam::isOptionalParamValid(orderByJson))
        message->SetObjectField(OperationParam::GlobalEntityServiceOrderBy.getValue(), JsonUtil::jsonStringToValue(orderByJson));

    message->SetNumberField(OperationParam::GlobalEntityServiceMaxReturn.getValue(), maxReturn);

    ServerCall *sc = new ServerCall(ServiceName::Entity, ServiceOperation::GetList, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudEntity::getListCount(const FString &whereJson, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetObjectField(OperationParam::GlobalEntityServiceWhere.getValue(), JsonUtil::jsonStringToValue(whereJson));

    ServerCall *sc = new ServerCall(ServiceName::Entity, ServiceOperation::GetListCount, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudEntity::getPage(const FString &context, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetObjectField(OperationParam::GlobalEntityServiceContext.getValue(), JsonUtil::jsonStringToValue(context));

    ServerCall *sc = new ServerCall(ServiceName::Entity, ServiceOperation::GetPage, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudEntity::getPageOffset(const FString &context, int32 pageOffset, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::GlobalEntityServiceContext.getValue(), context);
    message->SetNumberField(OperationParam::GlobalEntityServicePageOffset.getValue(), pageOffset);

    ServerCall *sc = new ServerCall(ServiceName::Entity, ServiceOperation::GetPageOffset, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudEntity::incrementUserEntityData(const FString &entityId, const FString &jsonData, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::EntityServiceEntityId.getValue(), entityId);
    message->SetObjectField(OperationParam::EntityServiceData.getValue(), JsonUtil::jsonStringToValue(jsonData));

    ServerCall *sc = new ServerCall(ServiceName::Entity, ServiceOperation::IncrementUserEntityData, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudEntity::incrementSharedUserEntityData(const FString &entityId, const FString &targetProfileId, const FString &jsonData, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::EntityServiceEntityId.getValue(), entityId);
    message->SetStringField(OperationParam::EntityServiceTargetPlayerId.getValue(), targetProfileId);
    message->SetObjectField(OperationParam::EntityServiceData.getValue(), JsonUtil::jsonStringToValue(jsonData));

    ServerCall *sc = new ServerCall(ServiceName::Entity, ServiceOperation::IncrementSharedUserEntityData, message, callback);
    _client->sendRequest(sc);
}