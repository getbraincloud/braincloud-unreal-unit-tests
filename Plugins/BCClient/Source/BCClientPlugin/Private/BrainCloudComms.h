// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once
#include "Interfaces/IHttpRequest.h"

class IEventCallback;
class IRewardCallback;
class IFileUploadCallback;
class IGlobalErrorCallback;
class INetworkErrorCallback;
class ServerCall;
class BCFileUploader;
class BrainCloudClient;
class UBCBlueprintRestCallProxyBase;
class BrainCloudComms
{
	typedef TSharedRef<TArray<TSharedRef<ServerCall>>> PacketRef;
	typedef TSharedPtr<TArray<TSharedRef<ServerCall>>> PacketPtr;

  public:
	BrainCloudComms(BrainCloudClient *client);
	~BrainCloudComms();

	void Initialize(const FString &serverURL, const FString &secretKey, const FString &appId);
	void InitializeWithApps(const FString &serverURL, const TMap<FString, FString> &secretMap, const FString &appId);
	void EnableLogging(bool shouldEnable) { _isLoggingEnabled = shouldEnable; };
	bool IsLoggingEnabled() { return _isLoggingEnabled; };

	void AddToQueue(ServerCall *);
	void ClearSessionId() { _sessionId.Empty(); }
	void ResetCommunication();
	void RunCallbacks();
	void Heartbeat();
	void InsertEndOfMessageBundleMarker();

	//Event callback
	void RegisterEventCallback(IEventCallback *eventCallback) { _eventCallback = eventCallback; };
	void RegisterEventCallback(UBCBlueprintRestCallProxyBase *callback);
	void DeregisterEventCallback();

	//Reward callback
	void RegisterRewardCallback(IRewardCallback *rewardCallback) { _rewardCallback = rewardCallback; }
	void RegisterRewardCallback(UBCBlueprintRestCallProxyBase *callback);
	void DeregisterRewardCallback();

	//File upload callback
	void RegisterFileUploadCallback(IFileUploadCallback *fileUploadCallback) { _fileUploadCallback = fileUploadCallback; }
	void RegisterFileUploadCallback(UBCBlueprintRestCallProxyBase *callback);
	void DeregisterFileUploadCallback();

	//Global error callback
	void RegisterGlobalErrorCallback(IGlobalErrorCallback *globalErrorCallback) { _globalErrorCallback = globalErrorCallback; }
	void RegisterGlobalErrorCallback(UBCBlueprintRestCallProxyBase *callback);
	void DeregisterGlobalErrorCallback();

	//Network error callback
	void RegisterNetworkErrorCallback(INetworkErrorCallback *networkErrorCallback) { _networkErrorCallback = networkErrorCallback; }
	void RegisterNetworkErrorCallback(UBCBlueprintRestCallProxyBase *callback);
	void DeregisterNetworkErrorCallback();

	//Getters
	bool IsAuthenticated() { return _isAuthenticated; }
	bool IsInitialized() { return _isInitialized; }
	const FString &GetSessionId() const { return _sessionId; }
	const FString &GetServerUrl() { return _serverUrl; }
	const FString &GetSecretKey() { return _secretKey; }
	const TArray<int32> &GetPacketTimeouts() { return _packetTimeouts; }
	int32 GetAuthenticationPacketTimeout() { return _authenticationTimeout; }
	int32 GetUploadLowTransferRateTimeout() { return _uploadLowTransferRateTimeout; }
	int32 GetUploadLowTransferRateThreshold() { return _uploadLowTransferRateThreshold; }
	int32 GetUploadOverallTimeout() { return _uploadOverallTimeout; }

	//Setters
	void SetServerUrl(const FString &serverUrl) { _serverUrl = serverUrl; }
	void SetSessionId(const FString &sessionId) { _sessionId = sessionId; }
	void SetHeartbeatInterval(int32 heartbeatInterval) { _heartbeatInterval = heartbeatInterval; }
	void SetPacketTimeouts(const TArray<int32> &packetTimeouts) { _packetTimeouts = packetTimeouts; }
	void SetPacketTimeoutsToDefault();
	void SetAuthenticationPacketTimeout(int32 timeoutSecs) { _authenticationTimeout = timeoutSecs; }
	void SetOldStyleStatusMessageErrorCallback(bool useOldStatusMessage) { _useOldStatusMessage = useOldStatusMessage; }
	void SetErrorCallbackOn202Status(bool isError) { _errorCallbackOn202 = isError; }
	void SetUploadLowTransferRateTimeout(int32 timeoutSecs) { _uploadLowTransferRateTimeout = timeoutSecs; }
	void SetUploadLowTransferRateThreshold(int32 bytesPerSec) { _uploadLowTransferRateThreshold = bytesPerSec; }
	void SetUploadOverallTimeout(int32 seconds) { _uploadOverallTimeout = seconds; }
	void SetAuthenticated() { _isAuthenticated = true; }

