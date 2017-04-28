// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudComms.h"

#include "IServerCallback.h"
#include "IEventCallback.h"
#include "IRewardCallback.h"
#include "IFileUploadCallback.h"
#include "IGlobalErrorCallback.h"
#include "INetworkErrorCallback.h"
#include "ServerCall.h"
#include "ServiceName.h"
#include "ServiceOperation.h"
#include "BrainCloudClient.h"
#include "BCFileUploader.h"

#include "ReasonCodes.h"
#include "HttpCodes.h"

BrainCloudComms::BrainCloudComms(BrainCloudClient* client) : _client(client)
{
	SetPacketTimeoutsToDefault();
	FHttpModule::Get().SetHttpTimeout(30);
}

BrainCloudComms::~BrainCloudComms()
{
}

void BrainCloudComms::Initialize(const FString& serverURL, const FString& secretKey, const FString& appId)
{
	_isInitialized = true;
	_serverUrl = serverURL;
	_secretKey = secretKey;
	_appId = appId;

	_uploadUrl = _serverUrl;
	_uploadUrl.RemoveFromEnd(TEXT("/dispatcherv2"));
	_uploadUrl += TEXT("/uploader");
}

void BrainCloudComms::SetPacketTimeoutsToDefault()
{
	_packetTimeouts.Empty();
	_packetTimeouts.Add(10);
	_packetTimeouts.Add(10);
	_packetTimeouts.Add(10);
}

void BrainCloudComms::AddToQueue(ServerCall *serverCall)
{
	if (!_isInitialized) UE_LOG(LogBrainCloudComms, Error, TEXT("Attempted to send request but client is not initialized!"));

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

	if (queueCount <= 0) return;

	_queueMutex.Lock();
	_messageQueue.GetHead()->GetValue()->setIsEndOfBundle(true);
	_queueMutex.Unlock();
}

