// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <string>
#include "braincloud/BrainCloudTypes.h"

namespace BrainCloud
{
	class IServerCallback;
	class BrainCloudClient;

	class BrainCloudGlobalEntity
	{
	public:
		BrainCloudGlobalEntity(BrainCloudClient* in_client);

		/**
		* Method creates a new entity on the server.
		*
		* Service Name - GlobalEntity
		* Service Operation - Create
		*
		* @param in_entityType The entity type as defined by the user
		* @param in_timeToLive Sets expiry time for entity in milliseconds if > 0
		* @param in_jsonEntityAcl The entity's access control list as json. A null acl implies default
		* @param in_jsonEntityData  The entity's data as a json string
		* @param in_callback The callback object
		*/
		void createEntity(const std::string& in_entityType, int64_t in_timeToLive, const std::string& in_jsonEntityAcl,
			const std::string& in_jsonEntityData, IServerCallback * in_callback = NULL);

		/**
		* Method creates a new entity on the server with an indexed id.
		*
		* Service Name - GlobalEntity
		* Service Operation - CreateWithIndexedId
		*
		* @param in_entityType The entity type as defined by the user
		* @param in_indexedId A secondary ID that will be indexed
		* @param in_timeToLive Sets expiry time for entity in milliseconds if > 0
		* @param in_jsonEntityAcl The entity's access control list as json. A null acl implies default
		* @param in_jsonEntityData  The entity's data as a json string
		* @param in_callback The callback object
		*/
		void createEntityWithIndexedId(const std::string& in_entityType, const std::string& in_indexedId, int64_t in_timeToLive,
			const std::string& in_jsonEntityAcl, const std::string& in_jsonEntityData, IServerCallback * in_callback = NULL);

		/**
		* Method updates an existing entity on the server.
		*
		* Service Name - GlobalEntity
		* Service Operation - Update
		*
		* @param in_entityId The entity ID
		* @param in_version The version of the entity to update
		* @param in_jsonEntityData  The entity's data as a json string
		* @param in_callback The callback object
		*/
		void updateEntity(const std::string& in_entityId, int64_t in_version, const std::string& in_jsonEntityData, IServerCallback * in_callback = NULL);

		/**
		* Method updates an existing entity's Acl on the server.
		*
		* Service Name - GlobalEntity
		* Service Operation - UpdateAcl
		*
		* @param in_entityId The entity ID
		* @param in_version The version of the entity to update
		* @param in_jsonEntityAcl The entity's access control list as json.
		* @param in_callback The callback object
		*/
		void updateEntityAcl(const std::string& in_entityId, int64_t in_version, const std::string& in_jsonEntityAcl, IServerCallback * in_callback = NULL);

		/**
		* Method updates an existing entity's time to live on the server.
		*
		* Service Name - GlobalEntity
		* Service Operation - UpdateTimeToLive
		*
		* @param in_entityId The entity ID
		* @param in_version The version of the entity to update
		* @param in_timeToLive Sets expiry time for entity in milliseconds if > 0
		* @param in_callback The callback object
		*/
		void updateEntityTimeToLive(const std::string& in_entityId, int64_t in_version, int64_t in_timeToLive, IServerCallback * in_callback = NULL);

		/**
		* Method deletes an existing entity on the server.
		*
		* Service Name - GlobalEntity
		* Service Operation - Delete
		*
		* @param in_entityId The entity ID
		* @param in_version The version of the entity to delete
		* @param in_callback The callback object
		*/
		void deleteEntity(const std::string& in_entityId, int64_t in_version, IServerCallback * in_callback = NULL);

		/**
		* Method reads an existing entity from the server.
		*
		* Service Name - GlobalEntity
		* Service Operation - Read
		*
		* @param in_entityId The entity ID
		* @param in_callback The callback object
		*/
		void readEntity(const std::string& in_entityId, IServerCallback * in_callback = NULL);

		/**
		* Method gets list of entities from the server base on type and/or where clause
		*
		* Service Name - GlobalEntity
		* Service Operation - GetList
		*
		* @param in_where Mongo style query string
		* @param in_orderBy Sort order
		* @param in_maxReturn The maximum number of entities to return
		* @param in_callback The callback object
		*/
		void getList(const std::string& in_where, const std::string& in_orderBy, int64_t in_maxReturn, IServerCallback * in_callback = NULL);

