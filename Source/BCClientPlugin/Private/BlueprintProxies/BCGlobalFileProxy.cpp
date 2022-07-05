// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCGlobalFileProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCGlobalFileProxy::UBCGlobalFileProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCGlobalFileProxy *UBCGlobalFileProxy::GetFileInfo(UBrainCloudWrapper *brainCloudWrapper, const FString &fileId)
{
    UBCGlobalFileProxy *Proxy = NewObject<UBCGlobalFileProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalFileService()->getFileInfo(fileId, Proxy);
    return Proxy;
}

UBCGlobalFileProxy *UBCGlobalFileProxy::GetFileInfoSimple(UBrainCloudWrapper *brainCloudWrapper, const FString &fileName, const FString &folderPath)
{
    UBCGlobalFileProxy *Proxy = NewObject<UBCGlobalFileProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalFileService()->getFileInfoSimple(fileName, folderPath, Proxy);
    return Proxy;
}

UBCGlobalFileProxy *UBCGlobalFileProxy::GetGlobalCDNUrl(UBrainCloudWrapper *brainCloudWrapper, const FString &fileId)
{
    UBCGlobalFileProxy *Proxy = NewObject<UBCGlobalFileProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalFileService()->getGlobalCDNUrl(fileId, Proxy);
    return Proxy;
}

UBCGlobalFileProxy *UBCGlobalFileProxy::GetGlobalFileList(UBrainCloudWrapper *brainCloudWrapper, const FString &folderPath, bool recurse)
{
    UBCGlobalFileProxy *Proxy = NewObject<UBCGlobalFileProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalFileService()->getGlobalFileList(folderPath, recurse, Proxy);
    return Proxy;
}
