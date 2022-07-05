// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudAsyncMatch
{
public:
  BrainCloudAsyncMatch(BrainCloudClient *client);

  /**
    * Creates an instance of an asynchronous match.
    *
    * Service Name - AsyncMatch
    * Service Operation - Create
    *
    * @param jsonOpponentIds  JSON string identifying the opponent platform and id for this match.
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
    * @param pushNotificationMessage Optional push notification message to send to the other party.
    *  Refer to the Push Notification functions for the syntax required.
    * @param callback Optional instance of IServerCallback to call when the server response is received.
    */
  void createMatch(const FString &jsonOpponentIds, const FString &pushNotificationMessage, IServerCallback *callback);

  /**
    * Creates an instance of an asynchronous match with an initial turn.
    *
    * Service Name - AsyncMatch
    * Service Operation - Create
    *
    * @param jsonOpponentIds  JSON string identifying the opponent platform and id for this match.
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
    * @param jsonMatchState    JSON string blob provided by the caller
    * @param pushNotificationMessage Optional push notification message to send to the other party.
    * Refer to the Push Notification functions for the syntax required.
    * @param nextPlayer Optionally, force the next player player to be a specific player
    * @param jsonSummary Optional JSON string defining what the other player will see as a summary of the game when listing their games
    * @param callback Optional instance of IServerCallback to call when the server response is received.
    */
  void createMatchWithInitialTurn(
      const FString &jsonOpponentIds,
      const FString &jsonMatchState,
      const FString &pushNotificationMessage,
      const FString &nextPlayer,
      const FString &jsonSummary,
      IServerCallback *callback);

  /**
    * Submits a turn for the given match.
    *
    * Service Name - AsyncMatch
    * Service Operation - SubmitTurn
    *
    * @param ownerId Match owner identfier
    * @param matchId Match identifier
    * @param version Game state version to ensure turns are submitted once and in order
    * @param jsonMatchState JSON string provided by the caller
    * @param pushNotificationMessage Optional push notification message to send to the other party.
    *  Refer to the Push Notification functions for the syntax required.
    * @param nextPlayer Optionally, force the next player player to be a specific player
    * @param jsonSummary Optional JSON string that other players will see as a summary of the game when listing their games
    * @param jsonStatistics Optional JSON string blob provided by the caller
    * @param callback Optional instance of IServerCallback to call when the server response is received.
    */
  void submitTurn(const FString &ownerId,
                  const FString &matchId,
                  uint64 version,
                  const FString &jsonMatchState,
                  const FString &pushNotificationMessage,
                  const FString &nextPlayer,
                  const FString &jsonSummary,
                  const FString &jsonStatistics,
                  IServerCallback *callback);

  /**
    * Allows the current player (only) to update Summary data without having to submit a whole turn.
    *
    * Service Name - AsyncMatch
    * Service Operation - UpdateMatchSummary
    *
    * @param ownerId Match owner identfier
    * @param matchId Match identifier
    * @param version Game state version to ensure turns are submitted once and in order
    * @param jsonSummary JSON string that other players will see as a summary of the game when listing their games
    * @param callback Optional instance of IServerCallback to call when the server response is received.
    */
  void updateMatchSummaryData(const FString &ownerId, const FString &matchId, uint64 version, const FString &jsonSummary, IServerCallback *callback);

  /**
    * Marks the given match as complete.
    *
    * Service Name - AsyncMatch
    * Service Operation - Complete
    *
    * @param ownerId Match owner identifier
    * @param matchId Match identifier
    * @param callback Optional instance of IServerCallback to call when the server response is received.
    */
  void completeMatch(const FString &ownerId, const FString &matchId, IServerCallback *callback);

  /**
    * Returns the current state of the given match.
    *
    * Service Name - AsyncMatch
    * Service Operation - ReadMatch
    *
    * @param ownerId   Match owner identifier
    * @param matchId   Match identifier
    * @param callback  Optional instance of IServerCallback to call when the server response is received.
    */
  void readMatch(const FString &ownerId, const FString &matchId, IServerCallback *callback);

  /**
    * Returns the match history of the given match.
    *
    * Service Name - AsyncMatch
    * Service Operation - ReadMatchHistory
    *
    * @param ownerId   Match owner identifier
    * @param matchId   Match identifier
    * @param callback  Optional instance of IServerCallback to call when the server response is received.
    */
  void readMatchHistory(const FString &ownerId, const FString &matchId, IServerCallback *callback);

  /**
    * Returns all matches that are NOT in a COMPLETE state for which the player is involved.
    *
    * Service Name - AsyncMatch
    * Service Operation - FindMatches
    *
    * @param callback  Optional instance of IServerCallback to call when the server response is received.
    */
  void findMatches(IServerCallback *callback);

  /**
    * Returns all matches that are in a COMPLETE state for which the player is involved.
    *
    * Service Name - AsyncMatch
    * Service Operation - FindMatchesCompleted
    *
    * @param callback  Optional instance of IServerCallback to call when the server response is received.
    */
  void findCompleteMatches(IServerCallback *callback);

  /**
    * Marks the given match as abandoned.
    *
    * Service Name - AsyncMatch
    * Service Operation - Abandon
    *
    * @param ownerId   Match owner identifier
    * @param matchId   Match identifier
    * @param callback  Optional instance of IServerCallback to call when the server response is received.
    */
  void abandonMatch(const FString &ownerId, const FString &matchId, IServerCallback *callback);

  /**
    * Removes the match and match history from the server. DEBUG ONLY, in production it is recommended
    *   the user leave it as completed.
    *
    * Service Name - AsyncMatch
    * Service Operation - Delete
    *
    * @param ownerId   Match owner identifier
    * @param matchId   Match identifier
    * @param callback  Optional instance of IServerCallback to call when the server response is received.
    */
  void deleteMatch(const FString &ownerId, const FString &matchId, IServerCallback *callback);

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
  void abandonMatchWithSummaryData(const FString &ownerId, const FString &matchId, const FString &pushContent, const FString &summary, IServerCallback *callback);
  
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
  void completeMatchWithSummaryData(const FString &ownerId, const FString &matchId, const FString &pushContent, const FString &summary, IServerCallback *callback);

private:
  BrainCloudClient *_client = nullptr;
};
