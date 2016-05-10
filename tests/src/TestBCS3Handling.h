#ifndef _TESTBCS3HANDLING_H_
#define _TESTBCS3HANDLING_H_

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestFixtureBase.h"
#include "json/json.h"

using namespace BrainCloud;

class TestBCS3Handling: public TestFixtureBase
{
protected:
    const char * m_category;
    
public:
    TestBCS3Handling()
    {
        m_category = "test";
    }
};

#endif
