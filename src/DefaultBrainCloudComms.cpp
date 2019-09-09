#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <ctype.h>
#include <string>
#include <list>
#include <sstream>
#if defined(BC_UWP)
#include "braincloud/internal/win/MD5.h"
#else
#include "braincloud/internal/md5x.h"
#endif
#include "braincloud/reason_codes.h"
#include "braincloud/http_codes.h"

#include "braincloud/internal/IFileUploader.h"
#include "braincloud/BrainCloudClient.h"
#include "braincloud/internal/DefaultBrainCloudComms.h"
#include "braincloud/internal/TimeUtil.h"

namespace BrainCloud
{
    IBrainCloudComms* IBrainCloudComms::create(BrainCloudClient* in_client)
    {
        return new DefaultBrainCloudComms(in_client);
    }

    DefaultBrainCloudComms::DefaultBrainCloudComms(BrainCloudClient* in_client)
		: IBrainCloudComms(in_client)
		, _loader(NULL)
		, _request(NULL)
		, _retryTimeMillis(RETRY_TIME_NOT_RETRYING)
	{
		resetErrorCache();
	}

	DefaultBrainCloudComms::~DefaultBrainCloudComms()
	{
	}


	////////////////////////////////////////////////////////
	// Public methods
	////////////////////////////////////////////////////////

	void DefaultBrainCloudComms::initialize(const char * serverURL, const char * appId, const char * secretKey)
	{
		_serverUrl = serverURL;
		_uploadUrl = serverURL;
		size_t index = _uploadUrl.find("/dispatcherv2");
		if (index != std::string::npos)
		{
			_uploadUrl = _uploadUrl.substr(0, index);
		}
		_uploadUrl += "/uploader";

		_appId = appId;
		_secretKey = secretKey;
		_secretMap[_appId] = _secretKey;

		_isInitialized = true;
	}

	/**
	 * If data was received and needs to be communicated to the app layer, this is where it will be done
	 */
	void DefaultBrainCloudComms::runCallbacks()
	{
		if (!_isInitialized)
		{
			return;
		}

		if (_blockingQueue)
		{
			return;
		}

        _loaderMutex.lock();

		if (_loader != NULL)
		{
			if (_loader->isDone())
			{
				handleResult(_loader->getResponse());
				delete _loader;
				_loader = NULL;
			}
            else
            {
#if defined(IW_SDK)
                //TODO: Move this into the request. Like we did in IXMLHttpRequestLoader which has a timeout in a thread
                // iwhttp doesn't have a timeout mechanism so we have to monitor ourselves
                // and cancel the request if it goes over the retry timeout
                int64_t currentTimeMillis = TimeUtil::getCurrentTimeMillis();
                int64_t retryTimeout = (int64_t)(getRetryTimeoutMillis(_retryCount));
                if (currentTimeMillis >= _packetSendTimeMillis + retryTimeout)
                {
                    if (_loggingEnabled)
                    {
                        std::cout << "#BCC Cancelling packet " << _expectedPacketId << " as we've exceeded timeout " << retryTimeout << std::endl;
                    }

                    // cancel the request and let the next tick handle it
                    _loader->close();
                }
#endif
            }
        }
		else
		{
			int64_t currentTimeMillis = TimeUtil::getCurrentTimeMillis();

            _queueMutex.lock();
			bool queueHasMessages = _queue.size() > 0;
            _queueMutex.unlock();

			// are we in a retry?
			if (_retryTimeMillis != RETRY_TIME_NOT_RETRYING && _request != NULL)
			{
				if (_retryTimeMillis <= currentTimeMillis)
				{
					_expectedPacketId = _packetId - 1;
					if (_loggingEnabled)
					{
						std::cout << "#BCC Resending packetId(" << _expectedPacketId << ") retry(" << _retryCount << ")" << std::endl;
					}

					startHttpRequest();
				}
			}
			// are there api calls to send?
			else if (queueHasMessages)
			{
				createAndSendBundle();
			}
			// is there a heartbeat to send?
			else if (_isAuthenticated && currentTimeMillis >= _packetSendTimeMillis + _heartbeatInterval)
			{
				sendHeartbeat();
			}
		}

        _loaderMutex.unlock();


		// ????
        _mutex.lock();
		Json::Value rewards;

		// Process any events that are present until the queue is empty.
		while (!_apiCallbackQueue.empty())
		{
			BrainCloudCallbackEvent* event = _apiCallbackQueue.front();
			_apiCallbackQueue.pop();

			// call the appropriate callback based on the type of response
			if (event->callback != NULL)
			{
				if (event->m_retryCount != 0)
				{
					event->callback->serverWarning(event->m_service, event->m_operation, event->m_statusCode, event->m_reasonCode, event->m_retryCount, event->m_data);
				}
				else if (event->m_error)
				{
					if (_globalErrorCallback != NULL)
					{
						_globalErrorCallback->globalError(event->m_service, event->m_operation, event->m_statusCode, event->m_reasonCode, event->m_data);
					}

					event->callback->serverError(event->m_service, event->m_operation, event->m_statusCode, event->m_reasonCode, event->m_data);
				}
				else
				{
					event->callback->serverCallback(event->m_service, event->m_operation, event->m_data);

				}
			}

			delete event;
		}

		while (!_rewardCallbackQueue.empty())
		{
			std::string &reward = _rewardCallbackQueue.front();
			if (_rewardCallback)
			{
				_rewardCallback->rewardCallback(reward);
			}
			_rewardCallbackQueue.pop_front();
		}

		while (!_eventCallbackQueue.empty())
		{
			std::string &event = _eventCallbackQueue.front();
			if (_eventCallback)
			{
				_eventCallback->eventCallback(event);
			}
			_eventCallbackQueue.pop_front();
		}

		runCallbacksFileUpload();
        _mutex.unlock();
	}

