// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <string>
#include "BrainCloudTypes.h"

namespace BrainCloud
{
	namespace eGroupMember {
		enum Role {
			UNKNOWN = 0,
			MEMBER,
			ADMIN,
			OWNER,
			OTHER
		};
	}

	class IServerCallback;
	class BrainCloudClient;

	class BrainCloudGroup
	{
	public:
		BrainCloudGroup(BrainCloudClient* in_client);

		/**
		* Accept an outstanding invitation to join the group.
		*
		* Service Name - group
		* Service Operation - ACCEPT_GROUP_INVITATION
		*
		* @param in_groupId ID of the group.
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": null
		* }
		*/
		void acceptGroupInvitation(const char* in_groupId, IServerCallback* in_callback = NULL);

		/**
		* Add a member to the group.
		*
		* Service Name - group
		* Service Operation - ADD_GROUP_MEMBER
		*
		* @param in_groupId ID of the group.
		* @param in_profileId Profile ID of the member being added.
		* @param in_role Role of the member being added.
		* @param in_jsonAttributes Attributes of the member being added.
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": null
		* }
		*/
		void addGroupMember(const char* in_groupId, const char* in_profileId, eGroupMember::Role role, const std::string& in_jsonAttributes, IServerCallback* in_callback = NULL);

		/**
		* Approve an outstanding request to join the group.
		*
		* Service Name - group
		* Service Operation - APPROVE_GROUP_JOIN_REQUEST
		*
		* @param in_groupId ID of the group.
		* @param in_profileId Profile ID of the invitation being deleted.
		* @param in_role Role of the member being invited.
		* @param in_jsonAttributes Attributes of the member being invited.
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": null
		* }
		*/
		void approveGroupJoinRequest(const char* in_groupId, const char* in_profileId, eGroupMember::Role role, const std::string& in_jsonAttributes, IServerCallback* in_callback = NULL);

		/**
		* Cancel an outstanding invitation to the group.
		*
		* Service Name - group
		* Service Operation - CANCEL_GROUP_INVITATION
		*
		* @param in_groupId ID of the group.
		* @param in_profileId Profile ID of the invitation being deleted.
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": null
		* }
		*/
		void cancelGroupInvitation(const char* in_groupId, const char* in_profileId, IServerCallback* in_callback = NULL);

		/**
		* Create a group.
		*
		* Service Name - group
		* Service Operation - CREATE_GROUP
		*
		* @param in_name Name of the group.
		* @param in_groupType Name of the type of group.
		* @param in_isOpenGroup true if group is open; false if closed.
		* @param in_acl The group's access control list. A null ACL implies default.
		* @param in_jsonOwnerAttributes Attributes for the group owner (current player).
		* @param in_jsonDefaultMemberAttributes Default attributes for group members.
		* @param in_jsonData Custom application data.
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": {
		*         "gameId": "20595",
		*         "groupId": "211559ef-234a-4aef-a643-48a90a6036c2",
		*         "ownerId": "ee8cad26-16f2-4ef8-9045-3aab84ce6362",
		*         "name": "my-group-name",
		*         "groupType": "TestGroup",
		*         "createdAt": 1461613090251,
		*         "updatedAt": 1461613090251,
		*         "members": {
		*             "ee8cad26-16f2-4ef8-9045-3aab84ce6362": {
		*                 "role": "OWNER",
		*                 "attributes": {}
		*             }
		*         },
		*         "pendingMembers": {},
		*         "version": 1,
		*         "data": {},
		*         "isOpenGroup": false,
		*         "defaultMemberAttributes": {},
		*         "memberCount": 1,
		*         "invitedPendingMemberCount": 0,
		*         "requestingPendingMemberCount": 0,
		*         "acl": {
		*             "member": 2,
		*             "other": 1
		*         }
		*     }
		* }
		*/
		void createGroup(
			const char* in_name,
			const char* in_groupType,
			bool in_isOpenGroup,
			const std::string& in_acl,
			const std::string& in_jsonData,
			const std::string& in_jsonOwnerAttributes,
			const std::string& in_jsonDefaultMemberAttributes,
			IServerCallback* in_callback = NULL);

