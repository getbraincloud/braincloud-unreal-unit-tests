#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCMail.h"
#include <time.h>

using namespace BrainCloud;


TEST_F(TestBCMail, SendBasicEmail)
{
	TestResult tr;
	m_bc->getMailService()->sendBasicEmail(
		GetUser(UserA)->m_profileId,
		"Test Subject",
		"Test body content text form unit test",
		&tr);
	tr.run(m_bc);
}

TEST_F(TestBCMail, SendAdvancedEmail)
{
	TestResult tr;
	Json::FastWriter fw;

	Json::Value data;
	data["subject"] = "Test Subject";
	data["body"] = "Test body";

	m_bc->getMailService()->sendAdvancedEmail(GetUser(UserB)->m_profileId, fw.write(data), &tr);
	tr.run(m_bc);
}