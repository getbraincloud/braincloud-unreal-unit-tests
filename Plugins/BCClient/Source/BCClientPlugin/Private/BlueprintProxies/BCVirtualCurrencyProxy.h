// Copyright 2018 bitHeads, Inc. All Rights Reserved.
#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCVirtualCurrencyProxy.generated.h"

UCLASS(MinimalAPI)
class UBCVirtualCurrencyProxy : public UBCBlueprintCallProxyBase
{
  GENERATED_BODY()

public:
  UBCVirtualCurrencyProxy(const FObjectInitializer &ObjectInitializer);
  /**
    * Retrieve the user's currency account. Optional parameters: vcId (if retrieving all currencies).
    *
    * Service Name - VirtualCurrency
    * Service Operation - GetCurrency
    *
    * @param vcId
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|VirtualCurrency")
  static UBCVirtualCurrencyProxy *GetCurrency(UBrainCloudWrapper *brainCloudWrapper, const FString &vcId);

  /**
    * Retrieve the parent user's currency account. Optional parameters: vcId (if retrieving all currencies).
    *
    * Service Name - VirtualCurrency
    * Service Operation - GetParentCurrency
    *
    * @param vcId
    * @param levelName
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|VirtualCurrency")
  static UBCVirtualCurrencyProxy *GetParentCurrency(UBrainCloudWrapper *brainCloudWrapper, const FString &vcId, const FString &levelName);

  /**
    * Retrieve the peer user's currency account. Optional parameters: vcId (if retrieving all currencies).
    *
    * Service Name - VirtualCurrency
    * Service Operation - GetPeerCurrency
    *
    * @param vcId
    * @param peerCode
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|VirtualCurrency")
  static UBCVirtualCurrencyProxy *GetPeerCurrency(UBrainCloudWrapper *brainCloudWrapper, const FString &vcId, const FString &peerCode);

    /**
    * Reset the player's currency to 0. 
    *
    * Service Name - VirtualCurrency
    * Service Operation - ResetCurrency
    *
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|VirtualCurrency")
  static UBCVirtualCurrencyProxy *ResetCurrency(UBrainCloudWrapper *brainCloudWrapper);

  /**
	  * @warning Method is recommended to be used in Cloud Code only for security
	  *
	  * For security reasons calling this API from the client is not recommended, and is rejected at the server by default. To over-ride, enable the 'Allow Currency Calls from Client" compatibility setting in the Design Portal.
	  */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|VirtualCurrency")
  static UBCVirtualCurrencyProxy *AwardCurrency(UBrainCloudWrapper *brainCloudWrapper, const FString &currencyType, int32 amount);

  /**
	  * @warning Method is recommended to be used in Cloud Code only for security
	  *
	  * For security reasons calling this API from the client is not recommended, and is rejected at the server by default. To over-ride, enable the 'Allow Currency Calls from Client" compatibility setting in the Design Portal.
	  */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|VirtualCurrency")
  static UBCVirtualCurrencyProxy *ConsumeCurrency(UBrainCloudWrapper *brainCloudWrapper, const FString &currencyType, int32 amount);
};
