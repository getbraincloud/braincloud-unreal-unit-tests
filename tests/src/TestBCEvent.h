#ifndef _TESTBCEVENT_H_
#define _TESTBCEVENT_H_

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "braincloud/BrainCloudTypes.h"
#include "TestFixtureBase.h"
#include "json/json.h"


using namespace BrainCloud;

class TestBCEvent: public TestFixtureBase, public IEventCallback
{
public:
    void eventCallback(std::string const & jsonData);
    
protected:
    void SendDefaultMessage();
    void DeleteIncomingMessage();
    
	std::string m_eventId;
    std::string m_eventDataKey;
    const char * m_eventType;
    
    bool m_didCallback;
    
public:
    TestBCEvent()
    {
        m_eventDataKey = "testEventKey";
        m_eventType = "testEventType";
    }
};

#endif
