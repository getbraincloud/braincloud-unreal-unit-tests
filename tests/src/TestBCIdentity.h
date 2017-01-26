#ifndef _TESTBCIDENTITY_H_
#define _TESTBCIDENTITY_H_

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestFixtureBase.h"
#include "json/json.h"

using namespace BrainCloud;

class TestBCIdentity: public TestFixtureBase
{
public:
    TestBCIdentity()
    {
    }

protected:
	void detachPeer();
	void detachParent();
};

#endif