	void DefaultBrainCloudComms::registerEventCallback(IEventCallback *in_eventCallback)
	{
        _mutex.lock();
        _eventCallback = in_eventCallback;
        _mutex.unlock();
    }

	void DefaultBrainCloudComms::deregisterEventCallback()
	{
        _mutex.lock();
        _eventCallback = NULL;
        _mutex.unlock();
    }

	void DefaultBrainCloudComms::registerFileUploadCallback(IFileUploadCallback *in_fileUploadCallback)
	{
        _mutex.lock();
        _fileUploadCallback = in_fileUploadCallback;
        _mutex.unlock();
    }

	void DefaultBrainCloudComms::deregisterFileUploadCallback()
	{
        _mutex.lock();
        _fileUploadCallback = NULL;
        _mutex.unlock();
    }

	void DefaultBrainCloudComms::registerRewardCallback(IRewardCallback *in_rewardCallback)
	{
        _mutex.lock();
        _rewardCallback = in_rewardCallback;
        _mutex.unlock();
    }

	void DefaultBrainCloudComms::deregisterRewardCallback()
	{
        _mutex.lock();
        _rewardCallback = NULL;
        _mutex.unlock();
    }

	void DefaultBrainCloudComms::registerGlobalErrorCallback(IGlobalErrorCallback *in_globalErrorCallback)
	{
        _mutex.lock();
        _globalErrorCallback = in_globalErrorCallback;
        _mutex.unlock();
    }

	void DefaultBrainCloudComms::deregisterGlobalErrorCallback()
	{
        _mutex.lock();
        _globalErrorCallback = NULL;
        _mutex.unlock();
    }

	void DefaultBrainCloudComms::registerNetworkErrorCallback(INetworkErrorCallback *in_networkErrorCallback)
	{
        _mutex.lock();
        _networkErrorCallback = in_networkErrorCallback;
        _mutex.unlock();
    }

	void DefaultBrainCloudComms::deregisterNetworkErrorCallback()
	{
        _mutex.lock();
		_networkErrorCallback = NULL;
        _mutex.unlock();
    }

	/**
	 * Add a new server call definition to the request queue.
	 */
	void DefaultBrainCloudComms::addToQueue(ServerCall * sc)
	{
		// Add the new ServerCall to the end of the queue.
        _queueMutex.lock();
		_queue.push_back(sc);
        _queueMutex.unlock();
	}

	void DefaultBrainCloudComms::enableNetworkErrorMessageCaching(bool in_enabled)
	{
        _loaderMutex.lock();
		_cacheMessagesOnNetworkError = in_enabled;
        _loaderMutex.unlock();
	}

	void DefaultBrainCloudComms::retryCachedMessages()
	{
        _loaderMutex.lock();
		if (_blockingQueue && _request)
		{
			_retryCount = 0;
			_expectedPacketId = _packetId - 1;
			startHttpRequest();
			_blockingQueue = false;
		}
        _loaderMutex.unlock();
	}

