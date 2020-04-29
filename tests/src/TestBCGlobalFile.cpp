#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCGlobalFile.h"
#include <vector>
using namespace BrainCloud;

static const std::string testfileName = "testGlobalFile.png";
static const std::string testFileId = "ed2d2924-4650-4a88-b095-94b75ce9aa18";
static const std::string testFolderPath = "/fname/";

TEST_F(TestBCGlobalFile, GetFileInfo)
{
	TestResult tr;
	m_bc->getGlobalFileService()->getFileInfo(testFileId, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCGlobalFile, GetFileInfoSimple)
{
	TestResult tr;
	m_bc->getGlobalFileService()->getFileInfoSimple(testFolderPath, testfileName, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCGlobalFile, GetGlobalCDNUrl)
{
	TestResult tr;
	m_bc->getGlobalFileService()->getGlobalCDNUrl(testFileId, &tr);
	tr.run(m_bc);
}

TEST_F(TestBCGlobalFile, GetGlobalFileList)
{
	TestResult tr;
	m_bc->getGlobalFileService()->getGlobalFileList(testFolderPath, true, &tr);
	tr.run(m_bc);
}
