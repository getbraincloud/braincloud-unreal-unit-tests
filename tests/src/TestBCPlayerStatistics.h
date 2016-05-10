#ifndef _TESTBCPLAYERSTATISTICS_H_
#define _TESTBCPLAYERSTATISTICS_H_

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestFixtureBase.h"
#include "json/json.h"

using namespace BrainCloud;

class TestBCPlayerStatistics: public TestFixtureBase
{
protected:
    const char* m_stat1;
    const char* m_stat2;
    
public:
    TestBCPlayerStatistics()
    {
        m_stat1 = "currency";
        m_stat2 = "highestScore";
    }
};

#endif
