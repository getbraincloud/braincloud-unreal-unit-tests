// Copyright 2018 bitHeads, Inc. All Rights Reserved.


#include "BrainCloudComms.h"
#include "BCClientPluginPrivatePCH.h"
#include "IServerCallback.h"
#include "IEventCallback.h"
#include "IRewardCallback.h"
#include "IFileUploadCallback.h"
#include "IGlobalErrorCallback.h"
#include "INetworkErrorCallback.h"
#include "ServerCall.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "BrainCloudWrapper.h"
#include "BrainCloudClient.h"
#include "BCFileUploader.h"

#include "BCBlueprintRestCallProxyBase.h"

#include "ReasonCodes.h"
#include "HttpCodes.h"

BrainCloudComms::BrainCloudComms(BrainCloudClient *client) : _client(client)
{
	SetPacketTimeoutsToDefault();
	FHttpModule::Get().SetHttpTimeout(30);
}

BrainCloudComms::~BrainCloudComms()
{
	DeregisterEventCallback();
	DeregisterRewardCallback();
	DeregisterFileUploadCallback();
	DeregisterGlobalErrorCallback();
	DeregisterNetworkErrorCallback();
}

void BrainCloudComms::Initialize(const FString &serverURL, const FString &secretKey, const FString &appId)
{
	_isInitialized = true;
	_serverUrl = serverURL;
	_secretKey = secretKey;
	_appId = appId;
	_secretMap.Emplace(appId, secretKey);

	_uploadUrl = _serverUrl;
	FString suffix = "/dispatcherv2";
	if(_uploadUrl.EndsWith(suffix))
	{
		_uploadUrl.RemoveFromEnd(TEXT("/dispatcherv2"));
	}
	while(_uploadUrl.Len() > 0 && _uploadUrl.EndsWith("/"))                         
	{
		_uploadUrl = _uploadUrl.Mid(0, _uploadUrl.Len() - 1);
	}

	_uploadUrl += TEXT("/uploader");
}

void BrainCloudComms::InitializeWithApps(const FString &serverURL, const TMap<FString, FString> &secretMap, const FString &appId)
{
	//refresh the map
	_secretMap.Empty();
	for (auto It = secretMap.CreateConstIterator(); It; ++It)
	{
		_secretMap.Emplace(It.Key(), It.Value());
	}

	FString secretKey = "MISSING";
	if (_secretMap.Contains(appId))
	{
		secretKey = secretMap[appId];
	}

	Initialize(serverURL, secretKey, appId);
}

void BrainCloudComms::SetPacketTimeoutsToDefault()
{
    _packetTimeouts.Empty();
	_packetTimeouts.Add(15);
	_packetTimeouts.Add(20);
	_packetTimeouts.Add(35);
	_packetTimeouts.Add(50);
}

void BrainCloudComms::AddToQueue(ServerCall *serverCall)
{
	if (!_isInitialized)
		UE_LOG(LogBrainCloudComms, Error, TEXT("Attempted to send request but client is not initialized!"));

	TSharedRef<ServerCall> sc = MakeShareable(serverCall);

	_queueMutex.Lock();
	_messageQueue.AddHead(sc);
	_queueMutex.Unlock();
}

void BrainCloudComms::InsertEndOfMessageBundleMarker()
{
	_queueMutex.Lock();
	int32 queueCount = _messageQueue.Num();
	_queueMutex.Unlock();

	if (queueCount <= 0)
		return;

	_queueMutex.Lock();
	_messageQueue.GetHead()->GetValue()->setIsEndOfBundle(true);
	_queueMutex.Unlock();
}

void BrainCloudComms::RegisterEventCallback(UBCBlueprintRestCallProxyBase *callback)
{
	callback->AddToRoot();
	m_registeredRestBluePrintCallbacks.Emplace(ServiceName::Event.getValue(), callback);
}

void BrainCloudComms::DeregisterEventCallback()
{
	FString serviceName = ServiceName::Event.getValue();
	if (m_registeredRestBluePrintCallbacks.Contains(serviceName))
	{
		m_registeredRestBluePrintCallbacks[serviceName]->RemoveFromRoot();
		m_registeredRestBluePrintCallbacks.Remove(serviceName);
	}

	_eventCallback = nullptr;
}

void BrainCloudComms::RegisterRewardCallback(UBCBlueprintRestCallProxyBase *callback)
{
	callback->AddToRoot();
	m_registeredRestBluePrintCallbacks.Emplace("reward", callback);
}

