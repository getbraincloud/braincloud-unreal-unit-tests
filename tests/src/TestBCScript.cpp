#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCScript.h"
#include <time.h>

using namespace BrainCloud;


TEST_F(TestBCScript, RunScript)
{
    TestResult tr;
    Json::FastWriter fw;
    Json::Value scriptData;
    scriptData["testParam1"] = 1;
    
    m_bc->getScriptService()->runScript(m_scriptName, fw.write(scriptData), &tr);
    tr.run(m_bc);
}

TEST_F(TestBCScript, ScheduleScriptUTC)
{
    TestResult tr;
    Json::FastWriter fw;
    Json::Value scriptData;
    scriptData["testParam1"] = 1;
    
    time_t t = time(0);
    struct tm * time  = localtime(&t);
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