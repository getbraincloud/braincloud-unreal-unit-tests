// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCEntityProxy.h"

UBCEntityProxy::UBCEntityProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCEntityProxy* UBCEntityProxy::CreateEntity(const FString& entityType, const FString& jsonEntityData, UBrainCloudACL* jsonEntityAcl)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    BrainCloudClient::getInstance()->getEntityService()->createEntity(entityType, jsonEntityData, jsonEntityAcl, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::UpdateEntity(const FString& entityId, const FString& entityType, const FString& jsonEntityData, UBrainCloudACL* jsonEntityAcl)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    BrainCloudClient::getInstance()->getEntityService()->updateEntity(entityId, entityType, jsonEntityData, jsonEntityAcl, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::GetEntity(const FString& entityId)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    BrainCloudClient::getInstance()->getEntityService()->getEntity(entityId, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::GetSingleton(const FString& entityType)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    BrainCloudClient::getInstance()->getEntityService()->getSingleton(entityType, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::UpdateSingleton(const FString& entityType, const FString& jsonEntityData)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    BrainCloudClient::getInstance()->getEntityService()->updateSingleton(entityType, jsonEntityData, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::DeleteEntity(const FString& entityId)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    BrainCloudClient::getInstance()->getEntityService()->deleteEntity(entityId, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::DeleteSingleton(const FString& entityType)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    BrainCloudClient::getInstance()->getEntityService()->deleteSingleton(entityType, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::GetEntitiesByType(const FString& entityType)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    BrainCloudClient::getInstance()->getEntityService()->getEntitiesByType(entityType, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::GetSharedEntityForPlayerId(const FString& playerId, const FString& entityId)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    BrainCloudClient::getInstance()->getEntityService()->getSharedEntityForPlayerId(playerId, entityId, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::GetSharedEntitiesForPlayerId(const FString& playerId)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    BrainCloudClient::getInstance()->getEntityService()->getSharedEntitiesForPlayerId(playerId, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::UpdateSharedEntity(const FString& entityId, const FString& targetPlayerId, const FString& entityType, const FString& jsonEntityData)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    BrainCloudClient::getInstance()->getEntityService()->updateSharedEntity(entityId, targetPlayerId, entityType, jsonEntityData, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::GetList(const FString& whereJson, const FString& orderByJson, int32 maxReturn)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    BrainCloudClient::getInstance()->getEntityService()->getList(whereJson, orderByJson, maxReturn, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::GetListCount(const FString& whereJson)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    BrainCloudClient::getInstance()->getEntityService()->getListCount(whereJson, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::GetPage(const FString& context)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    BrainCloudClient::getInstance()->getEntityService()->getPage(context, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::GetPageOffset(const FString& context, int32 pageOffset)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    BrainCloudClient::getInstance()->getEntityService()->getPageOffset(context, pageOffset, Proxy);
    return Proxy;
}

UBCEntityProxy * UBCEntityProxy::IncrementUserEntityData(const FString & entityId, const FString & jsonData)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    BrainCloudClient::getInstance()->getEntityService()->incrementUserEntityData(entityId, jsonData, Proxy);
    return Proxy;
}

UBCEntityProxy * UBCEntityProxy::IncrementSharedUserEntityData(const FString & entityId, const FString & targetPlayerId, const FString & jsonData)
{
	UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
	BrainCloudClient::getInstance()->getEntityService()->incrementSharedUserEntityData(entityId, targetPlayerId, jsonData, Proxy);
	return Proxy;
}

UBCEntityProxy* UBCEntityProxy::GetSharedEntitiesListForPlayerId(const FString& playerId, const FString& whereJson, const FString& orderByJson, int32 maxReturn)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    BrainCloudClient::getInstance()->getEntityService()->getSharedEntitiesListForPlayerId(playerId, whereJson, orderByJson, maxReturn, Proxy);
    return Proxy;
}

//callbacks
void UBCEntityProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
}

void UBCEntityProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
}

