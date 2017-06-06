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
		 * Sends an event to the designated user id with the attached json data.
		 * Any events that have been sent to a user will show up in their
		 * incoming event mailbox. If the in_recordLocally flag is set to true,
		 * a copy of this event (with the exact same event id) will be stored
		 * in the sending user's "sent" event mailbox.
		 *
		 * Note that the list of sent and incoming events for a user is returned
		 * in the "ReadPlayerState" call (in the BrainCloudPlayer module).
		 *
		 * Service Name - event
		 * Service Operation - SEND
		 *
		 * @param in_toProfileId The id of the user who is being sent the event
		 * @param in_eventType The user-defined type of the event.
		 * @param in_jsonEventData The user-defined data for this event encoded in JSON.
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void sendEvent(const char * in_toProfileId, const char * in_eventType, const std::string& in_jsonEventData, IServerCallback * in_callback = NULL);

		/**
		 * Updates an event in the user's incoming event mailbox.
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
		 * Delete an event out of the user's incoming mailbox.
		 *
		 * Service Name - event
		 * Service Operation - DELETE_INCOMING
		 *
		 * @param in_evId The event id
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void deleteIncomingEvent(const char * in_evId, IServerCallback * in_callback = NULL);

		/**
		 * Get the events currently queued for the user.
		 *
		 * Service Name - event
		 * Service Operation - GET_EVENTS
		 *
		 * @param in_callback The method to be invoked when the server response is received
		 */
		void getEvents(IServerCallback * in_callback = NULL);

		/**
		 * @deprecated Use method with new signature
		 */
		DEPRECATED void sendEvent(const char * in_toPlayerId, const char * in_eventType, const std::string& in_jsonEventData, bool in_recordLocally, IServerCallback * in_callback = NULL);
			
		/**
		 * @deprecated Use method with new signature
		 */
		DEPRECATED void updateIncomingEventData(const char * in_fromPlayerId, uint64_t in_eventId, const std::string& in_jsonEventData, IServerCallback * in_callback = NULL);
			
		/**
		 * @deprecated Use method with new signature
		 */
		DEPRECATED void deleteIncomingEvent(const char * in_fromPlayerId, uint64_t in_eventId, IServerCallback * in_callback = NULL);
			
		/**
		 * @deprecated Use method with new signature
		 */
		DEPRECATED void deleteSentEvent(const char * in_toPlayerId, uint64_t in_eventId, IServerCallback * in_callback = NULL);
			
		/**
		 * @deprecated Use method with new signature
		 */
		DEPRECATED void getEvents(bool in_includeIncomingEvents, bool in_includeSentEvents, IServerCallback * in_callback = NULL);


	private:
		BrainCloudClient * m_client;
	};
}
