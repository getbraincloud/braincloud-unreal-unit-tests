// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudEvent {
public:
    BrainCloudEvent(BrainCloudClient* client);

    /**
     * Sends an event to the designated player id with the attached json data.
     * Any events that have been sent to a player will show up in their
     * incoming event mailbox. If the recordLocally flag is set to true,
     * a copy of this event (with the exact same event id) will be stored
     * in the sending player's "sent" event mailbox.
     *
     * Note that the list of sent and incoming events for a player is returned
     * in the "ReadPlayerState" call (in the BrainCloudPlayer module).
     *
     * Service Name - Event
     * Service Operation - Send
     *
     * @param toPlayerId The id of the player who is being sent the event
     * @param eventType The user-defined type of the event.
     * @param jsonEventData The user-defined data for this event encoded in JSON.
     * @param recordLocally If true, a copy of this event will be saved in the
     * user's sent events mailbox.
     * @param callback The method to be invoked when the server response is received
     */
    void sendEvent(const FString& toPlayerId, const FString& eventType, const FString& jsonEventData, bool recordLocally, IServerCallback* callback);

    /**
     * Updates an event in the player's incoming event mailbox.
     *
     * Service Name - Event
     * Service Operation - UpdateEventData
     *
     * @param fromPlayerId The id of the player who sent the event
     * @param eventId The event id
     * @param jsonEventData The user-defined data for this event encoded in JSON.
     * @param callback The method to be invoked when the server response is received
     */
    void updateIncomingEventData(const FString& fromPlayerId, uint64 eventId, const FString& jsonEventData, IServerCallback* callback);

    /**
     * Delete an event out of the player's incoming mailbox.
     *
     * Service Name - Event
     * Service Operation - DeleteIncoming
     *
     * @param fromPlayerId The id of the player who sent the event
     * @param eventId The event id
     * @param callback The method to be invoked when the server response is received
     */
    void deleteIncomingEvent(const FString& fromPlayerId, uint64 eventId, IServerCallback* callback);

    /**
     * Delete an event from the player's sent mailbox.
     *
     * Note that only events sent with the "recordLocally" flag
     * set to true will be added to a player's sent mailbox.
     *
     * Service Name - Event
     * Service Operation - DeleteSent
     *
     * @param toPlayerId The id of the player who is being sent the even
     * @param eventId The event id
     * @param callback The method to be invoked when the server response is received
     */
    void deleteSentEvent(const FString& toPlayerId, uint64 eventId, IServerCallback* callback);

    /**
    * Get the events currently queued for the player.
    *
    * Service Name - Event
    * Service Operation - GetEvents
    *
    * @param includeIncomingEvents Get events sent to the player
    * @param includeSentEvents Get events sent from the player
    * @param callback The method to be invoked when the server response is received
    */
    void getEvents(bool includeIncomingEvents, bool includeSentEvents, IServerCallback * callback);

private:
    BrainCloudClient* _client = nullptr;
};
