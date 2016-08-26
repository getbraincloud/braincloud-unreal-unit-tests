// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BCS3HandlingProxy.generated.h"

UCLASS(MinimalAPI)
class UBCS3HandlingProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
    GENERATED_BODY()

public:
    UBCS3HandlingProxy(const FObjectInitializer& ObjectInitializer);

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
        static UBCS3HandlingProxy* GetUpdatedFiles(FString category, FString fileDetails);


    /*
    * Retrieves the details of custom files stored on the server
    *
    * Service Name - S3Handling
    * Service Operation - GetFileList
    *
    * Param - category  Category of files to retrieve
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|S3 Handling")
        static UBCS3HandlingProxy* GetFileList(FString category);

	/**
	* Returns the CDN url for a file
	*
	* Param - fileId ID of file
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|S3 Handling")
		static UBCS3HandlingProxy* GetCDNUrl(const FString& fileId);

    //Response delegates
    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnFailure;

protected:
    // IServerCallback interface
    void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
    void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
    // End of IServerCallback interface
};
