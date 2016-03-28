// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <string>
#include <vector>
#include "BrainCloudTypes.h"

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
         * @return Object containing profile information.
         *  The JSON returned in the callback
         * {
         *   "status":200,
         *   "data": {
         *     "matchedCount" : 20,
         *     "matches" : [{
         *       "profileId" : "17c7ee96-1b73-43d0-8817-cba1953bbf57",
         *       "profileName" : "Donald Trump",
         *       "playerSummaryData" : {}
         *     },{
         *       "profileId" : "19d7ee96-2x73-43d0-8817-cba1953bbf57",
         *       "profileName" : "Donald Duck",
         *       "playerSummaryData" : {}
         *     }
         *     ]
         *   }
         * }
         *
         * Alternatively, if there are too many results:
         * {
         *   "status":200,
         *   "data": {
         *     "matchedCount" : 2059,
         *     "message" : "Too many results to return."
         *   }
         * }
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
         *
         * @return The JSON returned in the callback
         * {
         *   "status":200,
         *   "data": {
         *     "playerId" : "17c7ee96-1b73-43d0-8817-cba1953bbf57",
         *     "playerName" : "Donald Trump",
         *     "email" : "donald@trumpcastle.com",
         *     "playerSummaryData" : {},
         *   }
         * }
         */
        void getFriendProfileInfoForExternalId(const char *in_externalId, const char *in_authenticationType, IServerCallback * in_callback = NULL);

        /**
         * Retrieves the external ID for the specified user profile ID on the specified social platform.
         *
         * @param in_profileId Profile (player) ID.
         * @param in_authenticationType Associated authentication type.
         *
         * @return The JSON returned in the callback
         * {
         *    "status": 200,
         *    "data": {
         *        "externalId": "19e1c0cf-9a2d-4d5c-9a71-1b0f6asdfb4b"
         *    }
         * }
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
        *
        * @return The JSON returned in the callback
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
        *
        * @return The JSON returned in the callback
        */
        void readFriendsEntities(const char* in_entityType, IServerCallback * in_callback = NULL);

        /**
        * Use listFriends method instead - removal after June 21 2016
        */
        DEPRECATED void readFriendsWithApplication(bool in_includeSummaryData = false, IServerCallback * in_callback = NULL);

        /**
         * Read a friend's player state.
         *
         * Service Name - PlayerState
         * Service Operation - ReadFriendsPlayerState
         *
         * @param in_friendId Target friend
         * @param in_callback Method to be invoked when the server response is received.
         */
        void readFriendPlayerState(const char * in_friendId, IServerCallback * in_callback = NULL);

        /**
         * Finds a list of players matching the search text by performing a substring
         * search of all player names.
         * If the number of results exceeds maxResults the message
         * "Too many results to return." is received and no players are returned
         *
         * Service Name - Friend
         * Service Operation - FindPlayerByName
         *
         * @param in_searchText The substring to search for. Minimum length of 3 characters.
         * @param in_maxResults  Maximum number of results to return. If there are more the message
         *                       "Too many results to return." is sent back instead of the players.
         * @param in_callback Method to be invoked when the server response is received.
         *
         * @return The JSON returned in the callback is as follows:
         * {
         *     "status": 200,
         *     "data": {
         *         "matches": [
         *         {
         *             "profileId": "63d1fdbd-2971-4791-a248-f8cda1a79bba",
         *             "playerSummaryData": null,
         *             "profileName": "ABC"
         *         }
         *         ],
         *         "matchedCount": 1
         *     }
         * }
         */
        void findPlayerByName(const char * in_searchText, int32_t in_maxResults, IServerCallback * in_callback = NULL);

        /**
         * Retrieves a list of player and friend platform information for all friends of the current player.
         *
         * Service Name - Friend
         * Service Operation - LIST_FRIENDS
         *
         * @param in_friendPlatform Friend platform to query.
         * @param in_includeSummaryData  True if including summary data; false otherwise.
         * @param in_callback Method to be invoked when the server response is received.
         *
         * @return The JSON returned in the callback is as follows:
         * Example 1: for friendPlatform = All
         * {
         *     "status": 200,
         *     "data": {
         *         "friends": [{
         *             "externalData": {
         *                 "Facebook": {
         *                     "pictureUrl": "https://scontent.xx.fbcdn.net/hprofile-xfp1/v/t1.0-1/p50x50/XXX.jpg?oh=YYY&oe=ZZZ",
         *                     "name": "scientist at large",
         *                     "externalId": "100003668521730"
         *
         *                 },
         *                 "brainCloud": {}
         *             },
         *             "playerId": "1aa3428c-5877-4624-a909-f2b1af931f00",
         *             "name": "Mr. Peabody",
         *             "summaryFriendData": {
         *                 "LEVEL": -4
         *             }
         *         }, {
         *             "externalData": {
         *                 "Facebook": {
         *                     "pictureUrl": "https://scontent.xx.fbcdn.net/hprofile-xfa1/v/t1.0-1/c0.11.50.50/p50x50/3AAA.jpg?oh=BBBa&oe=CCC",
         *                     "name": "Aquaman",
         *                     "externalId": "100003509724516"
         *                 }
         *             },
         *             "playerId": "1598c5b6-1b09-431b-96bc-9c2c928cad3b",
         *             "name": null,
         *             "summaryFriendData": {
         *                 "LEVEL": 1
         *             }
         *         }],
         *         "server_time": 1458224807855
         *     }
         * }
         *
         * Example 2: for friendPlatform = Facebook
         * {
         *     "status": 200,
         *     "data": {
         *         "friends": [{
         *             "externalData": {
         *                 "Facebook": {
         *                     "pictureUrl": "https://scontent.xx.fbcdn.net/hprofile-xfp1/v/t1.0-1/p50x50/XXX.jpg?oh=YYY&oe=ZZZ",
         *                     "name": "scientist at large",
         *                     "externalId": "100003668521730"
         *                 }
         *             },
         *             "playerId": "1aa3428c-5877-4624-a909-f2b1af931f00",
         *             "name": "Mr. Peabody",
         *             "summaryFriendData": {
         *                 "LEVEL": -4
         *             }
         *         }, {
         *             "externalData": {
         *                 "Facebook": {
         *                     "pictureUrl": "https://scontent.xx.fbcdn.net/hprofile-xfa1/v/t1.0-1/c0.11.50.50/p50x50/3AAA.jpg?oh=BBBa&oe=CCC",
         *                     "name": "Aquaman",
         *                     "externalId": "100003509724516"
         *                 }
         *             },
         *             "playerId": "1598c5b6-1b09-431b-96bc-9c2c928cad3b",
         *             "name": null,
         *             "summaryFriendData": {
         *                 "LEVEL": 1
         *             }
         *         }],
         *         "server_time": 1458224807855
         *     }
         * }
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
         *
         * @return The JSON returned in the callback is as follows:
         * {
         *     "status": 200,
         *     "data": null
         * }
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
        *
        * @return The JSON returned in the callback is as follows:
        * {
        *     "status": 200,
        *     "data": null
        * }
        */
        void removeFriends(const std::vector<std::string>& in_profileIds, IServerCallback * in_callback = NULL);

    private:
        BrainCloudClient * m_client;
    };
}