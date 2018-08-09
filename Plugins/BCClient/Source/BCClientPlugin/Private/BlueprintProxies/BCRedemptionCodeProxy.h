// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BCRedemptionCodeProxy.generated.h"

class ABrainCloud;

UCLASS(MinimalAPI)
class UBCRedemptionCodeProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
    GENERATED_BODY()

public:
    UBCRedemptionCodeProxy(const FObjectInitializer& ObjectInitializer);

    /**
    * Redeem a code.
    *
    * Service Name - RedemptionCode
    * Service Operation - REDEEM_CODE
    *
    * Param - scanCode The code to redeem
    * Param - codeType The type of code
    * Param - customRedemptionInfo Optional - A JSON string containing custom redemption data
    * Param - callback The method to be invoked when the server response is received
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Redemption Code")
        static UBCRedemptionCodeProxy* RedeemCode(UBrainCloudWrapper *brainCloudWrapper, const FString& scanCode, const FString& codeType, const FString& customRedemptionInfo);

    /**
    * Retrieve the codes already redeemed by player.
    *
    * Service Name - RedemptionCode
    * Service Operation - GET_REDEEMED_CODES
    *
    * Param - in_codeType Optional - The type of codes to retrieve. Returns all codes if left unspecified.
    * Param - in_callback The method to be invoked when the server response is received
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Redemption Code")
        static UBCRedemptionCodeProxy* GetRedeemedCodes(UBrainCloudWrapper *brainCloudWrapper, const FString& codeType);

    //Response delegates
    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnFailure;

protected:
    // IServerCallback interface
    void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
    void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
    // End of IServerCallback interface
};
