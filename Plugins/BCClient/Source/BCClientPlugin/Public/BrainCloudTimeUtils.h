// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudTimeUtils
{
  public:
    BrainCloudTimeUtils(BrainCloudClient *client);

    static int64 UTCDateTimeToUTCMillis(FDateTime dateTime);
    static FDateTime UTCMillisToUTCDateTime(int64 utcDateTime);
    static FDateTime LocalTimeToUTCTime(FDateTime localDate);
    static FDateTime UTCTimeToLocalTime(FDateTime utcDate);
      
  private:
    BrainCloudClient *_client = nullptr;
};
