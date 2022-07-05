// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

UENUM(BlueprintType)
enum class ERole : uint8
{
    OWNER UMETA(DisplayName = "Owner"),
    ADMIN UMETA(DisplayName = "Admin"),
    MEMBER UMETA(DisplayName = "Member"),
    OTHER UMETA(DisplayName = "Other")
};

UENUM(BlueprintType)
enum class EAutoJoinStrategy : uint8
{
    JoinFirstGroup UMETA(DisplayName = "JoinFirstGroup"),
    JoinRandomGroup UMETA(DisplayName = "JoinRandomGroup")
};

class BrainCloudClient;
class IServerCallback;
class UBrainCloudGroupACL;

class BCCLIENTPLUGIN_API BrainCloudGroup
{
  public:
    BrainCloudGroup(BrainCloudClient *client);

    /**
     * Accept an outstanding invitation to join the group.
     *
     * Service Name - group
     * Service Operation - ACCEPT_GROUP_INVITATION
     *
     * @param groupId ID of the group.
     * @param callback The method to be invoked when the server response is received
     */
    void acceptGroupInvitation(const FString &groupId, IServerCallback *callback = nullptr);

    /**
     * Add a member to the group.
     *
     * Service Name - group
     * Service Operation - ADD_GROUP_MEMBER
     *
     * @param groupId ID of the group.
     * @param profileId Profile ID of the member being added.
     * @param role Role of the member being added.
     * @param jsonAttributes Attributes of the member being added.
     * @param callback The method to be invoked when the server response is received
     */
    void addGroupMember(const FString &groupId, const FString &profileId, ERole role, const FString &jsonAttributes, IServerCallback *callback = nullptr);

    /**
     * Approve an outstanding request to join the group.
     *
     * Service Name - group
     * Service Operation - APPROVE_GROUP_JOIN_REQUEST
     *
     * @param groupId ID of the group.
     * @param profileId Profile ID of the invitation being deleted.
     * @param role Role of the member being invited.
     * @param jsonAttributes Attributes of the member being invited.
     * @param callback The method to be invoked when the server response is received
     */
    void approveGroupJoinRequest(const FString &groupId, const FString &profileId, ERole role, const FString &jsonAttributes, IServerCallback *callback = nullptr);

    /**
	* Automatically join an open group that matches the search criteria and has space available.
	*
	* Service Name - group
	* Service Operation - AUTO_JOIN_GROUP
	*
	* @param groupType Name of the associated group type.
	* @param autoJoinStrategy Selection strategy to employ when there are multiple matches
	* @param dataQueryJson Query parameters (optional)
	* @param callback The method to be invoked when the server response is received
	*/
    void autoJoinGroup(const FString &groupType, EAutoJoinStrategy autoJoinStrategy, const FString &dataQueryJson, IServerCallback *callback = nullptr);

        /**
	* Automatically join an open group that matches the search criteria and has space available.
	*
	* Service Name - group
	* Service Operation - AUTO_JOIN_GROUP_MULTI
	*
	* @param groupType Name of the associated group type.
	* @param autoJoinStrategy Selection strategy to employ when there are multiple matches
	* @param dataQueryJson Query parameters (optional)
	* @param callback The method to be invoked when the server response is received
	*/
    void autoJoinGroupMulti(const TArray<FString> &groupType, EAutoJoinStrategy autoJoinStrategy, const FString &dataQueryJson, IServerCallback *callback = nullptr);

    /**
     * Cancel an outstanding invitation to the group.
     *
     * Service Name - group
     * Service Operation - CANCEL_GROUP_INVITATION
     *
     * @param groupId ID of the group.
     * @param profileId Profile ID of the invitation being deleted.
     * @param callback The method to be invoked when the server response is received
     */
    void cancelGroupInvitation(const FString &groupId, const FString &profileId, IServerCallback *callback = nullptr);

