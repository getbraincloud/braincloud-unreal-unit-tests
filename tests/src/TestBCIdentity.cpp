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
	// kill the session with UserA
	Logout();

	// open up a fresh session with UserC who should have no child profiles
	TestResult tr;
	m_bc->getAuthenticationService()->authenticateUniversal(GetUser(UserC)->m_id, GetUser(UserC)->m_password, true, &tr);
	tr.run(m_bc);

	m_bc->getIdentityService()->switchToChildProfile(NULL, m_childAppId.c_str(), true, &tr);
	tr.run(m_bc);
	
	m_bc->getIdentityService()->switchToParentProfile("Master");
}

TEST_F(TestBCIdentity, SwitchToSingletonChildProfile)
{
	TestResult tr;
	m_bc->getIdentityService()->switchToSingletonChildProfile(m_childAppId.c_str(), true, &tr);

	if (tr.run(m_bc))
		detachParent();
	
}

TEST_F(TestBCIdentity, DetachParent)
{
	TestResult tr;
	m_bc->getIdentityService()->switchToSingletonChildProfile(m_childAppId.c_str(), true, &tr);

	if (tr.run(m_bc))
		detachParent();
}

TEST_F(TestBCIdentity, AttachParentWithIdentity)
{
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
	
}

TEST_F(TestBCIdentity, SwitchToParentProfile)
{
	TestResult tr;
	GoToChildProfile();
	m_bc->getIdentityService()->switchToParentProfile(m_parentLevelName.c_str(), &tr);
	tr.run(m_bc);
	
	TestResult tr2;
	m_bc->getIdentityService()->switchToChildProfile(NULL, m_childAppId.c_str(), true, &tr2);
	tr2.run(m_bc);
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

TEST_F(TestBCIdentity, AttachNonLoginUniversalId)
{
	TestResult tr;
	m_bc->getIdentityService()->attachNonLoginUniversalId("braincloudtest@gmail.com", &tr);
	//this user already has a universalId and so the server will return a duplicate identity type. 
	tr.runExpectFail(m_bc, 202, DUPLICATE_IDENTITY_TYPE);
}

TEST_F(TestBCIdentity, UpdateUniversalIdLogin)
{
	TestResult tr;
	m_bc->getIdentityService()->updateUniversalIdLogin("braincloudtest@gmail.com", &tr);
	//after this test is run once, the universal Id will always be in use, but changing the universal Id to something not in use passes. 
	tr.runExpectFail(m_bc, 400, NEW_CREDENTIAL_IN_USE);
}

void TestBCIdentity::detachParent()
{
	TestResult tr;
	m_bc->getIdentityService()->detachParent(&tr);
	tr.run(m_bc);
}
