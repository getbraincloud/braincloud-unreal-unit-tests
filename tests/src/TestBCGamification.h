#ifndef _TESTBCGAMIFICATION_H_
#define _TESTBCGAMIFICATION_H_

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestFixtureBase.h"
#include "json/json.h"
#include <vector>

using namespace BrainCloud;

class TestBCGamification: public TestFixtureBase
{
protected:
    std::vector<std::string> m_achievements;
    const char * m_userStatsCategory;
    const char * m_milestoneCategory;
    const char * m_milestoneId;
    std::vector<std::string> m_milestoneIds;
    const char * m_questCategory;
    
public:
    TestBCGamification();
};

#endif
