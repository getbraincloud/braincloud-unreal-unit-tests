#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "braincloud/AuthenticationType.h"
#include "TestResult.h"
#include "TestBCScript.h"
#include <ctime>

using namespace BrainCloud;


TEST_F(TestBCScript, RunScript)
{
	TestResult tr;
	m_bc->getScriptService()->runScript("emptyScript", "{}", &tr);
	tr.run(m_bc);	
}

TEST_F(TestBCScript, ScheduleScriptUTC)
{
	TestResult tr;
	Json::FastWriter fw;
	Json::Value scriptData;
	scriptData["testParam1"] = 1;

	time_t t = time(0);
	struct tm * time = gmtime(&t);
	time->tm_mday += 1;

	m_bc->getScriptService()->scheduleRunScriptUTC(m_scriptName, fw.write(scriptData).c_str(), time, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCScript, ScheduleScriptMinutesFromNow)
{
	TestResult tr;
	Json::FastWriter fw;
	Json::Value scriptData;
	scriptData["testParam1"] = 1;

	m_bc->getScriptService()->scheduleRunScriptMinutes(m_scriptName, fw.write(scriptData).c_str(), 60, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCScript, RunParentScript)
{
	TestResult tr;
	Json::FastWriter fw;
	Json::Value scriptData;
	scriptData["testParam1"] = 1;

	GoToChildProfile();

	m_bc->getScriptService()->runParentScript(m_scriptName, fw.write(scriptData).c_str(), m_parentLevelName.c_str(), &tr);
	tr.run(m_bc);
}

TEST_F(TestBCScript, CancelScheduledScript)
{
	TestResult tr;
	Json::FastWriter fw;
	Json::Value scriptData;
	scriptData["testParam1"] = 1;

	m_bc->getScriptService()->scheduleRunScriptMinutes(m_scriptName, fw.write(scriptData).c_str(), 60, &tr);
	tr.run(m_bc);

	std::string jobId = tr.m_response["data"]["jobId"].asString();

	m_bc->getScriptService()->cancelScheduledScript(jobId.c_str(), &tr);
	tr.run(m_bc);
}

TEST_F(TestBCScript, RunPeerScript)
{
	if (AttachPeer(UserA, AuthenticationType::Universal))
	{
		TestResult tr;
		Json::FastWriter fw;
		Json::Value scriptData;
		scriptData["testParam1"] = 1;

		m_bc->getScriptService()->runPeerScript(m_peerScriptName, fw.write(scriptData), m_peerName.c_str(), &tr);
		tr.run(m_bc);

		DetachPeer();
	}
}

TEST_F(TestBCScript, RunPeerScriptAsync)
{
	if (AttachPeer(UserA, AuthenticationType::Universal))
	{
		TestResult tr;
		Json::FastWriter fw;
		Json::Value scriptData;
		scriptData["testParam1"] = 1;

		m_bc->getScriptService()->runPeerScriptAsync(m_peerScriptName, fw.write(scriptData), m_peerName.c_str(), &tr);
		tr.run(m_bc);

		DetachPeer();
	}
}