// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <vector>
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

	namespace eAutoJoinStrategy {
		enum Strategy {
			JoinFirstGroup = 0,
			JoinRandomGroup
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
		*/
		void approveGroupJoinRequest(const char* in_groupId, const char* in_profileId, eGroupMember::Role role, const std::string& in_jsonAttributes, IServerCallback* in_callback = NULL);

		/**
		* Automatically join an open group that matches the search criteria and has space available.
		*
		* Service Name - group
		* Service Operation - AUTO_JOIN_GROUP
		*
		* @param in_groupType Name of the associated group type.
		* @param in_autoJoinStrategy Selection strategy to employ when there are multiple matches
		* @param in_dataQueryJson Query parameters (optional)
		* @param in_callback The method to be invoked when the server response is received
		*/
		void autoJoinGroup(const char* in_groupType, eAutoJoinStrategy::Strategy in_autoJoinStrategy, std::string in_dataQueryJson, IServerCallback* in_callback = NULL);

		/**
        * Find and join an open group in the pool of groups in multiple group types provided as input arguments.		*
		* Service Name - group
		* Service Operation - AUTO_JOIN_GROUP_MULTI
		*
		* @param in_groupTypes Name of the associated group type.
		* @param in_autoJoinStrategy Selection strategy to employ when there are multiple matches
		* @param in_where Query parameters (optional)
		* @param in_callback The method to be invoked when the server response is received
		*/
		void autoJoinGroupMulti(const std::vector<std::string>& in_groupTypes, eAutoJoinStrategy::Strategy in_autoJoinStrategy, std::string in_where, IServerCallback* in_callback = NULL);

		/**
		* Cancel an outstanding invitation to the group.
		*
		* Service Name - group
		* Service Operation - CANCEL_GROUP_INVITATION
		*
		* @param in_groupId ID of the group.
		* @param in_profileId Profile ID of the invitation being deleted.
		* @param in_callback The method to be invoked when the server response is received
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
		* @param in_jsonOwnerAttributes Attributes for the group owner (current user).
		* @param in_jsonDefaultMemberAttributes Default attributes for group members.
		* @param in_jsonData Custom application data.
		* @param in_callback The method to be invoked when the server response is received
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
		* Create a group with Summary Data.
		*
		* Service Name - group
		* Service Operation - CREATE_GROUP
		*
		* @param in_name Name of the group.
		* @param in_groupType Name of the type of group.
		* @param in_isOpenGroup true if group is open; false if closed.
		* @param in_acl The group's access control list. A null ACL implies default.
		* @param in_jsonOwnerAttributes Attributes for the group owner (current user).
		* @param in_jsonDefaultMemberAttributes Default attributes for group members.
		* @param in_jsonSummaryData the summary.
		* @param in_jsonData Custom application data.
		* @param in_callback The method to be invoked when the server response is received
		*/
		void createGroupWithSummaryData(
			const char* in_name,
			const char* in_groupType,
			bool in_isOpenGroup,
			const std::string& in_acl,
			const std::string& in_jsonData,
			const std::string& in_jsonOwnerAttributes,
			const std::string& in_jsonDefaultMemberAttributes,
			const std::string& in_jsonSummaryData,
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
		*/
		void deleteGroupEntity(const char* in_groupId, const char* in_entityId, int32_t in_version, IServerCallback* in_callback = NULL);

		/**
		* Read information on groups to which the current user belongs.
		*
		* Service Name - group
		* Service Operation - GET_MY_GROUPS
		* @param in_callback The method to be invoked when the server response is received
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
		*/
		void incrementGroupData(const char* in_groupId, const std::string& in_jsonData, IServerCallback* in_callback = NULL);

		/**
		* Increment elements for the group entity's data field.
		*
		* Service Name - group
		* Service Operation - INCREMENT_GROUP_ENTITY_DATA
		*
		* @param in_groupId ID of the group.
		* @param in_entityId ID of the entity.
		* @param in_jsonData Partial data map with incremental values.
		* @param in_callback The method to be invoked when the server response is received
		*/
		void incrementGroupEntityData(const char* in_groupId, const char* in_entityId, const std::string& in_jsonData, IServerCallback* in_callback = NULL);

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
		*/
		void joinGroup(const char* in_groupId, IServerCallback* in_callback = NULL);

		/**
		* Leave a group in which the user is a member.
		*
		* Service Name - group
		* Service Operation - LEAVE_GROUP
		*
		* @param in_groupId ID of the group.
		* @param in_callback The method to be invoked when the server response is received
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
		*/
		void listGroupsPageByOffset(const char* in_encodedContext, int32_t in_pageOffset, IServerCallback* in_callback = NULL);

		/**
		* Read information on groups to which the specified user belongs.  Access is subject to restrictions.
		*
		* Service Name - group
		* Service Operation - LIST_GROUPS_WITH_MEMBER
		*
		* @param in_profileId
		* @param in_callback The method to be invoked when the server response is received
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
		*/
		void readGroup(const char* in_groupId, IServerCallback* in_callback = NULL);

		/**
		* Read the specified group's data.
		*
		* Service Name - group
		* Service Operation - READ_GROUP_DATA
		*
		* @param in_groupId ID of the group.
		* @param in_callback The method to be invoked when the server response is received
		*/
		void readGroupData(const char* in_groupId, IServerCallback* in_callback = NULL);

		/**
		* Read a page of group entity information.
		*
		* Service Name - group
		* Service Operation - READ_GROUP_ENTITIES_PAGE
		*
		* @param in_context Query context.
		* @param in_callback The method to be invoked when the server response is received
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
		*/
		void updateGroupName(const char* in_groupId, const char* in_name, IServerCallback* in_callback = NULL);

		/**
		 * Set whether a group is open true or false
		 *
		 * Service Name - group
		 * Service Operation - SET_GROUP_OPEN
		 *
		 * @param groupId ID of the group.
		 * @param isOpenGroup whether its open or not
		 * @param callback The method to be invoked when the server response is received
		 */
		void setGroupOpen(const char* in_groupId, bool in_isOpenGroup, IServerCallback *callback = nullptr);

		/**
		 * Update a group's summary data
		 *
		 * Service Name - group
		 * Service Operation - UPDATE_GROUP_SUMMARY_DATA
		 *
		 * @param groupId ID of the group.
		 * @param version the version of the group
		 * @param jsonSummaryData custom application data
		 * @param callback The method to be invoked when the server response is received
		 */
		void updateGroupSummaryData(const char* in_groupId, int in_version, const std::string& in_jsonSummaryData, IServerCallback *callback = nullptr);

		/**
		 * Gets a list of up to maxReturn randomly selected groups from the server based on the where condition.
		 *
		 * Service Name - group
		 * Service Operation - GET_RANDOM_GROUPS_MATCHING
		 *
		 * @param jsonWhere where to search
		 * @param maxReturn # of groups to search
		 * @param callback The method to be invoked when the server response is received
		 */
		void getRandomGroupsMatching(std::string in_jsonWhere, int in_maxReturn, IServerCallback *callback = nullptr);

	private:
		BrainCloudClient * m_client;

		std::string roleToString(eGroupMember::Role role);
		std::string autoJoinStrategyToString(eAutoJoinStrategy::Strategy strategy);
	};
}