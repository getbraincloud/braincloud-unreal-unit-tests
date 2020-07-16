// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BrainCloudACL.h"
#include "BCCustomEntityProxy.generated.h"

UCLASS(MinimalAPI)
class UBCCustomEntityProxy : public UBCBlueprintCallProxyBase
{
    GENERATED_BODY()

  public:
    UBCCustomEntityProxy(const FObjectInitializer &ObjectInitializer);

   /**
     * Creates new custom entity.
     *
     * Service Name - CustomEntity
     * Service Operation - CreateEntity
     *
     * @param entityType The entity type as defined by the user
     * @param jsonEntityData    The entity's data as a json string
     * @param jsonEntityAcl The entity's access control list as an IAcl object. A null acl implies default
     * permissions which make the entity readable/writeable by only the player.
     * @param timeToLive
     * @param callback The method to be invoked when the server response is received
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|CustomEntity")
  static UBCCustomEntityProxy *CreateEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &jsonEntityData, UBrainCloudACL *jsonEntityAcl, const FString &timeToLive, bool isOwned);

  /**
     * Deletes the specified custom entity on the server.
     *
     * Service Name - CustomEntity
     * Service Operation - DeleteEntity
     *
     * @param entityType The entity type as defined by the user
     * @param entityId  The entity's data as a json string
     * @param version
     * @param callback The method to be invoked when the server response is received
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|CustomEntity")
  static UBCCustomEntityProxy *DeleteEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &entityId, int version);

    /**
     * Creates new custom entity.
     *
     * Service Name - CustomEntity
     * Service Operation - GetCount
     *
     * @param entityType The entity type as defined by the user
     * @param whereJson what to get count of
     * @param callback The method to be invoked when the server response is received
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|CustomEntity")
  static UBCCustomEntityProxy *GetCount(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &whereJson);

    /**
     * Retrieves first page of custom entities from the server based on the custom entity type and specified query context
     *
     * Service Name - CustomEntity
     * Service Operation - GetPage
     *
     * @param entityType The entity type as defined by the user
     * @param rowsPerPage num rows
     * @param searchJson what to search
     * @param doCount whether to count
     * @param callback The method to be invoked when the server response is received
     */
  //UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|CustomEntity")
   UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", DeprecatedFunction,DeprecatedMessage="Use GetEntityPage() instead"), Category = "BrainCloud|CustomEntity")
  static UBCCustomEntityProxy *GetPage(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, int rowsPerPage, const FString &searchJson, const FString &sortJson, bool doCount);

	/**
	* Method uses a paging system to iterate through Custom Entities
	* After retrieving a page of Custom Entities with this method,
	* use GetEntityPageOffset() to retrieve previous or next pages.
	*
	* Service Name - CustomEntity
	* Service Operation - GetEntityPage
	*
	* Param - context The json context for the page request. See the portal appendix documentation for format.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Custom Entity")
	static UBCCustomEntityProxy *GetEntityPage(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &context);

    /**
     * Gets the page of custom entities from the server based on the encoded context and specified page offset.
     * 
     * Service Name - CustomEntity
     * Service Operation - GetPageOffset
     *
     * @param entityType The entity type as defined by the user
     * @param context the page context
     * @param pageOffset number
     * @param callback The method to be invoked when the server response is received
     */

  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", DeprecatedFunction,DeprecatedMessage="Use GetEntityPageOffset() instead"), Category = "BrainCloud|CustomEntity")
  static UBCCustomEntityProxy *GetPageOffset(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &context, int pageOffset);

