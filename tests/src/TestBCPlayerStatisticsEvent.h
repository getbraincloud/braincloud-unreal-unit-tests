#ifndef _TESTBCPLAYERSTATISTICSEVENT_H_
#define _TESTBCPLAYERSTATISTICSEVENT_H_

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestFixtureBase.h"
#include "json/json.h"

using namespace BrainCloud;

class TestBCPlayerStatisticsEvent: public TestFixtureBase, public IRewardCallback
{
protected:
    const char* m_eventId01;
    const char* m_eventId02;
    
    int m_rewardCallbackHitCount;
    
public:
    TestBCPlayerStatisticsEvent()
    {
        m_eventId01 = "testEvent01";
        m_eventId02 = "rewardCredits";
        m_rewardCallbackHitCount = 0;
    }
    
    virtual void rewardCallback(std::string const & jsonData);
};

#endif
