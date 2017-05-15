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
	class AuthenticationType;

	class BrainCloudFriend
	{
	public:
		BrainCloudFriend(BrainCloudClient* in_client);

		/**
		* @deprecated Use findUserByUniversalId() instead - Removal after September 1 2017
		*/
		DEPRECATED
		void findPlayerByUniversalId(const char * in_searchText, int32_t in_maxResults, IServerCallback * in_callback = NULL);

		/**
		 * Retrieves profile information for the partial matches of the specified text.
		 *
		 * @param in_searchText Universal ID text on which to search.
		 * @param in_maxResults Maximum number of results to return.
		 */
		void findUserByUniversalId(const char * in_searchText, int32_t in_maxResults, IServerCallback * in_callback = NULL);

		/**
		* Retrieves profile information for the specified user.
		*
		* Service Name - friend
		* Service Operation - GET_PROFILE_INFO_FOR_CREDENTIAL
		*
		* @param in_externalId The users's external ID
		* @param in_authenticationType The authentication type of the user ID
		* @param in_callback Method to be invoked when the server response is received.
		*/
		void getProfileInfoForCredential(const char * in_externalId, AuthenticationType in_authenticationType, IServerCallback * in_callback = NULL);

		/**
		* Retrieves profile information for the specified external auth user.
		*
		* Service Name - friend
		* Service Operation - GET_PROFILE_INFO_FOR_EXTERNAL_AUTH_ID
		*
		* @param in_externalId External ID of the friend to find
		* @param in_externalAuthType The external authentication type used for this friend's external ID
		* @param in_callback Method to be invoked when the server response is received.
		*/
		void getProfileInfoForExternalAuthId(const char * in_externalId, const char * in_externalAuthType, IServerCallback * in_callback = NULL);

		/**
		 * Retrieves the external ID for the specified user profile ID on the specified social platform.
		 *
		 * @param in_profileId Profile (user) ID.
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
		* @deprecated Use readFriendUserState() instead - Removal after September 1 2017
		*/
		DEPRECATED
		void readFriendPlayerState(const char * in_friendId, IServerCallback * in_callback = NULL);
		
		/**
		 * Read a friend's user state.
		 *
		 * Service Name - Friend
		 * Service Operation - ReadFriendsPlayerState
		 *
		 * @param in_friendId Target friend
		 * @param in_callback Method to be invoked when the server response is received.
		 */
		void readFriendUserState(const char * in_friendId, IServerCallback * in_callback = NULL);

		/**
		* Returns user state of a particular user.
		*
		* Service Name - Friend
		* Service Operation - GET_SUMMARY_DATA_FOR_PROFILE_ID
		*
		* @param in_profileId Profile Id of user to retrieve user state for.
		* @param in_callback Method to be invoked when the server response is received.
		*/
		void getSummaryDataForProfileId(const char * in_profileId, IServerCallback * in_callback = NULL);

		/**
		* Finds a list of users matching the search text by performing an exact match search
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
		* Finds a list of users matching the search text by performing a substring
		* search of all user names.
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
		 * Retrieves a list of user and friend platform information for all friends of the current user.
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
		 * Links the current user and the specified users as brainCloud friends.
		 *
		 * Service Name - Friend
		 * Service Operation - ADD_FRIENDS
		 *
		 * @param in_profileIds Collection of profile IDs.
		 * @param in_callback Method to be invoked when the server response is received.
		 */
		void addFriends(const std::vector<std::string>& in_profileIds, IServerCallback * in_callback = NULL);

		/**
		* Unlinks the current user and the specified users as brainCloud friends.
		*
		* Service Name - Friend
		* Service Operation - REMOVE_FRIENDS
		*
		* @param in_profileIds Collection of profile IDs.
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
