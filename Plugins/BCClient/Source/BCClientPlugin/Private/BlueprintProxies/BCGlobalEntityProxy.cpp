// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCGlobalEntityProxy.h"

UBCGlobalEntityProxy::UBCGlobalEntityProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::CreateEntity(const FString& entityType, const FString& timeToLive, UBrainCloudACL* entityAcl, const FString& jsonEntityData)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	BrainCloudClient::getInstance()->getGlobalEntityService()->createEntity(entityType, timeToLive.IsEmpty() ? 0 : FCString::Atoi64(*timeToLive), entityAcl, jsonEntityData, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::CreateEntityWithIndexedId(const FString& entityType, const FString& indexedId, const FString& timeToLive, UBrainCloudACL* entityAcl, const FString& jsonEntityData)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	BrainCloudClient::getInstance()->getGlobalEntityService()->createEntityWithIndexedId(entityType, indexedId, timeToLive.IsEmpty() ? 0 : FCString::Atoi64(*timeToLive), entityAcl, jsonEntityData, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::UpdateEntity(const FString& entityId, int32 version, const FString& jsonEntityData)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	BrainCloudClient::getInstance()->getGlobalEntityService()->updateEntity(entityId, version, jsonEntityData, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::UpdateEntityAcl(const FString& entityId, int32 version, UBrainCloudACL* entityAcl)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	BrainCloudClient::getInstance()->getGlobalEntityService()->updateEntityAcl(entityId, version, entityAcl, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::UpdateEntityTimeToLive(const FString& entityId, int32 version, const FString& timeToLive)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	BrainCloudClient::getInstance()->getGlobalEntityService()->updateEntityTimeToLive(entityId, version, timeToLive.IsEmpty() ? 0 : FCString::Atoi64(*timeToLive), Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::DeleteEntity(const FString& entityId, int32 version)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	BrainCloudClient::getInstance()->getGlobalEntityService()->deleteEntity(entityId, version, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::ReadEntity(const FString& entityId)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	BrainCloudClient::getInstance()->getGlobalEntityService()->readEntity(entityId, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::GetList(const FString& whereQuery, const FString& orderBy, int32 maxReturn)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	BrainCloudClient::getInstance()->getGlobalEntityService()->getList(whereQuery, orderBy, maxReturn, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::GetListByIndexedId(const FString& entityIndexedId, int32 maxReturn)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	BrainCloudClient::getInstance()->getGlobalEntityService()->getListByIndexedId(entityIndexedId, maxReturn, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::GetListCount(const FString& whereQuery)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	BrainCloudClient::getInstance()->getGlobalEntityService()->getListCount(whereQuery, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::GetPage(const FString& context)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	BrainCloudClient::getInstance()->getGlobalEntityService()->getPage(context, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::GetPageOffset(const FString& context, int32 pageOffset)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	BrainCloudClient::getInstance()->getGlobalEntityService()->getPageOffset(context, pageOffset, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy * UBCGlobalEntityProxy::IncrementGlobalEntityData(const FString & entityId, const FString & jsonData)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	BrainCloudClient::getInstance()->getGlobalEntityService()->incrementGlobalEntityData(entityId, jsonData, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::UpdateEntityOwnerAndAcl(const FString& entityId, int32 version, const FString& ownerId, UBrainCloudACL* entityAcl)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	BrainCloudClient::getInstance()->getGlobalEntityService()->updateEntityOwnerAndAcl(entityId, version, ownerId, entityAcl, Proxy);
	return Proxy;
}

UBCGlobalEntityProxy* UBCGlobalEntityProxy::MakeSystemEntity(const FString& entityId, int32 version, UBrainCloudACL* entityAcl)
{
	UBCGlobalEntityProxy* Proxy = NewObject<UBCGlobalEntityProxy>();
	BrainCloudClient::getInstance()->getGlobalEntityService()->makeSystemEntity(entityId, version, entityAcl, Proxy);
	return Proxy;
}

//callbacks
void UBCGlobalEntityProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
	OnSuccess.Broadcast(jsonData, returnData);
}

void UBCGlobalEntityProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
	OnFailure.Broadcast(jsonError, returnData);
}

