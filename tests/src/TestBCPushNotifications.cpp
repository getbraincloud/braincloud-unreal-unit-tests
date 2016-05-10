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

TEST_F(TestBCPushNotifications, sendSimplePushNotification)
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