void BrainCloudComms::DeregisterRewardCallback()
{
	FString serviceName = TEXT("reward");
	if (m_registeredRestBluePrintCallbacks.Contains(serviceName))
	{
		m_registeredRestBluePrintCallbacks[serviceName]->RemoveFromRoot();
		m_registeredRestBluePrintCallbacks.Remove(serviceName);
	}

	_rewardCallback = nullptr;
}

void BrainCloudComms::RegisterFileUploadCallback(UBCBlueprintRestCallProxyBase *callback)
{
	callback->AddToRoot();
	m_registeredRestBluePrintCallbacks.Emplace(ServiceName::File.getValue(), callback);
}

void BrainCloudComms::DeregisterFileUploadCallback()
{
	FString serviceName = ServiceName::File.getValue();
	if (m_registeredRestBluePrintCallbacks.Contains(serviceName))
	{
		m_registeredRestBluePrintCallbacks[serviceName]->RemoveFromRoot();
		m_registeredRestBluePrintCallbacks.Remove(serviceName);
	}

	_fileUploadCallback = nullptr;
}

void BrainCloudComms::RegisterGlobalErrorCallback(UBCBlueprintRestCallProxyBase *callback)
{
	callback->AddToRoot();
	m_registeredRestBluePrintCallbacks.Emplace("globalError", callback);
}

void BrainCloudComms::DeregisterGlobalErrorCallback()
{
	FString serviceName = TEXT("globalError");
	if (m_registeredRestBluePrintCallbacks.Contains(serviceName))
	{
		m_registeredRestBluePrintCallbacks[serviceName]->RemoveFromRoot();
		m_registeredRestBluePrintCallbacks.Remove(serviceName);
	}

	_globalErrorCallback = nullptr;
}

void BrainCloudComms::RegisterNetworkErrorCallback(UBCBlueprintRestCallProxyBase *callback)
{
	callback->AddToRoot();
	m_registeredRestBluePrintCallbacks.Emplace("networkError", callback);
}

void BrainCloudComms::DeregisterNetworkErrorCallback()
{
	FString serviceName = TEXT("networkError");
	if (m_registeredRestBluePrintCallbacks.Contains(serviceName))
	{
		m_registeredRestBluePrintCallbacks[serviceName]->RemoveFromRoot();
		m_registeredRestBluePrintCallbacks.Remove(serviceName);
	}

	_networkErrorCallback = nullptr;
}

BrainCloudComms::PacketRef BrainCloudComms::BuildPacket()
{
	PacketRef packet = MakeShareable(new TArray<TSharedRef<ServerCall>>());

	_queueMutex.Lock();

	auto nextNode = _messageQueue.GetTail();
	while (nextNode != nullptr)
	{
		TSharedRef<ServerCall> message = nextNode->GetValue();

		if (message->getOperation() == ServiceOperation::Authenticate)
		{
			message->setIsEndOfBundle(true);
			_messageQueue.RemoveNode(nextNode);
			_messageQueue.AddTail(message);
			break;
		}

		if (message->getIsEndOfBundle() == true)
		{
			break;
		}

		nextNode = nextNode->GetPrevNode();
	}

	while (_messageQueue.Num() != 0 && packet->Num() < _maxBundleMessages)
	{
		auto tailNode = _messageQueue.GetTail();
		TSharedRef<ServerCall> message = tailNode->GetValue();
		_messageQueue.RemoveNode(tailNode);
		packet->Add(message);
		if (message->getIsEndOfBundle() == true)
		{
			break;
		}
	}
	_queueMutex.Unlock();

	return packet;
}

BrainCloudComms::PacketRef BrainCloudComms::BuildPacket(TSharedRef<ServerCall> sc)
{
	PacketRef packet = MakeShareable(new TArray<TSharedRef<ServerCall>>());
	packet->Add(sc);
	return packet;
}

