// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudMessaging
{
  public:
    BrainCloudMessaging(BrainCloudClient *client);

    /**
    * Deletes specified user messages on the server.
    * 
    * Service Name - messaging
	* Service Operation - DELETE_MESSAGES
    *
    * @param in_msgBox The msgBox that the msgIds belong to
	* @param in_msgsIds Array of msg Ids to delete
	* @param in_callback Method to be invoked when the server response is received.
    */
    void deleteMessages(const FString &in_msgBox, const TArray<FString> &in_msgsIds, IServerCallback *in_callback);

    /**
    * Retrieve user's message boxes, including 'inbox', 'sent', etc.
    * 
    * Service Name - messaging
	* Service Operation - GET_MESSAGE_BOXES
    *
	* @param in_callback Method to be invoked when the server response is received.
    */
    void getMessageBoxes(IServerCallback *in_callback);

    /**
    * Returns count of user's 'total' messages and their 'unread' messages.
    * 
    * Service Name - messaging
	* Service Operation - GET_MESSAGE_COUNTS
    *
	* @param in_callback Method to be invoked when the server response is received.
    */
    void getMessageCounts(IServerCallback *in_callback);

    /**
    * Retrieves list of specified messages.
    * 
    * Service Name - messaging
	* Service Operation - GET_MESSAGES
    *
    * @param in_msgBox The msgBox that the msgIds belong to
	* @param in_msgsIds Array of msg Ids to delete
	* @param in_callback Method to be invoked when the server response is received.
    */
    void getMessages(const FString &in_msgBox, const TArray<FString> &in_msgsIds, bool markAsRead, IServerCallback *in_callback);

    /**
    * Retrieves a page of messages.
    * 
    * Service Name - messaging
	* Service Operation - GET_MESSAGES_PAGE
    *
    * @param in_context 
	* @param in_callback Method to be invoked when the server response is received.
    */
    void getMessagesPage(const FString &in_context, IServerCallback *in_callback);

    /**
    * Retrieves a page of messages.
    * 
    * Service Name - messaging
	* Service Operation - GET_MESSAGES_PAGE_OFFSET
    *
    * @param in_context 
    * @param in_pageOffset 
	* @param in_callback Method to be invoked when the server response is received.
    */
    void getMessagesPageOffset(const FString &in_context, int32 in_pageOffset, IServerCallback *in_callback);

    /**
    * Retrieves a page of messages.
    * 
    * Service Name - messaging
	* Service Operation - MARK_MESSAGES_READ
    *
    * @param in_msgBox The msgBox that the msgIds belong to
	* @param in_msgsIds Array of msg Ids to mark as read
	* @param in_callback Method to be invoked when the server response is received.
    */
    void markMessagesRead(const FString &in_msgBox, const TArray<FString> &in_msgsIds, IServerCallback *in_callback);

    /**
    *Sends a message with specified 'subject' and 'text' to list of users.
    * 
    * Service Name - messaging
	* Service Operation - SEND_MESSAGE
    *
    * @param in_toProfileIds Array of recipients for the message
	* @param in_messageText Messsage Text
    * @param in_messageSubject Messsage subject
	* @param in_callback Method to be invoked when the server response is received.
    */
    void sendMessage(const TArray<FString> &in_toProfileIds, const FString &in_contentJson, IServerCallback *in_callback);

    /**
    *Sends a message with specified 'subject' and 'text' to list of users.
    * 
    * Service Name - messaging
	* Service Operation - SEND_MESSAGE_SIMPLE
    *
    * @param in_toProfileIds Array of recipients for the message
	* @param in_messageText Messsage Text
	* @param in_callback Method to be invoked when the server response is received.
    */
    void sendMessageSimple(const TArray<FString> &in_toProfileIds, const FString &in_messageText, IServerCallback *in_callback);

  private:
    BrainCloudClient *_client = nullptr;
};