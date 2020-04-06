// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCProfanityProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCProfanityProxy::UBCProfanityProxy(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCProfanityProxy *UBCProfanityProxy::ProfanityCheck(UBrainCloudWrapper *brainCloudWrapper, const FString &text, const FString &languages, bool flagEmail, bool flagPhone, bool flagUrls)
{
    UBCProfanityProxy *Proxy = NewObject<UBCProfanityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getProfanityService()->profanityCheck(text, languages, flagEmail, flagPhone, flagUrls, Proxy);
    return Proxy;
}

UBCProfanityProxy *UBCProfanityProxy::ProfanityReplaceText(UBrainCloudWrapper *brainCloudWrapper, const FString &text, const FString &replaceSymbol, const FString &languages, bool flagEmail, bool flagPhone, bool flagUrls)
{
    UBCProfanityProxy *Proxy = NewObject<UBCProfanityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getProfanityService()->profanityReplaceText(text, replaceSymbol, languages, flagEmail, flagPhone, flagUrls, Proxy);
    return Proxy;
}

UBCProfanityProxy *UBCProfanityProxy::ProfanityIdentifyBadWords(UBrainCloudWrapper *brainCloudWrapper, const FString &text, const FString &languages, bool flagEmail, bool flagPhone, bool flagUrls)
{
    UBCProfanityProxy *Proxy = NewObject<UBCProfanityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getProfanityService()->profanityIdentifyBadWords(text, languages, flagEmail, flagPhone, flagUrls, Proxy);
    return Proxy;
}
