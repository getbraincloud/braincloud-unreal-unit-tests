#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCEvent.h"

using namespace BrainCloud;

TEST_F(TestBCEvent, Send)
{
	m_didCallback = false;
	m_bc->registerEventCallback(this);

	SendDefaultMessage();

	EXPECT_TRUE(m_didCallback);

	DeleteIncomingMessage();
	m_bc->deregisterEventCallback();
}

TEST_F(TestBCEvent, DeleteIncoming)
{
	SendDefaultMessage();
	DeleteIncomingMessage();
}

TEST_F(TestBCEvent, UpdateIncoming)
{
	SendDefaultMessage();

	TestResult tr;
	Json::FastWriter fw;
	Json::Value eventData;
	eventData[m_eventDataKey] = "testEventValue";

	m_bc->getEventService()->updateIncomingEventData(m_eventId.c_str(), fw.write(eventData).c_str(), &tr);
	tr.run(m_bc);

	DeleteIncomingMessage();
}

TEST_F(TestBCEvent, GetEvents)
{
	SendDefaultMessage();

	TestResult tr;
	m_bc->getEventService()->getEvents(true, true, &tr);
	tr.run(m_bc);

	DeleteIncomingMessage();
}

void TestBCEvent::SendDefaultMessage()
{
	TestResult tr;
	Json::FastWriter fw;
	Json::Value eventData;
	eventData[m_eventDataKey] = "testEventValue";

	m_bc->getEventService()->sendEvent(GetUser(UserA)->m_profileId, m_eventType, fw.write(eventData).c_str(), &tr);
	tr.run(m_bc);
	m_eventId = tr.m_response["data"]["evId"].asString();
}

void TestBCEvent::DeleteIncomingMessage()
{
	TestResult tr;
	m_bc->getEventService()->deleteIncomingEvent(m_eventId.c_str(), &tr);
	tr.run(m_bc);
}

void TestBCEvent::eventCallback(const std::string &jsonData)
{
	m_didCallback = true;
	printf("%s %s\n", "Events Received:", jsonData.c_str());
}




