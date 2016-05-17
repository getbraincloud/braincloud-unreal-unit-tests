// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "braincloud/BrainCloudTypes.h"
#include <string>

namespace BrainCloud {

    class IServerCallback;
    class BrainCloudClient;
    
    class BrainCloudAsyncMatch {    
    public:
        BrainCloudAsyncMatch(BrainCloudClient* in_client);

        /**
         * Creates an instance of an asynchronous match.
         *
         * Service Name - AsyncMatch
         * Service Operation - Create
         *
         * @param in_jsonOpponentIds  JSON string identifying the opponent platform and id for this match.
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
         * @param in_pushNotificationMessage Optional push notification message to send to the other party.
         *  Refer to the Push Notification functions for the syntax required.
         * @param in_callback Optional instance of IServerCallback to call when the server response is received.
         */
        void createMatch(
            const char * in_jsonOpponentIds,
            const char * in_pushNotificationMessage = NULL,
            IServerCallback * in_callback = NULL );
        
        // Removal after May 10 2016 - Use method without in_matchId instead
        DEPRECATED void createMatch(
            const char * in_jsonOpponentIds,
            const char * in_pushNotificationMessage = NULL,
            const char * in_matchId = NULL,
            IServerCallback * in_callback = NULL );
    
        /**
         * Creates an instance of an asynchronous match with an initial turn.
         *
         * Service Name - AsyncMatch
         * Service Operation - Create
         *
         * @param in_jsonOpponentIds  JSON string identifying the opponent platform and id for this match.
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
         * @param in_jsonMatchState    JSON string blob provided by the caller
         * @param in_pushNotificationMessage Optional push notification message to send to the other party.
         * Refer to the Push Notification functions for the syntax required.
         * @param in_nextPlayer Optionally, force the next player player to be a specific player
         * @param in_jsonSummary Optional JSON string defining what the other player will see as a summary of the game when listing their games
         * @param in_callback Optional instance of IServerCallback to call when the server response is received.
         */
        void createMatchWithInitialTurn(
            const char * in_jsonOpponentIds,
            const char * in_jsonMatchState,
            const char * in_pushNotificationMessage = NULL,
            const char * in_nextPlayer = NULL,
            const char * in_jsonSummary = NULL,
            IServerCallback * in_callback = NULL);
        
        // Removal after May 10 2016 - Use method without in_matchId instead
        DEPRECATED void createMatchWithInitialTurn(
            const char * in_jsonOpponentIds,
            const char * in_jsonMatchState,
            const char * in_pushNotificationMessage = NULL,
            const char * in_matchId = NULL,
            const char * in_nextPlayer = NULL,
            const char * in_jsonSummary = NULL,
            IServerCallback * in_callback = NULL);
    
        /**
         * Submits a turn for the given match.
         *
         * Service Name - AsyncMatch
         * Service Operation - SubmitTurn
         *
         * @param in_ownerId Match owner identfier
         * @param in_matchId Match identifier
         * @param in_version Game state version to ensure turns are submitted once and in order
         * @param in_jsonMatchState JSON string provided by the caller
         * @param in_pushNotificationMessage Optional push notification message to send to the other party.
         *  Refer to the Push Notification functions for the syntax required.
         * @param in_nextPlayer Optionally, force the next player player to be a specific player
         * @param in_jsonSummary Optional JSON string that other players will see as a summary of the game when listing their games
         * @param in_jsonStatistics Optional JSON string blob provided by the caller
         * @param in_callback Optional instance of IServerCallback to call when the server response is received.
         */
        void submitTurn(
            const char * in_ownerId,
            const char * in_matchId,
            uint64_t in_version,
            const char * in_jsonMatchState,
            const char * in_pushNotificationMessage = NULL,
            const char * in_nextPlayer = NULL,
            const char * in_jsonSummary = NULL,
            const char * in_jsonStatistics = NULL,
            IServerCallback * in_callback = NULL );
    