		/**
		* Method gets list of entities from the server base on indexed id
		*
		* Service Name - GlobalEntity
		* Service Operation - GetListByIndexedId
		*
		* @param in_entityIndexedId The entity indexed Id
		* @param in_maxReturn The maximum number of entities to return
		* @param in_callback The callback object
		*/
		void getListByIndexedId(const std::string& in_entityIndexedId, int64_t in_maxReturn, IServerCallback * in_callback = NULL);

		/**
		* Method gets a count of entities based on the where clause
		*
		* Service Name - GlobalEntity
		* Service Operation - GetListCount
		*
		* @param in_where Mongo style query string
		* @param in_callback The callback object
		*/
		void getListCount(const std::string& in_where, IServerCallback * in_callback = NULL);

		/**
		 * Method uses a paging system to iterate through Global Entities
		 * After retrieving a page of Global Entities with this method,
		 * use GetPageOffset() to retrieve previous or next pages.
		 *
		 * Service Name - GlobalEntity
		 * Service Operation - GetPage
		 *
		 * @param in_context The json context for the page request.
		 *                   See the portal appendix documentation for format.
		 * @param in_callback The callback object
		 */
		void getPage(const char * in_context, IServerCallback * in_callback = NULL);

		/**
		 * Method to retrieve previous or next pages after having called the GetPage method.
		 *
		 * Service Name - GlobalEntity
		 * Service Operation - GetPageOffset
		 *
		 * @param in_context The context string returned from the server from a
		 *      previous call to GetPage or GetPageOffset
		 * @param in_pageOffset The positive or negative page offset to fetch. Uses the last page
		 *      retrieved using the context string to determine a starting point.
		 * @param in_callback The callback object
		 */
		void getPageOffset(const char * in_context, int in_pageOffset, IServerCallback * in_callback = NULL);

		/**
		* Partial increment of global entity data field items. Partial set of items incremented as specified.
		*
		* Service Name - globalEntity
		* Service Operation - INCREMENT_GLOBAL_ENTITY_DATA
		*
		* @param in_entityId The id of the entity to update
		* @param in_jsonData The entity's data object
		* @param in_callback The callback object
		*/
		void incrementGlobalEntityData(const char * in_entityId, std::string in_jsonData, IServerCallback * in_callback = NULL);

		/**
    	* Gets a list of up to randomCount randomly selected entities from the server based on the where condition and specified maximum return count.
    	*
    	* Service Name - globalEntity
    	* Service Operation - GET_RANDOM_ENTITIES_MATCHING
    	*
    	* @param in_where Mongo style query string
    	* @param in_maxReturn The maximum number of entities to return
    	* @param in_callback The callback object
    	*/
		void getRandomEntitiesMatching(const std::string& in_where, int64_t in_maxReturn, IServerCallback * in_callback);

		/**
		* Method updates an existing entity's Owner and ACL on the server.
		*
		* Service Name - globalEntity
		* Service Operation - UPDATE_ENTITY_OWNER_AND_ACL
		*
		* @param in_entityId The entity ID
		* @param in_version The version of the entity to update
		* @param in_ownerId The owner ID
		* @param in_jsonEntityAcl The entity's access control list as JSON.
		* @param in_callback The callback object
		*/
		void updateEntityOwnerAndAcl(const char * in_entityId, int64_t in_version, const char * in_ownerId, const std::string& in_jsonEntityAcl, IServerCallback * in_callback = NULL);

		/**
		* Method clears the owner id of an existing entity and sets the ACL on the server.
		*
		* Service Name - globalEntity
		* Service Operation - MAKE_SYSTEM_ENTITY
		*
		* @param in_entityId The entity ID
		* @param in_version The version of the entity to update
		* @param in_jsonEntityAcl The entity's access control list as JSON.
		* @param in_callback The callback object
		*/
		void makeSystemEntity(const char * in_entityId, int64_t in_version, const std::string& in_jsonEntityAcl, IServerCallback * in_callback = NULL);

	private:
		BrainCloudClient * m_client;
	};
}

