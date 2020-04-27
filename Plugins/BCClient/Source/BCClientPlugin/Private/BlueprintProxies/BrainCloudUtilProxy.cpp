// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudUtilProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

BrainCloudUtilProxy::BrainCloudUtilProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

BrainCloudUtilProxy *BrainCloudUtilProxy::ToEpochTime(UBrainCloudWrapper *brainCloudWrapper, FDateTime dateTime)
{
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUtil()->ToEpochTime(dateTime);
}

BrainCloudUtilProxy *BrainCloudUtilProxy::ToDateTimeFromEpoch(UBrainCloudWrapper *brainCloudWrapper, long utcDateTime)
{
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUtil()->ToDateTimeFromEpoch(utcDateTime);
}

BrainCloudUtilProxy *BrainCloudUtilProxy::ToDateTimeOffsetFromEpoch(UBrainCloudWrapper *brainCloudWrapper, long utcDateTime)
{
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getUtil()->ToDateTimeOffsetFromEpoch(utcDateTime);
}
