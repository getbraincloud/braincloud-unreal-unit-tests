// Copyright 2021 bitHeads, Inc. All Rights Reserved.

#pragma once

class BCCLIENTPLUGIN_API IRelayCallback
{
  public:
    virtual ~IRelayCallback() { }

    /**
     * Relay message from the Relay Service
     *
     * @param netId - Net Id of the member this message is from.
     * @param bytes - Data received
     */
    virtual void relayCallback(int netId, const TArray<uint8>& bytes) = 0;
};
