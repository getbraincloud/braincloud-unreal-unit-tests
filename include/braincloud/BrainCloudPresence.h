// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#ifndef _BRAINCLOUDPRESENCE_H_
#define _BRAINCLOUDPRESENCE_H_

#include "braincloud/BrainCloudTypes.h"

#include <string>
#include <vector>

namespace BrainCloud
{
	class IServerCallback;
	class BrainCloudClient;

	class BrainCloudPresence
	{
	public:
		BrainCloudPresence(BrainCloudClient* in_client);

		/**
		 * Force an RTT presence update to all listeners of the caller.
		 *
		 * Service Name - Presence
		 * Service Operation - ForcePush
		 *
		 * @param callback The method to be invoked when the server response is received
		 */
		void forcePush(IServerCallback* in_callback = NULL);

		/**
		 * Gets the presence data for the given <platform>. Can be one of "all",
		 * "brainCloud", or "facebook". Will not include offline profiles
		 * unless <includeOffline> is set to true.
		 */
		void getPresenceOfFriends(const std::string& in_platform, bool in_includeOffline, IServerCallback* in_callback = NULL);

		/**
		 * Gets the presence data for the given <groupId>. Will not include
		 * offline profiles unless <includeOffline> is set to true.
		 */
		void getPresenceOfGroup(const std::string& in_groupId, bool in_includeOffline, IServerCallback* in_callback = NULL);

		/**
		 * Gets the presence data for the given <profileIds>. Will not include
		 * offline profiles unless <includeOffline> is set to true.
		 */
		void getPresenceOfUsers(const std::vector<std::string>& in_profileIds, bool in_includeOffline, IServerCallback* in_callback = NULL);

		/**
		 * Registers the caller for RTT presence updates from friends for the
		 * given <platform>. Can be one of "all", "brainCloud", or "facebook".
		 * If <bidirectional> is set to true, then also registers the targeted
		 * users for presence updates from the caller.
		 */
		void registerListenersForFriends(const std::string& in_platform, bool in_bidirectional, IServerCallback* in_callback = NULL);

		/**
		 * Registers the caller for RTT presence updates from the members of
		 * the given <groupId>. Caller must be a member of said group. If
		 * <bidirectional> is set to true, then also registers the targeted
		 * users for presence updates from the caller.
		 */
		void registerListenersForGroup(const std::string& in_groupId, bool in_bidirectional, IServerCallback* in_callback = NULL);

		/**
		 * Registers the caller for RTT presence updates for the given
		 * <profileIds>. If <bidirectional> is set to true, then also registers
		 * the targeted users for presence updates from the caller.
		 */
		void registerListenersForProfiles(const std::vector<std::string>& in_profileIds, bool in_bidirectional, IServerCallback* in_callback = NULL);

		/**
		 * Update the presence data visible field for the caller.
		 */
		void setVisibility(bool in_visible, IServerCallback* in_callback = NULL);

		/**
		 * Stops the caller from receiving RTT presence updates. Does not
		 * affect the broadcasting of *their* presence updates to other
		 * listeners.
		 */
		void stopListening(IServerCallback* in_callback = NULL);

		/**
		 * Update the presence data activity field for the caller.
		 */
		void updateActivity(const std::string& in_jsonActivity, IServerCallback* in_callback = NULL);

	private:
		BrainCloudClient* m_client;
	};
};

#endif /* _BRAINCLOUDPRESENCE_H_ */
