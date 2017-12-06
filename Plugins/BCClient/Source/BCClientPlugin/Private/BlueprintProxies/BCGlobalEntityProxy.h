// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BrainCloudACL.h"
#include "BCGlobalEntityProxy.generated.h"

class ABrainCloud;

UCLASS(MinimalAPI)
class UBCGlobalEntityProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
	GENERATED_BODY()

public:
	UBCGlobalEntityProxy(const FObjectInitializer& ObjectInitializer);

	/**
	* Method creates a new entity on the server.
	*
	* Service Name - GlobalEntity
	* Service Operation - Create
	*
	* Param - entityType The entity type as defined by the user
	* Param - timeToLive Sets expiry time for entity if > 0
	* Param - entityAcl The entity's access control object
	* Param - jsonEntityData    The entity's data as a json string
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global Entity")
		static UBCGlobalEntityProxy* CreateEntity(ABrainCloud *brainCloud, const FString& entityType, const FString& timeToLive, UBrainCloudACL* entityAcl, const FString& jsonEntityData);

	/**
	* Method creates a new entity on the server with an indexed id.
	*
	* Service Name - GlobalEntity
	* Service Operation - CreateWithIndexedId
	*
	* Param - entityType The entity type as defined by the user
	* Param - indexedId A secondary ID that will be indexed
	* Param - timeToLive Sets expiry time for entity if > 0
	* Param - entityAcl The entity's access control object list as json.
	* Param - jsonEntityData    The entity's data as a json string
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global Entity")
		static UBCGlobalEntityProxy* CreateEntityWithIndexedId(ABrainCloud *brainCloud, const FString& entityType, const FString& indexedId, const FString& timeToLive, UBrainCloudACL* entityAcl, const FString& jsonEntityData);

	/**
	* Method updates an existing entity on the server.
	*
	* Service Name - GlobalEntity
	* Service Operation - Update
	*
	* Param - entityId The entity ID
	* Param - version The version of the entity to update
	* Param - jsonEntityData    The entity's data as a json string
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global Entity")
		static UBCGlobalEntityProxy* UpdateEntity(ABrainCloud *brainCloud, const FString& entityId, int32 version, const FString& jsonEntityData);

	/**
	* Method updates an existing entity's Acl on the server.
	*
	* Service Name - GlobalEntity
	* Service Operation - UpdateAcl
	*
	* Param - entityId The entity ID
	* Param - version The version of the entity to update
	* Param - entityAcl The entity's access control object list.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global Entity")
		static UBCGlobalEntityProxy* UpdateEntityAcl(ABrainCloud *brainCloud, const FString& entityId, int32 version, UBrainCloudACL* entityAcl);

	/**
	* Method updates an existing entity's time to live on the server.
	*
	* Service Name - GlobalEntity
	* Service Operation - UpdateTimeToLive
	*
	* Param - entityId The entity ID
	* Param - version The version of the entity to update
	* Param - timeToLive Sets expiry time for entity if > 0
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global Entity")
		static UBCGlobalEntityProxy* UpdateEntityTimeToLive(ABrainCloud *brainCloud, const FString& entityId, int32 version, const FString& timeToLive);

	/**
	* Method deletes an existing entity on the server.
	*
	* Service Name - GlobalEntity
	* Service Operation - Delete
	*
	* Param - entityId The entity ID
	* Param - version The version of the entity to delete
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global Entity")
		static UBCGlobalEntityProxy* DeleteEntity(ABrainCloud *brainCloud, const FString& entityId, int32 version);

	/**
	* Method reads an existing entity from the server.
	*
	* Service Name - GlobalEntity
	* Service Operation - Read
	*
	* Param - entityId The entity ID
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global Entity")
		static UBCGlobalEntityProxy* ReadEntity(ABrainCloud *brainCloud, const FString& entityId);

	/**
	* Method gets list of entities from the server base on type and/or where clause
	*
	* Service Name - GlobalEntity
	* Service Operation - GetList
	*
	* Param - where Mongo style query string
	* Param - orderBy Sort order
	* Param - maxReturn The maximum number of entities to return
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global Entity")
		static UBCGlobalEntityProxy* GetList(ABrainCloud *brainCloud, const FString& whereQuery, const FString& orderBy, int32 maxReturn);

	/**
	* Method gets list of entities from the server base on indexed id
	*
	* Service Name - GlobalEntity
	* Service Operation - GetListByIndexedId
	*
	* Param - entityIndexedId The entity indexed Id
	* Param - maxReturn The maximum number of entities to return
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global Entity")
		static UBCGlobalEntityProxy* GetListByIndexedId(ABrainCloud *brainCloud, const FString& entityIndexedId, int32 maxReturn);

	/**
	* Method gets a count of entities based on the where clause
	*
	* Service Name - GlobalEntity
	* Service Operation - GetListCount
	*
	* Param - where Mongo style query string
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global Entity")
		static UBCGlobalEntityProxy* GetListCount(ABrainCloud *brainCloud, const FString& whereQuery);

	/**
	* Method uses a paging system to iterate through Global Entities
	* After retrieving a page of Global Entities with this method,
	* use GetPageOffset() to retrieve previous or next pages.
	*
	* Service Name - GlobalEntity
	* Service Operation - GetPage
	*
	* Param - context The json context for the page request. See the portal appendix documentation for format.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global Entity")
		static UBCGlobalEntityProxy* GetPage(ABrainCloud *brainCloud, const FString& context);

	/**
	* Method to retrieve previous or next pages after having called the GetPage method.
	*
	* Service Name - GlobalEntity
	* Service Operation - GetPageOffset
	*
	* Param - context The context string returned from the server from a
	*      previous call to GetPage or GetPageOffset
	* Param - pageOffset The positive or negative page offset to fetch. Uses the last page
	*      retrieved using the context string to determine a starting point.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global Entity")
		static UBCGlobalEntityProxy* GetPageOffset(ABrainCloud *brainCloud, const FString& context, int32 pageOffset);

	/**
	* Partial increment of global entity data field items. Partial set of items incremented as specified.
	*
	* Service Name - globalEntity
	* Service Operation - INCREMENT_GLOBAL_ENTITY_DATA
	*
	* Param - entityId The id of the entity to update
	* Param - jsonData The entity's data object
	* Param - returnData Should the entity be returned in the response?
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global Entity")
		static UBCGlobalEntityProxy* IncrementGlobalEntityData(ABrainCloud *brainCloud, const FString& entityId, const FString& jsonData);

	/**
	* Gets a list of up to randomCount randomly selected entities from the server based on the where condition and specified maximum return count.
	*
	* Service Name - globalEntity
	* Service Operation - GET_RANDOM_ENTITIES_MATCHING
	*
	* Param - where Mongo style query string
	* Param - maxReturn The maximum number of entities to return
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global Entity")
		static UBCGlobalEntityProxy* GetRandomEntitiesMatching(ABrainCloud *brainCloud, const FString& whereQuery, int32 maxReturn);

	/**
	* Method updates an existing entity's Owner and ACL on the server.
	*
	* Service Name - globalEntity
	* Service Operation - UPDATE_ENTITY_OWNER_AND_ACL
	*
	* Param - entityId The entity ID
	* Param - version The version of the entity to update
	* Param - ownerId The owner ID
	* Param - entityAcl The entity's access control list
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global Entity")
		static UBCGlobalEntityProxy* UpdateEntityOwnerAndAcl(ABrainCloud *brainCloud, const FString& entityId, int32 version, const FString& ownerId, UBrainCloudACL* entityAcl);

	/**
	* Method clears the owner id of an existing entity and sets the ACL on the server.
	*
	* Service Name - globalEntity
	* Service Operation - MAKE_SYSTEM_ENTITY
	*
	* Param - entityId The entity ID
	* Param - version The version of the entity to update
	* Param - entityAcl The entity's access control list
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global Entity")
		static UBCGlobalEntityProxy* MakeSystemEntity(ABrainCloud *brainCloud, const FString& entityId, int32 version, UBrainCloudACL* entityAcl);

	//Response delegates
	UPROPERTY(BlueprintAssignable)
		FBrainCloudCallbackDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
		FBrainCloudCallbackDelegate OnFailure;

protected:
	// IServerCallback interface
	void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
	void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
	// End of IServerCallback interface
};
