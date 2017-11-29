// Copyright 2015 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BrainCloudACL.h"

#include "BCWrapperProxy.generated.h"

class ABrainCloud;

UCLASS(BlueprintType)
class UBCWrapperProxy : public UBCBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	static ABrainCloud *DefaultBrainCloudInstance;

	UBCWrapperProxy(const FObjectInitializer& ObjectInitializer);
	
	/**
	* Create an actor that contains its own instance of the brainCloud Wrapper
	* @param brainCloud - An actor that contains its own instance of the brainCloud Wrapper
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud")
		static ABrainCloud *CreateBrainCloudActor(const FString& wrapperName);

	/**
	* Set a default brainCloud instance to be used when none is provided.
	* When not set, the brainCloud Singleton will be used
	* @param brainCloud - An actor that contains its own instance of the brainCloud Wrapper
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud")
		static void SetDefaultBrainCloudInstance(ABrainCloud *brainCloud);

	/**
	* Clear the default brainCloud instance
	* When not set, the brainCloud Singleton will be used
	*/
	UFUNCTION(BlueprintCallable, Category = "BrainCloud")
		static void ClearDefaultBrainCloudInstance();

	/**
	* Returns a non null reference to brainCloud
	*
	* @param brainCloud - An actor that contains its own instance of the brainCloud Wrapper
	*/
	static BrainCloudWrapper *GetBrainCloudInstance(ABrainCloud *brainCloud);

protected:
	// IServerCallback interface
	void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
	void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
	// End of IServerCallback interface
};
