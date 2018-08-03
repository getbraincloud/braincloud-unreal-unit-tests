// Copyright 2018 bitHeads, Inc. All Rights Reserved.

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
	* @deprecated Use readUserState instead - removal after September 1 2017
	*/
	void readPlayerState(IServerCallback * callback, const FString& entityTypeFilter = TEXT(""));

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
     * @param callback The method to be invoked when the server response is received
     */
    void readUserState(IServerCallback * callback, const FString& entityTypeFilter = TEXT(""));

	/**
	* @deprecated Use deleteUser instead - removal after September 1 2017
	*/
	void deletePlayer(IServerCallback * callback);

    /**
     * Completely deletes the user record and all data fully owned
     * by the user. After calling this method, the user will need
     * to re-authenticate and create a new profile.
     * This is mostly used for debugging/qa.
     *
     * Service Name - PlayerState
     * Service Operation - FullReset
     *
     * @param callback The method to be invoked when the server response is received
     */
    void deleteUser(IServerCallback * callback);

	/**
	* @deprecated Use resetUserState instead - removal after September 1 2017
	*/
	void resetPlayerState(IServerCallback * callback);

    /**
     * This method will delete *most* data for the currently logged in user.
     * Data which is not deleted includes: currency, credentials, and
     * purchase transactions. ResetPlayer is different from DeleteUser in that
     * the user record will continue to exist after the reset (so the user
     * does not need to re-authenticate).
     *
     * Service Name - PlayerState
     * Service Operation - DataReset
     *
     * @param callback The method to be invoked when the server response is received
     */
    void resetUserState(IServerCallback * callback);

    /**
     * Logs user out of server.
     *
     * Service Name - PlayerState
     * Service Operation - Logout
     *
     * @param callback The method to be invoked when the server response is received
     */
    void logout(IServerCallback * callback);

	/**
	* @deprecated Use updateUserName instead - removal after September 1 2017
	*/
	void updatePlayerName(const FString& name, IServerCallback * callback);

    /**
	* @deprecated Use updateUserName instead
	*/
	void updateUserName(const FString& name, IServerCallback * callback);

    /**
    * Sets the user's name.
    *
    * Service Name - playerState
    * Service Operation - UPDATE_NAME
    *
    * @param name The name of the user
    * @param callback The method to be invoked when the server response is received
    */
    void updateName(const FString& name, IServerCallback * callback);

    /**
    * Updates the "friend summary data" associated with the logged in user.
    * Some operations will return this summary data. For instance the social
    * leaderboards will return the user's score in the leaderboard along
    * with the friend summary data. Generally this data is used to provide
    * a quick overview of the user without requiring a separate API call
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
    * Retrieve the user's attributes.
    *
    * Service Name - PlayerState
    * Service Operation - GetAttributes
    *
    * @param callback The method to be invoked when the server response is received
    */
    void getAttributes(IServerCallback * callback);

    /**
    * Update user's attributes.
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
    * Remove user's attributes.
    *
    * Service Name - PlayerState
    * Service Operation - RemoveAttributes
    *
    * @param attributeNames Array of attribute names.
    * @param callback The method to be invoked when the server response is received
    */
    void removeAttributes(const TArray<FString>& attributeNames, IServerCallback * callback);

	/**
	* @deprecated Use updateUserPictureUrl instead - removal after September 1 2017
	*/
	void updatePlayerPictureUrl(const FString& pictureUrl, IServerCallback * callback);

    /**
    * Update user's picture URL.
    *
    * Service Name - PlayerState
    * Service Operation - UPDATE_PICTURE_URL
    *
    * @param pictureUrl URL to apply
    * @param callback The method to be invoked when the server response is received
    */
    void updateUserPictureUrl(const FString& pictureUrl, IServerCallback * callback);

    /**
    * Update the user's contact email.
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
	* @deprecated Use getUserName instead - removal after September 1 2017
	*/
	const FString& getPlayerName();

    /**
    * Gets a cached value of the currently authenticated user's name
    * @returns The cached currently authenticated user's name
    */
    const FString& getUserName();

protected:
    void setUserName(const FString& name);

private:
    BrainCloudClient* _client = nullptr;
    FString _userName = "";
};
