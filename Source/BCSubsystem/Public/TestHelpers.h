// Copyright 2015 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TestHelpers.generated.h"

/**s
 * 
 */
UCLASS()
class BCSUBSYSTEM_API UTestHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "Test Utility")
	static bool GetUseCompression();

	UFUNCTION(BlueprintPure, Category = "Time")
	static int64 DateTimeToUnixTimestampMs(const FDateTime& DateTime);
};
