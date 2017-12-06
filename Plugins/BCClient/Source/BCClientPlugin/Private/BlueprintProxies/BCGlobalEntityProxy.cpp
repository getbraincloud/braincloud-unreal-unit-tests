// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloud.h"
#include "BCWrapperProxy.h"
#include "BCGlobalEntityProxy.h"
#include "BrainCloudWrapper.h"

UBCGlobalEntityProxy::UBCGlobalEntityProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::CreateEntity(ABrainCloud *brainCloud, const FString& entityType, const FString& timeToLive, UBrainCloudACL* entityAcl, const FString& jsonEntityData)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGlobalEntityService()->createEntity(entityType, timeToLive.IsEmpty() ? 0 : FCString::Atoi64(*timeToLive), entityAcl, jsonEntityData, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::CreateEntityWithIndexedId(ABrainCloud *brainCloud, const FString& entityType, const FString& indexedId, const FString& timeToLive, UBrainCloudACL* entityAcl, const FString& jsonEntityData)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGlobalEntityService()->createEntityWithIndexedId(entityType, indexedId, timeToLive.IsEmpty() ? 0 : FCString::Atoi64(*timeToLive), entityAcl, jsonEntityData, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::UpdateEntity(ABrainCloud *brainCloud, const FString& entityId, int32 version, const FString& jsonEntityData)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGlobalEntityService()->updateEntity(entityId, version, jsonEntityData, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::UpdateEntityAcl(ABrainCloud *brainCloud, const FString& entityId, int32 version, UBrainCloudACL* entityAcl)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGlobalEntityService()->updateEntityAcl(entityId, version, entityAcl, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::UpdateEntityTimeToLive(ABrainCloud *brainCloud, const FString& entityId, int32 version, const FString& timeToLive)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGlobalEntityService()->updateEntityTimeToLive(entityId, version, timeToLive.IsEmpty() ? 0 : FCString::Atoi64(*timeToLive), Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::DeleteEntity(ABrainCloud *brainCloud, const FString& entityId, int32 version)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGlobalEntityService()->deleteEntity(entityId, version, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::ReadEntity(ABrainCloud *brainCloud, const FString& entityId)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGlobalEntityService()->readEntity(entityId, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::GetList(ABrainCloud *brainCloud, const FString& whereQuery, const FString& orderBy, int32 maxReturn)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGlobalEntityService()->getList(whereQuery, orderBy, maxReturn, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::GetListByIndexedId(ABrainCloud *brainCloud, const FString& entityIndexedId, int32 maxReturn)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGlobalEntityService()->getListByIndexedId(entityIndexedId, maxReturn, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::GetListCount(ABrainCloud *brainCloud, const FString& whereQuery)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGlobalEntityService()->getListCount(whereQuery, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::GetPage(ABrainCloud *brainCloud, const FString& context)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGlobalEntityService()->getPage(context, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::GetPageOffset(ABrainCloud *brainCloud, const FString& context, int32 pageOffset)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGlobalEntityService()->getPageOffset(context, pageOffset, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy * UBCGlobalEntityProxy::IncrementGlobalEntityData(ABrainCloud *brainCloud, const FString & entityId, const FString & jsonData)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGlobalEntityService()->incrementGlobalEntityData(entityId, jsonData, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy * UBCGlobalEntityProxy::GetRandomEntitiesMatching(ABrainCloud *brainCloud, const FString& where, int32 maxReturn)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGlobalEntityService()->getRandomEntitiesMatching(where, maxReturn, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::UpdateEntityOwnerAndAcl(ABrainCloud *brainCloud, const FString& entityId, int32 version, const FString& ownerId, UBrainCloudACL* entityAcl)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGlobalEntityService()->updateEntityOwnerAndAcl(entityId, version, ownerId, entityAcl, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::MakeSystemEntity(ABrainCloud *brainCloud, const FString& entityId, int32 version, UBrainCloudACL* entityAcl)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGlobalEntityService()->makeSystemEntity(entityId, version, entityAcl, Proxy);
	return Proxy;
}

//callbacks
void UBCGlobalEntityProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
	OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCGlobalEntityProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
	OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

