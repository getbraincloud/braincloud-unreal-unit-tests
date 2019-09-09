
#include "braincloud/internal/IBrainCloudComms.h"
#include "braincloud/BrainCloudClient.h"

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <ctype.h>
#include <string>
#include <list>
#include "braincloud/internal/IFileUploader.h"


namespace BrainCloud {

	////////////////////////////////////////////////////////
	// Public methods
	////////////////////////////////////////////////////////

	IBrainCloudComms::IBrainCloudComms(BrainCloudClient* in_client)
		: _client(in_client)
		, _packetId(0)
		, _expectedPacketId(NO_PACKET_EXPECTED)
		, _retryCount(0)
		, _packetSendTimeMillis(0)
		, _isInitialized(false)
		, _isAuthenticated(false)
		, _heartbeatInterval(0)
		, _immediateRetryOnError(false)
		, _loggingEnabled(false)
		, _authenticationTimeoutMillis(DEFAULT_AUTHENTICATION_TIMEOUT_MILLIS)
		, _oldStyleStatusMessageErrorCallback(false)
		, _cacheMessagesOnNetworkError(false)
		, _errorCallbackOn202(true)
		, _blockingQueue(false)
		, _eventCallback(NULL)
		, _fileUploadCallback(NULL)
		, _globalErrorCallback(NULL)
		, _rewardCallback(NULL)
		, _networkErrorCallback(NULL)
		, _uploadLowTransferRateTimeoutSecs(120)
		, _uploadLowTransferRateThresholdBytesPerSec(50)
		, _uploadOverallTimeoutSecs(0)
		, _statusCodeCache(0)
		, _reasonCodeCache(0)
		, _maxBundleSize(10)
		, _killSwitchThreshold(11)
		, _killSwitchEngaged(false)
		, _killSwitchErrorCount(0)
	{
		setPacketTimeoutsToDefault();
	}

	IBrainCloudComms::~IBrainCloudComms()
	{
	}

    void IBrainCloudComms::initializeWithApps(const char * serverURL, const char * defaultAppId, const std::map<std::string, std::string>& secretMap)
    {
        _secretMap = secretMap;

        _secretKey = "MISSING";
        std::map<std::string, std::string>::const_iterator it = _secretMap.find(defaultAppId);
        if (it != _secretMap.end())
        {
            _secretKey = it->second;
        }

        initialize(serverURL, defaultAppId, _secretKey.c_str());
    }

	void IBrainCloudComms::enableLogging(bool shouldEnable)
	{
		_loggingEnabled = shouldEnable;
	}

	bool IBrainCloudComms::isInitialized()
	{
		return _isInitialized;
	}

	bool IBrainCloudComms::isAuthenticated()
	{
		return _isAuthenticated;
	}

	void IBrainCloudComms::setAuthenticated()
	{
		_isAuthenticated = true;
	}

	void IBrainCloudComms::setHeartbeatInterval(int milliseconds)
	{
		_heartbeatInterval = milliseconds;
	}

	void IBrainCloudComms::setImmediateRetryOnError(bool value)
	{
		_immediateRetryOnError = value;
	}

	const std::string& IBrainCloudComms::getGameId() const
	{
		return _appId;
	}

	const std::string& IBrainCloudComms::getAppId() const
	{
		return _appId;
	}

	void IBrainCloudComms::clearSessionId()
	{
		_sessionId.clear();
	}

	const std::string& IBrainCloudComms::getSessionId() const
	{
		return _sessionId;
	}

	void IBrainCloudComms::setSessionId(const char * sessionId)
	{
		_sessionId.clear();
		_sessionId.append(sessionId);
	}

	void IBrainCloudComms::setServerUrl(const char * serverUrl)
	{
		_serverUrl.clear();
		_serverUrl.append(serverUrl);
	}

	const std::vector<int> & IBrainCloudComms::getPacketTimeouts()
	{
		return _packetTimeouts;
	}

	void IBrainCloudComms::setPacketTimeouts(const std::vector<int> & in_packetTimeouts)
	{
		_packetTimeouts = in_packetTimeouts;
	}

	void IBrainCloudComms::setPacketTimeoutsToDefault()
	{
		_packetTimeouts.clear();
		_packetTimeouts.push_back(15);
		_packetTimeouts.push_back(10);
		_packetTimeouts.push_back(10);
	}

	void IBrainCloudComms::setAuthenticationPacketTimeout(int in_timeoutSecs)
	{
		if (in_timeoutSecs > 0)
		{
			_authenticationTimeoutMillis = in_timeoutSecs * 1000;
		}
	}

	int IBrainCloudComms::getAuthenticationPacketTimeout()
	{
		return _authenticationTimeoutMillis / 1000;
	}

	void IBrainCloudComms::setOldStyleStatusMessageErrorCallback(bool in_enabled)
	{
		_oldStyleStatusMessageErrorCallback = in_enabled;
	}

	void IBrainCloudComms::setErrorCallbackOn202Status(bool in_isError)
	{
		_errorCallbackOn202 = in_isError;
	}

	int IBrainCloudComms::getUploadLowTransferRateTimeout()
	{
		return _uploadLowTransferRateTimeoutSecs;
	}

	void IBrainCloudComms::setUploadLowTransferRateTimeout(int in_timeoutSecs)
	{
		_uploadLowTransferRateTimeoutSecs = in_timeoutSecs;
	}

	int IBrainCloudComms::getUploadLowTransferRateThreshold()
	{
		return _uploadLowTransferRateThresholdBytesPerSec;
	}

