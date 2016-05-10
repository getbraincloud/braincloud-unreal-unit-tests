#ifndef _TESTBCONEWAYMATCH_H_
#define _TESTBCONEWAYMATCH_H_

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestFixtureBase.h"
#include "json/json.h"

using namespace BrainCloud;

class TestBCOneWayMatch: public TestFixtureBase
{
protected:
    std::string m_streamId;
    void StartMatch();
    void CancelMatch();
};

#endif