	void DefaultBrainCloudComms::flushCachedMessages(bool in_sendApiErrorCallbacks)
	{
        _loaderMutex.lock();
		if (_blockingQueue)
		{
			if (in_sendApiErrorCallbacks)
			{
				_expectedPacketId = _packetId - 1;
				triggerCommsError(HTTP_CLIENT_NETWORK_ERROR, CLIENT_NETWORK_ERROR_TIMEOUT, "Network timeout", "ERROR");
			}
			while (!_inProgress.empty())
			{
				delete _inProgress.back();
				_inProgress.pop_back();
			}
			if (_request)
			{
				delete _request;
				_request = NULL;
			}
			_blockingQueue = false;
		}
        _loaderMutex.unlock();
	}

	void DefaultBrainCloudComms::handleResponseBundle(Json::Value & root)
	{
		Json::FastWriter writer;
		Json::Value messages = root["responses"];
		Json::Value apiRewards(Json::nullValue);
		int64_t receivedPacketId = root["packetId"].asInt64();
		if (receivedPacketId != NO_PACKET_EXPECTED && (_expectedPacketId == NO_PACKET_EXPECTED || _expectedPacketId != receivedPacketId))
		{
			// drop the packet - this is the wrong packet id
			if (_loggingEnabled)
			{
				std::cout << "#BCC Dropping packet id " << receivedPacketId << " as we're expecting " << _expectedPacketId << std::endl;
			}

            _mutex.lock();
            for (unsigned int i = 0; i < _inProgress.size(); ++i)
            {
                ServerCall * serverCall = _inProgress[i];

                IServerCallback* callback = serverCall->getCallback();
                if (callback)
                {
                    // set up the callback event
                    BrainCloudCallbackEvent* event = new BrainCloudCallbackEvent();
                    event->callback = callback;
                    event->m_service = serverCall->getService();
                    event->m_operation = serverCall->getOperation();
                    event->m_error = true;
                    event->m_statusCode = messages[i]["status"].asInt();
                    event->m_reasonCode = messages[i]["reason_code"].asInt();
                    event->m_data = messages[i]["status_message"].asString();

                    _apiCallbackQueue.push(event);
                }
            }
            _mutex.unlock();

			return;
		}
		_expectedPacketId = NO_PACKET_EXPECTED;


		////////////////////////////////////////////////////
		// LOCKING CALLBACK QUEUES WHILE PROCESSING BUNDLE
		// SO ALL MESSAGES IN A BUNDLE ARE PROCESSED IN
		// ONE UPDATE CYCLE.
		// (otherwise reward handler may not be
		// called in the same update)
		////////////////////////////////////////////////////

        _mutex.lock();

		for (unsigned int i = 0; i < _inProgress.size(); ++i)
		{
			ServerCall * serverCall = _inProgress[i];

			bool error = false;
			int reasonCode = messages[i]["reason_code"].asInt(); // will be 0 if json not present
			int statusCode = messages[i]["status"].asInt();
			std::string jsonError = "";

			if (statusCode != HTTP_OK)
			{
				if (!_errorCallbackOn202 && statusCode == 202)
				{
					error = false;
				}
				else
				{
					error = true;
					if (_oldStyleStatusMessageErrorCallback)
					{
						jsonError = messages[i]["status_message"].asString();
					}
					else
					{
						jsonError = writer.write(messages[i]);
					}
				}
			}
			
			//if its a switch call, we need to update the appId and secret
			if (serverCall->getOperation() == ServiceOperation::SwitchToChildProfile || serverCall->getOperation()  == ServiceOperation::SwitchToParentProfile)
			{
				ProcessSwitchResponse(messages[i]["data"]);
			}

			if (!error)
			{
				filterIncomingMessages(serverCall, messages[i]);
				resetKillSwitch();
			}
			else
			{
				if (reasonCode == PLAYER_SESSION_EXPIRED
					|| reasonCode == NO_SESSION
					|| reasonCode == PLAYER_SESSION_LOGGED_OUT)
				{
					_isAuthenticated = false;
					_sessionId.clear();

					//cache error if session related
					_statusCodeCache = statusCode;
					_reasonCodeCache = reasonCode;
					_statusMessageCache = messages[i]["status_message"].asString();
				}

				if (serverCall->getOperation() == ServiceOperation::Logout)
				{
					if (reasonCode == CLIENT_NETWORK_ERROR_TIMEOUT)
					{
						_isAuthenticated = false;
						_sessionId.clear();
					}
				}

				updateKillSwitch(serverCall->getService().getValue(), serverCall->getOperation().getValue(), statusCode);
			}

			IServerCallback* callback = serverCall->getCallback();
			if (callback)
			{
				// set up the callback event
				BrainCloudCallbackEvent* event = new BrainCloudCallbackEvent();
				event->callback = callback;
				event->m_service = serverCall->getService();
				event->m_operation = serverCall->getOperation();
				event->m_error = error;
				event->m_statusCode = statusCode;
				event->m_reasonCode = reasonCode;

				if (error)
				{
					event->m_data = jsonError;
				}
				else
				{
					event->m_data = writer.write(messages[i]);
				}

				_apiCallbackQueue.push(event);
			}

			// check for rewards
			if (!error)
			{
				ServiceName service = serverCall->getService();
				ServiceOperation operation = serverCall->getOperation();
				Json::Value rewards = Json::nullValue;
				// authenticate
				if (service == ServiceName::AuthenticateV2 && operation == ServiceOperation::Authenticate)
				{
					resetErrorCache();

					if (!messages[i]["data"]["rewards"]["rewards"].empty())
					{
						rewards = messages[i]["data"]["rewards"];
					}
				}
				// player stat increment or statistics event trigger
				else if ((service == ServiceName::PlayerStatistics && operation == ServiceOperation::Update)
					|| (service == ServiceName::PlayerStatisticsEvent
						&& (operation == ServiceOperation::Trigger || operation == ServiceOperation::TriggerMultiple)))
				{
					if (!messages[i]["data"]["rewards"].empty())
					{
						rewards = messages[i]["data"];
					}
				}

				if (!rewards.isNull())
				{
					Json::Value apiReward;
					apiReward["service"] = service.getValue();
					apiReward["operation"] = operation.getValue();
					apiReward["rewards"] = rewards;
					apiRewards["apiRewards"].append(apiReward);
				}
			}
		}

		if (_rewardCallback)
		{
			if (!apiRewards.empty())
			{
				std::string jsonApiRewards = writer.write(apiRewards);
				_rewardCallbackQueue.push_back(jsonApiRewards);
			}
		}

		if (_eventCallback)
		{
			Json::Value events = root["events"];
			if (!events.isNull())
			{
				Json::Value eventsRoot;
				eventsRoot["events"] = events;
				std::string jsonEvents = writer.write(eventsRoot);
				_eventCallbackQueue.push_back(jsonEvents);
			}
		}

        _mutex.unlock();
	}

