// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudGroup.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"
#include "BrainCloudGroupACL.h"

BrainCloudGroup::BrainCloudGroup(BrainCloudClient *client) : _client(client){};

void BrainCloudGroup::acceptGroupInvitation(const FString &groupId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::AcceptGroupInvitation, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::addGroupMember(const FString &groupId, const FString &profileId, ERole role, const FString &jsonAttributes, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetStringField(OperationParam::GroupProfileId.getValue(), profileId);
	message->SetStringField(OperationParam::GroupRole.getValue(), roleToString(role));
	if (OperationParam::isOptionalParamValid(jsonAttributes))
		message->SetObjectField(OperationParam::GroupAttributes.getValue(), JsonUtil::jsonStringToValue(jsonAttributes));

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::AddGroupMember, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::approveGroupJoinRequest(const FString &groupId, const FString &profileId, ERole role, const FString &jsonAttributes, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetStringField(OperationParam::GroupProfileId.getValue(), profileId);
	message->SetStringField(OperationParam::GroupRole.getValue(), roleToString(role));
	if (OperationParam::isOptionalParamValid(jsonAttributes))
		message->SetObjectField(OperationParam::GroupAttributes.getValue(), JsonUtil::jsonStringToValue(jsonAttributes));

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::ApproveGroupJoinRequest, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::autoJoinGroup(const FString &groupType, EAutoJoinStrategy autoJoinStrategy, const FString &dataQueryJson, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupType.getValue(), groupType);
	message->SetStringField(OperationParam::GroupAutoJoinStrategy.getValue(), AutoJoinStrategyToString(autoJoinStrategy));
	if (OperationParam::isOptionalParamValid(dataQueryJson))
		message->SetObjectField(OperationParam::GroupWhere.getValue(), JsonUtil::jsonStringToValue(dataQueryJson));

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::AutoJoinGroup, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::autoJoinGroupMulti(const TArray<FString> &groupTypes, EAutoJoinStrategy autoJoinStrategy, const FString &dataQueryJson, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetArrayField(OperationParam::GroupTypes.getValue(), JsonUtil::arrayToJsonArray(groupTypes));
	message->SetStringField(OperationParam::GroupAutoJoinStrategy.getValue(), AutoJoinStrategyToString(autoJoinStrategy));
	if (OperationParam::isOptionalParamValid(dataQueryJson))
		message->SetObjectField(OperationParam::GroupWhere.getValue(), JsonUtil::jsonStringToValue(dataQueryJson));

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::AutoJoinGroupMulti, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::cancelGroupInvitation(const FString &groupId, const FString &profileId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetStringField(OperationParam::GroupProfileId.getValue(), profileId);

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::CancelGroupInvitation, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::createGroup(
	const FString &name,
	const FString &groupType,
	bool isOpenGroup,
	UBrainCloudGroupACL *acl,
	const FString &jsonData,
	const FString &jsonOwnerAttributes,
	const FString &jsonDefaultMemberAttributes,
	IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	if (OperationParam::isOptionalParamValid(name))
		message->SetStringField(OperationParam::GroupName.getValue(), name);
	message->SetStringField(OperationParam::GroupType.getValue(), groupType);
	message->SetBoolField(OperationParam::GroupIsOpenGroup.getValue(), isOpenGroup);
	if (acl != nullptr)
		message->SetObjectField(OperationParam::GroupAcl.getValue(), acl->toJsonObject());
	if (OperationParam::isOptionalParamValid(jsonData))
		message->SetObjectField(OperationParam::GroupData.getValue(), JsonUtil::jsonStringToValue(jsonData));
	if (OperationParam::isOptionalParamValid(jsonOwnerAttributes))
		message->SetObjectField(OperationParam::GroupOwnerAttributes.getValue(), JsonUtil::jsonStringToValue(jsonOwnerAttributes));
	if (OperationParam::isOptionalParamValid(jsonDefaultMemberAttributes))
		message->SetObjectField(OperationParam::GroupDefaultMemberAttributes.getValue(), JsonUtil::jsonStringToValue(jsonDefaultMemberAttributes));

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::CreateGroup, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::createGroupWithSummaryData(
	const FString &name,
	const FString &groupType,
	bool isOpenGroup,
	UBrainCloudGroupACL *acl,
	const FString &jsonData,
	const FString &jsonOwnerAttributes,
	const FString &jsonDefaultMemberAttributes,
	const FString &jsonSummaryData,
	IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	if (OperationParam::isOptionalParamValid(name))
		message->SetStringField(OperationParam::GroupName.getValue(), name);
	message->SetStringField(OperationParam::GroupType.getValue(), groupType);
	message->SetBoolField(OperationParam::GroupIsOpenGroup.getValue(), isOpenGroup);
	if (acl != nullptr)
		message->SetObjectField(OperationParam::GroupAcl.getValue(), acl->toJsonObject());
	if (OperationParam::isOptionalParamValid(jsonData))
		message->SetObjectField(OperationParam::GroupData.getValue(), JsonUtil::jsonStringToValue(jsonData));
	if (OperationParam::isOptionalParamValid(jsonOwnerAttributes))
		message->SetObjectField(OperationParam::GroupOwnerAttributes.getValue(), JsonUtil::jsonStringToValue(jsonOwnerAttributes));
	if (OperationParam::isOptionalParamValid(jsonDefaultMemberAttributes))
		message->SetObjectField(OperationParam::GroupDefaultMemberAttributes.getValue(), JsonUtil::jsonStringToValue(jsonDefaultMemberAttributes));
	if (OperationParam::isOptionalParamValid(jsonSummaryData))
		message->SetObjectField(OperationParam::GroupSummaryData.getValue(), JsonUtil::jsonStringToValue(jsonSummaryData));

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::CreateGroup, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::createGroupEntity(
	const FString &groupId,
	const FString &entityType,
	bool isOwnedByGroupMember,
	UBrainCloudGroupACL *acl,
	const FString &jsonData,
	IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetStringField(OperationParam::GroupEntityType.getValue(), entityType);
	message->SetBoolField(OperationParam::GroupIsOwnedByGroupMember.getValue(), isOwnedByGroupMember);
	if (acl != nullptr)
		message->SetObjectField(OperationParam::GroupAcl.getValue(), acl->toJsonObject());
	if (OperationParam::isOptionalParamValid(jsonData))
		message->SetObjectField(OperationParam::GroupData.getValue(), JsonUtil::jsonStringToValue(jsonData));

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::CreateGroupEntity, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::deleteGroup(const FString &groupId, int32 version, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetNumberField(OperationParam::GroupVersion.getValue(), version);

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::DeleteGroup, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::deleteGroupEntity(const FString &groupId, const FString &entityId, int32 version, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetStringField(OperationParam::GroupEntityId.getValue(), entityId);
	message->SetNumberField(OperationParam::GroupVersion.getValue(), version);

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::DeleteGroupEntity, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::getMyGroups(IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::GetMyGroups, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::incrementGroupData(const FString &groupId, const FString &jsonData, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetObjectField(OperationParam::GroupData.getValue(), JsonUtil::jsonStringToValue(jsonData));

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::IncrementGroupData, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::incrementGroupEntityData(const FString &groupId, const FString &entityId, const FString &jsonData, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetStringField(OperationParam::GroupEntityId.getValue(), entityId);
	message->SetObjectField(OperationParam::GroupData.getValue(), JsonUtil::jsonStringToValue(jsonData));

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::IncrementGroupEntityData, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::inviteGroupMember(const FString &groupId, const FString &profileId, ERole role, const FString &jsonAttributes, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetStringField(OperationParam::GroupProfileId.getValue(), profileId);
	message->SetStringField(OperationParam::GroupRole.getValue(), roleToString(role));
	if (OperationParam::isOptionalParamValid(jsonAttributes))
		message->SetObjectField(OperationParam::GroupAttributes.getValue(), JsonUtil::jsonStringToValue(jsonAttributes));

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::InviteGroupMember, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::joinGroup(const FString &groupId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::JoinGroup, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::leaveGroup(const FString &groupId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::LeaveGroup, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::listGroupsPage(const FString &jsonContext, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetObjectField(OperationParam::GroupContext.getValue(), JsonUtil::jsonStringToValue(jsonContext));

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::ListGroupsPage, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::listGroupsPageByOffset(const FString &encodedContext, int32 pageOffset, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupContext.getValue(), encodedContext);
	message->SetNumberField(OperationParam::GroupPageOffset.getValue(), pageOffset);

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::ListGroupsPageByOffset, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::listGroupsWithMember(const FString &profileId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupProfileId.getValue(), profileId);

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::ListGroupsWithMember, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::readGroup(const FString &groupId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::ReadGroup, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::readGroupData(const FString &groupId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::ReadGroupData, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::readGroupEntitiesPage(const FString &jsonContext, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetObjectField(OperationParam::GroupContext.getValue(), JsonUtil::jsonStringToValue(jsonContext));

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::ReadGroupEntitiesPage, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::readGroupEntitiesPageByOffset(const FString &encodedContext, int32 pageOffset, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupContext.getValue(), encodedContext);
	message->SetNumberField(OperationParam::GroupPageOffset.getValue(), pageOffset);

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::ReadGroupEntitiesPageByOffset, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::readGroupEntity(const FString &groupId, const FString &entityId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetStringField(OperationParam::GroupEntityId.getValue(), entityId);

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::ReadGroupEntity, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::readGroupMembers(const FString &groupId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::ReadGroupMembers, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::rejectGroupInvitation(const FString &groupId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::RejectGroupInvitation, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::rejectGroupJoinRequest(const FString &groupId, const FString &profileId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetStringField(OperationParam::GroupProfileId.getValue(), profileId);

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::RejectGroupJoinRequest, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::removeGroupMember(const FString &groupId, const FString &profileId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetStringField(OperationParam::GroupProfileId.getValue(), profileId);

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::RemoveGroupMember, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::updateGroupData(const FString &groupId, int32 version, const FString &jsonData, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetNumberField(OperationParam::GroupVersion.getValue(), version);
	message->SetObjectField(OperationParam::GroupData.getValue(), JsonUtil::jsonStringToValue(jsonData));

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::UpdateGroupData, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::updateGroupEntityData(const FString &groupId, const FString &entityId, int32 version, const FString &jsonData, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetStringField(OperationParam::GroupEntityId.getValue(), entityId);
	message->SetNumberField(OperationParam::GroupVersion.getValue(), version);
	if (OperationParam::isOptionalParamValid(jsonData))
		message->SetObjectField(OperationParam::GroupData.getValue(), JsonUtil::jsonStringToValue(jsonData));

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::UpdateGroupEntity, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::updateGroupMember(const FString &groupId, const FString &profileId, ERole role, const FString &jsonAttributes, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetStringField(OperationParam::GroupProfileId.getValue(), profileId);
	message->SetStringField(OperationParam::GroupRole.getValue(), roleToString(role));
	if (OperationParam::isOptionalParamValid(jsonAttributes))
		message->SetObjectField(OperationParam::GroupAttributes.getValue(), JsonUtil::jsonStringToValue(jsonAttributes));

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::UpdateGroupMember, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::updateGroupName(const FString &groupId, const FString &name, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetStringField(OperationParam::GroupName.getValue(), name);

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::UpdateGroupName, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::setGroupOpen(const FString &groupId, bool isOpenGroup, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetBoolField(OperationParam::GroupIsOpenGroup.getValue(), isOpenGroup);

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::SetGroupOpen, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGroup::updateGroupSummaryData(const FString &groupId, int32 version,  const FString &jsonSummaryData, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GroupId.getValue(), groupId);
	message->SetNumberField(OperationParam::GroupVersion.getValue(), version);
	if (OperationParam::isOptionalParamValid(jsonSummaryData))
		message->SetObjectField(OperationParam::GroupSummaryData.getValue(), JsonUtil::jsonStringToValue(jsonSummaryData));

	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::UpdateGroupSummaryData, message, callback);
	_client->sendRequest(sc);
}
    
void BrainCloudGroup::getRandomGroupsMatching(const FString &jsonWhere, int32 maxReturn, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	if (OperationParam::isOptionalParamValid(jsonWhere))
		message->SetObjectField(OperationParam::GroupWhere.getValue(), JsonUtil::jsonStringToValue(jsonWhere));
	message->SetNumberField(OperationParam::GroupMaxReturn.getValue(), maxReturn);
	
	ServerCall *sc = new ServerCall(ServiceName::Group, ServiceOperation::GetRandomGroupsMatching, message, callback);
	_client->sendRequest(sc);
}

FString BrainCloudGroup::roleToString(ERole role)
{
	switch (role)
	{
	case ERole::OWNER:
		return "OWNER";
	case ERole::ADMIN:
		return "ADMIN";
	case ERole::MEMBER:
		return "MEMBER";
	case ERole::OTHER:
		return "OTHER";
	}
	return "TYPE_NOT_FOUND";
}

FString BrainCloudGroup::AutoJoinStrategyToString(EAutoJoinStrategy strategy)
{
	switch (strategy)
	{
	case EAutoJoinStrategy::JoinFirstGroup:
		return "JoinFirstGroup";
	case EAutoJoinStrategy::JoinRandomGroup:
		return "JoinRandomGroup";
	}
	return "STRATEGY_NOT_FOUND";
}
