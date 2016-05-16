// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <string>
#include "braincloud/BrainCloudTypes.h"

namespace BrainCloud
{
    class IServerCallback;
    class BrainCloudClient;

    class BrainCloudMatchmaking
    {
    public:
        BrainCloudMatchmaking(BrainCloudClient* in_client);

        /**
         * Read match making record
         *
         * Service Name - MatchMaking
         * Service Operation - Read
         *
         * @param in_callback The method to be invoked when the server response is received
         */
        void read(IServerCallback * in_callback = NULL);

        /**
         * Sets player rating
         *
         * Service Name - MatchMaking
         * Service Operation - SetPlayerRating
         *
         * @param in_playerRating The new player rating.
         * @param in_callback The method to be invoked when the server response is received
         */
        void setPlayerRating(int32_t in_playerRating, IServerCallback * in_callback = NULL);

        /**
         * Resets player rating
         *
         * Service Name - MatchMaking
         * Service Operation - ResetPlayerRating
         *
         * @param in_callback The method to be invoked when the server response is received
         */
        void resetPlayerRating(IServerCallback * in_callback = NULL);

        /**
         * Increments player rating
         *
         * Service Name - MatchMaking
         * Service Operation - IncrementPlayerRating
         *
         * @param in_increment The increment amount
         * @param in_callback The method to be invoked when the server response is received
         */
        void incrementPlayerRating(int32_t in_increment, IServerCallback * in_callback = NULL);

        /**
         * Decrements player rating
         *
         * Service Name - MatchMaking
         * Service Operation - DecrementPlayerRating
         *
         * @param in_decrement The decrement amount
         * @param in_callback The method to be invoked when the server response is received
         */
        void decrementPlayerRating(int32_t in_decrement, IServerCallback * in_callback = NULL);

        /**
         * Turns shield on
         *
         * Service Name - MatchMaking
         * Service Operation - ShieldOn
         *
         * @param in_callback The method to be invoked when the server response is received
         */
        void turnShieldOn(IServerCallback * in_callback = NULL);

        /**
         * Turns shield on for the specified number of minutes
         *
         * Service Name - MatchMaking
         * Service Operation - ShieldOnFor
         *
         * @param in_minutes Number of minutes to turn the shield on for
         * @param in_callback The method to be invoked when the server response is received
         */
        void turnShieldOnFor(int32_t in_minutes, IServerCallback * in_callback = NULL);

        /**
         * Turns shield off
         *
         * Service Name - MatchMaking
         * Service Operation - ShieldOff
         *
         * @param in_callback The method to be invoked when the server response is received
         */
        void turnShieldOff(IServerCallback * in_callback = NULL);

        /**
         * Gets the shield expiry for the given player id. Passing in a null player id
         * will return the shield expiry for the current player. The value returned is
         * the time in UTC millis when the shield will expire.
         *
         * Service Name - MatchMaking
         * Service Operation - GetShieldExpiry
         *
         * @param in_playerId The player id or use null to retrieve for the current player
         * @param in_callback The method to be invoked when the server response is received
         */
        void getShieldExpiry(const char * in_playerId, IServerCallback * in_callback = NULL);

        /**
         * Finds matchmaking enabled players
         *
         * Service Name - MatchMaking
         * Service Operation - FIND_PLAYERS
         *
         * @param in_rangeDelta The range delta
         * @param in_numMatches The maximum number of matches to return
         * @param in_callback The method to be invoked when the server response is received
         */
        void findPlayers(int32_t in_rangeDelta, int32_t in_numMatches, IServerCallback * in_callback = NULL);

        /**
         * Finds matchmaking enabled players with additional attributes
         *
         * Service Name - MatchMaking
         * Service Operation - FIND_PLAYERS
         *
         * @param in_rangeDelta The range delta
         * @param in_numMatches The maximum number of matches to return
         * @param in_jsonAttributes Attributes match criteria
         * @param in_callback The method to be invoked when the server response is received
         */
        void findPlayersWithAttributes(int32_t in_rangeDelta, int32_t in_numMatches, std::string in_jsonAttributes, IServerCallback * in_callback = NULL);

        /**
         * Finds matchmaking enabled players
         *
         * Service Name - MatchMaking
         * Service Operation - FIND_PLAYERS_USING_FILTER
         *
         * @param in_rangeDelta The range delta
         * @param in_numMatches The maximum number of matches to return
         * @param in_jsonExtraParms Parameters to pass to the CloudCode filter script
         * @param in_callback The method to be invoked when the server response is received
         */
        void findPlayersUsingFilter(int32_t in_rangeDelta, int32_t in_numMatches, std::string in_jsonExtraParms, IServerCallback * in_callback = NULL);

        /**
        * Finds matchmaking enabled players using a cloud code filter
        * and additional attributes
        *
        * Service Name - MatchMaking
        * Service Operation - FIND_PLAYERS_USING_FILTER
        *
        * @param in_rangeDelta The range delta
        * @param in_numMatches The maximum number of matches to return
        * @param in_jsonAttributes Attributes match criteria
        * @param in_jsonExtraParms Parameters to pass to the CloudCode filter script
        * @param in_callback The method to be invoked when the server response is received
        */
        void findPlayersWithAttributesUsingFilter(
            int32_t in_rangeDelta,
            int32_t in_numMatches,
            std::string in_jsonAttributes,
            std::string in_jsonExtraParms,
            IServerCallback * in_callback = NULL);

        /**
         * Enables Match Making for the Player
         *
         * Service Name - MatchMaking
         * Service Operation - EnableMatchMaking
         *
         * @param in_callback The method to be invoked when the server response is received
         */
        void enableMatchMaking(IServerCallback * in_callback = NULL);

        /**
        * Disables Match Making for the Player
        *
        * Service Name - MatchMaking
        * Service Operation - EnableMatchMaking
        *
        * @param in_callback The method to be invoked when the server response is received
        */
        void disableMatchMaking(IServerCallback * in_callback = NULL);

    private:
        BrainCloudClient * m_client;
    };
}