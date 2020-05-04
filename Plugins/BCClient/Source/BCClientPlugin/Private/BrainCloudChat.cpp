// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudChat.h"
#include "BCClientPluginPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServerCall.h"
#include "JsonUtil.h"

BrainCloudChat::BrainCloudChat(BrainCloudClient *client) : _client(client){};

void BrainCloudChat::channelConnect(const FString &in_channelId, int32 in_maxToReturn, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ChatChannelId.getValue(), in_channelId);
    message->SetNumberField(OperationParam::ChatMaxReturn.getValue(), in_maxToReturn);

    ServerCall *sc = new ServerCall(ServiceName::Chat, ServiceOperation::ChannelConnect, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudChat::channelDisconnect(const FString &in_channelId, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ChatChannelId.getValue(), in_channelId);

    ServerCall *sc = new ServerCall(ServiceName::Chat, ServiceOperation::ChannelDisconnect, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudChat::deleteChatMessage(const FString &in_channelId, const FString &in_messageId, int32 in_version, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ChatChannelId.getValue(), in_channelId);
    message->SetStringField(OperationParam::ChatMessageId.getValue(), in_messageId);
    message->SetNumberField(OperationParam::ChatVersion.getValue(), in_version);

    ServerCall *sc = new ServerCall(ServiceName::Chat, ServiceOperation::DeleteChatMessage, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudChat::getChannelId(const FString &in_channelType, const FString &in_channelSubId, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ChatChannelType.getValue(), in_channelType);
    message->SetStringField(OperationParam::ChatChannelSubId.getValue(), in_channelSubId);

    ServerCall *sc = new ServerCall(ServiceName::Chat, ServiceOperation::GetChannelId, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudChat::getChannelInfo(const FString &in_channelId, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ChatChannelId.getValue(), in_channelId);

    ServerCall *sc = new ServerCall(ServiceName::Chat, ServiceOperation::GetChannelInfo, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudChat::getChatMessage(const FString &in_channelId, const FString &in_messageId, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ChatChannelId.getValue(), in_channelId);
    message->SetStringField(OperationParam::ChatMessageId.getValue(), in_messageId);

    ServerCall *sc = new ServerCall(ServiceName::Chat, ServiceOperation::GetChatMessage, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudChat::getRecentChatMessages(const FString &in_channelId, int32 in_maxToReturn, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ChatChannelId.getValue(), in_channelId);
    message->SetNumberField(OperationParam::ChatMaxReturn.getValue(), in_maxToReturn);

    ServerCall *sc = new ServerCall(ServiceName::Chat, ServiceOperation::GetRecentChatMessages, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudChat::getSubscribedChannels(const FString &in_channelType, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ChatChannelType.getValue(), in_channelType);

    ServerCall *sc = new ServerCall(ServiceName::Chat, ServiceOperation::GetSubscribedChannels, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudChat::postChatMessage(const FString &in_channelId, const FString &in_plain, const FString &in_jsonRich, bool in_recordInHistory, IServerCallback *in_callback)
{
    // build content
    TSharedRef<FJsonObject> content = MakeShareable(new FJsonObject());
    content->SetStringField(OperationParam::ChatText.getValue(), in_plain);
    content->SetObjectField(OperationParam::ChatRich.getValue(), JsonUtil::jsonStringToValue(in_jsonRich));

    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ChatChannelId.getValue(), in_channelId);
    message->SetObjectField(OperationParam::ChatContent.getValue(), content);
    message->SetBoolField(OperationParam::ChatRecordInHistory.getValue(), in_recordInHistory);

    ServerCall *sc = new ServerCall(ServiceName::Chat, ServiceOperation::PostChatMessage, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudChat::postChatMessageSimple(const FString &in_channelId, const FString &in_plain, bool in_recordInHistory, IServerCallback *in_callback)
{
    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ChatChannelId.getValue(), in_channelId);
    message->SetStringField(OperationParam::ChatText.getValue(), in_plain);
    message->SetBoolField(OperationParam::ChatRecordInHistory.getValue(), in_recordInHistory);

    ServerCall *sc = new ServerCall(ServiceName::Chat, ServiceOperation::PostChatMessageSimple, message, in_callback);
    _client->sendRequest(sc);
}

void BrainCloudChat::updateChatMessage(const FString &in_channelId, const FString &in_messageId, int32 in_version,
                                       const FString &in_plain, const FString &in_jsonRich, IServerCallback *in_callback)
{
    // build content
    TSharedRef<FJsonObject> content = MakeShareable(new FJsonObject());
    content->SetStringField(OperationParam::ChatText.getValue(), in_plain);
    content->SetObjectField(OperationParam::ChatRich.getValue(), JsonUtil::jsonStringToValue(in_jsonRich));

    TSharedRef<FJsonObject> message = MakeShareable(new FJsonObject());
    message->SetStringField(OperationParam::ChatChannelId.getValue(), in_channelId);
    message->SetStringField(OperationParam::ChatMessageId.getValue(), in_messageId);
    message->SetNumberField(OperationParam::ChatVersion.getValue(), in_version);
    message->SetObjectField(OperationParam::ChatContent.getValue(), content);

    ServerCall *sc = new ServerCall(ServiceName::Chat, ServiceOperation::UpdateChatMessage, message, in_callback);
    _client->sendRequest(sc);
}
