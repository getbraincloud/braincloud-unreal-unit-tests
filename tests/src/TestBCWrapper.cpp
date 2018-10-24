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
	m_bcWrapper->client->setImmediateRetryOnError(true);
#else
	m_bcWrapper->client->setImmediateRetryOnError(false);
#endif

    // this forces us to create a new anonymous account
	m_bcWrapper->setStoredAnonymousId("");
	m_bcWrapper->setStoredProfileId("");
}

TEST_F(TestBCWrapper, AuthenticateAnonymous)
{
    m_bcWrapper->initialize(m_serverUrl.c_str(), m_secret.c_str(), m_appId.c_str(), m_version.c_str(), "wrapper", "unittest");

    TestResult tr;
	m_bcWrapper->authenticateAnonymous(&tr);
    tr.run(m_bc);
    
    Logout();
}

//Singleton usage is disabled DEPRECATED
TEST_F(TestBCWrapper, DISABLED_AuthenticateAnonymous)
{
    
    TestResult tr;
	m_bcWrapper->authenticateAnonymous(&tr);
    tr.run(m_bc);
    
    std::string anonId = m_bcWrapper->getStoredAnonymousId();
    std::string profileId = m_bcWrapper->getStoredProfileId();
    
    Logout();
	m_bcWrapper->getBC()->getAuthenticationService()->clearSavedProfileId();
    
	m_bcWrapper->authenticateAnonymous(&tr);
    tr.run(m_bc);
    
    EXPECT_TRUE(anonId.compare(m_bcWrapper->getStoredAnonymousId()) == 0);
    EXPECT_TRUE(profileId.compare(m_bcWrapper->getStoredProfileId()) == 0);
    
    Logout();
}

TEST_F(TestBCWrapper, AuthenticateEmailPassword)
{
	m_bcWrapper->initialize(m_serverUrl.c_str(), m_secret.c_str(), m_appId.c_str(), m_version.c_str(), "wrapper", "unittest");
    
    std::string email = GetUser(UserA)->m_email;
    email.append("_wrapper");
    
    TestResult tr;
	m_bcWrapper->authenticateEmailPassword(email.c_str(), GetUser(UserA)->m_password, true, &tr);
    tr.run(m_bc);
    
    Logout();
}

TEST_F(TestBCWrapper, AuthenticateUniversal)
{
    m_bcWrapper->initialize(m_serverUrl.c_str(), m_secret.c_str(), m_appId.c_str(), m_version.c_str(), "wrapper", "unittest");
    
    TestResult tr;
    std::string uid = GetUser(UserA)->m_id;
    uid.append("_wrapper");
    m_bcWrapper->authenticateUniversal(uid.c_str(), GetUser(UserA)->m_password, true, &tr);
    tr.run(m_bc);
    
    Logout();
}

//Singleton usage is disabled
TEST_F(TestBCWrapper, DISABLED_VerifyAlwaysAllowProfileFalse)
{
    m_bcWrapper->initialize(m_serverUrl.c_str(), m_secret.c_str(), m_appId.c_str(), m_version.c_str(), "wrapper", "unittest");
    m_bcWrapper->setAlwaysAllowProfileSwitch(false);

    // this forces us to create a new anonymous account
    m_bcWrapper->setStoredAnonymousId("");
    m_bcWrapper->setStoredProfileId("");

    TestResult tr;
    m_bcWrapper->authenticateAnonymous(&tr);
    tr.run(m_bc);

    std::string anonId = m_bcWrapper->getStoredAnonymousId();
    std::string profileId = m_bcWrapper->getStoredProfileId();
    std::string uid = GetUser(UserA)->m_id;
    uid.append("_wrapperVerifyAlwaysAllowProfileFalse");

	m_bcWrapper->getBC()->getIdentityService()->attachUniversalIdentity(uid.c_str(), GetUser(UserA)->m_password, &tr);
    tr.run(m_bc);

    Logout();
	m_bcWrapper->getBC()->getAuthenticationService()->clearSavedProfileId();

    m_bcWrapper->authenticateUniversal(uid.c_str(), GetUser(UserA)->m_password, true, &tr);
    tr.run(m_bc);

    EXPECT_TRUE(anonId.compare(m_bcWrapper->getStoredAnonymousId()) == 0);
    EXPECT_TRUE(profileId.compare(m_bcWrapper->getStoredProfileId()) == 0);

    m_bcWrapper->setAlwaysAllowProfileSwitch(true);
    Logout();
}

TEST_F(TestBCWrapper, Reconnect)
{
	TestResult tr;

	m_bcWrapper->initialize(m_serverUrl.c_str(), m_secret.c_str(), m_appId.c_str(), m_version.c_str(), "wrapper", "unittest");

	m_bcWrapper->reconnect(&tr);
	tr.run(m_bc);

	Logout();
}

//Singleton usage is disabled
TEST_F(TestBCWrapper, DISABLED_Reconnect)
{
	m_bcWrapper->initialize(m_serverUrl.c_str(), m_secret.c_str(), m_appId.c_str(), m_version.c_str(), "wrapper", "unittest");

	std::string email = GetUser(UserA)->m_email;
	email.append("_wrapper");

	TestResult tr;
	m_bcWrapper->authenticateEmailPassword(email.c_str(), GetUser(UserA)->m_password, true, &tr);
	tr.run(m_bc);

	m_bcWrapper->getBC()->getPlayerStateService()->logout(&tr);
	tr.run(m_bc);

	m_bcWrapper->reconnect(&tr);
	tr.run(m_bc);

	Logout();
}

TEST_F(TestBCWrapper, SmartSwitchAnonToUniversal)
{
	
	std::string uid = GetUser(UserA)->m_id;
	uid.append("_wrapper");

	m_bcWrapper->setStoredAnonymousId(m_bcWrapper->client->getAuthenticationService()->generateAnonymousId().c_str());
	m_bcWrapper->resetStoredProfileId();

	TestResult tr;

	m_bcWrapper->authenticateAnonymous(&tr);
	tr.run(m_bc);

	std::string profileId = m_bcWrapper->getStoredProfileId();

	m_bcWrapper->smartSwitchAuthenticateUniversal(uid.c_str(), GetUser(UserA)->m_password, true, &tr);
	tr.run(m_bc);

	EXPECT_TRUE(profileId.compare(m_bcWrapper->getStoredAnonymousId()) != 0);
}

TEST_F(TestBCWrapper, SmartSwitchUniversalToEmail)
{
	std::string email = GetUser(UserA)->m_email;
	email.append("_wrapper");

	m_bcWrapper->setStoredAnonymousId(m_bcWrapper->client->getAuthenticationService()->generateAnonymousId().c_str());
	m_bcWrapper->resetStoredProfileId();

	TestResult tr;
	std::string uid = GetUser(UserA)->m_id;
	uid.append("_wrapper");
	m_bcWrapper->authenticateUniversal(uid.c_str(), GetUser(UserA)->m_password, true, &tr);
	tr.run(m_bc);

	std::string profileId = m_bcWrapper->getStoredProfileId();

	m_bcWrapper->smartSwitchAuthenticateEmailPassword(email.c_str(), GetUser(UserA)->m_password, true, &tr);
	tr.run(m_bc);

	EXPECT_TRUE(profileId.compare(m_bcWrapper->getStoredProfileId()) != 0);
}

#endif

