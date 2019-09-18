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
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|CustomEntity")
  static UBCCustomEntityProxy *GetPage(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, int rowsPerPage, const FString &searchJson, const FString &sortJson, bool doCount);

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
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|CustomEntity")
  static UBCCustomEntityProxy *GetPageOffset(UBrainCloudWrapper *brainCloudWrapper, const FString &entityType, const FString &context, int pageOffset);

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

};
