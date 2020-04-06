// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCS3HandlingProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCS3HandlingProxy::UBCS3HandlingProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCS3HandlingProxy *UBCS3HandlingProxy::GetUpdatedFiles(UBrainCloudWrapper *brainCloudWrapper, FString category, FString fileDetails)
{
    UBCS3HandlingProxy *Proxy = NewObject<UBCS3HandlingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getS3HandlingService()->getUpdatedFiles(category, fileDetails, Proxy);
    return Proxy;
}

UBCS3HandlingProxy *UBCS3HandlingProxy::GetFileList(UBrainCloudWrapper *brainCloudWrapper, FString category)
{
    UBCS3HandlingProxy *Proxy = NewObject<UBCS3HandlingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getS3HandlingService()->getFileList(category, Proxy);
    return Proxy;
}

UBCS3HandlingProxy *UBCS3HandlingProxy::GetCDNUrl(UBrainCloudWrapper *brainCloudWrapper, const FString &fileId)
{
    UBCS3HandlingProxy *Proxy = NewObject<UBCS3HandlingProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getS3HandlingService()->getCDNUrl(fileId, Proxy);
    return Proxy;
}
