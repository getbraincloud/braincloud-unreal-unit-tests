// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;
class IAcl;

class BCCLIENTPLUGIN_API BrainCloudDataStream
{
public:
    BrainCloudDataStream(BrainCloudClient* client);

    /**
     * Creates custom data stream page event
     *
     * @param eventName Name of event
     * @param jsonEventProperties Properties of event
     * @param callback The callback object
     */
    void customPageEvent(const FString& eventName, const FString& jsonEventProperties, IServerCallback * callback = nullptr);

    /**
     * Creates custom data stream screen event
     *
     * @param eventName Name of event
     * @param jsonEventProperties Properties of event
     * @param callback The callback object
     */
    void customScreenEvent(const FString& eventName, const FString& jsonEventProperties, IServerCallback * callback = nullptr);

    /**
     * Creates custom data stream track event
     *
     * @param eventName Name of event
     * @param jsonEventProperties Properties of event
     * @param callback The callback object
     */
    void customTrackEvent(const FString& eventName, const FString& jsonEventProperties, IServerCallback * callback = nullptr);

private:
    BrainCloudClient* _client = nullptr;
};