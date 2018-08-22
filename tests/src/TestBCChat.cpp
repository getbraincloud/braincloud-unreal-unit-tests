#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "braincloud/http_codes.h"
#include "braincloud/reason_codes.h"
#include "TestResult.h"
#include "TestBCChat.h"

using namespace BrainCloud;

// Lot of expect fail here. This is ok, but we make sure the failed reason 
// is not about a bad or missing argument. We validate that the API is
// written correctly, not that the output from BC is correct. This is
// verified more in depth by use case and JS unit tests.

TEST_F(TestBCChat, ChannelConnect)
{
	TestResult tr;
	m_bc->getChatService()->channelConnect("bad_channel_id", 10, &tr);
	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, INSUFFICIENT_PERMISSIONS);
}

TEST_F(TestBCChat, ChannelDisconnect)
{
	TestResult tr;
	m_bc->getChatService()->channelDisconnect("bad_channel_id", &tr);
	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, INSUFFICIENT_PERMISSIONS);
}

TEST_F(TestBCChat, DeleteChatMessage)
{
	TestResult tr;
	m_bc->getChatService()->deleteChatMessage("bad_channel_id", "123456", 1, &tr);
	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, INSUFFICIENT_PERMISSIONS);
}

TEST_F(TestBCChat, GetChannelId)
{
	TestResult tr;
	m_bc->getChatService()->getChannelId("gl", "valid", &tr);
	tr.run(m_bc);
}

TEST_F(TestBCChat, GetChannelInfo)
{
	TestResult tr;
	m_bc->getChatService()->getChannelInfo("bad_channel_id", &tr);
	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, INSUFFICIENT_PERMISSIONS);
}

TEST_F(TestBCChat, GetChatMessage)
{
	TestResult tr;
	m_bc->getChatService()->getChatMessage("bad_channel_id", "12345", &tr);
	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, INSUFFICIENT_PERMISSIONS);
}

TEST_F(TestBCChat, GetRecentChatMessages)
{
	TestResult tr;
	m_bc->getChatService()->getRecentChatMessages("bad_channel_id", 10, &tr);
	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, INSUFFICIENT_PERMISSIONS);
}

TEST_F(TestBCChat, GetSubscribedChannels)
{
	TestResult tr;
	m_bc->getChatService()->getSubscribedChannels("gl", &tr);
	tr.run(m_bc);
}

TEST_F(TestBCChat, PostChatMessage)
{
	TestResult tr;
	m_bc->getChatService()->postChatMessage("bad_channel_id", "{\"text\":\"test message\"}", true, &tr);
	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, INSUFFICIENT_PERMISSIONS);
}

TEST_F(TestBCChat, PostChatMessageSimple)
{
	TestResult tr;
	m_bc->getChatService()->postChatMessageSimple("bad_channel_id", "test message", true, &tr);
	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, INSUFFICIENT_PERMISSIONS);
}

TEST_F(TestBCChat, UpdateChatMessage)
{
	TestResult tr;
	m_bc->getChatService()->updateChatMessage("bad_channel_id", "12345", 1, "{\"text\":\"edited message\"}", &tr);
	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, INSUFFICIENT_PERMISSIONS);
}
