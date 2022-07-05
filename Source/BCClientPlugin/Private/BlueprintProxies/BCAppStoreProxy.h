// Copyright 2018 bitHeads, Inc. All Rights Reserved.
#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BrainCloudWrapper.h"

#include "BCAppStoreProxy.generated.h"

UCLASS(MinimalAPI)
class UBCAppStoreProxy : public UBCBlueprintCallProxyBase
{
  GENERATED_BODY()

public:
  UBCAppStoreProxy(const FObjectInitializer &ObjectInitializer);

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
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|AppStore")
  static UBCAppStoreProxy *VerifyPurchase(UBrainCloudWrapper *brainCloudWrapper, const FString &storeId, const FString &receiptData);

  /**
    * Returns the eligible promotions for the player.
    *
    * Service Name - AppStore
    * Service Operation - EligiblePromotions
    *
    * @param in_callback The method to be invoked when the server response is received
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|AppStore")
  static UBCAppStoreProxy *GetEligiblePromotions(UBrainCloudWrapper *brainCloudWrapper);

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
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|AppStore")
  static UBCAppStoreProxy *GetSalesInventory(UBrainCloudWrapper *brainCloudWrapper, const FString &storeId, const FString &userCurrency);

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
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|AppStore")
  static UBCAppStoreProxy *GetSalesInventoryByCategory(UBrainCloudWrapper *brainCloudWrapper, const FString &storeId, const FString &userCurrency, const FString &category);

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
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|AppStore")
  static UBCAppStoreProxy *StartPurchase(UBrainCloudWrapper *brainCloudWrapper, const FString &storeId, const FString &purchaseData);

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
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|AppStore")
  static UBCAppStoreProxy *FinalizePurchase(UBrainCloudWrapper *brainCloudWrapper, const FString &storeId, const FString &transactionId, const FString &transactionData);

  /**
  * Returns up-to-date eligible 'promotions' for the user and a 'promotionsRefreshed' flag indicating whether the user's promotion info required refreshing.
  *
  * Service Name - appStore
  * Service Operation - REFRESH_PROMOTIONS
  */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|AppStore")
  static UBCAppStoreProxy *RefreshPromotions(UBrainCloudWrapper *brainCloudWrapper);
};
