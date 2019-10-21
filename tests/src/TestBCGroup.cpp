#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCGroup.h"
#include <vector>
using namespace BrainCloud;

TestBCGroup::TestBCGroup() :
	_groupType("test"),
	_entityType("test"),
	_groupId(""),
	_testJsonPair("{ \"test\": 123 }"),
	_testAcl("{ \"other\": 2, \"member\": 2 }")
{
}

TEST_F(TestBCGroup, AcceptGroupInvitation)
{
	Authenticate(UserA);
	CreateGroup();

	TestResult tr;
	m_bc->getGroupService()->inviteGroupMember(
		_groupId.c_str(),
		GetUser(UserB)->m_profileId,
		eGroupMember::ADMIN,
		"",
		&tr);
	tr.run(m_bc);

	Logout();
	Authenticate(UserB);

	m_bc->getGroupService()->acceptGroupInvitation(
		_groupId.c_str(),
		&tr);
	tr.run(m_bc);

	Logout();
	DeleteGroupAsUserA();
}

TEST_F(TestBCGroup, AddGroupMember)
{
	Authenticate(UserA);
	CreateGroup();

	TestResult tr;
	m_bc->getGroupService()->addGroupMember(
		_groupId.c_str(),
		GetUser(UserB)->m_profileId,
		eGroupMember::ADMIN,
		"",
		&tr);
	tr.run(m_bc);

	DeleteGroup();
}

TEST_F(TestBCGroup, ApproveGroupJoinRequest)
{
	CreateGroupAsUserA();
	Authenticate(UserB);

	TestResult tr;
	m_bc->getGroupService()->joinGroup(
		_groupId.c_str(),
		&tr);
	tr.run(m_bc);

	Logout();
	Authenticate(UserA);

	m_bc->getGroupService()->approveGroupJoinRequest(
		_groupId.c_str(),
		GetUser(UserB)->m_profileId,
		eGroupMember::MEMBER,
		"",
		&tr);
	tr.run(m_bc);

	DeleteGroup();
}

TEST_F(TestBCGroup, AutoJoinGroup)
{
	CreateGroupAsUserA(true);
	Authenticate(UserB);

	TestResult tr;
	m_bc->getGroupService()->autoJoinGroup(
		_groupType,
		eAutoJoinStrategy::JoinFirstGroup,
		"",
		&tr);
	tr.run(m_bc);

	Logout();
	DeleteGroupAsUserA();
}

TEST_F(TestBCGroup, AutoJoinGroupMulti)
{
	CreateGroupAsUserA(true);
	Authenticate(UserB);

	std::vector<std::string>  groupTypes;
	groupTypes.push_back(_groupType); 

	TestResult tr;
	m_bc->getGroupService()->autoJoinGroupMulti(
		groupTypes,
		eAutoJoinStrategy::JoinFirstGroup,
		"",
		&tr);
	tr.run(m_bc);

	Logout();
	DeleteGroupAsUserA();
}

TEST_F(TestBCGroup, CancelGroupInvitation)
{
	Authenticate(UserA);
	CreateGroup();

	TestResult tr;
	m_bc->getGroupService()->inviteGroupMember(
		_groupId.c_str(),
		GetUser(UserB)->m_profileId,
		eGroupMember::ADMIN,
		"",
		&tr);
	tr.run(m_bc);

	m_bc->getGroupService()->cancelGroupInvitation(
		_groupId.c_str(),
		GetUser(UserB)->m_profileId,
		&tr);
	tr.run(m_bc);

	DeleteGroup();
}

TEST_F(TestBCGroup, CreateGroup)
{
	Authenticate(UserA);
	CreateGroup();
	DeleteGroup();
	Logout();
}

TEST_F(TestBCGroup, CreateGroupWithSummaryData)
{
	Authenticate(UserA);
	CreateGroupWithSummaryData();
	DeleteGroup();
	Logout();
}

TEST_F(TestBCGroup, CreateGroupEntity)
{
	Authenticate(UserA);
	CreateGroup();
	CreateGroupEntity();
	DeleteGroup();
	Logout();
}

TEST_F(TestBCGroup, DeleteGroup)
{
	Authenticate(UserA);
	CreateGroup();
	DeleteGroup();
	Logout();
}


