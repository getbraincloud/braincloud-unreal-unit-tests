// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCRedemptionCodeProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCRedemptionCodeProxy::UBCRedemptionCodeProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCRedemptionCodeProxy *UBCRedemptionCodeProxy::RedeemCode(UBrainCloudWrapper *brainCloudWrapper, const FString &scanCode, const FString &codeType, const FString &customRedemptionInfo)
{
    UBCRedemptionCodeProxy *Proxy = NewObject<UBCRedemptionCodeProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRedemptionCodeService()->redeemCode(scanCode, codeType, customRedemptionInfo, Proxy);
    return Proxy;
}

UBCRedemptionCodeProxy *UBCRedemptionCodeProxy::GetRedeemedCodes(UBrainCloudWrapper *brainCloudWrapper, const FString &codeType)
{
    UBCRedemptionCodeProxy *Proxy = NewObject<UBCRedemptionCodeProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getRedemptionCodeService()->getRedeemedCodes(codeType, Proxy);
    return Proxy;
}
