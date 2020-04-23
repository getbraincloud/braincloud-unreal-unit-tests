// Copyright 2018 bitHeads, Inc. All Rights Reserved.

//#include "BrainCloudUserItems.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
//#include "ServerCall.h"
//#include "JsonUtil.h"
#include "BrainCloudUtils.h"

BrainCloudUtils::BrainCloudUtils(BrainCloudClient *client) {}; //_client(client) {};

//this one done right?
static long ToEpochTime(const FDateTime dateTime)
{
FTimespan mySpan;
FDateTime date = dateTime.UtcNow;
FDateTime myFDateTime(1970, 1, 1, 0, 0, 0, 0);
int64 ticks = date.GetTicks() - myFDateTime.GetTicks();
int64 ts = ticks / mySpan.GetTicks();
return ts;
}


//redo 
/// Converts the given epoch time to a <see cref="DateTime"/> with <see cref="DateTimeKind.Utc"/> kind.
static FDateTime ToDateTimeFromEpoch(long intDate)
{
      
   FTimespan mySpan;
   FDateTime timeInTicks = intDate * mySpan.GetTicks();
  
   FDateTime myFDateTime= FDateTime(1970, 1, 1, 0, 0, 0, 0)+timeInTicks.GetTicks();


return myFDateTime;
}

static FDateTime ToDateTimeOffsetFromEpoch(long intDate)
{
FTimespan mySpan;
int64 timeInTicks = intDate * mySpan.GetTicks();
FDateTime myDateTime= FDateTime(1970, 1, 1, 0, 0, 0).GetTicks()+timeInTicks;
return myDateTime;
}
//this in all
//now for locaal