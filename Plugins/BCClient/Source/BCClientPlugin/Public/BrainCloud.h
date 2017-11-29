// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "BrainCloud.generated.h"

class BrainCloudWrapper;

/**
 * An actor to contain an instance of the brainCloud wrapper.
 */
UCLASS()
class BCCLIENTPLUGIN_API ABrainCloud : public AActor
{
	GENERATED_BODY()

public:
	BrainCloudWrapper *BrainCloud = nullptr;

	UPROPERTY()
		FString WrapperName;
	
	ABrainCloud();
	ABrainCloud(FString& wrapperName);

	~ABrainCloud();

	void BeginPlay();
};
