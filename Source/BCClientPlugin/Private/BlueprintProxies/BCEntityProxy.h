// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BrainCloudACL.h"
#include "BCEntityProxy.generated.h"

UCLASS(MinimalAPI)
class UBCEntityProxy : public UBCBlueprintCallProxyBase
{
    GENERATED_BODY()

  public:
    UBCEntityProxy(const FObjectInitializer &ObjectInitializer);

    /**
    * Method creates a new entity on the server.
    *
    * Service Name - Entity
    * Service Operation - Create
    *
    * Param - entityType The entity type as defined by the user
    * Param - jsonEntityData    The entity's data as a json string
    * Param - jsonEntityAcl The entity's access control list as an IAcl object. A null acl implies default
    * permissions which make the entity readable/writeable by only the player.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Entity")
    static UBCEntityProxy *CreateEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &jsonEntityData, UBrainCloudACL *jsonEntityAcl);

    /**
    * Method updates a new entity on the server. This operation results in the entity
    * data being completely replaced by the passed in JSON string.
    *
    * Service Name - Entity
    * Service Operation - Update
    *
    * Param - entityId The id of the entity to update
    * Param - entityType The entity type as defined by the user
    * Param - jsonEntityData    The entity's data as a json string.
    * Param - jsonEntityAcl The entity's access control list as an IAcl object. A null acl implies default
    * permissions which make the entity readable/writeable by only the player.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Entity")
    static UBCEntityProxy *UpdateEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId, const FString &entityType, const FString &jsonEntityData, UBrainCloudACL *jsonEntityAcl);

    /** 
    * Method retreives a singleton entity on the server. If the entity doesn't exist, null is returned.
    *
    * Service Name - Entity
    * Service Operation - Read
    *
    * Param - entityType The entity type as defined by the user
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Entity")
    static UBCEntityProxy *GetEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId);

    /** 
    * Method to get a specific entity.
    *
    * Service Name - Entity
    * Service Operation - ReadSingleton
    *
    * Param - entityId The entity id
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Entity")
    static UBCEntityProxy *GetSingleton(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType);

    /**
    * Method updates a new singleton entity on the server. This operation results in the entity
    * data being completely replaced by the passed in JSON string. If the entity doesn't exists it is created
    *
    * Service Name - Entity
    * Service Operation - UpdateSingleton
    *
    * Param - entityType The entity type as defined by the user
    * Param - jsonEntityData    The entity's data as a json string.
    * permissions which make the entity readable/writeable by only the player.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Entity")
    static UBCEntityProxy *UpdateSingleton(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &jsonEntityData);

    /**
    * Method deletes the given entity on the server.
    *
    * Service Name - Entity
    * Service Operation - Delete
    *
    * Param - entityId The id of the entity to update
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Entity")
    static UBCEntityProxy *DeleteEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId);

    /**
    * Method deletes the given singleton entity on the server.
    *
    * Service Name - Entity
    * Service Operation - DeleteSingleton
    *
    * Param - entityType The type of the entity to delete
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Entity")
    static UBCEntityProxy *DeleteSingleton(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType);

    /** Method returns all player entities that match the given type.
    * Service Name - Entity
    * Service Operation - ReadByType
    *
    * Param - entityType The entity type to search for
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Entity")
    static UBCEntityProxy *GetEntitiesByType(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType);

    /**
    * Method updates a shared entity owned by another player. This operation results in the entity
    * data being completely replaced by the passed in JSON string.
    *
    * Service Name - Entity
    * Service Operation - UpdateShared
    *
    * Param - entityId The id of the entity to update
    * Param - targetPlayerId The id of the player who owns the shared entity
    * Param - entityType The entity type as defined by the user
    * Param - jsonEntityData    The entity's data as a json string.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Entity")
    static UBCEntityProxy *UpdateSharedEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId, const FString &targetProfileId, const FString &entityType, const FString &jsonEntityData);

    /**
    * Method gets list of entities from the server base on type and/or where clause
    *
    * Service Name - Entity
    * Service Operation - GET_LIST
    *
    * Param - whereJson Mongo style query string
    * Param - orderByJson Sort order
    * Param - maxReturn The maximum number of entities to return
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Entity")
    static UBCEntityProxy *GetList(UBrainCloudWrapper *brainCloudWrapper, const FString &whereJson, const FString &orderByJson, int32 maxReturn);

    /**
    * Method gets a count of entities based on the where clause
    *
    * Service Name - Entity
    * Service Operation - GET_LIST_COUNT
    *
    * Param - whereJson Mongo style query string
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Entity")
    static UBCEntityProxy *GetListCount(UBrainCloudWrapper *brainCloudWrapper, const FString &whereJson);

    /**
    * Method uses a paging system to iterate through user entities
    * After retrieving a page of entities with this method,
    * use GetPageOffset() to retrieve previous or next pages.
    *
    * Service Name - Entity
    * Service Operation - GetPage
    *
    * Param - context The json context for the page request.
    *                   See the portal appendix documentation for format.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Entity")
    static UBCEntityProxy *GetPage(UBrainCloudWrapper *brainCloudWrapper, const FString &context);

    /**
    * Method to retrieve previous or next pages after having called the GetPage method.
    *
    * Service Name - Entity
    * Service Operation - GetPageOffset
    *
    * Param - context The context string returned from the server from a
    *      previous call to GetPage or GetPageOffset
    * Param - pageOffset The positive or negative page offset to fetch. Uses the last page
    *      retrieved using the context string to determine a starting point.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Entity")
    static UBCEntityProxy *GetPageOffset(UBrainCloudWrapper *brainCloudWrapper, const FString &context, int32 pageOffset);

    /**
    * Partial increment of entity data field items. Partial set of items incremented as specified.
    *
    * Service Name - entity
    * Service Operation - INCREMENT_USER_ENTITY_DATA
    *
    * Param - entityId The id of the entity to update
    * Param - jsonData The entity's data object
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Entity")
    static UBCEntityProxy *IncrementUserEntityData(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId, const FString &jsonData);

    /**
    * Partial increment of entity data field items. Partial set of items incremented as specified.
    *
    * Service Name - entity
    * Service Operation - INCREMENT_SHARED_USER_ENTITY_DATA
    *
    * Param - entityId The id of the entity to update
    * Param - targetPlayerId Profile ID of the entity owner
    * Param - jsonData The entity's data object
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Entity")
    static UBCEntityProxy *IncrementSharedUserEntityData(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId, const FString &targetProfileId, const FString &jsonData);

    /**
    * Method returns a shared entity for the given player and entity ID.
    * An entity is shared if its ACL allows for the currently logged
    * in player to read the data.
    *
    * Service Name - Entity
    * Service Operation - READ_SHARED_ENTITY
    *
    * @param profileId The the profile ID of the player who owns the entity
    * @param entityId The ID of the entity that will be retrieved
    * @param callback The method to be invoked when the server response is received
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Entity")
    static UBCEntityProxy *GetSharedEntityForProfileId(UBrainCloudWrapper *brainCloudWrapper, const FString &entityId, const FString &profileId);

    /**
     * Method returns all shared entities for the given player id.
     * An entity is shared if its ACL allows for the currently logged
     * in player to read the data.
     *
     * Service Name - Entity
     * Service Operation - ReadShared
     *
     * @param profileId The player id to retrieve shared entities for
     * @param callback The method to be invoked when the server response is received
     */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Entity")
    static UBCEntityProxy *GetSharedEntitiesForProfileId(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId);


    /**
    * Method gets list of shared entities for the specified player based on type and/or where clause
    *
    * Service Name - Entity
    * Service Operation - READ_SHARED_ENTITIES_LIST
    *
    * @param profileId The player ID to retrieve shared entities for
    * @param whereJson Mongo style query
    * @param orderByJson Sort order
    * @param maxReturn The maximum number of entities to return
    * @param callback The method to be invoked when the server response is received
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Entity")
    static UBCEntityProxy *GetSharedEntitiesListForProfileId(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId, const FString &whereJson, const FString &orderByJson, int32 maxReturn);
};
