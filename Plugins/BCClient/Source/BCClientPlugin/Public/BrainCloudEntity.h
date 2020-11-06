// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;
class IAcl;

class BCCLIENTPLUGIN_API BrainCloudEntity
{
public:
  BrainCloudEntity(BrainCloudClient *client);

  /**
     * Method creates a new entity on the server.
     *
     * Service Name - Entity
     * Service Operation - Create
     *
     * @param entityType The entity type as defined by the user
     * @param jsonEntityData    The entity's data as a json string
     * @param jsonEntityAcl The entity's access control list as an IAcl object. A null acl implies default
     * permissions which make the entity readable/writeable by only the player.
     * @param callback The method to be invoked when the server response is received
     */
  void createEntity(const FString &entityType, const FString &jsonEntityData, IAcl *jsonEntityAcl, IServerCallback *callback);

  /**
     * Method updates a new entity on the server. This operation results in the entity
     * data being completely replaced by the passed in JSON string.
     *
     * Service Name - Entity
     * Service Operation - Update
     *
     * @param entityId The id of the entity to update
     * @param entityType The entity type as defined by the user
     * @param jsonEntityData    The entity's data as a json string.
     * @param jsonEntityAcl The entity's access control list as an IAcl object. A null acl implies default
     * permissions which make the entity readable/writeable by only the player.
     * @param callback The method to be invoked when the server response is received
     */
  void updateEntity(const FString &entityId, const FString &entityType, const FString &jsonEntityData, IAcl *jsonEntityAcl, IServerCallback *callback);

  /** Method to get a specific entity.
    *
    * Service Name - Entity
    * Service Operation - Read
    *
    * @param entityId The entity id
    * @param callback The method to be invoked when the server response is received
    */
  void getEntity(const FString &entityId, IServerCallback *callback);

  /**
    * Method retreives a singleton entity on the server. If the entity doesn't exist, null is returned.
    *
    * Service Name - Entity
    * Service Operation - ReadSingleton
    *
    * @param entityType The entity type as defined by the user
    * @param callback The method to be invoked when the server response is received
    */
  void getSingleton(const FString &entityType, IServerCallback *callback);

  /**
    * Method updates a new singleton entity on the server. This operation results in the entity
    * data being completely replaced by the passed in JSON string. If the entity doesn't exists it is created
    *
    * Service Name - Entity
    * Service Operation - UpdateSingleton
    *
    * @param entityType The entity type as defined by the user
    * @param jsonEntityData The entity's data as a json string.
    * permissions which make the entity readable/writeable by only the player.
    * @param callback The method to be invoked when the server response is received
    */
  void updateSingleton(const FString &entityType, const FString &jsonEntityData, IServerCallback *callback);

  /**
     * Method deletes the given entity on the server.
     *
     * Service Name - Entity
     * Service Operation - Delete
     *
     * @param entityId The id of the entity to update
     * @param callback The method to be invoked when the server response is received
     */
  void deleteEntity(const FString &entityId, IServerCallback *callback);

  /**
    * Method deletes the given singleton entity on the server.
    *
    * Service Name - Entity
    * Service Operation - DeleteSingleton
    *
    * @param entityType The type of the entity to delete
    * @param callback The method to be invoked when the server response is received
    */
  void deleteSingleton(const FString &entityType, IServerCallback *callback);

  /** Method returns all player entities that match the given type.
     * Service Name - Entity
     * Service Operation - ReadByType
     *
     * @param entityType The entity type to search for
     * @param callback The method to be invoked when the server response is received
     */
  void getEntitiesByType(const FString &entityType, IServerCallback *callback);

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
  void getSharedEntityForProfileId(const FString &profileId, const FString &entityId, IServerCallback *callback = nullptr);

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
  void getSharedEntitiesForProfileId(const FString &profileId, IServerCallback *callback);

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
  void getSharedEntitiesListForProfileId(const FString &profileId, const FString &whereJson, const FString &orderByJson, int32 maxReturn, IServerCallback *callback = nullptr);

  /**
     * Method updates a shared entity owned by another player. This operation results in the entity
     * data being completely replaced by the passed in JSON string.
     *
     * Service Name - Entity
     * Service Operation - UpdateShared
     *
     * @param entityId The id of the entity to update
     * @param targetProfileId The id of the player who owns the shared entity
     * @param entityType The entity type as defined by the user
     * @param jsonEntityData    The entity's data as a json string.
     * @param callback The method to be invoked when the server response is received
     */
  void updateSharedEntity(const FString &entityId, const FString &targetProfileId, const FString &entityType, const FString &jsonEntityData, IServerCallback *callback);

  /**
    * Method gets list of entities from the server base on type and/or where clause
    *
    * Service Name - Entity
    * Service Operation - GET_LIST
    *
    * @param whereJson Mongo style query string
    * @param orderByJson Sort order
    * @param maxReturn The maximum number of entities to return
    * @param callback The callback object
    */
  void getList(const FString &whereJson, const FString &orderByJson, int32 maxReturn, IServerCallback *callback);

  /**
    * Method gets a count of entities based on the where clause
    *
    * Service Name - Entity
    * Service Operation - GET_LIST_COUNT
    *
    * @param whereJson Mongo style query string
    * @param callback The callback object
    */
  void getListCount(const FString &whereJson, IServerCallback *callback);

  /**
    * Method uses a paging system to iterate through user entities
    * After retrieving a page of entities with this method,
    * use GetPageOffset() to retrieve previous or next pages.
    *
    * Service Name - Entity
    * Service Operation - GetPage
    *
    * @param context The json context for the page request.
    *                   See the portal appendix documentation for format.
    * @param callback The callback object
    */
  void getPage(const FString &context, IServerCallback *callback);

  /**
    * Method to retrieve previous or next pages after having called the GetPage method.
    *
    * Service Name - Entity
    * Service Operation - GetPageOffset
    *
    * @param context The context string returned from the server from a
    *      previous call to GetPage or GetPageOffset
    * @param pageOffset The positive or negative page offset to fetch. Uses the last page
    *      retrieved using the context string to determine a starting point.
    * @param callback The callback object
    */
  void getPageOffset(const FString &context, int32 pageOffset, IServerCallback *callback);

  /**
    * Partial increment of entity data field items. Partial set of items incremented as specified.
    *
    * Service Name - entity
    * Service Operation - INCREMENT_USER_ENTITY_DATA
    *
    * @param entityId The id of the entity to update
    * @param jsonData The entity's data object
    * @param returnData Should the entity be returned in the response?
    * @param callback The callback object
    */
  void incrementUserEntityData(const FString &entityId, const FString &jsonData, IServerCallback *callback = nullptr);

  /**
	* Partial increment of entity data field items. Partial set of items incremented as specified.
	*
	* Service Name - entity
	* Service Operation - INCREMENT_SHARED_USER_ENTITY_DATA
	*
	* @param entityId The id of the entity to update
	* @param targetProfileId Profile ID of the entity owner
	* @param jsonData The entity's data object
	* @param returnData Should the entity be returned in the response?
	* @param callback The callback object
	*/
  void incrementSharedUserEntityData(const FString &entityId, const FString &targetProfileId, const FString &jsonData, IServerCallback *callback = nullptr);

private:
  BrainCloudClient *_client = nullptr;
};