TEST_F(TestBCGroup, DeleteGroupEntity)
{
	Authenticate(UserA);
	CreateGroup();
	std::string entityId = CreateGroupEntity();

	TestResult tr;
	m_bc->getGroupService()->deleteGroupEntity(
		_groupId.c_str(),
		entityId.c_str(),
		1,
		&tr);
	tr.run(m_bc);

	DeleteGroup();
	Logout();
}

TEST_F(TestBCGroup, GetMyGroups)
{
	Authenticate(UserA);
	CreateGroup();

	TestResult tr;
	m_bc->getGroupService()->getMyGroups(
		&tr);
	tr.run(m_bc);

	DeleteGroup();
	Logout();
}

TEST_F(TestBCGroup, IncrementGroupData)
{
	Authenticate(UserA);
	CreateGroup();

	TestResult tr;
	m_bc->getGroupService()->incrementGroupData(
		_groupId.c_str(),
		_testJsonPair,
		&tr);
	tr.run(m_bc);

	DeleteGroup();
	Logout();
}

TEST_F(TestBCGroup, IncrementGroupEntityData)
{
	Authenticate(UserA);
	CreateGroup();
	std::string id = CreateGroupEntity();

	TestResult tr;
	m_bc->getGroupService()->incrementGroupEntityData(
		_groupId.c_str(),
		id.c_str(),
		_testJsonPair,
		&tr);
	tr.run(m_bc);

	DeleteGroup();
	Logout();
}

TEST_F(TestBCGroup, InviteGroupMember)
{
	Authenticate(UserA);
	CreateGroup();

	TestResult tr;
	m_bc->getGroupService()->inviteGroupMember(
		_groupId.c_str(),
		GetUser(UserB)->m_profileId,
		eGroupMember::MEMBER,
		"",
		&tr);
	tr.run(m_bc);

	DeleteGroup();
	Logout();
}

TEST_F(TestBCGroup, JoinGroup)
{
	CreateGroupAsUserA();
	Authenticate(UserB);

	TestResult tr;
	m_bc->getGroupService()->joinGroup(
		_groupId.c_str(),
		&tr);
	tr.run(m_bc);

	Logout();
	DeleteGroupAsUserA();
}

TEST_F(TestBCGroup, LeaveGroup)
{
	Authenticate(UserA);
	CreateGroup();

	TestResult tr;
	m_bc->getGroupService()->leaveGroup(
		_groupId.c_str(),
		&tr);
	tr.run(m_bc);

	m_bc->getGroupService()->readGroup(
		_groupId.c_str(),
		&tr);
	tr.runExpectFail(m_bc, 400, 40345);

	Logout();
}

TEST_F(TestBCGroup, ListGroupsPage)
{
	Authenticate(UserA);

	std::string context = CreateContext(10, 1, "groupType", _groupType);

	TestResult tr;
	m_bc->getGroupService()->listGroupsPage(
		context.c_str(),
		&tr);
	tr.run(m_bc);

	Logout();
}

TEST_F(TestBCGroup, ListGroupsPageByOffset)
{
	Authenticate(UserA);

	std::string context = CreateContext(10, 1, "groupType", _groupType);

	TestResult tr;
	m_bc->getGroupService()->listGroupsPage(
		context.c_str(),
		&tr);
	tr.run(m_bc);

	context = tr.m_response["data"]["context"].asString();

	m_bc->getGroupService()->listGroupsPageByOffset(
		context.c_str(),
		1,
		&tr);
	tr.run(m_bc);

	Logout();
}

TEST_F(TestBCGroup, ListGroupsWithMember)
{
	Authenticate(UserA);
	//CreateGroup();

	TestResult tr;
	m_bc->getGroupService()->listGroupsWithMember(
		GetUser(UserA)->m_profileId,
		&tr);
	tr.run(m_bc);

	Logout();
}

TEST_F(TestBCGroup, ReadGroup)
{
	Authenticate(UserA);
	CreateGroup();

	TestResult tr;
	m_bc->getGroupService()->readGroup(
		_groupId.c_str(),
		&tr);
	tr.run(m_bc);

	DeleteGroup();
	Logout();
}

TEST_F(TestBCGroup, ReadGroupData)
{
	Authenticate(UserA);
	CreateGroup();

	TestResult tr;
	m_bc->getGroupService()->readGroupData(
		_groupId.c_str(),
		&tr);
	tr.run(m_bc);

	DeleteGroup();
	Logout();
}

