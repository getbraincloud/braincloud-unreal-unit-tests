// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCCustomEntityProxy.h"

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

UBCCustomEntityProxy *UBCCustomEntityProxy::GetPage(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, int rowsPerPage, const FString &searchJson, const FString &sortJson, bool doCount)
{
    UBCCustomEntityProxy *Proxy = NewObject<UBCCustomEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getCustomEntityService()->getPage(entityType, rowsPerPage, searchJson, sortJson, doCount, Proxy);
    return Proxy;
}

UBCCustomEntityProxy *UBCCustomEntityProxy::GetEntityPage(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &context)
{
    UBCCustomEntityProxy *Proxy = NewObject<UBCCustomEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getCustomEntityService()->getEntityPage(entityType, context, Proxy);
    return Proxy;
}

UBCCustomEntityProxy *UBCCustomEntityProxy::GetPageOffset(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &context, int pageOffset)
{
    UBCCustomEntityProxy *Proxy = NewObject<UBCCustomEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getCustomEntityService()->getPageOffset(entityType, context, pageOffset, Proxy);
    return Proxy;
}

UBCCustomEntityProxy *UBCCustomEntityProxy::GetEntityPageOffset(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &context, int pageOffset)
{
    UBCCustomEntityProxy *Proxy = NewObject<UBCCustomEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getCustomEntityService()->getEntityPageOffset(entityType, context, pageOffset, Proxy);
    return Proxy;
}

UBCCustomEntityProxy *UBCCustomEntityProxy::ReadEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &entityId)
{
    UBCCustomEntityProxy *Proxy = NewObject<UBCCustomEntityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getCustomEntityService()->readEntity(entityType, entityId, Proxy);
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
