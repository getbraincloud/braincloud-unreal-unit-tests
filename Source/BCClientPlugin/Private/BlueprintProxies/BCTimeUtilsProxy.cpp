// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCTimeUtilsProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

UBCTimeUtilsProxy::UBCTimeUtilsProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

int64 UBCTimeUtilsProxy::UTCDateTimeToUTCMillisBP(FDateTime utcDate)
{
    return BrainCloudTimeUtils::UTCDateTimeToUTCMillis(utcDate);
}	

FDateTime UBCTimeUtilsProxy::UTCMillisToUTCDateTime(int64 utcDate)
{
    return BrainCloudTimeUtils::UTCMillisToUTCDateTime(utcDate);
}	

FDateTime UBCTimeUtilsProxy::LocalTimeToUTCTimeBP(FDateTime utcDate)
{
    return BrainCloudTimeUtils::LocalTimeToUTCTime(utcDate);
}	

FDateTime UBCTimeUtilsProxy::UTCTimeToLocalTimeBP(FDateTime utcDate)
{
    return BrainCloudTimeUtils::UTCTimeToLocalTime(utcDate);
}	

