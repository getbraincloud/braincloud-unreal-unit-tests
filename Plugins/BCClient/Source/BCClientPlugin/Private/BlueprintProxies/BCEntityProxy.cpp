// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloud.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCEntityProxy.h"

UBCEntityProxy::UBCEntityProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCEntityProxy* UBCEntityProxy::CreateEntity(ABrainCloud *brainCloud, const FString& entityType, const FString& jsonEntityData, UBrainCloudACL* jsonEntityAcl)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getEntityService()->createEntity(entityType, jsonEntityData, jsonEntityAcl, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::UpdateEntity(ABrainCloud *brainCloud, const FString& entityId, const FString& entityType, const FString& jsonEntityData, UBrainCloudACL* jsonEntityAcl)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getEntityService()->updateEntity(entityId, entityType, jsonEntityData, jsonEntityAcl, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::GetEntity(ABrainCloud *brainCloud, const FString& entityId)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getEntityService()->getEntity(entityId, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::GetSingleton(ABrainCloud *brainCloud, const FString& entityType)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getEntityService()->getSingleton(entityType, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::UpdateSingleton(ABrainCloud *brainCloud, const FString& entityType, const FString& jsonEntityData)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getEntityService()->updateSingleton(entityType, jsonEntityData, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::DeleteEntity(ABrainCloud *brainCloud, const FString& entityId)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getEntityService()->deleteEntity(entityId, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::DeleteSingleton(ABrainCloud *brainCloud, const FString& entityType)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getEntityService()->deleteSingleton(entityType, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::GetEntitiesByType(ABrainCloud *brainCloud, const FString& entityType)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getEntityService()->getEntitiesByType(entityType, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::GetSharedEntityForPlayerId(ABrainCloud *brainCloud, const FString& profileId, const FString& entityId)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getEntityService()->getSharedEntityForProfileId(profileId, entityId, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::GetSharedEntitiesForPlayerId(ABrainCloud *brainCloud, const FString& profileId)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getEntityService()->getSharedEntitiesForProfileId(profileId, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::UpdateSharedEntity(ABrainCloud *brainCloud, const FString& entityId, const FString& targetProfileId, const FString& entityType, const FString& jsonEntityData)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getEntityService()->updateSharedEntity(entityId, targetProfileId, entityType, jsonEntityData, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::GetList(ABrainCloud *brainCloud, const FString& whereJson, const FString& orderByJson, int32 maxReturn)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getEntityService()->getList(whereJson, orderByJson, maxReturn, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::GetListCount(ABrainCloud *brainCloud, const FString& whereJson)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getEntityService()->getListCount(whereJson, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::GetPage(ABrainCloud *brainCloud, const FString& context)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getEntityService()->getPage(context, Proxy);
    return Proxy;
}

UBCEntityProxy* UBCEntityProxy::GetPageOffset(ABrainCloud *brainCloud, const FString& context, int32 pageOffset)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getEntityService()->getPageOffset(context, pageOffset, Proxy);
    return Proxy;
}

UBCEntityProxy * UBCEntityProxy::IncrementUserEntityData(ABrainCloud *brainCloud, const FString & entityId, const FString & jsonData)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getEntityService()->incrementUserEntityData(entityId, jsonData, Proxy);
    return Proxy;
}

UBCEntityProxy * UBCEntityProxy::IncrementSharedUserEntityData(ABrainCloud *brainCloud, const FString & entityId, const FString & targetProfileId, const FString & jsonData)
{
	UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getEntityService()->incrementSharedUserEntityData(entityId, targetProfileId, jsonData, Proxy);
	return Proxy;
}

UBCEntityProxy* UBCEntityProxy::GetSharedEntitiesListForPlayerId(ABrainCloud *brainCloud, const FString& profileId, const FString& whereJson, const FString& orderByJson, int32 maxReturn)
{
    UBCEntityProxy* Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getEntityService()->getSharedEntitiesListForProfileId(profileId, whereJson, orderByJson, maxReturn, Proxy);
    return Proxy;
}

//callbacks
void UBCEntityProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCEntityProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

