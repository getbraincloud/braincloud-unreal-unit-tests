#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCIdentity.h"
#include "braincloud/AuthenticationType.h"

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
}

TEST_F(TestBCIdentity, SwitchToSingletonChildProfile)
{
	TestResult tr;
	m_bc->getIdentityService()->switchToSingletonChildProfile(m_childAppId.c_str(), true, &tr);
	
	if(tr.run(m_bc))
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
		true,
		NULL, 
		&tr);	
	tr.run(m_bc);
}

TEST_F(TestBCIdentity, SwitchToParentProfile)
{
	TestResult tr;
	GoToChildProfile();
	m_bc->getIdentityService()->switchToParentProfile(m_parentLevelName.c_str(), &tr);
	tr.run(m_bc);
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

TEST_F(TestBCIdentity, AttachPeerProfile)
{
	TestResult tr;
	m_bc->getIdentityService()->attachPeerProfile(GetUser(UserA)->m_id, GetUser(UserA)->m_password, AuthenticationType::Universal, true, NULL, m_peerName.c_str(), &tr);
	
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