	/**
	 * This gets called from the URLLoader via a callback...
	 * Used to retrieve data from our call
	 *
	 * @param response
	 * @return false if a retry is required, true if result parsed
	 */
	bool DefaultBrainCloudComms::handleResult(URLResponse const & response)
	{
		Json::Value root;
		Json::Reader reader;
		std::string responseData = response.getData();
		int responseStatus = response.getStatusCode();

		if (_loggingEnabled)
		{
			// make it easier to read the json
			Json::Value jsonDbg;
			std::string dataOutput = response.getData();
			if (reader.parse(responseData, jsonDbg))
			{
				Json::StyledWriter w;
				dataOutput = w.write(jsonDbg);
			}
			std::cout << "#BCC INCOMING status(" << responseStatus
				<< ") reasonPhrase: " << response.getReasonPhrase() << " data: "
				<< dataOutput << std::endl;
		}

		// The _inProgress queue holds the list of every message in the bundle,
		// or non-bundled request, which is currently being processed.
		// Therefore, if the _inProgress queue is empty, we shouldn't be in this
		// routine.
		if (_inProgress.empty())
		{
			if (_loggingEnabled)
			{
				std::cout << "#BCC ignoring last packet, inProgress queue is empty" << std::endl;
			}
			return false;
		}

		bool needsRetry = false;
		bool flushInProgressQueue = false;

		if (responseStatus != HTTP_OK
			|| responseData.length() <= 0
			|| !reader.parse(responseData, root))
		{
			// deals with retry timers
			handleError(response);

			// handleError method sets retry count to zero if we've hit retry limit.
			// this is not a good way to check the value but hard to unwind the code.
			needsRetry = (_retryCount != 0);

			// if ran out of retries, fake an error response
			if (!needsRetry)
			{
				if (_cacheMessagesOnNetworkError)
				{
					_blockingQueue = true;
					if (_networkErrorCallback)
					{
						_networkErrorCallback->networkError();
					}
				}
				else
				{
					triggerCommsError(HTTP_CLIENT_NETWORK_ERROR, CLIENT_NETWORK_ERROR_TIMEOUT, "Network timeout", "ERROR");
					flushInProgressQueue = true;
				}
			}
		}
		else
		{
			handleResponseBundle(root);
			flushInProgressQueue = true;
		}

		// Clear the inProgress queue
		if (flushInProgressQueue)
		{
			while (!_inProgress.empty())
			{
				delete _inProgress.back();
				_inProgress.pop_back();
			}
		}

		_expectedPacketId = NO_PACKET_EXPECTED;

		return needsRetry;
	}

