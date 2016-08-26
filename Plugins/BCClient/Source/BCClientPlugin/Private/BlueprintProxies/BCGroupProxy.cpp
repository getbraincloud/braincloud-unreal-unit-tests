// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCGroupProxy.h"
#include "BrainCloudGroupACL.h"

UBCGroupProxy::UBCGroupProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}


UBCGroupProxy* UBCGroupProxy::AcceptGroupInvitation(const FString& groupId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->acceptGroupInvitation(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::AddGroupMember(const FString& groupId, const FString& profileId, ERole role, const FString& jsonAttributes)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->addGroupMember(groupId, profileId, role, jsonAttributes, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ApproveGroupJoinRequest(const FString& groupId, const FString& profileId, ERole role, const FString& jsonAttributes)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->approveGroupJoinRequest(groupId, profileId, role, jsonAttributes, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::AutoJoinGroup(const FString& groupType, EAutoJoinStrategy autoJoinStrategy, const FString& dataQueryJson)
{
	UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
	BrainCloudClient::getInstance()->getGroupService()->autoJoinGroup(groupType, autoJoinStrategy, dataQueryJson, Proxy);
	return Proxy;
}

UBCGroupProxy* UBCGroupProxy::CancelGroupInvitation(const FString& groupId, const FString& profileId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->cancelGroupInvitation(groupId, profileId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::CreateGroup(
    const FString& name,
    const FString& type,
    bool isOpenGroup,
    UBrainCloudGroupACL* acl,
    const FString& jsonData,
    const FString& jsonOwnerAttributes,
    const FString& jsonDefaultMemberAttributes)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->createGroup(
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
    const FString& groupId,
    const FString& entityType,
    bool isOwnedByGroupMember,
    UBrainCloudGroupACL* acl,
    const FString& jsonData)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->createGroupEntity(groupId, entityType, isOwnedByGroupMember, acl, jsonData, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::DeleteGroup(const FString& groupId, int32 version)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->deleteGroup(groupId, version, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::DeleteGroupEntity(const FString& groupId, const FString& entityId, int32 version)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->deleteGroupEntity(groupId, entityId, version, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::GetMyGroups()
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->getMyGroups(Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::IncrementGroupData(const FString& groupId, const FString& jsonData)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->incrementGroupData(groupId, jsonData, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::IncrementGroupEntityData(const FString& groupId, const FString& entityId, const FString& jsonData)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->incrementGroupEntityData(groupId, entityId, jsonData, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::InviteGroupMember(const FString& groupId, const FString& profileId, ERole role, const FString& jsonAttributes)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->inviteGroupMember(groupId, profileId, role, jsonAttributes, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::JoinGroup(const FString& groupId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->joinGroup(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::LeaveGroup(const FString& groupId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->leaveGroup(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ListGroupsPage(const FString& jsonContext)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->listGroupsPage(jsonContext, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ListGroupsPageByOffset(const FString& context, int32 pageOffset)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->listGroupsPageByOffset(context, pageOffset, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ListGroupsWithMember(const FString& profileId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->listGroupsWithMember(profileId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ReadGroup(const FString& groupId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->readGroup(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ReadGroupData(const FString& groupId)
{
	UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
	BrainCloudClient::getInstance()->getGroupService()->readGroupData(groupId, Proxy);
	return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ReadGroupEntitiesPage(const FString& jsonContext)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->readGroupEntitiesPage(jsonContext, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ReadGroupEntitiesPageByOffset(const FString& context, int32 pageOffset)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->readGroupEntitiesPageByOffset(context, pageOffset, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ReadGroupEntity(const FString& groupId, const FString& entityId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->readGroupEntity(groupId, entityId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::ReadGroupMembers(const FString& groupId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->readGroupMembers(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::RejectGroupInvitation(const FString& groupId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->rejectGroupInvitation(groupId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::RejectGroupJoinRequest(const FString& groupId, const FString& profileId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->rejectGroupJoinRequest(groupId, profileId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::RemoveGroupMember(const FString& groupId, const FString& profileId)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->removeGroupMember(groupId, profileId, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::UpdateGroupData(const FString& groupId, int32 version, const FString& jsonData)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->updateGroupData(groupId, version, jsonData, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::UpdateGroupEntityData(const FString& groupId, const FString& entityId, int32 version, const FString& jsonData)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->updateGroupEntityData(groupId, entityId, version, jsonData, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::UpdateGroupMember(const FString& groupId, const FString& profileId, ERole role, const FString& jsonAttributes)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->updateGroupMember(groupId, profileId, role, jsonAttributes, Proxy);
    return Proxy;
}

UBCGroupProxy* UBCGroupProxy::UpdateGroupName(const FString& groupId, const FString& name)
{
    UBCGroupProxy* Proxy = NewObject<UBCGroupProxy>();
    BrainCloudClient::getInstance()->getGroupService()->updateGroupName(groupId, name, Proxy);
    return Proxy;
}

//callbacks
void UBCGroupProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
}

void UBCGroupProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
}

