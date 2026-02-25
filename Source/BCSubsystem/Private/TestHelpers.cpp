// Copyright 2015 bitHeads, Inc. All Rights Reserved.
#include "TestHelpers.h"

bool UTestHelpers::GetUseCompression()
{
	FString value = FPlatformMisc::GetEnvironmentVariable(TEXT("USE_COMPRESSION"));
	return value.Equals(TEXT("true"), ESearchCase::IgnoreCase);
}

int64 UTestHelpers::DateTimeToUnixTimestampMs(const FDateTime& DateTime)
{
	return DateTime.ToUnixTimestamp() * 1000LL;
}
