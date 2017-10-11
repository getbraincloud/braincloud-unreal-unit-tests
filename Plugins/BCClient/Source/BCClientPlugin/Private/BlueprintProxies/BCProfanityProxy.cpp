// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCProfanityProxy.h"

UBCProfanityProxy::UBCProfanityProxy(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UBCProfanityProxy* UBCProfanityProxy::ProfanityCheck(const FString& text, const FString& languages, bool flagEmail, bool flagPhone, bool flagUrls)
{
    UBCProfanityProxy* Proxy = NewObject<UBCProfanityProxy>();
    BrainCloudClient::getInstance()->getProfanityService()->profanityCheck(text, languages, flagEmail, flagPhone, flagUrls, Proxy);
    return Proxy;
}

UBCProfanityProxy* UBCProfanityProxy::ProfanityReplaceText(const FString& text, const FString& replaceSymbol, const FString& languages, bool flagEmail, bool flagPhone, bool flagUrls)
{
    UBCProfanityProxy* Proxy = NewObject<UBCProfanityProxy>();
    BrainCloudClient::getInstance()->getProfanityService()->profanityReplaceText(text, replaceSymbol, languages, flagEmail, flagPhone, flagUrls, Proxy);
    return Proxy;
}

UBCProfanityProxy* UBCProfanityProxy::ProfanityIdentifyBadWords(const FString& text, const FString& languages, bool flagEmail, bool flagPhone, bool flagUrls)
{
    UBCProfanityProxy* Proxy = NewObject<UBCProfanityProxy>();
    BrainCloudClient::getInstance()->getProfanityService()->profanityIdentifyBadWords(text, languages, flagEmail, flagPhone, flagUrls, Proxy);
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

