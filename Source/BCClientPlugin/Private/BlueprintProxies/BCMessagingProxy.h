// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCMessagingProxy.generated.h"

UCLASS(MinimalAPI)
class UBCMessagingProxy : public UBCBlueprintCallProxyBase
{
    GENERATED_BODY()

  public:
    UBCMessagingProxy(const FObjectInitializer &ObjectInitializer);

    /**
    * Deletes specified user messages on the server.
    * 
    * Service Name - messaging
	* Service Operation - DELETE_MESSAGES
    *
    * @param in_msgBox The msgBox that the msgIds belong to
	* @param in_msgsIds Array of msg Ids to delete	
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Messaging")
    static UBCMessagingProxy *DeleteMessages(UBrainCloudWrapper *brainCloudWrapper, const FString &in_msgBox, const TArray<FString> &in_msgsIds);

    /**
    * Retrieve user's message boxes, including 'inbox', 'sent', etc.
    * 
    * Service Name - messaging
	* Service Operation - GET_MESSAGE_BOXES
    *	
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Messaging")
    static UBCMessagingProxy *GetMessageBoxes(UBrainCloudWrapper *brainCloud);

    /**
    * Returns count of user's 'total' messages and their 'unread' messages.
    * 
    * Service Name - messaging
	* Service Operation - GET_MESSAGE_COUNTS
    *	
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Messaging")
    static UBCMessagingProxy *GetMessageCounts(UBrainCloudWrapper *brainCloud);

    /**
    * Retrieves list of specified messages.
    * 
    * Service Name - messaging
	* Service Operation - GET_MESSAGES
    *
    * @param in_msgBox The msgBox that the msgIds belong to
	* @param in_msgsIds Array of msg Ids to delete	
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Messaging")
    static UBCMessagingProxy *GetMessages(UBrainCloudWrapper *brainCloudWrapper, const FString &in_msgBox, const TArray<FString> &in_msgsIds, bool markAsRead);

    /**
    * Retrieves a page of messages.
    * 
    * Service Name - messaging
	* Service Operation - GET_MESSAGES_PAGE
    *
    * @param in_context 	
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Messaging")
    static UBCMessagingProxy *GetMessagesPage(UBrainCloudWrapper *brainCloudWrapper, const FString &in_context);

    /**
    * Retrieves a page of messages.
    * 
    * Service Name - messaging
	* Service Operation - GET_MESSAGES_PAGE_OFFSET
    *
    * @param in_context 
    * @param in_pageOffset 
	
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Messaging")
    static UBCMessagingProxy *GetMessagesPageOffset(UBrainCloudWrapper *brainCloudWrapper, const FString &in_context, int32 in_pageOffset);

    /**
    * Retrieves a page of messages.
    * 
    * Service Name - messaging
	* Service Operation - MARK_MESSAGES_READ
    *
    * @param in_msgBox The msgBox that the msgIds belong to
	* @param in_msgsIds Array of msg Ids to mark as read	
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Messaging")
    static UBCMessagingProxy *MarkMessagesRead(UBrainCloudWrapper *brainCloudWrapper, const FString &in_msgBox, const TArray<FString> &in_msgsIds);

    /**
    *Sends a message with specified 'subject' and 'text' to list of users.
    * 
    * Service Name - messaging
	* Service Operation - SEND_MESSAGE
    *
    * @param in_toProfileIds Array of recipients for the message
	* @param in_messageText Messsage Text
    * @param in_messageSubject Messsage subject	
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Messaging")
    static UBCMessagingProxy *SendMessage(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &in_toProfileIds, const FString &in_contentJson);

    /**
    *Sends a message with specified 'subject' and 'text' to list of users.
    * 
    * Service Name - messaging
	* Service Operation - SEND_MESSAGE_SIMPLE
    *
    * @param in_toProfileIds Array of recipients for the message
	* @param in_messageText Messsage Text	
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Messaging")
    static UBCMessagingProxy *SendMessageSimple(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &in_toProfileIds, const FString &in_messageText);
};
