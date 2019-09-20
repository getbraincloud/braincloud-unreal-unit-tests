#include <stdlib.h>
#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "braincloud/BrainCloudEntity.h"
#include "TestResult.h"
#include "json/json.h"
#include "TestBCDataStream.h"

using namespace BrainCloud;


TEST_F(TestBCDataStream, CustomPageEvent)
{
    TestResult tr;

    Json::Value eventProperties;
    eventProperties["testProperty"] = "1";

    Json::FastWriter fw;
    std::string strProps = fw.write(eventProperties);
    m_bc->getDataStreamService()->customPageEvent("testPage", strProps.c_str(), &tr);
    tr.run(m_bc);
}

TEST_F(TestBCDataStream, CustomScreenEvent)
{
    TestResult tr;
    
    Json::Value eventProperties;
    eventProperties["testProperty"] = "1";
    
    Json::FastWriter fw;
    std::string strProps = fw.write(eventProperties);
    m_bc->getDataStreamService()->customScreenEvent("testScreen", strProps.c_str(), &tr);
    tr.run(m_bc);
}

TEST_F(TestBCDataStream, CustomTrackEvent)
{
    TestResult tr;
    
    Json::Value eventProperties;
    eventProperties["testProperty"] = "1";
    
    Json::FastWriter fw;
    std::string strProps = fw.write(eventProperties);
    m_bc->getDataStreamService()->customTrackEvent("testTrack", strProps.c_str(), &tr);
    tr.run(m_bc);
}

TEST_F(TestBCDataStream, SubmitCrashReport)
{
    TestResult tr;
    m_bc->getDataStreamService()->submitCrashReport("test", "test", "{\"testReport\": \"Testing\"}", "test", "test", "test", "test", true, &tr);
    tr.run(m_bc);
}