#if ENGINE_MINOR_VERSION > 25
TSharedRef<IHttpRequest,ESPMode::ThreadSafe> BrainCloudComms::SendPacket(PacketRef packet)
#else
TSharedRef<IHttpRequest> BrainCloudComms::SendPacket(PacketRef packet)
#endif
{
	#if ENGINE_MINOR_VERSION > 25
	TSharedRef<IHttpRequest,ESPMode::ThreadSafe> httpRequest = FHttpModule::Get().CreateRequest();
	#else
	TSharedRef<IHttpRequest> httpRequest = FHttpModule::Get().CreateRequest();
	#endif


	FString packetIdStr = FString::FormatAsNumber(_packetId);
	_currentPacket = packet;

	httpRequest->SetURL(_serverUrl);
	httpRequest->SetVerb(TEXT("POST"));
	httpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	httpRequest->SetHeader(TEXT("X-Braincloud-PacketId"), packetIdStr);

	FString dataString = GetDataString(packet, _packetId++);
	if (_isLoggingEnabled)
		UE_LOG(LogBrainCloudComms, Log, TEXT("Sending request:%s\n"), *dataString);

	httpRequest->SetContentAsString(dataString);

	if (_secretKey.Len() > 0)
	{
		FString secret = dataString + _secretKey;
		FTCHARToUTF8 utf8_str(*secret);
		int32 len = utf8_str.Length();
		FString secretHeader = FMD5::HashBytes((const uint8 *)utf8_str.Get(),(uint64)len);
		httpRequest->SetHeader(TEXT("X-SIG"), secretHeader);
	}

	httpRequest->SetHeader(TEXT("X-APPID"), _appId);

	httpRequest->ProcessRequest();
	_requestSentTime = FPlatformTime::Seconds();
	return httpRequest;
}

void BrainCloudComms::ResendActivePacket()
{
	if (!_activeRequest.IsValid())
		return;
	#if ENGINE_MINOR_VERSION > 25
	TSharedRef<IHttpRequest,ESPMode::ThreadSafe> httpRequest = FHttpModule::Get().CreateRequest();
	#else
	TSharedRef<IHttpRequest> httpRequest = FHttpModule::Get().CreateRequest();
	#endif

	httpRequest->SetURL(_serverUrl);
	httpRequest->SetVerb(TEXT("POST"));
	httpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	httpRequest->SetHeader(TEXT("X-Braincloud-PacketId"), _activeRequest->GetHeader(TEXT("X-Braincloud-PacketId")));

	httpRequest->SetContent(_activeRequest->GetContent());
	httpRequest->SetHeader(TEXT("X-SIG"), _activeRequest->GetHeader(TEXT("X-SIG")));
	httpRequest->SetHeader(TEXT("X-APPID"), _activeRequest->GetHeader(TEXT("X-APPID")));

	httpRequest->ProcessRequest();
	_activeRequest = httpRequest;
	_requestSentTime = FPlatformTime::Seconds();
}

FString BrainCloudComms::GetDataString(PacketRef packet, uint64 packetId)
{
	FString jsonStr;

	TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&jsonStr);

	TArray<TSharedPtr<FJsonValue>> messages;

	for (int32 i = 0; i < packet->Num(); i++)
	{
		TSharedRef<ServerCall> sc = (packet.Get()[i]);
		TSharedRef<FJsonValue> message = MakeShareable(new FJsonValueObject(sc->getPayload()));
		messages.Add(message);
	}

	TSharedRef<FJsonObject> jsonDataObject = MakeShareable(new FJsonObject());
	jsonDataObject->SetArrayField("messages", messages);
	jsonDataObject->SetStringField("sessionId", _sessionId);
	jsonDataObject->SetStringField("gameId", _appId);
	jsonDataObject->SetNumberField("packetId", packetId);

	FJsonSerializer::Serialize(jsonDataObject, writer);
	return jsonStr;
}

void BrainCloudComms::CreateAndSendNextRequestBundle()
{
	_queueMutex.Lock();
	int32 queueCount = _messageQueue.Num();
	_queueMutex.Unlock();

	if (queueCount <= 0)
		return;

	bool isAuth = false;

	if (!_isAuthenticated)
	{
		_queueMutex.Lock();
		auto itr = TDoubleLinkedList<TSharedRef<ServerCall>>::TConstIterator(_messageQueue.GetHead());

		for (; itr; ++itr)
		{
			auto operation = itr->getOperation();
			if (operation == ServiceOperation::Authenticate ||
				operation == ServiceOperation::ResetEmailPassword ||
				operation == ServiceOperation::ResetEmailPasswordAdvanced)
			{
				isAuth = true;
				break;
			}
		}
		_queueMutex.Unlock();
	}

	if (!_killSwitchEngaged)
	{
		if (isAuth || _isAuthenticated)
		{
			_activeRequest = SendPacket(BuildPacket());
		}
		else
		{
			FakeErrorResponse(_statusCodeCache, _reasonCodeCache, _statusMessageCache);
		}
	}
	else
	{
		FakeErrorResponse(900, ReasonCodes::CLIENT_DISABLED, "Client disabled due to repeated errors from a single API call");
	}

	_retryCount = 0;
	_waitingForRetry = false;
}

