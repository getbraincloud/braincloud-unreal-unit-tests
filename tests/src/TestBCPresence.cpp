#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "braincloud/http_codes.h"
#include "braincloud/reason_codes.h"
#include "TestResult.h"
#include "TestBCPresence.h"

using namespace BrainCloud;

// Lot of expect fail here. This is ok, but we make sure the failed reason 
// is not about a bad or missing argument. We validate that the API is
// written correctly, not that the output from BC is correct. This is
// verified more in depth by use case and JS unit tests.

TEST_F(TestBCPresence, ForcePush)
{
	TestResult tr;
	m_bc->getPresenceService()->forcePush(&tr);
	tr.run(m_bc);
}

TEST_F(TestBCPresence, GetPresenceOfFriends)
{
	TestResult tr;

	m_bc->getPresenceService()->getPresenceOfFriends("brainCloud", true, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCPresence, GetPresenceOfGroup)
{
	TestResult tr;

	m_bc->getPresenceService()->getPresenceOfGroup("invalid_group_id", true, &tr);
	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, INVALID_GROUP_ID);
}

TEST_F(TestBCPresence, GetPresenceOfUsers)
{
	TestResult tr;

	std::vector<std::string> profileIds = {"invalid_profile_id"};
	m_bc->getPresenceService()->getPresenceOfUsers(profileIds, true, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCPresence, RegisterListenersForFriends)
{
	TestResult tr;

	m_bc->getPresenceService()->registerListenersForFriends("brainCloud", true, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCPresence, RegisterListenersForGroup)
{
	TestResult tr;

	m_bc->getPresenceService()->registerListenersForGroup("invalid_group_id", true, &tr);
	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, INVALID_GROUP_ID);
}

TEST_F(TestBCPresence, RegisterListenersForProfiles)
{
	TestResult tr;

	std::vector<std::string> profileIds = {"invalid_profile_id"};
	m_bc->getPresenceService()->registerListenersForProfiles(profileIds, true, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCPresence, SetVisibility)
{
	TestResult tr;

	m_bc->getPresenceService()->setVisibility(true, &tr);
	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, PRESENCE_NOT_INITIALIZED);
}

TEST_F(TestBCPresence, StopListening)
{
	TestResult tr;

	m_bc->getPresenceService()->stopListening(&tr);
	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, PRESENCE_NOT_INITIALIZED);
}

TEST_F(TestBCPresence, UpdateActivity)
{
	TestResult tr;

	m_bc->getPresenceService()->updateActivity("{\"status\":\"Work from home\"}", &tr);
	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, PRESENCE_NOT_INITIALIZED);
}
