#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCMatchMaking.h"

using namespace BrainCloud;


TEST_F(TestBCMatchMaking, GetShieldExpiry)
{
    TestResult tr;

    m_bc->getMatchmakingService()->getShieldExpiry(NULL, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCMatchMaking, Read)
{
    TestResult tr;

    m_bc->getMatchmakingService()->read(&tr);
    tr.run(m_bc);
}

TEST_F(TestBCMatchMaking, EnableMatchMaking)
{
    TestResult tr;

    m_bc->getMatchmakingService()->enableMatchMaking(&tr);
    tr.run(m_bc);
}

TEST_F(TestBCMatchMaking, DisableMatchMaking)
{
    TestResult tr;

    m_bc->getMatchmakingService()->disableMatchMaking(&tr);
    tr.run(m_bc);

    m_bc->getMatchmakingService()->enableMatchMaking(&tr);
    tr.run(m_bc);
}

TEST_F(TestBCMatchMaking, SetPlayerRating)
{
    TestResult tr;

    m_bc->getMatchmakingService()->setPlayerRating(5, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCMatchMaking, ResetPlayerRaing)
{
    TestResult tr;

    m_bc->getMatchmakingService()->resetPlayerRating(&tr);
    tr.run(m_bc);
}

TEST_F(TestBCMatchMaking, IncrementPlayerRating)
{
    TestResult tr;

    m_bc->getMatchmakingService()->incrementPlayerRating(1, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCMatchMaking, DecrementPlayerRating)
{
    TestResult tr;

    m_bc->getMatchmakingService()->decrementPlayerRating(1, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCMatchMaking, TurnShieldOn)
{
    TestResult tr;

    m_bc->getMatchmakingService()->turnShieldOn(&tr);
    tr.run(m_bc);
}

TEST_F(TestBCMatchMaking, TurnShieldOff)
{
    TestResult tr;

    m_bc->getMatchmakingService()->turnShieldOff(&tr);
    tr.run(m_bc);
}

TEST_F(TestBCMatchMaking, TurnShieldOnFOr)
{
    TestResult tr;

    m_bc->getMatchmakingService()->turnShieldOnFor(10, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCMatchMaking, IncrementShieldOnFor)
{
    TestResult tr;

    m_bc->getMatchmakingService()->incrementShieldOnFor(10, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCMatchMaking, FindPlayers)
{
    TestResult tr;

    m_bc->getMatchmakingService()->findPlayers(10, 3, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCMatchMaking, FindPlayersUsingFilter)
{
    TestResult tr;
    Json::FastWriter fw;
    Json::Value filters;
    filters["filter1"] = 10;

    m_bc->getMatchmakingService()->findPlayersUsingFilter(10, 3, fw.write(filters), &tr);
    tr.run(m_bc);
}

TEST_F(TestBCMatchMaking, FindPlayersWithAttributes)
{
    TestResult tr;

    Json::FastWriter fw;
    Json::Value attribs;
    attribs["name"] = "test";

    m_bc->getMatchmakingService()->findPlayersWithAttributes(10, 3, fw.write(attribs), &tr);
    tr.run(m_bc);
}

TEST_F(TestBCMatchMaking, FindPlayersWithAttributesUsingFilter)
{
    TestResult tr;
    Json::FastWriter fw;

    Json::Value filters;
    filters["filter1"] = 10;

    Json::Value attribs;
    attribs["name"] = "test";

    m_bc->getMatchmakingService()->findPlayersWithAttributesUsingFilter(
        10, 3, fw.write(attribs), fw.write(filters), &tr);
    tr.run(m_bc);
}