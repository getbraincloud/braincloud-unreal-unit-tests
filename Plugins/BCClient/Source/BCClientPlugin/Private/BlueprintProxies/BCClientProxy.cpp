// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCClientProxy.h"

UBCClientProxy::UBCClientProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UBCClientProxy::Initialize(const FString& serverUrl,
	const FString& secretKey,
	const FString& appId,
	const FString& version)
{
	BrainCloudClient::getInstance()->initialize(serverUrl, secretKey, appId, version);
}

void UBCClientProxy::InitializeIdentity(const FString& profileId, const FString& anonymousId)
{
	BrainCloudClient::getInstance()->initializeIdentity(profileId, anonymousId);
}

void UBCClientProxy::RunCallbacks()
{
	BrainCloudClient::getInstance()->runCallbacks();
}

void UBCClientProxy::RestoreRecentSession(const FString& sessionId)
{
	BrainCloudClient::getInstance()->restoreRecentSession(sessionId);
}

void UBCClientProxy::EnableLogging(bool shouldEnable)
{
	BrainCloudClient::getInstance()->enableLogging(shouldEnable);
}

bool UBCClientProxy::IsAuthenticated()
{
	return BrainCloudClient::getInstance()->isAuthenticated();
}

bool UBCClientProxy::IsInitialized()
{
	return BrainCloudClient::getInstance()->isInitialized();
}

void UBCClientProxy::ResetCommunication()
{
	BrainCloudClient::getInstance()->resetCommunication();
}

void UBCClientProxy::Heartbeat()
{
	BrainCloudClient::getInstance()->heartbeat();
}

//Setters
void UBCClientProxy::SetHeartbeatInterval(int32 intervalInMilliseconds)
{
	BrainCloudClient::getInstance()->setHeartbeatInterval(intervalInMilliseconds);
}

void UBCClientProxy::SetPacketTimeouts(const TArray<int32> & timeouts)
{
	BrainCloudClient::getInstance()->setPacketTimeouts(timeouts);
}

void UBCClientProxy::SetPacketTimeoutsToDefault()
{
	BrainCloudClient::getInstance()->setPacketTimeoutsToDefault();
}

void UBCClientProxy::SetAuthenticationPacketTimeout(int32 timeoutSecs)
{
	BrainCloudClient::getInstance()->setAuthenticationPacketTimeout(timeoutSecs);
}

void UBCClientProxy::SetOldStyleStatusMessageErrorCallback(bool enabled)
{
	BrainCloudClient::getInstance()->setOldStyleStatusMessageErrorCallback(enabled);
}

void UBCClientProxy::SetErrorCallbackOn202Status(bool isError)
{
	BrainCloudClient::getInstance()->setErrorCallbackOn202Status(isError);
}

void UBCClientProxy::SetUploadLowTransferRateTimeout(int32 timeoutSecs)
{
	BrainCloudClient::getInstance()->setUploadLowTransferRateTimeout(timeoutSecs);
}

void UBCClientProxy::SetUploadLowTransferRateThreshold(int32 bytesPerSec)
{
	BrainCloudClient::getInstance()->setUploadLowTransferRateThreshold(bytesPerSec);
}

//Getters
const FString & UBCClientProxy::GetGameId()
{
	return BrainCloudClient::getInstance()->getAppId();
}

const FString & UBCClientProxy::GetReleasePlatform()
{
	return BrainCloudClient::getInstance()->getReleasePlatform();
}

const FString & UBCClientProxy::GetGameVersion()
{
	return BrainCloudClient::getInstance()->getAppVersion();
}

const FString & UBCClientProxy::GetBrainCloudClientVersion()
{
	return BrainCloudClient::getInstance()->getBrainCloudClientVersion();
}

const TArray<int32> & UBCClientProxy::GetPacketTimeouts()
{
	return BrainCloudClient::getInstance()->getPacketTimeouts();
}

int32 UBCClientProxy::GetAuthenticationPacketTimeout()
{
	return BrainCloudClient::getInstance()->getAuthenticationPacketTimeout();
}

int32 UBCClientProxy::GetUploadLowTransferRateTimeout()
{
	return BrainCloudClient::getInstance()->getUploadLowTransferRateTimeout();
}

int32 UBCClientProxy::GetUploadLowTransferRateThreshold()
{
	return BrainCloudClient::getInstance()->getUploadLowTransferRateThreshold();
}

void UBCClientProxy::EnableNetworkErrorMessageCaching(bool enabled)
{
	BrainCloudClient::getInstance()->enableNetworkErrorMessageCaching(enabled);
}

void UBCClientProxy::RetryCachedMessages()
{
	BrainCloudClient::getInstance()->retryCachedMessages();
}

void UBCClientProxy::FlushCachedMessages(bool sendApiErrorCallbacks)
{
	BrainCloudClient::getInstance()->flushCachedMessages(sendApiErrorCallbacks);
}

void UBCClientProxy::InsertEndOfMessageBundleMarker()
{
	BrainCloudClient::getInstance()->insertEndOfMessageBundleMarker();
}

void UBCClientProxy::OverrideCountryCode(const FString& countryCode)
{
	BrainCloudClient::getInstance()->overrideCountryCode(countryCode);
}

void UBCClientProxy::OverrideLanguageCode(const FString& languageCode)
{
	BrainCloudClient::getInstance()->overrideLanguageCode(languageCode);
}
