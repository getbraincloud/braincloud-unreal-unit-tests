// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BCCLIENTPLUGIN_API BrainCloudUtil
{
  public:
    BrainCloudUtil(BrainCloudClient *client);

    static long ToEpochTime(FDateTime dateTime);
    static FDateTime ToDateTimeFromEpoch(long utcDateTime);
    static FDateTime ToDateTimeOffsetFromEpoch(long utcDateTime);
};
