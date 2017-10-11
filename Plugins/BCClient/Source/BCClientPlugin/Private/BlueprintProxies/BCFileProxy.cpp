// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCFileProxy.h"

UBCFileProxy::UBCFileProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCFileProxy* UBCFileProxy::UploadFile(
    const FString& cloudPath,
    const FString& cloudFilename,
    bool shareable,
    bool replaceIfExists,
    const FString& localPath)
{
    UBCFileProxy* Proxy = NewObject<UBCFileProxy>();
    BrainCloudClient::getInstance()->getFileService()->uploadFile(cloudPath, cloudFilename, shareable, replaceIfExists, localPath, Proxy);
    return Proxy;
}

UBCFileProxy* UBCFileProxy::ListUserFiles(const FString& cloudPath, bool recurse)
{
    UBCFileProxy* Proxy = NewObject<UBCFileProxy>();
    BrainCloudClient::getInstance()->getFileService()->listUserFiles(cloudPath, recurse, Proxy);
    return Proxy;
}

UBCFileProxy* UBCFileProxy::DeleteUserFile(const FString& cloudPath, const FString& cloudFilename)
{
    UBCFileProxy* Proxy = NewObject<UBCFileProxy>();
    BrainCloudClient::getInstance()->getFileService()->deleteUserFile(cloudPath, cloudFilename, Proxy);
    return Proxy;
}

UBCFileProxy* UBCFileProxy::DeleteUserFiles(const FString& cloudPath, bool recurse)
{
    UBCFileProxy* Proxy = NewObject<UBCFileProxy>();
    BrainCloudClient::getInstance()->getFileService()->deleteUserFiles(cloudPath, recurse, Proxy);
    return Proxy;
}

UBCFileProxy* UBCFileProxy::GetCDNUrl(const FString& cloudPath, const FString& cloudFileName)
{
	UBCFileProxy* Proxy = NewObject<UBCFileProxy>();
	BrainCloudClient::getInstance()->getFileService()->getCDNUrl(cloudPath, cloudFileName, Proxy);
	return Proxy;
}

void UBCFileProxy::CancelUpload(const FString& uploadId)
{
    BrainCloudClient::getInstance()->getFileService()->cancelUpload(uploadId);
}

float UBCFileProxy::GetUploadProgress(const FString& uploadId)
{
    return BrainCloudClient::getInstance()->getFileService()->getUploadProgress(uploadId);
}

int32 UBCFileProxy::GetUploadBytesTransferred(const FString& uploadId)
{
    return BrainCloudClient::getInstance()->getFileService()->getUploadBytesTransferred(uploadId);
}

int32 UBCFileProxy::GetUploadTotalBytesToTransfer(const FString& uploadId)
{
    return BrainCloudClient::getInstance()->getFileService()->getUploadTotalBytesToTransfer(uploadId);
}

//callbacks
void UBCFileProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCFileProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

