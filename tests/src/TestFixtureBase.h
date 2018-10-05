#ifndef _TESTFIXTUREBASE_H_
#define _TESTFIXTUREBASE_H_

#include <stdlib.h>
#include <vector>
#include <braincloud/BrainCloudWrapper.h>
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

	BrainCloudWrapper * m_bcWrapper;


    BrainCloudClient * m_bc;

    static std::string m_serverUrl;
    static std::string m_appId;
    static std::string m_secret;
    static std::string m_version;
    static std::string m_parentLevelName;
    static std::string m_childAppId;
    static std::string m_childSecret;
	static std::string m_peerName;

    virtual void SetUp();
    virtual void TearDown();
    virtual bool ShouldSkipAuthenticate();

    enum Users { UserA, UserB, UserC, USERS_MAX };
    static const char* Users_names[3];
    TestUser* GetUser(Users user);

    bool GoToChildProfile();
    bool GoToParentProfile();
	bool AttachPeer(Users user, AuthenticationType authType);
	bool DetachPeer();
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

