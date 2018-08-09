// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudLobby
{
public:
    BrainCloudLobby(BrainCloudClient* client);

private:
    BrainCloudClient* _client = nullptr;
};