		/**
		* Create a group entity.
		*
		* Service Name - group
		* Service Operation - CREATE_GROUP_ENTITY
		*
		* @param in_groupId ID of the group.
		* @param in_isOwnedByGroupMember true if entity is owned by a member; false if owned by the entire group.
		* @param in_entityType Type of the group entity.
		* @param in_acl Access control list for the group entity.
		* @param in_jsonData Custom application data.
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return Object encapsulating the group entity information.
		* {
		*     "status": 200,
		*     "data": {
		*         "gameId": "20595",
		*         "groupId": "fee55a37-5e86-43e8-942e-06bcbe1b701e",
		*         "entityId": "91cfece7-debb-4698-ba6b-cd2cb432458d",
		*         "ownerId": null,
		*         "entityType": "BLUE",
		*         "createdAt": 1462812680359,
		*         "updatedAt": 1462812680359,
		*         "version": 1,
		*         "data": {},
		*         "acl": {
		*             "member": 2,
		*             "other": 1
		*         }
		*     }
		* }
		*/
		void createGroupEntity(
			const char* in_groupId,
			const char* in_entityType,
			bool isOwnedByGroupMember,
			const std::string& in_acl,
			const std::string& in_jsonData,
			IServerCallback* in_callback = NULL);

		/**
		* Delete a group.
		*
		* Service Name - group
		* Service Operation - DELETE_GROUP
		*
		* @param in_groupId ID of the group.
		* @param in_version Current version of the group
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": null
		* }
		*/
		void deleteGroup(const char* in_groupId, int32_t in_version, IServerCallback* in_callback = NULL);

		/**
		* Delete a group entity.
		*
		* Service Name - group
		* Service Operation - DELETE_GROUP_ENTITY
		*
		* @param in_groupId ID of the group.
		* @param in_entityId ID of the entity.
		* @param in_version The current version of the group entity (for concurrency checking).
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": null
		* }
		*/
		void deleteGroupEntity(const char* in_groupId, const char* in_entityId, int32_t in_version, IServerCallback* in_callback = NULL);

		/**
		* Read information on groups to which the current player belongs.
		*
		* Service Name - group
		* Service Operation - GET_MY_GROUPS
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": {
		*         "groups": [
		*             {
		*                 "gameId": "20595",
		*                 "groupId": "4f176781-e65e-42ce-b24f-9d39449380d5",
		*                 "ownerId": "ee8cad26-16f2-4ef8-9045-3aab84ce6362",
		*                 "name": "temp-group-name",
		*                 "groupType": "test2",
		*                 "createdAt": 1462222320554,
		*                 "updatedAt": 1462222320554,
		*                 "members": {
		*                     "ee8cad26-16f2-4ef8-9045-3aab84ce6362": {
		*                         "role": "OWNER",
		*                         "attributes": {}
		*                     }
		*                 },
		*                 "pendingMembers": {},
		*                 "version": 1,
		*                 "data": {},
		*                 "isOpenGroup": false,
		*                 "defaultMemberAttributes": {},
		*                 "memberCount": 1,
		*                 "invitedPendingMemberCount": 0,
		*                 "requestingPendingMemberCount": 0,
		*                 "acl": {
		*                     "other": 1
		*                 }
		*             }
		*         ]
		*     }
		* }
		*/
		void getMyGroups(IServerCallback* in_callback = NULL);

		/**
		* Increment elements for the group's data field.
		*
		* Service Name - group
		* Service Operation - INCREMENT_GROUP_DATA
		*
		* @param in_groupId ID of the group.
		* @param in_jsonData Partial data map with incremental values.
		* @param in_callback The method to be invoked when the server response is received
		* @param in_returnData Should the group data be returned in the response?
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": null
		* }
		*/
		void incrementGroupData(const char* in_groupId, const std::string& in_jsonData, bool in_returnData, IServerCallback* in_callback = NULL);

		/**
		* Increment elements for the group entity's data field.
		*
		* Service Name - group
		* Service Operation - INCREMENT_GROUP_ENTITY_DATA
		*
		* @param in_groupId ID of the group.
		* @param in_entityId ID of the entity.
		* @param in_jsonData Partial data map with incremental values.
		* @param in_returnData Should the group entity be returned in the response?
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": null
		* }
		*/
		void incrementGroupEntityData(const char* in_groupId, const char* in_entityId, const std::string& in_jsonData, bool in_returnData, IServerCallback* in_callback = NULL);

