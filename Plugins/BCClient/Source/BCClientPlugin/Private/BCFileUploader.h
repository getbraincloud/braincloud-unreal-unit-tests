// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BCFileUploader
{
public:
  enum EFileUploaderStatus
  {
    UPLOAD_STATUS_NONE = 0,
    UPLOAD_STATUS_PENDING = 1,
    UPLOAD_STATUS_UPLOADING = 2,
    UPLOAD_STATUS_COMPLETE_FAILED = 3,
    UPLOAD_STATUS_COMPLETE_SUCCESS = 4
  };

  BCFileUploader(int32 lowTransferRateTimeoutSecs, int32 lowTransferRateThresholdBytes, int32 overallTimeoutSecs, bool loggingEnabled);
  ~BCFileUploader();

  bool UploadFile(FString &filePath, FString &sessionId, FString &fileUploadId, FString &uploadUrl);
  void CancelUpload();

  void EnableLogging(bool loggingEnabled) { _isLoggingEnabled = loggingEnabled; }
  void SetUploadLowTransferRateTimeout(int32 timeoutSecs) { _lowTransferRateTimeout = timeoutSecs; }
  void SetUploadLowTransferRateThreshold(int32 bytesPerSec) { _lowTransferRateThreshold = bytesPerSec; }

  int32 GetBytesTransferred() { return _bytesTransferred; }
  int32 GetTotalBytesToTransfer() { return _totalBytesToTransfer; }
  float GetProgress() { return _progress; }

  EFileUploaderStatus GetStatus() { return _status; }
  const FString &GetResponse() { return _response; }
  int GetHttpStatus() { return _statusCode; }
  int GetErrorReasonCode() { return _reasonCode; }
  const FString &GetUploadId() { return _uploadId; }

  void OnProcessRequestComplete(FHttpRequestPtr request, FHttpResponsePtr response, bool bWasSuccessful);
  void OnRequestProgress(FHttpRequestPtr request, int32 bytesSent, int32 bytesReceived);

private:
  TArray<uint8> CreateContent(FString &boundary, FString &sessionId, FString &fileUploadId, FString &fileName, TArray<uint8> &data);
  void ReportError(int32 statusCode, int32 reasonCode, FString &statusMessage);

  bool _isLoggingEnabled = false;

  int32 _lowTransferRateTimeout = 120;
  int32 _lowTransferRateThreshold = 50;
  int32 _overallTimeout = 120;

  double _lastTimestamp = 0.0;
  double _timeUnderTransferRate = 0.0;
  double _startTime = 0.0;

  int32 _bytesTransferred = -1;
  int32 _totalBytesToTransfer = -1;
  float _progress = -1.0;

  EFileUploaderStatus _status;
  FString _response;
  int32 _statusCode = 0;
  int32 _reasonCode = 0;

  FString _fileName;
  FString _uploadId;
  
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION > 25) || ENGINE_MAJOR_VERSION == 5 
  TSharedPtr<IHttpRequest,ESPMode::ThreadSafe> _request;
#else
  TSharedPtr<IHttpRequest> _request;
#endif

};
