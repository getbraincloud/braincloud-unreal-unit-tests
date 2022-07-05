// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudFile.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"
#include "BrainCloudComms.h"

BrainCloudFile::BrainCloudFile(BrainCloudClient *client) : _client(client){};

bool BrainCloudFile::uploadFile(
    const FString &cloudPath,
    const FString &cloudFilename,
    bool shareable,
    bool replaceIfExists,
    const FString &localPath,
    IServerCallback *callback)
{
    if (!FPaths::FileExists(localPath))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed uploading file at '%s': File not found\n"), *localPath);
        return false;
    }

    int64 FileSize = FPlatformFileManager::Get().GetPlatformFile().FileSize(*localPath);

    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::UploadCloudPath.getValue(), cloudPath);
    message->SetStringField(OperationParam::UploadCloudFilename.getValue(), cloudFilename);
    message->SetBoolField(OperationParam::UploadShareable.getValue(), shareable);
    message->SetBoolField(OperationParam::UploadReplaceIfExists.getValue(), replaceIfExists);
    message->SetNumberField(OperationParam::UploadFileSize.getValue(), FileSize);
    message->SetStringField(OperationParam::UploadLocalPath.getValue(), localPath);

    ServerCall *sc = new ServerCall(ServiceName::File, ServiceOperation::PrepareUserUpload, message, callback);
    _client->sendRequest(sc);

    return true;
}

void BrainCloudFile::listUserFiles(IServerCallback *callback)
{
    listUserFiles(TEXT(""), true, callback);
}

void BrainCloudFile::listUserFiles(const FString &cloudPath, bool recurse, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    if (OperationParam::isOptionalParamValid(cloudPath))
        message->SetStringField(OperationParam::UploadCloudPath.getValue(), cloudPath);
    message->SetBoolField(OperationParam::UploadRecurse.getValue(), recurse);

    ServerCall *sc = new ServerCall(ServiceName::File, ServiceOperation::ListUserFiles, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudFile::deleteUserFile(const FString &cloudPath, const FString &cloudFilename, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::UploadCloudPath.getValue(), cloudPath);
    message->SetStringField(OperationParam::UploadCloudFilename.getValue(), cloudFilename);

    ServerCall *sc = new ServerCall(ServiceName::File, ServiceOperation::DeleteUserFiles, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudFile::deleteUserFiles(const FString &cloudPath, bool recurse, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::UploadCloudPath.getValue(), cloudPath);
    message->SetBoolField(OperationParam::UploadRecurse.getValue(), recurse);

    ServerCall *sc = new ServerCall(ServiceName::File, ServiceOperation::DeleteUserFiles, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudFile::getCDNUrl(const FString &cloudPath, const FString &cloudFileName, IServerCallback *callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::UploadCloudPath.getValue(), cloudPath);
    message->SetStringField(OperationParam::UploadCloudFilename.getValue(), cloudFileName);

    ServerCall *sc = new ServerCall(ServiceName::File, ServiceOperation::GetCdnUrl, message, callback);
    _client->sendRequest(sc);
}

void BrainCloudFile::cancelUpload(const FString &uploadId)
{
    _client->getBrainCloudComms()->CancelUpload(uploadId);
}

float BrainCloudFile::getUploadProgress(const FString &uploadId)
{
    return _client->getBrainCloudComms()->GetUploadProgress(uploadId);
}

int32 BrainCloudFile::getUploadBytesTransferred(const FString &uploadId)
{
    return _client->getBrainCloudComms()->GetUploadBytesTransferred(uploadId);
}

int32 BrainCloudFile::getUploadTotalBytesToTransfer(const FString &uploadId)
{
    return _client->getBrainCloudComms()->GetUploadTotalBytesToTransfer(uploadId);
}