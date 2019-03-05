// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCFileProxy.generated.h"

UCLASS(MinimalAPI)
class UBCFileProxy : public UBCBlueprintCallProxyBase
{
    GENERATED_BODY()

  public:
    UBCFileProxy(const FObjectInitializer &ObjectInitializer);

    /**
    * Method returns the server time in UTC. This is in UNIX millis time format.
    * For instance 1396378241893 represents 2014-04-01 2:50:41.893 in GMT-4.
    *
    * Service Name - Time
    * Service Operation - Read
    */

    /**
    * Prepares a user file upload. On success the file will begin uploading
    * to the brainCloud server. To be informed of success/failure of the upload
    * register an IFileUploadCallback with the BrainCloudClient class.
    *
    * Param - cloudPath  The desired cloud path of the file
    * Param - cloudFilename  The desired cloud filename of the file
    * Param - shareable  True if the file is shareable.
    * Param - replaceIfExists  Whether to replace file if it exists
    * Param - localPath  The path and filename of the local file
    * Param - callback  The method to be invoked when the server response is received
    * Return - A bool which is false if the file cannot be found, or file size cannot be determind.
    *
    * Significant error codes:
    * 40429 - File maximum file size exceeded
    * 40430 - File exists, replaceIfExists not set
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|File")
    static UBCFileProxy *UploadFile(
        UBrainCloudWrapper *brainCloudWrapper,
        const FString &cloudPath,
        const FString &cloudFilename,
        bool shareable,
        bool replaceIfExists,
        const FString &localPath);

    /**
    * List user files from the given cloud path
    *
    * @param cloudPath File path
    * @param recurse Whether to recurse into sub-directories
    * @param callback The method to be invoked when the server response is received
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|File")
    static UBCFileProxy *ListUserFiles(UBrainCloudWrapper *brainCloudWrapper, const FString &cloudPath, bool recurse);

    /**
    * Deletes a single user file.
    *
    * @param cloudPath File path
    * @param cloudFilename name of file
    * @param callback The method to be invoked when the server response is received
    *
    * Significant error codes:
    * 40431 - Cloud storage service error
    * 40432 - File does not exist
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|File")
    static UBCFileProxy *DeleteUserFile(UBrainCloudWrapper *brainCloudWrapper, const FString &cloudPath, const FString &cloudFilename);

    /**
    * Delete multiple user files
    *
    * @param cloudPath File path
    * @param recurse Whether to recurse into sub-directories
    * @param callback The method to be invoked when the server response is received
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|File")
    static UBCFileProxy *DeleteUserFiles(UBrainCloudWrapper *brainCloudWrapper, const FString &cloudPath, bool recurse);

    /**
	* Returns the CDN url for a file object
	*
	* Param - cloudPath File path
	* Param - cloudFileName File name
	*/
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|File")
    static UBCFileProxy *GetCDNUrl(UBrainCloudWrapper *brainCloudWrapper, const FString &cloudPath, const FString &cloudFileName);

    /**
    * Method cancels an upload. If an IFileUploadCallback has been registered with the BrainCloudClient class,
    * the fileUploadFailed callback method will be called once the upload has been canceled.
    *
    * @param uploadId The id of the upload
    */
    UFUNCTION(BlueprintCallable, Category = "BrainCloud|File")
    static void CancelUpload(UBrainCloudWrapper *brainCloudWrapper, const FString &uploadId);

    /**
    * Returns the progress of the given upload from 0.0 to 1.0
    * or -1 if upload not found.
    *
    * @param uploadId The id of the upload
    * @return A progress from 0.0 to 1.0 or -1 if upload not found.
    */
    UFUNCTION(BlueprintCallable, Category = "BrainCloud|File")
    static float GetUploadProgress(UBrainCloudWrapper *brainCloudWrapper, const FString &uploadId);

    /**
    * Returns the number of bytes uploaded or -1 if upload not found.
    *
    * @param uploadId The id of the upload
    * @returns The number of bytes uploaded or -1 if upload not found.
    */
    UFUNCTION(BlueprintCallable, Category = "BrainCloud|File")
    static int32 GetUploadBytesTransferred(UBrainCloudWrapper *brainCloudWrapper, const FString &uploadId);

    /**
    * Returns the total number of bytes that will be uploaded or -1 if upload not found.
    *
    * @param uploadId The id of the upload
    * @returns The total number of bytes that will be uploaded or -1 if upload not found.
    */
    UFUNCTION(BlueprintCallable, Category = "BrainCloud|File")
    static int32 GetUploadTotalBytesToTransfer(UBrainCloudWrapper *brainCloudWrapper, const FString &uploadId);
};
