// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCFileProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCFileProxy::UBCFileProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCFileProxy *UBCFileProxy::UploadFile(
    UBrainCloudWrapper *brainCloudWrapper,
    const FString &cloudPath,
    const FString &cloudFilename,
    bool shareable,
    bool replaceIfExists,
    const FString &localPath)
{
    UBCFileProxy *Proxy = NewObject<UBCFileProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFileService()->uploadFile(cloudPath, cloudFilename, shareable, replaceIfExists, localPath, Proxy);
    return Proxy;
}

UBCFileProxy *UBCFileProxy::ListUserFiles(UBrainCloudWrapper *brainCloudWrapper, const FString &cloudPath, bool recurse)
{
    UBCFileProxy *Proxy = NewObject<UBCFileProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFileService()->listUserFiles(cloudPath, recurse, Proxy);
    return Proxy;
}

UBCFileProxy *UBCFileProxy::DeleteUserFile(UBrainCloudWrapper *brainCloudWrapper, const FString &cloudPath, const FString &cloudFilename)
{
    UBCFileProxy *Proxy = NewObject<UBCFileProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFileService()->deleteUserFile(cloudPath, cloudFilename, Proxy);
    return Proxy;
}

UBCFileProxy *UBCFileProxy::DeleteUserFiles(UBrainCloudWrapper *brainCloudWrapper, const FString &cloudPath, bool recurse)
{
    UBCFileProxy *Proxy = NewObject<UBCFileProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFileService()->deleteUserFiles(cloudPath, recurse, Proxy);
    return Proxy;
}

UBCFileProxy *UBCFileProxy::GetCDNUrl(UBrainCloudWrapper *brainCloudWrapper, const FString &cloudPath, const FString &cloudFileName)
{
    UBCFileProxy *Proxy = NewObject<UBCFileProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFileService()->getCDNUrl(cloudPath, cloudFileName, Proxy);
    return Proxy;
}

void UBCFileProxy::CancelUpload(UBrainCloudWrapper *brainCloudWrapper, const FString &uploadId)
{
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFileService()->cancelUpload(uploadId);
}

float UBCFileProxy::GetUploadProgress(UBrainCloudWrapper *brainCloudWrapper, const FString &uploadId)
{
    return UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFileService()->getUploadProgress(uploadId);
}

int32 UBCFileProxy::GetUploadBytesTransferred(UBrainCloudWrapper *brainCloudWrapper, const FString &uploadId)
{
    return UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFileService()->getUploadBytesTransferred(uploadId);
}

int32 UBCFileProxy::GetUploadTotalBytesToTransfer(UBrainCloudWrapper *brainCloudWrapper, const FString &uploadId)
{
    return UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getFileService()->getUploadTotalBytesToTransfer(uploadId);
}
