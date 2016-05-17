// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include <string>

namespace BrainCloud
{
    class IServerCallback;
    class BrainCloudClient;

    class BrainCloudRedemptionCode
    {
    public:
        BrainCloudRedemptionCode(BrainCloudClient* in_client);

        /**
         * Redeem a code.
         *
         * Service Name - RedemptionCode
         * Service Operation - REDEEM_CODE
         *
         * @param in_scanCode The code to redeem
         * @param in_codeType The type of code
         * @param in_jsonCustomRedemptionInfo Optional - A JSON string containing custom redemption data
         * @param in_callback The method to be invoked when the server response is received
         */
        void redeemCode(const char* in_scanCode, const char* in_codeType, const char* in_jsonCustomRedemptionInfo, IServerCallback * in_callback = NULL);

        /**
         * Retrieve the codes already redeemed by player.
         *
         * Service Name - RedemptionCode
         * Service Operation - GET_REDEEMED_CODES
         *
         * @param in_codeType Optional - The type of codes to retrieve. Returns all codes if left unspecified.
         * @param in_callback The method to be invoked when the server response is received
         */
        void getRedeemedCodes(const char* in_codeType, IServerCallback * in_callback = NULL);

    private:
        BrainCloudClient * m_client;
    };
}