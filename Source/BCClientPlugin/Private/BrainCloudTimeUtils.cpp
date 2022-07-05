// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudTimeUtils.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudWrapper.h"
#include "BCWrapperProxy.h"

BrainCloudTimeUtils::BrainCloudTimeUtils(BrainCloudClient *client) : _client(client){};

int64 BrainCloudTimeUtils::UTCDateTimeToUTCMillis(FDateTime dateTime)
{
    return (dateTime.GetTicks() - FDateTime(1970, 1, 1).GetTicks()) / ETimespan::TicksPerMillisecond;
}

FDateTime BrainCloudTimeUtils::UTCMillisToUTCDateTime(int64 utcDateTime)
{
    return FDateTime(1970, 1, 1) + FTimespan(utcDateTime * ETimespan::TicksPerMillisecond);
}

FDateTime BrainCloudTimeUtils::LocalTimeToUTCTime(FDateTime localDate)
{
    return localDate.UtcNow();
}
    
FDateTime BrainCloudTimeUtils::UTCTimeToLocalTime (FDateTime utcDate)
{
    return utcDate.Now();
}

