// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <string>
#include "braincloud/BrainCloudTypes.h"

namespace BrainCloud
{
	class IServerCallback;
	class BrainCloudClient;

	class BrainCloudEvent
	{
	public:
		BrainCloudEvent(BrainCloudClient* in_client);

		/**
		 * Sends an event to the designated player id with the attached json data.
		 * Any events that have been sent to a player will show up in their
		 * incoming event mailbox. If the in_recordLocally flag is set to true,
		 * a copy of this event (with the exact same event id) will be stored
		 * in the sending player's "sent" event mailbox.
		 *
		 * Note that the list of sent and incoming events for a player is returned
		 * in the "ReadPlayerState" call (in the BrainCloudPlayer module).
		 *
		 * Service Name - event
		 * Service Operation - SEND
		 *
		 * @param in_toPlayerId The id of the player who is being sent the event
		 * @param in_eventType The user-defined type of the event.
		 * @param in_jsonEventData The user-defined data for this event encoded in JSON.
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void sendEvent(const char * in_toPlayerId, const char * in_eventType, const std::string& in_jsonEventData, IServerCallback * in_callback = NULL);

		/**
		 * Updates an event in the player's incoming event mailbox.
		 *
		 * Service Name - event
		 * Service Operation - UPDATE_EVENT_DATA
		 *
		 * @param in_evId The event id
		 * @param in_jsonEventData The user-defined data for this event encoded in JSON.
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void updateIncomingEventData(const char * in_evId, const std::string& in_jsonEventData, IServerCallback * in_callback = NULL);

		/**
		 * Delete an event out of the player's incoming mailbox.
		 *
		 * Service Name - event
		 * Service Operation - DELETE_INCOMING
		 *
		 * @param in_evId The event id
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void deleteIncomingEvent(const char * in_evId, IServerCallback * in_callback = NULL);

		/**
		 * Get the events currently queued for the player.
		 *
		 * Service Name - event
		 * Service Operation - GET_EVENTS
		 *
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void getEvents(IServerCallback * in_callback = NULL);

	private:
		BrainCloudClient * m_client;
	};
}
