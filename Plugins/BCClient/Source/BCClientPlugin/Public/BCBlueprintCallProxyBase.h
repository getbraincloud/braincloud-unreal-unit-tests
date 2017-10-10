// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.generated.h"

UCLASS(MinimalAPI)
class UBCBlueprintCallProxyBase : public UObject
{
    GENERATED_BODY()

public:

	UBCBlueprintCallProxyBase(const FObjectInitializer& ObjectInitializer)
	{
		this->AddToRoot();
	}
};

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
    FBC_ReturnData(){}

    FBC_ReturnData(FString serviceName, FString serviceOperation, int32 statusCode, int32 reasonCode)
    : ServiceName(serviceName), ServiceOperation(serviceOperation), StatusCode(statusCode), ReasonCode(reasonCode)
    {
    }
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBrainCloudCallbackDelegate, FString, JsonData, FBC_ReturnData, AdditionalData);