// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <string>
#include "braincloud/BrainCloudTypes.h"

namespace BrainCloud
{
    class IServerCallback;
    class BrainCloudClient;

    class BrainCloudOneWayMatch
    {
    public:
        BrainCloudOneWayMatch(BrainCloudClient* in_client);

        /**
         * Starts a match
         *
         * Service Name - OneWayMatch
         * Service Operation - StartMatch
         *
         * @param in_otherPlayerId The player to start a match with
         * @param in_rangeDelta The range delta used for the initial match search
         * @param in_callback The method to be invoked when the server response is received
         */
        void startMatch(const char * in_otherPlayerId, int32_t in_rangeDelta, IServerCallback * in_callback = NULL);

        /**
         * Cancels a match
         *
         * Service Name - OneWayMatch
         * Service Operation - CancelMatch
         *
         * @param in_playbackStreamId The playback stream id returned in the start match
         * @param in_callback The method to be invoked when the server response is received
         */
        void cancelMatch(const char * in_playbackStreamId, IServerCallback * in_callback = NULL);

        /**
         * Completes a match
         *
         * Service Name - OneWayMatch
         * Service Operation - CompleteMatch
         *
         * @param in_playbackStreamId The playback stream id returned in the initial start match
         * @param in_callback The method to be invoked when the server response is received
         */
        void completeMatch(const char * in_playbackStreamId, IServerCallback * in_callback = NULL);

    private:
        BrainCloudClient * m_client;
    };
}