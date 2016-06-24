// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudFile.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

#include <stdio.h>

namespace BrainCloud
{
    BrainCloudFile::BrainCloudFile(BrainCloudClient* in_client) : m_client(in_client) { }

    bool BrainCloudFile::uploadFile(const char * in_cloudPath,
        const char * in_cloudFilename,
        bool in_shareable,
        bool in_replaceIfExists,
        const char * in_localPath,
        IServerCallback * in_callback)
    {
        int64_t fileSize = 0;

        // todo - improve the method of retrieving file size
        // as this has to scan the whole file
        int rc = 0;
        FILE * fp = NULL;
#if defined(WINAPI_FAMILY)
        fopen_s(&fp, in_localPath, "rb");
#else
        fp = fopen(in_localPath, "rb");
#endif
        if (fp == NULL)
        {
            return false;
        }
        if ((rc = fseek(fp, 0, SEEK_END)) != 0)
        {
            fclose(fp);
            return false;
        }
        fileSize = ftell(fp);
        fclose(fp);
        fp = NULL;
        if (fileSize <= 0)
        {
            return false;
        }

        Json::Value message;

        message[OperationParam::UploadCloudPath.getValue()] = in_cloudPath;
        message[OperationParam::UploadCloudFilename.getValue()] = in_cloudFilename;
        message[OperationParam::UploadShareable.getValue()] = in_shareable;
        message[OperationParam::UploadReplaceIfExists.getValue()] = in_replaceIfExists;
        message[OperationParam::UploadFileSize.getValue()] = (Json::Int64) fileSize;
        message[OperationParam::UploadLocalPath.getValue()] = in_localPath;

        ServerCall * sc = new ServerCall(ServiceName::File, ServiceOperation::PrepareUserUpload, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
        return true;
    }

    void BrainCloudFile::listUserFiles(IServerCallback * in_callback)
    {
        Json::Value message;

        ServerCall * sc = new ServerCall(ServiceName::File, ServiceOperation::ListUserFiles, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudFile::listUserFiles(const char * in_cloudPath, bool in_recurse, IServerCallback * in_callback)
    {
        Json::Value message;

        message[OperationParam::UploadCloudPath.getValue()] = in_cloudPath;
        message[OperationParam::UploadRecurse.getValue()] = in_recurse;

        ServerCall * sc = new ServerCall(ServiceName::File, ServiceOperation::ListUserFiles, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudFile::deleteUserFile(const char * in_cloudPath, const char * in_cloudFilename, IServerCallback * in_callback)
    {
        Json::Value message;

        message[OperationParam::UploadCloudPath.getValue()] = in_cloudPath;
        message[OperationParam::UploadCloudFilename.getValue()] = in_cloudFilename;


        ServerCall * sc = new ServerCall(ServiceName::File, ServiceOperation::DeleteUserFiles, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudFile::deleteUserFiles(const char * in_cloudPath, bool in_recurse, IServerCallback * in_callback)
    {
        Json::Value message;

        message[OperationParam::UploadCloudPath.getValue()] = in_cloudPath;
        message[OperationParam::UploadRecurse.getValue()] = in_recurse;

        ServerCall * sc = new ServerCall(ServiceName::File, ServiceOperation::DeleteUserFiles, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

	void BrainCloudFile::getCDNUrl(const char * in_cloudPath, const char * in_cloudFileName, IServerCallback * in_callback)
	{
		Json::Value message;

		message[OperationParam::UploadCloudPath.getValue()] = in_cloudPath;
		message[OperationParam::UploadCloudFilename.getValue()] = in_cloudFileName;

		ServerCall * sc = new ServerCall(ServiceName::File, ServiceOperation::GetCdnUrl, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}

	void BrainCloudFile::cancelUpload(const char * in_uploadFileId)
    {
        m_client->getBrainCloudComms()->cancelUpload(in_uploadFileId);
    }

    double BrainCloudFile::getUploadProgress(const char * in_uploadFileId)
    {
        return m_client->getBrainCloudComms()->getUploadProgress(in_uploadFileId);
    }

    int64_t BrainCloudFile::getUploadBytesTransferred(const char * in_uploadFileId)
    {
        return m_client->getBrainCloudComms()->getUploadBytesTransferred(in_uploadFileId);
    }

    int64_t BrainCloudFile::getUploadTotalBytesToTransfer(const char * in_uploadFileId)
    {
        return m_client->getBrainCloudComms()->getUploadTotalBytesToTransfer(in_uploadFileId);
    }
}
