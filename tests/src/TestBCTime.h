#ifndef _TESTBCTIME_H_
#define _TESTBCTIME_H_

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestFixtureBase.h"
#include "json/json.h"

using namespace BrainCloud;

class TestBCTime: public TestFixtureBase
{
protected:
    int m_serverTime;
};

#endif
