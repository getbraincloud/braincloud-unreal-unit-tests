// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCCustomEntityProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCCustomEntityProxy::UBCCustomEntityProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCCustomEntityProxy *UBCCustomEntityProxy::CreateEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &jsonEntityData, UBrainCloudACL *jsonEntityAcl, const FString &timeToLive, bool isOwned)
{
    UBCCustomEntityProxy *Proxy = NewObject<UBCCustomEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getCustomEntityService()->createEntity(entityType, jsonEntityData, jsonEntityAcl, timeToLive.IsEmpty() ? 0 : FCString::Atoi64(*timeToLive), isOwned, Proxy);
    return Proxy;
}

UBCCustomEntityProxy *UBCCustomEntityProxy::DeleteEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &entityId, int version)
{
    UBCCustomEntityProxy *Proxy = NewObject<UBCCustomEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getCustomEntityService()->deleteEntity(entityType, entityId, version, Proxy);
    return Proxy;
}

UBCCustomEntityProxy *UBCCustomEntityProxy::GetCount(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &whereJson)
{
    UBCCustomEntityProxy *Proxy = NewObject<UBCCustomEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getCustomEntityService()->getCount(entityType, whereJson, Proxy);
    return Proxy;
}

UBCCustomEntityProxy *UBCCustomEntityProxy::GetEntityPage(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &context)
{
    UBCCustomEntityProxy *Proxy = NewObject<UBCCustomEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getCustomEntityService()->getEntityPage(entityType, context, Proxy);
    return Proxy;
}

UBCCustomEntityProxy *UBCCustomEntityProxy::GetEntityPageOffset(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &context, int pageOffset)
{
    UBCCustomEntityProxy *Proxy = NewObject<UBCCustomEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getCustomEntityService()->getEntityPageOffset(entityType, context, pageOffset, Proxy);
    return Proxy;
}

UBCCustomEntityProxy *UBCCustomEntityProxy::GetRandomEntitiesMatching(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &whereJson, const int64 &maxReturn)
{
    UBCCustomEntityProxy *Proxy = NewObject<UBCCustomEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getCustomEntityService()->getRandomEntitiesMatching(entityType, whereJson, maxReturn, Proxy);
    return Proxy;
}

UBCCustomEntityProxy *UBCCustomEntityProxy::ReadEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &entityId)
{
    UBCCustomEntityProxy *Proxy = NewObject<UBCCustomEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getCustomEntityService()->readEntity(entityType, entityId, Proxy);
    return Proxy;
}

UBCCustomEntityProxy *UBCCustomEntityProxy::IncrementData(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &entityId, const FString &fieldsJson)
{
    UBCCustomEntityProxy *Proxy = NewObject<UBCCustomEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getCustomEntityService()->incrementData(entityType, entityId, fieldsJson, Proxy);
    return Proxy;
}

UBCCustomEntityProxy *UBCCustomEntityProxy::UpdateEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &entityId, int version, const FString &dataJson, UBrainCloudACL *jsonEntityAcl, const FString &timeToLive)
{
    UBCCustomEntityProxy *Proxy = NewObject<UBCCustomEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getCustomEntityService()->updateEntity(entityType, entityId, version, dataJson, jsonEntityAcl, timeToLive.IsEmpty() ? 0 : FCString::Atoi64(*timeToLive), Proxy);
    return Proxy;
}

UBCCustomEntityProxy *UBCCustomEntityProxy::UpdateEntityFields(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &entityId, int version, const FString &fieldsJson)
{
    UBCCustomEntityProxy *Proxy = NewObject<UBCCustomEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getCustomEntityService()->updateEntityFields(entityType, entityId, version, fieldsJson, Proxy);
    return Proxy;
}

UBCCustomEntityProxy *UBCCustomEntityProxy::DeleteEntities(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &deleteCriteria)
{
    UBCCustomEntityProxy *Proxy = NewObject<UBCCustomEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getCustomEntityService()->deleteEntities(entityType, deleteCriteria, Proxy);
    return Proxy;
}

UBCCustomEntityProxy *UBCCustomEntityProxy::ReadSingleton(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType)
{
    UBCCustomEntityProxy *Proxy = NewObject<UBCCustomEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getCustomEntityService()->readSingleton(entityType,Proxy);
    return Proxy;
}

UBCCustomEntityProxy *UBCCustomEntityProxy::DeleteSingleton(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, int version)
{
    UBCCustomEntityProxy *Proxy = NewObject<UBCCustomEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getCustomEntityService()->deleteSingleton(entityType, version, Proxy);
    return Proxy;
}

UBCCustomEntityProxy *UBCCustomEntityProxy::UpdateSingleton(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, int version, const FString &dataJson, UBrainCloudACL *jsonEntityAcl, const FString &timeToLive)
{
    UBCCustomEntityProxy *Proxy = NewObject<UBCCustomEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getCustomEntityService()->updateSingleton(entityType, version, dataJson, jsonEntityAcl, timeToLive.IsEmpty() ? 0 : FCString::Atoi64(*timeToLive), Proxy);
    return Proxy;
}

UBCCustomEntityProxy *UBCCustomEntityProxy::UpdateSingletonFields(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, int version, const FString &fieldsJson)
{
    UBCCustomEntityProxy *Proxy = NewObject<UBCCustomEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getCustomEntityService()->updateSingletonFields(entityType, version, fieldsJson, Proxy);
    return Proxy;
}

UBCCustomEntityProxy* UBCCustomEntityProxy::UpdateEntityFieldsShard(UBrainCloudWrapper* brainCloudWrapper, const FString& entityType,
    const FString& entityId, int version, const FString& fieldsJson, const FString& shardKeyJson)
{
    UBCCustomEntityProxy *Proxy = NewObject<UBCCustomEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getCustomEntityService()->updateEntityFieldsShard(entityType, entityId, version, fieldsJson, shardKeyJson, Proxy);
    return Proxy;
}
