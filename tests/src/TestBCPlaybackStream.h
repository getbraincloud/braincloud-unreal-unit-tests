#ifndef _TESTBCPLAYBACKSTREAM_H_
#define _TESTBCPLAYBACKSTREAM_H_

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestFixtureBase.h"
#include "json/json.h"

using namespace BrainCloud;

class TestBCPlaybackStream: public TestFixtureBase
{
protected:
    std::string m_streamId;
    void StartStream();
    void EndStream();
};

#endif
