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
	* @deprecated Method is recommended to be used in Cloud Code only for security
	* If you need to use it client side, enable 'Allow Currency Calls from Client' on the brainCloud dashboard
	*/
	DEPRECATED("3.2.0", "Method is recommended to be used in Cloud Code only for security. If you need to use it client side, enable 'Allow Currency Calls from Client' on the brainCloud dashboard.")
		void awardCurrency(const FString& currencyType, int32 amount, IServerCallback* callback);

	/**
	* @deprecated Method is recommended to be used in Cloud Code only for security
	* If you need to use it client side, enable 'Allow Currency Calls from Client' on the brainCloud dashboard
	*/
	DEPRECATED("3.2.0", "Method is recommended to be used in Cloud Code only for security. If you need to use it client side, enable 'Allow Currency Calls from Client' on the brainCloud dashboard.")
		void consumeCurrency(const FString& currencyType, int32 amount, IServerCallback* callback);

	/**
	* @deprecated Method is recommended to be used in Cloud Code only for security
	* If you need to use it client side, enable 'Allow Currency Calls from Client' on the brainCloud dashboard
	*/
	DEPRECATED("3.2.0", "Method is recommended to be used in Cloud Code only for security. If you need to use it client side, enable 'Allow Currency Calls from Client' on the brainCloud dashboard.")
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

private:
    BrainCloudClient* _client = nullptr;
};
