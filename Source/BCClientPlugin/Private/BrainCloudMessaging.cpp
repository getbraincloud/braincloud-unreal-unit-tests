// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudMessaging.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudMessaging::BrainCloudMessaging(BrainCloudClient *client) : _client(client){};

void BrainCloudMessaging::deleteMessages(const FString &in_msgBox, const TArray<FString> &in_msgsIds, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::MessagingMessageBox.getValue(), in_msgBox);
    message->SetArrayField(OperationParam::MessagingMessageIds.getValue(), JsonUtil::arrayToJsonArray(in_msgsIds));

    ServerCall *sc = new ServerCall(ServiceName::Messaging, ServiceOperation::DeleteMessages, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudMessaging::getMessageBoxes(IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    ServerCall *sc = new ServerCall(ServiceName::Messaging, ServiceOperation::GetMessageBoxes, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudMessaging::getMessageCounts(IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());

    ServerCall *sc = new ServerCall(ServiceName::Messaging, ServiceOperation::GetMessageCounts, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudMessaging::getMessages(const FString &in_msgBox, const TArray<FString> &in_msgsIds, bool in_markAsRead, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::MessagingMessageBox.getValue(), in_msgBox);
    message->SetArrayField(OperationParam::MessagingMessageIds.getValue(), JsonUtil::arrayToJsonArray(in_msgsIds));
    message->SetBoolField(OperationParam::MessagingMarkAsRead.getValue(), in_markAsRead);

    ServerCall *sc = new ServerCall(ServiceName::Messaging, ServiceOperation::GetMessages, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudMessaging::getMessagesPage(const FString &in_context, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetObjectField(OperationParam::MessagingContext.getValue(), JsonUtil::jsonStringToValue(in_context));

    ServerCall *sc = new ServerCall(ServiceName::Messaging, ServiceOperation::GetMessagesPage, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudMessaging::getMessagesPageOffset(const FString &in_context, int32 in_pageOffset, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::MessagingContext.getValue(), in_context);
    message->SetNumberField(OperationParam::MessagingPageOffset.getValue(), in_pageOffset);

    ServerCall *sc = new ServerCall(ServiceName::Messaging, ServiceOperation::GetMessagesPageOffset, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudMessaging::markMessagesRead(const FString &in_msgBox, const TArray<FString> &in_msgsIds, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::MessagingMessageBox.getValue(), in_msgBox);
    message->SetArrayField(OperationParam::MessagingMessageIds.getValue(), JsonUtil::arrayToJsonArray(in_msgsIds));

    ServerCall *sc = new ServerCall(ServiceName::Messaging, ServiceOperation::MarkMessagesRead, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudMessaging::sendMessage(const TArray<FString> &in_toProfileIds, const FString &in_contentJson, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetArrayField(OperationParam::MessagingToProfileIds.getValue(), JsonUtil::arrayToJsonArray(in_toProfileIds));
    message->SetObjectField(OperationParam::MessagingContent.getValue(), JsonUtil::jsonStringToValue(in_contentJson));

    ServerCall *sc = new ServerCall(ServiceName::Messaging, ServiceOperation::SEND_MESSAGE, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudMessaging::sendMessageSimple(const TArray<FString> &in_toProfileIds, const FString &in_messageText, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetArrayField(OperationParam::MessagingToProfileIds.getValue(), JsonUtil::arrayToJsonArray(in_toProfileIds));
    message->SetStringField(OperationParam::MessagingText.getValue(), in_messageText);

    ServerCall *sc = new ServerCall(ServiceName::Messaging, ServiceOperation::SendMessageSimple, message, in_callback);
    _client->sendRequest(sc);
}