    /**
     * Create a group.
     *
     * Service Name - group
     * Service Operation - CREATE_GROUP
     *
     * @param name Name of the group.
     * @param groupType Name of the type of group.
     * @param isOpenGroup true if group is open; false if closed.
     * @param acl The group's access control list. A null ACL implies default.
     * @param jsonOwnerAttributes Attributes for the group owner (current player).
     * @param jsonDefaultMemberAttributes Default attributes for group members.
     * @param jsonData Custom application data.
     * @param callback The method to be invoked when the server response is received
     */
    void createGroup(
        const FString &name,
        const FString &groupType,
        bool isOpenGroup,
        UBrainCloudGroupACL *acl,
        const FString &jsonData,
        const FString &jsonOwnerAttributes,
        const FString &jsonDefaultMemberAttributes,
        IServerCallback *callback = nullptr);

    /**
     * Create a group with summary data.
     *
     * Service Name - group
     * Service Operation - CREATE_GROUP
     *
     * @param name Name of the group.
     * @param groupType Name of the type of group.
     * @param isOpenGroup true if group is open; false if closed.
     * @param acl The group's access control list. A null ACL implies default.
     * @param jsonOwnerAttributes Attributes for the group owner (current player).
     * @param jsonDefaultMemberAttributes Default attributes for group members.
     * @param jsonData Custom application data.
     * @param jsonSummaryData a summary
     * @param callback The method to be invoked when the server response is received
     */
    void createGroupWithSummaryData(
        const FString &name,
        const FString &groupType,
        bool isOpenGroup,
        UBrainCloudGroupACL *acl,
        const FString &jsonData,
        const FString &jsonOwnerAttributes,
        const FString &jsonDefaultMemberAttributes,
        const FString &jsonSummaryData,
        IServerCallback *callback = nullptr);

    /**
     * Create a group entity.
     *
     * Service Name - group
     * Service Operation - CREATE_GROUP_ENTITY
     *
     * @param groupId ID of the group.
     * @param isOwnedByGroupMember true if entity is owned by a member; false if owned by the entire group.
     * @param entityType Type of the group entity.
     * @param acl Access control list for the group entity.
     * @param jsonData Custom application data.
     * @param callback The method to be invoked when the server response is received
     */
    void createGroupEntity(
        const FString &groupId,
        const FString &entityType,
        bool isOwnedByGroupMember,
        UBrainCloudGroupACL *acl,
        const FString &jsonData,
        IServerCallback *callback = nullptr);

    /**
     * Delete a group.
     *
     * Service Name - group
     * Service Operation - DELETE_GROUP
     *
     * @param groupId ID of the group.
     * @param version Current version of the group
     * @param callback The method to be invoked when the server response is received
     */
    void deleteGroup(const FString &groupId, int32 version, IServerCallback *callback = nullptr);

    /**
     * Delete a group entity.
     *
     * Service Name - group
     * Service Operation - DELETE_GROUP_ENTITY
     *
     * @param groupId ID of the group.
     * @param entityId ID of the entity.
     * @param version The current version of the group entity (for concurrency checking).
     * @param callback The method to be invoked when the server response is received
     */
    void deleteGroupEntity(const FString &groupId, const FString &entityId, int32 version, IServerCallback *callback = nullptr);

    /**
     * Read information on groups to which the current player belongs.
     *
     * Service Name - group
     * Service Operation - GET_MY_GROUPS
     * @param callback The method to be invoked when the server response is received
     */
    void getMyGroups(IServerCallback *callback = nullptr);

    /**
     * Increment elements for the group's data field.
     *
     * Service Name - group
     * Service Operation - INCREMENT_GROUP_DATA
     *
     * @param groupId ID of the group.
     * @param jsonData Partial data map with incremental values.
     * @param callback The method to be invoked when the server response is received
     */
    void incrementGroupData(const FString &groupId, const FString &jsonData, IServerCallback *callback = nullptr);

    /**
     * Increment elements for the group entity's data field.
     *
     * Service Name - group
     * Service Operation - INCREMENT_GROUP_ENTITY_DATA
     *
     * @param groupId ID of the group.
     * @param entityId ID of the entity.
     * @param jsonData Partial data map with incremental values.
     * @param callback The method to be invoked when the server response is received
     */
    void incrementGroupEntityData(const FString &groupId, const FString &entityId, const FString &jsonData, IServerCallback *callback = nullptr);

