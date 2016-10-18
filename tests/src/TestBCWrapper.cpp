#include "TestBCWrapper.h"
#include "braincloud/BrainCloudWrapper.h"

// These tests are normally commented out for apple as the wrapper
// manipulates the keychain which asks the user for confirmation.
// Build machines dislike this :-)
// However you can uncomment to verify the wrapper is working.

#ifndef __APPLE__

TEST_F(TestBCWrapper, AaaRunFirst)
{
    // test that should be run before all others
#if defined (USE_IMMEDIATE_RETRY)
    BrainCloudClient::getInstance()->setImmediateRetryOnError(true);
#else
    BrainCloudClient::getInstance()->setImmediateRetryOnError(false);
#endif

    // this forces us to create a new anonymous account
    BrainCloud::BrainCloudWrapper::getInstance()->setStoredAnonymousId("");
    BrainCloud::BrainCloudWrapper::getInstance()->setStoredProfileId("");
}

TEST_F(TestBCWrapper, AuthenticateAnonymous)
{
    BrainCloud::BrainCloudWrapper::getInstance()->initialize(m_serverUrl.c_str(), m_secret.c_str(), m_appId.c_str(), m_version.c_str(), "wrapper", "unittest");
    
    TestResult tr;
    BrainCloud::BrainCloudWrapper::getInstance()->authenticateAnonymous(&tr);
    tr.run(m_bc);
    
    std::string anonId = BrainCloud::BrainCloudWrapper::getInstance()->getStoredAnonymousId();
    std::string profileId = BrainCloud::BrainCloudWrapper::getInstance()->getStoredProfileId();
    
    Logout();
    BrainCloud::BrainCloudWrapper::getBC()->getAuthenticationService()->clearSavedProfileId();
    
    BrainCloud::BrainCloudWrapper::getInstance()->authenticateAnonymous(&tr);
    tr.run(m_bc);
    
    EXPECT_TRUE(anonId.compare(BrainCloud::BrainCloudWrapper::getInstance()->getStoredAnonymousId()) == 0);
    EXPECT_TRUE(profileId.compare(BrainCloud::BrainCloudWrapper::getInstance()->getStoredProfileId()) == 0);
    
    Logout();
}

TEST_F(TestBCWrapper, AuthenticateEmailPassword)
{
    BrainCloud::BrainCloudWrapper::getInstance()->initialize(m_serverUrl.c_str(), m_secret.c_str(), m_appId.c_str(), m_version.c_str(), "wrapper", "unittest");
    
    std::string email = GetUser(UserA)->m_email;
    email.append("_wrapper");
    
    TestResult tr;
    BrainCloud::BrainCloudWrapper::getInstance()->authenticateEmailPassword(email.c_str(), GetUser(UserA)->m_password, true, &tr);
    tr.run(m_bc);
    
    Logout();
}

TEST_F(TestBCWrapper, AuthenticateUniversal)
{
    BrainCloud::BrainCloudWrapper::getInstance()->initialize(m_serverUrl.c_str(), m_secret.c_str(), m_appId.c_str(), m_version.c_str(), "wrapper", "unittest");
    
    TestResult tr;
    std::string uid = GetUser(UserA)->m_id;
    uid.append("_wrapper");
    BrainCloud::BrainCloudWrapper::getInstance()->authenticateUniversal(uid.c_str(), GetUser(UserA)->m_password, true, &tr);
    tr.run(m_bc);
    
    Logout();
}

TEST_F(TestBCWrapper, VerifyAlwaysAllowProfileFalse)
{
    BrainCloud::BrainCloudWrapper::getInstance()->initialize(m_serverUrl.c_str(), m_secret.c_str(), m_appId.c_str(), m_version.c_str(), "wrapper", "unittest");
    BrainCloud::BrainCloudWrapper::getInstance()->setAlwaysAllowProfileSwitch(false);

    // this forces us to create a new anonymous account
    BrainCloud::BrainCloudWrapper::getInstance()->setStoredAnonymousId("");
    BrainCloud::BrainCloudWrapper::getInstance()->setStoredProfileId("");

    TestResult tr;
    BrainCloud::BrainCloudWrapper::getInstance()->authenticateAnonymous(&tr);
    tr.run(m_bc);

    std::string anonId = BrainCloud::BrainCloudWrapper::getInstance()->getStoredAnonymousId();
    std::string profileId = BrainCloud::BrainCloudWrapper::getInstance()->getStoredProfileId();
    std::string uid = GetUser(UserA)->m_id;
    uid.append("_wrapperVerifyAlwaysAllowProfileFalse");

    BrainCloud::BrainCloudWrapper::getBC()->getIdentityService()->attachUniversalIdentity(uid.c_str(), GetUser(UserA)->m_password, &tr);
    tr.run(m_bc);

    Logout();
    BrainCloud::BrainCloudWrapper::getBC()->getAuthenticationService()->clearSavedProfileId();

    BrainCloud::BrainCloudWrapper::getInstance()->authenticateUniversal(uid.c_str(), GetUser(UserA)->m_password, true, &tr);
    tr.run(m_bc);

    EXPECT_TRUE(anonId.compare(BrainCloud::BrainCloudWrapper::getInstance()->getStoredAnonymousId()) == 0);
    EXPECT_TRUE(profileId.compare(BrainCloud::BrainCloudWrapper::getInstance()->getStoredProfileId()) == 0);

    BrainCloud::BrainCloudWrapper::getInstance()->setAlwaysAllowProfileSwitch(true);
    Logout();
}

TEST_F(TestBCWrapper, Reconnect)
{
	BrainCloud::BrainCloudWrapper::getInstance()->initialize(m_serverUrl.c_str(), m_secret.c_str(), m_appId.c_str(), m_version.c_str(), "wrapper", "unittest");

	std::string email = GetUser(UserA)->m_email;
	email.append("_wrapper");

	TestResult tr;
	BrainCloud::BrainCloudWrapper::getInstance()->authenticateEmailPassword(email.c_str(), GetUser(UserA)->m_password, true, &tr);
	tr.run(m_bc);

	BrainCloud::BrainCloudWrapper::getBC()->getPlayerStateService()->logout(&tr);
	tr.run(m_bc);

	BrainCloud::BrainCloudWrapper::getInstance()->reconnect(&tr);
	tr.run(m_bc);

	Logout();
}

#endif

