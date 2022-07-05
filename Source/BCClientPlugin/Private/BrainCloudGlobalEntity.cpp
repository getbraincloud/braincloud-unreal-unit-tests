// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudGlobalEntity.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"
#include "IAcl.h"

BrainCloudGlobalEntity::BrainCloudGlobalEntity(BrainCloudClient *client) : _client(client){};

void BrainCloudGlobalEntity::createEntity(const FString &entityType, int64 timeToLive, IAcl *jsonEntityAcl,
                                          const FString &jsonEntityData, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::GlobalEntityServiceEntityType.getValue(), entityType);
    message->SetNumberField(OperationParam::GlobalEntityServiceTimeToLive.getValue(), timeToLive);
    message->SetObjectField(OperationParam::GlobalEntityServiceData.getValue(), JsonUtil::jsonStringToValue(jsonEntityData));
    message->SetObjectField(OperationParam::GlobalEntityServiceAcl.getValue(), jsonEntityAcl->toJsonObject());

    ServerCall *sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::Create, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGlobalEntity::createEntityWithIndexedId(const FString &entityType, const FString &indexedId, int64 timeToLive,
                                                       IAcl *jsonEntityAcl, const FString &jsonEntityData, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::GlobalEntityServiceEntityType.getValue(), entityType);
    message->SetStringField(OperationParam::GlobalEntityServiceIndexedId.getValue(), indexedId);
    message->SetNumberField(OperationParam::GlobalEntityServiceTimeToLive.getValue(), timeToLive);
    message->SetObjectField(OperationParam::GlobalEntityServiceData.getValue(), JsonUtil::jsonStringToValue(jsonEntityData));
    message->SetObjectField(OperationParam::GlobalEntityServiceAcl.getValue(), jsonEntityAcl->toJsonObject());

    ServerCall *sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::CreateWithIndexedId, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGlobalEntity::updateEntity(const FString &entityId, int32 version, const FString &jsonEntityData, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::GlobalEntityServiceEntityId.getValue(), entityId);
    message->SetNumberField(OperationParam::GlobalEntityServiceVersion.getValue(), version);
    message->SetObjectField(OperationParam::GlobalEntityServiceData.getValue(), JsonUtil::jsonStringToValue(jsonEntityData));

    ServerCall *sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::Update, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGlobalEntity::updateEntityAcl(const FString &entityId, int32 version, IAcl *jsonEntityAcl, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::GlobalEntityServiceEntityId.getValue(), entityId);
    message->SetNumberField(OperationParam::GlobalEntityServiceVersion.getValue(), version);
    message->SetObjectField(OperationParam::GlobalEntityServiceAcl.getValue(), jsonEntityAcl->toJsonObject());

    ServerCall *sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::UpdateAcl, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGlobalEntity::updateEntityTimeToLive(const FString &entityId, int32 version, int64 timeToLive, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::GlobalEntityServiceEntityId.getValue(), entityId);
    message->SetNumberField(OperationParam::GlobalEntityServiceVersion.getValue(), version);
    message->SetNumberField(OperationParam::GlobalEntityServiceTimeToLive.getValue(), timeToLive);

    ServerCall *sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::UpdateTimeToLive, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGlobalEntity::deleteEntity(const FString &entityId, int32 version, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::GlobalEntityServiceEntityId.getValue(), entityId);
    message->SetNumberField(OperationParam::GlobalEntityServiceVersion.getValue(), version);

    ServerCall *sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::Delete, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGlobalEntity::readEntity(const FString &entityId, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::GlobalEntityServiceEntityId.getValue(), entityId);

    ServerCall *sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::Read, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGlobalEntity::getList(const FString &where, const FString &orderBy, int32 maxReturn, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    if (OperationParam::isOptionalParamValid(where))
        message->SetObjectField(OperationParam::GlobalEntityServiceWhere.getValue(), JsonUtil::jsonStringToValue(where));

    if (OperationParam::isOptionalParamValid(orderBy))
        message->SetObjectField(OperationParam::GlobalEntityServiceOrderBy.getValue(), JsonUtil::jsonStringToValue(orderBy));

    message->SetNumberField(OperationParam::GlobalEntityServiceMaxReturn.getValue(), maxReturn);

    ServerCall *sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::GetList, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGlobalEntity::getListByIndexedId(const FString &entityIndexedId, int32 maxReturn, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::GlobalEntityServiceIndexedId.getValue(), entityIndexedId);
    message->SetNumberField(OperationParam::GlobalEntityServiceMaxReturn.getValue(), maxReturn);

    ServerCall *sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::GetListByIndexedId, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGlobalEntity::getListCount(const FString &where, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetObjectField(OperationParam::GlobalEntityServiceWhere.getValue(), JsonUtil::jsonStringToValue(where));

    ServerCall *sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::GetListCount, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGlobalEntity::getPage(const FString &context, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetObjectField(OperationParam::GlobalEntityServiceContext.getValue(), JsonUtil::jsonStringToValue(context));

    ServerCall *sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::GetPage, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGlobalEntity::getPageOffset(const FString &context, int32 pageOffset, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::GlobalEntityServiceContext.getValue(), context);
    message->SetNumberField(OperationParam::GlobalEntityServicePageOffset.getValue(), pageOffset);

    ServerCall *sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::GetPageOffset, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGlobalEntity::incrementGlobalEntityData(const FString &entityId, const FString &jsonData, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::GlobalEntityServiceEntityId.getValue(), entityId);
    message->SetObjectField(OperationParam::GlobalEntityServiceData.getValue(), JsonUtil::jsonStringToValue(jsonData));

    ServerCall *sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::IncrementGlobalEntityData, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGlobalEntity::getRandomEntitiesMatching(const FString &where, int32 maxReturn, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetObjectField(OperationParam::GlobalEntityServiceWhere.getValue(), JsonUtil::jsonStringToValue(where));
    message->SetNumberField(OperationParam::GlobalEntityServiceMaxReturn.getValue(), maxReturn);

    ServerCall *sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::GetRandomEntitiesMatching, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGlobalEntity::updateEntityIndexedId(const FString &entityId, int32 version, const FString &entityIndexedId, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::GlobalEntityServiceEntityId.getValue(), entityId);
    message->SetNumberField(OperationParam::GlobalEntityServiceVersion.getValue(), version);
    message->SetStringField(OperationParam::GlobalEntityServiceIndexedId.getValue(), entityIndexedId);

    ServerCall *sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::UpdateEntityIndexedId, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGlobalEntity::updateEntityOwnerAndAcl(const FString &entityId, int32 version, const FString &ownerId, IAcl *jsonEntityAcl, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::GlobalEntityServiceEntityId.getValue(), entityId);
    message->SetStringField(OperationParam::OwnerId.getValue(), ownerId);
    message->SetNumberField(OperationParam::GlobalEntityServiceVersion.getValue(), version);
    message->SetObjectField(OperationParam::GlobalEntityServiceAcl.getValue(), jsonEntityAcl->toJsonObject());

    ServerCall *sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::UpdateEntityOwnerAndAcl, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudGlobalEntity::makeSystemEntity(const FString &entityId, int32 version, IAcl *jsonEntityAcl, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::GlobalEntityServiceEntityId.getValue(), entityId);
    message->SetNumberField(OperationParam::GlobalEntityServiceVersion.getValue(), version);
    message->SetObjectField(OperationParam::GlobalEntityServiceAcl.getValue(), jsonEntityAcl->toJsonObject());

    ServerCall *sc = new ServerCall(ServiceName::GlobalEntity, ServiceOperation::MakeSystemEntity, message, callback);
    _client->sendRequest(sc);
}
