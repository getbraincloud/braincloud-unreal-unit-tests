#include <stdlib.h>
#include <time.h>
#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "json/json.h"
#include "TestBCSocialLeaderboard.h"

using namespace BrainCloud;

#define LB_ID "testLeaderboard"
#define SOCIAL_LB_ID "testSocialLeaderboard"
#define DYNAMIC_LB_ID "testDynamicLeaderboard"
#define REWARD_EVENT_ID "tournamentRewardId"

TEST_F(TestBCSocialLeaderboard, GetSocialLeaderboard)
{
	TestResult tr;

	m_bc->getSocialLeaderboardService()->getSocialLeaderboard(LB_ID, true, &tr);
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
	m_bc->getSocialLeaderboardService()->getMultiSocialLeaderboard(lbIds, 10, true, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, PostScore)
{
	PostScoreToNonDynamic();
}

TEST_F(TestBCSocialLeaderboard, GetGlobalLeaderboardVersions)
{
	TestResult tr;

	m_bc->getSocialLeaderboardService()->getGlobalLeaderboardVersions(LB_ID, &tr);
	tr.run(m_bc);
}


TEST_F(TestBCSocialLeaderboard, GetGlobalLeaderboardPageHigh)
{
	TestResult tr;
	m_bc->getSocialLeaderboardService()->getGlobalLeaderboardPage(LB_ID, HIGH_TO_LOW, 0, 10, true, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetGlobalLeaderboardPageLow)
{
	TestResult tr;
	m_bc->getSocialLeaderboardService()->getGlobalLeaderboardPage(LB_ID, LOW_TO_HIGH, 0, 10, true, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetGlobalLeaderboardViewHigh)
{
	TestResult tr;
	m_bc->getSocialLeaderboardService()->getGlobalLeaderboardView(LB_ID, HIGH_TO_LOW, 4, 5, true, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetGlobalLeaderboardViewLow)
{
	TestResult tr;
	m_bc->getSocialLeaderboardService()->getGlobalLeaderboardView(LB_ID, LOW_TO_HIGH, 4, 5, true, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, ResetScore)
{
	TestResult tr;

	m_bc->getSocialLeaderboardService()->resetLeaderboardScore(LB_ID, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetCompletedTournament)
{
	TestResult tr;

	m_bc->getSocialLeaderboardService()->getCompletedLeaderboardTournament(SOCIAL_LB_ID, true, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetGlobalPageByVersion)
{
	TestResult tr;

	m_bc->getSocialLeaderboardService()->getGlobalLeaderboardPageByVersion(LB_ID, HIGH_TO_LOW, 0, 10, true, 0, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetGlobalViewByVersion)
{
	TestResult tr;

	m_bc->getSocialLeaderboardService()->getGlobalLeaderboardViewByVersion(LB_ID, HIGH_TO_LOW, 0, 10, true, 0, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, TriggerSocialTournamentReward)
{
	TestResult tr;
	m_bc->getSocialLeaderboardService()->triggerSocialLeaderboardTournamentReward(SOCIAL_LB_ID, REWARD_EVENT_ID, 5, &tr);
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

	m_bc->getSocialLeaderboardService()->postScoreToDynamicLeaderboard(DYNAMIC_LB_ID, 100, fw.write(jsonData), HIGH_VALUE, NEVER, NULL, 2, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCSocialLeaderboard, GetGroupSocialLeaderboard)
{
	TestResult tr;
	m_bc->getGroupService()->createGroup("testGroup", "test", false, "", "", "", "", &tr);
	tr.run(m_bc);

	std::string groupId = tr.m_response["data"]["groupId"].asString();

	m_bc->getSocialLeaderboardService()->getGroupSocialLeaderboard(SOCIAL_LB_ID, groupId.c_str(), &tr);
	tr.run(m_bc);

	m_bc->getGroupService()->deleteGroup(groupId.c_str(), -1, &tr);
	tr.run(m_bc);
}

void TestBCSocialLeaderboard::PostScoreToDynamic()
{
	TestResult tr;
	Json::FastWriter fw;
	Json::Value jsonData;
	jsonData["testKey"] = "TestValue";
	time_t t = time(0);
	struct tm * time = localtime(&t);

	time->tm_mday += 1;
	mktime(time);

	m_bc->getSocialLeaderboardService()->postScoreToDynamicLeaderboard(DYNAMIC_LB_ID, 100, fw.write(jsonData), HIGH_VALUE, WEEKLY, time, 2, &tr);
	tr.run(m_bc);
}

void TestBCSocialLeaderboard::PostScoreToNonDynamic()
{
	TestResult tr;

	m_bc->getSocialLeaderboardService()->postScoreToLeaderboard(LB_ID, 100, "", &tr);
	tr.run(m_bc);
}