	void DefaultBrainCloudComms::triggerCommsError(int statusCode, int responseCode, const std::string & in_error, const std::string & in_severity)
	{
		Json::Value errorRoot;
		Json::Value messages;
		for (size_t i = 0, isize = _inProgress.size(); i < isize; ++i)
		{
			Json::Value msg;
			msg["status"] = HTTP_CLIENT_NETWORK_ERROR;
			msg["reason_code"] = CLIENT_NETWORK_ERROR_TIMEOUT;
			msg["status_message"] = "Network timeout";
			msg["severity"] = "ERROR";
			messages.append(msg);
		}
		errorRoot["responses"] = messages;
		errorRoot["packetId"] = (Json::Int64) _expectedPacketId;

		handleResponseBundle(errorRoot);
	}


	/**
	 * This method would normally just be in the BrainCloud, but because we call
	 * it from within the manager via a timer, we're placing it here...
	 */
	void DefaultBrainCloudComms::sendHeartbeat()
	{
		ServerCall * sc = new ServerCall(ServiceName::HeartBeat, ServiceOperation::Read, Json::Value(Json::nullValue), NULL);
		addToQueue(sc);
	}

	void DefaultBrainCloudComms::resetCommunication()
	{
		_isAuthenticated = false;
		_sessionId.clear();

		resetErrorCache();

        _loaderMutex.lock();
		if (_loader != NULL)
		{
			_loader->close();
			int timeToWait = 2000; // 2 secs should be enough
			int timeSlice = 100;
			while (!_loader->isDone() && timeToWait > 0)
			{
				TimeUtil::sleepMillis(timeSlice);
				timeToWait -= timeSlice;
			}
			// if loader is done it's safe to release the memory
			// otherwise we give up and just leak a bit
			if (_loader->isDone())
			{
				delete _loader;
			}
			_loader = NULL;
		}
        _loaderMutex.unlock();

		_retryCount = 0;
		_retryTimeMillis = RETRY_TIME_NOT_RETRYING;
		_packetSendTimeMillis = 0;
		if (_request)
		{
			delete _request;
			_request = NULL;
		}
		_blockingQueue = false;

		while (!_inProgress.empty())
		{
			delete _inProgress.back();
			_inProgress.pop_back();
		}

        _queueMutex.lock();
		while (!_queue.empty())
		{
			delete _queue.back();
			_queue.pop_back();
		}
		_eventCallbackQueue.clear();
        _queueMutex.unlock();
	}

	void DefaultBrainCloudComms::shutdown()
	{
		resetCommunication();
		_isInitialized = false;
	}


	////////////////////////////////////////////////////////
	// Private methods
	////////////////////////////////////////////////////////

	bool DefaultBrainCloudComms::shouldRetryPacket()
	{
		for (unsigned int i = 0; i < _inProgress.size(); ++i)
		{
			ServerCall * serverCall = _inProgress[i];
			if (serverCall)
			{
				if (serverCall->getService() == ServiceName::AuthenticateV2
					&& (serverCall->getOperation() == ServiceOperation::Authenticate))
				{
					return false;
				}
			}
		}
		return true;
	}

	long DefaultBrainCloudComms::getRetryTimeoutMillis(int retryAttempt)
	{
		if (!shouldRetryPacket())
		{
			return _authenticationTimeoutMillis;
		}

		return _packetTimeouts[retryAttempt >= (int)_packetTimeouts.size() ? _packetTimeouts.size() - 1 : retryAttempt] * 1000;
	}

	int DefaultBrainCloudComms::getMaxSendAttempts()
	{
		if (!shouldRetryPacket())
		{
			return 1;
		}

		return (int)_packetTimeouts.size();
	}