TEST_F(TestBCGroup, ReadGroupEntitiesPage)
{
	Authenticate(UserA);
	CreateGroup();

	std::string context = CreateContext(10, 1, "groupId", _groupId);

	TestResult tr;
	m_bc->getGroupService()->readGroupEntitiesPage(
		context.c_str(),
		&tr);
	tr.run(m_bc);

	DeleteGroup();
	Logout();
}

TEST_F(TestBCGroup, ReadGroupEntitiesPageByOffset)
{
	Authenticate(UserA);
	CreateGroup();

	std::string context = CreateContext(10, 1, "groupId", _groupId);

	TestResult tr;
	m_bc->getGroupService()->readGroupEntitiesPage(
		context.c_str(),
		&tr);
	tr.run(m_bc);

	context = tr.m_response["data"]["context"].asString();

	m_bc->getGroupService()->readGroupEntitiesPageByOffset(
		context.c_str(),
		1,
		&tr);
	tr.run(m_bc);

	DeleteGroup();
	Logout();
}

TEST_F(TestBCGroup, ReadGroupEntity)
{
	Authenticate(UserA);
	CreateGroup();
	std::string id = CreateGroupEntity();

	TestResult tr;
	m_bc->getGroupService()->readGroupEntity(
		_groupId.c_str(),
		id.c_str(),
		&tr);
	tr.run(m_bc);

	DeleteGroup();
	Logout();
}

TEST_F(TestBCGroup, ReadGroupMembers)
{
	Authenticate(UserA);
	CreateGroup();

	TestResult tr;
	m_bc->getGroupService()->readGroupMembers(
		_groupId.c_str(),
		&tr);
	tr.run(m_bc);

	DeleteGroup();
	Logout();
}

TEST_F(TestBCGroup, RejectGroupInvitation)
{
	Authenticate(UserA);
	CreateGroup();

	TestResult tr;
	m_bc->getGroupService()->inviteGroupMember(
		_groupId.c_str(),
		GetUser(UserB)->m_profileId,
		eGroupMember::ADMIN,
		"",
		&tr);
	tr.run(m_bc);

	Logout();
	Authenticate(UserB);

	m_bc->getGroupService()->rejectGroupInvitation(
		_groupId.c_str(),
		&tr);
	tr.run(m_bc);

	Logout();
	DeleteGroupAsUserA();
}

TEST_F(TestBCGroup, RejectGroupJoinRequest)
{
	CreateGroupAsUserA();
	Authenticate(UserB);

	TestResult tr;
	m_bc->getGroupService()->joinGroup(
		_groupId.c_str(),
		&tr);
	tr.run(m_bc);

	Logout();
	Authenticate(UserA);

	m_bc->getGroupService()->rejectGroupJoinRequest(
		_groupId.c_str(),
		GetUser(UserB)->m_profileId,
		&tr);
	tr.run(m_bc);

	DeleteGroup();
}

TEST_F(TestBCGroup, RemoveGroupMember)
{
	CreateGroupAsUserA(true);
	Authenticate(UserB);

	TestResult tr;
	m_bc->getGroupService()->joinGroup(
		_groupId.c_str(),
		&tr);
	tr.run(m_bc);

	Logout();
	Authenticate(UserA);

	m_bc->getGroupService()->removeGroupMember(
		_groupId.c_str(),
		GetUser(UserB)->m_profileId,
		&tr);
	tr.run(m_bc);

	DeleteGroup();
}

TEST_F(TestBCGroup, UpdateGroupData)
{
	Authenticate(UserA);
	CreateGroup();

	TestResult tr;
	m_bc->getGroupService()->updateGroupData(
		_groupId.c_str(),
		1,
		_testJsonPair,
		&tr);
	tr.run(m_bc);

	DeleteGroup();
	Logout();
}

TEST_F(TestBCGroup, UpdateGroupEntity)
{
	Authenticate(UserA);
	CreateGroup();
	std::string id = CreateGroupEntity();

	TestResult tr;
	m_bc->getGroupService()->updateGroupEntityData(
		_groupId.c_str(),
		id.c_str(),
		1,
		_testJsonPair,
		&tr);
	tr.run(m_bc);

	DeleteGroup();
	Logout();
}