    /**
     * Invite a member to the group.
     *
     * Service Name - group
     * Service Operation - INVITE_GROUP_MEMBER
     *
     * @param groupId ID of the group.
     * @param profileId Profile ID of the member being invited.
     * @param role Role of the member being invited.
     * @param jsonAttributes Attributes of the member being invited.
     * @param callback The method to be invoked when the server response is received
     */
    void inviteGroupMember(const FString &groupId, const FString &profileId, ERole role, const FString &jsonAttributes, IServerCallback *callback = nullptr);

    /**
     * Join an open group or request to join a closed group.
     *
     * Service Name - group
     * Service Operation - JOIN_GROUP
     *
     * @param groupId ID of the group.
     * @param callback The method to be invoked when the server response is received
     */
    void joinGroup(const FString &groupId, IServerCallback *callback = nullptr);

    /**
     * Leave a group in which the player is a member.
     *
     * Service Name - group
     * Service Operation - LEAVE_GROUP
     *
     * @param groupId ID of the group.
     * @param callback The method to be invoked when the server response is received
     */
    void leaveGroup(const FString &groupId, IServerCallback *callback = nullptr);

    /**
     * Read a page of group information.
     *
     * Service Name - group
     * Service Operation - LIST_GROUPS_PAGE
     *
     * @param context Query context.
     * @param callback The method to be invoked when the server response is received
     */
    void listGroupsPage(const FString &jsonContext, IServerCallback *callback = nullptr);

    /**
     * Read a page of group information.
     *
     * Service Name - group
     * Service Operation - LIST_GROUPS_PAGE_BY_OFFSET
     *
     * @param encodedContext Encoded reference query context.
     * @param offset Number of pages by which to offset the query.
     * @param callback The method to be invoked when the server response is received
     */
    void listGroupsPageByOffset(const FString &encodedContext, int32 pageOffset, IServerCallback *callback = nullptr);

    /**
     * Read information on groups to which the specified player belongs.  Access is subject to restrictions.
     *
     * Service Name - group
     * Service Operation - LIST_GROUPS_WITH_MEMBER
     *
     * @param profileId
     * @param callback The method to be invoked when the server response is received
     */
    void listGroupsWithMember(const FString &profileId, IServerCallback *callback = nullptr);

    /**
     * Read the specified group.
     *
     * Service Name - group
     * Service Operation - READ_GROUP
     *
     * @param groupId ID of the group.
     * @param callback The method to be invoked when the server response is received
     */
    void readGroup(const FString &groupId, IServerCallback *callback = nullptr);

    /**
	* Read the specified group's data.
	*
	* Service Name - group
	* Service Operation - READ_GROUP_DATA
	*
	* @param groupId ID of the group.
	* @param callback The method to be invoked when the server response is received
	*/
    void readGroupData(const FString &groupId, IServerCallback *callback = nullptr);

    /**
     * Read a page of group entity information.
     *
     * Service Name - group
     * Service Operation - READ_GROUP_ENTITIES_PAGE
     *
     * @param context Query context.
     * @param callback The method to be invoked when the server response is received
     */
    void readGroupEntitiesPage(const FString &jsonContext, IServerCallback *callback = nullptr);

    /**
     * Read a page of group entity information.
     *
     * Service Name - group
     * Service Operation - READ_GROUP_ENTITIES_PAGE_BY_OFFSET
     *
     * @param encodedContext Encoded reference query context.
     * @param offset Number of pages by which to offset the query.
     * @param callback The method to be invoked when the server response is received
     */
    void readGroupEntitiesPageByOffset(const FString &encodedContext, int32 pageOffset, IServerCallback *callback = nullptr);

    /**
     * Read the specified group entity.
     *
     * Service Name - group
     * Service Operation - READ_GROUP_ENTITY
     *
     * @param groupId ID of the group.
     * @param entityId ID of the entity.
     * @param callback The method to be invoked when the server response is received
     */
    void readGroupEntity(const FString &groupId, const FString &entityId, IServerCallback *callback = nullptr);

    /**
     * Read the members of the group.
     *
     * Service Name - group
     * Service Operation - READ_MEMBERS_OF_GROUP
     *
     * @param groupId ID of the group.
     * @param callback The method to be invoked when the server response is received
     */
    void readGroupMembers(const FString &groupId, IServerCallback *callback = nullptr);

