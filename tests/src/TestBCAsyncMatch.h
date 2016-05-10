#ifndef _TESTBCASYNCMATCH_H_
#define _TESTBCASYNCMATCH_H_

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestFixtureBase.h"
#include "json/json.h"

using namespace BrainCloud;

class TestBCAsyncMatch: public TestFixtureBase
{
protected:
    int m_serverTime;
    void CreateMatch();
    void CreateMatchWithInitialTurn();
    void AbandonMatch();
    
    std::string m_matchId;
};

#endif
