// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BrainCloudActor.h"
#include "BCWrapperProxy.h"
#include "BCChatProxy.h"
#include "BrainCloudWrapper.h"

UBCChatProxy::UBCChatProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCChatProxy* UBCChatProxy::ChannelConnect(ABrainCloudActor *brainCloud, const FString &in_channelId, int32 in_maxToReturn)
{
	UBCChatProxy* Proxy = NewObject<UBCChatProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getChatService()->channelConnect(in_channelId, in_maxToReturn, Proxy);
	return Proxy;
}

UBCChatProxy* UBCChatProxy::ChannelDisconnect(ABrainCloudActor *brainCloud, const FString &in_channelId)
{
	UBCChatProxy* Proxy = NewObject<UBCChatProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getChatService()->channelDisconnect(in_channelId, Proxy);
	return Proxy;
}

UBCChatProxy* UBCChatProxy::DeleteChatMessage(ABrainCloudActor *brainCloud, const FString &in_channelId, const FString &in_messageId, int32 in_version)
{
	UBCChatProxy* Proxy = NewObject<UBCChatProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getChatService()->deleteChatMessage(in_channelId, in_messageId, in_version, Proxy);
	return Proxy;
}

UBCChatProxy* UBCChatProxy::GetChannelId(ABrainCloudActor *brainCloud, const FString &in_channelType, const FString &in_channelSubId)
{
	UBCChatProxy* Proxy = NewObject<UBCChatProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getChatService()->getChannelId(in_channelType, in_channelSubId, Proxy);
	return Proxy;
}

UBCChatProxy* UBCChatProxy::GetChannelInfo(ABrainCloudActor *brainCloud, const FString &in_channelId)
{
	UBCChatProxy* Proxy = NewObject<UBCChatProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getChatService()->getChannelInfo(in_channelId, Proxy);
	return Proxy;
}

UBCChatProxy* UBCChatProxy::GetChatMessage(ABrainCloudActor *brainCloud, const FString &in_channelId, const FString &in_messageId)
{
	UBCChatProxy* Proxy = NewObject<UBCChatProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getChatService()->getChatMessage(in_channelId, in_messageId, Proxy);
	return Proxy;
}

UBCChatProxy* UBCChatProxy::GetRecentChatMessages(ABrainCloudActor *brainCloud, const FString &in_channelId, int32 in_maxToReturn)
{
	UBCChatProxy* Proxy = NewObject<UBCChatProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getChatService()->getRecentChatMessages(in_channelId, in_maxToReturn, Proxy);
	return Proxy;
}

UBCChatProxy* UBCChatProxy::GetSubscribedChannels(ABrainCloudActor *brainCloud, const FString &in_channelType)
{
	UBCChatProxy* Proxy = NewObject<UBCChatProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getChatService()->getSubscribedChannels(in_channelType, Proxy);
	return Proxy;
}

UBCChatProxy* UBCChatProxy::PostChatMessage(ABrainCloudActor *brainCloud, const FString &in_channelId, const FString &in_plain, const FString &in_jsonRich, bool in_recordInHistory)
{
	UBCChatProxy* Proxy = NewObject<UBCChatProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getChatService()->postChatMessage(in_channelId, in_plain, in_jsonRich, in_recordInHistory, Proxy);
	return Proxy;
}

UBCChatProxy* UBCChatProxy::PostChatMessageSimple(ABrainCloudActor *brainCloud, const FString &in_channelId, const FString &in_plain, bool in_recordInHistory)
{
	UBCChatProxy* Proxy = NewObject<UBCChatProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getChatService()->postChatMessageSimple(in_channelId, in_plain, in_recordInHistory, Proxy);
	return Proxy;
}

UBCChatProxy* UBCChatProxy::UpdateChatMessage(ABrainCloudActor *brainCloud, const FString &in_channelId, const FString &in_messageId, int32 in_version,
										   const FString &in_plain, const FString &in_jsonRich)
{
	UBCChatProxy* Proxy = NewObject<UBCChatProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getChatService()->updateChatMessage(in_channelId, in_messageId, in_version, in_plain, in_jsonRich, Proxy);
	return Proxy;
}

//callbacks
void UBCChatProxy::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), 200, 0);
	OnSuccess.Broadcast(jsonData, returnData);
	ConditionalBeginDestroy();
}

void UBCChatProxy::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError)
{
	FBC_ReturnData returnData = FBC_ReturnData(serviceName.getValue(), serviceOperation.getValue(), statusCode, reasonCode);
	OnFailure.Broadcast(jsonError, returnData);
	ConditionalBeginDestroy();
}

