// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudGroup.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

#include "braincloud/internal/StringUtil.h"
#include "braincloud/internal/JsonUtil.h"

namespace BrainCloud
{
	BrainCloudGroup::BrainCloudGroup(BrainCloudClient* in_client) : m_client(in_client) { }

	void BrainCloudGroup::acceptGroupInvitation(const char * in_groupId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::AcceptGroupInvitation, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::addGroupMember(const char * in_groupId, const char * in_profileId, eGroupMember::Role role, const std::string& in_jsonAttributes, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::GroupProfileId.getValue()] = in_profileId;
		if (role != eGroupMember::UNKNOWN)
			message[OperationParam::GroupRole.getValue()] = roleToString(role);
		if (StringUtil::IsOptionalParameterValid(in_jsonAttributes))
			message[OperationParam::GroupAttributes.getValue()] = JsonUtil::jsonStringToValue(in_jsonAttributes);

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::AddGroupMember, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::approveGroupJoinRequest(const char * in_groupId, const char * in_profileId, eGroupMember::Role role, const std::string& in_jsonAttributes, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::GroupProfileId.getValue()] = in_profileId;
		if (role != eGroupMember::UNKNOWN)
			message[OperationParam::GroupRole.getValue()] = roleToString(role);
		if (StringUtil::IsOptionalParameterValid(in_jsonAttributes))
			message[OperationParam::GroupAttributes.getValue()] = JsonUtil::jsonStringToValue(in_jsonAttributes);

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::ApproveGroupJoinRequest, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::autoJoinGroup(const char * in_groupType, eAutoJoinStrategy::Strategy in_autoJoinStrategy, std::string in_dataQueryJson, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupType.getValue()] = in_groupType;
		message[OperationParam::GroupAutoJoinStrategy.getValue()] = autoJoinStrategyToString(in_autoJoinStrategy);

		if (StringUtil::IsOptionalParameterValid(in_dataQueryJson))
			message[OperationParam::GroupWhere.getValue()] = JsonUtil::jsonStringToValue(in_dataQueryJson);

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::AutoJoinGroup, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::cancelGroupInvitation(const char * in_groupId, const char * in_profileId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::GroupProfileId.getValue()] = in_profileId;

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::CancelGroupInvitation, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::createGroup(
		const char * in_name,
		const char * in_groupType,
		bool in_isOpenGroup,
		const std::string& in_acl,
		const std::string& in_jsonData,
		const std::string& in_jsonOwnerAttributes,
		const std::string& in_jsonDefaultMemberAttributes,
		IServerCallback * in_callback)
	{
		Json::Value message;
		if (StringUtil::IsOptionalParameterValid(in_name))
			message[OperationParam::GroupName.getValue()] = in_name;
		message[OperationParam::GroupType.getValue()] = in_groupType;
		message[OperationParam::GroupIsOpenGroup.getValue()] = in_isOpenGroup;
		if (StringUtil::IsOptionalParameterValid(in_acl))
			message[OperationParam::GroupAcl.getValue()] = JsonUtil::jsonStringToValue(in_acl);
		if (StringUtil::IsOptionalParameterValid(in_jsonData))
			message[OperationParam::GroupData.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);
		if (StringUtil::IsOptionalParameterValid(in_jsonOwnerAttributes))
			message[OperationParam::GroupOwnerAttributes.getValue()] = JsonUtil::jsonStringToValue(in_jsonOwnerAttributes);
		if (StringUtil::IsOptionalParameterValid(in_jsonDefaultMemberAttributes))
			message[OperationParam::GroupDefaultMemberAttributes.getValue()] = JsonUtil::jsonStringToValue(in_jsonDefaultMemberAttributes);

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::CreateGroup, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

		void BrainCloudGroup::createGroupWithSummaryData(
		const char * in_name,
		const char * in_groupType,
		bool in_isOpenGroup,
		const std::string& in_acl,
		const std::string& in_jsonData,
		const std::string& in_jsonOwnerAttributes,
		const std::string& in_jsonDefaultMemberAttributes,
		const std::string& in_jsonSummaryData,
		IServerCallback * in_callback)
	{
		Json::Value message;
		if (StringUtil::IsOptionalParameterValid(in_name))
			message[OperationParam::GroupName.getValue()] = in_name;
		message[OperationParam::GroupType.getValue()] = in_groupType;
		message[OperationParam::GroupIsOpenGroup.getValue()] = in_isOpenGroup;
		if (StringUtil::IsOptionalParameterValid(in_acl))
			message[OperationParam::GroupAcl.getValue()] = JsonUtil::jsonStringToValue(in_acl);
		if (StringUtil::IsOptionalParameterValid(in_jsonData))
			message[OperationParam::GroupData.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);
		if (StringUtil::IsOptionalParameterValid(in_jsonOwnerAttributes))
			message[OperationParam::GroupOwnerAttributes.getValue()] = JsonUtil::jsonStringToValue(in_jsonOwnerAttributes);
		if (StringUtil::IsOptionalParameterValid(in_jsonDefaultMemberAttributes))
			message[OperationParam::GroupDefaultMemberAttributes.getValue()] = JsonUtil::jsonStringToValue(in_jsonDefaultMemberAttributes);
		if (StringUtil::IsOptionalParameterValid(in_jsonSummaryData))
			message[OperationParam::GroupSummaryData.getValue()] = JsonUtil::jsonStringToValue(in_jsonSummaryData);

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::CreateGroup, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::createGroupEntity(
		const char * in_groupId,
		const char * in_entityType,
		bool in_isOwnedByGroupMember,
		const std::string& in_acl,
		const std::string& in_jsonData,
		IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		if (StringUtil::IsOptionalParameterValid(in_entityType))
			message[OperationParam::GroupEntityType.getValue()] = in_entityType;
		message[OperationParam::GroupIsOwnedByGroupMember.getValue()] = in_isOwnedByGroupMember;
		if (StringUtil::IsOptionalParameterValid(in_acl))
			message[OperationParam::GroupAcl.getValue()] = JsonUtil::jsonStringToValue(in_acl);
		if (StringUtil::IsOptionalParameterValid(in_jsonData))
			message[OperationParam::GroupData.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::CreateGroupEntity, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::deleteGroup(const char * in_groupId, int32_t in_version, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::GroupVersion.getValue()] = in_version;

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::DeleteGroup, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::deleteGroupEntity(const char * in_groupId, const char * in_entityId, int32_t in_version, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::GroupEntityId.getValue()] = in_entityId;
		message[OperationParam::GroupVersion.getValue()] = in_version;

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::DeleteGroupEntity, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::getMyGroups(IServerCallback * in_callback)
	{
		Json::Value nullMsg = Json::nullValue;
		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::GetMyGroups, nullMsg, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::incrementGroupData(const char * in_groupId, const std::string& in_jsonData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::GroupData.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);;

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::IncrementGroupData, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::incrementGroupEntityData(const char * in_groupId, const char * in_entityId, const std::string& in_jsonData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::GroupEntityId.getValue()] = in_entityId;
		message[OperationParam::GroupData.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);;

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::IncrementGroupEntityData, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::inviteGroupMember(const char * in_groupId, const char * in_profileId, eGroupMember::Role role, const std::string& in_jsonAttributes, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::GroupProfileId.getValue()] = in_profileId;
		if (role != eGroupMember::UNKNOWN)
			message[OperationParam::GroupRole.getValue()] = roleToString(role);
		if (StringUtil::IsOptionalParameterValid(in_jsonAttributes))
			message[OperationParam::GroupAttributes.getValue()] = JsonUtil::jsonStringToValue(in_jsonAttributes);

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::InviteGroupMember, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::joinGroup(const char * in_groupId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::JoinGroup, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::leaveGroup(const char * in_groupId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::LeaveGroup, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::listGroupsPage(const std::string& in_jsonContext, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupContext.getValue()] = JsonUtil::jsonStringToValue(in_jsonContext);

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::ListGroupsPage, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::listGroupsPageByOffset(const char * in_encodedContext, int32_t in_pageOffset, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupContext.getValue()] = in_encodedContext;
		message[OperationParam::GroupPageOffset.getValue()] = in_pageOffset;

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::ListGroupsPageByOffset, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::listGroupsWithMember(const char * in_profileId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupProfileId.getValue()] = in_profileId;

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::ListGroupsWithMember, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::readGroup(const char * in_groupId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::ReadGroup, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::readGroupData(const char * in_groupId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::ReadGroupData, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::readGroupEntitiesPage(const std::string& in_jsonContext, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupContext.getValue()] = JsonUtil::jsonStringToValue(in_jsonContext);

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::ReadGroupEntitiesPage, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::readGroupEntitiesPageByOffset(const char * in_encodedContext, int32_t in_pageOffset, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupContext.getValue()] = in_encodedContext;
		message[OperationParam::GroupPageOffset.getValue()] = in_pageOffset;

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::ReadGroupEntitiesPageByOffset, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::readGroupEntity(const char * in_groupId, const char * in_entityId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::GroupEntityId.getValue()] = in_entityId;

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::ReadGroupEntity, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::readGroupMembers(const char * in_groupId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::ReadGroupMembers, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::rejectGroupInvitation(const char * in_groupId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::RejectGroupInvitation, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::rejectGroupJoinRequest(const char * in_groupId, const char * in_profileId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::GroupProfileId.getValue()] = in_profileId;

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::RejectGroupJoinRequest, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::removeGroupMember(const char * in_groupId, const char * in_profileId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::GroupProfileId.getValue()] = in_profileId;

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::RemoveGroupMember, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::updateGroupData(const char * in_groupId, int32_t in_version, const std::string& in_jsonData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::GroupVersion.getValue()] = in_version;
		message[OperationParam::GroupData.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::UpdateGroupData, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::updateGroupEntityData(const char * in_groupId, const char * in_entityId, int32_t in_version, const std::string& in_jsonData, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::GroupEntityId.getValue()] = in_entityId;
		message[OperationParam::GroupVersion.getValue()] = in_version;
		message[OperationParam::GroupData.getValue()] = JsonUtil::jsonStringToValue(in_jsonData);

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::UpdateGroupEntity, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::updateGroupMember(const char * in_groupId, const char * in_profileId, eGroupMember::Role role, const std::string& in_jsonAttributes, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::GroupProfileId.getValue()] = in_profileId;
		if (role != eGroupMember::UNKNOWN)
			message[OperationParam::GroupRole.getValue()] = roleToString(role);
		if (StringUtil::IsOptionalParameterValid(in_jsonAttributes))
			message[OperationParam::GroupAttributes.getValue()] = JsonUtil::jsonStringToValue(in_jsonAttributes);

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::UpdateGroupMember, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::updateGroupName(const char * in_groupId, const char * in_name, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::GroupName.getValue()] = in_name;

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::UpdateGroupName, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::setGroupOpen(const char * in_groupId, bool in_isOpenGroup, IServerCallback *in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::GroupIsOpenGroup.getValue()] = in_isOpenGroup;

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::SetGroupOpen, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudGroup::updateGroupSummaryData(const char* in_groupId, int in_version, const std::string& in_jsonSummaryData, IServerCallback *in_callback)
	{
		Json::Value message;
		message[OperationParam::GroupId.getValue()] = in_groupId;
		message[OperationParam::GroupVersion.getValue()] = in_version;
		if (StringUtil::IsOptionalParameterValid(in_jsonSummaryData))
			message[OperationParam::GroupSummaryData.getValue()] = JsonUtil::jsonStringToValue(in_jsonSummaryData);


		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::UpdateGroupSummaryData, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}


	void BrainCloudGroup::getRandomGroupsMatching(std::string in_jsonWhere, int in_maxReturn, IServerCallback *in_callback)
	{
		Json::Value message;
		if (StringUtil::IsOptionalParameterValid(in_jsonWhere))
			message[OperationParam::GroupWhere.getValue()] = JsonUtil::jsonStringToValue(in_jsonWhere);
		message[OperationParam::MaxReturn.getValue()] = in_maxReturn;

		ServerCall * sc = new ServerCall(ServiceName::Group, ServiceOperation::GetRandomGroupsMatching, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	std::string BrainCloudGroup::roleToString(eGroupMember::Role role)
	{
		if (role == eGroupMember::MEMBER)
			return "MEMBER";
		else if (role == eGroupMember::ADMIN)
			return "ADMIN";
		else if (role == eGroupMember::OWNER)
			return "OWNER";

		return "OTHER";
	}

	std::string BrainCloudGroup::autoJoinStrategyToString(eAutoJoinStrategy::Strategy strategy)
	{
		if (strategy == eAutoJoinStrategy::JoinFirstGroup)
			return "JoinFirstGroup";
		else if (strategy == eAutoJoinStrategy::JoinRandomGroup)
			return "JoinRandomGroup";
		return "UNKNOWN";
	}
}
