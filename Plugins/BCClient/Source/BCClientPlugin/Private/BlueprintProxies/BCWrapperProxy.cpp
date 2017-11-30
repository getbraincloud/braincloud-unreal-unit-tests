// Copyright 2015 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "ServerCall.h"
#include "BrainCloud.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

ABrainCloud* UBCWrapperProxy::DefaultBrainCloudInstance = nullptr;

UBCWrapperProxy::UBCWrapperProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

ABrainCloud* UBCWrapperProxy::CreateBrainCloudActor(const FString& wrapperName)
{
	ABrainCloud *brainCloudActor = ConstructObject<ABrainCloud>(ABrainCloud::StaticClass());
	brainCloudActor->AddToRoot();
	brainCloudActor->WrapperName = wrapperName;
	return brainCloudActor;
}

void UBCWrapperProxy::SetDefaultBrainCloudInstance(ABrainCloud *brainCloud)
{
	DefaultBrainCloudInstance = brainCloud;
}

void UBCWrapperProxy::ClearDefaultBrainCloudInstance()
{
	DefaultBrainCloudInstance = nullptr;
}

BrainCloudWrapper *UBCWrapperProxy::GetBrainCloudInstance(ABrainCloud *brainCloud)
{
	// Using a passed in instance of brainCloud
	if (brainCloud != nullptr) 
	{
		return brainCloud->BrainCloud;
	}
	// Using a default state instance of brainCloud
	else if (DefaultBrainCloudInstance != nullptr) 
	{
		return DefaultBrainCloudInstance->BrainCloud;
	}
	// Using the brainCloud singleton (not recommended)
	else 
	{
		return BrainCloudWrapper::getInstance();
	}
}

//callbacks
void UBCWrapperProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
	// unused
}

void UBCWrapperProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
	// unused
}