		/**
		* Invite a member to the group.
		*
		* Service Name - group
		* Service Operation - INVITE_GROUP_MEMBER
		*
		* @param in_groupId ID of the group.
		* @param in_profileId Profile ID of the member being invited.
		* @param in_role Role of the member being invited.
		* @param in_jsonAttributes Attributes of the member being invited.
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": null
		* }
		*/
		void inviteGroupMember(const char* in_groupId, const char* in_profileId, eGroupMember::Role role, const std::string& in_jsonAttributes, IServerCallback* in_callback = NULL);

		/**
		* Join an open group or request to join a closed group.
		*
		* Service Name - group
		* Service Operation - JOIN_GROUP
		*
		* @param in_groupId ID of the group.
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": null
		* }
		*/
		void joinGroup(const char* in_groupId, IServerCallback* in_callback = NULL);

		/**
		* Leave a group in which the player is a member.
		*
		* Service Name - group
		* Service Operation - LEAVE_GROUP
		*
		* @param in_groupId ID of the group.
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": null
		* }
		*/
		void leaveGroup(const char* in_groupId, IServerCallback* in_callback = NULL);

		/**
		* Read a page of group information.
		*
		* Service Name - group
		* Service Operation - LIST_GROUPS_PAGE
		*
		* @param in_context Query context.
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": {
		*         "results": {
		*             "moreBefore": false,
		*             "count": 1,
		*             "items": [
		*                 {
		*                     "groupType": "test",
		*                     "groupId": "1d1abb61-8825-4374-a52a-d8186f336775",
		*                     "isOpenGroup": false,
		*                     "requestingPendingMemberCount": 0,
		*                     "invitedPendingMemberCount": 0,
		*                     "ownerId": "29696ee1-82f6-4d6e-86de-b68c3a5c347e",
		*                     "name": "test",
		*                     "memberCount": 1
		*                 }
		*             ],
		*             "page": 1,
		*             "moreAfter": false
		*         },
		*         "context": "eyJzZWFyY2hDcml0ZXJpYSI6eyJncm91cFR5cGUiOiJ0ZXN0IiwiZ2FtZUlk"
		*     }
		* }
		*/
		void listGroupsPage(const std::string& in_jsonContext, IServerCallback* in_callback = NULL);

		/**
		* Read a page of group information.
		*
		* Service Name - group
		* Service Operation - LIST_GROUPS_PAGE_BY_OFFSET
		*
		* @param in_encodedContext Encoded reference query context.
		* @param in_offset Number of pages by which to offset the query.
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": {
		*         "results": {
		*             "moreBefore": true,
		*             "count": 2,
		*             "items": [
		*                 {
		*                     "groupType": "test",
		*                     "groupId": "1d1abb61-8825-4374-a52a-d8186f336775",
		*                     "isOpenGroup": false,
		*                     "requestingPendingMemberCount": 0,
		*                     "invitedPendingMemberCount": 0,
		*                     "ownerId": "29696ee1-82f6-4d6e-86de-b68c3a5c347e",
		*                     "name": "test",
		*                     "memberCount": 1
		*                 }
		*             ],
		*             "page": 2,
		*             "moreAfter": false
		*         },
		*         "context": "eyJzZWFyY2hDcml0ZXJpYSI6eyJncm91cFR5cGUiOiJ0ZXN0IiwiZ2FtZUlk"
		*     }
		* }
		*/
		void listGroupsPageByOffset(const char* in_encodedContext, int32_t in_pageOffset, IServerCallback* in_callback = NULL);

		/**
		* Read information on groups to which the specified player belongs.  Access is subject to restrictions.
		*
		* Service Name - group
		* Service Operation - LIST_GROUPS_WITH_MEMBER
		*
		* @param in_profileId
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": {
		*         "groups": [
		*             {
		*                 "groupType": "test",
		*                 "groupId": "69191b48-0cb1-4538-9758-e2f5ef4c524b",
		*                 "isOpenGroup": false,
		*                 "requestingPendingMemberCount": 0,
		*                 "invitedPendingMemberCount": 0,
		*                 "ownerId": "b67b2d73-1e8c-42e9-9be5-9c1879a48555",
		*                 "name": "test22",
		*                 "memberCount": 1
		*             }
		*         ]
		*     }
		* }
		*/
		void listGroupsWithMember(const char* in_profileId, IServerCallback* in_callback = NULL);

