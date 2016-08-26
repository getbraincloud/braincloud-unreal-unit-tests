// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BCPlayerStateProxy.generated.h"

UCLASS(MinimalAPI)
class UBCPlayerStateProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
    GENERATED_BODY()

public:
    UBCPlayerStateProxy(const FObjectInitializer& ObjectInitializer);

    /**
    * Read the state of the currently logged in player.
    * This method returns a JSON object describing most of the
    * player's data: entities, statistics, level, currency.
    * Apps will typically call this method after authenticating to get an
    * up-to-date view of the player's data.
    *
    * Service Name - PlayerState
    * Service Operation - Read
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
        static UBCPlayerStateProxy* ReadPlayerState();

    /**
    * Completely deletes the player record and all data fully owned
    * by the player. After calling this method, the player will need
    * to re-authenticate and create a new profile.
    * This is mostly used for debugging/qa.
    *
    * Service Name - PlayerState
    * Service Operation - FullReset
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
        static UBCPlayerStateProxy* DeletePlayer();

    /**
    * This method will delete *most* data for the currently logged in player.
    * Data which is not deleted includes: currency, credentials, and
    * purchase transactions. ResetPlayer is different from DeletePlayer in that
    * the player record will continue to exist after the reset (so the user
    * does not need to re-authenticate).
    *
    * Service Name - PlayerState
    * Service Operation - DataReset
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
        static UBCPlayerStateProxy* ResetPlayerState();

    /**
    * Logs player out of server.
    *
    * Service Name - PlayerState
    * Service Operation - Logout
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
        static UBCPlayerStateProxy* Logout();

    /**
    * Sets the players name.
    *
    * Service Name - playerState
    * Service Operation - UPDATE_NAME
    *
    * Param - playerName The name of the player
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
        static UBCPlayerStateProxy* UpdatePlayerName(FString playerName);

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
    * Param - jsonSummaryData A JSON string defining the summary data.
    * For example:
    * {
    *   "xp":123,
    *   "level":12,
    *   "highScore":45123
    * }
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
        static UBCPlayerStateProxy* UpdateSummaryFriendData(const FString& jsonSummaryData);

    /**
    * Retrieve the player attributes.
    *
    * Service Name - PlayerState
    * Service Operation - GetAttributes
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
        static UBCPlayerStateProxy* GetAttributes();

    /**
    * Update player attributes.
    *
    * Service Name - PlayerState
    * Service Operation - UpdateAttributes
    *
    * Param - jsonAttributes Single layer json string that is a set of key-value pairs
    * Param - wipeExisting Whether to wipe existing attributes prior to update.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
        static UBCPlayerStateProxy* UpdateAttributes(FString jsonAttributes, bool wipeExisting);

    /**
    * Remove player attributes.
    *
    * Service Name - PlayerState
    * Service Operation - RemoveAttributes
    *
    * Param - attributeNames Array of attribute names.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
        static UBCPlayerStateProxy* RemoveAttributes(const TArray<FString>& attributeNames);

    /**
    * Update Player picture URL.
    *
    * Service Name - PlayerState
    * Service Operation - UPDATE_PICTURE_URL
    *
    * Param - pictureUrl URL to apply
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
        static UBCPlayerStateProxy* UpdatePlayerPictureUrl(const FString& pictureUrl);

    /**
    * Update the player's contact email.
    * Note this is unrelated to email authentication.
    *
    * Service Name - PlayerState
    * Service Operation - UPDATE_CONTACT_EMAIL
    *
    * Param - contactEmail Updated email
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
        static UBCPlayerStateProxy* UpdateContactEmail(const FString& contactEmail);

    //Response delegates
    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnFailure;

protected:
    // IServerCallback interface
    void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
    void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
    // End of IServerCallback interface
};
