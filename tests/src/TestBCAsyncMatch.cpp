#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCAsyncMatch.h"

using namespace BrainCloud;


TEST_F(TestBCAsyncMatch, Create)
{
    TestBCAsyncMatch::CreateMatch();
    TestBCAsyncMatch::AbandonMatch();
}

TEST_F(TestBCAsyncMatch, Abandon)
{
    TestBCAsyncMatch::CreateMatch();
    TestBCAsyncMatch::AbandonMatch();
}

TEST_F(TestBCAsyncMatch, CreateWithInitialTurn)
{
    TestBCAsyncMatch::CreateMatchWithInitialTurn();
    TestBCAsyncMatch::AbandonMatch();
}

TEST_F(TestBCAsyncMatch, Complete)
{
    TestBCAsyncMatch::CreateMatchWithInitialTurn();
    
    TestResult tr;
    m_bc->getAsyncMatchService()->completeMatch(GetUser(UserA)->m_profileId, m_matchId.c_str(), &tr);
    tr.run(m_bc);
}

TEST_F(TestBCAsyncMatch, FindCompleteMatches)
{
    TestResult tr;
    m_bc->getAsyncMatchService()->findCompleteMatches(&tr);
    tr.run(m_bc);
}

TEST_F(TestBCAsyncMatch, FindMatches)
{
    TestBCAsyncMatch::CreateMatch();
    TestResult tr;
    m_bc->getAsyncMatchService()->findMatches(&tr);
    tr.run(m_bc);
    TestBCAsyncMatch::AbandonMatch();
}

TEST_F(TestBCAsyncMatch, ReadMatch)
{
    TestBCAsyncMatch::CreateMatch();
    TestResult tr;
    m_bc->getAsyncMatchService()->readMatch(GetUser(UserA)->m_profileId, m_matchId.c_str(), &tr);
    tr.run(m_bc);
    TestBCAsyncMatch::AbandonMatch();
}

TEST_F(TestBCAsyncMatch, ReadMatchHistory)
{
    TestBCAsyncMatch::CreateMatch();
    TestResult tr;
    m_bc->getAsyncMatchService()->readMatchHistory(GetUser(UserA)->m_profileId, m_matchId.c_str(), &tr);
    tr.run(m_bc);
    TestBCAsyncMatch::AbandonMatch();
}

TEST_F(TestBCAsyncMatch, SubmitTurn)
{
    TestBCAsyncMatch::CreateMatch();
    TestResult tr;
    
    Json::Value matchState;
    matchState["map"] = "level01";
    Json::FastWriter fw;
    
    m_bc->getAsyncMatchService()->submitTurn(GetUser(UserA)->m_profileId,
                                             m_matchId.c_str(),
                                             0,
                                             fw.write(matchState).c_str(),
                                             NULL,
                                             GetUser(UserB)->m_profileId,
                                             fw.write(matchState).c_str(),
                                             fw.write(matchState).c_str(),
                                             &tr);
    tr.run(m_bc);
    TestBCAsyncMatch::AbandonMatch();
}

TEST_F(TestBCAsyncMatch, UpdateMatchSummaryData)
{
    TestBCAsyncMatch::CreateMatch();
    TestResult tr;
    
    Json::Value matchState;
    matchState["map"] = "level01";
    Json::FastWriter fw;
    
    m_bc->getAsyncMatchService()->updateMatchSummaryData(GetUser(UserA)->m_profileId,
                                                         m_matchId.c_str(),
                                                         0,
                                                         fw.write(matchState).c_str(),
                                                         &tr);
    tr.run(m_bc);
    TestBCAsyncMatch::AbandonMatch();
}

TEST_F(TestBCAsyncMatch, CompleteMatchWithSummaryData)
{
    //create match and submit turn
    TestBCAsyncMatch::CreateMatch();
    TestResult tr;
    
    Json::Value matchState;
    matchState["map"] = "level01";
    Json::FastWriter fw;
    
    m_bc->getAsyncMatchService()->submitTurn(GetUser(UserA)->m_profileId,
                                             m_matchId.c_str(),
                                             0,
                                             fw.write(matchState).c_str(),
                                             NULL,
                                             GetUser(UserB)->m_profileId,
                                             fw.write(matchState).c_str(),
                                             fw.write(matchState).c_str(),
                                             &tr);
    tr.run(m_bc);

    //COMPLETE
        m_bc->getAsyncMatchService()->completeMatchWithSummaryData(GetUser(UserA)->m_profileId,
                                             m_matchId.c_str(),
                                             "",
                                             "{\"test\": \"Testing\"}",
                                             &tr);
    tr.run(m_bc);
}

TEST_F(TestBCAsyncMatch, AbandonMatchWithSummaryData)
{
    //create match and submit turn
    TestBCAsyncMatch::CreateMatch();
    TestResult tr;
    
    Json::Value matchState;
    matchState["map"] = "level01";
    Json::FastWriter fw;
    
    m_bc->getAsyncMatchService()->submitTurn(GetUser(UserA)->m_profileId,
                                             m_matchId.c_str(),
                                             0,
                                             fw.write(matchState).c_str(),
                                             NULL,
                                             GetUser(UserB)->m_profileId,
                                             fw.write(matchState).c_str(),
                                             fw.write(matchState).c_str(),
                                             &tr);
    tr.run(m_bc);

    //COMPLETE
        m_bc->getAsyncMatchService()->abandonMatchWithSummaryData(GetUser(UserA)->m_profileId,
                                             m_matchId.c_str(),
                                             "",
                                             "{\"test\": \"Testing\"}",
                                             &tr);
    tr.run(m_bc);
}

void TestBCAsyncMatch::CreateMatch()
{
    TestResult tr;
    Json::FastWriter fw;
    
    Json::Value player2Data;
    player2Data["id"] = GetUser(UserB)->m_profileId;
    player2Data["platform"] = "BC";
    
    Json::Value players(Json::arrayValue);
    players.append(player2Data);
    
    m_bc->getAsyncMatchService()->createMatch(fw.write(players).c_str(), NULL, &tr);
    tr.run(m_bc);
    m_matchId = tr.m_response["data"]["matchId"].asString();
}

void TestBCAsyncMatch::CreateMatchWithInitialTurn()
{
    TestResult tr;
    Json::FastWriter fw;
    
    Json::Value player2Data;
    player2Data["id"] = GetUser(UserB)->m_profileId;
    player2Data["platform"] = "BC";
    
    Json::Value players(Json::arrayValue);
    players.append(player2Data);
    
    Json::Value matchState;
    matchState["map"] = "level01";
    
    m_bc->getAsyncMatchService()->createMatchWithInitialTurn(fw.write(players).c_str(),
                                                             NULL,
                                                             NULL,
                                                             GetUser(UserB)->m_profileId,
                                                             fw.write(matchState).c_str(),
                                                             &tr);
    tr.run(m_bc);
    m_matchId = tr.m_response["data"]["matchId"].asString();
}

void TestBCAsyncMatch::AbandonMatch()
{
    TestResult tr;
    m_bc->getAsyncMatchService()->abandonMatch(GetUser(UserA)->m_profileId, m_matchId.c_str(), &tr);
    tr.run(m_bc);
}
