// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCChatProxy.generated.h"

UCLASS(MinimalAPI)
class UBCChatProxy : public UBCBlueprintCallProxyBase
{
    GENERATED_BODY()

  public:
    UBCChatProxy(const FObjectInitializer &ObjectInitializer);

    /**
    * Registers a listener for incoming events from <channelId>. 
    * Also returns a list of <maxReturn> recent messages from history.
    * 
    * Service Name - chat
	* Service Operation - CHANNEL_CONNECT
    *
    * @param in_channelId The channelId to connect to
	* @param in_maxToReturn Maximum number of messages to return.
	* @param in_callback Method to be invoked when the server response is received.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Chat")
    static UBCChatProxy *ChannelConnect(UBrainCloudWrapper *brainCloudWrapper, const FString &in_channelId, int32 in_maxToReturn);

    /**
    * Unregisters a listener for incoming events from <channelId>.
    * 
    * Service Name - chat
	* Service Operation - CHANNEL_DISCONNECT
    *
    * @param in_channelId The channelId to disconnect from
	* @param in_callback Method to be invoked when the server response is received.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Chat")
    static UBCChatProxy *ChannelDisconnect(UBrainCloudWrapper *brainCloudWrapper, const FString &in_channelId);

    /**
    * Delete a chat message. <version> 
    * 
    * Service Name - chat
	* Service Operation - DELETE_CHAT_MESSAGE
    *
    * @param in_channelId The channelId to delete the message from
    * @param in_messageId The messagedId of the message to delete
    * @param in_version The version of the message to delete, must match the latest or pass -1 to bypass version check.
	* @param in_callback Method to be invoked when the server response is received.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Chat")
    static UBCChatProxy *DeleteChatMessage(UBrainCloudWrapper *brainCloudWrapper, const FString &in_channelId, const FString &in_messageId, int32 in_version);

    /**
    * Gets the channelId for the given <channelType> and <channelSubId>. .
    * 
    * Service Name - chat
	* Service Operation - GET_CHANNEL_ID
    *
    * @param in_channelType The in_channelType of the channelId to retrieve, must be one of "gl"(GlobalChannelType) or "gr"(GroupChannelType)
    * @param in_channelSubId The in_channelSubId of the channelId to retrieve
	* @param in_callback Method to be invoked when the server response is received.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Chat")
    static UBCChatProxy *GetChannelId(UBrainCloudWrapper *brainCloudWrapper, const FString &in_channelType, const FString &in_channelSubId);

    /**
    * Gets description info and activity stats for channel <channelId>.
    * Note that numMsgs and listeners only returned for non-global groups.
    * Only callable for channels the user is a member of.
    * 
    * Service Name - chat
	* Service Operation - GET_CHANNEL_INFO
    *
    * @param in_channelId The channelId to delete the message from
	* @param in_callback Method to be invoked when the server response is received.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Chat")
    static UBCChatProxy *GetChannelInfo(UBrainCloudWrapper *brainCloudWrapper, const FString &in_channelId);

    /**
    * Gets a populated chat object (normally for editing).
    * 
    * Service Name - chat
	* Service Operation - GET_CHAT_MESSAGE
    *
    * @param in_channelId The channelId of the message to retrieve
    * @param in_messageId The messagedId of the message to retrieve
	* @param in_callback Method to be invoked when the server response is received.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Chat")
    static UBCChatProxy *GetChatMessage(UBrainCloudWrapper *brainCloudWrapper, const FString &in_channelId, const FString &in_messageId);

    /**
    * Get a list of <maxReturn> messages from history of channel <channelId>
    * 
    * Service Name - chat
	* Service Operation - GET_RECENT_CHAT_MESSAGES
    *
    * @param in_channelId The channelId to get recent chat history to
	* @param in_maxToReturn Maximum number of messages to return.
	* @param in_callback Method to be invoked when the server response is received.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Chat")
    static UBCChatProxy *GetRecentChatMessages(UBrainCloudWrapper *brainCloudWrapper, const FString &in_channelId, int32 in_maxToReturn);

    /**
    * Gets a list of the channels of type <channelType> that the user has access to.
    * 
    * Service Name - chat
	* Service Operation - GET_SUBSCRIBED_CHANNELS
    *
    * @param in_channelType The in_channelType of the channelIds to retrieve, must be one of "gl"(GlobalChannelType) or "gr"(GroupChannelType)
	* @param in_callback Method to be invoked when the server response is received.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Chat")
    static UBCChatProxy *GetSubscribedChannels(UBrainCloudWrapper *brainCloudWrapper, const FString &in_channelType);

    /**
    * Send a potentially rich chat message.
    * 
    * Service Name - chat
	* Service Operation - POST_CHAT_MESSAGE
    *
    * @param in_channelId The channelId to post the chat message to
    * @param in_plain The plain text message asscociated with the chat message
    * @param in_jsonRich The json string to associate with the chat message
    * @param in_recordInHistory Whether to record the message in history, or to only send it to currently active participants
	* @param in_callback Method to be invoked when the server response is received.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Chat")
    static UBCChatProxy *PostChatMessage(UBrainCloudWrapper *brainCloudWrapper, const FString &in_channelId, const FString &in_plain, const FString &in_jsonRich, bool in_recordInHistory);

    /**
    * Sends a plain-text chat message.
    * 
    * Service Name - chat
	* Service Operation - POST_CHAT_MESSAGE_SIMPLE
    *
    * @param in_channelId The channelId to post the chat message to
    * @param in_plain The plain text message asscociated with the chat message
    * @param in_recordInHistory Whether to record the message in history, or to only send it to currently active participants
	* @param in_callback Method to be invoked when the server response is received.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Chat")
    static UBCChatProxy *PostChatMessageSimple(UBrainCloudWrapper *brainCloudWrapper, const FString &in_channelId, const FString &in_plain, bool in_recordInHistory);

    /**
    * Update a chat message. <content> must contain at least a "plain" field for plain-text messaging. <version> must match the latest or pass -1 to bypass version check.
    * 
    * Service Name - chat
	* Service Operation - UPDATE_CHAT_MESSAGE
    *
    * @param in_channelId The channelId of the chat message to update
    * @param in_messageId The messagedId of the message to update
    * @param in_version The version of the message to update, must match the latest or pass -1 to bypass version check.
    * @param in_plain The plain text message asscociated with the chat message
    * @param in_jsonRich The json string to associate with the chat message
    * @param in_recordInHistory Whether to record the message in history, or to only send it to currently active participants
	* @param in_callback Method to be invoked when the server response is received.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Chat")
    static UBCChatProxy *UpdateChatMessage(UBrainCloudWrapper *brainCloudWrapper, const FString &in_channelId, const FString &in_messageId, int32 in_version,
                                           const FString &in_plain, const FString &in_jsonRich);
};
