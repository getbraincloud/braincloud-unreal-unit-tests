#include "TestBCAuth.h"
#include "braincloud/http_codes.h"
#include "braincloud/reason_codes.h"
#include "json/json.h"
#include <map>

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

TEST_F(TestBCAuth, AuthBadSig)
{
    //our problem is that users who refresh their app secret via the portal, the client would fail to read the response, and would retry infinitely.
    //This threatens our servers, because huge numbers of errors related to bad signature show up, and infinitely retry to get out of this error.
    //Instead of updating the signature via the portal, we will mimic a bad signature from the client.
    std::map<std::string, std::string> originalAppSecretMap;
    originalAppSecretMap[m_appId] = m_secret;
    originalAppSecretMap[m_childAppId] =  m_childSecret;
    int numRepeatBadSigFailures = 0;

    // mess up app 
    std::map<std::string, std::string> updatedAppSecretMap;
    updatedAppSecretMap[m_appId] = m_secret;
    updatedAppSecretMap[m_childAppId] = m_childSecret;

    std::map<std::string, std::string>::iterator it;
    for (it=updatedAppSecretMap.begin(); it!=updatedAppSecretMap.end(); it++)
    {
        std::string key = it->first;
        std::string value = it->second;
        updatedAppSecretMap.at(key) = value + "123";
    }       
/////////////////////Phase 1
    //first auth
    TestResult tr1;
    m_bc->getAuthenticationService()->authenticateUniversal(GetUser(UserA)->m_id, GetUser(UserA)->m_password, true, &tr1);
    tr1.run(m_bc);

    //check state
    m_bc->getPlayerStateService()->readUserState(&tr1);

//////////////////////////Phase 2
    TestResult tr3;
    m_bc->initializeWithApps(m_serverUrl.c_str(), m_appId.c_str(), updatedAppSecretMap, m_version.c_str());
    m_bc->getAuthenticationService()->authenticateUniversal(GetUser(UserA)->m_id, GetUser(UserA)->m_password, true, &tr3);
    tr3.runExpectFail(m_bc, 403, 40301);

    //check state
    m_bc->getPlayerStateService()->readUserState(&tr3);

    //wait a while
    TestResult::sleep(300);
    
    /////////////////////Phase 3
    TestResult tr5;
    m_bc->initializeWithApps(m_serverUrl.c_str(), m_appId.c_str(), originalAppSecretMap, m_version.c_str());
    m_bc->getAuthenticationService()->authenticateUniversal(GetUser(UserA)->m_id, GetUser(UserA)->m_password, true, &tr5);
    tr5.run(m_bc);

    //check state
    m_bc->getPlayerStateService()->readUserState(&tr5);
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
