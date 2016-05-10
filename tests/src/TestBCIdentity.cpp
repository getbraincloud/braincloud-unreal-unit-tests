#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCIdentity.h"

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