  	/**
	* Method to retrieve previous or next pages after having called the GetEntityPage method.
	*
	* Service Name - CustomEntity
	* Service Operation - GetEntityPageOffset
	*
	* Param - context The context string returned from the server from a
	*      previous call to GetEntityPage or GetEntityPageOffset
	* Param - pageOffset The positive or negative page offset to fetch. Uses the last page
	*      retrieved using the context string to determine a starting point.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Custom Entity")
	static UBCCustomEntityProxy *GetEntityPageOffset(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType,const FString &context, int pageOffset);


    /**
     * Reads a custom entity.
     * 
     * Service Name - CustomEntity
     * Service Operation - ReadEntity
     *
     * @param entityType The entity type as defined by the user
     * @param entityId
     * @param callback The method to be invoked when the server response is received
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|CustomEntity")
  static UBCCustomEntityProxy *ReadEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &entityId);

    /**
     * Reads a custom entity.
     * 
     * Service Name - CustomEntity
     * Service Operation - ReadEntity
     *
     * @param entityType The entity type as defined by the user
     * @param entityId
     * @param fieldsJson
     * @param callback The method to be invoked when the server response is received
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|CustomEntity")
  static UBCCustomEntityProxy *IncrementData(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &entityId, const FString &fieldsJson);


    /**
     * Reads a custom entity.
     * 
     * Service Name - CustomEntity
     * Service Operation - UpdateEntity
     *
     * @param entityType The entity type as defined by the user
     * @param entityId
     * @param version
     * @param dataJson
     * @param acl
     * @param timeToLive
     * @param callback The method to be invoked when the server response is received
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|CustomEntity")
  static UBCCustomEntityProxy *UpdateEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &entityId, int version, const FString &dataJson, UBrainCloudACL *jsonEntityAcl, const FString &timeToLive);

    /**
     * Sets the specified fields within custom entity data on the server.
     * 
     * Service Name - CustomEntity
     * Service Operation - UpdateEntityFields
     *
     * @param entityType The entity type as defined by the user
     * @param entityId
     * @param version
     * @param fieldsJson
     * @param callback The method to be invoked when the server response is received
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|CustomEntity")
  static UBCCustomEntityProxy *UpdateEntityFields(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &entityId, int version, const FString &fieldsJson);

    /**
     * deletes entities based on the deleteCriteria
     * 
     * Service Name - CustomEntity
     * Service Operation - DeleteEntities
     *
     * @param entityType The entity type as defined by the user
     * @param deleteCriteria
     * @param callback The method to be invoked when the server response is received
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|CustomEntity")
  static UBCCustomEntityProxy *DeleteEntities(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &deleteCriteria);

    /**
     * Reads the custom entity singleton owned by the session's user.
     * 
     * Service Name - CustomEntity
     * Service Operation - readSingleton
     *
     * @param entityType The entity type as defined by the user
     * @param callback The method to be invoked when the server response is received
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|CustomEntity")
  static UBCCustomEntityProxy *ReadSingleton(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType);


    /**
     * Updates the singleton owned by the user for the specified custom entity type on the server, creating the singleton if it does not exist. This operation results in the owned singleton's data being completely replaced by the passed in JSON object.
     * 
     * Service Name - CustomEntity
     * Service Operation - updateSingleton
     *
     * @param entityType The entity type as defined by the user
     * @param version
     * @param dataJson
     * @param jsonEntityAcl
     * @param timeToLive
     * @param callback The method to be invoked when the server response is received
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|CustomEntity")
  static UBCCustomEntityProxy *UpdateSingleton(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, int version, const FString &dataJson, UBrainCloudACL *jsonEntityAcl, const FString &timeToLive);


    /**
     * Partially updates the data, of the singleton owned by the user for the specified custom entity type, with the specified fields, on the server
     * 
     * Service Name - CustomEntity
     * Service Operation - updateSingletonFields
     *
     * @param entityType The entity type as defined by the user
     * @param version
     * @param fieldsJson
     * @param callback The method to be invoked when the server response is received
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|CustomEntity")
  static UBCCustomEntityProxy *UpdateSingletonFields(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, int version, const FString &fieldsJson);

    /**
     * Deletes the specified custom entity singleton, owned by the session's user, for the specified entity type, on the server.
     * 
     * Service Name - CustomEntity
     * Service Operation - deleteSingleton
     *
     * @param entityType The entity type as defined by the user
     * @param version
     * @param callback The method to be invoked when the server response is received
     */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|CustomEntity")
  static UBCCustomEntityProxy *DeleteSingleton(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, int version);



};
