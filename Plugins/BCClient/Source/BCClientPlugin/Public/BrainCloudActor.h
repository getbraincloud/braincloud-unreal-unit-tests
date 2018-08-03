// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "BrainCloudActor.generated.h"

class BrainCloudWrapper;

/**
 * An actor to contain an instance of the brainCloud wrapper.
 */
UCLASS()
class BCCLIENTPLUGIN_API ABrainCloudActor : public AActor
{
	GENERATED_BODY()

  public:
	BrainCloudWrapper *BCWrapper = nullptr;

	ABrainCloudActor();
	ABrainCloudActor(FString &wrapperName);

	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
	virtual void BeginDestroy() override;
};
