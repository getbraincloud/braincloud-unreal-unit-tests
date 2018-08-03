// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "BrainCloudActor.h"
#include "ServerCall.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"
#include "BCClientProxy.h"

UBCClientProxy::UBCClientProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UBCClientProxy::SoftErrorHandlingMode(const bool isEnabled)
{
	BrainCloudClient::EnableSoftErrorMode = isEnabled;
}

void UBCClientProxy::SingletonMode(const bool isEnabled) 
{
	BrainCloudClient::EnableSingletonMode = isEnabled;
}

void UBCClientProxy::Initialize(ABrainCloudActor *brainCloud, 
	const FString& serverUrl,
	const FString& secretKey,
	const FString& appId,
	const FString& version)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->initialize(serverUrl, secretKey, appId, version);
}

void UBCClientProxy::InitializeIdentity(ABrainCloudActor *brainCloud, const FString& profileId, const FString& anonymousId)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->initializeIdentity(profileId, anonymousId);
}

void UBCClientProxy::RunCallbacks(ABrainCloudActor *brainCloud)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->runCallbacks();
}

void UBCClientProxy::EnableLogging(ABrainCloudActor *brainCloud, bool shouldEnable)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->enableLogging(shouldEnable);
}

bool UBCClientProxy::IsAuthenticated(ABrainCloudActor *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->isAuthenticated();
}

bool UBCClientProxy::IsInitialized(ABrainCloudActor *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->isInitialized();
}

void UBCClientProxy::ResetCommunication(ABrainCloudActor *brainCloud)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->resetCommunication();
}

void UBCClientProxy::Heartbeat(ABrainCloudActor *brainCloud)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->heartbeat();
}

//Setters
void UBCClientProxy::SetHeartbeatInterval(ABrainCloudActor *brainCloud, int32 intervalInMilliseconds)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->setHeartbeatInterval(intervalInMilliseconds);
}

void UBCClientProxy::SetPacketTimeouts(ABrainCloudActor *brainCloud, const TArray<int32> & timeouts)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->setPacketTimeouts(timeouts);
}

void UBCClientProxy::SetPacketTimeoutsToDefault(ABrainCloudActor *brainCloud)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->setPacketTimeoutsToDefault();
}

void UBCClientProxy::SetAuthenticationPacketTimeout(ABrainCloudActor *brainCloud, int32 timeoutSecs)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->setAuthenticationPacketTimeout(timeoutSecs);
}

void UBCClientProxy::SetOldStyleStatusMessageErrorCallback(ABrainCloudActor *brainCloud, bool enabled)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->setOldStyleStatusMessageErrorCallback(enabled);
}

void UBCClientProxy::SetErrorCallbackOn202Status(ABrainCloudActor *brainCloud, bool isError)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->setErrorCallbackOn202Status(isError);
}

void UBCClientProxy::SetUploadLowTransferRateTimeout(ABrainCloudActor *brainCloud, int32 timeoutSecs)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->setUploadLowTransferRateTimeout(timeoutSecs);
}

void UBCClientProxy::SetUploadLowTransferRateThreshold(ABrainCloudActor *brainCloud, int32 bytesPerSec)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->setUploadLowTransferRateThreshold(bytesPerSec);
}

//Getters
const FString & UBCClientProxy::GetGameId(ABrainCloudActor *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->getAppId();
}

const FString & UBCClientProxy::GetReleasePlatform(ABrainCloudActor *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->getReleasePlatform();
}

const FString & UBCClientProxy::GetGameVersion(ABrainCloudActor *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->getAppVersion();
}

const FString & UBCClientProxy::GetBrainCloudClientVersion(ABrainCloudActor *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->getBrainCloudClientVersion();
}

const TArray<int32> & UBCClientProxy::GetPacketTimeouts(ABrainCloudActor *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->getPacketTimeouts();
}

int32 UBCClientProxy::GetAuthenticationPacketTimeout(ABrainCloudActor *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->getAuthenticationPacketTimeout();
}

int32 UBCClientProxy::GetUploadLowTransferRateTimeout(ABrainCloudActor *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->getUploadLowTransferRateTimeout();
}

int32 UBCClientProxy::GetUploadLowTransferRateThreshold(ABrainCloudActor *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->getUploadLowTransferRateThreshold();
}

void UBCClientProxy::EnableNetworkErrorMessageCaching(ABrainCloudActor *brainCloud, bool enabled)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->enableNetworkErrorMessageCaching(enabled);
}

void UBCClientProxy::RetryCachedMessages(ABrainCloudActor *brainCloud)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->retryCachedMessages();
}

void UBCClientProxy::FlushCachedMessages(ABrainCloudActor *brainCloud, bool sendApiErrorCallbacks)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->flushCachedMessages(sendApiErrorCallbacks);
}

void UBCClientProxy::InsertEndOfMessageBundleMarker(ABrainCloudActor *brainCloud)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->insertEndOfMessageBundleMarker();
}

void UBCClientProxy::OverrideCountryCode(ABrainCloudActor *brainCloud, const FString& countryCode)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->overrideCountryCode(countryCode);
}

void UBCClientProxy::OverrideLanguageCode(ABrainCloudActor *brainCloud, const FString& languageCode)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->overrideLanguageCode(languageCode);
}
