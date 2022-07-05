// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCMessagingProxy.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"
#include "ServerCall.h"

#include "BCWrapperProxy.h"
#include "BrainCloudWrapper.h"

UBCMessagingProxy::UBCMessagingProxy(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UBCMessagingProxy *UBCMessagingProxy::DeleteMessages(UBrainCloudWrapper *brainCloudWrapper, const FString &in_msgBox, const TArray<FString> &in_msgsIds)
{
	UBCMessagingProxy *Proxy = NewObject<UBCMessagingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMessagingService()->deleteMessages(in_msgBox, in_msgsIds, Proxy);
	return Proxy;
}

UBCMessagingProxy *UBCMessagingProxy::GetMessageBoxes(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCMessagingProxy *Proxy = NewObject<UBCMessagingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMessagingService()->getMessageBoxes(Proxy);
	return Proxy;
}

UBCMessagingProxy *UBCMessagingProxy::GetMessageCounts(UBrainCloudWrapper *brainCloudWrapper)
{
	UBCMessagingProxy *Proxy = NewObject<UBCMessagingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMessagingService()->getMessageCounts(Proxy);
	return Proxy;
}

UBCMessagingProxy *UBCMessagingProxy::GetMessages(UBrainCloudWrapper *brainCloudWrapper, const FString &in_msgBox, const TArray<FString> &in_msgsIds, bool in_markAsRead)
{
	UBCMessagingProxy *Proxy = NewObject<UBCMessagingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMessagingService()->getMessages(in_msgBox, in_msgsIds, in_markAsRead, Proxy);
	return Proxy;
}

UBCMessagingProxy *UBCMessagingProxy::GetMessagesPage(UBrainCloudWrapper *brainCloudWrapper, const FString &in_context)
{
	UBCMessagingProxy *Proxy = NewObject<UBCMessagingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMessagingService()->getMessagesPage(in_context, Proxy);
	return Proxy;
}

UBCMessagingProxy *UBCMessagingProxy::GetMessagesPageOffset(UBrainCloudWrapper *brainCloudWrapper, const FString &in_context, int32 in_pageOffset)
{
	UBCMessagingProxy *Proxy = NewObject<UBCMessagingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMessagingService()->getMessagesPageOffset(in_context, in_pageOffset, Proxy);
	return Proxy;
}

UBCMessagingProxy *UBCMessagingProxy::MarkMessagesRead(UBrainCloudWrapper *brainCloudWrapper, const FString &in_msgBox, const TArray<FString> &in_msgsIds)
{
	UBCMessagingProxy *Proxy = NewObject<UBCMessagingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMessagingService()->markMessagesRead(in_msgBox, in_msgsIds, Proxy);
	return Proxy;
}

UBCMessagingProxy *UBCMessagingProxy::SendMessage(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &in_toProfileIds, const FString &in_contentJson)
{
	UBCMessagingProxy *Proxy = NewObject<UBCMessagingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMessagingService()->sendMessage(in_toProfileIds, in_contentJson, Proxy);
	return Proxy;
}

UBCMessagingProxy *UBCMessagingProxy::SendMessageSimple(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &in_toProfileIds, const FString &in_messageText)
{
	UBCMessagingProxy *Proxy = NewObject<UBCMessagingProxy>();
	UBCWrapperProxy::GetBrainCloudInstance(brainCloudWrapper)->getMessagingService()->sendMessageSimple(in_toProfileIds, in_messageText, Proxy);
	return Proxy;
}
