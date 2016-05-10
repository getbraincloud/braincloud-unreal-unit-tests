#ifndef _TESTBCFILE_H_
#define _TESTBCFILE_H_

#include "gtest/gtest.h"
#include "braincloud/BrainCloudClient.h"
#include "TestFixtureBase.h"
#include "json/json.h"

using namespace BrainCloud;

struct UploadCompletedDetails
{
public:
    std::string _fileUploadId;
    std::string _jsonResponse;
};

struct UploadFailedDetails
{
public:
    std::string _fileUploadId;
    int _statusCode;
    int _reasonCode;
    std::string _jsonResponse;

    UploadFailedDetails()
    {
        _statusCode = 0;
        _reasonCode = 0;
    }
};

class TestBCFile: public TestFixtureBase, public IFileUploadCallback
{
protected:
    std::vector <UploadCompletedDetails> _completedUploadDetails;
    std::vector <UploadFailedDetails> _failedUploadDetails;
    
    int createFile(const char * in_path, int in_size);
    bool simpleUpload(int mb, const std::string & cloudPath, const std::string & cloudFilename, std::string & out_uploadId);

public:
    TestBCFile()
    {
    }
    
    virtual void fileUploadCompleted(const char * in_fileUploadId, const std::string & in_jsonResponse);
    virtual void fileUploadFailed(const char * in_fileUploadId, int in_statusCode, int in_reasonCode, const std::string & in_jsonResponse);

};

#endif
