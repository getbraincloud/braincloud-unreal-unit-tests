#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCProfanity.h"

using namespace BrainCloud;


TEST_F(TestBCProfanity, ProfanityCheck)
{
    TestResult tr;
    m_bc->getProfanityService()->profanityCheck("shitbird fly away", "en", true, true, true, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCProfanity, ProfanityReplaceText)
{
    TestResult tr;
    m_bc->getProfanityService()->profanityReplaceText("shitbird fly away", "*", "en", false, false, false, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCProfanity, ProfanityIdentifyBadWords)
{
    TestResult tr;
    m_bc->getProfanityService()->profanityIdentifyBadWords("shitbird fly away", "en,fr", true, false, false, &tr);
    tr.run(m_bc);
}
