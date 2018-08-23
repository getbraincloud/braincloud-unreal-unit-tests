#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "braincloud/http_codes.h"
#include "braincloud/reason_codes.h"
#include "TestResult.h"
#include "TestBCPresence.h"

using namespace BrainCloud;

// Lot of expect fail here. This is ok, but we make sure the failed reason 
// is not about a bad or missing argument. We validate that the API is
// written correctly, not that the output from BC is correct. This is
// verified more in depth by use case and JS unit tests.

// TEST_F(TestBCChat, ChannelConnect)
// {
// 	TestResult tr;
// 	m_bc->getChatService()->channelConnect("bad_channel_id", 10, &tr);
// 	tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, INSUFFICIENT_PERMISSIONS);
// }
