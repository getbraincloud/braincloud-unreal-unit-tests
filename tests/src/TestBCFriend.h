#ifndef _TESTBCFRIEND_H_
#define _TESTBCFRIEND_H_

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestFixtureBase.h"
#include "json/json.h"

using namespace BrainCloud;

class TestBCFriend : public TestFixtureBase
{
protected:
    void AddFriends();
};

#endif
