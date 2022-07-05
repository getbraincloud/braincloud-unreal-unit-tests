// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCChatProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCChatProxy::UBCChatProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCChatProxy *UBCChatProxy::ChannelConnect(UBrainCloudWrapper *brainCloudWrapper, const FString &in_channelId, int32 in_maxToReturn)
{
	UBCChatProxy *Proxy = NewObject<UBCChatProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getChatService()->channelConnect(in_channelId, in_maxToReturn, Proxy);
	return Proxy;
}

UBCChatProxy *UBCChatProxy::ChannelDisconnect(UBrainCloudWrapper *brainCloudWrapper, const FString &in_channelId)
{
	UBCChatProxy *Proxy = NewObject<UBCChatProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getChatService()->channelDisconnect(in_channelId, Proxy);
	return Proxy;
}

UBCChatProxy *UBCChatProxy::DeleteChatMessage(UBrainCloudWrapper *brainCloudWrapper, const FString &in_channelId, const FString &in_messageId, int32 in_version)
{
	UBCChatProxy *Proxy = NewObject<UBCChatProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getChatService()->deleteChatMessage(in_channelId, in_messageId, in_version, Proxy);
	return Proxy;
}

UBCChatProxy *UBCChatProxy::GetChannelId(UBrainCloudWrapper *brainCloudWrapper, const FString &in_channelType, const FString &in_channelSubId)
{
	UBCChatProxy *Proxy = NewObject<UBCChatProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getChatService()->getChannelId(in_channelType, in_channelSubId, Proxy);
	return Proxy;
}

UBCChatProxy *UBCChatProxy::GetChannelInfo(UBrainCloudWrapper *brainCloudWrapper, const FString &in_channelId)
{
	UBCChatProxy *Proxy = NewObject<UBCChatProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getChatService()->getChannelInfo(in_channelId, Proxy);
	return Proxy;
}

UBCChatProxy *UBCChatProxy::GetChatMessage(UBrainCloudWrapper *brainCloudWrapper, const FString &in_channelId, const FString &in_messageId)
{
	UBCChatProxy *Proxy = NewObject<UBCChatProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getChatService()->getChatMessage(in_channelId, in_messageId, Proxy);
	return Proxy;
}

UBCChatProxy *UBCChatProxy::GetRecentChatMessages(UBrainCloudWrapper *brainCloudWrapper, const FString &in_channelId, int32 in_maxToReturn)
{
	UBCChatProxy *Proxy = NewObject<UBCChatProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getChatService()->getRecentChatMessages(in_channelId, in_maxToReturn, Proxy);
	return Proxy;
}

UBCChatProxy *UBCChatProxy::GetSubscribedChannels(UBrainCloudWrapper *brainCloudWrapper, const FString &in_channelType)
{
	UBCChatProxy *Proxy = NewObject<UBCChatProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getChatService()->getSubscribedChannels(in_channelType, Proxy);
	return Proxy;
}

UBCChatProxy *UBCChatProxy::PostChatMessage(UBrainCloudWrapper *brainCloudWrapper, const FString &in_channelId, const FString &in_plain, const FString &in_jsonRich, bool in_recordInHistory)
{
	UBCChatProxy *Proxy = NewObject<UBCChatProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getChatService()->postChatMessage(in_channelId, in_plain, in_jsonRich, in_recordInHistory, Proxy);
	return Proxy;
}

UBCChatProxy *UBCChatProxy::PostChatMessageSimple(UBrainCloudWrapper *brainCloudWrapper, const FString &in_channelId, const FString &in_plain, bool in_recordInHistory)
{
	UBCChatProxy *Proxy = NewObject<UBCChatProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getChatService()->postChatMessageSimple(in_channelId, in_plain, in_recordInHistory, Proxy);
	return Proxy;
}

UBCChatProxy *UBCChatProxy::UpdateChatMessage(UBrainCloudWrapper *brainCloudWrapper, const FString &in_channelId, const FString &in_messageId, int32 in_version,
											  const FString &in_plain, const FString &in_jsonRich)
{
	UBCChatProxy *Proxy = NewObject<UBCChatProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getChatService()->updateChatMessage(in_channelId, in_messageId, in_version, in_plain, in_jsonRich, Proxy);
	return Proxy;
}
