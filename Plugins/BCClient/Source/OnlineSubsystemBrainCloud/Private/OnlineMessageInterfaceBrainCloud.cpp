// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "OnlineMessageInterfaceBrainCloud.h"
#include "OnlineSubsystemBrainCloudPrivatePCH.h"

#include "Misc/Base64.h"
#include "BrainCloudClient.h"
#include "ServiceOperation.h"
#include "ServiceName.h"
#include "MessageCallback.h"

#include "AssignableServerCallback.h"

FOnlineMessageBrainCloud::FOnlineMessageBrainCloud(FOnlineSubsystemBrainCloud* inSubsystem)
    : _subsystem(inSubsystem)
{
}

FOnlineMessageBrainCloud::~FOnlineMessageBrainCloud()
{
}

bool FOnlineMessageBrainCloud::EnumerateMessages(int32 LocalUserNum)
{
    AssignableServerCallback* cb = _subsystem->GetCallbackObject<AssignableServerCallback>();
    cb->OnSuccessDelegate.AddRaw(this, &FOnlineMessageBrainCloud::EnumerateMessagesSuccess);
    cb->OnFailDelegate.AddRaw(this, &FOnlineMessageBrainCloud::EnumerateMessagesFail);

    _subsystem->GetClient()->getEventService()->getEvents(cb);

    return true;
}

bool FOnlineMessageBrainCloud::GetMessageHeaders(int32 LocalUserNum, TArray<TSharedRef<FOnlineMessageHeader>>& OutHeaders)
{
    for (int32 i = 0; i < _cachedMessageHeaders.Num(); i++)
    {
        OutHeaders.Add(_cachedMessageHeaders[i].ToSharedRef());
    }
    return true;
}

bool FOnlineMessageBrainCloud::ClearMessageHeaders(int32 LocalUserNum)
{
    _cachedMessageHeaders.Empty();
    return true;
}

bool FOnlineMessageBrainCloud::ReadMessage(int32 LocalUserNum, const FUniqueMessageId & MessageId)
{
    for (int32 i = 0; i < _cachedMessages.Num(); i++)
    {
        if (_cachedMessages[i]->MessageId.Get() == MessageId)
        {
            OnReadMessageCompleteDelegates->Broadcast(0, true, MessageId, TEXT(""));
            return true;
        }
    }

    OnReadMessageCompleteDelegates->Broadcast(0, false, MessageId, TEXT("Message not found with ID"));
    return false;
}

TSharedPtr<FOnlineMessage> FOnlineMessageBrainCloud::GetMessage(int32 LocalUserNum, const FUniqueMessageId & MessageId)
{
    for (int32 i = 0; i < _cachedMessages.Num(); i++)
    {
        if (_cachedMessages[i]->MessageId.Get() == MessageId)
        {
            return _cachedMessages[i];
        }
    }
    return nullptr;
}

bool FOnlineMessageBrainCloud::ClearMessage(int32 LocalUserNum, const FUniqueMessageId & MessageId)
{
    for (int32 i = 0; i < _cachedMessages.Num(); i++)
    {
        if (_cachedMessages[i]->MessageId.Get() == MessageId)
        {
            _cachedMessages.RemoveAt(i);
            return true;
        }
    }
    return false;
}

bool FOnlineMessageBrainCloud::ClearMessages(int32 LocalUserNum)
{
    _cachedMessages.Empty();
    return true;
}

bool FOnlineMessageBrainCloud::SendMessage(int32 LocalUserNum, const TArray<TSharedRef<const FUniqueNetId>>& RecipientIds, const FString & MessageType, const FOnlineMessagePayload & Payload)
{
    TArray<uint8> payloadBytes;
    Payload.ToBytes(payloadBytes);
    FString payloadStr = FBase64::Encode(payloadBytes);

    TSharedRef<FJsonObject> jsonObj = MakeShareable(new FJsonObject());
    jsonObj->SetStringField(TEXT("payload"), payloadStr);

    FString jsonDataStr;
    TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&jsonDataStr);
    FJsonSerializer::Serialize(jsonObj, writer);

    AssignableServerCallback* cb = _subsystem->GetCallbackObject<AssignableServerCallback>();
    cb->OnSuccessDelegate.AddRaw(this, &FOnlineMessageBrainCloud::SendMessagesSuccess);
    cb->OnFailDelegate.AddRaw(this, &FOnlineMessageBrainCloud::SendMessagesFail);

    for (int32 i = 0; i < RecipientIds.Num(); i++)
    {
        
        _subsystem->GetClient()->getEventService()->sendEvent(
            RecipientIds[i]->ToString(),
            MessageType,
            jsonDataStr,
            i < RecipientIds.Num() - 1 ? nullptr : cb);
    }

    return true;
}

