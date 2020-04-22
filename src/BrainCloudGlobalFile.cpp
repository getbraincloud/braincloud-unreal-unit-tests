// Copyright 2020 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudGlobalFile.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

namespace BrainCloud
{
    BrainCloudGlobalFile::BrainCloudGlobalFile(BrainCloudClient* in_client) : m_client(in_client) { }

    void BrainCloudGlobalFile::getFileInfo(const std::string& in_fileId, IServerCallback* in_callback)
    {
        Json::Value message;
        message[OperationParam::GlobalFileV3ServiceFileId.getValue()] = in_fileId;

        ServerCall* sc = new ServerCall(ServiceName::GlobalFileV3, ServiceOperation::GetFileInfo, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudGlobalFile::getFileInfoSimple(const std::string& in_folderPath, const std::string& in_filename, IServerCallback* in_callback)
    {
        Json::Value message;
        message[OperationParam::GlobalFileV3ServiceFolderPath.getValue()] = in_folderPath;
        message[OperationParam::GlobalFileV3ServiceFileName.getValue()] = in_filename;

        ServerCall* sc = new ServerCall(ServiceName::GlobalFileV3, ServiceOperation::GetFileInfoSimple, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudGlobalFile::getGlobalCDNUrl(const std::string& in_fileId, IServerCallback* in_callback)
    {
        Json::Value message;
        message[OperationParam::GlobalFileV3ServiceFileId.getValue()] = in_fileId;

        ServerCall* sc = new ServerCall(ServiceName::GlobalFileV3, ServiceOperation::GetGlobalCDNUrl, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudGlobalFile::getGlobalFileList(const std::string& in_folderPath, bool in_recurse, IServerCallback* in_callback)
    {
        Json::Value message;
        message[OperationParam::GlobalFileV3ServiceFolderPath.getValue()] = in_folderPath;
        message[OperationParam::GlobalFileV3ServiceRecurse.getValue()] = in_recurse;

        ServerCall* sc = new ServerCall(ServiceName::GlobalFileV3, ServiceOperation::GetGlobalFileList, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }
}