BrainCloudComms::PacketRef BrainCloudComms::BuildPacket()
{
	PacketRef packet = MakeShareable(new TArray<TSharedRef<ServerCall>>());

	_queueMutex.Lock();

	auto nextNode = _messageQueue.GetTail();
	while (nextNode != nullptr) {
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
	PacketRef packet = MakeShareable(new TArray<TSharedRef<ServerCall> >());
	packet->Add(sc);
	return packet;
}

TSharedRef<IHttpRequest> BrainCloudComms::SendPacket(PacketRef packet)
{
	TSharedRef<IHttpRequest> httpRequest = FHttpModule::Get().CreateRequest();

	FString packetIdStr = FString::FormatAsNumber(_packetId);
	_currentPacket = packet;

	httpRequest->SetURL(_serverUrl);
	httpRequest->SetVerb(TEXT("POST"));
	httpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	httpRequest->SetHeader(TEXT("X-Braincloud-PacketId"), packetIdStr);

	FString dataString = GetDataString(packet, _packetId++);
	if (_isLoggingEnabled) UE_LOG(LogBrainCloudComms, Log, TEXT("Sending request:%s\n"), *dataString);

	httpRequest->SetContentAsString(dataString);

	if (_secretKey.Len() > 0)
	{
		FString secret = dataString + _secretKey;
		FString secretHeader = FMD5::HashAnsiString(*secret);
		httpRequest->SetHeader(TEXT("X-SIG"), secretHeader);
	}

	httpRequest->ProcessRequest();
	_requestSentTime = FPlatformTime::Seconds();
	return httpRequest;
}

void BrainCloudComms::ResendActivePacket()
{
	if (!_activeRequest.IsValid()) return;
	TSharedRef<IHttpRequest> httpRequest = FHttpModule::Get().CreateRequest();

	httpRequest->SetURL(_serverUrl);
	httpRequest->SetVerb(TEXT("POST"));
	httpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	httpRequest->SetHeader(TEXT("X-Braincloud-PacketId"), _activeRequest->GetHeader(TEXT("X-Braincloud-PacketId")));

	httpRequest->SetContent(_activeRequest->GetContent());
	httpRequest->SetHeader(TEXT("X-SIG"), _activeRequest->GetHeader(TEXT("X-SIG")));

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
	jsonDataObject->SetArrayField(TEXT("messages"), messages);
	jsonDataObject->SetStringField(TEXT("sessionId"), _sessionId);
	jsonDataObject->SetStringField(TEXT("gameId"), _gameId);
	jsonDataObject->SetNumberField(TEXT("packetId"), packetId);

	FJsonSerializer::Serialize(jsonDataObject, writer);

	jsonStr += TEXT("\r\n\r\n");
	return jsonStr;
}

void BrainCloudComms::CreateAndSendNextRequestBundle()
{
	_queueMutex.Lock();
	int32 queueCount = _messageQueue.Num();
	_queueMutex.Unlock();

	if (queueCount <= 0) return;

	bool isAuth = false;

	if (!_isAuthenticated)
	{
		_queueMutex.Lock();
		auto itr = TDoubleLinkedList<TSharedRef<ServerCall>>::TConstIterator(_messageQueue.GetHead());

		for (; itr; ++itr)
		{
			auto operation = itr->getOperation();
			if (operation == ServiceOperation::Authenticate ||
				operation == ServiceOperation::ResetEmailPassword)
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
		FakeErrorResponse(900, ReasonCode::CLIENT_DISABLED, "Client disabled due to repeated errors from a single API call");
	}

	_retryCount = 0;
	_waitingForRetry = false;
}

void BrainCloudComms::RunCallbacks()
{
	if (!_isInitialized || _blockingQueue) return;

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

			//request was sucessful
			if (status == EHttpRequestStatus::Succeeded)
			{
				FHttpResponsePtr resp = _activeRequest->GetResponse();
				if (resp.IsValid())
				{
					if (resp->GetResponseCode() == HttpCode::OK)
						HandleResponse(_activeRequest->GetResponse()->GetResponseCode(),
							_activeRequest->GetResponse()->GetContentAsString());
					else isError = true;
				}
			}
			else if (_activeRequest->GetStatus() == EHttpRequestStatus::Processing
				&& elapsedTime > GetRetryTimeoutSeconds(_retryCount))   //request timeout
			{
				if (_isLoggingEnabled) UE_LOG(LogBrainCloudComms, Warning, TEXT("Request timed out"));
				isError = true;
			}
			else if (!_waitingForRetry && status == EHttpRequestStatus::Failed)
			{
				if (_isLoggingEnabled) UE_LOG(LogBrainCloudComms, Warning, TEXT("Request failed"));
				isError = true;
			}

			if (isError) //request failed
			{
				_activeRequest->CancelRequest();

				if (_retryCount < GetMaxRetryAttempts())
				{
					if (_isLoggingEnabled) UE_LOG(LogBrainCloudComms, Warning, TEXT("Retrying..."));
					_retryWaitStart = FPlatformTime::Seconds();
					_retryWaitTime = GetRetryTimeoutSeconds(_retryCount) - elapsedTime;
					_waitingForRetry = true;
				}
				else
				{
					if (_isLoggingEnabled) UE_LOG(LogBrainCloudComms, Warning, TEXT("Reached max retry limit"));
					// if we're doing caching of messages on timeout, kick it in now!
					if (_cacheMessagesOnNetworkError && _networkErrorCallback != nullptr)
					{
						if (_isLoggingEnabled) UE_LOG(LogBrainCloudComms, Log, TEXT("Caching messages"));
						_blockingQueue = true;
						_networkErrorCallback->networkError();
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
								ReasonCode::CLIENT_NETWORK_ERROR_TIMEOUT,
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
		if (_isLoggingEnabled) UE_LOG(LogBrainCloudComms, Log, TEXT("Got response: %s\n"), *responseBody);

		TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(responseBody);
		TSharedPtr<FJsonObject> jsonPacket = MakeShareable(new FJsonObject());

		bool res = FJsonSerializer::Deserialize(reader, jsonPacket);
		if (res)
		{
			ReportResults(_currentPacket.ToSharedRef(), jsonPacket.ToSharedRef());

			if (_eventCallback && jsonPacket->HasField(TEXT("events")))
			{
				TArray<TSharedPtr<FJsonValue>> events = jsonPacket->GetArrayField(TEXT("events"));
				if (events.Num() > 0)
				{
					TSharedRef<FJsonObject> eventsRoot = MakeShareable(new FJsonObject);
					eventsRoot->SetArrayField(TEXT("events"), events);
					_eventCallback->eventCallback(GetJsonString(eventsRoot));
				}
			}
		}
		else //couldnt deserialize the response body
		{
			ReportError(_currentPacket.ToSharedRef(), HttpCode::CLIENT_NETWORK_ERROR, ReasonCode::JSON_PARSING_ERROR, TEXT("Unable to parse response"));
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
		UE_LOG(LogBrainCloudComms, Log, TEXT("Retrying cached messages"));
		_blockingQueue = false;
		_retryCount = 0;
		_waitingForRetry = false;
		ResendActivePacket();
	}
}

void BrainCloudComms::FlushCachedMessages(bool sendApiErrorCallbacks)
{
	UE_LOG(LogBrainCloudComms, Log, TEXT("Flushing cached messages"));

	if (sendApiErrorCallbacks)
	{
		ReportError(
			_currentPacket.ToSharedRef(),
			HttpCode::CLIENT_NETWORK_ERROR,
			ReasonCode::CLIENT_NETWORK_ERROR_TIMEOUT,
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
	if (_fileUploads.Num() <= 0) return;

	int32 count = _fileUploads.Num();

	for (int32 i = count - 1; i >= 0; --i)
	{
		if (_fileUploads[i]->GetStatus() == BCFileUploader::UPLOAD_STATUS_COMPLETE_SUCCESS)
		{
			if (_fileUploadCallback != nullptr)
				_fileUploadCallback->fileUploadCompleted(_fileUploads[i]->GetUploadId(), _fileUploads[i]->GetResponse());
			_fileUploads.RemoveAt(i);
		}
		else if (_fileUploads[i]->GetStatus() == BCFileUploader::UPLOAD_STATUS_COMPLETE_FAILED)
		{
			if (_fileUploadCallback != nullptr)
				_fileUploadCallback->fileUploadFailed(
					_fileUploads[i]->GetUploadId(),
					_fileUploads[i]->GetHttpStatus(),
					_fileUploads[i]->GetErrorReasonCode(),
					_fileUploads[i]->GetResponse());
			_fileUploads.RemoveAt(i);
		}
	}
}

void BrainCloudComms::CancelUpload(const FString& uploadId)
{
	TSharedPtr<BCFileUploader> uploader = FindFileUploader(uploadId);
	if (uploader.IsValid()) uploader->CancelUpload();
}

float BrainCloudComms::GetUploadProgress(const FString& uploadId)
{
	TSharedPtr<BCFileUploader> uploader = FindFileUploader(uploadId);
	if (uploader.IsValid()) return uploader->GetProgress();
	return -1.0f;
}

int32 BrainCloudComms::GetUploadBytesTransferred(const FString& uploadId)
{
	TSharedPtr<BCFileUploader> uploader = FindFileUploader(uploadId);
	if (uploader.IsValid()) return uploader->GetBytesTransferred();
	return -1;
}

int32 BrainCloudComms::GetUploadTotalBytesToTransfer(const FString& uploadId)
{
	TSharedPtr<BCFileUploader> uploader = FindFileUploader(uploadId);
	if (uploader.IsValid()) return uploader->GetTotalBytesToTransfer();
	return -1;
}

TSharedPtr<BCFileUploader> BrainCloudComms::FindFileUploader(const FString& uploadId)
{
	int32 count = _fileUploads.Num();
	for (int32 i = 0; i < count; ++i)
	{
		if (_fileUploads[i]->GetUploadId() == uploadId)
		{
			return _fileUploads[i];
		}
	}

	if (_isLoggingEnabled) UE_LOG(LogBrainCloudComms, Log, TEXT("Could not find Uploader with ID: %s"), *uploadId);
	return nullptr;
}

void BrainCloudComms::FakeErrorResponse(uint32 statusCode, uint32 reasonCode, const FString statusMessage)
{
	PacketRef requestPacket = BuildPacket();
	FString sendString = GetDataString(requestPacket, _packetId);
	if (_isLoggingEnabled) UE_LOG(LogBrainCloudComms, Log, TEXT("Sending request:%s\n"), *sendString);

	_currentPacket = requestPacket;
	ReportError(requestPacket, statusCode, reasonCode, statusMessage);
}

void BrainCloudComms::ReportResults(PacketRef requestPacket, TSharedRef<FJsonObject> responsePacket)
{
	TArray<TSharedPtr<FJsonValue>> responses = responsePacket->GetArrayField(TEXT("responses"));

	TArray<TSharedPtr<FJsonValue>> apiRewards;

	for (int32 i = 0; i < responses.Num(); i++)
	{
		TSharedRef<ServerCall> sc = (*requestPacket)[i];
		TSharedPtr<FJsonObject> respObj = responses[i]->AsObject();

		uint32 statusCode = respObj->GetNumberField(TEXT("status"));

		IServerCallback* callback = sc->getCallback();

		FString jsonRespStr = GetJsonString(respObj.ToSharedRef());

		if (statusCode == HttpCode::OK || (!_errorCallbackOn202 && statusCode == 202))
		{
			ResetKillSwitch();
			FilterIncomingMessages(sc, respObj.ToSharedRef());
			if (callback != nullptr) callback->serverCallback(sc->getService(), sc->getOperation(), *jsonRespStr);
		}
		else
		{
			uint32 reasonCode = 0;
			if (respObj->HasField(TEXT("reason_code")))
			{
				reasonCode = respObj->GetNumberField(TEXT("reason_code"));
				if (reasonCode == ReasonCode::PLAYER_SESSION_EXPIRED || reasonCode == ReasonCode::NO_SESSION
					|| reasonCode == ReasonCode::PLAYER_SESSION_LOGGED_OUT || sc->getOperation() == ServiceOperation::Logout
					|| sc->getOperation() == ServiceOperation::FullReset)
				{
					_isAuthenticated = false;
					_sessionId = TEXT("");
					_statusCodeCache = statusCode;
					_reasonCodeCache = reasonCode;
					_statusMessageCache = respObj->GetStringField(TEXT("status_message"));
				}
			}

			FString errorString;
			if (_useOldStatusMessage)
			{
				errorString = respObj->GetStringField(TEXT("status_message"));
			}
			else
			{
				errorString = jsonRespStr;
			}

			if (callback != nullptr)
				callback->serverError(sc->getService(), sc->getOperation(), statusCode, reasonCode, *errorString);
			if (_globalErrorCallback != nullptr)
				_globalErrorCallback->globalError(sc->getService(), sc->getOperation(), statusCode, reasonCode, *errorString);
			
			UpdateKillSwitch(sc->getService().getValue(), sc->getOperation().getValue(), statusCode);
		}

		if (_rewardCallback && (statusCode == HttpCode::OK || (!_errorCallbackOn202 && statusCode == 202)))
		{
			ServiceName service = sc->getService();
			ServiceOperation operation = sc->getOperation();

			TSharedPtr<FJsonObject> rewards = nullptr;

			// authenticate
			if (service == ServiceName::AuthenticateV2 && operation == ServiceOperation::Authenticate)
			{
				if (respObj->GetObjectField(TEXT("data"))->GetObjectField(TEXT("rewards"))->GetObjectField(TEXT("rewards"))->Values.Num() > 0)
				{
					rewards = respObj->GetObjectField(TEXT("data"))->GetObjectField(TEXT("rewards"));
				}
			}
			// player stat increment or statistics event trigger
			else if ((service == ServiceName::PlayerStatistics && operation == ServiceOperation::Update)
				|| (service == ServiceName::PlayerStatisticsEvent
					&& (operation == ServiceOperation::Trigger || operation == ServiceOperation::TriggerMultiple)))
			{
				if (respObj->GetObjectField(TEXT("data"))->GetObjectField(TEXT("rewards"))->Values.Num() > 0)
				{
					rewards = respObj->GetObjectField(TEXT("data"));
				}
			}

			if (rewards.IsValid())
			{
				TSharedPtr<FJsonObject> apiReward = MakeShareable(new FJsonObject());
				apiReward->SetStringField(TEXT("service"), service.getValue());
				apiReward->SetStringField(TEXT("operation"), operation.getValue());
				apiReward->SetObjectField(TEXT("rewards"), rewards);
				apiRewards.Add(MakeShareable(new FJsonValueObject(apiReward)));
			}
		}
	}

	if (apiRewards.Num() > 0)
	{
		TSharedRef<FJsonObject> rewards = MakeShareable(new FJsonObject());
		rewards->SetArrayField(TEXT("apiRewards"), apiRewards);

		FString jsonString;
		TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&jsonString);

		if (FJsonSerializer::Serialize(rewards, writer))
		{
			_rewardCallback->rewardCallback(jsonString);
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
		IServerCallback* callback = sc->getCallback();
		if (callback != nullptr)
		{
			FString errorString;
			if (_useOldStatusMessage)
			{
				errorString = statusMessage;
			}
			else
			{
				TSharedRef<FJsonObject> jsonObj = MakeShareable(new FJsonObject());

				jsonObj->SetNumberField(TEXT("status"), statusCode);
				jsonObj->SetNumberField(TEXT("reason_code"), reasonCode);
				jsonObj->SetStringField(TEXT("statusMessage"), statusMessage);
				jsonObj->SetStringField(TEXT("severity"), TEXT("ERROR"));

				errorString = GetJsonString(jsonObj);
			}
			callback->serverError(sc->getService(), sc->getOperation(), statusCode, reasonCode, *errorString);
			if (_globalErrorCallback != nullptr)
				_globalErrorCallback->globalError(sc->getService(), sc->getOperation(), statusCode, reasonCode, *errorString);
		}
	}

	_activeRequest = nullptr; //clear the active request
	_currentPacket = nullptr;
}

void BrainCloudComms::FilterIncomingMessages(TSharedRef<ServerCall> servercall, TSharedRef<FJsonObject> response)
{
	ServiceName service = servercall->getService();
	ServiceOperation operation = servercall->getOperation();

	if (service == ServiceName::AuthenticateV2 && operation == ServiceOperation::Authenticate)
	{
		_isAuthenticated = true;
		ResetErrorCache();
		ClearSessionId();

		TSharedPtr<FJsonObject> data = response->GetObjectField(TEXT("data"));

		if (data.IsValid())
		{
			data->TryGetStringField(TEXT("sessionId"), _sessionId);

			FString profileId = data->GetStringField(TEXT("profileId"));
			_client->getAuthenticationService()->setProfileId(profileId);

			if (_heartbeatInterval == 0)
			{
				int32 sessionTimeout = data->GetIntegerField(TEXT("playerSessionExpiry"));
				sessionTimeout = (int32)sessionTimeout * 0.85;

				// minimum 30 secs
				_heartbeatInterval = sessionTimeout > 30 ? sessionTimeout : 30;
				_heartbeatInterval *= 1000; //to ms
			}

			_maxBundleMessages = data->GetNumberField(TEXT("maxBundleMsgs"));

			if(data->HasField("maxKillCount"))
				_killSwitchThreshold = data->GetNumberField(TEXT("maxKillCount"));

			//set player name
			FString name = data->GetStringField(TEXT("playerName"));
			_client->getPlayerStateService()->setPlayerName(name);
		}
	}
	else if (service == ServiceName::PlayerState &&
		(operation == ServiceOperation::FullReset || operation == ServiceOperation::Logout))
	{
		_isAuthenticated = false;
		_sessionId = TEXT("");
		ResetErrorCache();
		_client->getAuthenticationService()->clearSavedProfileId();
		_client->getPlayerStateService()->setPlayerName(TEXT(""));
	}
	else if (service == ServiceName::PlayerState && operation == ServiceOperation::UpdateName)
	{
		if (response->GetObjectField(TEXT("data")).IsValid())
		{
			FString name = response->GetObjectField(TEXT("data"))->GetStringField(TEXT("playerName"));
			_client->getPlayerStateService()->setPlayerName(name);
		}
	}
	else if (service == ServiceName::File && operation == ServiceOperation::PrepareUserUpload)
	{
		if (response->HasField(TEXT("data")))
		{
			TSharedPtr<FJsonObject> fileInfo = response->GetObjectField(TEXT("data"))->GetObjectField(TEXT("fileDetails"));

			TSharedRef<BCFileUploader> uploader = MakeShareable(
				new BCFileUploader(
					_uploadLowTransferRateTimeout,
					_uploadLowTransferRateThreshold,
					_uploadOverallTimeout,
					_isLoggingEnabled));

			FString localPath = fileInfo->GetStringField(TEXT("localPath"));
			FString uploadId = fileInfo->GetStringField(TEXT("uploadId"));

			_fileUploads.Add(uploader);
			uploader->UploadFile(localPath, _sessionId, uploadId, _uploadUrl);
		}
	}
}

void BrainCloudComms::ResetCommunication()
{
	_messageQueue.Empty();
	_isAuthenticated = false;
	_sessionId = TEXT("");
	ResetErrorCache();
	_waitingForRetry = false;

	if (_activeRequest.IsValid()) _activeRequest->CancelRequest();
	_activeRequest = nullptr;
	_currentPacket = nullptr;

	_blockingQueue = false;
}

void BrainCloudComms::ResetErrorCache()
{
	_statusCodeCache = HttpCode::FORBIDDEN;
	_reasonCodeCache = ReasonCode::NO_SESSION;
	_statusMessageCache = TEXT("No session");
}

void BrainCloudComms::UpdateKillSwitch(const FString& service, const FString& operation, int32 statusCode)
{
	if (statusCode == 900) return;

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
		ServerCall * sc = new ServerCall(ServiceName::HeartBeat, ServiceOperation::Read, val, nullptr);
		AddToQueue(sc);
	}
}

bool BrainCloudComms::ShouldRetryPacket()
{
	TArray<TSharedRef<ServerCall>> arr = *_currentPacket.Get();
	for (int32 i = 0; i < arr.Num(); i++)
	{
		TSharedRef<ServerCall> sc = arr[i];

		if (arr[i]->getService() == ServiceName::AuthenticateV2
			&& (arr[i]->getOperation() == ServiceOperation::Authenticate))
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

FString BrainCloudComms::GetJsonString(TSharedRef<FJsonObject> jsonDataObject)
{
	FString jsonStr;
	TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&jsonStr);
	FJsonSerializer::Serialize(jsonDataObject, writer);
	return jsonStr;
}