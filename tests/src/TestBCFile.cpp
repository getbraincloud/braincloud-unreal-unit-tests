#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestResult.h"
#include "TestBCFile.h"
#include "braincloud/http_codes.h"
#include "braincloud/reason_codes.h"

//#define UPLOAD_TIMEOUT_SECS 30
#define SLEEP_INTERVAL_MS 300

int TestBCFile::createFile(const char * in_path, int in_size)
{
    FILE* fp = NULL;
    fp = fopen(in_path, "w");
    if (fp == NULL)
    {
        return -1;
    }
    for (int i = 0; i < in_size; ++i)
    {
        fputc('!', fp);
    }
    fseek(fp, 0, SEEK_END);
    int fileLen = ftell(fp);
    fclose(fp);
    fp = NULL;
    return fileLen;
}

bool TestBCFile::simpleUpload(int mb, const std::string & cloudPath, const std::string & cloudFilename, std::string & out_uploadId)
{
    std::string localPath = cloudFilename;
    createFile(localPath.c_str(), mb * 1024 * 1024);

    TestResult tr;
    m_bc->getFileService()->uploadFile(cloudPath.c_str(), cloudFilename.c_str(), true, true, localPath.c_str(), &tr);
    if (!tr.run(m_bc))
    {
        return false;
    }
    out_uploadId = tr.m_response["data"]["fileDetails"]["uploadId"].asString();

    m_bc->registerFileUploadCallback(this);
    while (_completedUploadDetails.size() == 0 && _failedUploadDetails.size() == 0)
    {
        int64_t transferred = m_bc->getFileService()->getUploadBytesTransferred(out_uploadId.c_str());
        int64_t total = m_bc->getFileService()->getUploadTotalBytesToTransfer(out_uploadId.c_str());
        double progress = m_bc->getFileService()->getUploadProgress(out_uploadId.c_str());
        printf("%lld transfered %lld total %f progress\n", transferred, total, progress);

        m_bc->runCallbacks();
        TestResult::sleep(SLEEP_INTERVAL_MS);
    }
    m_bc->deregisterFileUploadCallback();
    return true;
}


void TestBCFile::fileUploadCompleted(const char * in_fileUploadId, const std::string & in_jsonResponse)
{
    std::cout << "FileUploadCompleted callback hit" << std::endl;

    UploadCompletedDetails details;
    details._fileUploadId = in_fileUploadId;
    details._jsonResponse = in_jsonResponse;
    _completedUploadDetails.push_back(details);
}

void TestBCFile::fileUploadFailed(const char * in_fileUploadId, int in_statusCode, int in_reasonCode, const std::string & in_jsonResponse)
{
    std::cout << "FileUploadFailed callback hit status(" << in_statusCode << ") reason(" << in_reasonCode << ")" << std::endl;

    UploadFailedDetails details;
    details._fileUploadId = in_fileUploadId;
    details._statusCode = in_statusCode;
    details._reasonCode = in_reasonCode;
    details._jsonResponse = in_jsonResponse;
    _failedUploadDetails.push_back(details);
}

// marmalade does not support file uploads... yet!
#if !defined(IW_SDK)

TEST_F(TestBCFile, UploadSimpleFile)
{
    std::string uploadId;
    if (!simpleUpload(5, "", "uploadsimplefile.txt", uploadId))
    {
        return;
    }
    
    ASSERT_EQ(_completedUploadDetails.size(), 1);
    ASSERT_EQ(_failedUploadDetails.size(), 0);
}