void BrainCloudComms::RunCallbacks()
{
	if (!_isInitialized || _blockingQueue)
		return;

	if (_activeRequest.IsValid())
	{
		if (_waitingForRetry) //We're waiting to retry
		{
			if (FPlatformTime::Seconds() - _retryWaitStart > _retryWaitTime)
			{
				_waitingForRetry = false;
				ResendActivePacket();
				_retryCount++;
			}
		}
		else
		{
			EHttpRequestStatus::Type status = _activeRequest->GetStatus();
			double elapsedTime = FPlatformTime::Seconds() - _requestSentTime;
			bool isError = false;

			//request was successful
			if (status == EHttpRequestStatus::Succeeded)
			{
				FHttpResponsePtr resp = _activeRequest->GetResponse();
				if (resp.IsValid())
				{
					if (resp->GetResponseCode() == HttpCode::OK)
						HandleResponse(_activeRequest->GetResponse()->GetResponseCode(),
									   _activeRequest->GetResponse()->GetContentAsString());
					else
						isError = true;
				}
			}
			else if (_activeRequest->GetStatus() == EHttpRequestStatus::Processing && elapsedTime > GetRetryTimeoutSeconds(_retryCount)) //request timeout
			{
				if (_isLoggingEnabled)
					UE_LOG(LogBrainCloudComms, Warning, TEXT("Request timed out"));
				isError = true;
			}
			else if (!_waitingForRetry && status == EHttpRequestStatus::Failed)
			{
				if (_isLoggingEnabled)
					UE_LOG(LogBrainCloudComms, Warning, TEXT("Request failed"));
				isError = true;
			}

			if (isError) //request failed
			{
				_activeRequest->CancelRequest();
				if (_retryCount < GetMaxRetryAttempts())
				{
					if (_isLoggingEnabled)
						UE_LOG(LogBrainCloudComms, Warning, TEXT("Retrying...#%d of %d"), _retryCount + 1, GetMaxRetryAttempts() + 1);
					_retryWaitStart = FPlatformTime::Seconds();
					_retryWaitTime = GetRetryTimeoutSeconds(_retryCount) - elapsedTime;

					_waitingForRetry = true;
				}
				else
				{
					if (_isLoggingEnabled)
						UE_LOG(LogBrainCloudComms, Warning, TEXT("Reached max retry limit #%d of %d"), _retryCount + 1, GetMaxRetryAttempts() + 1);
					// if we're doing caching of messages on timeout, kick it in now!
					INetworkErrorCallback *networkErrorCallback = _networkErrorCallback != nullptr ? _networkErrorCallback : m_registeredRestBluePrintCallbacks.Contains("networkError") ? m_registeredRestBluePrintCallbacks["networkError"] : nullptr;

					if (_cacheMessagesOnNetworkError && networkErrorCallback != nullptr)
					{
						if (_isLoggingEnabled)
							UE_LOG(LogBrainCloudComms, Log, TEXT("Caching messages"));
						_blockingQueue = true;
						networkErrorCallback->networkError();
					}
					else
					{
						FHttpResponsePtr resp = _activeRequest->GetResponse();
						if (resp.IsValid())
							HandleResponse(resp->GetResponseCode(), resp->GetContentAsString());
						else
						{
							ReportError(
								_currentPacket.ToSharedRef(),
								HttpCode::CLIENT_NETWORK_ERROR,
								ReasonCodes::CLIENT_NETWORK_ERROR_TIMEOUT,
								"Timeout trying to reach brainCloud server");
						}
					}
				}
			}
		}
	}
	else
	{
		CreateAndSendNextRequestBundle();
	}

	UpdateUploads();
	Heartbeat();
}

void BrainCloudComms::HandleResponse(int32 statusCode, FString responseBody)
{
	if (statusCode == HttpCode::OK)
	{
		if (_isLoggingEnabled)
			UE_LOG(LogBrainCloudComms, Log, TEXT("Got response: %s\n"), *responseBody);

		TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(responseBody);
		TSharedPtr<FJsonObject> jsonPacket = MakeShareable(new FJsonObject());

		bool res = FJsonSerializer::Deserialize(reader, jsonPacket);
		if (res)
		{
			ReportResults(_currentPacket.ToSharedRef(), jsonPacket.ToSharedRef());
			IEventCallback *eventCallback = _eventCallback != nullptr ? _eventCallback : m_registeredRestBluePrintCallbacks.Contains(ServiceName::Event.getValue()) ? m_registeredRestBluePrintCallbacks[ServiceName::Event.getValue()] : nullptr;

			if (eventCallback && jsonPacket->HasField("events"))
			{
				TArray<TSharedPtr<FJsonValue>> events = jsonPacket->GetArrayField("events");
				if (events.Num() > 0)
				{
					TSharedRef<FJsonObject> eventsRoot = MakeShareable(new FJsonObject);
					eventsRoot->SetArrayField("events", events);
					eventCallback->eventCallback(UBrainCloudWrapper::GetJsonString(eventsRoot));
				}
			}
		}
		else //couldnt deserialize the response body
		{
			ReportError(_currentPacket.ToSharedRef(), HttpCode::CLIENT_NETWORK_ERROR, ReasonCodes::JSON_PARSING_ERROR, TEXT("Unable to parse response"));
		}
	}
	else
	{
		ReportError(_currentPacket.ToSharedRef(), statusCode, 0, responseBody);
	}
}

