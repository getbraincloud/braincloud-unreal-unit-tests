// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudProduct
{
public:
    BrainCloudProduct(BrainCloudClient* client);

    /**
     * Gets the player's currency for the given currency type
     * or all currency types if null passed in.
     *
     * Service Name - Product
     * Service Operation - GetPlayerVC
     *
     * @param currencyType The currency type to retrieve or null
     * if all currency types are being requested.
     *
     * @param callback The method to be invoked when the server response is received
     */
    void getCurrency(const FString& currencyType, IServerCallback* callback);

    /**
     * Award player the passed-in amount of currency. Returns
     * JSON representing the new currency values.
     *
     * Service Name - Product
     * Service Operation - AwardVC
     *
     * @param callback The method to be invoked when the server response is received
     */
    void awardCurrency(const FString& currencyType, int32 amount, IServerCallback* callback);

    /**
     * Consume the passed-in amount of currency from the player.
     *
     * Service Name - Product
     * Service Operation - ConsumePlayerVC
     *
     * @param currencyType The currency type to consume.
     * @param amount The amount of currency to consume.
     * @param callback The method to be invoked when the server response is received
     */
    void consumeCurrency(const FString& currencyType, int32 amount, IServerCallback* callback);

    /**
     * Resets the player's currency back to zero.
     *
     * Service Name - Product
     * Service Operation - ResetPlayerVC
     *
     * @param callback The method to be invoked when the server response is received
     */
    void resetCurrency(IServerCallback* callback);

    /**
    * Method gets the active sales inventory for the passed-in platform and
    * currency type.
    *
    * Service Name - Product
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
    * @param userCurrency The currency to retrieve the sales
    * inventory for. This is only used for Steam and Facebook stores.
    * @param callback The method to be invoked when the server response is received
    */
    void getSalesInventory(const FString& platform, const FString& userCurrency, IServerCallback* callback);

    /**
    * Method gets the active sales inventory for the passed-in platform,
    * currency type and category.
    *
    * Service Name - Product
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
    * @param userCurrency The currency to retrieve the sales
    * inventory for. This is only used for Steam and Facebook stores.
    * @param category Inventory category to retrieve
    * @param callback The method to be invoked when the server response is received
    */
    void getSalesInventoryByCategory(const FString& platform, const FString& userCurrency, const FString& category, IServerCallback * callback);

    /**
    * Method verifies an iTunes receipt and awards the items related to this receipt.
    *
    * Service Name - Product
    * Server Operation - OP_CASH_IN_RECEIPT
    *
    * @param base64EncReceiptData The iTunes receipt
    * @param callback The method to be invoked when the server response is received
    */
    void verifyItunesReceipt(const FString& base64EncReceiptData, IServerCallback * callback);

    /**
     * Initialize Steam Transaction
     *
     * Service Name - Product
     * Service Operation - StartSteamTransaction
     *
     * @param language ISO 639-1 language code
     * @param items Items to purchase
     * @param callback The method to be invoked when the server response is received
     */
    void startSteamTransaction(const FString& language, const FString& itemId, IServerCallback* callback);

    /**
     * Finalize Steam Transaction
     *
     * Service Name - Product
     * Service Operation - FinalizeSteamTransaction
     *
     * @param transId Steam transaction id
     * @param callback The method to be invoked when the server response is received
     */
    void finalizeSteamTransaction(const FString& transId, IServerCallback* callback);

    /**
     * Verify Microsoft Receipt
     *
     * Service Name - Product
     * Service Operation - VerifyMicrosoftReceipt
     *
     * @param receipt Receipt XML
     * @param callback The method to be invoked when the server response is received
     */
    void verifyMicrosoftReceipt(const FString& receipt, IServerCallback* callback);

    /**
    * Confirms a google play purchase. On success, the player will be awarded the
    * associated currencies.
    *
    * Service Name - Product
    * Server Operation - CONFIRM_GOOGLEPLAY_PURCHASE
    *
    * @param orderId The order id
    * @param productId The product id
    * @param token Google Play token string
    * @param callback The method to be invoked when the server response is received
    */
    void confirmGooglePlayPurchase(const FString& orderId, const FString& productId, const FString& token, IServerCallback * callback);

    /**
    * Get Eligible Promotions
    *
    * Service Name - Product
    * Service Operation - GetEligiblePromotions
    *
    * @param callback The method to be invoked when the server response is received
    */
    void getEligiblePromotions(IServerCallback* callback);

    /**
    * Awards currency in a parent app.
    *
    * Service Name - Product
    * Service Operation - AWARD_PARENT_VC
    *
    * @param currencyType The ID of the parent currency
    * @param amount The amount of currency to award
    * @param parentLevel The level of the parent containing the currency
    * @param callback The method to be invoked when the server response is received
    */
    void awardParentCurrency(const FString& currencyType, int32 amount, const FString& parentLevel, IServerCallback * callback);

    /**
    * Consumes currency in a parent app.
    *
    * Service Name - Product
    * Service Operation - CONSUME_PARENT_VC
    *
    * @param currencyType The ID of the parent currency
    * @param amount The amount of currency to consume
    * @param parentLevel The level of the parent containing the currency
    * @param callback The method to be invoked when the server response is received
    */
    void consumeParentCurrency(const FString& currencyType, int32 amount, const FString& parentLevel, IServerCallback * callback);

    /**
    * Gets information on a single currency in a parent app
    * or all currency types if a null type is passed in.
    *
    * Service Name - Product
    * Service Operation - GET_PARENT_VC
    *
    * @param currencyType The ID of the parent currency or null to get all currencies
    * @param parentLevel The level of the parent containing the currency
    * @param callback The method to be invoked when the server response is received
    */
    void getParentCurrency(const FString& currencyType, const FString& parentLevel, IServerCallback * callback);

    /**
    * Resets all currencies in a parent app.
    *
    * Service Name - Product
    * Service Operation - RESET_PARENT_VC
    *
    * @param parentLevel The level of the parent containing the currencies
    * @param callback The method to be invoked when the server response is received
    */
    void resetParentCurrency(const FString& parentLevel, IServerCallback * callback);

private:
    BrainCloudClient* _client = nullptr;
};