bool FOnlineMessageBrainCloud::DeleteMessage(int32 LocalUserNum, const FUniqueMessageId & MessageId)
{
    TSharedPtr<FOnlineMessageHeader> message;

    for (int32 i = 0; i < _cachedMessageHeaders.Num(); i++)
    {
        if (_cachedMessageHeaders[i]->MessageId.Get() == MessageId)
        {
            message = _cachedMessageHeaders[i];
            break;
        }
    }

    if (!message.IsValid())
    {
        UE_LOG(LogOnline, Warning, TEXT("Cannot find cached message header for ID %s to delete"), *MessageId.ToString());
        return false;
    }

    MessageCallback* cb = new MessageCallback(MessageId);
    _subsystem->RegisterCallbackObject(cb);
    cb->OnSuccessDelegate.AddRaw(this, &FOnlineMessageBrainCloud::DeleteMessagesSuccess);
    cb->OnFailDelegate.AddRaw(this, &FOnlineMessageBrainCloud::DeleteMessagesFail);

    _subsystem->GetClient()->getEventService()->deleteIncomingEvent(
        message->FromUserId->ToString(),
        cb);

    return true;
}

//BC Callbacks
void FOnlineMessageBrainCloud::EnumerateMessagesSuccess(const FString& jsonData)
{
    _cachedMessageHeaders.Empty();
    _cachedMessages.Empty();

    TArray<TSharedPtr<FJsonValue>> messages = FOnlineSubsystemBrainCloud::GetJsonData(jsonData)->GetArrayField("incoming_events");

    for (int32 i = 0; i < messages.Num(); ++i)
    {
        FJsonObject* messageObj = messages[i]->AsObject().Get();

        if (!messageObj->GetObjectField(TEXT("eventData"))->HasField("payload"))
        {
            UE_LOG(LogOnline, Display, TEXT("Message with no payload received, ignoring."));
            continue;
        }

        //header creation
        FString fromId = messageObj->GetStringField("fromPlayerId");
        FString messageId = FString::FromInt((int64)messageObj->GetNumberField("eventId"));


        #if ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION >= 18
        const TSharedRef <FUniqueNetIdString> sref_fromId = MakeShareable(new FUniqueNetIdString(fromId));
        const TSharedRef <FUniqueNetIdString> sref_messageId = MakeShareable(new FUniqueNetIdString(messageId));
        FOnlineMessageHeader *fOnlineMessageHeader = new FOnlineMessageHeader(sref_fromId, sref_messageId);

        TSharedPtr<FOnlineMessageHeader> header = MakeShareable(fOnlineMessageHeader);
        #else
        TSharedPtr<FOnlineMessageHeader> header = MakeShareable( 
            new FOnlineMessageHeader(new FUniqueNetIdString(fromId), new FUniqueNetIdString(messageId))); 
        #endif


        header->TimeStamp = FDateTime::FromUnixTimestamp((int64)messageObj->GetNumberField("createdAt") / 1000).ToString();
        header->Type = messageObj->GetStringField("eventType");

        _cachedMessageHeaders.Add(header);

        //message
        TSharedPtr<FOnlineMessage> message = MakeShareable(new FOnlineMessage(new FUniqueNetIdString(messageId)));

        FString payloadStr = messageObj->GetObjectField("eventData")->GetStringField("payload");
        TArray<uint8> bytes;
        FBase64::Decode(payloadStr, bytes);
        message->Payload.FromBytes(bytes);

        _cachedMessages.Add(message);
    }

    OnEnumerateMessagesCompleteDelegates->Broadcast(0, true, TEXT(""));
}

void FOnlineMessageBrainCloud::EnumerateMessagesFail(int32 returnCode, const FString& jsonData)
{
    OnEnumerateMessagesCompleteDelegates->Broadcast(0, false, jsonData);
}

void FOnlineMessageBrainCloud::SendMessagesSuccess(const FString& jsonData)
{
    OnSendMessageCompleteDelegates->Broadcast(0, true, TEXT(""));
}

void FOnlineMessageBrainCloud::SendMessagesFail(int32 returnCode, const FString& jsonData)
{
    OnSendMessageCompleteDelegates->Broadcast(0, false, jsonData);
}

void FOnlineMessageBrainCloud::DeleteMessagesSuccess(const FString& jsonData, const FUniqueMessageId& MessageId)
{
    OnDeleteMessageCompleteDelegates->Broadcast(0, true, MessageId, TEXT(""));
}

void FOnlineMessageBrainCloud::DeleteMessagesFail(int32 returnCode, const FString& jsonData, const FUniqueMessageId& MessageId)
{
    OnDeleteMessageCompleteDelegates->Broadcast(0, false, MessageId, jsonData);
}
