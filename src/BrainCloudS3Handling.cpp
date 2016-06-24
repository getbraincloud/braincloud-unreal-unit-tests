// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "braincloud/BrainCloudS3Handling.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IServerCallback.h"
#include "braincloud/ServerCall.h"
#include "braincloud/ServiceName.h"
#include "braincloud/ServiceOperation.h"
#include "braincloud/OperationParam.h"
#include "json/json.h"

#include "braincloud/internal/StringUtil.h"

namespace BrainCloud
{
    BrainCloudS3Handling::BrainCloudS3Handling(BrainCloudClient* in_client) : m_client(in_client) { }

    void BrainCloudS3Handling::getUpdatedFiles(const char * in_category, const char * in_fileDetails, IServerCallback * in_callback)
    {
        Json::Value message;
        Json::Reader reader;

        if (StringUtil::IsOptionalParameterValid(in_category)) {
            message[OperationParam::S3HandlingServiceCategory.getValue()] = in_category;
        }

        Json::Value parsedDetails;
        reader.parse(in_fileDetails, parsedDetails);

        message[OperationParam::S3HandlingServiceFileDetails.getValue()] = parsedDetails;
        ServerCall * sc = new ServerCall(ServiceName::S3Handling, ServiceOperation::GetUpdatedFiles, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

    void BrainCloudS3Handling::getFileList(const char * in_category, IServerCallback * in_callback)
    {
        Json::Value message;

        if (StringUtil::IsOptionalParameterValid(in_category)) {
            message[OperationParam::S3HandlingServiceCategory.getValue()] = in_category;
        }

        ServerCall * sc = new ServerCall(ServiceName::S3Handling, ServiceOperation::GetFileList, message, in_callback);
        m_client->getBrainCloudComms()->addToQueue(sc);
    }

	void BrainCloudS3Handling::getCDNUrl(const char * in_fileId, IServerCallback * in_callback)
	{
		Json::Value message;
		message[OperationParam::S3HandlingServiceFileId.getValue()] = in_fileId;

		ServerCall * sc = new ServerCall(ServiceName::S3Handling, ServiceOperation::GetCdnUrl, message, in_callback);
		m_client->getBrainCloudComms()->addToQueue(sc);
	}
}