#ifndef _TESTBCPLAYERSTATE_H_
#define _TESTBCPLAYERSTATE_H_

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestFixtureBase.h"
#include "json/json.h"

using namespace BrainCloud;

class TestBCPlayerState: public TestFixtureBase
{
protected:
    virtual bool ShouldSkipAuthenticate() {
        return true;
    }
    
    void Authenticate();
    void Logout();    
};

#endif
