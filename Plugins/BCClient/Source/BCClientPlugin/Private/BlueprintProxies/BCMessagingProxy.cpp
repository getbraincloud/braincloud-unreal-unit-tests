// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BCMessagingProxy.h"
#include "BrainCloudWrapper.h"

UBCMessagingProxy::UBCMessagingProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCMessagingProxy *UBCMessagingProxy::DeleteMessages(UBrainCloudWrapper *brainCloud, const FString &in_msgBox, const TArray<FString> &in_msgsIds)
{
	UBCMessagingProxy *Proxy = NewObject<UBCMessagingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMessagingService()->deleteMessages(in_msgBox, in_msgsIds, Proxy);
	return Proxy;
}

UBCMessagingProxy *UBCMessagingProxy::GetMessageBoxes(UBrainCloudWrapper *brainCloud)
{
	UBCMessagingProxy *Proxy = NewObject<UBCMessagingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMessagingService()->getMessageBoxes(Proxy);
	return Proxy;
}

UBCMessagingProxy *UBCMessagingProxy::GetMessageCounts(UBrainCloudWrapper *brainCloud)
{
	UBCMessagingProxy *Proxy = NewObject<UBCMessagingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMessagingService()->getMessageCounts(Proxy);
	return Proxy;
}

UBCMessagingProxy *UBCMessagingProxy::GetMessages(UBrainCloudWrapper *brainCloud, const FString &in_msgBox, const TArray<FString> &in_msgsIds, bool in_markAsRead)
{
	UBCMessagingProxy *Proxy = NewObject<UBCMessagingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMessagingService()->getMessages(in_msgBox, in_msgsIds, in_markAsRead, Proxy);
	return Proxy;
}

UBCMessagingProxy *UBCMessagingProxy::GetMessagesPage(UBrainCloudWrapper *brainCloud, const FString &in_context)
{
	UBCMessagingProxy *Proxy = NewObject<UBCMessagingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMessagingService()->getMessagesPage(in_context, Proxy);
	return Proxy;
}

UBCMessagingProxy *UBCMessagingProxy::GetMessagesPageOffset(UBrainCloudWrapper *brainCloud, const FString &in_context, int32 in_pageOffset)
{
	UBCMessagingProxy *Proxy = NewObject<UBCMessagingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMessagingService()->getMessagesPageOffset(in_context, in_pageOffset, Proxy);
	return Proxy;
}

UBCMessagingProxy *UBCMessagingProxy::MarkMessagesRead(UBrainCloudWrapper *brainCloud, const FString &in_msgBox, const TArray<FString> &in_msgsIds)
{
	UBCMessagingProxy *Proxy = NewObject<UBCMessagingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMessagingService()->markMessagesRead(in_msgBox, in_msgsIds, Proxy);
	return Proxy;
}

UBCMessagingProxy *UBCMessagingProxy::SendMessage(UBrainCloudWrapper *brainCloud, const TArray<FString> &in_toProfileIds, const FString &in_contentJson)
{
	UBCMessagingProxy *Proxy = NewObject<UBCMessagingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMessagingService()->sendMessage(in_toProfileIds, in_contentJson, Proxy);
	return Proxy;
}

UBCMessagingProxy *UBCMessagingProxy::SendMessageSimple(UBrainCloudWrapper *brainCloud, const TArray<FString> &in_toProfileIds, const FString &in_messageText)
{
	UBCMessagingProxy *Proxy = NewObject<UBCMessagingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloud)->getMessagingService()->sendMessageSimple(in_toProfileIds, in_messageText, Proxy);
	return Proxy;
}
