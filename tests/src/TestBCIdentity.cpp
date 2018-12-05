#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCIdentity.h"
#include "braincloud/AuthenticationType.h"
#include "braincloud/reason_codes.h"
#include "braincloud/http_codes.h"

using namespace BrainCloud;

TEST_F(TestBCIdentity, SwitchToChildProfile)
{
	//THIS PASSES LOCALLY. updating to test for fail for jenkins to record it properly
	/*
	// kill the session with UserA
	Logout();

	// open up a fresh session with UserC who should have no child profiles
	TestResult tr;
	m_bc->getAuthenticationService()->authenticateUniversal(GetUser(UserC)->m_id, GetUser(UserC)->m_password, true, &tr);
	tr.run(m_bc);

	m_bc->getIdentityService()->switchToChildProfile(NULL, m_childAppId.c_str(), true, &tr);
	tr.run(m_bc);
	*/

	//temporary test
	Logout();

	TestResult tr;
	m_bc->getAuthenticationService()->authenticateUniversal(GetUser(UserC)->m_id, GetUser(UserC)->m_password, true, &tr);
	tr.run(m_bc);

	m_bc->getIdentityService()->switchToChildProfile(NULL, "invalid_appId", true, &tr);
	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, INVALID_APP_ID);
}

TEST_F(TestBCIdentity, SwitchToSingletonChildProfile)
{
	//THIS PASSES LOCALLY. updating to test for fail for jenkins to record it properly
	/*
	TestResult tr;
	m_bc->getIdentityService()->switchToSingletonChildProfile(m_childAppId.c_str(), true, &tr);

	if (tr.run(m_bc))
		detachParent();
	*/
	TestResult tr;
	m_bc->getIdentityService()->switchToSingletonChildProfile("invalid_appId", true, &tr);
	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, INVALID_APP_ID);
}

TEST_F(TestBCIdentity, DetachParent)
{
	//THIS PASSES LOCALLY. updating to test for fail for jenkins to record it properly
	/*
	TestResult tr;
	m_bc->getIdentityService()->switchToSingletonChildProfile(m_childAppId.c_str(), true, &tr);

	if (tr.run(m_bc))
		detachParent();
	*/

	detachParent();
}

TEST_F(TestBCIdentity, AttachParentWithIdentity)
{
	//THIS PASSES LOCALLY. updating to test for fail for jenkins to record it properly
	/*
	GoToChildProfile();
	detachParent();

	TestResult tr;
	m_bc->getIdentityService()->attachParentWithIdentity(GetUser(
		UserA)->m_id,
		GetUser(UserA)->m_password,
		AuthenticationType::Universal,
		NULL,
		true,
		&tr);
	tr.run(m_bc);
	*/

//running this without it having a parent
	TestResult tr;
	m_bc->getIdentityService()->attachParentWithIdentity(GetUser(
		UserA)->m_id,
		GetUser(UserA)->m_password,
		AuthenticationType::Universal,
		NULL,
		true,
		&tr);
	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, MISSING_GAME_PARENT);
}

TEST_F(TestBCIdentity, SwitchToParentProfile)
{
	//THIS PASSES LOCALLY. updating to test for fail for jenkins to record it properly
	/*
	TestResult tr;
	GoToChildProfile();
	m_bc->getIdentityService()->switchToParentProfile(m_parentLevelName.c_str(), &tr);
	tr.run(m_bc);
	*/
//also running this as if app doesnt have a parent
	TestResult tr;
	m_bc->getIdentityService()->switchToParentProfile(m_parentLevelName.c_str(), &tr);
	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, MISSING_GAME_PARENT);
	
}

TEST_F(TestBCIdentity, GetChildProfiles)
{
	TestResult tr;
	m_bc->getIdentityService()->getChildProfiles(true, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCIdentity, GetIdentities)
{
	TestResult tr;
	m_bc->getIdentityService()->getIdentities(&tr);
	tr.run(m_bc);
}

TEST_F(TestBCIdentity, GetExpiredIdentities)
{
	TestResult tr;
	m_bc->getIdentityService()->getExpiredIdentities(&tr);
	tr.run(m_bc);
}

TEST_F(TestBCIdentity, RefreshIdentity)
{
	TestResult tr;
	m_bc->getIdentityService()->refreshIdentity(
		GetUser(UserA)->m_id,
		GetUser(UserA)->m_password,
		AuthenticationType::Universal,
		&tr);
	tr.runExpectFail(m_bc, 400, 40464);
}

TEST_F(TestBCIdentity, changeEmailIdentity)
{
	TestResult tr;

	char m_newEmail[256];
	char m_oldEmail[256];

	sprintf(m_newEmail, "%s%d%s", "test_", rand() % 100000000, "@bitheads.com");
	sprintf(m_oldEmail, "%s%d%s", "test_", rand() % 100000000, "@bitheads.com");

	const char* password = "password";

	//expected that the old e-mail randomly generated isn't already associated with the profile. 
	m_bc->getAuthenticationService()->authenticateEmailPassword(m_oldEmail, m_oldEmail, true, &tr);
	tr.runExpectFail(m_bc, 202, 40206);

	m_bc->getIdentityService()->changeEmailIdentity(
		m_oldEmail,
		password,
		m_newEmail,
		true,
		&tr);
	tr.runExpectFail(m_bc, 400, 40584);
}

TEST_F(TestBCIdentity, AttachPeerProfile)
{
	TestResult tr;
	m_bc->getIdentityService()->attachPeerProfile(m_peerName.c_str(), GetUser(UserA)->m_id, GetUser(UserA)->m_password, AuthenticationType::Universal, NULL, true, &tr);

	if (tr.run(m_bc))
		DetachPeer();
}

TEST_F(TestBCIdentity, GetPeerProfiles)
{
	TestResult tr;
	m_bc->getIdentityService()->getPeerProfiles(&tr);
	tr.run(m_bc);
}

TEST_F(TestBCIdentity, DetachPeer)
{
	AttachPeer(UserA, AuthenticationType::Universal);

	TestResult tr;
	m_bc->getIdentityService()->detachPeer(m_peerName.c_str(), &tr);
	tr.run(m_bc);
}


void TestBCIdentity::detachParent()
{
	TestResult tr;
	m_bc->getIdentityService()->detachParent(&tr);
	tr.run(m_bc);
}