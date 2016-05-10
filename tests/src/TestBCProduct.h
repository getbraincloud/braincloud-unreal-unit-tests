#ifndef _TESTBCPRODUCT_H_
#define _TESTBCPRODUCT_H_

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestFixtureBase.h"
#include "json/json.h"

using namespace BrainCloud;

class TestBCProduct: public TestFixtureBase
{
protected:
    const char * m_currencyType;
    const char * m_platform;
    const char * m_productCategory;
    
public:
    TestBCProduct()
    {
        m_currencyType = "credits";
        m_platform = "windows";
        m_productCategory = "Test";
    }
};

#endif