	void IBrainCloudComms::setUploadLowTransferRateThreshold(int in_bytesPerSec)
	{
		_uploadLowTransferRateThresholdBytesPerSec = in_bytesPerSec;
	}

	//////////////////////////////////////////////////////
	// Protected methods
	//////////////////////////////////////////////////////

	void IBrainCloudComms::setCredentials(const Json::Value& in_jsonResponse)
	{
		if (in_jsonResponse["data"] != Json::nullValue)
		{
			const Json::Value& jsonData = in_jsonResponse["data"];

			if (jsonData["sessionId"] != Json::nullValue)
			{
				std::string sessionId = jsonData.get("sessionId", "").asString();
				setSessionId(sessionId.c_str());
			}

            if (jsonData["profileId"] != Json::nullValue)
            {
                std::string profileId = jsonData.get("profileId", "").asString();
                _client->getAuthenticationService()->setProfileId(profileId.c_str());
            }

            if (jsonData["switchToAppId"] != Json::nullValue)
            {
                _appId = jsonData.get("switchToAppId", "").asString();

                // Update secret key
                _secretKey = "MISSING";
                std::map<std::string, std::string>::const_iterator it = _secretMap.find(_appId);
                if (it != _secretMap.end())
                {
                    _secretKey = it->second;
                }
            }
        }
	}

	void IBrainCloudComms::filterIncomingMessages(const ServerCall* servercall, const Json::Value& response)
	{
		//This is a hook to perform processing on any messages that come in, before they are sent to the calling application.
  
		// A session id or a profile id could potentially come back in any messages
				//we want to make sure to update this on Authentication and Identity calls only
		if (servercall->getService() == ServiceName::AuthenticateV2 || servercall->getService() == ServiceName::Identity)
		{
			setCredentials(response);
		}

		if (servercall->getService() == ServiceName::AuthenticateV2 &&
			servercall->getOperation() == ServiceOperation::Authenticate &&
			response["reason_code"] == Json::nullValue)
		{
			_isAuthenticated = true;
			clearSessionId();
			setCredentials(response);

			if (response["data"] != Json::nullValue)
			{
				// pick up the timeout interval from the auth call
				if (_heartbeatInterval == 0)
				{
					if (response["data"]["playerSessionExpiry"] != Json::nullValue)
					{
						int sessionTimeout = response["data"]["playerSessionExpiry"].asInt();
						sessionTimeout = (int)((double)sessionTimeout * 0.85);
                        _heartbeatInterval = sessionTimeout * 1000;
					}
				}

				if (response["data"]["maxBundleMsgs"] != Json::nullValue)
				{
					_maxBundleSize = response["data"]["maxBundleMsgs"].asInt();
				}

				if (response["data"]["maxKillCount"] != Json::nullValue)
				{
					_killSwitchThreshold = response["data"]["maxKillCount"].asInt();
				}
			}
		}
		else if (servercall->getService() == ServiceName::PlayerState
			&& (servercall->getOperation() == ServiceOperation::FullReset
				|| servercall->getOperation() == ServiceOperation::Logout))
		{
			_isAuthenticated = false;
			_sessionId.clear();
			_client->getAuthenticationService()->clearSavedProfileId();
		}
		else if (servercall->getService() == ServiceName::File
			&& (servercall->getOperation() == ServiceOperation::PrepareUserUpload))
		{
			startFileUpload(response);
		}
	}

	void IBrainCloudComms::runCallbacksFileUpload()
	{
		// go through map and check for completions/failures
		// and remove uploads that are done

		// if we are now transferring fewer than the max,
		// check if any uploads are pending and start them

		// we assume that all mutex locking has been done from the calling method!

		tFileUploadsIterator it;
		for (it = _fileUploads.begin(); it != _fileUploads.end();)
		{
			IFileUploader::eFileUploaderStatus status = it->second->getStatus();
			bool cleanup = false;
			switch (status)
			{
			case IFileUploader::UPLOAD_STATUS_COMPLETE_SUCCESS:
			{
				if (!it->second->isThreadRunning())
				{
					if (_fileUploadCallback != NULL)
					{
						_fileUploadCallback->fileUploadCompleted(it->first.c_str(), it->second->getHttpResponse());
					}
					cleanup = true;
				}
				break;
			}
			case IFileUploader::UPLOAD_STATUS_COMPLETE_FAILED:
			{
				if (!it->second->isThreadRunning())
				{
					if (_fileUploadCallback != NULL)
					{
						_fileUploadCallback->fileUploadFailed(it->first.c_str(), it->second->getHttpStatus(), it->second->getErrorReasonCode(), it->second->getHttpResponse());
					}
					cleanup = true;
				}
				break;
			}
			default:
				break;
			}
			if (cleanup)
			{
				delete it->second;
				_fileUploads.erase(it++);
			}
			else
			{
				++it;
			}
		}
	}

	void IBrainCloudComms::insertEndOfMessageBundleMarker()
	{
		ServerCall *sc = new ServerCall();
		sc->setEndOfBundleMarker(true);
		addToQueue(sc);
	}

	void IBrainCloudComms::createJsonErrorResponse(int in_statusCode,
		int in_reasonCode,
		const std::string & in_statusMessage,
		std::string & out_jsonErrorResponse)
	{
		Json::Value root;
		Json::FastWriter writer;

		root["status"] = in_statusCode;
		root["reason_code"] = in_reasonCode;
		root["status_message"] = in_statusMessage;
		root["severity"] = "ERROR";

		out_jsonErrorResponse = writer.write(root);
	}

}  // end namespace