		/**
		* Read the specified group.
		*
		* Service Name - group
		* Service Operation - READ_GROUP
		*
		* @param in_groupId ID of the group.
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": {
		*         "gameId": "123456",
		*         "groupId": "69191b48-0cb1-4538-9758-e2f5ef4c524b",
		*         "ownerId": "b67b2d73-1e8c-42e9-9be5-9c1879a48555",
		*         "name": "test22",
		*         "groupType": "test",
		*         "createdAt": 1462462308991,
		*         "updatedAt": 1462462308991,
		*         "members": {
		*             "b67b2d73-1e8c-42e9-9be5-9c1879a48555": {
		*                 "role": "OWNER",
		*                 "attributes": {}
		*             }
		*         },
		*         "pendingMembers": {},
		*         "version": 1,
		*         "data": {},
		*         "isOpenGroup": false,
		*         "defaultMemberAttributes": {},
		*         "memberCount": 1,
		*         "invitedPendingMemberCount": 0,
		*         "requestingPendingMemberCount": 0,
		*         "acl": {
		*             "other": 1,
		*             "member": 1
		*         }
		*     }
		* }
		*/
		void readGroup(const char* in_groupId, IServerCallback* in_callback = NULL);

		/**
		* Read a page of group entity information.
		*
		* Service Name - group
		* Service Operation - READ_GROUP_ENTITIES_PAGE
		*
		* @param in_context Query context.
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": {
		*         "results": {
		*             "moreBefore": false,
		*             "count": 3,
		*             "items": [
		*                 {
		*                     "gameId": "20595",
		*                     "groupId": "fee55a37-5e86-43e8-942e-06bcbe1b701e",
		*                     "entityId": "91cfece7-debb-4698-ba6b-cd2cb432458d",
		*                     "ownerId": null,
		*                     "entityType": "BLUE",
		*                     "createdAt": 1462812680359,
		*                     "updatedAt": 1462812680359,
		*                     "version": 1,
		*                     "data": {},
		*                     "acl": {
		*                         "member": 2,
		*                         "other": 1
		*                     }
		*                 }
		*             ],
		*             "page": 1,
		*             "moreAfter": true
		*         },
		*         "context": "eyJzZWFyY2hDcml0ZXJpYSI6eyJncm91cElkIjoiZmVlNTVhMzct"
		*     }
		* }
		*/
		void readGroupEntitiesPage(const std::string& in_jsonContext, IServerCallback* in_callback = NULL);

		/**
		* Read a page of group entity information.
		*
		* Service Name - group
		* Service Operation - READ_GROUP_ENTITIES_PAGE_BY_OFFSET
		*
		* @param in_encodedContext Encoded reference query context.
		* @param in_offset Number of pages by which to offset the query.
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": {
		*         "results": {
		*             "moreBefore": true,
		*             "count": 3,
		*             "items": [
		*                 {
		*                     "gameId": "20595",
		*                     "groupId": "fee55a37-5e86-43e8-942e-06bcbe1b701e",
		*                     "entityId": "ccbf996c-9e96-4935-b570-eebaab81c75a",
		*                     "ownerId": null,
		*                     "entityType": "RED",
		*                     "createdAt": 1462812845384,
		*                     "updatedAt": 1462812845384,
		*                     "version": 1,
		*                     "data": {
		*                         "third": true
		*                     },
		*                     "acl": {
		*                         "member": 2,
		*                         "other": 1
		*                     }
		*                 }
		*             ],
		*             "page": 2,
		*             "moreAfter": false
		*         },
		*         "context": "eyJzZWFyY2hDcml0ZXJpYSI6eyJncm91cElkIjoiZmVlNTVhMzctNWU4Ni00M2U4LTk"
		*     }
		* }
		*/
		void readGroupEntitiesPageByOffset(const char* in_encodedContext, int32_t in_pageOffset, IServerCallback* in_callback = NULL);

		/**
		* Read the specified group entity.
		*
		* Service Name - group
		* Service Operation - READ_GROUP_ENTITY
		*
		* @param in_groupId ID of the group.
		* @param in_entityId ID of the entity.
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": {
		*         "gameId": "20595",
		*         "groupId": "fee55a37-5e86-43e8-942e-06bcbe1b701e",
		*         "entityId": "91cfece7-debb-4698-ba6b-cd2cb432458d",
		*         "ownerId": null,
		*         "entityType": "BLUE",
		*         "createdAt": 1462812680359,
		*         "updatedAt": 1462812680359,
		*         "version": 1,
		*         "data": {},
		*         "acl": {
		*             "member": 2,
		*             "other": 1
		*         }
		*     }
		* }
		*/
		void readGroupEntity(const char* in_groupId, const char* in_entityId, IServerCallback* in_callback = NULL);

