// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <string>
#include <vector>
#include "braincloud/BrainCloudTypes.h"

namespace BrainCloud
{
    class IServerCallback;
    class BrainCloudClient;

    class BrainCloudPlayerState
    {
    public:
        BrainCloudPlayerState(BrainCloudClient* in_client);


        /**
		* @deprecated Use readUserState() instead - Removal after September 1 2017
		*/
        DEPRECATED
        void readPlayerState(IServerCallback * in_callback, const char* in_entityTypeFilter = NULL);


        /**
         * Read the state of the currently logged in user.
         * This method returns a JSON object describing most of the
         * user's data: entities, statistics, level, currency.
         * Apps will typically call this method after authenticating to get an
         * up-to-date view of the user's data.
         *
         * Service Name - PlayerState
         * Service Operation - Read
         *
         * @param in_callback The method to be invoked when the server response is received
         */
        void readUserState(IServerCallback *in_callback, const char *in_entityTypeFilter = NULL);

        /**
		* @deprecated Use deleteUser() instead - Removal after September 1 2017
		*/
        DEPRECATED
        void deletePlayer(IServerCallback *in_callback = NULL);

        /**
         * Completely deletes the user record and all data fully owned
         * by the user. After calling this method, the user will need
         * to re-authenticate and create a new profile.
         * This is mostly used for debugging/qa.
         *
         * Service Name - PlayerState
         * Service Operation - FullReset
         *
         * @param in_callback The method to be invoked when the server response is received
         */
        void deleteUser(IServerCallback *in_callback = NULL);

        /**
		* @deprecated Use resetUserState() instead - Removal after September 1 2017
		*/
        DEPRECATED
        void resetPlayerState(IServerCallback * in_callback = NULL);

        /**
         * This method will delete *most* data for the currently logged in user.
         * Data which is not deleted includes: currency, credentials, and
         * purchase transactions. ResetUser is different from DeleteUser in that
         * the user record will continue to exist after the reset (so the user
         * does not need to re-authenticate).
         *
         * Service Name - PlayerState
         * Service Operation - DataReset
         *
         * @param in_callback The method to be invoked when the server response is received
         */
        void resetUserState(IServerCallback *in_callback = NULL);

        /**
         * Logs user out of server.
         *
         * Service Name - PlayerState
         * Service Operation - Logout
         *
         * @param in_callback The method to be invoked when the server response is received
         */
        void logout(IServerCallback * in_callback = NULL);

        /**
		* @deprecated Use updateUserName() instead - Removal after September 1 2017
		*/
        DEPRECATED
        void updatePlayerName(const char * in_userName, IServerCallback * in_callback = NULL);

        /**
        * Sets the user's name.
        *
        * Service Name - playerState
        * Service Operation - UPDATE_NAME
        *
        * @param in_userName The name of the user
        * @param in_callback The method to be invoked when the server response is received
        */
        void updateUserName(const char *in_userName, IServerCallback *in_callback = NULL);

        /**
         * Updates the "friend summary data" associated with the logged in user.
         * Some operations will return this summary data. For instance the social
         * leaderboards will return the player's score in the leaderboard along
         * with the friend summary data. Generally this data is used to provide
         * a quick overview of the player without requiring a separate API call
         * to read their public stats or entity data.
         *
         * Service Name - PlayerState
         * Service Operation - UpdateSummary
         *
         * @param in_jsonSummaryData A JSON string defining the summary data.
         * For example:
         * {
         *   "xp":123,
         *   "level":12,
         *   "highScore":45123
         * }
         * @param in_callback Method to be invoked when the server response is received.
         */
        void updateSummaryFriendData(const char * in_jsonSummaryData, IServerCallback * in_callback = NULL);

        /**
        * Retrieve the user's attributes.
        *
        * Service Name - PlayerState
        * Service Operation - GetAttributes
        *
        * @param in_callback The method to be invoked when the server response is received
        */
        void getAttributes(IServerCallback * in_callback = NULL);

        /**
        * Update user's attributes.
        *
        * Service Name - PlayerState
        * Service Operation - UpdateAttributes
        *
        * @param in_jsonAttributes Single layer json string that is a set of key-value pairs
        * @param in_wipeExisting Whether to wipe existing attributes prior to update.
        * @param in_callback The method to be invoked when the server response is received
        */
        void updateAttributes(const std::string& in_jsonAttributes, bool in_wipeExisting, IServerCallback * in_callback = NULL);

        /**
        * Remove user's attributes.
        *
        * Service Name - PlayerState
        * Service Operation - RemoveAttributes
        *
        * @param in_attributeNames Collection of attribute names.
        * @param in_callback The method to be invoked when the server response is received
        */
        void removeAttributes(const std::vector<std::string> & in_attributeNames, IServerCallback * in_callback = NULL);

        /**
		* @deprecated Use updateUserPictureUrl() instead - Removal after September 1 2017
		*/
        DEPRECATED
        void updatePlayerPictureUrl(const char * in_pictureUrl, IServerCallback * in_callback = NULL);

        /**
         * Update User picture URL.
         *
         * Service Name - PlayerState
         * Service Operation - UPDATE_PICTURE_URL
         *
         * @param in_pictureUrl URL to apply
         * @param in_callback The method to be invoked when the server response is received
         */
        void updateUserPictureUrl(const char *in_pictureUrl, IServerCallback *in_callback = NULL);

        /**
         * Update the user's contact email.
         * Note this is unrelated to email authentication.
         *
         * Service Name - PlayerState
         * Service Operation - UPDATE_CONTACT_EMAIL
         *
         * @param in_contactEmail Updated email
         * @param in_callback The method to be invoked when the server response is received
         */
        void updateContactEmail(const char * in_contactEmail, IServerCallback * in_callback = NULL);

    private:
        BrainCloudClient * m_client;
    };
}