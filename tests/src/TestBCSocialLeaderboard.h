#ifndef _TESTBCSOCIALLEADERBOARD_H_
#define _TESTBCSOCIALLEADERBOARD_H_

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestFixtureBase.h"
#include "json/json.h"

using namespace BrainCloud;

class TestBCSocialLeaderboard : public TestFixtureBase
{
protected:
    void PostScoreToDynamic();
    void PostScoreToNonDynamic();
};

#endif
