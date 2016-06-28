#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCS3Handling.h"

using namespace BrainCloud;


TEST_F(TestBCS3Handling, GetUpdatedFiles)
{
    TestResult tr;
    Json::Reader r;
    Json::FastWriter fw;
    
    m_bc->getS3HandlingService()->getFileList(m_category, &tr);
    tr.run(m_bc);
    
    Json::Value files = tr.m_response["data"]["fileDetails"];
    files[0]["md5Hash"] = "ngbgbuofod4f03vc0248ht0f";
    
    tr.reset();
    m_bc->getS3HandlingService()->getUpdatedFiles(m_category, fw.write(files).c_str(), &tr);
    tr.run(m_bc);
}

TEST_F(TestBCS3Handling, GetFileList)
{
    TestResult tr;
    m_bc->getS3HandlingService()->getFileList(m_category, &tr);
    tr.run(m_bc);
}

TEST_F(TestBCS3Handling, GetCDNUrl)
{
	TestResult tr;
	m_bc->getS3HandlingService()->getFileList(m_category, &tr);
	tr.run(m_bc);

	std::string fileId = tr.m_response["data"]["fileDetails"][0]["fileId"].asString();

	m_bc->getS3HandlingService()->getCDNUrl(fileId.c_str(), &tr);
	tr.run(m_bc);
}

