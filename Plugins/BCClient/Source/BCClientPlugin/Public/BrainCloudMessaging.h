// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudMessaging
{
public:
    BrainCloudMessaging(BrainCloudClient* client);
        /// <summary>
    /// Deletes specified user messages on the server. in_msgBox = OperationParam.InboxMessageType && OperationParam.SentMessageType
    /// </summary>

    /// <summary>
    /// Retrieve user's message boxes, including 'inbox', 'sent', etc.
    /// </summary>

    /// <summary>
    /// Returns count of user's 'total' messages and their 'unread' messages.
    /// </summary>

    /// <summary>
    /// Retrieves list of specified messages.
    /// </summary>

    /// <summary>
    /// Retrieves a page of messages.
    /// </summary>

    /// <summary>
    /// Gets the page of messages from the server based on the encoded context and specified page offset.
    /// </summary>

    /// <summary>
    /// Marks list of user messages as read on the server.
    /// </summary>

    /// <summary>
    /// Sends a message with specified 'subject' and 'text' to list of users.
    /// </summary>

    /// <summary>
    /// Send a potentially rich chat message. <content> must contain at least a "plain" field for plain-text messaging.
    /// </summary>
private:
    BrainCloudClient* _client = nullptr;
};