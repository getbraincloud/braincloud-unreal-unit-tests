#include "OnlineTitleFileInterfaceBrainCloud.h"
#include "OnlineSubsystemBrainCloudPrivatePCH.h"

#include "BrainCloudClient.h"
#include "ServiceOperation.h"
#include "ServiceName.h"
#include "HttpModule.h"

#include "OnlineSubsystemBrainCloud.h"

#include "AssignableServerCallback.h"

FOnlineTitleFileBrainCloud::FOnlineTitleFileBrainCloud(FOnlineSubsystemBrainCloud * InSubsystem)
    : _subsystem(InSubsystem)
{
    _tempFolderPath = FPaths::Combine(FPlatformProcess::UserTempDir(), TEXT("brainCloud_Unreal"));
}

bool FOnlineTitleFileBrainCloud::GetFileContents(const FString & FileName, TArray<uint8>& FileContents)
{
    if (!_cachedFiles.Contains(FileName))
    {
        UE_LOG(LogOnline, Display, TEXT("File %s has not been downloaded, call ReadFile first."), *FileName);
        return false;
    }

    if (FPaths::FileExists(*_cachedFiles.Find(FileName)))
    {
        FileContents.Empty();

        if (!FFileHelper::LoadFileToArray(FileContents, **_cachedFiles.Find(FileName)))
        {
            UE_LOG(LogOnline, Display, TEXT("Error reading file %s from disk."), *FileName);
            return false;
        }
    }
    else
    {
        UE_LOG(LogOnline, Display, TEXT("Error reading file %s, cached file is missing on disk."), *FileName);
        return false;
    }

    return true;
}

bool FOnlineTitleFileBrainCloud::ClearFiles()
{
    DeleteCachedFiles(false);
    return true;
}

bool FOnlineTitleFileBrainCloud::ClearFile(const FString & FileName)
{
    if (_activeRequests.Contains(FileName))
    {
        UE_LOG(LogOnline, Display, TEXT("Unable to clear file %s, read in progress."), *FileName);
        return false;
    }

    for (int32 i = 0; i < _cachedFiles.Num(); i++)
    {
        if (_cachedFiles.Contains(FileName))
        {
            FPlatformFileManager::Get().GetPlatformFile().DeleteFile(**_cachedFiles.Find(FileName));
            break;
        }
    }
    return true;
}

void FOnlineTitleFileBrainCloud::DeleteCachedFiles(bool bSkipEnumerated)
{
    TArray<FString> files = GetAllFilesInDirectory(_tempFolderPath, true);
    IPlatformFile &platformFile = FPlatformFileManager::Get().GetPlatformFile();

    if (!bSkipEnumerated)
    {
        for (int32 i = 0; i < files.Num(); i++)
        {
            platformFile.DeleteFile(*files[i]);
        }
        _cachedFiles.Empty();
    }
    else
    {
        for (int32 i = 0; i < files.Num(); i++)
        {
            FString  fileName = FPaths::GetCleanFilename(files[i]);
            bool isEnumerated = false;

            for (int32 j = 0; j < _cachedFileHeaders.Num(); j++)
            {
                if (FPaths::GetCleanFilename(files[i]) == _cachedFileHeaders[j]->FileName)
                {
                    isEnumerated = true;
                    break;
                }
            }

            if (!isEnumerated)
            {
                platformFile.DeleteFile(*files[i]);
                _cachedFiles.Remove(FPaths::GetCleanFilename(files[i]));
            }
        }
    }
}

bool FOnlineTitleFileBrainCloud::EnumerateFiles(const FPagedQuery & Page)
{
    AssignableServerCallback* cb = _subsystem->GetCallbackObject<AssignableServerCallback>();
    cb->OnSuccessDelegate.AddRaw(this, &FOnlineTitleFileBrainCloud::EnumerateFilesSuccess);
    cb->OnFailDelegate.AddRaw(this, &FOnlineTitleFileBrainCloud::EnumerateFilesFail);

    _subsystem->GetClient()->getS3HandlingService()->getFileList(TEXT(""), cb);
    return true;
}

void FOnlineTitleFileBrainCloud::GetFileList(TArray<FCloudFileHeader>& Files)
{
    for (int32 i = 0; i < _cachedFileHeaders.Num(); ++i)
    {
        Files.Add(*_cachedFileHeaders[i].Get());
    }
}

bool FOnlineTitleFileBrainCloud::ReadFile(const FString & FileName)
{
    //ensure file isnt already being read
    if (_activeRequests.Contains(FileName))
    {
        UE_LOG(LogOnline, Display, TEXT("File %s read already in progress"), *FileName);
        return false;
    }

    //get file info from cache
    TSharedPtr<FCloudFileHeaderBrainCloud> header;

    for (int32 i = 0; i < _cachedFileHeaders.Num(); ++i)
    {
        if (_cachedFileHeaders[i]->FileName == FileName)
        {
            header = _cachedFileHeaders[i];
            break;
        }
    }

    if (!header.IsValid())
    {
        UE_LOG(LogOnline, Display, TEXT("Unable to find file %s in header cache, read aborted."), *FileName);
        return false;
    }

    //Setup HTTP request
    FHttpRequestPtr httpRequest = FHttpModule::Get().CreateRequest();
    httpRequest->SetURL(header->URL);
    httpRequest->SetVerb(TEXT("GET"));
    httpRequest->OnProcessRequestComplete().BindRaw(this, &FOnlineTitleFileBrainCloud::RequestComplete);
    httpRequest->ProcessRequest();

    _activeRequests.Add(header->URL, httpRequest);
    return true;
}