	void DefaultBrainCloudComms::handleError(URLResponse const & response)
	{
#if ( defined(GAMECLIENT_DEBUGLEVEL)  )
		std::cout << "DefaultBrainCloudComms::handleError() status(" << response.getStatusCode()
			<< ") reasonPhrase: " << response.getReasonPhrase() << " data: " << response.getData() << std::endl;
#endif

		_retryCount++;

		if (_retryCount < getMaxSendAttempts())
		{
			// We haven't reached the maximum number of retries yet.  Try again.

			int64_t currentTime = TimeUtil::getCurrentTimeMillis();
			int64_t delta = currentTime - _packetSendTimeMillis;
			int64_t sleepTime = (int64_t)(getRetryTimeoutMillis(_retryCount));

			// still more time to spend sleeping
			if (delta > 0 && sleepTime > delta)
			{
				sleepTime -= delta;
			}
			// looks like we've waited long enough (but within max margin of 2 secs over retry timeout
			// in case we get some weird time altering event like system clock being changed)
			else if (delta > sleepTime && delta < (getRetryTimeoutMillis(_retryCount) + 2000))
			{
				sleepTime = 1;
			}

			if (_immediateRetryOnError)
			{
				sleepTime = 1; // well schedule it for *very soon* (1ms) if not immediately
			}

			_retryTimeMillis = currentTime + sleepTime;
		}
		else
		{
			_retryCount = 0;
			_retryTimeMillis = RETRY_TIME_NOT_RETRYING;
		}
	}

