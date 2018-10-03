#ifndef _TESTGUID_H_
#define _TESTGUID_H_

#include "TestFixtureBase.h"

using namespace BrainCloud;

class TestGUID : public TestFixtureBase
{
protected:
    virtual bool ShouldSkipAuthenticate() {
        return true;
    }
};

#endif
