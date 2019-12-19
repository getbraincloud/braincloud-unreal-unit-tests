#include <stdlib.h>
#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "braincloud/BrainCloudEntity.h"
#include "TestResult.h"
#include "json/json.h"
#include "TestBCEntity.h"
#include "braincloud/reason_codes.h"
#include "braincloud/http_codes.h"


using namespace BrainCloud;


TEST_F(TestBCEntity, Create)
{
	TestResult tr;

	Json::Value entityData;
	entityData["address"] = "1309 Carling Ave";

	Json::FastWriter fw;
	m_bc->getEntityService()->createEntity(m_entityType, fw.write(entityData), "", &tr);
	if (tr.run(m_bc))
	{
		m_entityId = tr.m_response["data"]["entityId"].asString();
		ASSERT_NE("", m_entityId);
	}

	TestBCEntity::DeleteEntity();
}


TEST_F(TestBCEntity, Update)
{
	TestResult tr;
	Json::Value entityData;
	Json::FastWriter fw;

	CreateDefaultEntity();

	entityData["address"] = "1309a Carling Ave, Ottawa ON";
	m_bc->getEntityService()->updateEntity(m_entityId.c_str(), m_entityType, fw.write(entityData), "", -1, &tr);
	tr.run(m_bc);

	TestBCEntity::DeleteEntity();
}

TEST_F(TestBCEntity, BadUpdate)
{
	TestResult tr;
	Json::Value entityData;
	entityData["address"] = "1309 Carling Ave";
	std::string badEntityId = "wakawaka";

	Json::FastWriter fw;
	m_bc->getEntityService()->updateEntity(badEntityId.c_str(), m_entityType, fw.write(entityData), "", -1, &tr);
	// TODO : put in the correct error code constant
	tr.runExpectFail(m_bc, HTTP_NOT_FOUND, 40332);
}

