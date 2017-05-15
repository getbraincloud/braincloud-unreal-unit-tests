#include <stdlib.h>
#include "TestBCComms.h"


// Note that TestBCAuth skips the normal authenticate setup provided by TestFixtureBase
// All TestBCAuth test methods must perform their own authenticate + logout

TEST_F(TestBCComms, BadUrl)
{
	TestResult tr;
	m_bc->initialize("https://internal-failunittest.braincloudservers.com", "123", "123", "1.0.0");
	// pj - don't use test user as auth will fail due to bogus initialize above
	m_bc->getAuthenticationService()->authenticateUniversal("abc", "123", true, &tr);
	tr.runExpectFail(m_bc, HTTP_CLIENT_NETWORK_ERROR, CLIENT_NETWORK_ERROR_TIMEOUT);

	m_bc->resetCommunication();
}

TEST_F(TestBCComms, BadEndPoint)
{
	TestResult tr;
	m_bc->initialize("https://internal.braincloudservers.com/failunittest", "123", "123", "1.0.0");
	// pj - don't use test user as auth will fail due to bogus initialize above
	m_bc->getAuthenticationService()->authenticateUniversal("abc", "123", true, &tr);
	tr.runExpectFail(m_bc, HTTP_CLIENT_NETWORK_ERROR, CLIENT_NETWORK_ERROR_TIMEOUT);

	m_bc->resetCommunication();
}

TEST_F(TestBCComms, BadSecret)
{
	TestResult tr;
	m_bc->initialize("https://internal.braincloudservers.com/dispatcherv2", "fail-unit-test", "10170", "1.0.0");
	// pj - don't use test user as auth will fail due to bogus initialize above
	m_bc->getAuthenticationService()->authenticateUniversal("abc", "123", true, &tr);
	tr.runExpectFail(m_bc, HTTP_FORBIDDEN, -1);

	m_bc->resetCommunication();
}

TEST_F(TestBCComms, BadPacketId)
{
	// not sure how to do this one
}

TEST_F(TestBCComms, Heartbeat)
{
	//speed up heartbeat
	m_bc->setHeartbeatInterval(30 * 1000);

	TestResult tr;
	m_bc->getAuthenticationService()->authenticateUniversal(GetUser(UserA)->m_id, GetUser(UserA)->m_password, true, &tr);

	if (tr.run(m_bc))
	{
		printf("\nWaiting for session to timeout...\n");
		sleepForMillisAndRunCallbacks(62 * 1000);
	}

	m_bc->getTimeService()->readServerTime(&tr);
	tr.run(m_bc);

	ASSERT_TRUE(m_bc->isAuthenticated());

	m_bc->setHeartbeatInterval(0);
	m_bc->resetCommunication();
}

TEST_F(TestBCComms, HeartbeatStops)
{
	//delay heartbeat
	m_bc->setHeartbeatInterval(1200 * 1000);

	TestResult tr;
	m_bc->getAuthenticationService()->authenticateUniversal(GetUser(UserA)->m_id, GetUser(UserA)->m_password, true, &tr);

	if (tr.run(m_bc))
	{
		printf("\nWaiting for session to timeout...\n");
		sleepForMillisAndRunCallbacks(62 * 1000);
	}

	m_bc->getTimeService()->readServerTime(&tr);
	tr.runExpectFail(m_bc, HTTP_FORBIDDEN, PLAYER_SESSION_EXPIRED);

	ASSERT_FALSE(m_bc->isAuthenticated());

	//This should trigger local session error handling in comms
	m_bc->getTimeService()->readServerTime(&tr);
	tr.runExpectFail(m_bc, HTTP_FORBIDDEN, PLAYER_SESSION_EXPIRED);

	m_bc->setHeartbeatInterval(0);
	m_bc->resetCommunication();
}

TEST_F(TestBCComms, SessionErrorReturn)
{
	TestResult tr;
	m_bc->getAuthenticationService()->authenticateUniversal(GetUser(UserA)->m_id, GetUser(UserA)->m_password, true, &tr);
	tr.run(m_bc);

	m_bc->getTimeService()->readServerTime(&tr);
	tr.run(m_bc);

	m_bc->getPlayerStateService()->logout(&tr);
	tr.run(m_bc);

	m_bc->getTimeService()->readServerTime(&tr);
	m_bc->getTimeService()->readServerTime(&tr);
	m_bc->getTimeService()->readServerTime(&tr);
	m_bc->getTimeService()->readServerTime(&tr);
	m_bc->getTimeService()->readServerTime(&tr);
	tr.runExpectFail(m_bc, HTTP_FORBIDDEN, NO_SESSION);

	m_bc->resetCommunication();
}

