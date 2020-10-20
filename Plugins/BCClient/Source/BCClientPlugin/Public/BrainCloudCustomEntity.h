// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;
class IAcl;

class BCCLIENTPLUGIN_API BrainCloudCustomEntity
{
public:
  BrainCloudCustomEntity(BrainCloudClient *client);

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
  void createEntity(const FString &entityType, const FString &jsonEntityData, IAcl *jsonEntityAcl, int64 timeToLive, bool isOwned, IServerCallback *callback);

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
  void deleteEntity(const FString &entityType, const FString &entityId, int version, IServerCallback *callback);

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
  void getCount(const FString &entityType, const FString &whereJson, IServerCallback *callback);

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
    /**
    * @deprecated Use getEntityPage instead
    */
  void getPage(const FString &entityType, int rowsPerPage, const FString &searchJson, const FString &sortJson, bool doCount, IServerCallback *callback);

    /**
     * Retrieves first page of custom entities from the server based on the custom entity type and specified query context
     *
     * Service Name - CustomEntity
     * Service Operation - GetEntityPage
     *
     * @param entityType The entity type as defined by the user
     * @param context
     * @param callback The method to be invoked when the server response is received
     */
  void getEntityPage(const FString &entityType, const FString &context, IServerCallback *callback);

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
    /**
    * @deprecated Use getEntityPageOffset instead
    */
  void getPageOffset(const FString &entityType, const FString &context, int pageOffset, IServerCallback *callback);

    /**
     * Gets the page of custom entities from the server based on the encoded context and specified page offset.
     * 
     * Service Name - CustomEntity
     * Service Operation - GetEntityPageOffset
     *
     * @param entityType The entity type as defined by the user
     * @param context the page context
     * @param pageOffset number
     * @param callback The method to be invoked when the server response is received
     */
  void getEntityPageOffset(const FString &entityType, const FString &context, int pageOffset, IServerCallback *callback);

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
  void readEntity(const FString &entityType, const FString &entityId, IServerCallback *callback);

    /**
     * Increments the specified fields by the specified amount within custom entity data on the server, enforcing ownership/ACL permissions.
     * 
     * Service Name - CustomEntity
     * Service Operation - IncrementData
     *
     * @param entityType The entity type as defined by the user
     * @param entityId 
     * @param fieldJson
     * @param callback The method to be invoked when the server response is received
     */
  void incrementData(const FString &entityType, const FString &entityId, const FString &fieldsJson, IServerCallback *callback);

    /**
     * Creates new custom entity.
     *
     * Service Name - CustomEntity
     * Service Operation - GetRandomEntitiesMatching
     *
     * @param entityType The entity type as defined by the user
     * @param whereJson what to get count of
     * @param maxReturn
     * @param callback The method to be invoked when the server response is received
     */
  void getRandomEntitiesMatching(const FString &entityType, const FString &whereJson, const int64 &maxReturn, IServerCallback *callback);


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
  void updateEntity(const FString &entityType, const FString &entityId, int version, const FString &dataJson, IAcl *jsonEntityAcl, int64 timeToLive, IServerCallback *callback);

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
  void updateEntityFields(const FString &entityType, const FString &entityId, int version, const FString &fieldsJson, IServerCallback *callback);

   /**
    * deletes entities defined within the deleteCriteria.
    * 
    * Service Name - CustomEntity
    * Service Operation - deleteEntities
    *
    * @param entityType The entity type as defined by the user
    * @param deleteCriteria
    * @param callback The method to be invoked when the server response is received
    */
  void deleteEntities(const FString &entityType, const FString &deleteCriteria, IServerCallback *callback);

  /**
     * Reads the custom entity singleton owned by the session's user.
     * 
     * Service Name - CustomEntity
     * Service Operation - readSingleton
     *
     * @param entityType The entity type as defined by the user
     * @param callback The method to be invoked when the server response is received
     */
  void readSingleton(const FString &entityType, IServerCallback *callback);

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
  void updateSingleton(const FString &entityType, int version, const FString &dataJson, IAcl *jsonEntityAcl, int64 timeToLive, IServerCallback *callback);

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
  void updateSingletonFields(const FString &entityType, int version, const FString &fieldsJson, IServerCallback *callback);

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
  void deleteSingleton(const FString &entityType, int version, IServerCallback *callback);


private:
  BrainCloudClient *_client = nullptr;
};
