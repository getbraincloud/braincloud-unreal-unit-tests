// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "BrainCloud.h"
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

void UBCClientProxy::Initialize(ABrainCloud *brainCloud, 
	const FString& serverUrl,
	const FString& secretKey,
	const FString& appId,
	const FString& version)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->initialize(serverUrl, secretKey, appId, version);
}

void UBCClientProxy::InitializeIdentity(ABrainCloud *brainCloud, const FString& profileId, const FString& anonymousId)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->initializeIdentity(profileId, anonymousId);
}

void UBCClientProxy::RunCallbacks(ABrainCloud *brainCloud)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->runCallbacks();
}

void UBCClientProxy::RestoreRecentSession(const FString& sessionId)
{
	// Remove this function
}

void UBCClientProxy::EnableLogging(ABrainCloud *brainCloud, bool shouldEnable)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->enableLogging(shouldEnable);
}

bool UBCClientProxy::IsAuthenticated(ABrainCloud *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->isAuthenticated();
}

bool UBCClientProxy::IsInitialized(ABrainCloud *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->isInitialized();
}

void UBCClientProxy::ResetCommunication(ABrainCloud *brainCloud)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->resetCommunication();
}

void UBCClientProxy::Heartbeat(ABrainCloud *brainCloud)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->heartbeat();
}

//Setters
void UBCClientProxy::SetHeartbeatInterval(ABrainCloud *brainCloud, int32 intervalInMilliseconds)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->setHeartbeatInterval(intervalInMilliseconds);
}

void UBCClientProxy::SetPacketTimeouts(ABrainCloud *brainCloud, const TArray<int32> & timeouts)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->setPacketTimeouts(timeouts);
}

void UBCClientProxy::SetPacketTimeoutsToDefault(ABrainCloud *brainCloud)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->setPacketTimeoutsToDefault();
}

void UBCClientProxy::SetAuthenticationPacketTimeout(ABrainCloud *brainCloud, int32 timeoutSecs)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->setAuthenticationPacketTimeout(timeoutSecs);
}

void UBCClientProxy::SetOldStyleStatusMessageErrorCallback(ABrainCloud *brainCloud, bool enabled)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->setOldStyleStatusMessageErrorCallback(enabled);
}

void UBCClientProxy::SetErrorCallbackOn202Status(ABrainCloud *brainCloud, bool isError)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->setErrorCallbackOn202Status(isError);
}

void UBCClientProxy::SetUploadLowTransferRateTimeout(ABrainCloud *brainCloud, int32 timeoutSecs)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->setUploadLowTransferRateTimeout(timeoutSecs);
}

void UBCClientProxy::SetUploadLowTransferRateThreshold(ABrainCloud *brainCloud, int32 bytesPerSec)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->setUploadLowTransferRateThreshold(bytesPerSec);
}

//Getters
const FString & UBCClientProxy::GetGameId(ABrainCloud *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->getAppId();
}

const FString & UBCClientProxy::GetReleasePlatform(ABrainCloud *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->getReleasePlatform();
}

const FString & UBCClientProxy::GetGameVersion(ABrainCloud *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->getAppVersion();
}

const FString & UBCClientProxy::GetBrainCloudClientVersion(ABrainCloud *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->getBrainCloudClientVersion();
}

const TArray<int32> & UBCClientProxy::GetPacketTimeouts(ABrainCloud *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->getPacketTimeouts();
}

int32 UBCClientProxy::GetAuthenticationPacketTimeout(ABrainCloud *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->getAuthenticationPacketTimeout();
}

int32 UBCClientProxy::GetUploadLowTransferRateTimeout(ABrainCloud *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->getUploadLowTransferRateTimeout();
}

int32 UBCClientProxy::GetUploadLowTransferRateThreshold(ABrainCloud *brainCloud)
{
	return UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->getUploadLowTransferRateThreshold();
}

void UBCClientProxy::EnableNetworkErrorMessageCaching(ABrainCloud *brainCloud, bool enabled)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->enableNetworkErrorMessageCaching(enabled);
}

void UBCClientProxy::RetryCachedMessages(ABrainCloud *brainCloud)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->retryCachedMessages();
}

void UBCClientProxy::FlushCachedMessages(ABrainCloud *brainCloud, bool sendApiErrorCallbacks)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->flushCachedMessages(sendApiErrorCallbacks);
}

void UBCClientProxy::InsertEndOfMessageBundleMarker(ABrainCloud *brainCloud)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->insertEndOfMessageBundleMarker();
}

void UBCClientProxy::OverrideCountryCode(ABrainCloud *brainCloud, const FString& countryCode)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->overrideCountryCode(countryCode);
}

void UBCClientProxy::OverrideLanguageCode(ABrainCloud *brainCloud, const FString& languageCode)
{
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getBCClient()->overrideLanguageCode(languageCode);
}