    /**
     * Reject an outstanding invitation to join the group.
     *
     * Service Name - group
     * Service Operation - REJECT_GROUP_INVITATION
     *
     * @param groupId ID of the group.
     * @param callback The method to be invoked when the server response is received
     */
    void rejectGroupInvitation(const FString &groupId, IServerCallback *callback = nullptr);

    /**
     * Reject an outstanding request to join the group.
     *
     * Service Name - group
     * Service Operation - REJECT_GROUP_JOIN_REQUEST
     *
     * @param groupId ID of the group.
     * @param profileId Profile ID of the invitation being deleted.
     * @param callback The method to be invoked when the server response is received
     */
    void rejectGroupJoinRequest(const FString &groupId, const FString &profileId, IServerCallback *callback = nullptr);

    /**
     * Remove a member from the group.
     *
     * Service Name - group
     * Service Operation - REMOVE_GROUP_MEMBER
     *
     * @param groupId ID of the group.
     * @param profileId Profile ID of the member being deleted.
     * @param callback The method to be invoked when the server response is received
     */
    void removeGroupMember(const FString &groupId, const FString &profileId, IServerCallback *callback = nullptr);

    /**
     * Updates a group's data.
     *
     * Service Name - group
     * Service Operation - UPDATE_GROUP_DATA
     *
     * @param groupId ID of the group.
     * @param version Version to verify.
     * @param jsonData Data to apply.
     * @param callback The method to be invoked when the server response is received
     */
    void updateGroupData(const FString &groupId, int32 version, const FString &jsonData, IServerCallback *callback = nullptr);

    /**
     * Update a group entity.
     *
     * Service Name - group
     * Service Operation - UPDATE_GROUP_ENTITY_DATA
     *
     * @param groupId ID of the group.
     * @param entityId ID of the entity.
     * @param version The current version of the group entity (for concurrency checking).
     * @param jsonData Custom application data.
     * @param callback The method to be invoked when the server response is received
     */
    void updateGroupEntityData(const FString &groupId, const FString &entityId, int32 version, const FString &jsonData, IServerCallback *callback = nullptr);

    /**
     * Update a member of the group.
     *
     * Service Name - group
     * Service Operation - UPDATE_GROUP_MEMBER
     *
     * @param groupId ID of the group.
     * @param profileId Profile ID of the member being updated.
     * @param role Role of the member being updated (optional).
     * @param jsonAttributes Attributes of the member being updated (optional).
     * @param callback The method to be invoked when the server response is received
     */
    void updateGroupMember(const FString &groupId, const FString &profileId, ERole role, const FString &jsonAttributes, IServerCallback *callback = nullptr);

    /**
     * Updates a group's name.
     *
     * Service Name - group
     * Service Operation - UPDATE_GROUP_NAME
     *
     * @param groupId ID of the group.
     * @param name Name to apply.
     * @param callback The method to be invoked when the server response is received
     */
    void updateGroupName(const FString &groupId, const FString &name, IServerCallback *callback = nullptr);

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
    void setGroupOpen(const FString &groupId, bool isOpenGroup, IServerCallback *callback = nullptr);

    /**
     * Update a froup's summary data
     *
     * Service Name - group
     * Service Operation - UPDATE_GROUP_SUMMARY_DATA
     *
     * @param groupId ID of the group.
     * @param version the version
     * @param jsonSummaryData custom application data 
     * @param callback The method to be invoked when the server response is received
     */
    void updateGroupSummaryData(const FString &groupId, int32 version,  const FString &jsonSummaryData, IServerCallback *callback = nullptr);
    
    /**
     * Get a list of up to maxReturn randomly selected groups from the server based on where condition
     *
     * Service Name - group
     * Service Operation - GET_RANDOM_GROUPS_MATCHING
     *
     * @param jsonWhere where to search.
     * @param maxReturn #of groups to search 
     * @param callback The method to be invoked when the server response is received
     */
    void getRandomGroupsMatching(const FString &jsonWhere, int32 maxReturn, IServerCallback *callback = nullptr);

  private:
    BrainCloudClient *_client = nullptr;

    FString roleToString(ERole role);
    FString AutoJoinStrategyToString(EAutoJoinStrategy strategy);
};
