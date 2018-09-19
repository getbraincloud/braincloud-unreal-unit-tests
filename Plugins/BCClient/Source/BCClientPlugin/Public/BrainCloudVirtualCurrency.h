// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudVirtualCurrency
{
public:
    BrainCloudVirtualCurrency(BrainCloudClient* client);

    /**
    * Retrieve the user's currency account. Optional parameters: vcId (if retrieving all currencies).
    *
    * Service Name - VirtualCurrency
    * Service Operation - GetCurrency
    *
    * @param vcId
    * @param in_callback The method to be invoked when the server response is received
    */
    void getCurrency(const FString& in_vcId, IServerCallback * callback = nullptr);

    /**
    * Retrieve the parent user's currency account. Optional parameters: vcId (if retrieving all currencies).
    *
    * Service Name - VirtualCurrency
    * Service Operation - GetParentCurrency
    *
    * @param vcId
    * @param levelName
    * @param in_callback The method to be invoked when the server response is received
    */
    void getParentCurrency(const FString& in_vcId, const FString& in_levelName, IServerCallback * callback = nullptr);

    /**
    * Retrieve the peer user's currency account. Optional parameters: vcId (if retrieving all currencies).
    *
    * Service Name - VirtualCurrency
    * Service Operation - GetPeerCurrency
    *
    * @param vcId
    * @param peerCode
    * @param in_callback The method to be invoked when the server response is received
    */
    void getPeerCurrency(const FString& in_vcId, const FString& in_peerCode, IServerCallback * callback = nullptr);

private:
    BrainCloudClient* _client = nullptr;
};


