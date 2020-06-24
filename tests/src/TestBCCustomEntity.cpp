#include <stdlib.h>
#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "braincloud/BrainCloudEntity.h"
#include "TestResult.h"
#include "json/json.h"
#include "TestBCCustomEntity.h"
#include "braincloud/reason_codes.h"
#include "braincloud/http_codes.h"


using namespace BrainCloud;


TEST_F(TestBCCustomEntity, CreateCustomEntity)
{
	TestResult tr;

	Json::FastWriter fw;
	m_bc->getCustomEntityService()->createEntity(m_entityType, "{\"test\": \"Testing\"}", "{\"test\": \"Testing\"}", NULL, true, &tr);
	if (tr.run(m_bc))
	{
		m_entityId = tr.m_response["data"]["entityId"].asString();
		ASSERT_NE("", m_entityId);
	}
}

TEST_F(TestBCCustomEntity, GetEntityPage)
{
	TestResult tr;
    Json::Value context;
	Json::FastWriter fw;

	context["pagination"]["rowsPerPage"] = 15;
    context["pagination"]["pageNumber"] = 1;

	m_bc->getCustomEntityService()->getEntityPage(m_entityType, fw.write(context).c_str(), &tr);
	tr.run(m_bc);
}


TEST_F(TestBCCustomEntity, GetEntityPageOffset)
{
	TestResult tr;
	std::string context = "eyJzZWFyY2hDcml0ZXJpYSI6eyJkYXRhLnBvc2l0aW9uIjoiZGVmZW5zZSIsIiRvciI6W3sib3duZXJJZCI6ImIyZGRjNTBjLWNkNjUtNDk0OC04NDI4LThlNjEwMmU4YmNhZSJ9LHsiYWNsLm90aGVyIjp7IiRuZSI6MH19XX0sInNvcnRDcml0ZXJpYSI6eyJjcmVhdGVkQXQiOjF9LCJwYWdpbmF0aW9uIjp7InJvd3NQZXJQYWdlIjoyMCwicGFnZU51bWJlciI6MSwiZG9Db3VudCI6ZmFsc2V9LCJvcHRpb25zIjpudWxsfQ";

	Json::FastWriter fw;
	m_bc->getCustomEntityService()->getEntityPageOffset(m_entityType, context, 1, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCCustomEntity, ReadEntity)
{
	TestResult tr;
	std::string id;

	Json::FastWriter fw;
	m_bc->getCustomEntityService()->createEntity(m_entityType, "{\"test\": \"Testing\"}", "{\"test\": \"Testing\"}", NULL, true, &tr);
	if (tr.run(m_bc))
	{
		id = tr.m_response["data"]["entityId"].asString();
		ASSERT_NE("", id);
	}
	TestResult tr2;
	m_bc->getCustomEntityService()->readEntity(m_entityType, id.c_str(), &tr2);
	tr2.run(m_bc);
}

TEST_F(TestBCCustomEntity, ReadCustomEntity)
{
	TestResult tr;
	std::string id;

	Json::FastWriter fw;
	m_bc->getCustomEntityService()->createEntity(m_entityType, "{\"test\": \"Testing\"}", "{\"test\": \"Testing\"}", NULL, true, &tr);
	if (tr.run(m_bc))
	{
		id = tr.m_response["data"]["entityId"].asString();
		ASSERT_NE("", id);
	}
	TestResult tr2;
	m_bc->getCustomEntityService()->readEntity(m_entityType, id.c_str(), &tr2);
	tr2.run(m_bc);
}

TEST_F(TestBCCustomEntity, UpdateCustomEntity)
{
	TestResult tr;
	std::string id;

	Json::FastWriter fw;
	m_bc->getCustomEntityService()->createEntity(m_entityType, "{\"test\": \"Testing\"}", "{\"test\": \"Testing\"}", NULL, true, &tr);
	if (tr.run(m_bc))
	{
		id = tr.m_response["data"]["entityId"].asString();
		ASSERT_NE("", id);
	}
	TestResult tr2;
	m_bc->getCustomEntityService()->updateEntity(m_entityType, id.c_str(), 1, "{\"taergaregest\": \"rsgsdrsrgerg\"}", "{\"teaergaegst\": \"Teergergergergasersting\"}", NULL, &tr2);
	tr2.run(m_bc);
}

TEST_F(TestBCCustomEntity, UpdateCustomEntityFields)
{
	//TODO
	// TestResult tr;
	// std::string id;

	// Json::FastWriter fw;
	// m_bc->getCustomEntityService()->createEntity(m_entityType, "{\"test\": \"Testing\"}", "{\"test\": \"Testing\"}", NULL, true, &tr);
	// if (tr.run(m_bc))
	// {
	// 	id = tr.m_response["data"]["entityId"].asString();
	// 	ASSERT_NE("", id);
	// }
	// TestResult tr2;
	// m_bc->getCustomEntityService()->updateEntityFields(m_entityType, id.c_str(), 1, "{\"data.goals\": \"3\", \"data.assists\": \"5\"}", &tr2);
	// tr2.run(m_bc);
}

TEST_F(TestBCCustomEntity, GetCount)
{
	TestResult tr;
	std::string id;

	Json::FastWriter fw;
	m_bc->getCustomEntityService()->createEntity(m_entityType, "{\"test\": \"Testing\"}", "{\"test\": \"Testing\"}", NULL, true, &tr);
	if (tr.run(m_bc))
	{
		id = tr.m_response["data"]["entityId"].asString();
		ASSERT_NE("", id);
	}
	TestResult tr2;
	m_bc->getCustomEntityService()->getCount(m_entityType, "{\"data.position\": \"defense\"}", &tr2);
	tr2.run(m_bc);
}

TEST_F(TestBCCustomEntity, DeleteEntity)
{
	TestResult tr;
	std::string id;

	Json::FastWriter fw;
	m_bc->getCustomEntityService()->createEntity(m_entityType, "{\"test\": \"Testing\"}", "{\"test\": \"Testing\"}", NULL, true, &tr);
	if (tr.run(m_bc))
	{
		id = tr.m_response["data"]["entityId"].asString();
		ASSERT_NE("", id);
	}
	TestResult tr2;
	m_bc->getCustomEntityService()->deleteEntity(m_entityType, id.c_str(), "{\"test\": \"Testing\"}", 1, &tr2);
	tr2.run(m_bc);
}


TEST_F(TestBCCustomEntity, DeleteEntities)
{
	TestResult tr;
	std::string id;

	TestResult tr2;
	m_bc->getCustomEntityService()->deleteEntities(m_entityType, "{\"entityId\": \"Testing\"}", &tr2);
	tr2.run(m_bc);
}

TEST_F(TestBCCustomEntity, DeleteSingleton)
{
	TestResult tr;
	std::string id;

	TestResult tr2;
	m_bc->getCustomEntityService()->deleteSingleton(m_entityType, -1, &tr2);
	tr2.run(m_bc);
}

TEST_F(TestBCCustomEntity, UpdateSingleton)
{
	TestResult tr;
	std::string id;

	TestResult tr2;
	m_bc->getCustomEntityService()->updateSingleton(m_entityType, -1, "{\"entityId\": \"Testing\"}", "{\"entityId\": \"Testing\"}", NULL, &tr2);
	//(m_entityType, "{\"test\": \"Testing\"}", "{\"test\": \"Testing\"}", NULL, true, &tr);
	tr2.run(m_bc);
}

TEST_F(TestBCCustomEntity, UpdateSingletonFields)
{
	TestResult tr;
	std::string id;

	TestResult tr2;
	m_bc->getCustomEntityService()->updateSingletonFields(m_entityType, -1, "{\"entityId\": \"Testing\"}", &tr2);
	tr2.run(m_bc);
}

TEST_F(TestBCCustomEntity, ReadSingleton)
{
	TestResult tr;
	std::string id;

	TestResult tr2;
	m_bc->getCustomEntityService()->readSingleton(m_entityType,  &tr2);
	tr2.run(m_bc);
}

TEST_F(TestBCCustomEntity, IncrementData)
{
	m_bc->getAuthenticationService()->authenticateAnonymous(true);
	TestResult tr;
	const char *id;
	m_bc->getCustomEntityService()->createEntity(m_entityType, "{\"test\": \"Testing\"}", "{\"test\": \"Testing\"}", NULL, true, &tr);
	if (tr.run(m_bc))
	{
		id = tr.m_response["data"]["entityId"].asCString();
		ASSERT_NE("", id);
	}
	TestResult tr2;
	m_bc->getCustomEntityService()->incrementData(m_entityType, id,  "{\"goals\":1, \"assists\":4}",   &tr2);
	tr2.run(m_bc);

	TestResult tr3;
	m_bc->getCustomEntityService()->deleteEntity(m_entityType, id, "{\"test\": \"Testing\"}", -1, &tr3);
	tr3.run(m_bc);
}
