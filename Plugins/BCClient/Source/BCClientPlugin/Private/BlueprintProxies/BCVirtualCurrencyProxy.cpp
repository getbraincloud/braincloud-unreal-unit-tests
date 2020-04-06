// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCVirtualCurrencyProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCVirtualCurrencyProxy::UBCVirtualCurrencyProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCVirtualCurrencyProxy *UBCVirtualCurrencyProxy::GetCurrency(UBrainCloudWrapper *brainCloudWrapper, const FString &vcId)
{
    UBCVirtualCurrencyProxy *Proxy = NewObject<UBCVirtualCurrencyProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getVirtualCurrencyService()->getCurrency(vcId, Proxy);
    return Proxy;
}

UBCVirtualCurrencyProxy *UBCVirtualCurrencyProxy::GetParentCurrency(UBrainCloudWrapper *brainCloudWrapper, const FString &vcId, const FString &levelName)
{
    UBCVirtualCurrencyProxy *Proxy = NewObject<UBCVirtualCurrencyProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getVirtualCurrencyService()->getParentCurrency(vcId, levelName, Proxy);
    return Proxy;
}

UBCVirtualCurrencyProxy *UBCVirtualCurrencyProxy::GetPeerCurrency(UBrainCloudWrapper *brainCloudWrapper, const FString &vcId, const FString &peerCode)
{
    UBCVirtualCurrencyProxy *Proxy = NewObject<UBCVirtualCurrencyProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getVirtualCurrencyService()->getPeerCurrency(vcId, peerCode, Proxy);
    return Proxy;
}

UBCVirtualCurrencyProxy *UBCVirtualCurrencyProxy::ResetCurrency(UBrainCloudWrapper *brainCloudWrapper)
{
    UBCVirtualCurrencyProxy *Proxy = NewObject<UBCVirtualCurrencyProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getVirtualCurrencyService()->resetCurrency(Proxy);
    return Proxy;
}

UBCVirtualCurrencyProxy *UBCVirtualCurrencyProxy::AwardCurrency(UBrainCloudWrapper *brainCloudWrapper, const FString &currencyType, int32 amount)
{
    UBCVirtualCurrencyProxy *Proxy = NewObject<UBCVirtualCurrencyProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getVirtualCurrencyService()->awardCurrency(currencyType, amount, Proxy);
    return Proxy;
}

UBCVirtualCurrencyProxy *UBCVirtualCurrencyProxy::ConsumeCurrency(UBrainCloudWrapper *brainCloudWrapper, const FString &currencyType, int32 amount)
{
    UBCVirtualCurrencyProxy *Proxy = NewObject<UBCVirtualCurrencyProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getVirtualCurrencyService()->consumeCurrency(currencyType, amount, Proxy);
    return Proxy;
}
