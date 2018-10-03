#ifndef _TESTBCCOMMS_H_
#define _TESTBCCOMMS_H_

#include "TestFixtureBase.h"
#include "braincloud/IGlobalErrorCallback.h"

using namespace BrainCloud;

class TestBCComms : public TestFixtureBase
{
protected:
    virtual bool ShouldSkipAuthenticate() {
        return true;
    }
    
    void sleepForMillis(int millis);
    void sleepForMillisAndRunCallbacks(int millis);
};

class TestBCCommsWithAuth : public TestFixtureBase
{
};

#endif
