// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCUtilsProxy.generated.h"

UCLASS(MinimalAPI)
class UBCUtilsProxy : public UBCBlueprintCallProxyBase
{
	GENERATED_BODY()

  public:
	UBCUserItemsProxy(const FObjectInitializer &ObjectInitializer);

	/*
    * Allows item(s) to be awarded to a user without collecting
	* the purchase amount. If includeDef is true, response 
	* includes associated itemDef with language fields limited
	* to the current or default language.
    *
    * Service Name - UserItems
    * Service Operation - AWARD_USER_ITEM
    *
    * @param defId
    * @param callback The method to be invoked when the server response is received
    */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|UserItems")
	static UBCUserItemsProxy *AwardUserItem(UBrainCloudWrapper *brainCloudWrapper, const FString &defId, int quantity, bool includeDef);

UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Utils")
static UBCUtilsProxy *ToEpochTime(UBrainCloudWrapper *brainCloudWrapper, FDateTime dateTime);

UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Utils")
static UBCUtilsProxy *ToDateTimeFromEpoch(UBrainCloudWrapper *brainCloudWrapper, long intDate);

UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Utils")
static UBCUtilsProxy *ToDateTimeOffsetFromEpoch(UBrainCloudWrapper *brainCloudWrapper, long intDate);

};