void FOnlineTitleFileBrainCloud::EnumerateFilesSuccess(const FString & jsonData)
{
    _cachedFileHeaders.Empty();

    TArray<TSharedPtr<FJsonValue>> files = FOnlineSubsystemBrainCloud::GetJsonData(jsonData)->GetArrayField("fileDetails");

    for (int32 i = 0; i < files.Num(); ++i)
    {
        FJsonObject* fileObj = files[i]->AsObject().Get();

        TSharedPtr<FCloudFileHeaderBrainCloud> fileHeader = MakeShareable(new FCloudFileHeaderBrainCloud());

        fileHeader->DLName = fileObj->GetStringField("shortName");
        fileHeader->FileName = fileHeader->DLName;
        fileHeader->URL = fileObj->GetStringField("absoluteUrl");
        fileHeader->Hash = fileObj->GetStringField("md5Hash");
        fileHeader->FileSize = fileObj->GetNumberField("fileSize");

        _cachedFileHeaders.Add(fileHeader);
    }

// Unreal Engine Version is >= 4.18 OR in Unreal Engine 5
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 18) || ENGINE_MAJOR_VERSION == 5
    OnEnumerateFilesCompleteDelegates.Broadcast(true, TEXT("FOnlineTitleFileBrainCloud"));
#else
    OnEnumerateFilesCompleteDelegates.Broadcast(false); 
#endif
}

void FOnlineTitleFileBrainCloud::EnumerateFilesFail(int32 returnCode, const FString & jsonData)
{
// Unreal Engine Version is >= 4.18 OR in Unreal Engine 5
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 18) || ENGINE_MAJOR_VERSION == 5
    OnEnumerateFilesCompleteDelegates.Broadcast(false, TEXT("FOnlineTitleFileBrainCloud"));
#else
    OnEnumerateFilesCompleteDelegates.Broadcast(false); 
#endif
}

void FOnlineTitleFileBrainCloud::RequestComplete(FHttpRequestPtr request, FHttpResponsePtr response, bool wasSuccess)
{
    _activeRequests.Remove(request->GetURL());

    TSharedPtr<FCloudFileHeaderBrainCloud> header;

    if (!GetFileHeader(request->GetURL(), header))
    {
        UE_LOG(LogOnline, Display, TEXT("Unable to find file %s in FCloudFileHeader cache, read aborted"), *request->GetURL());
        OnReadFileCompleteDelegates.Broadcast(false, TEXT(""));
        return;
    }

    if (wasSuccess && response->GetResponseCode() < 299)
    {
        FString fullFilePath = FPaths::Combine(*_tempFolderPath, *header->FileName);

        TArray<uint8> content = response->GetContent();

        if (!FFileHelper::SaveArrayToFile(content, *fullFilePath))
        {
            UE_LOG(LogOnline, Display, TEXT("Error saving file %s to %s"), *header->FileName, *fullFilePath);
            OnReadFileCompleteDelegates.Broadcast(false, header->FileName);
            return;
        }

        _cachedFiles.Add(header->FileName, fullFilePath);
    }
    else
    {
        UE_LOG(LogOnline, Display, TEXT("ReadFile failed for %s with code %d "), *header->FileName, response->GetResponseCode());
        OnReadFileCompleteDelegates.Broadcast(false, header->FileName);
        return;
    }

    OnReadFileCompleteDelegates.Broadcast(true, header->FileName);
}

bool FOnlineTitleFileBrainCloud::GetFileHeader(const FString& Url, TSharedPtr<FCloudFileHeaderBrainCloud>& OutHeader)
{
    for (int32 i = 0; i < _cachedFileHeaders.Num(); ++i)
    {
        if (_cachedFileHeaders[i]->URL == Url)
        {
            OutHeader = _cachedFileHeaders[i];
            return true;
        }
    }
    return false;
}

/**
 * Gets all the files in a given directory.
 *
 * @param directory The full path of the directory we want to iterate over.
 * @param fullpath Whether the returned list should be the full file paths or just the filenames.
 * @param onlyFilesStartingWith Will only return filenames starting with this string. Also applies onlyFilesEndingWith if specified.
 * @param onlyFilesEndingWith Will only return filenames ending with this string (it looks at the extension as well!). Also applies onlyFilesStartingWith if specified.
 *
 * @return A list of files (including the extension).
 */
TArray<FString> FOnlineTitleFileBrainCloud::GetAllFilesInDirectory(const FString& directory, const bool fullPath, const FString& onlyFilesStartingWith, const FString& onlyFilesWithExtension)
{
    // Get all files in directory
    TArray<FString> directoriesToSkip;
    IPlatformFile &PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    FLocalTimestampDirectoryVisitor Visitor(PlatformFile, directoriesToSkip, directoriesToSkip, false);
    PlatformFile.IterateDirectory(*directory, Visitor);
    TArray<FString> files;

    for (TMap<FString, FDateTime>::TIterator TimestampIt(Visitor.FileTimes); TimestampIt; ++TimestampIt)
    {
        const FString filePath = TimestampIt.Key();
        const FString fileName = FPaths::GetCleanFilename(filePath);
        bool shouldAddFile = true;

        // Check if filename starts with required characters
        if (!onlyFilesStartingWith.IsEmpty())
        {
            const FString left = fileName.Left(onlyFilesStartingWith.Len());

            if (!(fileName.Left(onlyFilesStartingWith.Len()).Equals(onlyFilesStartingWith)))
                shouldAddFile = false;
        }

        // Check if file extension is required characters
        if (!onlyFilesWithExtension.IsEmpty())
        {
            if (!(FPaths::GetExtension(fileName, false).Equals(onlyFilesWithExtension, ESearchCase::IgnoreCase)))
                shouldAddFile = false;
        }

        // Add full path to results
        if (shouldAddFile)
        {
            files.Add(fullPath ? filePath : fileName);
        }
    }

    return files;
}