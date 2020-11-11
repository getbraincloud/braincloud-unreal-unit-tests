// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCEntityProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCEntityProxy::UBCEntityProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCEntityProxy *UBCEntityProxy::CreateEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &jsonEntityData, UBrainCloudACL *jsonEntityAcl)
{
    UBCEntityProxy *Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getEntityService()->createEntity(entityType, jsonEntityData, jsonEntityAcl, Proxy);
    return Proxy;
}

UBCEntityProxy *UBCEntityProxy::UpdateEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId, const FString &entityType, const FString &jsonEntityData, UBrainCloudACL *jsonEntityAcl)
{
    UBCEntityProxy *Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getEntityService()->updateEntity(entityId, entityType, jsonEntityData, jsonEntityAcl, Proxy);
    return Proxy;
}

UBCEntityProxy *UBCEntityProxy::GetEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId)
{
    UBCEntityProxy *Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getEntityService()->getEntity(entityId, Proxy);
    return Proxy;
}

UBCEntityProxy *UBCEntityProxy::GetSingleton(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType)
{
    UBCEntityProxy *Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getEntityService()->getSingleton(entityType, Proxy);
    return Proxy;
}

UBCEntityProxy *UBCEntityProxy::UpdateSingleton(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &jsonEntityData)
{
    UBCEntityProxy *Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getEntityService()->updateSingleton(entityType, jsonEntityData, Proxy);
    return Proxy;
}

UBCEntityProxy *UBCEntityProxy::DeleteEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId)
{
    UBCEntityProxy *Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getEntityService()->deleteEntity(entityId, Proxy);
    return Proxy;
}

UBCEntityProxy *UBCEntityProxy::DeleteSingleton(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType)
{
    UBCEntityProxy *Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getEntityService()->deleteSingleton(entityType, Proxy);
    return Proxy;
}

UBCEntityProxy *UBCEntityProxy::GetEntitiesByType(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType)
{
    UBCEntityProxy *Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getEntityService()->getEntitiesByType(entityType, Proxy);
    return Proxy;
}

UBCEntityProxy *UBCEntityProxy::UpdateSharedEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId, const FString &targetProfileId, const FString &entityType, const FString &jsonEntityData)
{
    UBCEntityProxy *Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getEntityService()->updateSharedEntity(entityId, targetProfileId, entityType, jsonEntityData, Proxy);
    return Proxy;
}

UBCEntityProxy *UBCEntityProxy::GetList(UBrainCloudWrapper *brainCloudWrapper, const FString &whereJson, const FString &orderByJson, int32 maxReturn)
{
    UBCEntityProxy *Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getEntityService()->getList(whereJson, orderByJson, maxReturn, Proxy);
    return Proxy;
}

UBCEntityProxy *UBCEntityProxy::GetListCount(UBrainCloudWrapper *brainCloudWrapper, const FString &whereJson)
{
    UBCEntityProxy *Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getEntityService()->getListCount(whereJson, Proxy);
    return Proxy;
}

UBCEntityProxy *UBCEntityProxy::GetPage(UBrainCloudWrapper *brainCloudWrapper, const FString &context)
{
    UBCEntityProxy *Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getEntityService()->getPage(context, Proxy);
    return Proxy;
}

UBCEntityProxy *UBCEntityProxy::GetPageOffset(UBrainCloudWrapper *brainCloudWrapper, const FString &context, int32 pageOffset)
{
    UBCEntityProxy *Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getEntityService()->getPageOffset(context, pageOffset, Proxy);
    return Proxy;
}

UBCEntityProxy *UBCEntityProxy::IncrementUserEntityData(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId, const FString &jsonData)
{
    UBCEntityProxy *Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getEntityService()->incrementUserEntityData(entityId, jsonData, Proxy);
    return Proxy;
}

UBCEntityProxy *UBCEntityProxy::IncrementSharedUserEntityData(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId, const FString &targetProfileId, const FString &jsonData)
{
    UBCEntityProxy *Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getEntityService()->incrementSharedUserEntityData(entityId, targetProfileId, jsonData, Proxy);
    return Proxy;
}

UBCEntityProxy *UBCEntityProxy::GetSharedEntityForProfileId(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId, const FString &profileId)
{
    UBCEntityProxy *Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getEntityService()->getSharedEntityForProfileId(entityId, profileId, Proxy);
    return Proxy;
}

UBCEntityProxy *UBCEntityProxy::GetSharedEntitiesForProfileId(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId)
{
    UBCEntityProxy *Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getEntityService()->getSharedEntitiesForProfileId(profileId, Proxy);
    return Proxy;
}

UBCEntityProxy *UBCEntityProxy::GetSharedEntitiesListForProfileId(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId, const FString &whereJson, const FString &orderByJson, int32 maxReturn)
{
    UBCEntityProxy *Proxy = NewObject<UBCEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getEntityService()->getSharedEntitiesListForProfileId(profileId, whereJson, orderByJson, maxReturn, Proxy);
    return Proxy;
}
