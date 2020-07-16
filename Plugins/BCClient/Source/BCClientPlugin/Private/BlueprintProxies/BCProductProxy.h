// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCProductProxy.generated.h"

UCLASS(MinimalAPI)
class UBCProductProxy : public UBCBlueprintCallProxyBase
{
    GENERATED_BODY()

  public:
    UBCProductProxy(const FObjectInitializer &ObjectInitializer);

    /**
    * Gets the player's currency for the given currency type
    * or all currency types if null passed in.
    *
    * Service Name - Product
    * Service Operation - GetPlayerVC
    *
    * Param - currencyType The currency type to retrieve or null
    * if all currency types are being requested.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Product")
    static UBCProductProxy *GetCurrency(UBrainCloudWrapper *brainCloudWrapper, const FString &currencyType);

    /**
	* @deprecated Method is recommended to be used in Cloud Code only for security
	* If you need to use it client side, enable 'Allow Currency Calls from Client' on the brainCloud dashboard
	*/
#if ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION >= 22
    UE_DEPRECATED("3.2.0", "Method is recommended to be used in Cloud Code only for security. If you need to use it client side, enable 'Allow Currency Calls from Client' on the brainCloud dashboard")
#else 
    DEPRECATED("3.2.0", "Method is recommended to be used in Cloud Code only for security. If you need to use it client side, enable 'Allow Currency Calls from Client' on the brainCloud dashboard")
#endif
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Product")
    static UBCProductProxy *AwardCurrency(UBrainCloudWrapper *brainCloudWrapper, const FString &currencyType, int32 amount);

    /**
	* @deprecated Method is recommended to be used in Cloud Code only for security
	* If you need to use it client side, enable 'Allow Currency Calls from Client' on the brainCloud dashboard
	*/
#if ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION >= 22
    UE_DEPRECATED("3.2.0", "Method is recommended to be used in Cloud Code only for security. If you need to use it client side, enable 'Allow Currency Calls from Client' on the brainCloud dashboard")
#else
    DEPRECATED("3.2.0", "Method is recommended to be used in Cloud Code only for security. If you need to use it client side, enable 'Allow Currency Calls from Client' on the brainCloud dashboard")
#endif
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Product")
    static UBCProductProxy *ConsumeCurrency(UBrainCloudWrapper *brainCloudWrapper, const FString &currencyType, int32 amount);

    /**
	* @deprecated Method is recommended to be used in Cloud Code only for security
	* If you need to use it client side, enable 'Allow Currency Calls from Client' on the brainCloud dashboard
	*/
#if ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION >= 22
    UE_DEPRECATED("3.2.0", "Method is recommended to be used in Cloud Code only for security. If you need to use it client side, enable 'Allow Currency Calls from Client' on the brainCloud dashboard")
#else 
    DEPRECATED("3.2.0", "Method is recommended to be used in Cloud Code only for security. If you need to use it client side, enable 'Allow Currency Calls from Client' on the brainCloud dashboard")
#endif
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Product")
    static UBCProductProxy *ResetCurrency(UBrainCloudWrapper *brainCloudWrapper);

    /**
    * Method gets the active sales inventory for the passed-in platform and
    * currency type.
    *
    * Service Name - Product
    * Service Operation - GetInventory
    *
    * Param - platform The store platform. Valid stores are:
    * - itunes
    * - facebook
    * - appworld
    * - steam
    * - windows
    * - windowsPhone
    * - googlePlay
    * Param - userCurrency The currency to retrieve the sales
    * inventory for. This is only used for Steam and Facebook stores.
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Product")
    static UBCProductProxy *GetSalesInventory(UBrainCloudWrapper *brainCloudWrapper, const FString &platform, const FString &userCurrency);

    /**
    * Method gets the active sales inventory for the passed-in platform,
    * currency type and category.
    *
    * Service Name - Product
    * Service Operation - GetInventory
    *
    * Param - platform The store platform. Valid stores are:
    * - itunes
    * - facebook
    * - appworld
    * - steam
    * - windows
    * - windowsPhone
    * - googlePlay
    * Param - userCurrency The currency to retrieve the sales
    * inventory for. This is only used for Steam and Facebook stores.
    * Param - category Inventory category to retrieve
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Product")
    static UBCProductProxy *GetSalesInventoryByCategory(UBrainCloudWrapper *brainCloudWrapper, const FString &platform, const FString &userCurrency, const FString &category);

    /**
    * Method verifies an iTunes receipt and awards the items related to this receipt.
    *
    * Service Name - Product
    * Server Operation - OP_CASH_IN_RECEIPT
    *
    * Param - base64EncReceiptData The iTunes receipt
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Product")
    static UBCProductProxy *VerifyItunesReceipt(UBrainCloudWrapper *brainCloudWrapper, const FString &base64EncReceiptData);

    /**
    * Initialize Steam Transaction
    *
    * Service Name - Product
    * Service Operation - StartSteamTransaction
    *
    * Param - language ISO 639-1 language code
    * Param - items Items to purchase
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Product")
    static UBCProductProxy *StartSteamTransaction(UBrainCloudWrapper *brainCloudWrapper, const FString &language, const FString &itemId);

    /**
    * Finalize Steam Transaction
    *
    * Service Name - Product
    * Service Operation - FinalizeSteamTransaction
    *
    * Param - transId Steam transaction id
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Product")
    static UBCProductProxy *FinalizeSteamTransaction(UBrainCloudWrapper *brainCloudWrapper, const FString &transId);

    /**
    * Verify Microsoft Receipt
    *
    * Service Name - Product
    * Service Operation - VerifyMicrosoftReceipt
    *
    * Param - receipt Receipt XML
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Product")
    static UBCProductProxy *VerifyMicrosoftReceipt(UBrainCloudWrapper *brainCloudWrapper, const FString &receipt);

    /**
    * Confirms a google play purchase. On success, the player will be awarded the
    * associated currencies.
    *
    * Service Name - Product
    * Server Operation - CONFIRM_GOOGLEPLAY_PURCHASE
    *
    * Param - orderId The order id
    * Param - productId The product id
    * Param - token Google Play token string
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Product")
    static UBCProductProxy *ConfirmGooglePlayPurchase(UBrainCloudWrapper *brainCloudWrapper, const FString &orderId, const FString &productId, const FString &token);

    /**
    * Get Eligible Promotions
    *
    * Service Name - Product
    * Service Operation - GetEligiblePromotions
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Product")
    static UBCProductProxy *GetEligiblePromotions(UBrainCloudWrapper *brainCloudWrapper);
};
