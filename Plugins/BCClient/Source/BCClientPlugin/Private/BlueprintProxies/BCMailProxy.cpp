// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloud.h"
#include "BCWrapperProxy.h"
#include "BCMailProxy.h"
#include "BrainCloudWrapper.h"

UBCMailProxy::UBCMailProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCMailProxy* UBCMailProxy::SendBasicEmail(ABrainCloud *brainCloud, const FString& profileId, const FString& subject, const FString& body)
{
	UBCMailProxy* Proxy = NewObject<UBCMailProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMailService()->sendBasicEmail(profileId, subject, body, Proxy);
	return Proxy;
}

UBCMailProxy* UBCMailProxy::SendAdvancedEmail(ABrainCloud *brainCloud, const FString& profileId, const FString& jsonServiceParams)
{
	UBCMailProxy* Proxy = NewObject<UBCMailProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMailService()->sendAdvancedEmail(profileId, jsonServiceParams, Proxy);
	return Proxy;
}

UBCMailProxy* UBCMailProxy::SendAdvancedEmailByAddress(ABrainCloud *brainCloud, const FString& emailAddress, const FString& jsonServiceParams)
{
	UBCMailProxy* Proxy = NewObject<UBCMailProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMailService()->sendAdvancedEmailByAddress(emailAddress, jsonServiceParams, Proxy);
	return Proxy;
}

//callbacks
void UBCMailProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
	OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCMailProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
	OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

