// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudRTT
{
public:
  BrainCloudRTT(BrainCloudClient *client);

  /// <summary>
  /// Requests the event server address
  /// </summary>
  void requestClientConnection(IServerCallback *callback);

private:
  BrainCloudClient *_client = nullptr;
};
