#ifndef _TESTBCSCRIPT_H_
#define _TESTBCSCRIPT_H_

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestFixtureBase.h"
#include "json/json.h"

using namespace BrainCloud;

class TestBCScript: public TestFixtureBase
{
public:
    TestBCScript()
    {
        m_scriptName = "testScript";
		m_peerScriptName = "TestPeerScriptPublic";
    }
protected:
    const char* m_scriptName;
	const char* m_peerScriptName;
};

#endif
