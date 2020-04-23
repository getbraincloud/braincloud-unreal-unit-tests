// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

//class IEventCallback;
//class IRewardCallback;
//class IFileUploadCallback;
//class IGlobalErrorCallback;
//class INetworkErrorCallback;
//class ServerCall;
//class BCFileUploader;
#include "Misc/DateTime.h"
class BrainCloudClient;
//class UBCBlueprintRestCallProxyBase;

class BrainCloudUtils
{

  public:
	BrainCloudUtils(BrainCloudClient *client);
	~BrainCloudUtils();

/// Converts the given date value to epoch time.
static long ToEpochTime(FDateTime dateTime);

/// Converts the given epoch time to a <see cref="DateTime"/> with <see cref="DateTimeKind.Utc"/> kind.
static FDateTime ToDateTimeFromEpoch(long intDate);
//this in all

/// Converts the given epoch time to a UTC <see cref="DateTimeOffset"/>.
static FDateTime ToDateTimeOffsetFromEpoch(long intDate);

//????got rid of?
};
