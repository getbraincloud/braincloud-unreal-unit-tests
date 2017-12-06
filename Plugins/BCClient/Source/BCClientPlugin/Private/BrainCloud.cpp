// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloud.h"
#include "BrainCloudWrapper.h"

ABrainCloud::ABrainCloud() : WrapperName(TEXT(""))
{
	BrainCloud = new BrainCloudWrapper();
}

ABrainCloud::ABrainCloud(FString& wrapperName)
{
	WrapperName = wrapperName;
	BrainCloud = new BrainCloudWrapper(wrapperName);
}


void ABrainCloud::BeginPlay()
{
	AActor::BeginPlay();

	BrainCloud->setWrapperName(WrapperName);
}


void ABrainCloud::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	AActor::EndPlay(EndPlayReason);

	this->RemoveFromRoot();
	
}

void ABrainCloud::BeginDestroy()
{
	AActor::BeginDestroy();

	if (!this->IsValidLowLevel()) {
		return;
	}

	this->RemoveFromRoot();

	this->Destroy();
	this->ConditionalBeginDestroy();

	delete BrainCloud;
	BrainCloud = nullptr;
}

