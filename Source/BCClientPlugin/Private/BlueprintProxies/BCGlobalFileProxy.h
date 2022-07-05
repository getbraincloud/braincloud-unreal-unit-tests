// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "BCGlobalFileProxy.generated.h"

UCLASS(MinimalAPI)
class UBCGlobalFileProxy : public UBCBlueprintCallProxyBase
{
  GENERATED_BODY()

public:
  UBCGlobalFileProxy(const FObjectInitializer &ObjectInitializer);

    /**
     * Returns information on a file using fileId.
     *
     * Service Name - GlobalFile
     * Service Operation - GetFileInfo
     *
     * @param - fileId - the file's id
     * @param - callback The method to be invoked when the server response is received
     */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global File")
    static UBCGlobalFileProxy *GetFileInfo(UBrainCloudWrapper *brainCloudWrapper, const FString &fileId);
    /**
     * Returns information on a file using path and name.
     *
     * Service Name - GlobalFile
     * Service Operation - GetFileInfoSimple
     *
     * @param - folderPath - the folder path the file is stored at
     * @param - fileId - the file's id
     * @param - callback The method to be invoked when the server response is received
     */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global File")
    static UBCGlobalFileProxy *GetFileInfoSimple(UBrainCloudWrapper *brainCloudWrapper, const FString &fileName, const FString &folderPath);
    /**
     * Return CDN url for file for clients that cannot handle redirect.
     *
     * Service Name - GlobalFile
     * Service Operation - GetGlobalCDNUrl
     *
     * @param - fileId - the file's id
     * @param - callback The method to be invoked when the server response is received
     */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global File")
    static UBCGlobalFileProxy *GetGlobalCDNUrl(UBrainCloudWrapper *brainCloudWrapper, const FString &fileId);
    /**
     * Returns a list of files.
     *
     * Service Name - GlobalFile
     * Service Operation - GetGlobalFileList
     *
     * @param - folderPath - the folder path the file is stored at
     * @param - recurse - does it recurse?
     * @param - callback The method to be invoked when the server response is received
     */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Global File")
    static UBCGlobalFileProxy *GetGlobalFileList(UBrainCloudWrapper *brainCloudWrapper, const FString &folderPath, bool recurse);
};
