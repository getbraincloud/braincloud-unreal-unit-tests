#ifndef _TESTFIXTUREBASE_H_
#define _TESTFIXTUREBASE_H_

#include <stdlib.h>
#include <vector>
#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestUser.h"

using namespace BrainCloud;

class TestFixtureBase : public testing::Test
{
#define ENABLE_SETUP_TEARDOWN_LOGGING false

public:
    TestFixtureBase() {}

protected:
    BrainCloudClient * m_bc;

    std::string m_serverUrl;
    std::string m_appId;
    std::string m_secret;
    std::string m_version;

    std::string m_parentLevelName;
    std::string m_childAppId;

    virtual void SetUp();
    virtual void TearDown();
    virtual bool ShouldSkipAuthenticate();

    enum Users { UserA, UserB, UserC, USERS_MAX };
    static const char* Users_names[3];
    TestUser* GetUser(Users user);

    bool GoToChildProfile();
    bool GoToParentProfile();
    void Logout();

private:
    static bool m_init;
    void Init();

    static bool m_initUsers;
    static std::vector<TestUser*> m_testUsers;
    void LoadIds();
    std::string ParseIdLine(std::string line);
};
#endif

