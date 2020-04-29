#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCPushNotifications.h"

using namespace BrainCloud;

TEST_F(TestBCPushNotifications, DeregisterPushNotificationDeviceToken)
{
    TestResult tr;
    m_bc->getPushNotificationService()->registerPushNotificationDeviceToken(Platform::iOS, "GARBAGE_TOKEN", &tr);
    tr.run(m_bc);

    tr.reset();
    m_bc->getPushNotificationService()->deregisterPushNotificationDeviceToken(Platform::iOS, "GARBAGE_TOKEN", &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPushNotifications, DeregisterAllPushNotificationDeviceTokens)
{
    TestResult tr;
    m_bc->getPushNotificationService()->deregisterAllPushNotificationDeviceTokens(&tr);
    tr.run(m_bc);
}

TEST_F(TestBCPushNotifications, RegisterPushNotificationDeviceToken)
{
    TestResult tr;
    m_bc->getPushNotificationService()->registerPushNotificationDeviceToken(Platform::iOS, "GARBAGE_TOKEN", &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPushNotifications, SendSimplePushNotification)
{
    TestResult tr;
    m_bc->getPushNotificationService()->sendSimplePushNotification(GetUser(UserA)->m_profileId, "GARBAGE_TOKEN", &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPushNotifications, SendRichPushNotification)
{
    TestResult tr;
    m_bc->getPushNotificationService()->sendRichPushNotification(GetUser(UserA)->m_profileId, 1, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPushNotifications, RunParentScript)
{
    TestResult tr;
    Json::FastWriter fw;
    Json::Value scriptData;
    scriptData["1"] = GetUser(UserA)->m_id;

    m_bc->getPushNotificationService()->sendRichPushNotificationWithParams(GetUser(UserA)->m_profileId, 1, fw.write(scriptData).c_str(), &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPushNotifications, SendTemplatedPushNotificationToGroup)
{
    TestResult tr;
    m_bc->getGroupService()->createGroup("testGroup", "test", false, "", "", "", "", &tr);
    tr.run(m_bc);

    std::string groupId = tr.m_response["data"]["groupId"].asString();

    Json::FastWriter fw;
    Json::Value scriptData;
    scriptData["1"] = GetUser(UserA)->m_id;

    m_bc->getPushNotificationService()->sendTemplatedPushNotificationToGroup(groupId.c_str(), 1, fw.write(scriptData), &tr);
    tr.run(m_bc);

    m_bc->getGroupService()->deleteGroup(groupId.c_str(), -1, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPushNotifications, SendNormalizedPushNotificationToGroup)
{
    TestResult tr;
    m_bc->getGroupService()->createGroup("testGroup", "test", false, "", "", "", "", &tr);
    tr.run(m_bc);

    std::string groupId = tr.m_response["data"]["groupId"].asString();

    Json::FastWriter fw;
    Json::Value scriptData;
    scriptData["body"] = "asdf";
    scriptData["title"] = "asdf";

    m_bc->getPushNotificationService()->sendNormalizedPushNotificationToGroup(groupId.c_str(), fw.write(scriptData), "", &tr);
    tr.run(m_bc);

    m_bc->getGroupService()->deleteGroup(groupId.c_str(), -1, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPushNotifications, ScheduleRichPushNotificationUTC)
{
    TestResult tr;

    Json::FastWriter fw;
    Json::Value data;
    data["body"] = "asdf";
    data["title"] = "asdf";

    uint64_t startTime = 0;

    m_bc->getPushNotificationService()->scheduleRichPushNotificationUTC(GetUser(UserA)->m_profileId, 1, fw.write(data), startTime, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPushNotifications, ScheduleNormalizedPushNotificationUTC)
{
    TestResult tr;

    Json::FastWriter fw;
    Json::Value data;
    data["body"] = "asdf";
    data["title"] = "asdf";

    uint64_t startTime = 0;

    m_bc->getPushNotificationService()->scheduleNormalizedPushNotificationUTC(GetUser(UserA)->m_profileId, fw.write(data), "", startTime, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPushNotifications, ScheduleRichPushNotificationMinutes)
{
    TestResult tr;

    Json::FastWriter fw;
    Json::Value data;
    data["body"] = "asdf";
    data["title"] = "asdf";

    int32_t minutesFromNow = 0;

    m_bc->getPushNotificationService()->scheduleRichPushNotificationMinutes(GetUser(UserA)->m_profileId, 1, fw.write(data), minutesFromNow, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPushNotifications, ScheduleRawPushNotificationUTC)
{
    TestResult tr;

    std::string fcmContent =  "{ \"notification\": { \"body\": \"content of message\", \"title\": \"message title\" }, \"data\": { \"customfield1\": \"customValue1\", \"customfield2\": \"customValue2\" }, \"priority\": \"normal\" }";
    std::string iosContent = "{ \"aps\": { \"alert\": { \"body\": \"content of message\", \"title\": \"message title\" }, \"badge\": 0, \"sound\": \"gggg\" } }";
    std::string facebookContent = "{\"template\": \"content of message\"}";

    uint64_t startTime = 0;

    m_bc->getPushNotificationService()->scheduleRawPushNotificationUTC(GetUser(UserA)->m_profileId, fcmContent, iosContent, facebookContent, startTime, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPushNotifications, ScheduleRawPushNotificationMinutes)
{
    TestResult tr;

    std::string fcmContent =  "{ \"notification\": { \"body\": \"content of message\", \"title\": \"message title\" }, \"data\": { \"customfield1\": \"customValue1\", \"customfield2\": \"customValue2\" }, \"priority\": \"normal\" }";
    std::string iosContent = "{ \"aps\": { \"alert\": { \"body\": \"content of message\", \"title\": \"message title\" }, \"badge\": 0, \"sound\": \"gggg\" } }";
    std::string facebookContent = "{\"template\": \"content of message\"}";

    int32_t minutesFromNow = 0;

    m_bc->getPushNotificationService()->scheduleRawPushNotificationMinutes(GetUser(UserA)->m_profileId, fcmContent, iosContent, facebookContent, minutesFromNow, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPushNotifications, SendRawPushNotification)
{
    TestResult tr;

    std::string fcmContent =  "{ \"notification\": { \"body\": \"content of message\", \"title\": \"message title\" }, \"data\": { \"customfield1\": \"customValue1\", \"customfield2\": \"customValue2\" }, \"priority\": \"normal\" }";
    std::string iosContent = "{ \"aps\": { \"alert\": { \"body\": \"content of message\", \"title\": \"message title\" }, \"badge\": 0, \"sound\": \"gggg\" } }";
    std::string facebookContent = "{\"template\": \"content of message\"}";

    m_bc->getPushNotificationService()->sendRawPushNotification(GetUser(UserA)->m_profileId, fcmContent, iosContent, facebookContent, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPushNotifications, SendRawPushNotificationBatch)
{
    TestResult tr;

    std::vector<std::string> profileIds;
    profileIds.push_back(GetUser(UserA)->m_profileId);
    profileIds.push_back(GetUser(UserB)->m_profileId);

    std::string fcmContent =  "{ \"notification\": { \"body\": \"content of message\", \"title\": \"message title\" }, \"data\": { \"customfield1\": \"customValue1\", \"customfield2\": \"customValue2\" }, \"priority\": \"normal\" }";
    std::string iosContent = "{ \"aps\": { \"alert\": { \"body\": \"content of message\", \"title\": \"message title\" }, \"badge\": 0, \"sound\": \"gggg\" } }";
    std::string facebookContent = "{\"template\": \"content of message\"}";

    m_bc->getPushNotificationService()->sendRawPushNotificationBatch(profileIds, fcmContent, iosContent, facebookContent, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPushNotifications, SendRawPushNotificationToGroup)
{
    TestResult tr;
    m_bc->getGroupService()->createGroup("testGroup", "test", false, "", "", "", "", &tr);
    tr.run(m_bc);

    std::string groupId = tr.m_response["data"]["groupId"].asString();


    std::string fcmContent =  "{ \"notification\": { \"body\": \"content of message\", \"title\": \"message title\" }, \"data\": { \"customfield1\": \"customValue1\", \"customfield2\": \"customValue2\" }, \"priority\": \"normal\" }";
    std::string iosContent = "{ \"aps\": { \"alert\": { \"body\": \"content of message\", \"title\": \"message title\" }, \"badge\": 0, \"sound\": \"gggg\" } }";
    std::string facebookContent = "{\"template\": \"content of message\"}";

    m_bc->getPushNotificationService()->sendRawPushNotificationToGroup(groupId.c_str(), fcmContent, iosContent, facebookContent, &tr);
    tr.run(m_bc);

    m_bc->getGroupService()->deleteGroup(groupId.c_str(), -1, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCPushNotifications, SendNormalizedPushNotification)
{
	TestResult tr;

	Json::FastWriter fw;
	Json::Value data;
	data["body"] = "asdf";
	data["title"] = "asdf";

	m_bc->getPushNotificationService()->sendNormalizedPushNotification(GetUser(UserA)->m_profileId, fw.write(data), "", &tr);
	tr.run(m_bc);
}

TEST_F(TestBCPushNotifications, SendNormalizedPushNotificationBatch)
{
	TestResult tr;

	std::vector<std::string> profileIds;
	profileIds.push_back(GetUser(UserA)->m_profileId);
	profileIds.push_back(GetUser(UserB)->m_profileId);

	Json::FastWriter fw;
	Json::Value data;
	data["body"] = "asdf";
	data["title"] = "asdf";

	m_bc->getPushNotificationService()->sendNormalizedPushNotificationBatch(profileIds, fw.write(data), "", &tr);
	tr.run(m_bc);
}