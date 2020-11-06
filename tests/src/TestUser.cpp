#include <vector>
#include "TestResult.h"
#include "TestUser.h"

using namespace std;

TestUser::TestUser(std::string prefix, int suffix, BrainCloudClient *client)
{
	sprintf(m_id, "%s%s%d", prefix.c_str(), "_CPP_", suffix);
	sprintf(m_password, "%s", m_id);
	sprintf(m_email, "%s@bctestuser.com", m_id);

	m_client = client;

	Authenticate();
}

void TestUser::Authenticate()
{
	TestResult tr;

	m_client->getAuthenticationService()->authenticateUniversal(m_id, m_password, true, &tr);
	tr.run(m_client);
	sprintf(m_profileId, "%s", m_client->getAuthenticationService()->getProfileId().c_str());

	m_client->getPlayerStateService()->updateName(m_id, &tr);
	tr.run(m_client);

	m_client->getPlayerStateService()->updateContactEmail("braincloudunittest@gmail.com", &tr);
	tr.run(m_client);

	m_client->getPlayerStateService()->logout(&tr);
	tr.run(m_client);

	m_client->getAuthenticationService()->clearSavedProfileId();
}

