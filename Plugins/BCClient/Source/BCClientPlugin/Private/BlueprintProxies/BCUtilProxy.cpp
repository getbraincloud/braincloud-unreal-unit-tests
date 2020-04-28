// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCUtilProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCUtilProxy::UBCUtilProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCUtilProxy *UBCUtilProxy::ToEpochTime(UBrainCloudWrapper *brainCloudWrapper, FDateTime dateTime)
{
    UBCUtilProxy *Proxy = NewObject<UBCUtilProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUtil()->ToEpochTime(dateTime);
    return Proxy;
}

UBCUtilProxy *UBCUtilProxy::ToDateTimeFromEpoch(UBrainCloudWrapper *brainCloudWrapper, int64 utcDateTime)
{
    UBCUtilProxy *Proxy = NewObject<UBCUtilProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUtil()->ToDateTimeFromEpoch(utcDateTime);
    return Proxy;
}

UBCUtilProxy *UBCUtilProxy::ToDateTimeOffsetFromEpoch(UBrainCloudWrapper *brainCloudWrapper, int64 utcDateTime)
{
    UBCUtilProxy *Proxy = NewObject<UBCUtilProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUtil()->ToDateTimeOffsetFromEpoch(utcDateTime);
    return Proxy;
}
