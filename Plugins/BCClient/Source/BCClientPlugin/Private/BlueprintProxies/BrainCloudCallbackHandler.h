// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IFileUploadCallback.h"
#include "IEventCallback.h"
#include "IRewardCallback.h"
#include "IGlobalErrorCallback.h"
#include "INetworkErrorCallback.h"

#include "BrainCloudCallbackHandler.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBCFileCallbackCompletedDelegate, const FString&, fileUploadId, const FString&, jsonResponse);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FBCFileCallbackFailedDelegate, const FString&, fileUploadId, int32, statusCode, int32, reasonCode, const FString&, jsonResponse);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBCRewardDelegate,const FString&, jsonData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBCEventDelegate, const FString&, jsonData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FBCGlobalErrorDelegate, const FString&, serviceName, const FString&, serviceOperation, int32, statusCode, int32, reasonCode, const FString&, jsonResponse);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBCNetworkErrorDelegate);

class UBrainCloudWrapper;
class ServiceName;
class ServiceOperation;

UCLASS(BlueprintType)
class UBrainCloudCallbackHandler : 
    public UObject, 
    public IFileUploadCallback, 
    public IEventCallback, 
    public IRewardCallback, 
    public IGlobalErrorCallback, 
    public INetworkErrorCallback
{
    GENERATED_BODY()

public:
    UBrainCloudCallbackHandler(const FObjectInitializer& ObjectInitializer);

    virtual void BeginDestroy() override;

    /**
    * Method returns the server time in UTC. This is in UNIX millis time format.
    * For instance 1396378241893 represents 2014-04-01 2:50:41.893 in GMT-4.
    *
    * Service Name - Time
    * Service Operation - Read
    */
    UFUNCTION(BlueprintCallable, Category = "BrainCloud|Callback Handling")
        void RegisterCallbacks(
			UBrainCloudWrapper *brainCloudWrapper,
            bool fileCallbacks = true, 
            bool rewardCallback = true, 
            bool eventCallback = true, 
            bool globalErrorCallback = true, 
            bool networkErrorCallback = true);

    //Response delegates
    UPROPERTY(BlueprintAssignable)
        FBCFileCallbackCompletedDelegate FileUploadComplete;

    UPROPERTY(BlueprintAssignable)
        FBCFileCallbackFailedDelegate FileUploadFailed;

    UPROPERTY(BlueprintAssignable)
        FBCEventDelegate EventCallback;
    
    UPROPERTY(BlueprintAssignable)
        FBCRewardDelegate RewardCallback;

    UPROPERTY(BlueprintAssignable)
        FBCGlobalErrorDelegate GlobalErrorCallback;

    UPROPERTY(BlueprintAssignable)
        FBCNetworkErrorDelegate NetworkErrorCallback;

protected:
    virtual void fileUploadCompleted(const FString& fileUploadId, const FString& jsonResponse);
    virtual void fileUploadFailed(const FString& fileUploadId, int32 statusCode, int32 reasonCode, const FString& jsonResponse);

    virtual void rewardCallback(const FString& jsonData);
    virtual void eventCallback(const FString& jsonData);

    virtual void globalError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);

    virtual void networkError();

	UBrainCloudWrapper * _brainCloudWrapper;
};
