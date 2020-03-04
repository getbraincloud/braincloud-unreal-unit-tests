#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCTournament.h"
#include "braincloud/reason_codes.h"
#include "braincloud/BrainCloudSocialLeaderboard.h"
#include <ctime>

using namespace BrainCloud;


TEST_F(TestBCTournament, ClaimTournamentReward)
{
	int32_t version = JoinTournament();

	TestResult tr;

	m_bc->getTournamentService()->claimTournamentReward(_leaderboardId, version, &tr);
	tr.runExpectFail(m_bc, 400, VIEWING_REWARD_FOR_NON_PROCESSED_TOURNAMENTS);

	LeaveTournament();
}

TEST_F(TestBCTournament, GetDivisionInfo)
{
	TestResult tr;
	m_bc->getTournamentService()->getDivisionInfo("Invalid_Id", &tr);
	tr.runExpectFail(m_bc, 400, DIVISION_SET_DOESNOT_EXIST);
}

TEST_F(TestBCTournament, GetMyDivisions)
{
	TestResult tr; 
	m_bc->getTournamentService()->getMyDivisions(&tr);
	tr.run(m_bc);
}

TEST_F(TestBCTournament, JoinDivision)
{
	TestResult tr; 
	m_bc->getTournamentService()->joinDivision("Invalid_Id", _tournamentCode, 0,  &tr);
	tr.runExpectFail(m_bc, 400, DIVISION_SET_DOESNOT_EXIST);
}

TEST_F(TestBCTournament, LeaveDivisionInstance)
{
	TestResult tr; 
	m_bc->getTournamentService()->leaveDivisionInstance(_leaderboardId, &tr);
	tr.runExpectFail(m_bc, 400, LEADERBOARD_NOT_DIVISION_SET_INSTANCE);
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

TEST_F(TestBCTournament, PostTournamentScoreUTC)
{
	int32_t version = JoinTournament();

	TestResult tr;
	time_t t = time(NULL);
	struct tm * time = gmtime(&t);
	time->tm_hour +=1;

	m_bc->getTournamentService()->postTournamentScoreUTC(_leaderboardId, 200, "", time, &tr);
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

TEST_F(TestBCTournament, PostTournamentScoreWithResultsUTC)
{
	int32_t version = JoinTournament();

	TestResult tr;
	time_t t = time(0);
	struct tm * time = gmtime(&t);
	time->tm_hour +=1;

	m_bc->getTournamentService()->postTournamentScoreWithResultsUTC(_leaderboardId, 200, "", time, HIGH_TO_LOW, 10, 10, 0, &tr);
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
	tr.runExpectFail(m_bc, 400, PLAYER_NOT_ENROLLED_IN_TOURNAMENT);

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
