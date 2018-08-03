// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloudActor.h"
#include "BCWrapperProxy.h"
#include "BCGroupProxy.h"
#include "BrainCloudGroupACL.h"
#include "BrainCloudWrapper.h"

UBCGroupProxy::UBCGroupProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}


UBCGroupProxy* UBCGroupProxy::AcceptGroupInvitation(ABrainCloudActor *brainCloud, const FString& groupId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->acceptGroupInvitation(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::AddGroupMember(ABrainCloudActor *brainCloud, const FString& groupId, const FString& profileId, ERole role, const FString& jsonAttributes)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->addGroupMember(groupId, profileId, role, jsonAttributes, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ApproveGroupJoinRequest(ABrainCloudActor *brainCloud, const FString& groupId, const FString& profileId, ERole role, const FString& jsonAttributes)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->approveGroupJoinRequest(groupId, profileId, role, jsonAttributes, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::AutoJoinGroup(ABrainCloudActor *brainCloud, const FString& groupType, EAutoJoinStrategy autoJoinStrategy, const FString& dataQueryJson)
{
	UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->autoJoinGroup(groupType, autoJoinStrategy, dataQueryJson, Proxy);
	return Proxy;
}

UBCGroupProxy* UBCGroupProxy::CancelGroupInvitation(ABrainCloudActor *brainCloud, const FString& groupId, const FString& profileId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->cancelGroupInvitation(groupId, profileId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::CreateGroup(
	ABrainCloudActor *brainCloud,
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
	ABrainCloudActor *brainCloud,
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

UBCGroupProxy* UBCGroupProxy::DeleteGroup(ABrainCloudActor *brainCloud, const FString& groupId, int32 version)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->deleteGroup(groupId, version, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::DeleteGroupEntity(ABrainCloudActor *brainCloud, const FString& groupId, const FString& entityId, int32 version)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->deleteGroupEntity(groupId, entityId, version, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::GetMyGroups(ABrainCloudActor *brainCloud)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->getMyGroups(Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::IncrementGroupData(ABrainCloudActor *brainCloud, const FString& groupId, const FString& jsonData)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->incrementGroupData(groupId, jsonData, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::IncrementGroupEntityData(ABrainCloudActor *brainCloud, const FString& groupId, const FString& entityId, const FString& jsonData)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->incrementGroupEntityData(groupId, entityId, jsonData, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::InviteGroupMember(ABrainCloudActor *brainCloud, const FString& groupId, const FString& profileId, ERole role, const FString& jsonAttributes)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->inviteGroupMember(groupId, profileId, role, jsonAttributes, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::JoinGroup(ABrainCloudActor *brainCloud, const FString& groupId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->joinGroup(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::LeaveGroup(ABrainCloudActor *brainCloud, const FString& groupId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->leaveGroup(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ListGroupsPage(ABrainCloudActor *brainCloud, const FString& jsonContext)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->listGroupsPage(jsonContext, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ListGroupsPageByOffset(ABrainCloudActor *brainCloud, const FString& context, int32 pageOffset)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->listGroupsPageByOffset(context, pageOffset, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ListGroupsWithMember(ABrainCloudActor *brainCloud, const FString& profileId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->listGroupsWithMember(profileId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ReadGroup(ABrainCloudActor *brainCloud, const FString& groupId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->readGroup(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ReadGroupData(ABrainCloudActor *brainCloud, const FString& groupId)
{
	UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->readGroupData(groupId, Proxy);
	return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ReadGroupEntitiesPage(ABrainCloudActor *brainCloud, const FString& jsonContext)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->readGroupEntitiesPage(jsonContext, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ReadGroupEntitiesPageByOffset(ABrainCloudActor *brainCloud, const FString& context, int32 pageOffset)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->readGroupEntitiesPageByOffset(context, pageOffset, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ReadGroupEntity(ABrainCloudActor *brainCloud, const FString& groupId, const FString& entityId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->readGroupEntity(groupId, entityId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ReadGroupMembers(ABrainCloudActor *brainCloud, const FString& groupId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->readGroupMembers(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::RejectGroupInvitation(ABrainCloudActor *brainCloud, const FString& groupId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->rejectGroupInvitation(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::RejectGroupJoinRequest(ABrainCloudActor *brainCloud, const FString& groupId, const FString& profileId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->rejectGroupJoinRequest(groupId, profileId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::RemoveGroupMember(ABrainCloudActor *brainCloud, const FString& groupId, const FString& profileId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->removeGroupMember(groupId, profileId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::UpdateGroupData(ABrainCloudActor *brainCloud, const FString& groupId, int32 version, const FString& jsonData)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->updateGroupData(groupId, version, jsonData, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::UpdateGroupEntityData(ABrainCloudActor *brainCloud, const FString& groupId, const FString& entityId, int32 version, const FString& jsonData)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->updateGroupEntityData(groupId, entityId, version, jsonData, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::UpdateGroupMember(ABrainCloudActor *brainCloud, const FString& groupId, const FString& profileId, ERole role, const FString& jsonAttributes)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getGroupService()->updateGroupMember(groupId, profileId, role, jsonAttributes, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::UpdateGroupName(ABrainCloudActor *brainCloud, const FString& groupId, const FString& name)
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