TEST_F(TestBCFile, UploadSimpleFileAndCancel)
{
    std::string localPath = "uploadsimplefile.txt";
    createFile(localPath.c_str(), 3*1024*1024);
    
    TestResult tr;
    m_bc->getFileService()->uploadFile("", localPath.c_str(), true, true, localPath.c_str(), &tr);
    if (!tr.run(m_bc))
    {
        return;
    }
    std::string uploadId = tr.m_response["data"]["fileDetails"]["uploadId"].asString();
    
    m_bc->registerFileUploadCallback(this);
    bool transferHasStarted = false;
    while(!transferHasStarted)
    {
        m_bc->runCallbacks();
        int64_t transferred = m_bc->getFileService()->getUploadBytesTransferred(uploadId.c_str());
        int64_t total = m_bc->getFileService()->getUploadTotalBytesToTransfer(uploadId.c_str());
        double progress = m_bc->getFileService()->getUploadProgress(uploadId.c_str());
        printf("%lld transfered %lld total %f progress\n", transferred, total, progress);
        
        if (transferred > 0)
        {
            transferHasStarted = true;
        }
        TestResult::sleep(SLEEP_INTERVAL_MS);
    }
    if (!transferHasStarted)
    {
        m_bc->deregisterFileUploadCallback();
        ASSERT_TRUE(transferHasStarted);
        return;
    }
    
    printf("Cancelling upload\n");
    m_bc->getFileService()->cancelUpload(uploadId.c_str());
    while (_completedUploadDetails.size() == 0 && _failedUploadDetails.size() == 0)
    {
        m_bc->runCallbacks();
        TestResult::sleep(SLEEP_INTERVAL_MS);
    }
    m_bc->deregisterFileUploadCallback();

    ASSERT_EQ(_failedUploadDetails.size(), 1);
    ASSERT_EQ(_completedUploadDetails.size(), 0);
    ASSERT_EQ(_failedUploadDetails[0]._statusCode, HTTP_CLIENT_NETWORK_ERROR);
    ASSERT_EQ(_failedUploadDetails[0]._reasonCode, CLIENT_UPLOAD_FILE_CANCELLED);
}

TEST_F(TestBCFile, ListUserFiles)
{
    TestResult tr;
    m_bc->getFileService()->listUserFiles(&tr);
    tr.run(m_bc);
}

TEST_F(TestBCFile, UploadMultipleFiles)
{
    std::string localPath = "uploadsimplefile.txt";
    createFile(localPath.c_str(), 3*1024*1024);
    
    std::vector<std::string> uploadIds;
    int numTransfers = 3;
    for (int i = 0; i < numTransfers; ++i)
    {
        TestResult tr;
        m_bc->getFileService()->uploadFile("", localPath.c_str(), true, true, localPath.c_str(), &tr);
        if (!tr.run(m_bc))
        {
            return;
        }
        std::string uploadId = tr.m_response["data"]["fileDetails"]["uploadId"].asString();
        uploadIds.push_back(uploadId);
    }
    
    m_bc->registerFileUploadCallback(this);
    int timeoutMs = 60000;
    while (_completedUploadDetails.size() + _failedUploadDetails.size() < numTransfers && timeoutMs > 0)
    {
        m_bc->runCallbacks();
        for (int i = 0; i < numTransfers; ++i)
        {
            int64_t transferred = m_bc->getFileService()->getUploadBytesTransferred(uploadIds[i].c_str());
            int64_t total = m_bc->getFileService()->getUploadTotalBytesToTransfer(uploadIds[i].c_str());
            double progress = m_bc->getFileService()->getUploadProgress(uploadIds[i].c_str());
            if (transferred >= 0)
            {
                printf("File%d %lld transfered %lld total %f progress\n", i+1, transferred, total, progress);
            }
        }
        
        timeoutMs -= SLEEP_INTERVAL_MS;
        TestResult::sleep(SLEEP_INTERVAL_MS);
    }
    m_bc->deregisterFileUploadCallback();

    ASSERT_TRUE(timeoutMs >= 0);
    ASSERT_EQ(_completedUploadDetails.size(), numTransfers);
    ASSERT_EQ(_failedUploadDetails.size(), 0);
}

TEST_F(TestBCFile, DeleteUserFile)
{
    std::string uploadId;
    if (!simpleUpload(19, "", "uploadsimplefile.txt", uploadId))
    {
        return;
    }
    
    ASSERT_EQ(_completedUploadDetails.size(), 1);
    ASSERT_EQ(_failedUploadDetails.size(), 0);
    
    TestResult tr;
    m_bc->getFileService()->deleteUserFile("", "uploadsimplefile.txt", &tr);
    tr.run(m_bc);
}

// this test requires use of a bandwidth limiter
// so it's normally commented out
/*
TEST_F(TestBCFile, LowRateTimeout)
{
    m_bc->setUploadLowTransferRateThreshold(500);
    m_bc->setUploadLowTransferRateTimeout(15);

    std::string uploadId;
    if (!simpleUpload(19, "", "uploadsimplefile.txt", uploadId))
    {
        return;
    }

    ASSERT_EQ(_completedUploadDetails.size(), 0);
    ASSERT_EQ(_failedUploadDetails.size(), 1);
    ASSERT_EQ(_failedUploadDetails[0]._statusCode, HTTP_CUSTOM);
    ASSERT_EQ(_failedUploadDetails[0]._reasonCode, CLIENT_UPLOAD_FILE_TIMED_OUT);
}
*/

#endif //!IW_SDK