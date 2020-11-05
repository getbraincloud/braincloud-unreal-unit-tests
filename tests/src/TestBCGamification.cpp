#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCGamification.h"

using namespace BrainCloud;

TestBCGamification::TestBCGamification()
{
    m_achievements.push_back("testAchievement01");
    m_achievements.push_back("testAchievement02");
    
    m_userStatsCategory = "playerStats";
    m_milestoneCategory = "Experience";
    m_milestoneId= "2";
    m_milestoneIds.push_back(m_milestoneId);
    m_questCategory= "Experience";
}

TEST_F(TestBCGamification, AwardAchievements)
{
    TestResult tr;
    m_bc->getGamificationService()->awardAchievements(m_achievements, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGamification, ReadAchievedAchievments)
{
    TestResult tr;
    m_bc->getGamificationService()->readAchievedAchievements(true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGamification, ReadAchievments)
{
    TestResult tr;
    m_bc->getGamificationService()->readAchievements(true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGamification, ReadCompletedMilestones)
{
    TestResult tr;
    m_bc->getGamificationService()->readCompletedMilestones(true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGamification, ReadInProgressMilestones)
{
    TestResult tr;
    m_bc->getGamificationService()->readInProgressMilestones(true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGamification, ReadMilestones)
{
    TestResult tr;
    m_bc->getGamificationService()->readMilestones(true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGamification, ReadMilestonesByCategory)
{
    TestResult tr;
    m_bc->getGamificationService()->readMilestonesByCategory(m_milestoneCategory, true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGamification, ReadCompletedQuests)
{
    TestResult tr;
    m_bc->getGamificationService()->readCompletedQuests(true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGamification, ReadNotStartedQuests)
{
    TestResult tr;
    m_bc->getGamificationService()->readNotStartedQuests(true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGamification, ReadInProgressQuests)
{
    TestResult tr;
    m_bc->getGamificationService()->readInProgressQuests(true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGamification, ReadQuests)
{
    TestResult tr;
    m_bc->getGamificationService()->readQuests(true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGamification, ReadQuestsByCategory)
{
    TestResult tr;
    m_bc->getGamificationService()->readQuestsByCategory(m_questCategory, true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGamification, ReadQuestsWithBasicPercentage)
{
    TestResult tr;
    m_bc->getGamificationService()->readQuestsWithBasicPercentage(true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGamification, ReadQuestsWithComplexPercentage)
{
    TestResult tr;
    m_bc->getGamificationService()->readQuestsWithComplexPercentage(true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGamification, ReadQuestsWithSatus)
{
    TestResult tr;
    m_bc->getGamificationService()->readQuestsWithStatus(true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGamification, ReadAll)
{
    TestResult tr;
    m_bc->getGamificationService()->readAllGamification(true, &tr);
    tr.run(m_bc);
}

