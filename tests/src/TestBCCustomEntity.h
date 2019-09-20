#ifndef _TESTBCCUSTOMENTITY_H_
#define _TESTBCCUSTOMENTITY_H_

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestFixtureBase.h"
#include "json/json.h"

using namespace BrainCloud;

class TestBCCustomEntity : public TestFixtureBase
{
protected:
    std::string m_entityId;
    const char* m_entityType = "athletes";
    
public:

};

#endif