	//File upload
	void CancelUpload(const FString &fileUploadId);
	float GetUploadProgress(const FString &fileUploadId);
	int32 GetUploadTotalBytesToTransfer(const FString &fileUploadId);
	int32 GetUploadBytesTransferred(const FString &fileUploadId);

	//caching
	void EnableNetworkErrorMessageCaching(bool enabled) { _cacheMessagesOnNetworkError = enabled; }
	void RetryCachedMessages();
	void FlushCachedMessages(bool sendApiErrorCallbacks);

  private:
	void CreateAndSendNextRequestBundle();
	PacketRef BuildPacket();
	PacketRef BuildPacket(TSharedRef<ServerCall> sc);
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION > 25) || ENGINE_MAJOR_VERSION == 5
	TSharedRef<IHttpRequest,ESPMode::ThreadSafe> SendPacket(PacketRef packet);
#else
	TSharedRef<IHttpRequest> SendPacket(PacketRef packet);
#endif
	void ResendActivePacket();
	void FilterIncomingMessages(TSharedRef<ServerCall> servercall, TSharedRef<FJsonObject> response);

	bool ShouldRetryPacket();
	double GetRetryTimeoutSeconds(int16 retry);
	int16 GetMaxRetryAttempts();

	FString GetDataString(PacketRef packet, uint64 packetId);
	void ReportError(PacketRef requestPacket, uint32 statusCode, uint32 reasonCode, const FString statusMessage);
	void ReportResults(PacketRef requestPacket, TSharedRef<FJsonObject> jsonPacket);

	void ResetErrorCache();
	void FakeErrorResponse(uint32 statusCode, uint32 reasonCode, const FString statusMessage);

	//kill switch
	void UpdateKillSwitch(const FString &service, const FString &operation, int32 statusCode);
	void ResetKillSwitch();

	void UpdateUploads();
	TSharedPtr<BCFileUploader> FindFileUploader(const FString &uploadId);

	BrainCloudClient *_client;

	int32 _statusCodeCache = 0;
	int32 _reasonCodeCache = 0;
	FString _statusMessageCache;

	bool _isLoggingEnabled = false;
	bool _isAuthenticated = false;
	bool _isInitialized = false;

	int32 _bundleId = 0;
	FString _sessionId;

	FString _serverUrl;
	FString _secretKey;
	TMap<FString, FString> _secretMap;
	FString _appId;
	FString _uploadUrl;

	IEventCallback *_eventCallback = nullptr;
	IRewardCallback *_rewardCallback = nullptr;
	IFileUploadCallback *_fileUploadCallback = nullptr;
	IGlobalErrorCallback *_globalErrorCallback = nullptr;
	INetworkErrorCallback *_networkErrorCallback = nullptr;
	TMap<FString, UBCBlueprintRestCallProxyBase *> m_registeredRestBluePrintCallbacks;

	uint64 _packetId = 0;

	int32 _heartbeatInterval = 0;
	float _idleTime = 0.0;
	int32 _retryCount = 0;
	TArray<int32> _packetTimeouts;
	int32 _maxBundleMessages = 10;
	int32 _authenticationTimeout = 15;
	bool _useOldStatusMessage = false;
	bool _errorCallbackOn202 = true;

	int32 _uploadLowTransferRateTimeout = 120;
	int32 _uploadLowTransferRateThreshold = 50;
	int32 _uploadOverallTimeout = 120;

	TDoubleLinkedList<TSharedRef<ServerCall>> _messageQueue;
	TArray<TSharedRef<BCFileUploader>> _fileUploads;

	//New!
	void HandleResponse(int32 statusCode, FString responseBody);

	FCriticalSection _queueMutex;
	double _requestSentTime = 0.0;
	bool _waitingForRetry = false;
	double _retryWaitStart = -1.0;
	double _retryWaitTime = -1.0;
	FHttpRequestPtr _activeRequest;
	PacketPtr _currentPacket;

	//caching
	bool _cacheMessagesOnNetworkError = false;
	bool _blockingQueue = false;

	//For kill switch
	int32 _killSwitchThreshold = 11;
	bool _killSwitchEngaged = false;
	int32 _killSwitchErrorCount = 0;
	FString _killSwitchService;
	FString _killSwitchOperation;
};
