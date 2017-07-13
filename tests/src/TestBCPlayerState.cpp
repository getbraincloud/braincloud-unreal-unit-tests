#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCPlayerState.h"

using namespace BrainCloud;


TEST_F(TestBCPlayerState, DeletePlayer)
{
    Authenticate();
    TestResult tr;
    m_bc->getPlayerStateService()->deleteUser(&tr);
    tr.run(m_bc);
    
    // after having deleted a player, the cached profile id will be incorrect
    // in the cached array. So we fix it here...
    Authenticate();
    std::string profileId = m_bc->getAuthenticationService()->getProfileId();
    sprintf(GetUser(UserA)->m_profileId, "%s", profileId.c_str());
}

TEST_F(TestBCPlayerState, GetAttributes)
{
    Authenticate();
    TestResult tr;
    m_bc->getPlayerStateService()->getAttributes(&tr);
    tr.run(m_bc);
    Logout();
}

TEST_F(TestBCPlayerState, Logout)
{
    Authenticate();
    TestResult tr;
    m_bc->getPlayerStateService()->logout(&tr);
    tr.run(m_bc);
}

TEST_F(TestBCPlayerState, ReadPlayerState)
{
    Authenticate();
    TestResult tr;
    m_bc->getPlayerStateService()->readUserState(&tr);
    tr.run(m_bc);
    Logout();
}

TEST_F(TestBCPlayerState, RemoveAttributes)
{
    Authenticate();
    TestResult tr;
    
    std::vector<std::string> attributes;
    attributes.push_back("testAttribute1");
    attributes.push_back("testAttribute2");
    
    m_bc->getPlayerStateService()->removeAttributes(attributes, &tr);
    tr.run(m_bc);
    Logout();
}

TEST_F(TestBCPlayerState, ResetPlayerState)
{
    Authenticate();
    TestResult tr;
    m_bc->getPlayerStateService()->resetUserState(&tr);
    tr.run(m_bc);
    Logout();
}

TEST_F(TestBCPlayerState, UpdateAttributes)
{
    Authenticate();
    TestResult tr;
    Json::FastWriter fw;
    Json::Value stats;
    stats["testAttribute1"] = "10";
    stats["testAttribute2"] = "20";
    m_bc->getPlayerStateService()->updateAttributes(fw.write(stats), true, &tr);
    tr.run(m_bc);
    Logout();
}

TEST_F(TestBCPlayerState, UpdatePlayerName)
{
    Authenticate();
    TestResult tr;
    m_bc->getPlayerStateService()->updateUserName(GetUser(UserA)->m_id, &tr);
    tr.run(m_bc);
    Logout();
}

TEST_F(TestBCPlayerState, UpdateSummaryFriendData)
{
    Authenticate();
    TestResult tr;
    m_bc->getPlayerStateService()->updateSummaryFriendData("{\"field\":\"value\"}", &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPlayerState, UpdatePlayerPictureUrl)
{
    Authenticate();
    TestResult tr;
    m_bc->getPlayerStateService()->updateUserPictureUrl("https://some.domain.com/mypicture.jpg", &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPlayerState, UpdateContactEmail)
{
    Authenticate();
    TestResult tr;
    m_bc->getPlayerStateService()->updateContactEmail(GetUser(UserA)->m_email, &tr);
    tr.run(m_bc);
}

void TestBCPlayerState::Authenticate()
{
    TestResult tr;
    m_bc->getAuthenticationService()->authenticateUniversal(GetUser(UserA)->m_id, GetUser(UserA)->m_password, true, &tr);
    tr.run(m_bc);
}

void TestBCPlayerState::Logout()
{
    TestResult tr;
    m_bc->getPlayerStateService()->logout(&tr);
    tr.run(m_bc);
}

