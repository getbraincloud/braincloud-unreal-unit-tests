// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudOneWayMatch
{
  public:
    BrainCloudOneWayMatch(BrainCloudClient *client);

    /**
    * Starts a match
    *
    * Service Name - OneWayMatch
    * Service Operation - StartMatch
    *
    * @param otherPlayerId The player to start a match with
    * @param rangeDelta The range delta used for the initial match search
    * @param callback The method to be invoked when the server response is received
    */
    void startMatch(const FString &otherPlayerId, int32 rangeDelta, IServerCallback *callback);

    /**
    * Cancels a match
    *
    * Service Name - OneWayMatch
    * Service Operation - CancelMatch
    *
    * @param playbackStreamId The playback stream id returned in the start match
    * @param callback The method to be invoked when the server response is received
    */
    void cancelMatch(const FString &playbackStreamId, IServerCallback *callback);

    /**
     * Completes a match
     *
     * Service Name - OneWayMatch
     * Service Operation - CompleteMatch
     *
     * @param playbackStreamId The playback stream id returned in the initial start match
     * @param callback The method to be invoked when the server response is received
     */
    void completeMatch(const FString &playbackStreamId, IServerCallback *callback);

  private:
    BrainCloudClient *_client = nullptr;
};