		/**
		* Read the members of the group.
		*
		* Service Name - group
		* Service Operation - READ_MEMBERS_OF_GROUP
		*
		* @param in_groupId ID of the group.
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": {
		*         "ee8cad26-16f2-4ef8-9045-3aab84ce6362": {
		*             "role": "OWNER",
		*             "attributes": {},
		*             "playerName": "Peter",
		*             "emailAddress": "klug@bitheads.com"
		*         },
		*         "295c510f-507f-4bcf-80e1-ebc73708ec3c": {
		*             "role": "MEMBER",
		*             "attributes": {},
		*             "playerName": "Billy",
		*             "emailAddress": "billy@bitheads.com"
		*         }
		*     }
		* }
		*/
		void readGroupMembers(const char* in_groupId, IServerCallback* in_callback = NULL);

		/**
		* Reject an outstanding invitation to join the group.
		*
		* Service Name - group
		* Service Operation - REJECT_GROUP_INVITATION
		*
		* @param in_groupId ID of the group.
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": null
		* }
		*/
		void rejectGroupInvitation(const char* in_groupId, IServerCallback* in_callback = NULL);

		/**
		* Reject an outstanding request to join the group.
		*
		* Service Name - group
		* Service Operation - REJECT_GROUP_JOIN_REQUEST
		*
		* @param in_groupId ID of the group.
		* @param in_profileId Profile ID of the invitation being deleted.
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": null
		* }
		*/
		void rejectGroupJoinRequest(const char* in_groupId, const char* in_profileId, IServerCallback* in_callback = NULL);

		/**
		* Remove a member from the group.
		*
		* Service Name - group
		* Service Operation - REMOVE_GROUP_MEMBER
		*
		* @param in_groupId ID of the group.
		* @param in_profileId Profile ID of the member being deleted.
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": null
		* }
		*/
		void removeGroupMember(const char* in_groupId, const char* in_profileId, IServerCallback* in_callback = NULL);

		/**
		* Updates a group's data.
		*
		* Service Name - group
		* Service Operation - UPDATE_GROUP_DATA
		*
		* @param in_groupId ID of the group.
		* @param in_version Version to verify.
		* @param in_jsonData Data to apply.
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": null
		* }
		*/
		void updateGroupData(const char* in_groupId, int32_t in_version, const std::string& in_jsonData, IServerCallback* in_callback = NULL);

		/**
		* Update a group entity.
		*
		* Service Name - group
		* Service Operation - UPDATE_GROUP_ENTITY_DATA
		*
		* @param in_groupId ID of the group.
		* @param in_entityId ID of the entity.
		* @param in_version The current version of the group entity (for concurrency checking).
		* @param in_jsonData Custom application data.
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": null
		* }
		*/
		void updateGroupEntityData(const char* in_groupId, const char* in_entityId, int32_t in_version, const std::string& in_jsonData, IServerCallback* in_callback = NULL);

		/**
		* Update a member of the group.
		*
		* Service Name - group
		* Service Operation - UPDATE_GROUP_MEMBER
		*
		* @param in_groupId ID of the group.
		* @param in_profileId Profile ID of the member being updated.
		* @param in_role Role of the member being updated (optional).
		* @param in_jsonAttributes Attributes of the member being updated (optional).
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": null
		* }
		*/
		void updateGroupMember(const char* in_groupId, const char* in_profileId, eGroupMember::Role role, const std::string& in_jsonAttributes, IServerCallback* in_callback = NULL);

		/**
		* Updates a group's name.
		*
		* Service Name - group
		* Service Operation - UPDATE_GROUP_NAME
		*
		* @param in_groupId ID of the group.
		* @param in_name Name to apply.
		* @param in_callback The method to be invoked when the server response is received
		*
		* @return The JSON returned in the callback is as follows:
		* {
		*     "status": 200,
		*     "data": null
		* }
		*/
		void updateGroupName(const char* in_groupId, const char* in_name, IServerCallback* in_callback = NULL);

	private:
		BrainCloudClient * m_client;

		std::string roleToString(eGroupMember::Role role);
	};
}