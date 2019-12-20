// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <string>

#include "braincloud/BrainCloudTypes.h"

namespace BrainCloud {

	class IServerCallback;
	class BrainCloudClient;

	class BrainCloudCustomEntity
	{
	public:
		BrainCloudCustomEntity(BrainCloudClient* in_client);

		/**
		 * Creates new custom entity.
		 *
		 * Service Name - CustomEntity
		 * Service Operation - CreateEntity
		 *
		 * @param in_entityType The entity type as defined by the user
		 * @param in_jsonEntityData The entity's data as a json string
		 * @param in_jsonEntityAcl The entity's access control list as json. A null acl implies default
		 * permissions which make the entity readable/writeable by only the user.
		 * @param timeToLive
		 * @param isOwned
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void createEntity(const char * in_entityType, const std::string& in_jsonEntityData, const std::string& in_jsonEntityAcl, int64_t in_timeToLive, bool in_isOwned, IServerCallback * in_callback = NULL);

		/**
		 * Deletes the specified custom entity on the server.
		 *
		 * Service Name - CustomEntity
		 * Service Operation - DeleteEntity
		 *
		 * @param in_entityType The entity type as defined by the user
		 * @param in_jsonEntityData The entity's data as a json string
		 * @param version
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void deleteEntity(const char * in_entityType, const char * in_entityId, const std::string& in_jsonEntityData, int32_t in_version, IServerCallback * in_callback = NULL);

		/**
		 * Deletes the specified custom entity on the server.
		 *
		 * Service Name - CustomEntity
		 * Service Operation - GetCount
		 *
		 * @param in_entityType The entity type as defined by the user
		 * @param in_whereJson
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void getCount(const char * in_entityType, const std::string& in_whereJson, IServerCallback * in_callback = NULL);

		/**
		 * Retrieves first page of custom entities from the server based on the custom entity type and specified query context
		 *
		 * Service Name - CustomEntity
		 * Service Operation - GetPage
		 *
		 * @param in_entityType The entity type as defined by the user
		 * @param in_rowsPerPage
		 * @param in_searchJson
		 * @param in_sortJson
		 * @param in_doCount
		 * @param in_callback The method to be invoked when the server response is received
		 */

		//Deprecated use overload with in_entityType, and in_context
		void getEntityPage(const char * in_entityType, int32_t in_rowsPerPage, const std::string& in_searchJson, const std::string& in_sortJson, bool in_doCount, IServerCallback * in_callback = NULL);
		 /**
		 * Method uses a paging system to iterate through Custom Entities
		 * After retrieving a page of Custom Entities with this method,
		 * use GetEntityPageOffset() to retrieve previous or next pages.
		 *
		 * Service Name - CustomEntity
		 * Service Operation - GetCustomEntityPage
		 *
		 * @param in_entityType The entity type as defined by the user
		 * @param in_context The json context for the page request.
		 *                   See the portal appendix documentation for format.
		 * @param in_callback The callback object
		 */
		void getEntityPage(const char * in_entityType, const char * in_context, IServerCallback * in_callback = NULL);

		/**
		 * Gets the page of custom entities from the server based on the encoded context and specified page offset.
		 *
		 * Service Name - CustomEntity
		 * Service Operation - GetEntityPageOffset
		 *
		 * @param in_entityType The entity type as defined by the user
		 * @param in_context
		 * @param in_pageOffset
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void getEntityPageOffset(const char * in_entityType, const std::string& in_context, int32_t in_pageOffset, IServerCallback * in_callback = NULL);

		/**
		 * Gets the page of custom entities from the server based on the encoded context and specified page offset.
		 *
		 * Service Name - CustomEntity
		 * Service Operation - ReadEntity
		 *
		 * @param in_entityType The entity type as defined by the user
		 * @param in_entityId
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void readEntity(const char * in_entityType, const char * in_entityId, IServerCallback * in_callback = NULL);

		/**
		 * Replaces the specified custom entity's data, and optionally updates the acl and expiry, on the server.
		 *
		 * Service Name - CustomEntity
		 * Service Operation - UpdateEntity
		 *
		 * @param in_entityType The entity type as defined by the user
		 * @param in_entityId
		 * @param in_version
		 * @param in_jsonEntityData The entity's data as a json string
		 * @param in_jsonEntityAcl The entity's access control list as json. A null acl implies default
		 * permissions which make the entity readable/writeable by only the user.
		 * @param timeToLive
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void updateEntity(const char * in_entityType, const char * in_entityId, int32_t in_version, const std::string& in_jsonEntityData, const std::string& in_jsonEntityAcl, int64_t in_timeToLive, IServerCallback * in_callback = NULL);

		/**
		 * Replaces the specified custom entity's data, and optionally updates the acl and expiry, on the server.
		 *
		 * Service Name - CustomEntity
		 * Service Operation - UpdateEntityFields
		 *
		 * @param in_entityType The entity type as defined by the user
		 * @param in_entityId
		 * @param in_version
		 * @param in_fieldsJson
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void updateEntityFields(const char * in_entityType, const char * in_entityId, int32_t in_version, const std::string& in_fieldsJson, IServerCallback * in_callback = NULL);


	private:
		BrainCloudClient * m_client;
	};
}