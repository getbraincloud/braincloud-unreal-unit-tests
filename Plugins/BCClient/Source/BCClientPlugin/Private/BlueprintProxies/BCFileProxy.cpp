// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloud.h"
#include "BCWrapperProxy.h"
#include "BCFileProxy.h"
#include "BrainCloudWrapper.h"

UBCFileProxy::UBCFileProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCFileProxy* UBCFileProxy::UploadFile(
	ABrainCloud *brainCloud,
    const FString& cloudPath,
    const FString& cloudFilename,
    bool shareable,
    bool replaceIfExists,
    const FString& localPath)
{
    UBCFileProxy* Proxy = NewObject<UBCFileProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFileService()->uploadFile(cloudPath, cloudFilename, shareable, replaceIfExists, localPath, Proxy);
    return Proxy;
}

UBCFileProxy* UBCFileProxy::ListUserFiles(ABrainCloud *brainCloud, const FString& cloudPath, bool recurse)
{
    UBCFileProxy* Proxy = NewObject<UBCFileProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFileService()->listUserFiles(cloudPath, recurse, Proxy);
    return Proxy;
}

UBCFileProxy* UBCFileProxy::DeleteUserFile(ABrainCloud *brainCloud, const FString& cloudPath, const FString& cloudFilename)
{
    UBCFileProxy* Proxy = NewObject<UBCFileProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFileService()->deleteUserFile(cloudPath, cloudFilename, Proxy);
    return Proxy;
}

UBCFileProxy* UBCFileProxy::DeleteUserFiles(ABrainCloud *brainCloud, const FString& cloudPath, bool recurse)
{
    UBCFileProxy* Proxy = NewObject<UBCFileProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFileService()->deleteUserFiles(cloudPath, recurse, Proxy);
    return Proxy;
}

UBCFileProxy* UBCFileProxy::GetCDNUrl(ABrainCloud *brainCloud, const FString& cloudPath, const FString& cloudFileName)
{
	UBCFileProxy* Proxy = NewObject<UBCFileProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFileService()->getCDNUrl(cloudPath, cloudFileName, Proxy);
	return Proxy;
}

void UBCFileProxy::CancelUpload(ABrainCloud *brainCloud, const FString& uploadId)
{
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFileService()->cancelUpload(uploadId);
}

float UBCFileProxy::GetUploadProgress(ABrainCloud *brainCloud, const FString& uploadId)
{
    return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFileService()->getUploadProgress(uploadId);
}

int32 UBCFileProxy::GetUploadBytesTransferred(ABrainCloud *brainCloud, const FString& uploadId)
{
    return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFileService()->getUploadBytesTransferred(uploadId);
}

int32 UBCFileProxy::GetUploadTotalBytesToTransfer(ABrainCloud *brainCloud, const FString& uploadId)
{
    return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getFileService()->getUploadTotalBytesToTransfer(uploadId);
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

