// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloud.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCProfanityProxy.h"

UBCProfanityProxy::UBCProfanityProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCProfanityProxy* UBCProfanityProxy::ProfanityCheck(ABrainCloud *brainCloud, const FString& text, const FString& languages, bool flagEmail, bool flagPhone, bool flagUrls)
{
    UBCProfanityProxy* Proxy = NewObject<UBCProfanityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getProfanityService()->profanityCheck(text, languages, flagEmail, flagPhone, flagUrls, Proxy);
    return Proxy;
}

UBCProfanityProxy* UBCProfanityProxy::ProfanityReplaceText(ABrainCloud *brainCloud, const FString& text, const FString& replaceSymbol, const FString& languages, bool flagEmail, bool flagPhone, bool flagUrls)
{
    UBCProfanityProxy* Proxy = NewObject<UBCProfanityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getProfanityService()->profanityReplaceText(text, replaceSymbol, languages, flagEmail, flagPhone, flagUrls, Proxy);
    return Proxy;
}

UBCProfanityProxy* UBCProfanityProxy::ProfanityIdentifyBadWords(ABrainCloud *brainCloud, const FString& text, const FString& languages, bool flagEmail, bool flagPhone, bool flagUrls)
{
    UBCProfanityProxy* Proxy = NewObject<UBCProfanityProxy>();
    UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getProfanityService()->profanityIdentifyBadWords(text, languages, flagEmail, flagPhone, flagUrls, Proxy);
    return Proxy;
}

//callbacks
void UBCProfanityProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
    OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCProfanityProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
    FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
    OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

