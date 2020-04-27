// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudUtil.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudWrapper.h"
#include "BCWrapperProxy.h"

long BrainCloudUtil::ToEpochTime(FDateTime dateTime)
{
    FTimespan mySpan;
    FDateTime date = dateTime.UtcNow;
    FDateTime myFDateTime(1970, 1, 1, 0, 0, 0, 0);
    int64 ticks = date.GetTicks() - myFDateTime.GetTicks();
    int64 ts = ticks / mySpan.GetTicks();
    return ts;
}

FDateTime BrainCloudUtil::ToDateTimeFromEpoch(long utcDateTime)
{
    FTimespan mySpan;
    FDateTime timeInTicks = intDate * mySpan.GetTicks();
    FDateTime myFDateTime= FDateTime(1970, 1, 1, 0, 0, 0, 0)+timeInTicks.GetTicks();
    return myFDateTime;
}
FDateTime BrainCloudUtil::ToDateTimeOffsetFromEpoch(long utcDateTime)
{
    FTimespan mySpan;
    int64 timeInTicks = intDate * mySpan.GetTicks();
    FDateTime myDateTime= FDateTime(1970, 1, 1, 0, 0, 0).GetTicks()+timeInTicks;
    return myDateTime;
}
