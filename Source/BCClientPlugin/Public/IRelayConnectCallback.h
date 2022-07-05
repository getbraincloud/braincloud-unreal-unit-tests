// Copyright 2021 bitHeads, Inc. All Rights Reserved.

#pragma once

class BCCLIENTPLUGIN_API IRelayConnectCallback
{
public:
    virtual ~IRelayConnectCallback() { }

    /**
     * Method called when connection to Relay server was successful
     *
     * @param jsonData - System message with connect success packet
     */
    virtual void relayConnectSuccess(const FString& jsonResponse) = 0;

    /**
     * Method called when connection to relay failed or got disconnected
     *
     * @param errorMessage - Text message describing the error.
     */
    virtual void relayConnectFailure(const FString& errorMessage) = 0;
};
