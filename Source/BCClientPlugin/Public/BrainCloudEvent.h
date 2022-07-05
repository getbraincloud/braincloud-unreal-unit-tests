// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudEvent
{
  public:
	BrainCloudEvent(BrainCloudClient *client);

	/**
	 * Sends an event to the designated player id with the attached json data.
	 * Any events that have been sent to a player will show up in their
	 * incoming event mailbox. If the recordLocally flag is set to true,
	 * a copy of this event (with the exact same event id) will be stored
	 * in the sending player's "sent" event mailbox.
	 *
	 * Note that the list of sent and incoming events for a player is returned
	 * in the "ReadUserState" call (in the BrainCloudPlayer module).
	 *
	 * Service Name - Event
	 * Service Operation - Send
	 *
	 * @param toPlayerId The id of the player who is being sent the event
	 * @param eventType The user-defined type of the event.
	 * @param jsonEventData The user-defined data for this event encoded in JSON.
	 * user's sent events mailbox.
	 * @param callback The method to be invoked when the server response is received
	 */
	void sendEvent(const FString &toPlayerId, const FString &eventType, const FString &jsonEventData, IServerCallback *callback);

	/**
	 * Updates an event in the player's incoming event mailbox.
	 *
	 * Service Name - Event
	 * Service Operation - UpdateEventData
	 *
	 * @param evId The event id
	 * @param jsonEventData The user-defined data for this event encoded in JSON.
	 * @param callback The method to be invoked when the server response is received
	 */
	void updateIncomingEventData(const FString &evId, const FString &jsonEventData, IServerCallback *callback);

	/**
	 * Delete an event out of the player's incoming mailbox.
	 *
	 * Service Name - Event
	 * Service Operation - DeleteIncoming
	 *
	 * @param evId The event id
	 * @param callback The method to be invoked when the server response is received
	 */
	void deleteIncomingEvent(const FString &evId, IServerCallback *callback);
	
	/**
	* Delete a list of events out of the user's incoming mailbox.
	*
	* Service Name - event
	* Service Operation - DELETE_INCOMING_EVENTS
	*
	* @param eventIds Collection of event ids
	* @param callback The method to be invoked when the server response is received
	*/
	void deleteIncomingEvents(const TArray<FString> & eventIds, IServerCallback *callback);
	
	/**
	* Delete any events older than the given date out of the user's incoming mailbox.
	*
	* Service Name - event
	* Service Operation - DELETE_INCOMING_EVENTS_OLDER_THAN
	*
	* @param dateMillis createdAt cut-off time whereby older events will be deleted (In UTC since Epoch)
	* @param callback The method to be invoked when the server response is received
	*/
	void deleteIncomingEventsOlderThan(int64 dateMillis, IServerCallback * callback);

	/**
	* Delete any events of the given type older than the given date out of the user's incoming mailbox.
	*
	* Service Name - event
	* Service Operation - DELETE_INCOMING_EVENTS_BY_TYPE_OLDER_THAN
	*
	* @param eventType The user-defined type of the event
	* @param dateMillis createdAt cut-off time whereby older events will be deleted (In UTC since Epoch)
	* @param callback The method to be invoked when the server response is received
	*/
	void deleteIncomingEventsByTypeOlderThan(const FString & eventType, int64 dateMillis, IServerCallback * callback);
	
	/**
	* Get the events currently queued for the player.
	*
	* Service Name - Event
	* Service Operation - GetEvents
	*
	* @param callback The method to be invoked when the server response is received
	*/
	void getEvents(IServerCallback *callback);

  private:
	BrainCloudClient *_client = nullptr;
};
