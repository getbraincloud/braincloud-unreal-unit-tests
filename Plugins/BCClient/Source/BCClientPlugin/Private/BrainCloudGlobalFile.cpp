// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudGlobalFile.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudGlobalFile::BrainCloudGlobalFile(BrainCloudClient *client) : _client(client){};


void BrainCloudGlobalFile::getFileInfo(const FString &fileId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GlobalFileFileId.getValue(), fileId);

	ServerCall *sc = new ServerCall(ServiceName::GlobalFile, ServiceOperation::GetFileInfo, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGlobalFile::getFileInfoSimple(const FString &fileName, const FString &folderPath, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GlobalFileFileName.getValue(), fileName);
    message->SetStringField(OperationParam::GlobalFileFolderPath.getValue(), folderPath);

	ServerCall *sc = new ServerCall(ServiceName::GlobalFile, ServiceOperation::GetFileInfoSimple, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGlobalFile::getGlobalCDNUrl(const FString &fileId, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GlobalFileFileId.getValue(), fileId);

	ServerCall *sc = new ServerCall(ServiceName::GlobalFile, ServiceOperation::GetGlobalCDNUrl, message, callback);
	_client->sendRequest(sc);
}

void BrainCloudGlobalFile::getGlobalFileList(const FString &folderPath, bool recurse, IServerCallback *callback)
{
	TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
	message->SetStringField(OperationParam::GlobalFileFolderPath.getValue(), folderPath);
    message->SetBoolField(OperationParam::GlobalFileRecurse.getValue(), recurse);

	ServerCall *sc = new ServerCall(ServiceName::GlobalFile, ServiceOperation::GetGlobalFileList, message, callback);
	_client->sendRequest(sc);
}
