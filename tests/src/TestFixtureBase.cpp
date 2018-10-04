#include <fstream>
#include <time.h>
#include "TestFixtureBase.h"
#include "TestResult.h"
#include "braincloud/AuthenticationType.h"

using namespace std;

#ifndef ID_FILE_NAME
#define ID_FILE_NAME "ids.txt"
#endif

std::string TestFixtureBase::m_serverUrl = "";
std::string TestFixtureBase::m_appId = "";
std::string TestFixtureBase::m_secret = "";
std::string TestFixtureBase::m_version = "";
std::string TestFixtureBase::m_parentLevelName = "";
std::string TestFixtureBase::m_childAppId = "";
std::string TestFixtureBase::m_childSecret = "";
std::string TestFixtureBase::m_peerName = "";

bool TestFixtureBase::m_init = false;
bool TestFixtureBase::m_initUsers = false;
std::vector<TestUser*> TestFixtureBase::m_testUsers;

const char* TestFixtureBase::Users_names[3] = { "UserA", "UserB", "UserC" };



void TestFixtureBase::SetUp()
{
	m_bcWrapper = new BrainCloudWrapper("_wrapperName");

	LoadIds();

	std::map<std::string, std::string> secretMap;
	secretMap[m_appId] = m_secret;
	secretMap[m_childAppId] = m_childSecret;
	m_bcWrapper->initializeWithApps(m_serverUrl.c_str(), m_appId.c_str(), secretMap, m_version.c_str(), "", "");

	m_bc = m_bcWrapper->client;

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

	delete m_bcWrapper;
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
		m_testUsers.push_back(new TestUser(Users_names[i], rand() % 100000000, m_bc));
		printf("..%i", i + 1);
	}
	printf("..completed\n\n");
	m_initUsers = true;
}

void TestFixtureBase::LoadIds()
{
	if (m_serverUrl.length() > 0) return; //check if loaded

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
			else if (line.find("childSecret") != string::npos)
			{
				m_childSecret = line.substr(line.find("childSecret") + sizeof("childSecret"), line.length() - 1);
			}
			else if (line.find("parentLevelName") != string::npos)
			{
				m_parentLevelName = line.substr(line.find("parentLevelName") + sizeof("parentLevelName"), line.length() - 1);
			}
			else if (line.find("peerName") != string::npos)
			{
				m_peerName = line.substr(line.find("peerName") + sizeof("peerName"), line.length() - 1);
			}
		}
		fclose(fp);

		printf("\nURL - %s", m_serverUrl.c_str());
		printf("\nApp ID - %s", m_appId.c_str());
		printf("\nSecret - %s", m_secret.c_str());
		printf("\nVersion - %s", m_version.c_str());
		printf("\nChild App ID - %s", m_childAppId.c_str());
		printf("\nChild Secret - %s", m_childSecret.c_str());
		printf("\nParent Level Name - %s\n", m_parentLevelName.c_str());
		printf("\nPeer Name - %s\n", m_peerName.c_str());
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

bool TestFixtureBase::AttachPeer(Users user, AuthenticationType authType)
{
	TestResult tr;
	m_bc->getIdentityService()->attachPeerProfile(m_peerName.c_str(), GetUser(user)->m_id, GetUser(user)->m_password, authType, NULL, true, &tr);
	return tr.run(m_bc);
}

bool TestFixtureBase::DetachPeer()
{
	TestResult tr;
	m_bc->getIdentityService()->detachPeer(m_peerName.c_str(), &tr);
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
	std::map<std::string, std::string> secretMap;
	secretMap[m_appId] = m_secret;
	secretMap[m_childAppId] = m_childSecret;
	m_bc->initializeWithApps(m_serverUrl.c_str(), m_appId.c_str(), secretMap, m_version.c_str());
}
