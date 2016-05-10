#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCGlobalApp.h"

using namespace BrainCloud;


TEST_F(TestBCGlobalApp, ReadProperties)
{
    TestResult tr;
    
    m_bc->getGlobalAppService()->readProperties(&tr);
    tr.run(m_bc);
}