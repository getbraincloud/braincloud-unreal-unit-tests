// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <string>
#include "braincloud/BrainCloudTypes.h"

namespace BrainCloud
{
    class IServerCallback;
    class BrainCloudClient;

    class BrainCloudPlaybackStream
    {
    public:
        BrainCloudPlaybackStream(BrainCloudClient* in_client);

        /**
        * Starts a stream
        *
        * Service Name - PlaybackStream
        * Service Operation - StartStream
        *
        * @param in_targetPlayerId The player to start a stream with
        * @param in_includeSharedData Whether to include shared data in the stream
        * @param in_callback The method to be invoked when the server response is received
        */
        void startStream(const char * in_targetPlayerId, bool in_includeSharedData, IServerCallback * in_callback = NULL);

        /**
        * Reads a stream
        *
        * Service Name - PlaybackStream
        * Service Operation - ReadStream
        *
        * @param in_playbackStreamId Identifies the stream to read
        * @param in_callback The method to be invoked when the server response is received
        */
        void readStream(const char * in_playbackStreamId, IServerCallback * in_callback = NULL);

        /**
        * Ends a stream
        *
        * Service Name - PlaybackStream
        * Service Operation - EndStream
        *
        * @param in_playbackStreamId Identifies the stream to read
        * @param in_callback The method to be invoked when the server response is received
        */
        void endStream(const char * in_playbackStreamId, IServerCallback * in_callback = NULL);

        /**
        * Deletes a stream
        *
        * Service Name - PlaybackStream
        * Service Operation - DeleteStream
        *
        * @param in_playbackStreamId Identifies the stream to read
        * @param in_callback The method to be invoked when the server response is received
        */
        void deleteStream(const char * in_playbackStreamId, IServerCallback * in_callback = NULL);

        /**
        * Adds a stream event
        *
        * Service Name - PlaybackStream
        * Service Operation - AddEvent
        *
        * @param in_playbackStreamId Identifies the stream to read
        * @param in_jsonEventData Describes the event
        * @param in_jsonSummary Current summary data as of this event
        * @param in_callback The method to be invoked when the server response is received
        */
        void addEvent(const char * in_playbackStreamId, const char * in_jsonEventData, const char * in_jsonSummary, IServerCallback * in_callback = NULL);

        /**
        * Gets stream summaries for initiating player
        *
        * Service Name - PlaybackStream
        * Service Operation - GetStreamSummariesForInitiatingPlayer
        *
        * @param in_initiatingPlayerId The player that started the stream
        * @param in_callback The method to be invoked when the server response is received
        */
        void getStreamSummariesForInitiatingPlayer(const char * in_initiatingPlayerId, IServerCallback * in_callback = NULL);

        /**
        * Gets stream summaries for target player
        *
        * Service Name - PlaybackStream
        * Service Operation - GetStreamSummariesForTargetPlayer
        *
        * @param in_targetPlayerId The player that started the stream
        * @param in_callback The method to be invoked when the server response is received
        */
        void getStreamSummariesForTargetPlayer(const char * in_targetPlayerId, IServerCallback * in_callback = NULL);

        /**
        * Gets recent stream summaries for initiating player
        *
        * Service Name - PlaybackStream
        * Service Operation - GetRecentStreamsForInitiatingPlayer
        *
        * @param targetPlayerId The player that started the stream
        * @param maxNumStreams The max number of streams to query
        * @param callback The callback.
        */
        void getRecentStreamsForInitiatingPlayer(const char * in_initiatingPlayerId, int in_maxNumStreams, IServerCallback * in_callback = NULL);

        /**
        * Gets recent stream summaries for target player
        *
        * Service Name - PlaybackStream
        * Service Operation - GetRecentStreamsForTargetPlayer
        *
        * @param targetPlayerId The player that was target of the stream
        * @param maxNumStreams The max number of streams to query
        * @param callback The callback.
        */
        void getRecentStreamsForTargetPlayer(const char * in_targetPlayerId, int in_maxNumStreams, IServerCallback * in_callback = NULL);

    private:
        BrainCloudClient * m_client;
    };
}