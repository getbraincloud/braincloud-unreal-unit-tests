#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCPlayerStatisticsEvent.h"

using namespace BrainCloud;

TEST_F(TestBCPlayerStatisticsEvent, TriggerPlayerStatisticsEvent)
{
    TestResult tr;
    m_bc->getPlayerStatisticsEventService()->triggerStatsEvent(m_eventId01, 10, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPlayerStatisticsEvent, TriggerPlayerStatisticsEvents)
{
    TestResult tr;
    Json::FastWriter fw;
    Json::Value eventArray(Json::arrayValue);
    
    Json::Value event;
    event["eventName"] = m_eventId01;
    event["eventMultiplier"] = 10;
    eventArray.append(event);
    
    event.clear();
    event["eventName"] = m_eventId02;
    event["eventMultiplier"] = 10;
    eventArray.append(event);

    m_bc->getPlayerStatisticsEventService()->triggerStatsEvents(fw.write(eventArray).c_str(), &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPlayerStatisticsEvent, RewardHandlerTriggerStatisticsEvents)
{
    m_rewardCallbackHitCount = 0;
    
    TestResult tr;
    Json::FastWriter fw;
    Json::Value eventArray(Json::arrayValue);

    m_bc->getPlayerStateService()->resetUserState(&tr);
    tr.run(m_bc);
    
    Json::Value event;
    event["eventName"] = "incQuest1Stat";
    event["eventMultiplier"] = 1;
    eventArray.append(event);
    
    event.clear();
    event["eventName"] = "incQuest2Stat";
    event["eventMultiplier"] = 1;
    eventArray.append(event);
    
    m_bc->registerRewardCallback(this);
    m_bc->getPlayerStatisticsEventService()->triggerStatsEvents(fw.write(eventArray).c_str(), &tr);
    tr.run(m_bc, true);
    
    // sleep a bit... to let threaded comms trigger the reward callback
    TestResult::sleep(1000);
    m_bc->deregisterRewardCallback();

    ASSERT_EQ(m_rewardCallbackHitCount, 1);
}

// Bundles not supported right now
TEST_F(TestBCPlayerStatisticsEvent, RewardHandlerMultipleApiCallsInBundle)
{
    m_rewardCallbackHitCount = 0;
    
    TestResult tr;
    Json::FastWriter fw;
    Json::Value eventArray(Json::arrayValue);

    m_bc->getPlayerStateService()->resetUserState(&tr);
    tr.run(m_bc);
    
    Json::Value event;
    event["eventName"] = "incQuest1Stat";
    event["eventMultiplier"] = 1;
    eventArray.append(event);
    
    m_bc->registerRewardCallback(this);
    m_bc->getPlayerStatisticsEventService()->triggerStatsEvents(fw.write(eventArray).c_str(), &tr);
    
    eventArray.clear();
    event.clear();
    event["eventName"] = "incQuest2Stat";
    event["eventMultiplier"] = 1;
    eventArray.append(event);

    m_bc->getPlayerStatisticsEventService()->triggerStatsEvents(fw.write(eventArray).c_str(), &tr);
    tr.runExpectCount(m_bc, 2, true);
    
    // sleep a bit... to let threaded comms trigger the reward callback
    TestResult::sleep(1000);
    m_bc->deregisterRewardCallback();

    ASSERT_EQ(m_rewardCallbackHitCount, 2);
}

void TestBCPlayerStatisticsEvent::rewardCallback(std::string const & jsonData)
{
    Json::Reader reader;
    Json::Value root;
    reader.parse(jsonData, root);
    Json::StyledWriter writer;
    printf("rewardCallback returned JSON...\n%s", writer.write(root).c_str());
    
    m_rewardCallbackHitCount += root["apiRewards"].size();
}