TEST_F(TestBCEntity, Delete)
{
	TestResult tr;
	TestBCEntity::CreateDefaultEntity();
	m_bc->getEntityService()->deleteEntity(m_entityId.c_str(), -1, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCEntity, GetEntity)
{
	TestResult tr;
	TestBCEntity::CreateDefaultEntity();
	m_bc->getEntityService()->getEntity(m_entityId.c_str(), &tr);
	tr.run(m_bc);
	TestBCEntity::DeleteEntity();
}

TEST_F(TestBCEntity, GetSingleton)
{
	TestResult tr;
	TestBCEntity::CreateDefaultEntity();
	m_bc->getEntityService()->getSingleton(m_entityType, &tr);
	tr.run(m_bc);
	TestBCEntity::DeleteEntity();
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
TEST_F(TestBCEntity, GetSharedEntityForPlayerId)
{
	TestResult tr;
	CreateDefaultEntity();
	m_bc->getEntityService()->getSharedEntityForPlayerId(GetUser(UserA)->m_profileId, m_entityId.c_str(), &tr);
	tr.run(m_bc);
	DeleteEntity();
}
#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
TEST_F(TestBCEntity, GetSharedEntitiesForPlayerId)
{
	TestResult tr;
	CreateDefaultEntity();
	m_bc->getEntityService()->getSharedEntitiesForPlayerId(GetUser(UserA)->m_profileId, &tr);
	tr.run(m_bc);
	DeleteEntity();
}
#pragma clang diagnostic pop

TEST_F(TestBCEntity, GetEntitesByType)
{
	TestResult tr;
	TestBCEntity::CreateDefaultEntity();
	m_bc->getEntityService()->getEntitiesByType(m_entityType, &tr);
	tr.run(m_bc);
	TestBCEntity::DeleteEntity();
}

TEST_F(TestBCEntity, DeleteSingleton)
{
	TestResult tr;
	TestBCEntity::CreateDefaultEntity();
	m_bc->getEntityService()->deleteSingleton(m_entityType, -1, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCEntity, UpdateSharedEntity)
{
	TestResult tr;
	Json::Value entityData;
	Json::FastWriter fw;

	CreateDefaultEntity();

	entityData["address"] = "1309a Carling Ave, Ottawa ON";
	m_bc->getEntityService()->updateSharedEntity(m_entityId.c_str(), GetUser(UserA)->m_profileId, m_entityType, fw.write(entityData), -1, &tr);
	tr.run(m_bc);

	DeleteEntity();
}

TEST_F(TestBCEntity, UpdateSingleton)
{
	TestResult tr;
	Json::Value entityData;
	Json::FastWriter fw;

	entityData["address"] = "1309a Carling Ave, Ottawa ON";
	m_bc->getEntityService()->updateSingleton(m_entityType, fw.write(entityData), "", -1, &tr);
	if (tr.run(m_bc))
	{
		m_entityId = tr.m_response["data"]["entityId"].asString();
		ASSERT_NE("", m_entityId);
	}

	DeleteEntity(m_entityId);
}

TEST_F(TestBCEntity, GetList)
{
	GenerateDefaultEntites(2);
	TestResult tr;

	Json::FastWriter fw;
	Json::Value whereJson;
	whereJson["entityType"] = m_entityType;

	m_bc->getEntityService()->getList(fw.write(whereJson), "", 100, &tr);
	tr.run(m_bc);

	DeleteAllDefaultEntities();
}

TEST_F(TestBCEntity, GetSharedEntitiesListForPlayerId)
{
	GenerateDefaultEntites(2);
	TestResult tr;

	Json::FastWriter fw;
	Json::Value whereJson;
	whereJson["entityType"] = m_entityType;

	m_bc->getEntityService()->getSharedEntitiesListForPlayerId(
		GetUser(UserA)->m_profileId,
		fw.write(whereJson), "", 100, &tr);
	tr.run(m_bc);

	DeleteAllDefaultEntities();
}

TEST_F(TestBCEntity, GetListCount)
{
	GenerateDefaultEntites(2);
	TestResult tr;

	Json::FastWriter fw;
	Json::Value searchType;
	searchType["entityType"] = m_entityType;
	std::string searchTypeStr = fw.write(searchType);

	m_bc->getEntityService()->getListCount(searchTypeStr, &tr);
	tr.run(m_bc);

	DeleteAllDefaultEntities();
}

TEST_F(TestBCEntity, GetPage)
{
	GenerateDefaultEntites(20);

	Json::Value context;
	Json::FastWriter fw;

	context["pagination"]["rowsPerPage"] = 12;
	context["pagination"]["pageNumber"] = 1;
	context["searchCriteria"]["entityType"] = m_entityType;

	TestResult tr;
	m_bc->getEntityService()->getPage(fw.write(context).c_str(), &tr);
	tr.run(m_bc);

	DeleteAllDefaultEntities();
}

TEST_F(TestBCEntity, GetPageOffset)
{
	GenerateDefaultEntites(20);

	Json::Value context;
	Json::FastWriter fw;

	context["pagination"]["rowsPerPage"] = 12;
	context["pagination"]["pageNumber"] = 1;
	context["searchCriteria"]["entityType"] = m_entityType;

	TestResult tr;
	m_bc->getEntityService()->getPage(fw.write(context).c_str(), &tr);
	tr.run(m_bc);

	std::string context_str = tr.m_response["data"]["context"].asString();

	tr.reset();
	m_bc->getEntityService()->getPageOffset(context_str.c_str(), 1, &tr);
	tr.run(m_bc);

	DeleteAllDefaultEntities();
}

TEST_F(TestBCEntity, IncrementUserEntityData)
{
	TestResult tr;
	Json::Value entityData;
	entityData["test"] = 1233;

	std::string entityId;

	Json::FastWriter fw;
	m_bc->getEntityService()->createEntity(m_entityType, fw.write(entityData), "", &tr);
	if (tr.run(m_bc)) entityId = tr.m_response["data"]["entityId"].asString();

	m_bc->getEntityService()->incrementUserEntityData(entityId.c_str(), fw.write(entityData), &tr);
	tr.run(m_bc);

	DeleteEntity(entityId);
}

TEST_F(TestBCEntity, IncrementSharedUserEntityData)
{
	TestResult tr;
	Json::Value entityData;
	entityData["test"] = 1233;

	std::string entityId;

	Json::FastWriter fw;
	m_bc->getEntityService()->createEntity(m_entityType, fw.write(entityData), "", &tr);
	if (tr.run(m_bc)) entityId = tr.m_response["data"]["entityId"].asString();

	m_bc->getEntityService()->incrementSharedUserEntityData(entityId.c_str(), GetUser(UserA)->m_profileId, fw.write(entityData), &tr);
	tr.run(m_bc);

	DeleteEntity(entityId);
}

void TestBCEntity::CreateDefaultEntity()
{
	TestResult tr;
	Json::Value entityData;
	entityData["address"] = "1309 Carling Ave";
	Json::Value entityAcl;
	entityAcl["other"] = 2;


	std::string entityId;

	Json::FastWriter fw;
	m_bc->getEntityService()->createEntity(m_entityType, fw.write(entityData), fw.write(entityAcl), &tr);
	if (tr.run(m_bc))
	{
		m_entityId = tr.m_response["data"]["entityId"].asString();
	}
}

void TestBCEntity::DeleteEntity(std::string entityId)
{
	if (entityId.length() <= 0) entityId = m_entityId;
	TestResult tr;
	m_bc->getEntityService()->deleteEntity(entityId.c_str(), -1, &tr);
	tr.run(m_bc);
}

void TestBCEntity::GenerateDefaultEntites(int numToGenerate)
{
	TestResult tr;

	Json::FastWriter fw;
	Json::Value searchType;
	searchType["entityType"] = m_entityType;
	std::string searchTypeStr = fw.write(searchType);

	for (int i = 0; i < numToGenerate; i++) {
		CreateDefaultEntity();
	}
}

void TestBCEntity::DeleteAllDefaultEntities()
{
	TestResult tr;
	m_bc->getEntityService()->getEntitiesByType(m_entityType, &tr);
	if (tr.run(m_bc))
	{
		Json::Value entityArray = tr.m_response["data"]["entities"];

		/* for some reason, marmalade goes past entityArray.end() so we do this via indices
		Json::Value::iterator it;
		for (it = entityArray.begin(); it !=entityArray.end(); ++it)
		{
		Json::Value key = it.key(); // why get this?
		Json::Value value = (*it);

		DeleteEntity(value["entityId"].asString());
		}
		*/

		for (int i = 0, isize = entityArray.size(); i < isize; ++i)
		{
			Json::Value value = entityArray[i];
			DeleteEntity(value["entityId"].asString());
		}
		m_entityId = tr.m_response["data"]["entityId"].asString();
	}
}


/*
 TEST_F(TestBCTime, LargePacket)
 {
 TestResult tr;

 std::vector<int> hugeTimeout;
 hugeTimeout.push_back(180);
 m_bc->setPacketTimeouts(hugeTimeout);

 Json::Value entityData;
 int mbs = 1;
 for (int i = 0; i < mbs; ++i)
 {
 std::ostringstream oss;
 oss << i;
 std::string key = oss.str();
 oss.clear();
 for (int j = 0; j < (1024/8)*1024; ++j)
 {
 oss << "01234567";
 }
 std::string data = oss.str();
 entityData[key] = data;
 }
 Json::FastWriter fw;
 m_bc->getEntityService()->createEntity("largepacket", fw.write(entityData), "", &tr);
 if (tr.run(m_bc))
 {
 // m_entityId = tr.m_response["data"]["entityId"].asString();
 // ASSERT_NE("", m_entityId);
 }

 m_bc->setPacketTimeoutsToDefault();
 }
 */







