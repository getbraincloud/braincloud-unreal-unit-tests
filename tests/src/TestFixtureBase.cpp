#include <fstream>
#include <time.h>
#include "TestFixtureBase.h"
#include "TestResult.h"

#ifdef _WIN32
#define getcwd _getcwd // stupid MSFT "deprecation" warning
#endif

using namespace std;

#define ID_FILE_NAME "ids.txt"

std::string TestFixtureBase::m_serverUrl = "";
std::string TestFixtureBase::m_appId = "";
std::string TestFixtureBase::m_secret = "";
std::string TestFixtureBase::m_version = "";
std::string TestFixtureBase::m_parentLevelName = "";
std::string TestFixtureBase::m_childAppId = "";

bool TestFixtureBase::m_init = false;
bool TestFixtureBase::m_initUsers = false;
std::vector<TestUser*> TestFixtureBase::m_testUsers;

const char* TestFixtureBase::Users_names[3] = { "UserA", "UserB", "UserC" };



void TestFixtureBase::SetUp()
{
    m_bc = BrainCloudClient::getInstance();
    LoadIds();
    m_bc->initialize(m_serverUrl.c_str(), m_secret.c_str(), m_appId.c_str(), m_version.c_str());

    m_bc->enableLogging(ENABLE_SETUP_TEARDOWN_LOGGING);

    Init(); //init, only run once

    if (!ShouldSkipAuthenticate())
    {
        TestResult tr;
        m_bc->getAuthenticationService()->authenticateUniversal(GetUser(UserA)->m_id, GetUser(UserA)->m_password, true, &tr);
        tr.run(m_bc);
    }

    m_bc->enableLogging(true);
}

void TestFixtureBase::TearDown()
{
    m_bc->enableLogging(ENABLE_SETUP_TEARDOWN_LOGGING);

    if (!ShouldSkipAuthenticate())
    {
        TestResult tr;
        m_bc->getPlayerStateService()->logout(&tr);
        tr.run(m_bc);
    }
    m_bc->resetCommunication();
    m_bc->getAuthenticationService()->clearSavedProfileId();
    m_bc->deregisterEventCallback();
    m_bc->deregisterRewardCallback();

    m_bc->enableLogging(true);
}

bool TestFixtureBase::ShouldSkipAuthenticate()
{
    return false;
}

void TestFixtureBase::Init()
{
    if (m_init) return;
    m_init = true;

    printf("\nInitializing TestFixtureBase\n");
    if (!ENABLE_SETUP_TEARDOWN_LOGGING)
    {
        printf("\n//////////////////////////////////////////////////\n");
        printf("//\tNOTE: SETUP & TEARDOWN LOGGING IS DISABLED!\n");
        printf("//////////////////////////////////////////////////\n\n");
    }

    //Create Users
    srand(time(NULL));

    printf("Creating test users");
    for (int i = 0; i < USERS_MAX; i++)
    {
        m_testUsers.push_back(new TestUser(Users_names[i], rand() % 100000000));
        printf("..%i", i + 1);
    }
    printf("..completed\n\n");
    m_initUsers = true;
}

void TestFixtureBase::LoadIds()
{
    if (m_serverUrl.length() > 0) return; //check if loaded

    //Get current working directory
    char buff[1024];
    std::string currentDir = (getcwd(buff, sizeof(buff)) ? std::string(buff) : std::string(""));
    printf("\nLooking for ids.txt in %s\n", currentDir.c_str());

    FILE * fp = fopen(ID_FILE_NAME, "r");
    if (fp == NULL)
    {
        // new tactic - hardcode the bloody thing!!!
        printf("ERROR: Failed to load ids.txt file!\n");

        exit(1);
        /* hardcode the parameters below if necessary
        m_serverUrl = "";
        m_appId = "";
        m_secret = "";
        m_version = "";
        m_childAppId = "";
        m_parentLevelName = "";
        */
    }
    else
    {
        printf("Found ids.txt file!\n");
        char buf[1024];
        while (fgets(buf, sizeof(buf), fp) != NULL)
        {
            char *c = strchr(buf, '\n');
            if (c) { *c = 0; }

            c = strchr(buf, '\r');
            if (c) { *c = 0; }

            string line(buf);
            if (line.find("serverUrl") != string::npos)
            {
                m_serverUrl = line.substr(line.find("serverUrl") + sizeof("serverUrl"), line.length() - 1);
            }
            else if (line.find("appId") != string::npos)
            {
                m_appId = line.substr(line.find("appId") + sizeof("appId"), line.length() - 1);
            }
            else if (line.find("secret") != string::npos)
            {
                m_secret = line.substr(line.find("secret") + sizeof("secret"), line.length() - 1);
            }
            else if (line.find("version") != string::npos)
            {
                m_version = line.substr(line.find("version") + sizeof("version"), line.length() - 1);
            }
            else if (line.find("childAppId") != string::npos)
            {
                m_childAppId = line.substr(line.find("childAppId") + sizeof("childAppId"), line.length() - 1);
            }
            else if (line.find("parentLevelName") != string::npos)
            {
                m_parentLevelName = line.substr(line.find("parentLevelName") + sizeof("parentLevelName"), line.length() - 1);
            }
        }
        fclose(fp);

        printf("\nURL - %s", m_serverUrl.c_str());
        printf("\nApp ID - %s", m_appId.c_str());
        printf("\nSecret - %s", m_secret.c_str());
        printf("\nVersion - %s", m_version.c_str());
        printf("\nChild App ID - %s", m_childAppId.c_str());
        printf("\nParent Level Name - %s\n", m_parentLevelName.c_str());
    }
}

string TestFixtureBase::ParseIdLine(std::string line)
{
    stringstream ss(line);
    string temp = "";

    getline(ss, temp, '=');
    getline(ss, temp);
    return temp;
}

TestUser* TestFixtureBase::GetUser(TestFixtureBase::Users user)
{
    return m_testUsers.at(user);
}

bool TestFixtureBase::GoToChildProfile()
{
    TestResult tr;
    m_bc->getIdentityService()->switchToSingletonChildProfile(m_childAppId.c_str(), true, &tr);
    return tr.run(m_bc);
}

bool TestFixtureBase::GoToParentProfile()
{
    TestResult tr;
    m_bc->getIdentityService()->switchToParentProfile(m_parentLevelName.c_str(), &tr);
    return tr.run(m_bc);
}

void TestFixtureBase::Logout()
{
    TestResult tr;
    m_bc->getPlayerStateService()->logout(&tr);
    tr.run(m_bc, true);

    m_bc->resetCommunication();
    m_bc->getAuthenticationService()->clearSavedProfileId();

    // preston - in bccomms2 (win c++) the internal thread is killed during resetCommunication.
    // for consistency, we re-initialize the comms to re-create the thread in case any further
    // processing is required (for instance where a test logs out the player but then re-auths as
    // someone else).
    //
    // In any case, the test case will call resetCommunication in the TearDown - the only worry
    // is if re-init will use different parameters from what the test case was expecting. Super unlikely.

    m_bc->initialize(m_serverUrl.c_str(), m_secret.c_str(), m_appId.c_str(), m_version.c_str());
}
