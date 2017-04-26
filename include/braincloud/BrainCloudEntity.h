// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <string>

#include "braincloud/BrainCloudTypes.h"

namespace BrainCloud {

	class IServerCallback;
	class BrainCloudClient;

	class BrainCloudEntity
	{
	public:
		BrainCloudEntity(BrainCloudClient* in_client);

		/**
		 * Method creates a new entity on the server.
		 *
		 * Service Name - Entity
		 * Service Operation - Create
		 *
		 * @param in_entityType The entity type as defined by the user
		 * @param in_jsonEntityData The entity's data as a json string
		 * @param in_jsonEntityAcl The entity's access control list as json. A null acl implies default
		 * permissions which make the entity readable/writeable by only the user.
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void createEntity(const char * in_entityType, const std::string& in_jsonEntityData, const std::string& in_jsonEntityAcl, IServerCallback * in_callback = NULL);

		/**
		 * Method updates a new entity on the server. This operation results in the entity
		 * data being completely replaced by the passed in JSON string.
		 *
		 * Service Name - Entity
		 * Service Operation - Update
		 *
		 * @param in_entityId The id of the entity to update
		 * @param in_entityType The entity type as defined by the user
		 * @param in_jsonEntityData The entity's data as a json string.
		 * @param in_jsonEntityAcl The entity's access control list as json. A null acl implies default
		 * permissions which make the entity readable/writeable by only the user.
		 * @param in_version Current version of the entity. If the version of the
		 * entity on the server does not match the version passed in, the
		 * server operation will fail. Use -1 to skip version checking.
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void updateEntity(
			const char * in_entityId,
			const char * in_entityType,
			const std::string& in_jsonEntityData,
			const std::string& in_jsonEntityAcl,
			int64_t in_version,
			IServerCallback * in_callback = NULL);

		/**
		* Method updates a new singleton entity on the server. This operation results in the entity
		* data being completely replaced by the passed in JSON string. If the entity doesn't exists it is created
		*
		* Service Name - Entity
		* Service Operation - UpdateSingleton
		*
		* @param in_entityType The entity type as defined by the user
		* @param in_jsonEntityData  The entity's data as a json string.
		* permissions which make the entity readable/writeable by only the user.
		* @param in_jsonEntityAcl The entity's access control list as json. A null acl implies default
		* permissions which make the entity readable/writeable by only the user.
		* @param in_version Current version of the entity. If the version of the
		* entity on the server does not match the version passed in, the
		* server operation will fail. Use -1 to skip version checking.
		* @param in_callback The method to be invoked when the server response is received
		*/
		void updateSingleton(const char * in_entityType, const std::string& in_jsonEntityData, const std::string& in_jsonEntityAcl, int64_t in_version, IServerCallback * in_callback = NULL);

		/**
		 * Method deletes the given entity on the server.
		 *
		 * Service Name - Entity
		 * Service Operation - Delete
		 *
		 * @param in_entityId The id of the entity to update
		 * @param in_version Current version of the entity. If the version of the
		 * entity on the server does not match the version passed in, the
		 * server operation will fail. Use -1 to skip version checking.
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void deleteEntity(const char * in_entityId, int64_t in_version, IServerCallback * in_callback = NULL);

		/**
		* Method deletes the given singleton entity on the server.
		*
		* Service Name - Entity
		* Service Operation - DeleteSingleton
		*
		* @param in_entityType The type of the entity to delete
		* @param in_version Current version of the entity. If the version of the
		* entity on the server does not match the version passed in, the
		* server operation will fail. Use -1 to skip version checking.
		* @param in_callback The method to be invoked when the server response is received
		*/
		void deleteSingleton(const char * in_entityType, int64_t in_version, IServerCallback * in_callback = NULL);

		/** Method to get a specific entity.
		 *
		 * Service Name - Entity
		 * Service Operation - Read
		 *
		 * @param in_entityId The entity id
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void getEntity(const char * in_entityId, IServerCallback * in_callback = NULL);

		/** Method retreives a singleton entity on the server. If the entity doesn't exist, null is returned.
		 *
		 * Service Name - Entity
		 * Service Operation - ReadSingleton
		 *
		 * @param in_entityType The entity type as defined by the user
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void getSingleton(const char * in_entityType, IServerCallback * in_callback = NULL);

		/** Method returns all user entities that match the given type.
		 * Service Name - Entity
		 * Service Operation - ReadByType
		 *
		 * @param in_entityType The entity type to search for
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void getEntitiesByType(const char * in_entityType, IServerCallback * in_callback = NULL);

		/**
		* @deprecated Use getSharedEntityForProfileId() instead - Removal after September 1 2017
		*/
		DEPRECATED
		void getSharedEntityForPlayerId(const char * in_profileId, const char * in_entityId, IServerCallback * in_callback = NULL);

