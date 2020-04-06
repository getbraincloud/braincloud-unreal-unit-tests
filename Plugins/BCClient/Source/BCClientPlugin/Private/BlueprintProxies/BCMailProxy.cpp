// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCMailProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCMailProxy::UBCMailProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCMailProxy *UBCMailProxy::SendBasicEmail(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId, const FString &subject, const FString &body)
{
	UBCMailProxy *Proxy = NewObject<UBCMailProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMailService()->sendBasicEmail(profileId, subject, body, Proxy);
	return Proxy;
}

UBCMailProxy *UBCMailProxy::SendAdvancedEmail(UBrainCloudWrapper *brainCloudWrapper, const FString &profileId, const FString &jsonServiceParams)
{
	UBCMailProxy *Proxy = NewObject<UBCMailProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMailService()->sendAdvancedEmail(profileId, jsonServiceParams, Proxy);
	return Proxy;
}

UBCMailProxy *UBCMailProxy::SendAdvancedEmailByAddress(UBrainCloudWrapper *brainCloudWrapper, const FString &emailAddress, const FString &jsonServiceParams)
{
	UBCMailProxy *Proxy = NewObject<UBCMailProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMailService()->sendAdvancedEmailByAddress(emailAddress, jsonServiceParams, Proxy);
	return Proxy;
}
