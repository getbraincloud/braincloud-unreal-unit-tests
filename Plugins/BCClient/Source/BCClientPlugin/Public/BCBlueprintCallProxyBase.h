// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "IServerCallback.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "BCBlueprintCallProxyBase.generated.h"

USTRUCT(BlueprintType, Category = "BrainCloud")
struct FBC_ReturnData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString ServiceName = TEXT("");

    UPROPERTY(BlueprintReadWrite)
    FString ServiceOperation = TEXT("");

    UPROPERTY(BlueprintReadWrite)
    int32 StatusCode = 0;

    UPROPERTY(BlueprintReadWrite)
    int32 ReasonCode = 0;

    /*Constructors*/
    FBC_ReturnData() {}

    FBC_ReturnData(FString serviceName, FString serviceOperation, int32 statusCode, int32 reasonCode)
        : ServiceName(serviceName), ServiceOperation(serviceOperation), StatusCode(statusCode), ReasonCode(reasonCode)
    {
    }
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBrainCloudCallbackDelegate, FString, JsonData, FBC_ReturnData, AdditionalData);

UCLASS(MinimalAPI)
class UBCBlueprintCallProxyBase : public UObject, public IServerCallback
{
    GENERATED_BODY()

  public:
    UBCBlueprintCallProxyBase(const FObjectInitializer &ObjectInitializer)
    {
        // ensures these are not removed during scene loads! which is important!
        this->AddToRoot();
    }

    //Response delegates
    UPROPERTY(BlueprintAssignable)
    FBrainCloudCallbackDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FBrainCloudCallbackDelegate OnFailure;

    //callbacks
    void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString &jsonData)
    {
        FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
        OnSuccess.Broadcast(jsonData, returnData);
        
        cleanup();
    }

    void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString &jsonError)
    {
        FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
        OnFailure.Broadcast(jsonError, returnData);
        
        cleanup();
    }

    protected:
    bool _bCleanupAfterFirstResponse = true;

    private:
    void cleanup()
    {
        if (_bCleanupAfterFirstResponse)
        {
            // allow it to be removed, if no longer referenced
            this->RemoveFromRoot();
            this->ConditionalBeginDestroy();
        }
    }
};
