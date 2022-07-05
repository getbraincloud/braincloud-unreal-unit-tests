// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCFileUploader.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudWrapper.h"

#include "ReasonCodes.h"
#include "HttpCodes.h"

BCFileUploader::BCFileUploader(int32 lowTransferRateTimeoutSecs, int32 lowTransferRateThresholdBytes, int32 overallTimeoutSecs, bool loggingEnabled) 
: _isLoggingEnabled(loggingEnabled)
, _lowTransferRateTimeout(lowTransferRateTimeoutSecs)    
, _lowTransferRateThreshold(lowTransferRateThresholdBytes)  
, _overallTimeout(overallTimeoutSecs)
{
    _status = UPLOAD_STATUS_PENDING;
}

BCFileUploader::~BCFileUploader()
{
}

bool BCFileUploader::UploadFile(FString &filePath, FString &sessionId, FString &fileUploadId, FString &uploadUrl)
{
    if (!FPaths::FileExists(filePath))
    {
        UE_LOG(LogBrainCloudComms, Error, TEXT("Failed uploading file at '%s': File not found\n"), *filePath);
        return false;
    }

    _uploadId = fileUploadId;

    TArray<uint8> fileData;
    FFileHelper::LoadFileToArray(fileData, *filePath);
    _totalBytesToTransfer = fileData.Num();
    _fileName = FPaths::GetCleanFilename(filePath);

    bool useMultipart = false;
    if (useMultipart)
    {
        FString boundary = FGuid::NewGuid().ToString();
        TArray<uint8> payload = CreateContent(boundary, sessionId, fileUploadId, _fileName, fileData);

        _request = FHttpModule::Get().CreateRequest();

        _request->SetURL(uploadUrl);
        _request->SetVerb(TEXT("POST"));
        _request->SetHeader(TEXT("Content-Type"), FString::Printf(TEXT("multipart/form-data; boundary=%s"), *boundary));
        _request->SetContent(payload);
    }
    else
    {
        _request = FHttpModule::Get().CreateRequest();
        FString url = uploadUrl;
        url += "?uploadId=" + _uploadId;
        url += "&sessionId=" + sessionId;

        _request->SetURL(url);
        _request->SetVerb(TEXT("PUT"));
        _request->SetHeader(TEXT("Content-Type"), "application/octet-stream");
        _request->SetContent(fileData);
    }

    _request->OnProcessRequestComplete().BindRaw(this, &BCFileUploader::OnProcessRequestComplete);
    _request->OnRequestProgress().BindRaw(this, &BCFileUploader::OnRequestProgress);

    _request->ProcessRequest();
    if (_isLoggingEnabled)
        UE_LOG(LogBrainCloudComms, Log, TEXT("Uploading file '%s'\n"), *_fileName);
    _status = UPLOAD_STATUS_UPLOADING;

    _startTime = FPlatformTime::Seconds();
    _lastTimestamp = _startTime;
    return true;
}

void BCFileUploader::CancelUpload()
{
    _request->CancelRequest();

    FString message = FString::Printf(TEXT("Upload of %s canceled by user"), *_fileName);
    ReportError(HttpCode::CLIENT_NETWORK_ERROR, ReasonCodes::CLIENT_UPLOAD_FILE_CANCELLED, message);

    if (_isLoggingEnabled)
        UE_LOG(LogBrainCloudComms, Log, TEXT("Upload of %s canceled by user"), *_fileName);
}

void BCFileUploader::OnProcessRequestComplete(FHttpRequestPtr request, FHttpResponsePtr response, bool bWasSuccessful)
{
    if (bWasSuccessful)
    {
        _response = response->GetContentAsString();
        _statusCode = response->GetResponseCode();
        _status = UPLOAD_STATUS_COMPLETE_SUCCESS;
    }
    else
    {
        _status = UPLOAD_STATUS_COMPLETE_FAILED;
        _reasonCode = ReasonCodes::CLIENT_UPLOAD_FILE_UNKNOWN;
    }
}

void BCFileUploader::OnRequestProgress(FHttpRequestPtr request, int32 bytesSent, int32 bytesReceived)
{
    double time = FPlatformTime::Seconds() - _lastTimestamp;
    double rate = (bytesSent - _bytesTransferred) / time;
    rate < _lowTransferRateThreshold ? _timeUnderTransferRate += time : _timeUnderTransferRate = 0.0;
    _lastTimestamp = FPlatformTime::Seconds();

    _bytesTransferred = bytesSent;
    _progress = (float)_bytesTransferred / (float)_totalBytesToTransfer;

    if (_timeUnderTransferRate > _lowTransferRateTimeout ||
        FPlatformTime::Seconds() - _startTime > _overallTimeout)
    {
        FString message = FString::Printf(TEXT("Upload of %s timed out"), *_fileName);
        ReportError(HttpCode::CLIENT_NETWORK_ERROR, ReasonCodes::CLIENT_UPLOAD_FILE_TIMED_OUT, message);

        UE_LOG(LogBrainCloudComms, Error, TEXT("%s"), *message);
        _request->CancelRequest();
    }
}

TArray<uint8> BCFileUploader::CreateContent(FString &boundary, FString &sessionId, FString &fileUploadId, FString &fileName, TArray<uint8> &data)
{
    FString boundaryLine = FString::Printf(TEXT("--%s\r\n"), *boundary);

    FString content = boundaryLine;
    content += TEXT("Content-Disposition: form-data; name=\"sessionId\"\r\n\r\n");
    content += FString::Printf(TEXT("%s\r\n"), *sessionId);

    content += boundaryLine;
    content += TEXT("Content-Disposition: form-data; name=\"uploadId\"\r\n\r\n");
    content += FString::Printf(TEXT("%s\r\n"), *fileUploadId);

    content += boundaryLine;
    content += TEXT("Content-Disposition: form-data; name=\"fileSize\"\r\n\r\n");
    content += FString::Printf(TEXT("%d\r\n"), data.Num());

    content += boundaryLine;
    content += FString::Printf(TEXT("Content-Disposition: form-data; name=\"uploadFile\"; filename=\"%s\"\r\n"), *fileName);
    content += TEXT("Content-Type: application/octet-stream\r\n\r\n");

    FTCHARToUTF8 Converter(*content);
    TArray<uint8> payload;
    payload.SetNum(Converter.Length());
    FMemory::Memcpy(payload.GetData(), (uint8 *)(ANSICHAR *)Converter.Get(), payload.Num());

    FString finalLine = FString::Printf(TEXT("\r\n--%s--"), *boundary);
    FTCHARToUTF8 NewConverter(*finalLine);
    TArray<uint8> finalPayload;
    finalPayload.SetNum(NewConverter.Length());
    FMemory::Memcpy(finalPayload.GetData(), (uint8 *)(ANSICHAR *)NewConverter.Get(), finalPayload.Num());

    payload.Append(data);
    payload.Append(finalPayload);

    return payload;
}

void BCFileUploader::ReportError(int32 statusCode, int32 reasonCode, FString &statusMessage)
{
    _statusCode = statusCode;
    _reasonCode = reasonCode;
    _response = UBrainCloudWrapper::buildErrorJson(statusCode, reasonCode, statusMessage);
    _status = UPLOAD_STATUS_COMPLETE_FAILED;
}

