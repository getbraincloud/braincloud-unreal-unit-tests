// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "Misc/Paths.h"
#include "Modules/ModuleManager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "brainCloud Init Params")
		FString PeerName = "";
};

UCLASS(MinimalAPI)
class UUnitTestHelpers : public UObject
{
	GENERATED_BODY()

public:
	UUnitTestHelpers(const FObjectInitializer& ObjectInitializer);

    // deprecated: use ids.h and InitializeFromHeader below
	UFUNCTION(BlueprintCallable, Category = "Unit Test Helpers")
		static FBrainCloudInitParams InitializeFromFile();

    /*
     use this to initialize braincloud
     modify the file at Source/[projectname]/ids.h
     */
	UFUNCTION(BlueprintCallable, Category = "Unit Test Helpers")
		static FBrainCloudInitParams InitializeFromHeader();
};
