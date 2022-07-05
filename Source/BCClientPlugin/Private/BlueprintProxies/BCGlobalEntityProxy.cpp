// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCGlobalEntityProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCGlobalEntityProxy::UBCGlobalEntityProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCGlobalEntityProxy *UBCGlobalEntityProxy::CreateEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &timeToLive, UBrainCloudACL *entityAcl, const FString &jsonEntityData)
{
	UBCGlobalEntityProxy *Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalEntityService()->createEntity(entityType, timeToLive.IsEmpty() ? 0 : FCString::Atoi64(*timeToLive), entityAcl, jsonEntityData, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy *UBCGlobalEntityProxy::CreateEntityWithIndexedId(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &indexedId, const FString &timeToLive, UBrainCloudACL *entityAcl, const FString &jsonEntityData)
{
	UBCGlobalEntityProxy *Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalEntityService()->createEntityWithIndexedId(entityType, indexedId, timeToLive.IsEmpty() ? 0 : FCString::Atoi64(*timeToLive), entityAcl, jsonEntityData, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy *UBCGlobalEntityProxy::UpdateEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId, int32 version, const FString &jsonEntityData)
{
	UBCGlobalEntityProxy *Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalEntityService()->updateEntity(entityId, version, jsonEntityData, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy *UBCGlobalEntityProxy::UpdateEntityAcl(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId, int32 version, UBrainCloudACL *entityAcl)
{
	UBCGlobalEntityProxy *Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalEntityService()->updateEntityAcl(entityId, version, entityAcl, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy *UBCGlobalEntityProxy::UpdateEntityTimeToLive(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId, int32 version, const FString &timeToLive)
{
	UBCGlobalEntityProxy *Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalEntityService()->updateEntityTimeToLive(entityId, version, timeToLive.IsEmpty() ? 0 : FCString::Atoi64(*timeToLive), Proxy);
	return Proxy;
}

UBCGlobalEntityProxy *UBCGlobalEntityProxy::DeleteEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId, int32 version)
{
	UBCGlobalEntityProxy *Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalEntityService()->deleteEntity(entityId, version, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy *UBCGlobalEntityProxy::ReadEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId)
{
	UBCGlobalEntityProxy *Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalEntityService()->readEntity(entityId, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy *UBCGlobalEntityProxy::GetList(UBrainCloudWrapper *brainCloudWrapper, const FString &whereQuery, const FString &orderBy, int32 maxReturn)
{
	UBCGlobalEntityProxy *Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalEntityService()->getList(whereQuery, orderBy, maxReturn, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy *UBCGlobalEntityProxy::GetListByIndexedId(UBrainCloudWrapper *brainCloudWrapper, const FString &entityIndexedId, int32 maxReturn)
{
	UBCGlobalEntityProxy *Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalEntityService()->getListByIndexedId(entityIndexedId, maxReturn, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy *UBCGlobalEntityProxy::GetListCount(UBrainCloudWrapper *brainCloudWrapper, const FString &whereQuery)
{
	UBCGlobalEntityProxy *Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalEntityService()->getListCount(whereQuery, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy *UBCGlobalEntityProxy::GetPage(UBrainCloudWrapper *brainCloudWrapper, const FString &context)
{
	UBCGlobalEntityProxy *Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalEntityService()->getPage(context, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy *UBCGlobalEntityProxy::GetPageOffset(UBrainCloudWrapper *brainCloudWrapper, const FString &context, int32 pageOffset)
{
	UBCGlobalEntityProxy *Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalEntityService()->getPageOffset(context, pageOffset, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy *UBCGlobalEntityProxy::IncrementGlobalEntityData(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId, const FString &jsonData)
{
	UBCGlobalEntityProxy *Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalEntityService()->incrementGlobalEntityData(entityId, jsonData, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy *UBCGlobalEntityProxy::GetRandomEntitiesMatching(UBrainCloudWrapper *brainCloudWrapper, const FString &where, int32 maxReturn)
{
	UBCGlobalEntityProxy *Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalEntityService()->getRandomEntitiesMatching(where, maxReturn, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy *UBCGlobalEntityProxy::UpdateEntityIndexedId(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId, int32 version, const FString &entityIndexedId)
{
	UBCGlobalEntityProxy *Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalEntityService()->updateEntityIndexedId(entityId, version, entityIndexedId, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy *UBCGlobalEntityProxy::UpdateEntityOwnerAndAcl(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId, int32 version, const FString &ownerId, UBrainCloudACL *entityAcl)
{
	UBCGlobalEntityProxy *Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalEntityService()->updateEntityOwnerAndAcl(entityId, version, ownerId, entityAcl, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy *UBCGlobalEntityProxy::MakeSystemEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId, int32 version, UBrainCloudACL *entityAcl)
{
	UBCGlobalEntityProxy *Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalEntityService()->makeSystemEntity(entityId, version, entityAcl, Proxy);
	return Proxy;
}
