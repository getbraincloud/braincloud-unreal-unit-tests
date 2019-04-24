#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "braincloud/http_codes.h"
#include "braincloud/reason_codes.h"
#include "TestResult.h"
#include "TestBCLobby.h"

using namespace BrainCloud;

// Lot of expect fail here. This is ok, but we make sure the failed reason 
// is not about a bad or missing argument. We validate that the API is
// written correctly, not that the output from BC is correct. This is
// verified more in depth by use case and JS unit tests.

TEST_F(TestBCLobby, FindLobby)
{
	TestResult tr;

	std::vector<std::string> otherUserCxIds;
	m_bc->getLobbyService()->findLobby("MATCH_UNRANKED", 0, 1, "{\"strategy\":\"ranged-absolute\",\"alignment\":\"center\",\"ranges\":[1000]}", "{}", otherUserCxIds, true, "{}", "all", &tr);

	tr.run(m_bc);
}

TEST_F(TestBCLobby, CreateLobby)
{
	TestResult tr;

	std::vector<std::string> otherUserCxIds;
	m_bc->getLobbyService()->createLobby("MATCH_UNRANKED", 0, otherUserCxIds, true, "{}", "all", "{}", &tr);

	tr.run(m_bc);
}

TEST_F(TestBCLobby, FindOrCreateLobby)
{
	TestResult tr;

	std::vector<std::string> otherUserCxIds;
	m_bc->getLobbyService()->findOrCreateLobby("MATCH_UNRANKED", 0, 1, "{\"strategy\":\"ranged-absolute\",\"alignment\":\"center\",\"ranges\":[1000]}", "{}", otherUserCxIds, "{}", true, "{}", "all", &tr);

	tr.run(m_bc);
}

TEST_F(TestBCLobby, GetLobbyData)
{
	TestResult tr;

	m_bc->getLobbyService()->getLobbyData("wrongLobbyId", &tr);

	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, LOBBY_NOT_FOUND);
}

TEST_F(TestBCLobby, LeaveLobby)
{
	TestResult tr;

	m_bc->getLobbyService()->leaveLobby("wrongLobbyId", &tr);

	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, LOBBY_NOT_FOUND);
}

TEST_F(TestBCLobby, JoinLobby)
{
	TestResult tr;
	std::vector<std::string> otherUserCxIds;
	//otherUserCxIds.push_back("5555");
	//otherUserCxIds.push_back("aaa-bbb-ccc-ddd");
	//m_bc->getLobbyService()->createLobby("4v4", 76, otherUserCxIds, true, "{}", "red", "{}", &tr);
	//m_bc->getLobbyService()->joinLobby("20001:4v4:1", true, "{}", "red", otherUserCxIds, &tr);
	m_bc->getLobbyService()->joinLobby("wrongLobbyId", true, "{}", "red", otherUserCxIds, &tr);

	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, LOBBY_NOT_FOUND);
}


TEST_F(TestBCLobby, RemoveMember)
{
	TestResult tr;

	m_bc->getLobbyService()->removeMember("wrongLobbyId", "wrongConId", &tr);

	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, LOBBY_NOT_FOUND);
}

TEST_F(TestBCLobby, SendSignal)
{
	TestResult tr;

	m_bc->getLobbyService()->sendSignal("wrongLobbyId", "{\"msg\":\"test\"}", &tr);

	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, LOBBY_NOT_FOUND);
}

TEST_F(TestBCLobby, SwitchTeam)
{
	TestResult tr;

	m_bc->getLobbyService()->switchTeam("wrongLobbyId", "all", &tr);

	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, LOBBY_NOT_FOUND);
}

TEST_F(TestBCLobby, UpdateReady)
{
	TestResult tr;

	m_bc->getLobbyService()->updateReady("wrongLobbyId", true, "{}", &tr);

	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, LOBBY_NOT_FOUND);
}

TEST_F(TestBCLobby, UpdateSettings)
{
	TestResult tr;

	m_bc->getLobbyService()->updateSettings("wrongLobbyId", "{\"msg\":\"test\"}", &tr);

	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, LOBBY_NOT_FOUND);
}
