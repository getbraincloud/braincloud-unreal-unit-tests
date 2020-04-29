// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCUtilProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCUtilProxy::UBCUtilProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// UBCUtilProxy *UBCUtilProxy::ToUTCEpochTime(UBrainCloudWrapper *brainCloudWrapper, FDateTime dateTime)
// {
//     UBCUtilProxy *Proxy = NewObject<UBCUtilProxy>();
//     UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUtil()->ToUTCEpochTime(dateTime);
//     return Proxy;
// }

// UBCUtilProxy *UBCUtilProxy::ToDateTimeFromUTCEpoch(UBrainCloudWrapper *brainCloudWrapper, int64 utcDateTime)
// {
//     UBCUtilProxy *Proxy = NewObject<UBCUtilProxy>();
//     UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUtil()->ToDateTimeFromUTCEpoch(utcDateTime);
//     return Proxy;
// }
