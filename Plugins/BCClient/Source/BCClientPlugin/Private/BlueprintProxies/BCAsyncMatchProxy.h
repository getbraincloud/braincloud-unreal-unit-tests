// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCAsyncMatchProxy.generated.h"

UCLASS(MinimalAPI)
class UBCAsyncMatchProxy : public UBCBlueprintCallProxyBase
{
  GENERATED_BODY()

public:
  UBCAsyncMatchProxy(const FObjectInitializer &ObjectInitializer);

  /**
    * Creates an instance of an asynchronous match.
    *
    * Service Name - AsyncMatch
    * Service Operation - Create
    *
    * Param - jsonOpponentIds  JSON string identifying the opponent platform and id for this match.
    *
    * Platforms are identified as:
    * BC - a brainCloud profile id
    * FB - a Facebook id
    *
    * An example of this string would be:
    * [
    *     {
    *         "platform": "BC",
    *         "id": "some-braincloud-profile"
    *     },
    *     {
    *         "platform": "FB",
    *         "id": "some-facebook-id"
    *     }
    * ]
    *
    * Param - pushNotificationMessage Optional push notification message to send to the other party.
    *  Refer to the Push Notification functions for the syntax required.
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
  static UBCAsyncMatchProxy *CreateMatch(UBrainCloudWrapper *brainCloudWrapper, FString jsonOpponentIds, FString pushNotificationMessage);

  /**
    * Creates an instance of an asynchronous match with an initial turn.
    *
    * Service Name - AsyncMatch
    * Service Operation - Create
    *
    * Param - jsonOpponentIds  JSON string identifying the opponent platform and id for this match.
    *
    * Platforms are identified as:
    * BC - a brainCloud profile id
    * FB - a Facebook id
    *
    * An exmaple of this string would be:
    * [
    *     {
    *         "platform": "BC",
    *         "id": "some-braincloud-profile"
    *     },
    *     {
    *         "platform": "FB",
    *         "id": "some-facebook-id"
    *     }
    * ]
    *
    * Param - jsonMatchState    JSON string blob provided by the caller
    * Param - pushNotificationMessage Optional push notification message to send to the other party.
    * Refer to the Push Notification functions for the syntax required.
    * Param - nextPlayer Optionally, force the next player player to be a specific player
    * Param - jsonSummary Optional JSON string defining what the other player will see as a summary of the game when listing their games
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
  static UBCAsyncMatchProxy *CreateMatchWithInitialTurn(UBrainCloudWrapper *brainCloudWrapper, FString jsonOpponentIds, FString jsonMatchState,
                                                        FString pushNotificationMessage, FString nextPlayer, FString jsonSummary);

  /**
    * Submits a turn for the given match.
    *
    * Service Name - AsyncMatch
    * Service Operation - SubmitTurn
    *
    * Param - ownerId Match owner identfier
    * Param - matchId Match identifier
    * Param - version Game state version to ensure turns are submitted once and in order
    * Param - jsonMatchState JSON string provided by the caller
    * Param - pushNotificationMessage Optional push notification message to send to the other party.
    *  Refer to the Push Notification functions for the syntax required.
    * Param - nextPlayer Optionally, force the next player player to be a specific player
    * Param - jsonSummary Optional JSON string that other players will see as a summary of the game when listing their games
    * Param - jsonStatistics Optional JSON string blob provided by the caller
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
  static UBCAsyncMatchProxy *SubmitTurn(UBrainCloudWrapper *brainCloudWrapper, FString ownerId, FString matchId, int32 version, FString jsonMatchState, FString pushNotificationMessage,
                                        FString nextPlayer, FString jsonSummary, FString jsonStatistics);

  /**
    * Allows the current player (only) to update Summary data without having to submit a whole turn.
    *
    * Service Name - AsyncMatch
    * Service Operation - UpdateMatchSummary
    *
    * Param - ownerId Match owner identfier
    * Param - matchId Match identifier
    * Param - version Game state version to ensure turns are submitted once and in order
    * Param - jsonSummary JSON string that other players will see as a summary of the game when listing their games
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
  static UBCAsyncMatchProxy *UpdateMatchSummaryData(UBrainCloudWrapper *brainCloudWrapper, FString ownerId, FString matchId, int32 version, FString jsonSummary);

  /**
    * Marks the given match as complete.
    *
    * Service Name - AsyncMatch
    * Service Operation - Complete
    *
    * Param - ownerId Match owner identifier
    * Param - matchId Match identifier
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
  static UBCAsyncMatchProxy *CompleteMatch(UBrainCloudWrapper *brainCloudWrapper, FString ownerId, FString matchId);

  /**
    * Returns the current state of the given match.
    *
    * Service Name - AsyncMatch
    * Service Operation - ReadMatch
    *
    * Param - ownerId   Match owner identifier
    * Param - matchId   Match identifier
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
  static UBCAsyncMatchProxy *ReadMatch(UBrainCloudWrapper *brainCloudWrapper, FString ownerId, FString matchId);

  /**
    * Returns the match history of the given match.
    *
    * Service Name - AsyncMatch
    * Service Operation - ReadMatchHistory
    *
    * Param - ownerId   Match owner identifier
    * Param - matchId   Match identifier
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
  static UBCAsyncMatchProxy *ReadMatchHistory(UBrainCloudWrapper *brainCloudWrapper, FString ownerId, FString matchId);

  /**
    * Returns all matches that are NOT in a COMPLETE state for which the player is involved.
    *
    * Service Name - AsyncMatch
    * Service Operation - FindMatches
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
  static UBCAsyncMatchProxy *FindMatches(UBrainCloudWrapper *brainCloudWrapper);

  /**
    * Returns all matches that are in a COMPLETE state for which the player is involved.
    *
    * Service Name - AsyncMatch
    * Service Operation - FindMatchesCompleted
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
  static UBCAsyncMatchProxy *FindCompleteMatches(UBrainCloudWrapper *brainCloudWrapper);

  /**
    * Marks the given match as abandoned.
    *
    * Service Name - AsyncMatch
    * Service Operation - Abandon
    *
    * The JSON returned in the callback is as follows:
    * {
    *     "status": 200,
    *     "data": {}
    * }
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
  static UBCAsyncMatchProxy *AbandonMatch(UBrainCloudWrapper *brainCloudWrapper, FString ownerId, FString matchId);

  /**
    * Removes the match and match history from the server. DEBUG ONLY, in production it is recommended
    *   the user leave it as completed.
    *
    * Service Name - AsyncMatch
    * Service Operation - Delete
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
  static UBCAsyncMatchProxy *DeleteMatch(UBrainCloudWrapper *brainCloudWrapper, FString ownerId, FString matchId);

  /**
    * Marks the given match as abandoned. This call can send a notification message.
    *
    * Service Name - AsyncMatch
    * Service Operation - ABANDON_MATCH_WITH_SUMMARY_DATA
    *
    * @param ownerId   Match owner identifier
    * @param matchId   Match identifier
    * @param pushContent
    * @param summary
    * @param callback  Optional instance of IServerCallback to call when the server response is received.
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
  static UBCAsyncMatchProxy *AbandonMatchWithSummaryData(UBrainCloudWrapper *brainCloudWrapper, const FString &ownerId, const FString &matchId, const FString &pushContent, const FString &summary);
  /**
    * Marks the given match as complete. This call can send a notification message.
    * 
    * Service Name - AsyncMatch
    * Service Operation - COMPLETE_MATCH_WITH_SUMMARY_DATA
    *
    * @param ownerId   Match owner identifier
    * @param matchId   Match identifier
    * @param pushContent
    * @param summary
    * @param callback  Optional instance of IServerCallback to call when the server response is received.
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Async Match")
  static UBCAsyncMatchProxy *CompleteMatchWithSummaryData(UBrainCloudWrapper *brainCloudWrapper, const FString &ownerId, const FString &matchId, const FString &pushContent, const FString &summary);
};
