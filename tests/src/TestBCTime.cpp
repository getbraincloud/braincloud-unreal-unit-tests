#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCTime.h"

using namespace BrainCloud;


TEST_F(TestBCTime, ReadServerTime)
{
    TestResult tr;

    m_bc->getTimeService()->readServerTime(&tr);
    tr.run(m_bc);
}