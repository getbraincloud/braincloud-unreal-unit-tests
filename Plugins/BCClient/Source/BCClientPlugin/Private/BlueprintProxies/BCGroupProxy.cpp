// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCGroupProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudGroupACL.h"
#include "BrainCloudWrapper.h"

UBCGroupProxy::UBCGroupProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCGroupProxy *UBCGroupProxy::AcceptGroupInvitation(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->acceptGroupInvitation(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::AddGroupMember(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, const FString &profileId, ERole role, const FString &jsonAttributes)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->addGroupMember(groupId, profileId, role, jsonAttributes, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::ApproveGroupJoinRequest(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, const FString &profileId, ERole role, const FString &jsonAttributes)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->approveGroupJoinRequest(groupId, profileId, role, jsonAttributes, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::AutoJoinGroup(UBrainCloudWrapper *brainCloudWrapper, const FString &groupType, EAutoJoinStrategy autoJoinStrategy, const FString &dataQueryJson)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->autoJoinGroup(groupType, autoJoinStrategy, dataQueryJson, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::AutoJoinGroupMulti(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &groupTypes, EAutoJoinStrategy autoJoinStrategy, const FString &dataQueryJson)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->autoJoinGroupMulti(groupTypes, autoJoinStrategy, dataQueryJson, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::CancelGroupInvitation(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, const FString &profileId)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->cancelGroupInvitation(groupId, profileId, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::CreateGroup(
    UBrainCloudWrapper *brainCloudWrapper,
    const FString &name,
    const FString &type,
    bool isOpenGroup,
    UBrainCloudGroupACL *acl,
    const FString &jsonData,
    const FString &jsonOwnerAttributes,
    const FString &jsonDefaultMemberAttributes)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->createGroup(name, type, isOpenGroup, acl, jsonData, jsonOwnerAttributes, jsonDefaultMemberAttributes, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::CreateGroupWithSummaryData(
    UBrainCloudWrapper *brainCloudWrapper,
    const FString &name,
    const FString &type,
    bool isOpenGroup,
    UBrainCloudGroupACL *acl,
    const FString &jsonData,
    const FString &jsonOwnerAttributes,
    const FString &jsonDefaultMemberAttributes,
    const FString &jsonSummaryData)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->createGroupWithSummaryData(name, type, isOpenGroup, acl, jsonData, jsonOwnerAttributes, jsonDefaultMemberAttributes, jsonSummaryData, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::CreateGroupEntity(
    UBrainCloudWrapper *brainCloudWrapper,
    const FString &groupId,
    const FString &entityType,
    bool isOwnedByGroupMember,
    UBrainCloudGroupACL *acl,
    const FString &jsonData)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->createGroupEntity(groupId, entityType, isOwnedByGroupMember, acl, jsonData, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::DeleteGroup(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, int32 version)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->deleteGroup(groupId, version, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::DeleteGroupEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, const FString &entityId, int32 version)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->deleteGroupEntity(groupId, entityId, version, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::GetMyGroups(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->getMyGroups(Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::IncrementGroupData(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, const FString &jsonData)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->incrementGroupData(groupId, jsonData, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::IncrementGroupEntityData(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, const FString &entityId, const FString &jsonData)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->incrementGroupEntityData(groupId, entityId, jsonData, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::InviteGroupMember(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, const FString &profileId, ERole role, const FString &jsonAttributes)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->inviteGroupMember(groupId, profileId, role, jsonAttributes, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::JoinGroup(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->joinGroup(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::LeaveGroup(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->leaveGroup(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::ListGroupsPage(UBrainCloudWrapper *brainCloudWrapper, const FString &jsonContext)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->listGroupsPage(jsonContext, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::ListGroupsPageByOffset(UBrainCloudWrapper *brainCloudWrapper, const FString &context, int32 pageOffset)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->listGroupsPageByOffset(context, pageOffset, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::ListGroupsWithMember(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->listGroupsWithMember(profileId, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::ReadGroup(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->readGroup(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::ReadGroupData(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->readGroupData(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::ReadGroupEntitiesPage(UBrainCloudWrapper *brainCloudWrapper, const FString &jsonContext)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->readGroupEntitiesPage(jsonContext, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::ReadGroupEntitiesPageByOffset(UBrainCloudWrapper *brainCloudWrapper, const FString &context, int32 pageOffset)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->readGroupEntitiesPageByOffset(context, pageOffset, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::ReadGroupEntity(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, const FString &entityId)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->readGroupEntity(groupId, entityId, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::ReadGroupMembers(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->readGroupMembers(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::RejectGroupInvitation(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->rejectGroupInvitation(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::RejectGroupJoinRequest(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, const FString &profileId)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->rejectGroupJoinRequest(groupId, profileId, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::RemoveGroupMember(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, const FString &profileId)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->removeGroupMember(groupId, profileId, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::UpdateGroupData(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, int32 version, const FString &jsonData)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->updateGroupData(groupId, version, jsonData, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::UpdateGroupEntityData(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, const FString &entityId, int32 version, const FString &jsonData)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->updateGroupEntityData(groupId, entityId, version, jsonData, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::UpdateGroupMember(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, const FString &profileId, ERole role, const FString &jsonAttributes)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->updateGroupMember(groupId, profileId, role, jsonAttributes, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::UpdateGroupName(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, const FString &name)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->updateGroupName(groupId, name, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::SetGroupOpen(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, bool isOpenGroup)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->setGroupOpen(groupId, isOpenGroup, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::UpdateGroupSummaryData(UBrainCloudWrapper *brainCloudWrapper, const FString &groupId, int32 version,  const FString &jsonSummaryData)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->updateGroupSummaryData(groupId, version, jsonSummaryData, Proxy);
    return Proxy;
}

UBCGroupProxy *UBCGroupProxy::GetRandomGroupsMatching(UBrainCloudWrapper *brainCloudWrapper, const FString &jsonWhere, int32 maxReturn)
{
    UBCGroupProxy *Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGroupService()->getRandomGroupsMatching(jsonWhere, maxReturn, Proxy);
    return Proxy;
}
