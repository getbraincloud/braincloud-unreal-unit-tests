// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BCCLIENTPLUGIN_API INetworkErrorCallback
{

  public:
    virtual ~INetworkErrorCallback() {}

    /**
     * The networkError method is invoked whenever a network error is encountered
     * communicating to the brainCloud server.
     *
     * Note this method is *not* invoked when FlushCachedMessages(true) is called.
     */
    virtual void networkError() = 0;
};