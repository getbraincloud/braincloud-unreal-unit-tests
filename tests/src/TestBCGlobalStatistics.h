#ifndef _TESTBCGLOBALSTATISTICS_H_
#define _TESTBCGLOBALSTATISTICS_H_

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestFixtureBase.h"
#include "json/json.h"

using namespace BrainCloud;

class TestBCGlobalStatistics: public TestFixtureBase
{
protected:
    std::string m_statName;
    
public:
    TestBCGlobalStatistics()
    {
        m_statName = "TestStat";
    }
};

#endif
