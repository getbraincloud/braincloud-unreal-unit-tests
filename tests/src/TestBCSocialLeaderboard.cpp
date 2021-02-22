#include <stdlib.h>
#include <time.h>
#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "json/json.h"
#include "TestBCSocialLeaderboard.h"
#include <chrono>

using namespace BrainCloud;

#define LB_ID "testLeaderboard"
#define SOCIAL_LB_ID "testSocialLeaderboard"
#define DYNAMIC_LB_ID "testDynamicLeaderboard"
#define REWARD_EVENT_ID "tournamentRewardId"
#define GROUP_LB_ID "groupLeaderboardConfig"

TEST_F(TestBCSocialLeaderboard, GetSocialLeaderboard)
{
    TestResult tr;

    m_bc->getLeaderboardService()->getSocialLeaderboard(LB_ID, true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetSocialLeaderboardByVersion)
{
    TestResult tr;

    m_bc->getLeaderboardService()->getSocialLeaderboardByVersion(LB_ID, true, 0, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetMultiSocialLeaderboard)
{
    // post a few scores first so we have some data
    PostScoreToNonDynamic();
    PostScoreToDynamic();

    TestResult tr;
    std::vector<std::string> lbIds;
    lbIds.push_back(LB_ID);
    lbIds.push_back(DYNAMIC_LB_ID);
    m_bc->getLeaderboardService()->getMultiSocialLeaderboard(lbIds, 10, true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, PostScore)
{
    PostScoreToNonDynamic();
}

TEST_F(TestBCSocialLeaderboard, GetGlobalLeaderboardVersions)
{
    TestResult tr;

    m_bc->getLeaderboardService()->getGlobalLeaderboardVersions(LB_ID, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetGlobalLeaderboardPageHigh)
{
    TestResult tr;
    m_bc->getLeaderboardService()->getGlobalLeaderboardPage(LB_ID, HIGH_TO_LOW, 0, 10, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetGlobalLeaderboardPageLow)
{
    TestResult tr;
    m_bc->getLeaderboardService()->getGlobalLeaderboardPage(LB_ID, LOW_TO_HIGH, 0, 10, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetGlobalLeaderboardViewHigh)
{
    TestResult tr;
    m_bc->getLeaderboardService()->getGlobalLeaderboardView(LB_ID, HIGH_TO_LOW, 4, 5, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetGlobalLeaderboardViewLow)
{
    TestResult tr;
    m_bc->getLeaderboardService()->getGlobalLeaderboardView(LB_ID, LOW_TO_HIGH, 4, 5, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetGlobalPageByVersion)
{
    TestResult tr;

    m_bc->getLeaderboardService()->getGlobalLeaderboardPageByVersion(LB_ID, HIGH_TO_LOW, 0, 10, 0, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetGlobalViewByVersion)
{
    TestResult tr;

    m_bc->getLeaderboardService()->getGlobalLeaderboardViewByVersion(LB_ID, HIGH_TO_LOW, 0, 10, 0, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, PostScoreToDynamic)
{
    PostScoreToDynamic();
}

TEST_F(TestBCSocialLeaderboard, PostScoreToDynamicNullRotationTime)
{
    TestResult tr;
    Json::FastWriter fw;
    Json::Value jsonData;
    jsonData["testKey"] = "TestValue";

    m_bc->getLeaderboardService()->postScoreToDynamicLeaderboard(DYNAMIC_LB_ID, 100, fw.write(jsonData), HIGH_VALUE, NEVER, NULL, 2, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, PostScoreToDynamicUTC)
{
	srand(time(NULL));

    TestResult tr;
    Json::FastWriter fw;
    Json::Value jsonData;
    jsonData["testKey"] = "TestValue";

    int64_t milliseconds_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() + (2 * 60 * 1000); //add 2 minutes so its within the time 

	std::string name = DYNAMIC_LB_ID + std::to_string(rand());

    m_bc->getLeaderboardService()->postScoreToDynamicLeaderboardUTC(name.c_str(), 100, fw.write(jsonData), HIGH_VALUE, WEEKLY, milliseconds_since_epoch, 2, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, PostScoreToDynamicDays)
{
	TestResult tr;
	Json::FastWriter fw;
	Json::Value jsonData;
	jsonData["testKey"] = "TestValue";

	m_bc->getLeaderboardService()->postScoreToDynamicLeaderboardDays("TestDynamicDaysCpp", 100, fw.write(jsonData), HIGH_VALUE, NULL, 2, 3, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, PostScoreToDynamicDaysUTC)
{
	TestResult tr;
	Json::FastWriter fw;
	Json::Value jsonData;
	jsonData["testKey"] = "TestValue";

    int64_t milliseconds_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	m_bc->getLeaderboardService()->postScoreToDynamicLeaderboardDaysUTC("TestDynamicDaysCpp", 100, fw.write(jsonData), HIGH_VALUE, milliseconds_since_epoch, 2, 3, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetGroupSocialLeaderboard)
{
    TestResult tr;
    m_bc->getGroupService()->createGroup("testGroup", "test", false, "", "", "", "", &tr);
    tr.run(m_bc);

    std::string groupId = tr.m_response["data"]["groupId"].asString();

    m_bc->getLeaderboardService()->getGroupSocialLeaderboard(SOCIAL_LB_ID, groupId.c_str(), &tr);
    tr.run(m_bc);

    m_bc->getGroupService()->deleteGroup(groupId.c_str(), -1, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetGroupSocialLeaderboardByVersion)
{
    TestResult tr;
    m_bc->getGroupService()->createGroup("testGroup", "test", false, "", "", "", "", &tr);
    tr.run(m_bc);

    std::string groupId = tr.m_response["data"]["groupId"].asString();

    m_bc->getLeaderboardService()->getGroupSocialLeaderboardByVersion(SOCIAL_LB_ID, groupId.c_str(), 0, &tr);
    tr.run(m_bc);

    m_bc->getGroupService()->deleteGroup(groupId.c_str(), -1, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetPlayersSocialLeaderboard)
{
	TestResult tr;

	std::vector<std::string> profileIds;
	profileIds.push_back(GetUser(UserA)->m_profileId);
	profileIds.push_back(GetUser(UserB)->m_profileId);

	m_bc->getLeaderboardService()->getPlayersSocialLeaderboard(SOCIAL_LB_ID, profileIds, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetPlayersSocialLeaderboardByVersion)
{
	TestResult tr;

	std::vector<std::string> profileIds;
	profileIds.push_back(GetUser(UserA)->m_profileId);
	profileIds.push_back(GetUser(UserB)->m_profileId);

	m_bc->getLeaderboardService()->getPlayersSocialLeaderboardByVersion(SOCIAL_LB_ID, profileIds, 0, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, ListAllLeaderboards)
{
	TestResult tr;

	m_bc->getLeaderboardService()->listAllLeaderboards(&tr);
	tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetGlobalLeaderboardEntryCount)
{
	TestResult tr;

	m_bc->getLeaderboardService()->getGlobalLeaderboardEntryCount(LB_ID, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetGlobalLeaderboardEntryCountByVersion)
{
	TestResult tr;

	m_bc->getLeaderboardService()->getGlobalLeaderboardEntryCountByVersion(LB_ID, 1, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, RemoveScore)
{
	PostScoreToNonDynamic();

	TestResult tr;
	m_bc->getLeaderboardService()->removePlayerScore(LB_ID, -1, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetPlayerScore)
{
	PostScoreToNonDynamic();

	TestResult tr;
	m_bc->getLeaderboardService()->getPlayerScore(LB_ID, -1, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetPlayerScores)
{
	PostScoreToNonDynamic();

	TestResult tr;
	m_bc->getLeaderboardService()->getPlayerScores(LB_ID, -1, 5, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetPlayerScoresFromLeaderboards)
{
	// post a few scores first so we have some data
	PostScoreToNonDynamic();
	PostScoreToDynamic();

	TestResult tr;
	std::vector<std::string> lbIds;
	lbIds.push_back(LB_ID);
	lbIds.push_back(DYNAMIC_LB_ID);
	m_bc->getLeaderboardService()->getPlayerScoresFromLeaderboards(lbIds, &tr);
	tr.run(m_bc);
}

void TestBCSocialLeaderboard::PostScoreToDynamic()
{
	srand(time(NULL));

    TestResult tr;
    Json::FastWriter fw;
    Json::Value jsonData;
    jsonData["testKey"] = "TestValue";

    time_t t = time(0);
    struct tm * time = localtime(&t);
    time->tm_mday += 1;
    mktime(time);

	std::string name = DYNAMIC_LB_ID + std::to_string(rand());

    m_bc->getLeaderboardService()->postScoreToDynamicLeaderboard(name.c_str(), 100, fw.write(jsonData), HIGH_VALUE, WEEKLY, time, 2, &tr);
    tr.run(m_bc);
}

void TestBCSocialLeaderboard::PostScoreToNonDynamic()
{
    TestResult tr;

    m_bc->getLeaderboardService()->postScoreToLeaderboard(LB_ID, 100, "", &tr);
    tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, PostScoreToGroupLeaderboard)
{
    TestResult tr; 
    m_bc->getGroupService()->createGroup("testGroup", "test", false, "", "", "", "", &tr);
    tr.run(m_bc);

    std::string groupId = tr.m_response["data"]["groupId"].asString();

    Json::FastWriter fw;
    Json::Value jsonData;
    jsonData["testKey"] = "TestValue";

    m_bc->getLeaderboardService()->postScoreToGroupLeaderboard(GROUP_LB_ID, groupId.c_str(), 0, fw.write(jsonData), &tr);
    tr.run(m_bc);

    m_bc->getGroupService()->deleteGroup(groupId.c_str(), -1, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, PostScoreToDynamicGroupLeaderboard)
{
    TestResult tr; 
    m_bc->getGroupService()->createGroup("testGroup", "test", false, "", "", "", "", &tr);
    tr.run(m_bc);

    std::string groupId = tr.m_response["data"]["groupId"].asString();

    Json::FastWriter fw;
    Json::Value jsonData;
    jsonData["testKey"] = "TestValue";

    m_bc->getLeaderboardService()->postScoreToDynamicGroupLeaderboard(GROUP_LB_ID, groupId.c_str(), 0, fw.write(jsonData), "HIGH_VALUE", "WEEKLY", 157116287, 2, &tr);
    tr.run(m_bc);

    m_bc->getGroupService()->deleteGroup(groupId.c_str(), -1, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, PostScoreToDynamicGroupLeaderboardUTC)
{
    TestResult tr; 
    m_bc->getGroupService()->createGroup("testGroup", "test", false, "", "", "", "", &tr);
    tr.run(m_bc);

    std::string groupId = tr.m_response["data"]["groupId"].asString();

    Json::FastWriter fw;
    Json::Value jsonData;
    jsonData["testKey"] = "TestValue";

    int64_t milliseconds_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    m_bc->getLeaderboardService()->postScoreToDynamicGroupLeaderboardUTC(GROUP_LB_ID, groupId.c_str(), 0, fw.write(jsonData), "HIGH_VALUE", "WEEKLY", milliseconds_since_epoch, 2, &tr);
    tr.run(m_bc);

    m_bc->getGroupService()->deleteGroup(groupId.c_str(), -1, &tr);
    tr.run(m_bc);
}


TEST_F(TestBCSocialLeaderboard, RemoveGroupScore)
{
    TestResult tr; 
    m_bc->getGroupService()->createGroup("testGroup", "test", false, "", "", "", "", &tr);
    tr.run(m_bc);

    std::string groupId = tr.m_response["data"]["groupId"].asString();

    Json::FastWriter fw;
    Json::Value jsonData;
    jsonData["testKey"] = "TestValue";

    m_bc->getLeaderboardService()->postScoreToGroupLeaderboard(GROUP_LB_ID, groupId.c_str(), 100, fw.write(jsonData), &tr);
    tr.run(m_bc);

    m_bc->getLeaderboardService()->removeGroupScore(GROUP_LB_ID, groupId.c_str(), -1, &tr);
    tr.run(m_bc);

    m_bc->getGroupService()->deleteGroup(groupId.c_str(), -1, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetGroupLeaderboardView)
{
    TestResult tr; 
    m_bc->getGroupService()->createGroup("testGroup", "test", false, "", "", "", "", &tr);
    tr.run(m_bc);

    std::string groupId = tr.m_response["data"]["groupId"].asString();

    m_bc->getLeaderboardService()->getGroupLeaderboardView(GROUP_LB_ID, groupId.c_str(), HIGH_TO_LOW, 5, 5, &tr);
    tr.run(m_bc);

    m_bc->getGroupService()->deleteGroup(groupId.c_str(), -1, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetGroupLeaderboardViewByVersion)
{
    TestResult tr; 
    m_bc->getGroupService()->createGroup("testGroup", "test", false, "", "", "", "", &tr);
    tr.run(m_bc);

    std::string groupId = tr.m_response["data"]["groupId"].asString();

    m_bc->getLeaderboardService()->getGroupLeaderboardViewByVersion(GROUP_LB_ID, groupId.c_str(), 1, HIGH_TO_LOW, 5, 5, &tr);
    tr.run(m_bc);

    m_bc->getGroupService()->deleteGroup(groupId.c_str(), -1, &tr);
    tr.run(m_bc);
}