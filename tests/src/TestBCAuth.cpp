#include "TestBCAuth.h"
#include "braincloud/http_codes.h"
#include "braincloud/reason_codes.h"

TEST_F(TestBCAuth, AaaRunFirst)
{
    // test that should be run before all others
#if defined (USE_IMMEDIATE_RETRY)
    m_bc->setImmediateRetryOnError(true);
#else
    BrainCloudClient::getInstance()->setImmediateRetryOnError(false);
#endif
}

// Note that TestBCAuth skips the normal authenticate setup provided by TestFixtureBase
// All TestBCAuth test methods must perform their own authenticate + logout



TEST_F(TestBCAuth, AuthenticateEmailPassword)
{
    TestResult tr;
    m_bc->getAuthenticationService()->authenticateEmailPassword(GetUser(UserA)->m_email, GetUser(UserA)->m_password, true, &tr);
    tr.run(m_bc);
    Logout();
}

TEST_F(TestBCAuth, AuthenticateUniversal)
{
    TestResult tr;
    m_bc->getAuthenticationService()->authenticateUniversal(GetUser(UserA)->m_id, GetUser(UserA)->m_password, true, &tr);
    tr.run(m_bc);

    Logout();
}

TEST_F(TestBCAuth, AuthenticateParse)
{
    TestResult tr;
    m_bc->getAuthenticationService()->authenticateParse("VVVbiejp0k", "r:b1oj5nchWRnQnWlJbsTQjObTT", true, &tr);
    tr.runExpectFail(m_bc, HTTP_FORBIDDEN, TOKEN_DOES_NOT_MATCH_USER);
    Logout();
}

TEST_F(TestBCAuth, AuthenticateHandoff)
{
    TestResult tr;
    m_bc->getAuthenticationService()->authenticateHandoff("invalid_handoffId", "invalid_securityToken", &tr);
    tr.runExpectFail(m_bc, HTTP_FORBIDDEN, TOKEN_DOES_NOT_MATCH_USER);
    Logout();
}

TEST_F(TestBCAuth, ResetEmailPassword)
{
    const char* email = "braincloudunittest@gmail.com";

    TestResult tr;
    m_bc->getAuthenticationService()->resetEmailPassword(email, &tr);
    tr.run(m_bc);
}