void BrainCloudComms::RetryCachedMessages()
{
	if (_blockingQueue)
	{
		if (_isLoggingEnabled)
			UE_LOG(LogBrainCloudComms, Log, TEXT("Retrying cached messages"));
		_blockingQueue = false;
		_retryCount = 0;
		_waitingForRetry = false;
		ResendActivePacket();
	}
}

void BrainCloudComms::FlushCachedMessages(bool sendApiErrorCallbacks)
{
	if (_isLoggingEnabled)
		UE_LOG(LogBrainCloudComms, Log, TEXT("Flushing cached messages"));

	if (sendApiErrorCallbacks)
	{
		ReportError(
			_currentPacket.ToSharedRef(),
			HttpCode::CLIENT_NETWORK_ERROR,
			ReasonCodes::CLIENT_NETWORK_ERROR_TIMEOUT,
			"Timeout trying to reach brainCloud server");
	}

	_blockingQueue = false;
	_retryCount = 0;
	_waitingForRetry = false;

	_activeRequest = nullptr;
	_currentPacket = nullptr;

	_queueMutex.Lock();
	_messageQueue.Empty();
	_queueMutex.Unlock();
}

void BrainCloudComms::UpdateUploads()
{
	if (_fileUploads.Num() <= 0)
		return;

	int32 count = _fileUploads.Num();

	IFileUploadCallback *fileCallback = _fileUploadCallback != nullptr ? _fileUploadCallback : m_registeredRestBluePrintCallbacks.Contains(ServiceName::File.getValue()) ? m_registeredRestBluePrintCallbacks[ServiceName::File.getValue()] : nullptr;
	for (int32 i = count - 1; i >= 0; --i)
	{
		if (_fileUploads[i]->GetStatus() == BCFileUploader::UPLOAD_STATUS_COMPLETE_SUCCESS)
		{
			if (fileCallback != nullptr)
				fileCallback->fileUploadCompleted(_fileUploads[i]->GetUploadId(), _fileUploads[i]->GetResponse());
			_fileUploads.RemoveAt(i);
		}
		else if (_fileUploads[i]->GetStatus() == BCFileUploader::UPLOAD_STATUS_COMPLETE_FAILED)
		{
			if (fileCallback != nullptr)
				fileCallback->fileUploadFailed(
					_fileUploads[i]->GetUploadId(),
					_fileUploads[i]->GetHttpStatus(),
					_fileUploads[i]->GetErrorReasonCode(),
					_fileUploads[i]->GetResponse());
			_fileUploads.RemoveAt(i);
		}
	}
}

void BrainCloudComms::CancelUpload(const FString &uploadId)
{
	TSharedPtr<BCFileUploader> uploader = FindFileUploader(uploadId);
	if (uploader.IsValid())
		uploader->CancelUpload();
}

float BrainCloudComms::GetUploadProgress(const FString &uploadId)
{
	TSharedPtr<BCFileUploader> uploader = FindFileUploader(uploadId);
	if (uploader.IsValid())
		return uploader->GetProgress();
	return -1.0f;
}

int32 BrainCloudComms::GetUploadBytesTransferred(const FString &uploadId)
{
	TSharedPtr<BCFileUploader> uploader = FindFileUploader(uploadId);
	if (uploader.IsValid())
		return uploader->GetBytesTransferred();
	return -1;
}

int32 BrainCloudComms::GetUploadTotalBytesToTransfer(const FString &uploadId)
{
	TSharedPtr<BCFileUploader> uploader = FindFileUploader(uploadId);
	if (uploader.IsValid())
		return uploader->GetTotalBytesToTransfer();
	return -1;
}

TSharedPtr<BCFileUploader> BrainCloudComms::FindFileUploader(const FString &uploadId)
{
	int32 count = _fileUploads.Num();
	for (int32 i = 0; i < count; ++i)
	{
		if (_fileUploads[i]->GetUploadId() == uploadId)
		{
			return _fileUploads[i];
		}
	}

	if (_isLoggingEnabled)
		UE_LOG(LogBrainCloudComms, Log, TEXT("Could not find Uploader with ID: %s"), *uploadId);
	return nullptr;
}