TEST_F(TestBCGroup, UpdateGroupMember)
{
	Authenticate(UserA);
	CreateGroup();

	TestResult tr;
	m_bc->getGroupService()->updateGroupMember(
		_groupId.c_str(),
		GetUser(UserA)->m_profileId,
		eGroupMember::UNKNOWN,
		"",
		&tr);
	tr.run(m_bc);

	DeleteGroup();
	Logout();
}

TEST_F(TestBCGroup, UpdateGroupName)
{
	Authenticate(UserA);
	CreateGroup();

	TestResult tr;
	m_bc->getGroupService()->updateGroupName(
		_groupId.c_str(),
		"testName",
		&tr);
	tr.run(m_bc);

	DeleteGroup();
	Logout();
}

TEST_F(TestBCGroup, SetGroupOpen)
{
	Authenticate(UserA);
	CreateGroup();

	TestResult tr;
	m_bc->getGroupService()->setGroupOpen(
		_groupId.c_str(),
		true,
		&tr);
	tr.run(m_bc);

	DeleteGroup();
	Logout();
}

TEST_F(TestBCGroup, UpdateGroupSummaryData)
{
	Authenticate(UserA);
	CreateGroup();

	TestResult tr;
	m_bc->getGroupService()->updateGroupSummaryData(
		_groupId.c_str(),
		1,
		_testJsonPair,
		&tr);
	tr.run(m_bc);

	DeleteGroup();
	Logout();
}

TEST_F(TestBCGroup, GetRandomGroupsMatching)
{
	Authenticate(UserA);
	CreateGroup();

	TestResult tr;
	m_bc->getGroupService()->getRandomGroupsMatching(
	"{\"groupType\": \"BLUE\"}",
	2,
	&tr);
	tr.run(m_bc);

	DeleteGroup();
	Logout();
}

/*
 * Helpers
 */

void TestBCGroup::CreateGroupAsUserA(bool isOpen)
{
	Authenticate(UserA);
	CreateGroup(isOpen);
	Logout();
}

void TestBCGroup::DeleteGroupAsUserA()
{
	Authenticate(UserA);
	DeleteGroup();
	Logout();
}

void TestBCGroup::Authenticate(Users user)
{
	TestResult tr;
	m_bc->getAuthenticationService()->authenticateUniversal(
		GetUser(user)->m_id,
		GetUser(user)->m_password,
		true,
		&tr);
	tr.run(m_bc);
}

void TestBCGroup::CreateGroup(bool isOpen)
{
	TestResult tr;
	m_bc->getGroupService()->createGroup(
		"testGroup",
		_groupType,
		isOpen,
		_testAcl,
		_testJsonPair,
		_testJsonPair,
		_testJsonPair,
		&tr);
	tr.run(m_bc);

	_groupId = tr.m_response["data"]["groupId"].asString();
}

void TestBCGroup::CreateGroupWithSummaryData(bool isOpen)
{
	TestResult tr;
	m_bc->getGroupService()->createGroupWithSummaryData(
		"testGroup",
		_groupType,
		isOpen,
		_testAcl,
		_testJsonPair,
		_testJsonPair,
		_testJsonPair,
		_testJsonPair,
		&tr);
	tr.run(m_bc);

	_groupId = tr.m_response["data"]["groupId"].asString();
}

std::string TestBCGroup::CreateGroupEntity()
{
	TestResult tr;
	Json::Value entityData;
	entityData["address"] = "1309 Carling Ave";
	Json::Value entityAcl;
	entityAcl["other"] = 2;

	std::string entityId;

	Json::FastWriter fw;
	m_bc->getGroupService()->createGroupEntity(_groupId.c_str(), _entityType, false, fw.write(entityAcl), fw.write(entityData), &tr);
	if (tr.run(m_bc))
	{
		return tr.m_response["data"]["entityId"].asString();
	}
	return "";
}

void TestBCGroup::DeleteGroup()
{
	TestResult tr;
	m_bc->getGroupService()->deleteGroup(
		_groupId.c_str(),
		-1,
		&tr);
	tr.run(m_bc);
}

std::string TestBCGroup::CreateContext(int numItemsPerPage, int startPage, std::string searchKey, std::string searchValue)
{
	Json::Value context;
	Json::FastWriter fw;

	context["pagination"]["rowsPerPage"] = numItemsPerPage;
	context["pagination"]["pageNumber"] = startPage;
	context["searchCriteria"][searchKey] = searchValue;

	return fw.write(context);
}

