#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCRedemptionCode.h"

using namespace BrainCloud;


TEST_F(TestBCRedemptionCode, RedeemCode)
{
    TestResult tr;
    int64_t code = getValidCode();

    std::stringstream strstream;
    strstream << code;
    std::string codeStr = strstream.str();
    
    m_bc->getRedemptionCodeService()->redeemCode(codeStr.c_str(), m_codeType, NULL, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCRedemptionCode, GetRedeemedCodes)
{
    TestResult tr;
    m_bc->getRedemptionCodeService()->getRedeemedCodes(m_codeType, &tr);
    tr.run(m_bc);
}

int64_t TestBCRedemptionCode::getValidCode()
{
    TestResult tr;
    Json::FastWriter fw;
    Json::Value statData;
    statData[m_lastUsedCodeStatName] = "+1";
    std::string statDataStr = fw.write(statData);
    
    m_bc->getGlobalStatisticsService()->incrementGlobalGameStat(statDataStr.c_str(), &tr);
    tr.run(m_bc);
    
    Json::Value stats = tr.m_response["data"]["statistics"];
    return stats[m_lastUsedCodeStatName].asInt64();
}