void BrainCloudComms::FakeErrorResponse(uint32 statusCode, uint32 reasonCode, const FString statusMessage)
{
	PacketRef requestPacket = BuildPacket();
	FString sendString = GetDataString(requestPacket, _packetId);
	if (_isLoggingEnabled)
		UE_LOG(LogBrainCloudComms, Log, TEXT("Sending request:%s\n"), *sendString);

	_currentPacket = requestPacket;
	ReportError(requestPacket, statusCode, reasonCode, statusMessage);
}

void BrainCloudComms::ReportResults(PacketRef requestPacket, TSharedRef<FJsonObject> responsePacket)
{
	TArray<TSharedPtr<FJsonValue>> responses = responsePacket->GetArrayField("responses");

	TArray<TSharedPtr<FJsonValue>> apiRewards;
	UObject *tempCallback = nullptr;
	IRewardCallback *rewardCallback = _rewardCallback != nullptr ? _rewardCallback : m_registeredRestBluePrintCallbacks.Contains("reward") ? m_registeredRestBluePrintCallbacks["reward"] : nullptr;

	for (int32 i = 0; i < responses.Num(); i++)
	{
		TSharedRef<ServerCall> sc = (*requestPacket)[i];
		TSharedPtr<FJsonObject> respObj = responses[i]->AsObject();

		uint32 statusCode = respObj->GetNumberField("status");

		IServerCallback *callback = sc->getCallback();

		FString jsonRespStr = UBrainCloudWrapper::GetJsonString(respObj.ToSharedRef());

		if (statusCode == HttpCode::OK || (!_errorCallbackOn202 && statusCode == 202))
		{
			ResetKillSwitch();
			FilterIncomingMessages(sc, respObj.ToSharedRef());
			if (callback != nullptr)
				callback->serverCallback(sc->getService(), sc->getOperation(), *jsonRespStr);
		}
		else
		{
			uint32 reasonCode = 0;
			if (respObj->HasField("reason_code"))
			{
				reasonCode = respObj->GetNumberField("reason_code");
				if (reasonCode == ReasonCodes::PLAYER_SESSION_EXPIRED || reasonCode == ReasonCodes::NO_SESSION || reasonCode == ReasonCodes::PLAYER_SESSION_LOGGED_OUT || sc->getOperation() == ServiceOperation::Logout || sc->getOperation() == ServiceOperation::FullReset)
				{
					_isAuthenticated = false;
					_sessionId = TEXT("");
					_statusCodeCache = statusCode;
					_reasonCodeCache = reasonCode;
					_statusMessageCache = respObj->GetStringField("status_message");
				}
			}

			FString errorString;
			if (_useOldStatusMessage)
			{
				errorString = respObj->GetStringField("status_message");
			}
			else
			{
				errorString = jsonRespStr;
			}

			if (callback != nullptr)
				callback->serverError(sc->getService(), sc->getOperation(), statusCode, reasonCode, *errorString);

			IGlobalErrorCallback *globalErrorCallback = _globalErrorCallback != nullptr ? _globalErrorCallback : m_registeredRestBluePrintCallbacks.Contains("globalError") ? m_registeredRestBluePrintCallbacks["globalError"] : nullptr;

			if (globalErrorCallback != nullptr)
				globalErrorCallback->globalError(sc->getService(), sc->getOperation(), statusCode, reasonCode, *errorString);

			UpdateKillSwitch(sc->getService().getValue(), sc->getOperation().getValue(), statusCode);
		}

		if (rewardCallback && (statusCode == HttpCode::OK || (!_errorCallbackOn202 && statusCode == 202)))
		{
			ServiceName service = sc->getService();
			ServiceOperation operation = sc->getOperation();

			TSharedPtr<FJsonObject> rewards = nullptr;

			// authenticate
			if (service == ServiceName::AuthenticateV2 && operation == ServiceOperation::Authenticate)
			{
				TSharedPtr<FJsonObject> rewardData = respObj->GetObjectField("data")->GetObjectField("rewards");
				if (rewardData->GetObjectField("rewards")->Values.Num() > 0)
				{
					rewards = rewardData;
				}
			}
			// player stat increment or statistics event trigger
			else if ((service == ServiceName::PlayerStatistics && operation == ServiceOperation::Update) || (service == ServiceName::PlayerStatisticsEvent && (operation == ServiceOperation::Trigger || operation == ServiceOperation::TriggerMultiple)))
			{
				TSharedPtr<FJsonObject> data = respObj->GetObjectField("data");
				if (data->GetObjectField("rewards")->Values.Num() > 0)
				{
					rewards = data;
				}
			}

			if (rewards.IsValid())
			{
				TSharedPtr<FJsonObject> apiReward = MakeShareable(new FJsonObject());
				apiReward->SetStringField("service", service.getValue());
				apiReward->SetStringField("operation", operation.getValue());
				apiReward->SetObjectField("rewards", rewards);
				apiRewards.Add(MakeShareable(new FJsonValueObject(apiReward)));
			}
		}
	}

	if (apiRewards.Num() > 0)
	{
		TSharedRef<FJsonObject> rewards = MakeShareable(new FJsonObject());
		rewards->SetArrayField("apiRewards", apiRewards);

		FString jsonString;
		TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&jsonString);

		if (FJsonSerializer::Serialize(rewards, writer))
		{
			rewardCallback->rewardCallback(jsonString);
		}
	}

	_activeRequest = nullptr; //clear the active request
	_currentPacket = nullptr;
}

