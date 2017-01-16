#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCTournament.h"
#include "braincloud/reason_codes.h"
#include "braincloud/BrainCloudSocialLeaderboard.h"
#include <time.h>

using namespace BrainCloud;


TEST_F(TestBCTournament, ClaimTournamentReward)
{
	int32_t version = JoinTournament();

	TestResult tr;

	m_bc->getTournamentService()->claimTournamentReward(_leaderboardId, version, &tr);
	tr.runExpectFail(m_bc, 400, VIEWING_REWARD_FOR_NON_PROCESSED_TOURNAMENTS);

	LeaveTournament();
}

TEST_F(TestBCTournament, GetTournamentStatus)
{
	int32_t version = JoinTournament();

	TestResult tr;

	m_bc->getTournamentService()->getTournamentStatus(_leaderboardId, version, &tr);
	tr.run(m_bc);

	LeaveTournament();
}

TEST_F(TestBCTournament, JoinTournament)
{
	JoinTournament();
	LeaveTournament();
}

TEST_F(TestBCTournament, LeaveTournament)
{
	JoinTournament();
	LeaveTournament();
}

TEST_F(TestBCTournament, PostTournamentScore)
{
	int32_t version = JoinTournament();

	TestResult tr;
	time_t t = time(0);
	struct tm * time = gmtime(&t);

	m_bc->getTournamentService()->postTournamentScore(_leaderboardId, 200, "", time, &tr);
	tr.run(m_bc);

	LeaveTournament();
}

TEST_F(TestBCTournament, PostTournamentScoreWithResults)
{
	int32_t version = JoinTournament();

	TestResult tr;
	time_t t = time(0);
	struct tm * time = gmtime(&t);

	m_bc->getTournamentService()->postTournamentScoreWithResults(_leaderboardId, 200, "", time, HIGH_TO_LOW, 10, 10, 0, &tr);
	tr.run(m_bc);

	LeaveTournament();
}

TEST_F(TestBCTournament, ViewCurrentReward)
{
	JoinTournament();

	TestResult tr;
	m_bc->getTournamentService()->viewCurrentReward(_leaderboardId, &tr);
	tr.run(m_bc);

	LeaveTournament();
}

TEST_F(TestBCTournament, ViewReward)
{
	JoinTournament();

	TestResult tr;
	m_bc->getTournamentService()->viewReward(_leaderboardId, -1, &tr);
	tr.run(m_bc);

	LeaveTournament();
}

int32_t TestBCTournament::JoinTournament()
{
	TestResult tr;
	m_bc->getTournamentService()->joinTournament(_leaderboardId, _tournamentCode, 100, &tr);
	tr.run(m_bc);

	m_bc->getTournamentService()->getTournamentStatus(_leaderboardId, -1, &tr);
	tr.run(m_bc);
	return tr.m_response["data"]["versionId"].asInt();
}

void TestBCTournament::LeaveTournament()
{
	TestResult tr;
	m_bc->getTournamentService()->leaveTournament(_leaderboardId, &tr);
	tr.run(m_bc);
}