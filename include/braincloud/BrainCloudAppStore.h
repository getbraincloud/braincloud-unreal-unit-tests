// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#ifndef _BRAINCLOUDAPPSTORE_H_
#define _BRAINCLOUDAPPSTORE_H_

#include <string>
#include "braincloud/BrainCloudTypes.h"

namespace BrainCloud
{
    class IServerCallback;
    class BrainCloudClient;

    class BrainCloudAppStore
    {
    public:
        BrainCloudAppStore(BrainCloudClient* in_client);

        /**
        * Verifies that purchase was properly made at the store.
        *
        * Service Name - AppStore
        * Service Operation - VerifyPurchase
        *
        * @param storeId The store platform. Valid stores are:
        * - itunes
        * - facebook
        * - appworld
        * - steam
        * - windows
        * - windowsPhone
        * - googlePlay
        * @param receiptData the specific store data required
        * @param in_callback The method to be invoked when the server response is received
        */
        void verifyPurchase(const std::string& in_storeId, const std::string& in_jsonReceiptData, IServerCallback* in_callback = NULL);

        /**
        * Returns the eligible promotions for the player.
        *
        * Service Name - AppStore
        * Service Operation - EligiblePromotions
        *
        * @param in_callback The method to be invoked when the server response is received
        */
        void getEligiblePromotions(IServerCallback* in_callback = NULL);

        /**
        * Method gets the active sales inventory for the passed-in
        * currency type.
        *
        * Service Name - AppStore
        * Service Operation - GetInventory
        *
        * @param platform The store platform. Valid stores are:
        * - itunes
        * - facebook
        * - appworld
        * - steam
        * - windows
        * - windowsPhone
        * - googlePlay
        * @param userCurrency The currency type to retrieve the sales inventory for.
        * @param in_callback The method to be invoked when the server response is received
        */
        void getSalesInventory(const std::string& in_storeId, const std::string& in_userCurrency, IServerCallback* in_callback = NULL);

        /**
        * Method gets the active sales inventory for the passed-in
        * currency type.
        *
        * Service Name - AppStore
        * Service Operation - GetInventory
        *
        * @param storeId The store platform. Valid stores are:
        * - itunes
        * - facebook
        * - appworld
        * - steam
        * - windows
        * - windowsPhone
        * - googlePlay
        * @param userCurrency The currency type to retrieve the sales inventory for.
        * @param category The product category
        * @param in_callback The method to be invoked when the server response is received
        */
        void getSalesInventoryByCategory(const std::string& in_storeId, const std::string& in_userCurrency, const std::string& in_category, IServerCallback* in_callback = NULL);

        /**
        * Start A Two Staged Purchase Transaction
        *
        * Service Name - AppStore
        * Service Operation - StartPurchase
        *
        * @param storeId The store platform. Valid stores are:
        * - itunes
        * - facebook
        * - appworld
        * - steam
        * - windows
        * - windowsPhone
        * - googlePlay
        * @param purchaseData specific data for purchasing 2 staged purchases
        * @param in_callback The method to be invoked when the server response is received
        */
        void startPurchase(const std::string& in_storeId, const std::string& in_jsonPurchaseData, IServerCallback* in_callback = NULL);

        /**
        * Finalize A Two Staged Purchase Transaction
        *
        * Service Name - AppStore
        * Service Operation - FinalizePurchase
        *
        * @param storeId The store platform. Valid stores are:
        * - itunes
        * - facebook
        * - appworld
        * - steam
        * - windows
        * - windowsPhone
        * - googlePlay
        * @param transactionId the transactionId returned from start Purchase
        * @param transactionData specific data for purchasing 2 staged purchases
        * @param in_callback The method to be invoked when the server response is received
        */
        void finalizePurchase(const std::string& in_storeId, const std::string& in_transactionId, const std::string& in_jsonTransactionData, IServerCallback* in_callback = NULL);

    private:
        BrainCloudClient * m_client;
    };
}

#endif
