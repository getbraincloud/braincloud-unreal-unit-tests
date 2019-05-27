#include "TestBCAuth.h"
#include "braincloud/http_codes.h"
#include "braincloud/reason_codes.h"
#include "json/json.h"

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

TEST_F(TestBCAuth, ResetEmailPasswordAdvanced)
{
    const char* email = "braincloudunittest@gmail.com";
    std::string content = "{\"fromAddress\": \"fromAddress\",\"fromName\": \"fromName\",\"replyToAddress\": \"replyToAddress\",\"replyToName\": \"replyToName\", \"templateId\": \"8f14c77d-61f4-4966-ab6d-0bee8b13d090\",\"subject\": \"subject\",\"body\": \"Body goes here\", \"substitutions\": { \":name\": \"John Doe\",\":resetLink\": \"www.dummuyLink.io\"}, \"categories\": [\"category1\",\"category2\" ]}";

    TestResult tr;
    m_bc->getAuthenticationService()->resetEmailPasswordAdvanced(email, content, &tr);
    tr.runExpectFail(m_bc, HTTP_BAD_REQUEST, INVALID_FROM_ADDRESS);
}

TEST_F(TestBCAuth, ResetUniversalIdPassword)
{
    TestResult tr2;
    m_bc->getAuthenticationService()->authenticateUniversal(GetUser(UserA)->m_id, GetUser(UserA)->m_password, true, &tr2);
    tr2.run(m_bc);

    TestResult tr;
    m_bc->getAuthenticationService()->resetUniversalIdPassword(GetUser(UserA)->m_id, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCAuth, ResetUniversalIdPasswordAdvanced)
{
    TestResult tr2;
    m_bc->getAuthenticationService()->authenticateUniversal(GetUser(UserA)->m_id, GetUser(UserA)->m_password, true, &tr2);
    tr2.run(m_bc);

    std::string content = "{\"templateId\": \"d-template-id-guid\", \"substitutions\": { \":name\": \"John Doe\",\":resetLink\": \"www.dummuyLink.io\"}, \"categories\": [\"category1\",\"category2\" ]}"; 

    TestResult tr;
    m_bc->getAuthenticationService()->resetUniversalIdPasswordAdvanced(GetUser(UserA)->m_id, content, &tr);
    tr.run(m_bc);
}
