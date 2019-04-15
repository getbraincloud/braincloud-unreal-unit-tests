// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudRoomServer
{
public:
  BrainCloudRoomServer(BrainCloudRSComms *client);

private:
  BrainCloudRSComms *_rsComms = nullptr;
};
