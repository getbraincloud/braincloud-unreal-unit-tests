// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <string>
#include <vector>
#include "braincloud/BrainCloudTypes.h"

namespace BrainCloud
{
	class IServerCallback;
	class BrainCloudClient;
	class FriendPlatform;

	class BrainCloudFriend
	{
	public:
		BrainCloudFriend(BrainCloudClient* in_client);

		/**
		 * Retrieves profile information for the partial matches of the specified text.
		 *
		 * @param in_searchText Universal ID text on which to search.
		 * @param in_maxResults Maximum number of results to return.
		 */
		void findPlayerByUniversalId(const char * in_searchText, int32_t in_maxResults, IServerCallback * in_callback = NULL);

		/**
		 * Retrieves profile information for the specified user.
		 *
		 * Service Name - Friend
		 * Service Operation - GetFriendProfileInfoForExternalId
		 *
		 * @param in_externalId The friend's external id e.g. Facebook id
		 * @param in_authenticationType The authentication type of the friend id e.g. Facebook
		 */
		void getFriendProfileInfoForExternalId(const char *in_externalId, const char *in_authenticationType, IServerCallback * in_callback = NULL);

		/**
		 * Retrieves the external ID for the specified user profile ID on the specified social platform.
		 *
		 * @param in_profileId Profile (player) ID.
		 * @param in_authenticationType Associated authentication type.
		 */
		void getExternalIdForProfileId(const char * in_profileId, const char * in_authenticationType, IServerCallback * in_callback = NULL);

		/**
		* Returns a particular entity of a particular friend.
		*
		* Service Name - Friend
		* Service Operation - ReadFriendEntity
		*
		* @param in_entityId Id of entity to retrieve.
		* @param in_friendId Profile Id of friend who owns entity.
		* @param in_callback Method to be invoked when the server response is received.
		*/
		void readFriendEntity(const char* in_entityId, const char*  in_friendId, IServerCallback * in_callback = NULL);

		/**
		* Returns entities of all friends optionally based on type.
		*
		* Service Name - Friend
		* Service Operation - ReadFriendsEntities
		*
		* @param in_entityType Types of entities to retrieve.
		* @param in_callback Method to be invoked when the server response is received.
		*/
		void readFriendsEntities(const char* in_entityType, IServerCallback * in_callback = NULL);

		/**
		 * Read a friend's player state.
		 *
		 * Service Name - Friend
		 * Service Operation - ReadFriendsPlayerState
		 *
		 * @param in_friendId Target friend
		 * @param in_callback Method to be invoked when the server response is received.
		 */
		void readFriendPlayerState(const char * in_friendId, IServerCallback * in_callback = NULL);

		/**
		* Returns player state of a particular user.
		*
		* Service Name - Friend
		* Service Operation - GET_SUMMARY_DATA_FOR_PROFILE_ID
		*
		* @param in_profileId Profile Id of player to retrieve player state for.
		* @param in_callback Method to be invoked when the server response is received.
		*/
		void getSummaryDataForProfileId(const char * in_profileId, IServerCallback * in_callback = NULL);

		/**
		* @deprecated Use findUsersByExactName & findUsersBySubstrName instead - removal after Nov 22 2016
		*/
		DEPRECATED void findPlayerByName(const char * in_searchText, int32_t in_maxResults, IServerCallback * in_callback = NULL);

		/**
		* Finds a list of players matching the search text by performing an exact match search
		*
		* Service Name - friend
		* Service Operation - FIND_USERS_BY_EXACT_NAME
		*
		* @param searchText The string to search for.
		* @param maxResults  Maximum number of results to return.
		* @param callback Method to be invoked when the server response is received.
		*/
		void findUsersByExactName(const char * in_searchText, int32_t in_maxResults, IServerCallback * in_callback = NULL);

		/**
		* Finds a list of players matching the search text by performing a substring
		* search of all player names.
		*
		* Service Name - friend
		* Service Operation - FIND_USERS_BY_SUBSTR_NAME
		*
		* @param searchText The substring to search for. Minimum length of 3 characters.
		* @param maxResults  Maximum number of results to return. If there are more the message
		* @param callback Method to be invoked when the server response is received.
		*/
		void findUsersBySubstrName(const char * in_searchText, int32_t in_maxResults, IServerCallback * in_callback = NULL);

		/**
		 * Retrieves a list of player and friend platform information for all friends of the current player.
		 *
		 * Service Name - Friend
		 * Service Operation - LIST_FRIENDS
		 *
		 * @param in_friendPlatform Friend platform to query.
		 * @param in_includeSummaryData  True if including summary data; false otherwise.
		 * @param in_callback Method to be invoked when the server response is received.
		 */
		void listFriends(const FriendPlatform& in_friendPlatform, bool in_includeSummaryData, IServerCallback * in_callback = NULL);

		/**
		 * Links the current player and the specified players as brainCloud friends.
		 *
		 * Service Name - Friend
		 * Service Operation - ADD_FRIENDS
		 *
		 * @param in_profileIds Collection of player IDs.
		 * @param in_callback Method to be invoked when the server response is received.
		 */
		void addFriends(const std::vector<std::string>& in_profileIds, IServerCallback * in_callback = NULL);

		/**
		* Unlinks the current player and the specified players as brainCloud friends.
		*
		* Service Name - Friend
		* Service Operation - REMOVE_FRIENDS
		*
		* @param in_profileIds Collection of player IDs.
		* @param in_callback Method to be invoked when the server response is received.
		*/
		void removeFriends(const std::vector<std::string>& in_profileIds, IServerCallback * in_callback = NULL);

		/**
		* Get users online status
		*
		* Service Name - Friend
		* Service Operation - GET_USERS_ONLINE_STATUS
		*
		* @param in_profileIds Collection of profile IDs.
		* @param in_callback Method to be invoked when the server response is received.
		*/
		void getUsersOnlineStatus(const std::vector<std::string>& in_profileIds, IServerCallback * in_callback = NULL);

	private:
		BrainCloudClient * m_client;
	};
}