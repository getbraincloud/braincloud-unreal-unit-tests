#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "braincloud/http_codes.h"
#include "braincloud/reason_codes.h"
#include "TestResult.h"
#include "TestBCMessaging.h"

using namespace BrainCloud;

// Lot of expect fail here. This is ok, but we make sure the failed reason 
// is not about a bad or missing argument. We validate that the API is
// written correctly, not that the output from BC is correct. This is
// verified more in depth by use case and JS unit tests.

TEST_F(TestBCMessaging, DeleteMessages)
{
	TestResult tr;

	std::vector<std::string> msgIds = {"invalidMsgId"};
	m_bc->getMessagingService()->deleteMessages("inbox", msgIds, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCMessaging, GetMessageboxes)
{
	TestResult tr;

	m_bc->getMessagingService()->getMessageboxes(&tr);
	tr.run(m_bc);
}

TEST_F(TestBCMessaging, GetMessageCounts)
{
	TestResult tr;

	m_bc->getMessagingService()->getMessageCounts(&tr);
	tr.run(m_bc);
}

TEST_F(TestBCMessaging, GetMessages)
{
	TestResult tr;

	std::vector<std::string> msgIds = {"invalidMsgId"};
	m_bc->getMessagingService()->getMessages("inbox", msgIds, true, &tr);
	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, MESSAGE_NOT_FOUND);
}

TEST_F(TestBCMessaging, GetMessagesPage)
{
	TestResult tr;

	auto profileId = m_bc->getAuthenticationService()->getProfileId();

	m_bc->getMessagingService()->getMessagesPage("{\"pagination\":{\"rowsPerPage\":10,\"pageNumber\":1},\"searchCriteria\":{\"$or\":[{\"message.message.from\":\"" + profileId + "\"},{\"message.message.to\":\"" + profileId + "\"}]},\"sortCriteria\":{\"mbCr\":1,\"mbUp\":-1}}", &tr);
	tr.run(m_bc);
}

TEST_F(TestBCMessaging, GetMessagesPageOffset)
{
	TestResult tr;

	m_bc->getMessagingService()->getMessagesPageOffset("invalidContext", 1, &tr);
	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, DECODE_CONTEXT);
}

TEST_F(TestBCMessaging, SendMessage)
{
	TestResult tr;
	
	std::string contentJson = "{\"subject\": \"Chat and messaging features are here!\", \"text\": \"hi.\"}";

	auto profileId = m_bc->getAuthenticationService()->getProfileId();
	std::vector<std::string> toProfileIds = {profileId};
	m_bc->getMessagingService()->sendMessage(toProfileIds, contentJson, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCMessaging, SendMessageSimple)
{
	TestResult tr;
	auto profileId = m_bc->getAuthenticationService()->getProfileId();

	std::vector<std::string> toProfileIds = {profileId};
	m_bc->getMessagingService()->sendMessageSimple(toProfileIds, "This is text", &tr);
	tr.run(m_bc);
}

TEST_F(TestBCMessaging, MarkMessagesRead)
{
	TestResult tr;
	auto profileId = m_bc->getAuthenticationService()->getProfileId();

	std::vector<std::string> msgIds = {"invalidMsgId"};
	m_bc->getMessagingService()->markMessagesRead("inbox", msgIds, &tr);
	tr.run(m_bc);
}
