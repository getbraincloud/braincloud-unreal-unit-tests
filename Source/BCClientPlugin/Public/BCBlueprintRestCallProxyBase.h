// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "IEventCallback.h"
#include "IRewardCallback.h"
#include "INetworkErrorCallback.h"
#include "IGlobalErrorCallback.h"
#include "IFileUploadCallback.h"
#include "BCBlueprintCallProxyBase.h"
#include "BCBlueprintRestCallProxyBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBrainCloudRestCallbackDelegate, FString, JsonData, FBC_ReturnData, AdditionalData);

UCLASS(MinimalAPI)
class UBCBlueprintRestCallProxyBase : public UObject, public IEventCallback, public IRewardCallback, public INetworkErrorCallback, public IGlobalErrorCallback, public IFileUploadCallback
{
    GENERATED_BODY()

  public:
    UBCBlueprintRestCallProxyBase(const FObjectInitializer &ObjectInitializer) {}

    //Response delegates
    UPROPERTY(BlueprintAssignable)
    FBrainCloudRestCallbackDelegate OnCallback;

    //IEventCallback
    void eventCallback(const FString &jsonData)
    {
        FBC_ReturnData returnData = FBC_ReturnData();
        OnCallback.Broadcast(jsonData, returnData);
    }

    //IRewardCallback
    void rewardCallback(const FString &jsonData)
    {
        FBC_ReturnData returnData = FBC_ReturnData();
        OnCallback.Broadcast(jsonData, returnData);
    }

    //INetworkErrorCallback
    void networkError()
    {
        FBC_ReturnData returnData = FBC_ReturnData();
        OnCallback.Broadcast(TEXT(""), returnData);
    }

    //IGlobalErrorCallback
    void globalError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString &jsonError)
    {
        FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
        OnCallback.Broadcast(jsonError, returnData);
    }

    //IFileUploadCallback
    void fileUploadCompleted(const FString &fileUploadId, const FString &jsonResponse)
    {
        FBC_ReturnData returnData = FBC_ReturnData(fileUploadId, fileUploadId, 200, 0);
        OnCallback.Broadcast(jsonResponse, returnData);
    }

    void fileUploadFailed(const FString &fileUploadId, int32 statusCode, int32 reasonCode, const FString &jsonResponse)
    {
        FBC_ReturnData returnData = FBC_ReturnData(fileUploadId, fileUploadId, statusCode, reasonCode);
        OnCallback.Broadcast(jsonResponse, returnData);
    }
};
