#include <stdlib.h>
#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "braincloud/BrainCloudEntity.h"
#include "TestResult.h"
#include "json/json.h"
#include "braincloud/FriendPlatform.h"

#include "TestBCFriend.h"

#include <vector>
#include <string>

using namespace BrainCloud;

TEST_F(TestBCFriend, GetFriendProfileInfo)
{
    TestResult tr;
    m_bc->getFriendService()->getFriendProfileInfoForExternalId("12345", "Facebook", &tr);
    tr.run(m_bc);
}

TEST_F(TestBCFriend, GetExternalIdForProfileId)
{
    TestResult tr;
    m_bc->getFriendService()->getExternalIdForProfileId(GetUser(UserA)->m_profileId, "Facebook", &tr);
    tr.run(m_bc);
}

TEST_F(TestBCFriend, FindPlayerByName)
{
    TestResult tr;
    m_bc->getFriendService()->findPlayerByName("test", 10, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCFriend, FindPlayerByUniversalId)
{
    TestResult tr;
    m_bc->getFriendService()->findPlayerByUniversalId("search", 10, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCFriend, GetSummaryDataForProfileId)
{
	TestResult tr;
	m_bc->getFriendService()->getSummaryDataForProfileId(GetUser(UserA)->m_profileId, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCFriend, AddFriends)
{
    AddFriends();
}

TEST_F(TestBCFriend, ListFriends)
{
    TestResult tr;
    m_bc->getFriendService()->listFriends(FriendPlatform::All, true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCFriend, RemoveFriends)
{
    AddFriends();

    TestResult tr;
    std::vector<std::string> profiles;
    profiles.push_back(GetUser(UserB)->m_profileId);

    m_bc->getFriendService()->removeFriends(profiles, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCFriend, GetUsersOnlineStatus)
{
	TestResult tr;
	std::vector<std::string> profiles;
	profiles.push_back(GetUser(UserB)->m_profileId);

	m_bc->getFriendService()->getUsersOnlineStatus(profiles, &tr);
	tr.run(m_bc);
}

void TestBCFriend::AddFriends()
{
    TestResult tr;
    std::vector<std::string> profiles;
    profiles.push_back(GetUser(UserB)->m_profileId);

    m_bc->getFriendService()->addFriends(profiles, &tr);
    tr.run(m_bc);
}



