#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCGlobalEntity.h"

using namespace BrainCloud;

TestBCGlobalEntity::TestBCGlobalEntity()
{
    m_entityType = "testGlobalEntity";
    m_indexedId = "testIndex";

    Json::FastWriter fw;
    Json::Value acl;
    acl["other"] = 2;
    m_entityAclJson = fw.write(acl);

    Json::Value entityData;
    entityData["testKey"] = "testValue";
    m_entityDataJson = fw.write(entityData);
}


TEST_F(TestBCGlobalEntity, CreateGlobalEntity)
{
    CreateDefaultGlobalEntity();
}

TEST_F(TestBCGlobalEntity, CreateGlobalEntityWithIndexId)
{
    CreateDefaultGlobalEntity(m_indexedId);
}

TEST_F(TestBCGlobalEntity, DeleteGlobalEntity)
{
    TestResult tr;
    CreateDefaultGlobalEntity();
    m_bc->getGlobalEntityService()->deleteEntity(m_entityId, 1, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGlobalEntity, GetList)
{
    CreateDefaultGlobalEntity();
    TestResult tr;

    Json::FastWriter fw;
    Json::Value searchType;
    searchType["entityType"] = m_entityType;
    std::string searchTypeStr = fw.write(searchType);

    m_bc->getGlobalEntityService()->getList(searchTypeStr, "", 100, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGlobalEntity, GetListByIndexedId)
{
    CreateDefaultGlobalEntity(m_indexedId);
    TestResult tr;
    m_bc->getGlobalEntityService()->getListByIndexedId(m_indexedId, 20, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGlobalEntity, GetListCount)
{
    CreateDefaultGlobalEntity();
    TestResult tr;

    Json::FastWriter fw;
    Json::Value searchType;
    searchType["entityType"] = m_entityType;
    std::string searchTypeStr = fw.write(searchType);

    m_bc->getGlobalEntityService()->getListCount(searchTypeStr, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGlobalEntity, ReadEntity)
{
    CreateDefaultGlobalEntity(m_indexedId);

    TestResult tr;
    m_bc->getGlobalEntityService()->readEntity(m_entityId, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGlobalEntity, UpdateEntity)
{
    CreateDefaultGlobalEntity(m_indexedId);

    TestResult tr;
    m_bc->getGlobalEntityService()->updateEntity(m_entityId, 1, m_entityDataJson, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGlobalEntity, UpdateEntityAcl)
{
    CreateDefaultGlobalEntity(m_indexedId);

    TestResult tr;
    m_bc->getGlobalEntityService()->updateEntityAcl(m_entityId, 1, m_entityAclJson, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGlobalEntity, UpdateEntityTimeToLive)
{
    CreateDefaultGlobalEntity(m_indexedId);

    TestResult tr;
    m_bc->getGlobalEntityService()->updateEntityTimeToLive(m_entityId, 1, 2048, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGlobalEntity, GetPage)
{
    GenerateDefaultEntites(25);
    Json::Value context;
    Json::FastWriter fw;

    context["pagination"]["rowsPerPage"] = 15;
    context["pagination"]["pageNumber"] = 1;
    context["searchCriteria"]["entityType"] = m_entityType;

    TestResult tr;
    m_bc->getGlobalEntityService()->getPage(fw.write(context).c_str(), &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGlobalEntity, GetPageOffset)
{
    GenerateDefaultEntites(25);

    Json::Value context;
    Json::FastWriter fw;

    context["pagination"]["rowsPerPage"] = 15;
    context["pagination"]["pageNumber"] = 1;
    context["searchCriteria"]["entityType"] = m_entityType;

    TestResult tr;
    m_bc->getGlobalEntityService()->getPage(fw.write(context).c_str(), &tr);
    tr.run(m_bc);

    std::string context_str = tr.m_response["data"]["context"].asString();

    tr.reset();
    m_bc->getGlobalEntityService()->getPageOffset(context_str.c_str(), 1, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGlobalEntity, IncremenGlobalEntityData)
{
    TestResult tr;
    Json::Value entityData;
    entityData["test"] = 1233;

    std::string entityId;

    Json::FastWriter fw;
    m_bc->getGlobalEntityService()->createEntity(m_entityType, -1, m_entityAclJson, fw.write(entityData), &tr);
    if (tr.run(m_bc)) entityId = tr.m_response["data"]["entityId"].asString();

    m_bc->getGlobalEntityService()->incrementGlobalEntityData(entityId.c_str(), fw.write(entityData), &tr);
    tr.run(m_bc);

    m_bc->getGlobalEntityService()->deleteEntity(entityId, -1, &tr);
    tr.run(m_bc);
}


TEST_F(TestBCGlobalEntity, GetRandomEntitiesMatching)
{
    CreateDefaultGlobalEntity();
    TestResult tr;

    Json::FastWriter fw;
    Json::Value searchType;
    searchType["entityType"] = m_entityType;
    std::string searchTypeStr = fw.write(searchType);

    m_bc->getGlobalEntityService()->getRandomEntitiesMatching(searchTypeStr, 100, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGlobalEntity, UpdateEntityIndexedId)
{
	CreateDefaultGlobalEntity(m_indexedId);

	TestResult tr;
	m_bc->getGlobalEntityService()->updateEntityIndexedId(m_entityId.c_str(), -1, m_indexedId.c_str(), &tr);
	tr.run(m_bc);
}

TEST_F(TestBCGlobalEntity, UpdateEntityOwnerAndAcl)
{
	CreateDefaultGlobalEntity(m_indexedId);

	TestResult tr;
	m_bc->getGlobalEntityService()->updateEntityOwnerAndAcl(m_entityId.c_str(), -1, GetUser(UserB)->m_profileId, m_entityAclJson, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCGlobalEntity, MakeSystemEntity)
{
	CreateDefaultGlobalEntity(m_indexedId);

	TestResult tr;
	m_bc->getGlobalEntityService()->makeSystemEntity(m_entityId.c_str(), -1, m_entityAclJson, &tr);
	tr.run(m_bc);
}

void TestBCGlobalEntity::CreateDefaultGlobalEntity(std::string indexedId)
{
    TestResult tr;

    if (indexedId.length() > 0)
        m_bc->getGlobalEntityService()->createEntity(m_entityType, 3434343, m_entityAclJson, m_entityDataJson, &tr);
    else
        m_bc->getGlobalEntityService()->createEntityWithIndexedId(m_entityType, m_indexedId, 3434343, m_entityAclJson, m_entityDataJson, &tr);

    tr.run(m_bc);

    m_entityId = tr.m_response["data"]["entityId"].asString();
}

void TestBCGlobalEntity::GenerateDefaultEntites(int numToGenerate)
{
    TestResult tr;

    Json::FastWriter fw;
    Json::Value searchType;
    searchType["entityType"] = m_entityType;
    std::string searchTypeStr = fw.write(searchType);

    m_bc->getGlobalEntityService()->getListCount(searchTypeStr, &tr);
    tr.run(m_bc);

    numToGenerate -= tr.m_response["data"]["entityListCount"].asInt();

    if (numToGenerate <= 0) return;

    for (int i = 0; i < numToGenerate; i++) {
        CreateDefaultGlobalEntity("");
    }
}



