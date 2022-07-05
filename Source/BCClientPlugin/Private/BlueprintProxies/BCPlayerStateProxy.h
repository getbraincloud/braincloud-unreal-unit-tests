// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCPlayerStateProxy.generated.h"

UCLASS(MinimalAPI)
class UBCPlayerStateProxy : public UBCBlueprintCallProxyBase
{
    GENERATED_BODY()

  public:
    UBCPlayerStateProxy(const FObjectInitializer &ObjectInitializer);

    /**
    * Read the state of the currently logged in user.
    * This method returns a JSON object describing most of the
    * user's data: entities, statistics, level, currency.
    * Apps will typically call this method after authenticating to get an
    * up-to-date view of the user's data.
    *
    * Service Name - PlayerState
    * Service Operation - Read
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
    static UBCPlayerStateProxy *ReadUserState(UBrainCloudWrapper *brainCloudWrapper);

    /**
    * Completely deletes the user record and all data fully owned
    * by the user. After calling this method, the user will need
    * to re-authenticate and create a new profile.
    * This is mostly used for debugging/qa.
    *
    * Service Name - PlayerState
    * Service Operation - FullReset
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
    static UBCPlayerStateProxy *DeleteUser(UBrainCloudWrapper *brainCloudWrapper);

    /**
    * This method will delete *most* data for the currently logged in user.
    * Data which is not deleted includes: currency, credentials, and
    * purchase transactions. ResetUser is different from DeleteUser in that
    * the user record will continue to exist after the reset (so the user
    * does not need to re-authenticate).
    *
    * Service Name - PlayerState
    * Service Operation - DataReset
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
    static UBCPlayerStateProxy *ResetUserState(UBrainCloudWrapper *brainCloudWrapper);

    /**
    * Logs user out of server.
    *
    * Service Name - PlayerState
    * Service Operation - Logout
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
    static UBCPlayerStateProxy *Logout(UBrainCloudWrapper *brainCloudWrapper);

    /**
    * Sets the user's name.
    *
    * Service Name - playerState
    * Service Operation - UPDATE_NAME
    *
    * Param - name The name of the user
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
    static UBCPlayerStateProxy *UpdateUserName(UBrainCloudWrapper *brainCloudWrapper, FString userName);

    /**
    * @deprecated Use updateUserName instead - to be removed September 2021
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
    static UBCPlayerStateProxy *UpdateName(UBrainCloudWrapper *brainCloudWrapper, FString name);

    /**
    * Updates the "friend summary data" associated with the logged in player.
    * Some operations will return this summary data. For instance the social
    * leaderboards will return the user's score in the leaderboard along
    * with the friend summary data. Generally this data is used to provide
    * a quick overview of the user without requiring a separate API call
    * to read their public stats or entity data.
    *
    * Service Name - PlayerState
    * Service Operation - UpdateSummary
    *
    * Param - jsonSummaryData A JSON string defining the summary data.
    * For example:
    * {
    *   "xp":123,
    *   "level":12,
    *   "highScore":45123
    * }
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
    static UBCPlayerStateProxy *UpdateSummaryFriendData(UBrainCloudWrapper *brainCloudWrapper, const FString &jsonSummaryData);

    /**
    * Retrieve the user's attributes.
    *
    * Service Name - PlayerState
    * Service Operation - GetAttributes
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
    static UBCPlayerStateProxy *GetAttributes(UBrainCloudWrapper *brainCloudWrapper);

    /**
    * Update user's attributes.
    *
    * Service Name - PlayerState
    * Service Operation - UpdateAttributes
    *
    * Param - jsonAttributes Single layer json string that is a set of key-value pairs
    * Param - wipeExisting Whether to wipe existing attributes prior to update.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
    static UBCPlayerStateProxy *UpdateAttributes(UBrainCloudWrapper *brainCloudWrapper, FString jsonAttributes, bool wipeExisting);

    /**
    * Remove user's attributes.
    *
    * Service Name - PlayerState
    * Service Operation - RemoveAttributes
    *
    * Param - attributeNames Array of attribute names.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
    static UBCPlayerStateProxy *RemoveAttributes(UBrainCloudWrapper *brainCloudWrapper, const TArray<FString> &attributeNames);

    /**
    * Update user picture URL.
    *
    * Service Name - PlayerState
    * Service Operation - UPDATE_PICTURE_URL
    *
    * Param - pictureUrl URL to apply
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
    static UBCPlayerStateProxy *UpdateUserPictureUrl(UBrainCloudWrapper *brainCloudWrapper, const FString &pictureUrl);

    /**
    * Update the user's contact email.
    * Note this is unrelated to email authentication.
    *
    * Service Name - PlayerState
    * Service Operation - UPDATE_CONTACT_EMAIL
    *
    * Param - contactEmail Updated email
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
    static UBCPlayerStateProxy *UpdateContactEmail(UBrainCloudWrapper *brainCloudWrapper, const FString &contactEmail);

    /**
    * Delete's the specified status
    *
    * Service Name - PlayerState
    * Service Operation - CLEAR_USER_STATUS
    *
    * @param statusName a status name of the user
    * @param callback The method to be invoked when the server response is received
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
    static UBCPlayerStateProxy *ClearUserStatus(UBrainCloudWrapper *brainCloudWrapper, const FString &statusName);

    /**
    * Stack user's statuses
    *
    * Service Name - PlayerState
    * Service Operation - EXTEND_USER_STATUS
    *
    * @param statusName a status name of the user
    * @param additionalSecs time
    * @param details json of details of user status
    * @param callback The method to be invoked when the server response is received
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
    static UBCPlayerStateProxy *ExtendUserStatus(UBrainCloudWrapper *brainCloudWrapper, const FString &statusName, int additionalSecs, const FString &details);

    /**
    * Get user status
    *
    * Service Name - PlayerState
    * Service Operation - GET_USER_STATUS
    *
    * @param statusName a status name of the user
    * @param callback The method to be invoked when the server response is received
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
    static UBCPlayerStateProxy *GetUserStatus(UBrainCloudWrapper *brainCloudWrapper, const FString &statusName);

    /**
    * Get user status
    *
    * Service Name - PlayerState
    * Service Operation - GET_USER_STATUS
    *
    * @param statusName a status name of the user
    * @param durationSecs the time
    * @param details the user details
    * @param callback The method to be invoked when the server response is received
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
    static UBCPlayerStateProxy *SetUserStatus(UBrainCloudWrapper *brainCloudWrapper, const FString &statusName, int durationSecs, const FString &details);

    /**
    * Update user's time zone offset preference on their profile
    *
    * Service Name - PlayerState
    * Service Operation - UPDATE_TIMEZONE_OFFSET
    *
    * @param timeZoneOffset the offset
    * @param callback The method to be invoked when the server response is received
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
    static UBCPlayerStateProxy *UpdateTimeZoneOffset(UBrainCloudWrapper *brainCloudWrapper, int32 timeZoneOffset);

    /**
    * Update user's language code preference on their profile.
    *
    * Service Name - PlayerState
    * Service Operation - UPDATE_LANGUAGE_CODE
    *
    * @param languageCode the offset
    * @param callback The method to be invoked when the server response is received
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
    static UBCPlayerStateProxy *UpdateLanguageCode(UBrainCloudWrapper *brainCloudWrapper, const FString &languageCode);

};
