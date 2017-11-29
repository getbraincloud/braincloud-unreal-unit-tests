// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloud.h"
#include "BCWrapperProxy.h"
#include "BCGroupProxy.h"
#include "BrainCloudGroupACL.h"
#include "BrainCloudWrapper.h"

UBCGroupProxy::UBCGroupProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}


UBCGroupProxy* UBCGroupProxy::AcceptGroupInvitation(ABrainCloud *brainCloud, const FString& groupId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->acceptGroupInvitation(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::AddGroupMember(ABrainCloud *brainCloud, const FString& groupId, const FString& profileId, ERole role, const FString& jsonAttributes)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->addGroupMember(groupId, profileId, role, jsonAttributes, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ApproveGroupJoinRequest(ABrainCloud *brainCloud, const FString& groupId, const FString& profileId, ERole role, const FString& jsonAttributes)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->approveGroupJoinRequest(groupId, profileId, role, jsonAttributes, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::AutoJoinGroup(ABrainCloud *brainCloud, const FString& groupType, EAutoJoinStrategy autoJoinStrategy, const FString& dataQueryJson)
{
	UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->autoJoinGroup(groupType, autoJoinStrategy, dataQueryJson, Proxy);
	return Proxy;
}

UBCGroupProxy* UBCGroupProxy::CancelGroupInvitation(ABrainCloud *brainCloud, const FString& groupId, const FString& profileId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->cancelGroupInvitation(groupId, profileId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::CreateGroup(
	ABrainCloud *brainCloud,
    const FString& name,
    const FString& type,
    bool isOpenGroup,
    UBrainCloudGroupACL* acl,
    const FString& jsonData,
    const FString& jsonOwnerAttributes,
    const FString& jsonDefaultMemberAttributes)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->createGroup(
        name,
        type,
        isOpenGroup,
        acl,
        jsonData,
        jsonOwnerAttributes,
        jsonDefaultMemberAttributes,
        Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::CreateGroupEntity(
	ABrainCloud *brainCloud,
	const FString& groupId,
    const FString& entityType,
    bool isOwnedByGroupMember,
    UBrainCloudGroupACL* acl,
    const FString& jsonData)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->createGroupEntity(groupId, entityType, isOwnedByGroupMember, acl, jsonData, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::DeleteGroup(ABrainCloud *brainCloud, const FString& groupId, int32 version)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->deleteGroup(groupId, version, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::DeleteGroupEntity(ABrainCloud *brainCloud, const FString& groupId, const FString& entityId, int32 version)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->deleteGroupEntity(groupId, entityId, version, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::GetMyGroups(ABrainCloud *brainCloud)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->getMyGroups(Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::IncrementGroupData(ABrainCloud *brainCloud, const FString& groupId, const FString& jsonData)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->incrementGroupData(groupId, jsonData, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::IncrementGroupEntityData(ABrainCloud *brainCloud, const FString& groupId, const FString& entityId, const FString& jsonData)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->incrementGroupEntityData(groupId, entityId, jsonData, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::InviteGroupMember(ABrainCloud *brainCloud, const FString& groupId, const FString& profileId, ERole role, const FString& jsonAttributes)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->inviteGroupMember(groupId, profileId, role, jsonAttributes, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::JoinGroup(ABrainCloud *brainCloud, const FString& groupId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->joinGroup(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::LeaveGroup(ABrainCloud *brainCloud, const FString& groupId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->leaveGroup(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ListGroupsPage(ABrainCloud *brainCloud, const FString& jsonContext)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->listGroupsPage(jsonContext, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ListGroupsPageByOffset(ABrainCloud *brainCloud, const FString& context, int32 pageOffset)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->listGroupsPageByOffset(context, pageOffset, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ListGroupsWithMember(ABrainCloud *brainCloud, const FString& profileId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->listGroupsWithMember(profileId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ReadGroup(ABrainCloud *brainCloud, const FString& groupId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->readGroup(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ReadGroupData(ABrainCloud *brainCloud, const FString& groupId)
{
	UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->readGroupData(groupId, Proxy);
	return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ReadGroupEntitiesPage(ABrainCloud *brainCloud, const FString& jsonContext)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->readGroupEntitiesPage(jsonContext, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ReadGroupEntitiesPageByOffset(ABrainCloud *brainCloud, const FString& context, int32 pageOffset)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->readGroupEntitiesPageByOffset(context, pageOffset, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ReadGroupEntity(ABrainCloud *brainCloud, const FString& groupId, const FString& entityId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->readGroupEntity(groupId, entityId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ReadGroupMembers(ABrainCloud *brainCloud, const FString& groupId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->readGroupMembers(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::RejectGroupInvitation(ABrainCloud *brainCloud, const FString& groupId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->rejectGroupInvitation(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::RejectGroupJoinRequest(ABrainCloud *brainCloud, const FString& groupId, const FString& profileId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->rejectGroupJoinRequest(groupId, profileId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::RemoveGroupMember(ABrainCloud *brainCloud, const FString& groupId, const FString& profileId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->removeGroupMember(groupId, profileId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::UpdateGroupData(ABrainCloud *brainCloud, const FString& groupId, int32 version, const FString& jsonData)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->updateGroupData(groupId, version, jsonData, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::UpdateGroupEntityData(ABrainCloud *brainCloud, const FString& groupId, const FString& entityId, int32 version, const FString& jsonData)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->updateGroupEntityData(groupId, entityId, version, jsonData, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::UpdateGroupMember(ABrainCloud *brainCloud, const FString& groupId, const FString& profileId, ERole role, const FString& jsonAttributes)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->updateGroupMember(groupId, profileId, role, jsonAttributes, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::UpdateGroupName(ABrainCloud *brainCloud, const FString& groupId, const FString& name)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->updateGroupName(groupId, name, Proxy);
    return Proxy;
}

//callbacks
void UBCGroupProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCGroupProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