        /**
         * Allows the current player (only) to update Summary data without having to submit a whole turn.
         *
         * Service Name - AsyncMatch
         * Service Operation - UpdateMatchSummary
         *
         * @param in_ownerId Match owner identfier
         * @param in_matchId Match identifier
         * @param in_version Game state version to ensure turns are submitted once and in order
         * @param in_jsonSummary JSON string that other players will see as a summary of the game when listing their games
         * @param in_callback Optional instance of IServerCallback to call when the server response is received.
         */
        void updateMatchSummaryData(
            const char * in_ownerId,
            const char * in_matchId,
            uint64_t in_version,
            const char * in_jsonSummary,
            IServerCallback * in_callback = NULL );
    
        /**
         * Marks the given match as complete.
         *
         * Service Name - AsyncMatch
         * Service Operation - Complete
         *
         * @param in_ownerId Match owner identifier
         * @param in_matchId Match identifier
         * @param in_callback Optional instance of IServerCallback to call when the server response is received.
         */
        void completeMatch( const char * in_ownerId, const char * in_matchId, IServerCallback * in_callback = NULL );
    
        /**
         * Returns the current state of the given match.
         *
         * Service Name - AsyncMatch
         * Service Operation - ReadMatch
         *
         * @param in_ownerId   Match owner identifier
         * @param in_matchId   Match identifier
         * @param in_callback  Optional instance of IServerCallback to call when the server response is received.
         */
        void readMatch( const char * in_ownerId, const char * in_matchId, IServerCallback * in_callback = NULL );
    
        /**
         * Returns the match history of the given match.
         *
         * Service Name - AsyncMatch
         * Service Operation - ReadMatchHistory
         *
         * @param in_ownerId   Match owner identifier
         * @param in_matchId   Match identifier
         * @param in_callback  Optional instance of IServerCallback to call when the server response is received.
         */
        void readMatchHistory( const char * in_ownerId, const char * in_matchId, IServerCallback * in_callback = NULL );
    
        /**
         * Returns all matches that are NOT in a COMPLETE state for which the player is involved.
         *
         * Service Name - AsyncMatch
         * Service Operation - FindMatches
         *
         * @param in_callback  Optional instance of IServerCallback to call when the server response is received.
         */
        void findMatches( IServerCallback * in_callback );
    
        /**
         * Returns all matches that are in a COMPLETE state for which the player is involved.
         *
         * Service Name - AsyncMatch
         * Service Operation - FindMatchesCompleted
         *
         * @param in_callback  Optional instance of IServerCallback to call when the server response is received.
         */
        void findCompleteMatches( IServerCallback * in_callback = NULL);
    
        /**
         * Marks the given match as abandoned.
         *
         * Service Name - AsyncMatch
         * Service Operation - Abandon
         *
         * @param in_ownerId   Match owner identifier
         * @param in_matchId   Match identifier
         * @param in_callback  Optional instance of IServerCallback to call when the server response is received.
         */
        void abandonMatch( const char * in_ownerId, const char * in_matchId, IServerCallback * in_callback = NULL );
    
        /**
         * Removes the match and match history from the server. DEBUG ONLY, in production it is recommended
         *   the user leave it as completed.
         *
         * Service Name - AsyncMatch
         * Service Operation - Delete
         *
         * @param in_ownerId   Match owner identifier
         * @param in_matchId   Match identifier
         * @param in_callback  Optional instance of IServerCallback to call when the server response is received.
         */
        void deleteMatch( const char * in_ownerId, const char * in_matchId, IServerCallback * in_callback = NULL );
    
    private:
        void createMatchInternal(
            const char * in_jsonOpponentIds,
            const char * in_jsonMatchState,
            const char * in_pushNotificationMessage,
            const char * in_matchId,
            const char * in_nextPlayer,
            const char * in_jsonSummary,
            IServerCallback * in_callback);

        BrainCloudClient * m_client;
    };
}