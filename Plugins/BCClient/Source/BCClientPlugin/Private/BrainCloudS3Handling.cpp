// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudS3Handling.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudS3Handling::BrainCloudS3Handling(BrainCloudClient *client) : _client(client){};

void BrainCloudS3Handling::getUpdatedFiles(const FString &category, const FString &fileDetails, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

	if (OperationParam::isOptionalParamValid(category))
	{
		message->SetStringField(OperationParam::S3HandlingServiceCategory.getValue(), category);
	}
	message->SetObjectField(OperationParam::PlayerStateServiceReadEntitySubtype.getValue(), JsonUtil::jsonStringToValue(fileDetails));

	ServerCall *sc = new ServerCall(ServiceName::S3Handling, ServiceOperation::GetUpdatedFiles, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudS3Handling::getFileList(const FString &category, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

	if (OperationParam::isOptionalParamValid(category))
	{
		message->SetStringField(OperationParam::S3HandlingServiceCategory.getValue(), category);
	}

	ServerCall *sc = new ServerCall(ServiceName::S3Handling, ServiceOperation::GetFileList, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudS3Handling::getCDNUrl(const FString &fileId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::S3HandlingServiceFileId.getValue(), fileId);

	ServerCall *sc = new ServerCall(ServiceName::S3Handling, ServiceOperation::GetCdnUrl, message, callback);
	_client->sendRequest(sc);
}