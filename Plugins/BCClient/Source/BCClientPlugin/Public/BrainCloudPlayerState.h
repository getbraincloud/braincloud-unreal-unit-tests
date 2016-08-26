// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudPlayerState
{
    friend class BrainCloudComms;
    friend class BrainCloudComms2;

public:
    BrainCloudPlayerState(BrainCloudClient* client);

    /**
     * Read the state of the currently logged in player.
     * This method returns a JSON object describing most of the
     * player's data: entities, statistics, level, currency.
     * Apps will typically call this method after authenticating to get an
     * up-to-date view of the player's data.
     *
     * Service Name - PlayerState
     * Service Operation - Read
     *
     * @param callback The method to be invoked when the server response is received
     */
    void readPlayerState(IServerCallback * callback, const FString& entityTypeFilter = TEXT(""));

    /**
     * Completely deletes the player record and all data fully owned
     * by the player. After calling this method, the player will need
     * to re-authenticate and create a new profile.
     * This is mostly used for debugging/qa.
     *
     * Service Name - PlayerState
     * Service Operation - FullReset
     *
     * @param callback The method to be invoked when the server response is received
     */
    void deletePlayer(IServerCallback * callback);

    /**
     * This method will delete *most* data for the currently logged in player.
     * Data which is not deleted includes: currency, credentials, and
     * purchase transactions. ResetPlayer is different from DeletePlayer in that
     * the player record will continue to exist after the reset (so the user
     * does not need to re-authenticate).
     *
     * Service Name - PlayerState
     * Service Operation - DataReset
     *
     * @param callback The method to be invoked when the server response is received
     */
    void resetPlayerState(IServerCallback * callback);

    /**
     * Logs player out of server.
     *
     * Service Name - PlayerState
     * Service Operation - Logout
     *
     * @param callback The method to be invoked when the server response is received
     */
    void logout(IServerCallback * callback);

    /**
    * Sets the players name.
    *
    * Service Name - playerState
    * Service Operation - UPDATE_NAME
    *
    * @param playerName The name of the player
    * @param callback The method to be invoked when the server response is received
    */
    void updatePlayerName(const FString& playerName, IServerCallback * callback);

    /**
    * Updates the "friend summary data" associated with the logged in player.
    * Some operations will return this summary data. For instance the social
    * leaderboards will return the player's score in the leaderboard along
    * with the friend summary data. Generally this data is used to provide
    * a quick overview of the player without requiring a separate API call
    * to read their public stats or entity data.
    *
    * Service Name - PlayerState
    * Service Operation - UpdateSummary
    *
    * @param jsonSummaryData A JSON string defining the summary data.
    * For example:
    * {
    *   "xp":123,
    *   "level":12,
    *   "highScore":45123
    * }
    * @param callback Method to be invoked when the server response is received.
    */
    void updateSummaryFriendData(const FString& jsonSummaryData, IServerCallback * callback);

    /**
    * Retrieve the player attributes.
    *
    * Service Name - PlayerState
    * Service Operation - GetAttributes
    *
    * @param callback The method to be invoked when the server response is received
    */
    void getAttributes(IServerCallback * callback);

    /**
    * Update player attributes.
    *
    * Service Name - PlayerState
    * Service Operation - UpdateAttributes
    *
    * @param jsonAttributes Single layer json string that is a set of key-value pairs
    * @param wipeExisting Whether to wipe existing attributes prior to update.
    * @param callback The method to be invoked when the server response is received
    */
    void updateAttributes(const FString& jsonAttributes, bool wipeExisting, IServerCallback * callback);

    /**
    * Remove player attributes.
    *
    * Service Name - PlayerState
    * Service Operation - RemoveAttributes
    *
    * @param attributeNames Array of attribute names.
    * @param callback The method to be invoked when the server response is received
    */
    void removeAttributes(const TArray<FString>& attributeNames, IServerCallback * callback);

    /**
    * Update Player picture URL.
    *
    * Service Name - PlayerState
    * Service Operation - UPDATE_PICTURE_URL
    *
    * @param pictureUrl URL to apply
    * @param callback The method to be invoked when the server response is received
    */
    void updatePlayerPictureUrl(const FString& pictureUrl, IServerCallback * callback);

    /**
    * Update the player's contact email.
    * Note this is unrelated to email authentication.
    *
    * Service Name - PlayerState
    * Service Operation - UPDATE_CONTACT_EMAIL
    *
    * @param contactEmail Updated email
    * @param callback The method to be invoked when the server response is received
    */
    void updateContactEmail(const FString& contactEmail, IServerCallback * callback);

    /**
    * Gets a cached value of the currently authenticated player's name
    * @returns The cached currently authenticated player's name
    */
    const FString& getPlayerName();

protected:
    void setPlayerName(const FString& name);

private:
    BrainCloudClient* _client = nullptr;
    FString _playerName = "";
};
