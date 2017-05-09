#include <vector>
#include "TestResult.h"
#include "TestUser.h"

using namespace std;

TestUser::TestUser(std::string prefix, int suffix)
{
	sprintf(m_id, "%s%s%d", prefix.c_str(), "_CPP_", suffix);
	sprintf(m_password, "%s", m_id);
	sprintf(m_email, "%s@bctestuser.com", m_id);

	Authenticate();
}

void TestUser::Authenticate()
{
	BrainCloudClient* bc = BrainCloudClient::getInstance();
	TestResult tr;

	bc->getAuthenticationService()->authenticateUniversal(m_id, m_password, true, &tr);
	tr.run(bc);
	sprintf(m_profileId, "%s", bc->getAuthenticationService()->getProfileId().c_str());

    bc->getPlayerStateService()->updateUserName(m_id, &tr);
	tr.run(bc);

	bc->getPlayerStateService()->updateContactEmail("braincloudunittest@gmail.com", &tr);
	tr.run(bc);

	bc->getPlayerStateService()->logout(&tr);
	tr.run(bc);

	bc->getAuthenticationService()->clearSavedProfileId();
}

