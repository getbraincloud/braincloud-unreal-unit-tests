// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "UnitTestHelpers.generated.h"

USTRUCT(BlueprintType)
struct FBrainCloudInitParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "brainCloud Init Params")
		FString ServerUrl = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "brainCloud Init Params")
		FString AppId = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "brainCloud Init Params")
		FString Secret = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "brainCloud Init Params")
		FString Version = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "brainCloud Init Params")
		FString ChildAppId = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "brainCloud Init Params")
		FString ParentLevelName = "";
};

UCLASS(MinimalAPI)
class UUnitTestHelpers : public UObject
{
	GENERATED_BODY()

public:
	UUnitTestHelpers(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Unit Test Helpers")
		static FBrainCloudInitParams InitializeFromFile();
};