// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;
class IAcl;

class BCCLIENTPLUGIN_API BrainCloudGlobalEntity
{
  public:
	BrainCloudGlobalEntity(BrainCloudClient *client);

	/**
	* Method creates a new entity on the server.
	*
	* Service Name - GlobalEntity
	* Service Operation - Create
	*
	* @param entityType The entity type as defined by the user
	* @param timeToLive Sets expiry time for entity if > 0
	* @param jsonEntityAcl The entity's access control object
	* @param jsonEntityData The entity's data as a json string
	* @param callback The callback object
	*/
	void createEntity(const FString &entityType, int64 timeToLive, IAcl *jsonEntityAcl,
					  const FString &jsonEntityData, IServerCallback *callback);

	/**
	* Method creates a new entity on the server with an indexed id.
	*
	* Service Name - GlobalEntity
	* Service Operation - CreateWithIndexedId
	*
	* @param entityType The entity type as defined by the user
	* @param indexedId A secondary ID that will be indexed
	* @param timeToLive Sets expiry time for entity if > 0
	* @param jsonEntityAcl The entity's access control object list as json.
	* @param jsonEntityData The entity's data as a json string
	* @param callback The callback object
	*/
	void createEntityWithIndexedId(const FString &entityType, const FString &indexedId, int64 timeToLive,
								   IAcl *jsonEntityAcl, const FString &jsonEntityData, IServerCallback *callback);

	/**
	* Method updates an existing entity on the server.
	*
	* Service Name - GlobalEntity
	* Service Operation - Update
	*
	* @param entityId The entity ID
	* @param version The version of the entity to update
	* @param jsonEntityData The entity's data as a json string
	* @param callback The callback object
	*/
	void updateEntity(const FString &entityId, int32 version, const FString &jsonEntityData, IServerCallback *callback);

	/**
	* Method updates an existing entity's Acl on the server.
	*
	* Service Name - GlobalEntity
	* Service Operation - UpdateAcl
	*
	* @param entityId The entity ID
	* @param version The version of the entity to update
	* @param jsonEntityAcl The entity's access control object list.
	* @param callback The callback object
	*/
	void updateEntityAcl(const FString &entityId, int32 version, IAcl *jsonEntityAcl, IServerCallback *callback);

	/**
	* Method updates an existing entity's time to live on the server.
	*
	* Service Name - GlobalEntity
	* Service Operation - UpdateTimeToLive
	*
	* @param entityId The entity ID
	* @param version The version of the entity to update
	* @param timeToLive Sets expiry time for entity if > 0
	* @param callback The callback object
	*/
	void updateEntityTimeToLive(const FString &entityId, int32 version, int64 timeToLive, IServerCallback *callback);

	/**
	* Method deletes an existing entity on the server.
	*
	* Service Name - GlobalEntity
	* Service Operation - Delete
	*
	* @param entityId The entity ID
	* @param version The version of the entity to delete
	* @param callback The callback object
	*/
	void deleteEntity(const FString &entityId, int32 version, IServerCallback *callback);

	/**
	* Method reads an existing entity from the server.
	*
	* Service Name - GlobalEntity
	* Service Operation - Read
	*
	* @param entityId The entity ID
	* @param callback The callback object
	*/
	void readEntity(const FString &entityId, IServerCallback *callback);

	/**
	* Method gets list of entities from the server base on type and/or where clause
	*
	* Service Name - GlobalEntity
	* Service Operation - GetList
	*
	* @param where Mongo style query string
	* @param orderBy Sort order
	* @param maxReturn The maximum number of entities to return
	* @param callback The callback object
	*/
	void getList(const FString &where, const FString &orderBy, int32 maxReturn, IServerCallback *callback);

	/**
	* Method gets list of entities from the server base on indexed id
	*
	* Service Name - GlobalEntity
	* Service Operation - GetListByIndexedId
	*
	* @param entityIndexedId The entity indexed Id
	* @param maxReturn The maximum number of entities to return
	* @param callback The callback object
	*/
	void getListByIndexedId(const FString &entityIndexedId, int32 maxReturn, IServerCallback *callback);

	/**
	* Method gets a count of entities based on the where clause
	*
	* Service Name - GlobalEntity
	* Service Operation - GetListCount
	*
	* @param where Mongo style query string
	* @param callback The callback object
	*/
	void getListCount(const FString &where, IServerCallback *callback);

	/**
	* Method uses a paging system to iterate through Global Entities
	* After retrieving a page of Global Entities with this method,
	* use GetPageOffset() to retrieve previous or next pages.
	*
	* Service Name - GlobalEntity
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
	* Service Name - GlobalEntity
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
	* Partial increment of global entity data field items. Partial set of items incremented as specified.
	*
	* Service Name - globalEntity
	* Service Operation - INCREMENT_GLOBAL_ENTITY_DATA
	*
	* @param entityId The id of the entity to update
	* @param jsonData The entity's data object
	* @param callback The callback object
	*/
	void incrementGlobalEntityData(const FString &entityId, const FString &jsonData, IServerCallback *callback = nullptr);

	/**
	* Gets a list of up to randomCount randomly selected entities from the server based on the where condition and specified maximum return count.
	*
	* Service Name - globalEntity
	* Service Operation - GET_RANDOM_ENTITIES_MATCHING
	*
	* @param where Mongo style query string.
	* @param maxReturn The maximum number of entities to return.
	* @param callback The callback object
	*/
	void getRandomEntitiesMatching(const FString &where, int32 maxReturn, IServerCallback *callback = nullptr);

	/**
	* Method updates an existing entity's Owner and ACL on the server.
	*
	* Service Name - globalEntity
	* Service Operation - UPDATE_ENTITY_OWNER_AND_ACL
	*
	* @param entityId The entity ID
	* @param version The version of the entity to update
	* @param entityIndexedId the id index of the entity 
	* @param callback The callback object
	*/
	void updateEntityIndexedId(const FString &entityId, int32 version, const FString &entityIndexedId, IServerCallback *callback = nullptr);

	/**
	* Method updates an existing entity's Owner and ACL on the server.
	*
	* Service Name - globalEntity
	* Service Operation - UPDATE_ENTITY_OWNER_AND_ACL
	*
	* @param entityId The entity ID
	* @param version The version of the entity to update
	* @param ownerId The owner ID
	* @param jsonEntityAcl The entity's access control list as JSON.
	* @param callback The callback object
	*/
	void updateEntityOwnerAndAcl(const FString &entityId, int32 version, const FString &ownerId, IAcl *jsonEntityAcl, IServerCallback *callback);

	/**
	* Method clears the owner id of an existing entity and sets the ACL on the server.
	*
	* Service Name - globalEntity
	* Service Operation - MAKE_SYSTEM_ENTITY
	*
	* @param entityId The entity ID
	* @param version The version of the entity to update
	* @param jsonEntityAcl The entity's access control list as JSON.
	* @param callback The callback object
	*/
	void makeSystemEntity(const FString &entityId, int32 version, IAcl *jsonEntityAcl, IServerCallback *callback);

  private:
	BrainCloudClient *_client = nullptr;
};