// these are for dev testing not automated build machine stuff...
/*
TEST_F(TestBCComms, devBadAuthNoRetry)
{
TestResult tr;
m_bc->initialize("http://localhost:3099", "", "123", "1.0.0", "", "");
m_bc->getAuthenticationService()->authenticateUniversal("abc", "123", true, &tr);
tr.runExpectFail(m_bc, -1, -1);

// this should always succeed but helps devs verify that only one auth packet gets sent
m_bc->resetCommunication();
}

TEST_F(TestBCComms, devBad503)
{
// this test assumes you're running a server that returns 503
TestResult tr;
m_bc->initialize("http://207.181.118.113:5432", "", "123", "1.0.0", "", "");
// don't authenticate as we want retries to happen
m_bc->getPlayerStateService()->getAttributes(&tr);
tr.runExpectFail(m_bc, HTTP_CUSTOM, CLIENT_NETWORK_ERROR_TIMEOUT);

m_bc->resetCommunication();
}
*/

TEST_F(TestBCComms, ErrorCallback)
{
	TestResult tr;
	m_bc->initialize(m_serverUrl.c_str(), m_secret.c_str(), m_appId.c_str(), m_version.c_str());

	m_bc->getEntityService()->createEntity("type", "", "", &tr);
	tr.runExpectFail(m_bc, -1, -1);
	printf("%s\n", tr.m_statusMessage.c_str());
	ASSERT_TRUE(tr.m_statusMessage[0] == '{');

	tr.reset();
	m_bc->setOldStyleStatusMessageErrorCallback(true);
	m_bc->getEntityService()->createEntity("type", "", "", &tr);
	tr.runExpectFail(m_bc, -1, -1);
	printf("%s\n", tr.m_statusMessage.c_str());
	ASSERT_FALSE(tr.m_statusMessage[0] == '{');

	m_bc->initialize("http://localhost:5432", m_secret.c_str(), m_appId.c_str(), m_version.c_str());

	tr.reset();
	m_bc->setOldStyleStatusMessageErrorCallback(false);
	m_bc->getEntityService()->createEntity("type", "", "", &tr);
	tr.runExpectFail(m_bc, -1, -1);
	printf("%s\n", tr.m_statusMessage.c_str());
	ASSERT_TRUE(tr.m_statusMessage[0] == '{');

	tr.reset();
	m_bc->setOldStyleStatusMessageErrorCallback(true);
	m_bc->getEntityService()->createEntity("type", "", "", &tr);
	tr.runExpectFail(m_bc, -1, -1);
	printf("%s\n", tr.m_statusMessage.c_str());
	ASSERT_FALSE(tr.m_statusMessage[0] == '{');

	m_bc->setOldStyleStatusMessageErrorCallback(false);
	m_bc->resetCommunication();
}

TEST_F(TestBCComms, GlobalErrorCallback)
{
	int globalErrorCount = 0;
	TestResult tr;

	m_bc->registerGlobalErrorCallback(&tr);

	m_bc->getTimeService()->readServerTime(&tr);
	tr.runExpectFail(m_bc, HTTP_FORBIDDEN, NO_SESSION);
	globalErrorCount += tr.m_globalErrorCount;

	m_bc->getTimeService()->readServerTime(&tr);
	tr.runExpectFail(m_bc, HTTP_FORBIDDEN, NO_SESSION);
	globalErrorCount += tr.m_globalErrorCount;

	m_bc->getTimeService()->readServerTime(&tr);
	tr.runExpectFail(m_bc, HTTP_FORBIDDEN, NO_SESSION);
	globalErrorCount += tr.m_globalErrorCount;

	m_bc->deregisterGlobalErrorCallback();
	m_bc->resetCommunication();

	ASSERT_EQ(3, globalErrorCount);
}

TEST_F(TestBCComms, ResetCommsDuringHTTPRequest)
{
	TestResult tr;
	m_bc->getAuthenticationService()->authenticateUniversal(GetUser(UserA)->m_id, GetUser(UserA)->m_password, true, &tr);
	m_bc->runCallbacks();
	sleepForMillis(10);
	m_bc->runCallbacks();

	m_bc->resetCommunication();
}

TEST_F(TestBCComms, 202IsErrorFlag)
{
	TestResult tr;
	m_bc->getAuthenticationService()->setProfileId(GetUser(UserB)->m_profileId);

	m_bc->getAuthenticationService()->authenticateUniversal(GetUser(UserA)->m_id, GetUser(UserA)->m_password, true, &tr);
	tr.runExpectFail(m_bc, 202, SWITCHING_PROFILES);

	m_bc->setErrorCallbackOn202Status(false);
	m_bc->getAuthenticationService()->authenticateUniversal(GetUser(UserA)->m_id, GetUser(UserA)->m_password, true, &tr);
	tr.run(m_bc);

	m_bc->setErrorCallbackOn202Status(true);
	m_bc->resetCommunication();
}

