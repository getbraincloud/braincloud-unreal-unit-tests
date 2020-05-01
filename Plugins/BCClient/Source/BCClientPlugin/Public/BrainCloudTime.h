// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudTime
{
  public:
    BrainCloudTime(BrainCloudClient *client);

    /**
       * Method returns the server time in UTC. This is in UNIX millis time format.
       * For instance 1396378241893 represents 2014-04-01 2:50:41.893 in GMT-4.
       *
       * Service Name - Time
       * Service Operation - Read
       *
       * Server API reference: ServiceName.Time, ServiceOperation.Read
       *
       * @param callback The method to be invoked when the server response is received
       */
    void readServerTime(IServerCallback *callback);

  private:
    BrainCloudClient *_client = nullptr;
};
