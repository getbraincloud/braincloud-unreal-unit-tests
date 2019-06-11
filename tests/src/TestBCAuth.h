#ifndef _TESTBCAUTH_H_
#define _TESTBCAUTH_H_

#include "TestFixtureBase.h"

using namespace BrainCloud;

class TestBCAuth : public TestFixtureBase
{
protected:
    virtual bool ShouldSkipAuthenticate() {
        return true;
    }

    void AuthEmailPassword();
    
    int mostRecentPacket = 1000000;
    int secondMostRecentPacket = 1000000;
};

#endif
