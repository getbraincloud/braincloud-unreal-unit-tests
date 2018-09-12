// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#ifndef _BRAINCLOUDVIRTUALCURRENCY_H_
#define _BRAINCLOUDVIRTUALCURRENCY_H_

#include <string>
#include "braincloud/BrainCloudTypes.h"

namespace BrainCloud
{
    class IServerCallback;
    class BrainCloudClient;

    class BrainCloudVirtualCurrency
    {
    public:
        BrainCloudVirtualCurrency(BrainCloudClient* in_client);

        /**
        * Retrieve the user's currency account. Optional parameters: vcId (if retrieving all currencies).
        *
        * Service Name - VirtualCurrency
        * Service Operation - GetCurrency
        *
        * @param vcId
        * @param in_callback The method to be invoked when the server response is received
        */
        void getCurrency(const std::string& in_vcId, IServerCallback * in_callback = NULL);

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
        void getParentCurrency(const std::string& in_vcId, const std::string& in_levelName, IServerCallback * in_callback = NULL);

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
        void getPeerCurrency(const std::string& in_vcId, const std::string& in_peerCode, IServerCallback * in_callback = NULL);

    private:
        BrainCloudClient * m_client;
    };
}

#endif
