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

ABrainCloud::~ABrainCloud()
{
	if (BrainCloud != nullptr)
	{
		delete BrainCloud;
	}

	BrainCloud = nullptr;
}

void ABrainCloud::BeginPlay()
{
	BrainCloud->setWrapperName(WrapperName);
}
