// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudGlobalApp
{
public:
    BrainCloudGlobalApp(BrainCloudClient* client);

    /**
     * Read game's global properties
     *
     * Service Name - GlobalApp
     * Service Operation - ReadProperties
     *
     * @param - callback The method to be invoked when the server response is received
     */
    void readProperties(IServerCallback * callback);

private:
    BrainCloudClient* _client = nullptr;
};