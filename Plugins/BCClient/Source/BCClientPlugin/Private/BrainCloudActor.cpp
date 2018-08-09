// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudActor.h"
#include "BrainCloudWrapper.h"

ABrainCloudActor::ABrainCloudActor()
{
	BCWrapper = NewObject<UBrainCloudWrapper>();
}

ABrainCloudActor::ABrainCloudActor(FString &wrapperName)
{
	BCWrapper = NewObject<UBrainCloudWrapper>();
}

void ABrainCloudActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABrainCloudActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	this->RemoveFromRoot();
}

void ABrainCloudActor::BeginDestroy()
{
	Super::BeginDestroy();

	if (!this->IsValidLowLevel())
	{
		return;
	}

	this->RemoveFromRoot();

	this->Destroy();
	this->ConditionalBeginDestroy();

	BCWrapper->ConditionalBeginDestroy();
}
