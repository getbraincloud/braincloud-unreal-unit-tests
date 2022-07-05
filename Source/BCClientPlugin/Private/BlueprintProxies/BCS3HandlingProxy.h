// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCS3HandlingProxy.generated.h"

UCLASS(MinimalAPI)
class UBCS3HandlingProxy : public UBCBlueprintCallProxyBase
{
    GENERATED_BODY()

  public:
    UBCS3HandlingProxy(const FObjectInitializer &ObjectInitializer);

    /*
    * Sends an array of file details and returns
    * the details of any of those files that have changed
    *
    * Service Name - S3Handling
    * Service Operation - GetUpdatedFiles
    *
    * Param - category  Category of files on server to compare against
    * Param - fileDetailsJson  An array of file details
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|S3 Handling")
    static UBCS3HandlingProxy *GetUpdatedFiles(UBrainCloudWrapper *brainCloudWrapper, FString category, FString fileDetails);

    /*
    * Retrieves the details of custom files stored on the server
    *
    * Service Name - S3Handling
    * Service Operation - GetFileList
    *
    * Param - category  Category of files to retrieve
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|S3 Handling")
    static UBCS3HandlingProxy *GetFileList(UBrainCloudWrapper *brainCloudWrapper, FString category);

    /**
	* Returns the CDN url for a file
	*
	* Param - fileId ID of file
	*/
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|S3 Handling")
    static UBCS3HandlingProxy *GetCDNUrl(UBrainCloudWrapper *brainCloudWrapper, const FString &fileId);
};