void BrainCloudComms::ReportError(PacketRef requestPacket, uint32 statusCode, uint32 reasonCode, const FString statusMessage)
{
	TArray<TSharedRef<ServerCall>> arr = requestPacket.Get();
	for (int32 i = 0; i < arr.Num(); i++)
	{
		TSharedRef<ServerCall> sc = arr[i];
		IServerCallback *callback = sc->getCallback();
		if (callback != nullptr)
		{
			FString errorString;
			if (_useOldStatusMessage)
			{
				errorString = statusMessage;
			}
			else
			{
				errorString = UBrainCloudWrapper::buildErrorJson(statusCode, reasonCode, statusMessage);
			}
			callback->serverError(sc->getService(), sc->getOperation(), statusCode, reasonCode, *errorString);

			IGlobalErrorCallback *globalErrorCallback = _globalErrorCallback != nullptr ? _globalErrorCallback : m_registeredRestBluePrintCallbacks.Contains("globalError") ? m_registeredRestBluePrintCallbacks["globalError"] : nullptr;
			if (globalErrorCallback != nullptr)
				globalErrorCallback->globalError(sc->getService(), sc->getOperation(), statusCode, reasonCode, *errorString);
		}
	}

	_activeRequest = nullptr; //clear the active request
	_currentPacket = nullptr;
}

void BrainCloudComms::FilterIncomingMessages(TSharedRef<ServerCall> servercall, TSharedRef<FJsonObject> response)
{
	ServiceName service = servercall->getService();
	ServiceOperation operation = servercall->getOperation();

	TSharedPtr<FJsonValue> Field = response->TryGetField("data");
	const TSharedPtr<FJsonObject>* data = nullptr;
	bool isDataValid = Field->TryGetObject(data);
	// A session id or a profile id could potentially come back in any messages
	//Only allow it in Authenticate and Identity calls.
	if ( isDataValid && (service == ServiceName::AuthenticateV2 || service == ServiceName::Identity))
	{
		(*data)->TryGetStringField("sessionId", _sessionId);

		FString profileIdOut;
		(*data)->TryGetStringField("profileId", profileIdOut);

		if (!profileIdOut.IsEmpty())
		{
			_client->getAuthenticationService()->setProfileId(profileIdOut);
		}

		FString appIdOut;
		(*data)->TryGetStringField("switchToAppId", appIdOut);
		if (!appIdOut.IsEmpty())
		{
			_appId = (*data)->GetStringField("switchToAppId");

			//update the secret key
			_secretKey = "MISSING";
			if (_secretMap.Contains(_appId))
			{
				_secretKey = _secretMap[_appId];
			}
		}
	}

	if (service == ServiceName::AuthenticateV2 && operation == ServiceOperation::Authenticate)
	{
		_isAuthenticated = true;
		ResetErrorCache();

		if (isDataValid)
		{
			if (_heartbeatInterval == 0)
			{
				int32 sessionTimeout = (*data)->GetIntegerField("playerSessionExpiry");
				sessionTimeout = (int32)((double)sessionTimeout * 0.85);

				// minimum 30 secs
				_heartbeatInterval = sessionTimeout;
				_heartbeatInterval *= 1000; //to ms
			}

			_maxBundleMessages = (*data)->GetNumberField("maxBundleMsgs");

			if ((*data)->HasField("maxKillCount"))
				_killSwitchThreshold = (*data)->GetNumberField("maxKillCount");

			//set player name
			FString name = (*data)->GetStringField("playerName");
			_client->getPlayerStateService()->setUserName(name);
		}
	}
	else if (service == ServiceName::PlayerState &&
			 (operation == ServiceOperation::FullReset || operation == ServiceOperation::Logout))
	{
		_isAuthenticated = false;
		_sessionId = TEXT("");
		ResetErrorCache();
		_client->getAuthenticationService()->clearSavedProfileId();
		_client->getPlayerStateService()->setUserName(TEXT(""));
	}
	else if (service == ServiceName::PlayerState && operation == ServiceOperation::UpdateName)
	{
		if (isDataValid)
		{
			FString name = (*data)->GetStringField("playerName");
			_client->getPlayerStateService()->setUserName(name);
		}
	}
	else if (service == ServiceName::File && operation == ServiceOperation::PrepareUserUpload)
	{
		if (isDataValid)
		{
			TSharedPtr<FJsonObject> fileInfo = (*data)->GetObjectField("fileDetails");

			TSharedRef<BCFileUploader> uploader = MakeShareable(
				new BCFileUploader(
					_uploadLowTransferRateTimeout,
					_uploadLowTransferRateThreshold,
					_uploadOverallTimeout,
					_isLoggingEnabled));

			FString localPath = fileInfo->GetStringField("localPath");
			FString uploadId = fileInfo->GetStringField("uploadId");

			_fileUploads.Add(uploader);
			uploader->UploadFile(localPath, _sessionId, uploadId, _uploadUrl);
		}
	}
}

