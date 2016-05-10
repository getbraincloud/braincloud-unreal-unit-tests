#ifndef _TESTBCWRAPPER_H_
#define _TESTBCWRAPPER_H_

#include "TestFixtureBase.h"

using namespace BrainCloud;

class TestBCWrapper : public TestFixtureBase
{
protected:
    virtual bool ShouldSkipAuthenticate() {
        return true;
    }
};
#endif