	void DefaultBrainCloudComms::updateKillSwitch(const std::string & service, const std::string & operation, int32_t statusCode)
	{
		if (statusCode == 900) return;

		if (_killSwitchService.length() == 0)
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

			if (_loggingEnabled)
				std::cout << "Client disabled due to repeated errors from a single API call: " << service << " | " << operation << std::endl;
		}
	}

	void DefaultBrainCloudComms::resetKillSwitch()
	{
		_killSwitchErrorCount = 0;
		_killSwitchService = "";
		_killSwitchOperation = "";
	}

	/**
	 * Creates a fake response to stop packets being sent to the server
	 * without a valid session.
	 */
	void DefaultBrainCloudComms::fakeErrorResponse(int32_t statusCode, int32_t reasonCode, const std::string & statusMessage)
	{
		size_t numMessages = _inProgress.size();
		Json::Value errorRoot;
		errorRoot["packetId"] = (Json::Int64) _expectedPacketId;
		Json::Value messages;
		for (size_t i = 0; i < numMessages; ++i)
		{
			Json::Value msg;

			msg["status"] = statusCode;
			msg["reason_code"] = reasonCode;
			msg["status_message"] = statusMessage;
			msg["severity"] = "ERROR";

			messages.append(msg);
		}
		errorRoot["responses"] = messages;

		if (_loggingEnabled)
		{
			// make it easier to read the json
			std::string dataOutput;

			Json::StyledWriter w;
			dataOutput = w.write(errorRoot);

			std::cout << "#BCC INCOMING status(" << _statusCodeCache
				<< ") reasonPhrase: " << _reasonCodeCache << " data: "
				<< dataOutput << std::endl;
		}

		handleResponseBundle(errorRoot);

		// Clear the inProgress queue
		while (!_inProgress.empty())
		{
			delete _inProgress.back();
			_inProgress.pop_back();
		}
	}

	void DefaultBrainCloudComms::ProcessSwitchResponse(Json::Value in_responses)
	{
		Json::FastWriter fastWriter;
		std::string switchToAppId = fastWriter.write(in_responses["switchToAppId"]);
		//if the response data contains a switchToAppId
		if(switchToAppId != "" || switchToAppId != "unknown")
		{
			_appId = switchToAppId;

			//update secretKey
			std::map<std::string, std::string>::const_iterator it = _secretMap.find(_appId);
			if (it != _secretMap.end())
			{
				_secretKey = it->second;
			}
		}
	}

	void DefaultBrainCloudComms::resetErrorCache()
	{
		_statusCodeCache = HTTP_FORBIDDEN;
		_reasonCodeCache = NO_SESSION;
		_statusMessageCache = "No session";
	}

	/**
	 * If there are requests in the queue, make a call to the server.
	 */
	void DefaultBrainCloudComms::createAndSendBundle()
	{
		bool authenticating = false;
		Json::Value messages(Json::arrayValue);

		// pull all the messages off the queue and release lock
        _queueMutex.lock();

		// reorder the queue if it has an authenticate message, since the server relies
		// upon the auth being the first message in the queue, if it doens't
		// and a message previous to it requires a session id, all items will be rejected
		bool bFoundAuthCallInCurrentMarker = false;
		if (_queue.size() > 1)
		{
			ServerCall * call = NULL;

			// loop over all the queue, if we find an auth call, stop remove it
			// and insert to the front of the queue
			std::vector<ServerCall*>::iterator it = _queue.begin();
			for (; it != _queue.end(); ++it)
			{
				call = (*it);
				// break if end of bundle marker
				if (call->isEndOfBundleMarker())
				{
					break;
				}

				if (call->getOperation() == ServiceOperation::Authenticate
					|| call->getOperation() == ServiceOperation::ResetEmailPassword
					|| call->getOperation() == ServiceOperation::ResetEmailPasswordAdvanced)
				{
					bFoundAuthCallInCurrentMarker = true;
					break;
				}
			}
			if (bFoundAuthCallInCurrentMarker && it != _queue.end())
			{
				_queue.erase(it);
				_queue.insert(_queue.begin(), call);
			}
		}

		// We want to cap the number of messages in each bundle.
		while (!_queue.empty() && (int)_inProgress.size() < _maxBundleSize)
		{
			ServerCall * call = _queue.front();
			if (call->isEndOfBundleMarker())
			{
				_queue.erase(_queue.begin());
				delete call;
				call = NULL;
				// if the first message is marker, just throw it away
				if (_inProgress.size() == 0)
				{
					continue;
				}
				else // cut off the bundle at the marker and toss marker away
				{
					break;
				}
			}
			if (call->getService() == ServiceName::HeartBeat
				&& call->getOperation() == ServiceOperation::Read)
			{
				// ignore heartbeat if other packets are in the bundle
				if (_queue.size() > 1 || _inProgress.size() > 0)
				{
					_queue.erase(_queue.begin());
					continue;
				}
			}
			messages.append(*(call->getPayload()));
			_inProgress.push_back(call);
			_queue.erase(_queue.begin());
			if (call->getOperation() == ServiceOperation::Authenticate
				|| call->getOperation() == ServiceOperation::ResetEmailPassword
				|| call->getOperation() == ServiceOperation::ResetEmailPasswordAdvanced)
			{
				authenticating = true;
			}

			// break, right away so that there is only ONE message with authenticate
			if (bFoundAuthCallInCurrentMarker)
				break;
		}

        _queueMutex.unlock();

		// if there are messages to send, do it
		if (messages.size() > 0)
		{
			std::string url = _serverUrl;
			URLRequest * request = NULL;

			_expectedPacketId = _packetId++;

			Json::Value allMessages;
			allMessages["messages"] = messages;
			allMessages["gameId"] = _appId;
			allMessages["sessionId"] = _sessionId;
			allMessages["packetId"] = (Json::Int64) _expectedPacketId;

			Json::StyledWriter writer;
			std::string dataString = writer.write(allMessages);
			dataString += "\r\n\r\n";

			if (_loggingEnabled)
			{
				std::cout << "#BCC OUTGOING " << dataString << std::endl;
			}

			if (_killSwitchEngaged)
			{
				fakeErrorResponse(900, CLIENT_DISABLED, "Client has been disabled due to repeated errors from a single API call");
				return;
			}

			// handle session errors locally
			if (!_isAuthenticated && !authenticating)
			{
				fakeErrorResponse(_statusCodeCache, _reasonCodeCache, _statusMessageCache);
				return;
			}

			request = new URLRequest(url);
			request->setData(dataString);
			request->setContentType("application/json");

			// Now we'll take our string append an application secret, and MD5 it, adding that to the HTTP header
			// This is based loosely on facebook signatures...
			// http://developers.facebook.com/docs/authentication/fb_sig/
			if (_secretKey.length())
			{
				// append secret key
				dataString += _secretKey;
				// get binary md5 digest

#if defined(BC_UWP)
                MD5 state(dataString);
                std::string sig = state.hexdigest();
#else
				//encode the string in an md5 format
				const int DIGEST_LENGTH = 16;
				md5_state_t     state;
				md5_byte_t      digest[DIGEST_LENGTH];

				md5_init(&state);
				md5_append(&state, (const md5_byte_t *)dataString.c_str(), (int)dataString.length());
				md5_finish(&state, digest);

				// convert each byte to string form
				char buf[DIGEST_LENGTH * 2 + 1];
				for (unsigned char i = 0; i < DIGEST_LENGTH; ++i)
				{
					sprintf(&buf[i * 2], "%02x", digest[i]);
				}

				// convert to uppercase std::string and add sig to header
				std::string sig((const char*)buf, DIGEST_LENGTH * 2);
				std::transform(sig.begin(), sig.end(), sig.begin(), toupper);
#endif
				request->addHeader(URLRequestHeader("X-SIG", sig));
				request->addHeader(URLRequestHeader("X-APPID", _appId));
			}

			// Store the currently active HTTP Request in the object.
			if (_request != NULL)
			{
				delete _request;
			}
			_request = request;

			if (_loader != NULL)
			{
				delete _loader;
			}

			startHttpRequest();
		}
	}

	// we assume loader mutex has been locked and var is null etc
	void DefaultBrainCloudComms::startHttpRequest()
	{
        _loader = URLLoader::create();
        if (_loader)
        {
            _loader->setTimeout((int)getRetryTimeoutMillis(_retryCount));
            _loader->load(_request);
        }

		_packetSendTimeMillis = TimeUtil::getCurrentTimeMillis();
		_retryTimeMillis = RETRY_TIME_NOT_RETRYING;
	}


	// UPLOADER STUFF
	void DefaultBrainCloudComms::cancelUpload(const char * in_fileUploadId)
	{
        _mutex.lock();
		tFileUploadsIterator it = _fileUploads.find(in_fileUploadId);
		if (it != _fileUploads.end())
		{
			it->second->cancelUpload();
		}
        _mutex.unlock();
	}

	double DefaultBrainCloudComms::getUploadProgress(const char * in_fileUploadId)
	{
		double progress = 0;
        _mutex.lock();
        tFileUploadsIterator it = _fileUploads.find(in_fileUploadId);
		if (it != _fileUploads.end())
		{
			progress = it->second->getProgress();
		}
		else
		{
			progress = -1;
		}
        _mutex.unlock();

		return progress;
	}

	int64_t DefaultBrainCloudComms::getUploadTotalBytesToTransfer(const char * in_fileUploadId)
	{
		int64_t totalBytesToTransfer = 0;
        _mutex.lock();
        tFileUploadsIterator it = _fileUploads.find(in_fileUploadId);
		if (it != _fileUploads.end())
		{
			totalBytesToTransfer = it->second->getTotalBytesToTransfer();
		}
		else
		{
			totalBytesToTransfer = -1;
		}
        _mutex.unlock();

		return totalBytesToTransfer;
	}

	int64_t DefaultBrainCloudComms::getUploadBytesTransferred(const char * in_fileUploadId)
	{
		int64_t bytesToTransfer = 0;
        _mutex.lock();
        tFileUploadsIterator it = _fileUploads.find(in_fileUploadId);
		if (it != _fileUploads.end())
		{
			bytesToTransfer = it->second->getBytesTransferred();
		}
		else
		{
			bytesToTransfer = -1;
		}
        _mutex.unlock();

		return bytesToTransfer;
	}

	void DefaultBrainCloudComms::startFileUpload(const Json::Value & in_jsonPrepareUploadResponse)
	{
		std::string fileUploadId = in_jsonPrepareUploadResponse["data"]["fileDetails"]["uploadId"].asString();
		if (fileUploadId.length() <= 0)
		{
			return;
		}

		std::string localPath = in_jsonPrepareUploadResponse["data"]["fileDetails"]["localPath"].asString();
		if (localPath.length() <= 0)
		{
			return;
		}

		int64_t fileSize = in_jsonPrepareUploadResponse["data"]["fileDetails"]["fileSize"].asInt64();
		if (fileSize == 0)
		{
			return;
		}

		// TODO: throttle file uploads to max #

        _mutex.lock();

		if (_fileUploads.find(fileUploadId) != _fileUploads.end())
		{
			// that can't be right....
            _mutex.unlock();
            return;
		}

        IFileUploader* uploader = IFileUploader::create();
        if (uploader)
        {
            uploader->enableLogging(_loggingEnabled);
            uploader->setUploadLowTransferRateThreshold(_uploadLowTransferRateThresholdBytesPerSec);
            uploader->setUploadLowTransferRateTimeout(_uploadLowTransferRateTimeoutSecs);
            _fileUploads[fileUploadId] = uploader;
            if (!uploader->uploadFile(_sessionId, fileUploadId, localPath, fileSize, _uploadUrl))
            {
                _fileUploads.erase(_fileUploads.find(fileUploadId));
                delete uploader;
            }
        }

        _mutex.unlock();
    }


}