void BrainCloudComms::ResetCommunication()
{
	_queueMutex.Lock();
	_messageQueue.Empty();
	_queueMutex.Unlock();
	_isAuthenticated = false;
	_sessionId = TEXT("");
	_packetId = 0;
	ResetErrorCache();
	_waitingForRetry = false;

	if (_activeRequest.IsValid())
		_activeRequest->CancelRequest();
	_activeRequest = nullptr;
	_currentPacket = nullptr;

	_blockingQueue = false;
}

void BrainCloudComms::ResetErrorCache()
{
	_statusCodeCache = HttpCode::FORBIDDEN;
	_reasonCodeCache = ReasonCodes::NO_SESSION;
	_statusMessageCache = TEXT("No session");
}

void BrainCloudComms::UpdateKillSwitch(const FString &service, const FString &operation, int32 statusCode)
{
	if (statusCode == 900)
		return;

	if (_killSwitchService.IsEmpty())
	{
		_killSwitchService = service;
		_killSwitchOperation = operation;
		_killSwitchErrorCount++;
	}
	else if (service == _killSwitchService && operation == _killSwitchOperation)
		_killSwitchErrorCount++;

	if (!_killSwitchEngaged && _killSwitchErrorCount >= _killSwitchThreshold)
	{
		_killSwitchEngaged = true;
		if (_isLoggingEnabled)
			UE_LOG(LogBrainCloudComms, Error, TEXT("Client disabled due to repeated errors from a single API call: %s | %s"), *service, *operation);
	}
}

void BrainCloudComms::ResetKillSwitch()
{
	_killSwitchErrorCount = 0;
	_killSwitchService = "";
	_killSwitchOperation = "";
}

void BrainCloudComms::Heartbeat()
{
	if (_isAuthenticated && FPlatformTime::Seconds() - _requestSentTime > _heartbeatInterval)
	{
		TSharedRef<FJsonObject> val = MakeShareable(new FJsonObject());
		ServerCall *sc = new ServerCall(ServiceName::HeartBeat, ServiceOperation::Read, val, nullptr);
		AddToQueue(sc);
	}
}

bool BrainCloudComms::ShouldRetryPacket()
{
	TArray<TSharedRef<ServerCall>> arr = *_currentPacket.Get();
	for (int32 i = 0; i < arr.Num(); i++)
	{
		TSharedRef<ServerCall> sc = arr[i];

		if (arr[i]->getService() == ServiceName::AuthenticateV2 && (arr[i]->getOperation() == ServiceOperation::Authenticate))
		{
			return false;
		}
	}
	return true;
}

double BrainCloudComms::GetRetryTimeoutSeconds(int16 retryAttempt)
{
	if (!ShouldRetryPacket())
	{
		return _authenticationTimeout;
	}

	return _packetTimeouts[retryAttempt >= _packetTimeouts.Num() ? _packetTimeouts.Num() - 1 : retryAttempt];
}

int16 BrainCloudComms::GetMaxRetryAttempts()
{
	return ShouldRetryPacket() ? (int16)_packetTimeouts.Num() - 1 : 0;
}