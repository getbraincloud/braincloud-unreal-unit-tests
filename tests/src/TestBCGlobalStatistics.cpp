#include <vector>

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCGlobalStatistics.h"

using namespace BrainCloud;


TEST_F(TestBCGlobalStatistics, IncrementGloblaStats)
{
    TestResult tr;
    Json::FastWriter fw;
    Json::Value serverData;
    serverData[m_statName] = "RESET";
    std::string serverDataStr = fw.write(serverData);
    
    m_bc->getGlobalStatisticsService()->incrementGlobalGameStat(serverDataStr, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGlobalStatistics, ReadAllGlobalStats)
{
    TestResult tr;
    
    m_bc->getGlobalStatisticsService()->readAllGlobalStats(&tr);
    tr.run(m_bc);
}

TEST_F(TestBCGlobalStatistics, ReadGlobalStatsSubset)
{
    TestResult tr;
    
    std::vector<std::string> stats;
    stats.push_back(m_statName);
    
    m_bc->getGlobalStatisticsService()->readGlobalStatsSubset(stats, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGlobalStatistics, ReadGlobalStatsForCategory)
{
    TestResult tr;
    m_bc->getGlobalStatisticsService()->readGlobalStatsForCategory("Test", &tr);
    tr.run(m_bc);
}

TEST_F(TestBCGlobalStatistics, ProcessStatistics)
{
	TestResult tr;
	Json::FastWriter fw;
	Json::Value serverData;
	serverData[m_statName] = "RESET";
	std::string serverDataStr = fw.write(serverData);

	m_bc->getGlobalStatisticsService()->processStatistics(serverDataStr, &tr);
	tr.run(m_bc);
}
