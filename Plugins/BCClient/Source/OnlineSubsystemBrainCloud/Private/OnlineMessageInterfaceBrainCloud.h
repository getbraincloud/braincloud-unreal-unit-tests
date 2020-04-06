// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "Interfaces/OnlineMessageInterface.h"
#include "OnlineSubsystemBrainCloud.h"

/**
* BrainCloud service implementation of the online message interface
*/
class FOnlineMessageBrainCloud : public IOnlineMessage
{
public:

    /**
    * Constructor
    * @param inSubsystem online subsystem being used
    */
    FOnlineMessageBrainCloud(FOnlineSubsystemBrainCloud* inSubsystem);

    /**
    * Destructor
    */
    virtual ~FOnlineMessageBrainCloud();

    /**
    * Enumerate list of available message headers from user's inbox
    *
    * @param LocalUserNum the controller number of the associated user that made the request
    *
    * @return true if request was started
    */
    virtual bool EnumerateMessages(int32 LocalUserNum) override;

    /**
    * Get the cached list of message headers for a user. Cache is populated by calling EnumerateMessages
    *
    * @param LocalUserNum the controller number of the associated user that made the request
    * @param OutHeaders [out] array of message headers that were found
    *
    * @return true if cached entry was found
    */
    virtual bool GetMessageHeaders(int32 LocalUserNum, TArray< TSharedRef<FOnlineMessageHeader> >& OutHeaders) override;

    /**
    * Clear the cached list of message headers
    *
    * @param LocalUserNum the controller number of the associated user that made the request
    *
    * @return true if messages were clear, false if there was a problem
    */
    virtual bool ClearMessageHeaders(int32 LocalUserNum) override;

    /**
    * Download a message and its payload from user's inbox
    *
    * @param LocalUserNum the controller number of the associated user that made the request
    * @param MessageId unique id of the message to download. Obtained from message header list
    *
    * @return true if request was started
    */
    virtual bool ReadMessage(int32 LocalUserNum, const FUniqueMessageId& MessageId) override;

    /**
    * Get the cached message and its contents for a user. Cache is populated by calling ReadMessage with a message id
    *
    * @param LocalUserNum the controller number of the associated user that made the request
    * @param MessageId unique id of the message downloaded to find
    *
    * @return pointer to message entry if found or NULL
    */
    virtual TSharedPtr<FOnlineMessage> GetMessage(int32 LocalUserNum, const FUniqueMessageId& MessageId) override;

    /**
    * Clear the given cached message
    *
    * @param LocalUserNum the controller number of the associated user that made the request
    *
    * @return true if messages were clear, false if there was a problem
    */
    virtual bool ClearMessage(int32 LocalUserNum, const FUniqueMessageId& MessageId) override;

    /**
    * Clear all the cached messages
    *
    * @param LocalUserNum the controller number of the associated user that made the request
    *
    * @return true if messages were clear, false if there was a problem
    */
    virtual bool ClearMessages(int32 LocalUserNum) override;

    /**
    * Send a message from the currently logged in user to a list of recipients
    *
    * @param LocalUserNum the controller number of the associated user that made the request
    * @param RecipientIds unique ids of users to send this message to
    * @param MessageType string representing the type of message
    * @param Payload the body/content of the message
    *
    * @return true if request was started
    */
    virtual bool SendMessage(int32 LocalUserNum, const TArray< TSharedRef<const FUniqueNetId> >& RecipientIds, const FString& MessageType, const FOnlineMessagePayload& Payload) override;

    /**
    * Delete a message from currently logged in user's inbox
    *
    * @param LocalUserNum the controller number of the associated user that made the request
    * @param MessageId unique id of the message to delete. Obtained from message header list
    *
    * @return true if request was started
    */
    virtual bool DeleteMessage(int32 LocalUserNum, const FUniqueMessageId& MessageId) override;

private:
    FOnlineSubsystemBrainCloud* _subsystem;

    TArray<TSharedPtr<FOnlineMessageHeader>> _cachedMessageHeaders;
    TArray<TSharedPtr<FOnlineMessage>> _cachedMessages;

    //BC Callbacks
    void EnumerateMessagesSuccess(const FString& jsonData);
    void EnumerateMessagesFail(int32 returnCode, const FString& jsonData);

    void SendMessagesSuccess(const FString& jsonData);
    void SendMessagesFail(int32 returnCode, const FString& jsonData);

    void DeleteMessagesSuccess(const FString& jsonData, const FUniqueMessageId& MessageId);
    void DeleteMessagesFail(int32 returnCode, const FString& jsonData, const FUniqueMessageId& MessageId);
};

typedef TSharedPtr<FOnlineMessageBrainCloud, ESPMode::ThreadSafe> FOnlineMessageBrainCloudPtr;