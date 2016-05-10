#ifndef _TESTBCTIME_H_
#define _TESTBCTIME_H_

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestFixtureBase.h"
#include "json/json.h"

using namespace BrainCloud;

class TestBCRedemptionCode: public TestFixtureBase
{
public:
    TestBCRedemptionCode()
    {
        m_lastUsedCodeStatName = "lastCodeUsed";
        m_codeType = "default";
    }
protected:
    const char * m_lastUsedCodeStatName;
    const char * m_codeType;
    
    int64_t getValidCode();
};

#endif
