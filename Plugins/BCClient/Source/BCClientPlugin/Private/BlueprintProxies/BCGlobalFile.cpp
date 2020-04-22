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

UBCGlobalFileProxy *UBCGlobalFileProxy::GetFileInfo(UBrainCloudWrapper *brainCloud, const FString &fileId)
{
    UBCGlobalFileProxy *Proxy = NewObject<UBCGlobalFileProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalFileService()->readProperties(Proxy, fileId);
    return Proxy;
}

UBCGlobalFileProxy *UBCGlobalFileProxy::GetFileInfoSimple(UBrainCloudWrapper *brainCloud, const FString &fileId, const FString &folderPath)
{
    UBCGlobalFileProxy *Proxy = NewObject<UBCGlobalFileProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalFileService()->readProperties(Proxy, fileId, folderPath);
    return Proxy;
}

UBCGlobalFileProxy *UBCGlobalFileProxy::GetGlobalCDNUrl(UBrainCloudWrapper *brainCloud, const FString &fileId)
{
    UBCGlobalFileProxy *Proxy = NewObject<UBCGlobalFileProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalFileService()->readProperties(Proxy, fileId);
    return Proxy;
}

UBCGlobalFileProxy *UBCGlobalFileProxy::GetGlobalFileList(UBrainCloudWrapper *brainCloudconst FString &folderPath, bool recurse)
{
    UBCGlobalFileProxy *Proxy = NewObject<UBCGlobalFileProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getGlobalFileService()->readProperties(Proxy, folderPath, recurse);
    return Proxy;
}
