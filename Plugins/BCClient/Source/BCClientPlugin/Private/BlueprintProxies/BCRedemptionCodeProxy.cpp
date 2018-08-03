// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloudActor.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCRedemptionCodeProxy.h"

UBCRedemptionCodeProxy::UBCRedemptionCodeProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCRedemptionCodeProxy* UBCRedemptionCodeProxy::RedeemCode(ABrainCloudActor *brainCloud, const FString& scanCode, const FString& codeType, const FString& customRedemptionInfo)
{
    UBCRedemptionCodeProxy* Proxy = NewObject<UBCRedemptionCodeProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getRedemptionCodeService()->redeemCode(scanCode, codeType, customRedemptionInfo, Proxy);
    return Proxy;
}

UBCRedemptionCodeProxy* UBCRedemptionCodeProxy::GetRedeemedCodes(ABrainCloudActor *brainCloud, const FString& codeType)
{
    UBCRedemptionCodeProxy* Proxy = NewObject<UBCRedemptionCodeProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getRedemptionCodeService()->getRedeemedCodes(codeType, Proxy);
    return Proxy;
}

//callbacks
void UBCRedemptionCodeProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCRedemptionCodeProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

