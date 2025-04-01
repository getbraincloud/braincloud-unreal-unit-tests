// Copyright 2015 bitHeads, Inc. All Rights Reserved.
#include "TestHelpers.h"

bool UTestHelpers::GetUseCompression()
{
	FString value = FPlatformMisc::GetEnvironmentVariable(TEXT("USE_COMPRESSION"));
	return value.Equals(TEXT("true"), ESearchCase::IgnoreCase);
}
