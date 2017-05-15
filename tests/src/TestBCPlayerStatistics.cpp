#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCPlayerStatistics.h"

using namespace BrainCloud;

TEST_F(TestBCPlayerStatistics, ReadAllPlayerStats)
{
    TestResult tr;
    m_bc->getPlayerStatisticsService()->readAllUserStats(&tr);
    tr.run(m_bc);
}

TEST_F(TestBCPlayerStatistics, ReadPlayerStatsSubset)
{
    TestResult tr;
    
    std::vector<std::string> stats;
    stats.push_back(m_stat1);
    stats.push_back(m_stat2);

    m_bc->getPlayerStatisticsService()->readUserStatsSubset(stats, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPlayerStatistics, ReadGlobalStatsForCategory)
{
    TestResult tr;
    m_bc->getPlayerStatisticsService()->readUserStatsForCategory("Test", &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPlayerStatistics, IncrementPlayerStats)
{
    TestResult tr;
    Json::FastWriter fw;
    Json::Value stats;
    stats[m_stat1] = "RESET";
    m_bc->getPlayerStatisticsService()->incrementUserStats(fw.write(stats).c_str(), &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPlayerStatistics, ResetAllPlayerStats)
{
    TestResult tr;
    m_bc->getPlayerStatisticsService()->resetAllUserStats(&tr);
    tr.run(m_bc);
}

TEST_F(TestBCPlayerStatistics, IncrementExperiencePoints)
{
    TestResult tr;
    m_bc->getPlayerStatisticsService()->incrementExperiencePoints(10, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPlayerStatistics, GetNextExperienceLevel)
{
    TestResult tr;
    m_bc->getPlayerStatisticsService()->getNextExperienceLevel(&tr);
    tr.run(m_bc);
}

TEST_F(TestBCPlayerStatistics, SetExperiencePoints)
{
    TestResult tr;
    m_bc->getPlayerStatisticsService()->setExperiencePoints(50, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPlayerStatistics, ProcessStatistics)
{
	TestResult tr;
	Json::FastWriter fw;
	Json::Value stats;
	stats[m_stat1] = "RESET";
	m_bc->getPlayerStatisticsService()->processStatistics(fw.write(stats).c_str(), &tr);
	tr.run(m_bc);
}
