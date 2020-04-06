// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "Interfaces/OnlineTitleFileInterface.h"
#include "OnlineSubsystemBrainCloud.h"

#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

/** Holds metadata about a given downloadable file */
struct FCloudFileHeaderBrainCloud : public FCloudFileHeader
{
    /** URL for the file on the server */
    FString URL;

    FCloudFileHeaderBrainCloud() :
        FCloudFileHeader()
    {}

    FCloudFileHeaderBrainCloud(const FString& InFileName, const FString& InDLName, int32 InFileSize, const FString& InURL) :
        FCloudFileHeader(InFileName, InDLName, InFileSize),
        URL(InURL)
    {}
};

class FOnlineTitleFileBrainCloud : public IOnlineTitleFile
{
public:
    /**
    * Constructor
    * @param inSubsystem online subsystem being used
    */
    FOnlineTitleFileBrainCloud(class FOnlineSubsystemBrainCloud* InSubsystem);

    /**
    * Destructor
    */
    virtual ~FOnlineTitleFileBrainCloud() {};

    /**
     * Copies the file data into the specified buffer for the specified file
     *
     * @param FileName the name of the file to read
     * @param FileContents the out buffer to copy the data into
     *
     * @return true if the data was copied, false otherwise
     */
    virtual bool GetFileContents(const FString& FileName, TArray<uint8>& FileContents);

    /**
     * Empties the set of downloaded files if possible (no async tasks outstanding)
     *
     * @return true if they could be deleted, false if they could not
     */
    virtual bool ClearFiles();

    /**
     * Empties the cached data for this file if it is not being downloaded currently
     *
     * @param FileName the name of the file to remove from the cache
     *
     * @return true if it could be deleted, false if it could not
     */
    virtual bool ClearFile(const FString& FileName);

    /**
     * Delete cached files on disk
     *
     * @param bSkipEnumerated if true then only non-enumerated files are deleted
     */
    virtual void DeleteCachedFiles(bool bSkipEnumerated);

    /**
    * Requests a list of available files from the network store
    *
    * @param Page paging info to use for query
    *
    * @return true if the request has started, false if not
    */
    virtual bool EnumerateFiles(const FPagedQuery& Page = FPagedQuery());

    /**
     * Returns the list of files that was returned by the network store
     * 
     * @param Files out array of file metadata
     *
     */
    virtual void GetFileList(TArray<FCloudFileHeader>& Files);

    /**
     * Starts an asynchronous read of the specified file from the network platform's file store
     *
     * @param FileToRead the name of the file to read
     *
     * @return true if the calls starts successfully, false otherwise
     */
    virtual bool ReadFile(const FString& FileName);

private:
    FOnlineSubsystemBrainCloud* _subsystem;
    FString _tempFolderPath;

    TArray<TSharedPtr<FCloudFileHeaderBrainCloud>> _cachedFileHeaders;
    TMap<FString, FHttpRequestPtr> _activeRequests;
    TMap<FString, FString> _cachedFiles;

    bool GetFileHeader(const FString& Url, TSharedPtr<FCloudFileHeaderBrainCloud>& OutHeader);
    TArray<FString> GetAllFilesInDirectory(const FString& directory, const bool fullPath, const FString& onlyFilesStartingWith = TEXT(""), const FString& onlyFilesWithExtension = TEXT(""));

    //BC Callbacks
    void EnumerateFilesSuccess(const FString& jsonData);
    void EnumerateFilesFail(int32 returnCode, const FString& jsonData);

    void RequestComplete(FHttpRequestPtr request, FHttpResponsePtr response, bool wasSuccess);
};

typedef TSharedPtr<FOnlineTitleFileBrainCloud, ESPMode::ThreadSafe> FOnlineTitleFileBrainCloudPtr;
typedef TSharedRef<FOnlineTitleFileBrainCloud, ESPMode::ThreadSafe> FOnlineTitleFileBrainCloudRef;