TEST_F(TestBCComms, MessageCache)
{
	TestResult tr;
	m_bc->initialize("https://internal.braincloudservers.com/failunittest", "abc", "123", "1.0.0");
	m_bc->registerGlobalErrorCallback(&tr);
	m_bc->registerNetworkErrorCallback(&tr);
	m_bc->enableNetworkErrorMessageCaching(true);
	m_bc->enableLogging(true);

	std::vector<int> packetTimeouts;
	packetTimeouts.push_back(1);
	packetTimeouts.push_back(1);
	packetTimeouts.push_back(1);
	m_bc->setPacketTimeouts(packetTimeouts);

	//tr.setMaxWaitSecs(10);

	int networkErrorCount = 0;
	int globalErrorCount = 0;

	// pj - don't use test user as auth will fail due to bogus initialize above
	m_bc->getAuthenticationService()->authenticateUniversal("abc", "123", true, &tr);
	tr.runExpectFail(m_bc, HTTP_CLIENT_NETWORK_ERROR, CLIENT_NETWORK_ERROR_TIMEOUT);
	networkErrorCount += tr.m_networkErrorCount;

	m_bc->retryCachedMessages();
	tr.runExpectFail(m_bc, HTTP_CLIENT_NETWORK_ERROR, CLIENT_NETWORK_ERROR_TIMEOUT);
	networkErrorCount += tr.m_networkErrorCount;

	m_bc->flushCachedMessages(true);
	m_bc->runCallbacks();
	globalErrorCount += tr.m_globalErrorCount;

	m_bc->resetCommunication();
	m_bc->setPacketTimeoutsToDefault();
	m_bc->enableNetworkErrorMessageCaching(false);
	m_bc->deregisterNetworkErrorCallback();
	m_bc->deregisterGlobalErrorCallback();

	ASSERT_EQ(2, networkErrorCount);
	ASSERT_EQ(1, tr.m_globalErrorCount);
}


TEST_F(TestBCComms, MessageBundleMarker)
{
	TestResult tr;
	m_bc->initialize(m_serverUrl.c_str(), m_secret.c_str(), m_appId.c_str(), m_version.c_str());

	m_bc->getAuthenticationService()->authenticateUniversal(GetUser(UserA)->m_id, GetUser(UserA)->m_password, true, &tr);
	m_bc->insertEndOfMessageBundleMarker();

    m_bc->getPlayerStatisticsService()->readAllUserStats(&tr);
	m_bc->insertEndOfMessageBundleMarker();

    m_bc->getPlayerStatisticsService()->readAllUserStats(&tr);
    m_bc->getPlayerStatisticsService()->readAllUserStats(&tr);
	m_bc->insertEndOfMessageBundleMarker();

	tr.run(m_bc);
	tr.run(m_bc);
	tr.run(m_bc);
}

//TEST_F(TestBCComms, KillSwitch)
//{
//	TestResult tr;
//	m_bc->initialize(m_serverUrl.c_str(), m_secret.c_str(), m_appId.c_str(), m_version.c_str());
//
//	m_bc->getAuthenticationService()->authenticateUniversal(GetUser(UserA)->m_id, GetUser(UserA)->m_password, true, &tr);
//	tr.run(m_bc);
//
//	for (int i = 0; i < 12; ++i)
//	{
//		m_bc->getEntityService()->updateEntity(
//			"FAIL",
//			"FAIL",
//			"{ \"test\": 1 }",
//			"{ \"test\": 1 }",
//			-1, &tr);
//		tr.run(m_bc, true);
//	}
//
//	m_bc->getTimeService()->readServerTime(&tr);
//	tr.runExpectFail(m_bc, 900, CLIENT_DISABLED);
//}

void TestBCComms::sleepForMillis(int millis)
{
#if __cplusplus >= 201103L
	auto sleep = std::chrono::milliseconds(millis);
	std::this_thread::sleep_for(sleep);
#elif WIN32
	Sleep(millis);
#else
	usleep(millis * 1000);
#endif
}

void TestBCComms::sleepForMillisAndRunCallbacks(int millis)
{
	int slice = 500;
	while (millis > 0)
	{
#if __cplusplus >= 201103L
		auto sleep = std::chrono::milliseconds(slice);
		std::this_thread::sleep_for(sleep);
#elif WIN32
		Sleep(slice);
#else
		usleep(slice * 1000);
#endif
		millis -= slice;
		BrainCloud::BrainCloudClient::getInstance()->runCallbacks();
	}
}

