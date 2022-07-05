// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BrainCloudWrapper.h"
#include "BCGlobalAppProxy.generated.h"

UCLASS(MinimalAPI)
class UBCGlobalAppProxy : public UBCBlueprintCallProxyBase
{
  GENERATED_BODY()

public:
  UBCGlobalAppProxy(const FObjectInitializer &ObjectInitializer);

  /**
    * Read game's global properties
    *
    * Service Name - GlobalApp
    * Service Operation - ReadProperties
    */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global App")
  static UBCGlobalAppProxy *ReadProperties(UBrainCloudWrapper *brainCloudWrapper);

  /**
  * Returns a list of properties, identified by the propertyIds provided.
  * If a property from the list isn't found, it just isn't returned (no error).
  *
  * Service Name - GlobalApp
  * Service Operation - ReadSelectedProperties
  *
  * @param - in_propertyIds Specifies which property to return
  */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global App")
  static UBCGlobalAppProxy *ReadSelectedProperties(const TArray<FString>& in_propertyIds, UBrainCloudWrapper *brainCloudWrapper);

  /**
  * Returns a list of properties, identified by the categories provided.
  * If a category from the list isn't found, it just isn't returned (no error).
  *
  * Service Name - GlobalApp
  * Service Operation - ReadPropertiesInCategories
  *
  * @param - in_categories Specifies which category to return
  */
  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global App")
  static UBCGlobalAppProxy *ReadPropertiesInCategories(const TArray<FString>& in_categories, UBrainCloudWrapper *brainCloudWrapper);
};