		/**
		* Method returns a shared entity for the given user and entity ID.
		* An entity is shared if its ACL allows for the currently logged
		* in user to read the data.
		*
		* Service Name - Entity
		* Service Operation - READ_SHARED_ENTITY
		*
		* @param in_profileId The the profile ID of the user who owns the entity
		* @param in_entityId The ID of the entity that will be retrieved
		* @param in_callback The method to be invoked when the server response is received
		*/
		void getSharedEntityForProfileId(const char * in_profileId, const char * in_entityId, IServerCallback * in_callback = NULL);

		/**
		* @deprecated Use getSharedEntitiesForProfileId() instead - Removal after September 1 2017
		*/
		DEPRECATED
		void getSharedEntitiesForPlayerId(const char * in_profileId, IServerCallback * in_callback = NULL);

		/**
		 * Method returns all shared entities for the given profile id.
		 * An entity is shared if its ACL allows for the currently logged
		 * in user to read the data.
		 *
		 * Service Name - Entity
		 * Service Operation - ReadShared
		 *
		 * @param in_profileId The profile id to retrieve shared entities for
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void getSharedEntitiesForProfileId(const char * in_profileId, IServerCallback * in_callback = NULL);

		/**
		* @deprecated Use getSharedEntitiesListForProfileId() instead - Removal after September 1 2017
		*/
		DEPRECATED
		void getSharedEntitiesListForPlayerId(const char * in_profileId, std::string in_whereJson, std::string in_orderByJson, int32_t in_maxReturn, IServerCallback * in_callback = NULL);


		/**
		* Method gets list of shared entities for the specified user based on type and/or where clause
		*
		* Service Name - Entity
		* Service Operation - READ_SHARED_ENTITIES_LIST
		*
		* @param in_profileId The profile ID to retrieve shared entities for
		* @param in_whereJson Mongo style query
		* @param in_orderByJson Sort order
		* @param in_maxReturn The maximum number of entities to return
		* @param in_callback The method to be invoked when the server response is received
		*/
		void getSharedEntitiesListForProfileId(const char * in_profileId, std::string in_whereJson, std::string in_orderByJson, int32_t in_maxReturn, IServerCallback * in_callback = NULL);

		/**
		 * Method updates a shared entity owned by another user. This operation results in the entity
		 * data being completely replaced by the passed in JSON string.
		 *
		 * Service Name - Entity
		 * Service Operation - UpdateShared
		 *
		 * @param in_entityId The id of the entity to update
		 * @param in_targetProfileId The id of the user who owns the shared entity
		 * @param in_entityType The entity type as defined by the user
		 * @param in_jsonEntityData The entity's data as a json string.
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void updateSharedEntity(
			const char * in_entityId,
			const char * in_targetProfileId,
			const char * in_entityType,
			const std::string& in_jsonEntityData,
			int64_t in_version,
			IServerCallback * in_callback = NULL);

		/**
		* Method gets list of entities from the server base on type and/or where clause
		*
		* Service Name - Entity
		* Service Operation - GET_LIST
		*
		* @param in_whereJson Mongo style query string
		* @param in_orderByJson Sort order
		* @param in_maxReturn The maximum number of entities to return
		* @param in_callback The callback object
		*/
		void getList(const std::string& in_whereJson, const std::string& in_orderByJson, int64_t in_maxReturn, IServerCallback * in_callback = NULL);

		/**
		* Method gets a count of entities based on the where clause
		*
		* Service Name - Entity
		* Service Operation - GET_LIST_COUNT
		*
		* @param in_whereJson Mongo style query string
		* @param in_callback The callback object
		*/
		void getListCount(const std::string& in_whereJson, IServerCallback * in_callback = NULL);

		/**
		 * Method uses a paging system to iterate through user entities
		 * After retrieving a page of entities with this method,
		 * use GetPageOffset() to retrieve previous or next pages.
		 *
		 * Service Name - Entity
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
		 * Service Name - Entity
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
		* Partial increment of entity data field items. Partial set of items incremented as specified.
		*
		* Service Name - entity
		* Service Operation - INCREMENT_USER_ENTITY_DATA
		*
		* @param in_entityId The id of the entity to update
		* @param in_jsonData The entity's data object
		* @param in_callback The callback object
		*/
		void incrementUserEntityData(const char * in_entityId, std::string in_jsonData, IServerCallback * in_callback = NULL);

		/**
		* Partial increment of entity data field items. Partial set of items incremented as specified.
		*
		* Service Name - entity
		* Service Operation - INCREMENT_SHARED_USER_ENTITY_DATA
		*
		* @param in_entityId The id of the entity to update
		* @param in_targetProfileId Profile ID of the entity owner
		* @param in_jsonData The entity's data object
		* @param in_callback The callback object
		*/
		void incrementSharedUserEntityData(const char * in_entityId, const char * in_targetProfileId, std::string in_jsonData, IServerCallback * in_callback = NULL);

	private:
		BrainCloudClient * m_client;
	};
}