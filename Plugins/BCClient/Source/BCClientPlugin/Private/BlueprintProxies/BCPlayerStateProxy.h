// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BCPlayerStateProxy.generated.h"

class ABrainCloud;

UCLASS(MinimalAPI)
class UBCPlayerStateProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
    GENERATED_BODY()

public:
    UBCPlayerStateProxy(const FObjectInitializer& ObjectInitializer);

	/**
	* @deprecated Use findUserByUniversalId instead
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
		static UBCPlayerStateProxy* ReadPlayerState(ABrainCloud *brainCloud);

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
        static UBCPlayerStateProxy* ReadUserState(ABrainCloud *brainCloud);

	/**
	* @deprecated Use DeleteUser instead
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
		static UBCPlayerStateProxy* DeletePlayer(ABrainCloud *brainCloud);

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
        static UBCPlayerStateProxy* DeleteUser(ABrainCloud *brainCloud);

	/**
	* @deprecated Use ResetUserState instead
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
		static UBCPlayerStateProxy* ResetPlayerState(ABrainCloud *brainCloud);

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
        static UBCPlayerStateProxy* ResetUserState(ABrainCloud *brainCloud);

    /**
    * Logs user out of server.
    *
    * Service Name - PlayerState
    * Service Operation - Logout
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
        static UBCPlayerStateProxy* Logout(ABrainCloud *brainCloud);

	/**
	* @deprecated Use UpdateName instead
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
		static UBCPlayerStateProxy* UpdatePlayerName(ABrainCloud *brainCloud, FString playerName);


	/**
	* @deprecated Use UpdateName instead
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
        static UBCPlayerStateProxy* UpdateUserName(ABrainCloud *brainCloud, FString userName);

    /**
    * Sets the user's name.
    *
    * Service Name - playerState
    * Service Operation - UPDATE_NAME
    *
    * Param - name The name of the user
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
        static UBCPlayerStateProxy* UpdateName(ABrainCloud *brainCloud, FString name);

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
        static UBCPlayerStateProxy* UpdateSummaryFriendData(ABrainCloud *brainCloud, const FString& jsonSummaryData);

    /**
    * Retrieve the user's attributes.
    *
    * Service Name - PlayerState
    * Service Operation - GetAttributes
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
        static UBCPlayerStateProxy* GetAttributes(ABrainCloud *brainCloud);

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
        static UBCPlayerStateProxy* UpdateAttributes(ABrainCloud *brainCloud, FString jsonAttributes, bool wipeExisting);

    /**
    * Remove user's attributes.
    *
    * Service Name - PlayerState
    * Service Operation - RemoveAttributes
    *
    * Param - attributeNames Array of attribute names.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
        static UBCPlayerStateProxy* RemoveAttributes(ABrainCloud *brainCloud, const TArray<FString>& attributeNames);

	/**
	* @deprecated Use UpdateUserPictureUrl instead
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
		static UBCPlayerStateProxy* UpdatePlayerPictureUrl(ABrainCloud *brainCloud, const FString& pictureUrl);

    /**
    * Update user picture URL.
    *
    * Service Name - PlayerState
    * Service Operation - UPDATE_PICTURE_URL
    *
    * Param - pictureUrl URL to apply
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Player State")
        static UBCPlayerStateProxy* UpdateUserPictureUrl(ABrainCloud *brainCloud, const FString& pictureUrl);

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
        static UBCPlayerStateProxy* UpdateContactEmail(ABrainCloud *brainCloud, const FString& contactEmail);

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
