// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BrainCloudClient;
class IServerCallback;

class BCCLIENTPLUGIN_API BrainCloudAppStore
{
public:
  BrainCloudAppStore(BrainCloudClient *client);

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
  void verifyPurchase(const FString &in_storeId, const FString &in_jsonReceiptData, IServerCallback *callback = nullptr);

  /**
    * Returns the eligible promotions for the player.
    *
    * Service Name - AppStore
    * Service Operation - EligiblePromotions
    *
    * @param in_callback The method to be invoked when the server response is received
    */
  void getEligiblePromotions(IServerCallback *callback = nullptr);

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
  void getSalesInventory(const FString &in_storeId, const FString &in_userCurrency, IServerCallback *callback = nullptr);

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
  void getSalesInventoryByCategory(const FString &in_storeId, const FString &in_userCurrency, const FString &in_category, IServerCallback *callback = nullptr);

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
  void startPurchase(const FString &in_storeId, const FString &in_jsonPurchaseData, IServerCallback *callback = nullptr);

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
  void finalizePurchase(const FString &in_storeId, const FString &in_transactionId, const FString &in_jsonTransactionData, IServerCallback *callback = nullptr);

  /**
  * Returns up-to-date eligible 'promotions' for the user and a 'promotionsRefreshed' flag indicating whether the user's promotion info required refreshing.
  *
  * Service Name - appStore
  * Service Operation - REFRESH_PROMOTIONS
  *
  * @param callback The method to be invoked when the server response is received
  */
  void refreshPromotions(IServerCallback *callback = nullptr);

private:
  BrainCloudClient *_client = nullptr;
};
