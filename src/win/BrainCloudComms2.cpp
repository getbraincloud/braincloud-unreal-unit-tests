#ifndef __ANDROID__


#include <string>
#include <iostream>
#include <sstream>
#include <chrono>

#include "json/json.h"
#include "cpprest/http_client.h"

#include "braincloud/internal/win/BrainCloudComms2.h"
#include "braincloud/internal/win/MD5.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/http_codes.h"
#include "braincloud/reason_codes.h"
#include "braincloud/internal/win/CppRestFileUploader.h"

#ifdef WINAPI
#include <tchar.h>
#endif
//#define VERBOSE 1

#define DEFAULT_AUTHENTICATION_TIMEOUT_MILLIS 15000

//using System.Runtime.InteropServices.WindowsRuntime;
using namespace web::http;

namespace BrainCloud
{
    BrainCloudComms2::BrainCloudComms2(BrainCloudClient* in_client) : IBrainCloudComms(in_client),
        _tearDownThread(false)
    {
    }

    BrainCloudComms2::~BrainCloudComms2()
    {
    }

    void BrainCloudComms2::initialize(const char * serverURL, const char * appId, const char * secretKey)
    {
#ifdef VERBOSE
        std::cout << "Entering initialize(), initialized:" << _isInitialized << std::endl;
#endif
        if (_isInitialized)
        {
            resetCommunication();
        }
        if (!_isInitialized)
        {
            _isInitialized = true;
            _isAuthenticated = false;
            _serverUrl = serverURL;
            _uploadUrl = serverURL;
            size_t index = _uploadUrl.find("/dispatcherv2");
            if (index != -1)
            {
                _uploadUrl = _uploadUrl.substr(0, index);
            }
            _uploadUrl += "/uploader";
            _appId = appId;
            _secretKey = secretKey;

            _processQueue = std::thread(&BrainCloudComms2::processQueue, this);
        }
#ifdef VERBOSE
        std::cout << "Exiting initialize()" << std::endl;
#endif
    }

    void BrainCloudComms2::registerEventCallback(IEventCallback *in_eventCallback)
    {
        _eventCallback = in_eventCallback;
    }

    void BrainCloudComms2::deregisterEventCallback()
    {
        _eventCallback = NULL;
    }

    void BrainCloudComms2::registerFileUploadCallback(IFileUploadCallback *in_fileUploadCallback)
    {
        std::unique_lock<std::recursive_mutex> lock(_uploaderMutex);
        _fileUploadCallback = in_fileUploadCallback;
    }

    void BrainCloudComms2::deregisterFileUploadCallback()
    {
        std::unique_lock<std::recursive_mutex> lock(_uploaderMutex);
        _fileUploadCallback = NULL;
    }

    void BrainCloudComms2::registerRewardCallback(IRewardCallback *in_rewardCallback)
    {
        _rewardCallback = in_rewardCallback;
    }

    void BrainCloudComms2::deregisterRewardCallback()
    {
        _rewardCallback = NULL;
    }

    void BrainCloudComms2::registerGlobalErrorCallback(IGlobalErrorCallback *in_globalErrorCallback)
    {
        _globalErrorCallback = in_globalErrorCallback;
    }

    void BrainCloudComms2::deregisterGlobalErrorCallback()
    {
        _globalErrorCallback = NULL;
    }

    void BrainCloudComms2::registerNetworkErrorCallback(INetworkErrorCallback *in_networkErrorCallback)
    {
    }

    void BrainCloudComms2::deregisterNetworkErrorCallback()
    {
    }

    void BrainCloudComms2::addToQueue(ServerCall *serverCall)
    {
#ifdef VERBOSE
        std::cout << "Entering addToQueue()" << std::endl;
#endif
        std::shared_ptr<ServerCall> sc(serverCall);
        std::unique_lock<std::mutex> lock(_queueMutex);

        _messageQueue.push_back(sc);
        _waitForMessage.notify_one();
#ifdef VERBOSE
        std::cout << "Exiting addToQueue()" << std::endl;
#endif
    }

    void BrainCloudComms2::enableNetworkErrorMessageCaching(bool in_enabled)
    {
    }

    void BrainCloudComms2::retryCachedMessages()
    {
    }

    void BrainCloudComms2::flushCachedMessages(bool in_sendApiErrorCallbacks)
    {}




    void BrainCloudComms2::processQueue()
    {
#ifdef VERBOSE
        std::cout << "Entering processQueue()" << std::endl;
#endif
        while (!_tearDownThread)
        {
            std::unique_lock<std::mutex> lock(_inProgressMutex);
            fillInProgress();

            if (!_inProgressQueue.empty())
            {
                while (!_tearDownThread)
                {
                    if (processMessages())
                    {
                        break;
                    }
                    // processMessages increments retryCount before returning
                    long totalSleepTimeMs = getRetryTimeoutMillis(_retryCount - 1);
                    while (totalSleepTimeMs > 0 && !_tearDownThread)
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                        totalSleepTimeMs -= 100;
                    }
                }
            }
        }
#ifdef VERBOSE
        std::cout << "Thread about to exit" << std::endl;
        std::cout << "Exiting  processQueue()" << std::endl;
#endif
    }


    void BrainCloudComms2::log(const std::string & s)
    {
        if (_loggingEnabled)
        {
#ifdef WINAPI
            // additionally log to the vs console if available
            OutputDebugStringA(s.c_str());
#endif
            std::cout << s << std::endl;
        }
    }

    void BrainCloudComms2::fillInProgress()
    {
#ifdef VERBOSE
        std::cout << "Entering fillInProgress()" << std::endl;
#endif

        std::unique_lock<std::mutex> lock(_queueMutex);

        while (_messageQueue.empty() && !_tearDownThread)
        {
            if (_heartbeatInterval > 0)
            {
                std::_Cv_status res = _waitForMessage.wait_for(lock, std::chrono::milliseconds(_heartbeatInterval));
                if (res == std::cv_status::timeout)
                {
                    std::shared_ptr<ServerCall> sc(new ServerCall(ServiceName::HeartBeat, ServiceOperation::Read, Json::Value(Json::nullValue), NULL));
                    _messageQueue.push_back(sc);
                }
            }
            else
            {
                _waitForMessage.wait(lock);
            }
        }

		while (!_messageQueue.empty() && !_tearDownThread && _messageQueue.size() < _maxBundleSize)
        {
            std::shared_ptr<ServerCall> message = _messageQueue.front();
			_messageQueue.pop_front();

			if (message->isEndOfBundleMarker())
			{
				// if the first message is marker, just throw it away
				if (_messageQueue.empty())
				{
					continue;
				}
				else // cut off the bundle at the marker and toss marker away
				{
					break;
				}
			}

            _inProgressQueue.push_back(message);
        }
#ifdef VERBOSE
        std::cout << "Exiting fillInProgress()" << std::endl;
#endif
    }

    bool BrainCloudComms2::processMessages()
    {
        try
        {
            std::string dataString = getDataString();

            if (_loggingEnabled)
            {
                Json::StyledWriter styledWriter;
                Json::Reader reader;
                Json::Value logRoot;
                reader.parse(dataString, logRoot);
                std::ostringstream s;
                s << "#BCC OUTGOING " << styledWriter.write(logRoot);
                log(s.str());
            }

            //dont send packet if not authenticated
            if (!_isAuthenticated)
            {
                bool isAuth = false;
                std::deque<std::shared_ptr < ServerCall > >::iterator it = _inProgressQueue.begin();
                for (; it != _inProgressQueue.end(); it++)
                {
                    if ((*it)->getOperation() == ServiceOperation::Authenticate ||
                        (*it)->getOperation() == ServiceOperation::ResetEmailPassword)
                    {
                        isAuth = true;
                        break;
                    }
                }

                if (!isAuth)
                {
                    handleNoAuth();
                    return true;
                }
            }

            Json::Reader reader;
            Json::FastWriter writer;

            utility::string_t url = utility::conversions::to_string_t(_serverUrl);
            web::http::client::http_client_config client_config;

            int httpTimeout = getRetryTimeoutMillis(_retryCount);
            if (httpTimeout < 1000)
            {
                httpTimeout = 1000;
            }
            client_config.set_timeout(utility::seconds(httpTimeout / 1000));

            web::http::client::http_client client(url, client_config);
            web::http::http_request request;
            request.set_method(methods::POST);
            request.headers().add(web::http::header_names::content_type, L"application/json");

            utility::string_t body = utility::conversions::to_string_t(dataString);
            request.set_body(body);

            if (_secretKey.length())
            {
                std::string secret = md5(dataString + _secretKey);
                utility::string_t secretHeader = utility::conversions::to_string_t(secret);
                // add signature to header
                request.headers().add(L"X-SIG", secretHeader);
            }

            pplx::task<web::http::http_response> respTask = client.request(request);
            web::http::http_response response = respTask.get(); //blocks
            web::http::status_code statusCode = response.status_code();

            uint32_t reasonCode = 0;
            if (statusCode == web::http::status_codes::RequestTimeout)
            {
                reasonCode = CLIENT_NETWORK_ERROR_TIMEOUT;
            }

            if (statusCode != web::http::status_codes::OK)
            {
                if (statusCode == web::http::status_codes::RequestTimeout ||
                    statusCode == web::http::status_codes::ServiceUnavailable)
                {
                    _retryCount++;
                    if (_retryCount < getMaxSendAttempts())
                    {
                        reportWarning(statusCode, reasonCode, "Retrying", _retryCount);
                        return false;
                    }
                }
                reportError(HTTP_CUSTOM, CLIENT_NETWORK_ERROR_TIMEOUT, "Retry count exhausted");
                _retryCount = 0;
                _inProgressQueue.clear();
                return true;
            }

            _retryCount = 0;

            pplx::task<utility::string_t> extractTask = response.extract_string();
            utility::string_t responseBody = extractTask.get();
            std::string result = utility::conversions::to_utf8string(responseBody);

            if (statusCode != web::http::status_codes::OK)
            {
                reportError(HTTP_CUSTOM, CLIENT_NETWORK_ERROR_TIMEOUT, result);
                _inProgressQueue.clear();
                return true;
            }

            Json::Value root;

            // This generates parsing error callback
            if (result.length() > 0)
            {
                if (!reader.parse(result, root))
                {
                    reportParseError();
                    _inProgressQueue.clear();
                    return true;
                }
            }

            int64_t receivedPacketId = root["packetId"].asInt64();
            if (_expectedPacketId == NO_PACKET_EXPECTED || receivedPacketId != _expectedPacketId)
            {
                if (_loggingEnabled)
                {
                    std::ostringstream s;
                    s << "#BCC Ignoring packet id " << receivedPacketId << ", expected id " << _expectedPacketId;
                    log(s.str());
                }
                return true;
            }
            _expectedPacketId = NO_PACKET_EXPECTED;

            if (_loggingEnabled)
            {
                Json::StyledWriter styledWriter;
                std::ostringstream s;
                s << "#BCC INCOMING " << styledWriter.write(root);
                log(s.str());
            }

            Json::Value messages = root["responses"];
            reportResults(messages);

            if (_eventCallback)
            {
                Json::Value events = root["events"];
                if (!events.isNull())
                {
                    Json::FastWriter writer;
                    Json::Value eventsRoot;
                    eventsRoot["events"] = events;
                    std::string jsonEvents = writer.write(eventsRoot);
                    _eventCallback->eventCallback(jsonEvents);
                }
            }

            _inProgressQueue.clear();
        }
        catch (web::http::http_exception& e)
        {
#if VERBOSE
            std::cerr << "HttpException: " << e.what() << std::endl;
#endif
            reportError(HTTP_CUSTOM, CLIENT_NETWORK_ERROR_TIMEOUT, e.what());
            _inProgressQueue.clear();
        }
        catch (std::exception& e)
        {
#if VERBOSE
            std::cerr << "Exception: " << e.what() << std::endl;
#endif
            reportError(HTTP_CUSTOM, CLIENT_NETWORK_ERROR_TIMEOUT, e.what());
            _inProgressQueue.clear();
        }
        return true;
    }

    /**
    * Creates a fake response to stop packets being sent to the server
    * without a valid session.
    */
    void BrainCloudComms2::handleNoAuth()
    {
        Json::Value errorRoot;
        errorRoot["packetId"] = (Json::Int64) _expectedPacketId;

        Json::Value messages;
        size_t numMessages = _inProgressQueue.size();
        for (size_t i = 0; i < numMessages; ++i)
        {
            Json::Value msg;

            msg["status"] = _statusCodeCache;
            msg["reason_code"] = _reasonCodeCache;
            msg["status_message"] = _statusMessageCache;
            msg["severity"] = "ERROR";

            messages.append(msg);
        }
        errorRoot["responses"] = messages;

        if (_loggingEnabled)
        {
            Json::StyledWriter styledWriter;
            std::ostringstream s;
            s << "#BCC INCOMING " << styledWriter.write(errorRoot);
            log(s.str());
        }

        reportResults(messages);

        _expectedPacketId = NO_PACKET_EXPECTED;
        _inProgressQueue.clear();
    }

    std::string BrainCloudComms2::getDataString()
    {
        Json::FastWriter writer;
        Json::Value messages(Json::arrayValue);

        std::deque<std::shared_ptr < ServerCall > >::iterator it = _inProgressQueue.begin();

        for (; it != _inProgressQueue.end(); it++)
        {
            messages.append(*((*it)->getPayload()));
        }

        _expectedPacketId = _packetId++;
        Json::Value allMessages;
        allMessages["messages"] = messages;
        allMessages["gameId"] = _appId;
        allMessages["sessionId"] = _sessionId;
        allMessages["packetId"] = _expectedPacketId;

        std::string dataString = writer.write(allMessages);
        dataString += "\r\n\r\n";
        return dataString;
    }

    void BrainCloudComms2::reportParseError()
    {
        reportError(HTTP_UNAVAILABLE, NO_REASON_CODE, "Unable to parse response");
    }

    void BrainCloudComms2::reportError(uint32_t statusCode, uint32_t reasonCode, const std::string statusMessage)
    {
        uint32_t errorStatusCode = statusCode;
        uint32_t errorReasonCode = reasonCode;
        if (statusCode == web::http::status_codes::ServiceUnavailable)
        {
            errorStatusCode = HTTP_CUSTOM;
            errorReasonCode = CLIENT_NETWORK_ERROR_TIMEOUT;
        }

        std::string jsonErrorStr;
        if (_oldStyleStatusMessageErrorCallback)
        {
            jsonErrorStr = statusMessage;
        }
        else
        {
            Json::FastWriter writer;
            Json::Value errorJsonObj;
            errorJsonObj["status"] = errorStatusCode;
            errorJsonObj["reason_code"] = errorReasonCode;
            errorJsonObj["status_message"] = statusMessage;
            errorJsonObj["severity"] = "ERROR";
            jsonErrorStr = writer.write(errorJsonObj);
        }

        std::deque<std::shared_ptr < ServerCall > >::iterator it = _inProgressQueue.begin();
        for (; it != _inProgressQueue.end(); it++)
        {
            IServerCallback* callback = (*it)->getCallback();
            if (callback != NULL)
            {
                callback->serverError((*it)->getService(), (*it)->getOperation(), errorStatusCode, errorReasonCode, jsonErrorStr);
            }
        }
    }

    void BrainCloudComms2::reportWarning(uint32_t statusCode, uint32_t reasonCode, const std::string data, uint8_t retryCount)
    {
        std::deque<std::shared_ptr < ServerCall > >::iterator it = _inProgressQueue.begin();
        for (; it != _inProgressQueue.end(); it++)
        {
            IServerCallback* callback = (*it)->getCallback();
            if (callback != NULL)
            {
                callback->serverWarning((*it)->getService(), (*it)->getOperation(), statusCode, reasonCode, retryCount, data);
            }
        }
    }

    void BrainCloudComms2::reportResults(Json::Value& root)
    {
        Json::FastWriter writer;
        std::deque<std::shared_ptr < ServerCall > >::iterator it = _inProgressQueue.begin();
        Json::Value apiRewards = Json::nullValue;

        for (int ndx = 0; it != _inProgressQueue.end(); it++, ndx++)
        {
            ServiceName service = (*it)->getService();
            ServiceOperation operation = (*it)->getOperation();

            int statusCode = root[ndx]["status"].asInt();
            if (statusCode == HTTP_OK || (!_errorCallbackOn202 && statusCode == 202))
            {
                filterIncomingMessages((*it).get(), root[ndx]);

                Json::Value rewards = Json::nullValue;
                // authenticate
                if (service == ServiceName::AuthenticateV2 && operation == ServiceOperation::Authenticate)
                {
                    resetErrorCache();

                    if (!root[ndx]["data"]["rewards"]["rewards"].empty())
                    {
                        rewards = root[ndx]["data"]["rewards"];
                    }
                }
                // player stat increment or statistics event trigger
                else if ((service == ServiceName::PlayerStatistics && operation == ServiceOperation::Update)
                    || (service == ServiceName::PlayerStatisticsEvent
                    && (operation == ServiceOperation::Trigger || operation == ServiceOperation::TriggerMultiple)))
                {
                    if (!root[ndx]["data"]["rewards"].empty())
                    {
                        rewards = root[ndx]["data"];
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
            else
            {
                int reasonCode = root[ndx]["reason_code"].asInt();
                if (reasonCode == PLAYER_SESSION_EXPIRED
                    || reasonCode == NO_SESSION
                    || reasonCode == PLAYER_SESSION_LOGGED_OUT)
                {
                    _isAuthenticated = false;
                    _sessionId.clear();

                    //cache error if session related
                    _statusCodeCache = statusCode;
                    _reasonCodeCache = reasonCode;
                    _statusMessageCache = root[ndx]["status_message"].asString();
                }

                if (operation == ServiceOperation::Logout)
                {
                    if (reasonCode == CLIENT_NETWORK_ERROR_TIMEOUT)
                    {
                        _isAuthenticated = false;
                        _sessionId.clear();
                    }
                }
            }

            IServerCallback* callback = (*it)->getCallback();
            if (callback != NULL)
            {
                if (statusCode == HTTP_OK || (!_errorCallbackOn202 && statusCode == 202))
                {
                    callback->serverCallback(service, operation, writer.write(root[ndx]));
                }
                else
                {
                    int reasonCode = root[ndx]["reason_code"].asInt();
                    std::string jsonError;
                    if (_oldStyleStatusMessageErrorCallback)
                    {
                        jsonError = root[ndx]["status_message"].asString();
                    }
                    else
                    {
                        jsonError = writer.write(root[ndx]);
                    }
                    callback->serverError(service, operation, statusCode, reasonCode, jsonError);

                    if (_globalErrorCallback != NULL)
                    {
                        _globalErrorCallback->globalError(service, operation, statusCode, reasonCode, jsonError);
                    }
                }
            }
        }

        if (_rewardCallback)
        {
            if (!apiRewards.isNull())
            {
                std::string rewards = writer.write(apiRewards);
                _rewardCallback->rewardCallback(rewards);
            }
        }
    }

    void BrainCloudComms2::sendHeartbeat()
    {
        ServerCall * sc = new ServerCall(ServiceName::HeartBeat, ServiceOperation::Read, Json::Value(Json::nullValue), NULL);
        addToQueue(sc);
    }

    void BrainCloudComms2::resetCommunication()
    {
#ifdef VERBOSE
        std::cout << "Entering resetCommunication()" << std::endl;
#endif
        _tearDownThread = true;
        _heartbeatInterval = 0; // to prevent queue thread from going back into a heartbeat wait cycle
        _waitForMessage.notify_all(); // to kick the thread lock
        if (_processQueue.joinable())
        {
            // should die within 100ms max
            _processQueue.join();
        }
        _tearDownThread = false;
        _isInitialized = false;
        _isAuthenticated = false;
        _sessionId.clear();
        resetErrorCache();
#ifdef VERBOSE
        std::cout << "Exiting resetCommunication()" << std::endl;
#endif
    }

    void BrainCloudComms2::shutdown()
    {
        resetCommunication();
    }

    void BrainCloudComms2::runCallbacks()
    {
        std::unique_lock<std::recursive_mutex> lock(_uploaderMutex);
        runCallbacksFileUpload();
    }

    bool BrainCloudComms2::shouldRetryPacket()
    {
        std::deque<std::shared_ptr < ServerCall > >::iterator it = _inProgressQueue.begin();
        for (; it != _inProgressQueue.end(); it++)
        {
            if ((*it)->getService() == ServiceName::AuthenticateV2
                && (*it)->getOperation() == ServiceOperation::Authenticate)
            {
                return false;
            }
        }
        return true;
    }

    long BrainCloudComms2::getRetryTimeoutMillis(int retryAttempt)
    {
        if (!shouldRetryPacket())
        {
            return _authenticationTimeoutMillis;
        }

        return _packetTimeouts[retryAttempt >= (int)_packetTimeouts.size() ? _packetTimeouts.size() - 1 : retryAttempt] * 1000;
    }

    int BrainCloudComms2::getMaxSendAttempts()
    {
        if (!shouldRetryPacket())
        {
            return 1;
        }

        return (int)_packetTimeouts.size();
    }

    void BrainCloudComms2::resetErrorCache()
    {
        _statusCodeCache = HTTP_FORBIDDEN;
        _reasonCodeCache = NO_SESSION;
        _statusMessageCache = "No session";
    }

    void BrainCloudComms2::cancelUpload(const char * in_fileUploadId)
    {
        std::unique_lock<std::recursive_mutex> lock(_uploaderMutex);
        tFileUploadsIterator it = _fileUploads.find(in_fileUploadId);
        if (it != _fileUploads.end())
        {
            it->second->cancelUpload();
        }
    }

    double BrainCloudComms2::getUploadProgress(const char * in_fileUploadId)
    {
        double progress = 0;
        std::unique_lock<std::recursive_mutex> lock(_uploaderMutex);
        tFileUploadsIterator it = _fileUploads.find(in_fileUploadId);
        if (it != _fileUploads.end())
        {
            progress = it->second->getProgress();
        }
        else
        {
            progress = -1;
        }

        return progress;
    }

    int64_t BrainCloudComms2::getUploadTotalBytesToTransfer(const char * in_fileUploadId)
    {
        int64_t totalBytesToTransfer = 0;
        std::unique_lock<std::recursive_mutex> lock(_uploaderMutex);
        tFileUploadsIterator it = _fileUploads.find(in_fileUploadId);
        if (it != _fileUploads.end())
        {
            totalBytesToTransfer = it->second->getTotalBytesToTransfer();
        }
        else
        {
            totalBytesToTransfer = -1;
        }

        return totalBytesToTransfer;
    }

    int64_t BrainCloudComms2::getUploadBytesTransferred(const char * in_fileUploadId)
    {
        int64_t bytesToTransfer = 0;
        std::unique_lock<std::recursive_mutex> lock(_uploaderMutex);
        tFileUploadsIterator it = _fileUploads.find(in_fileUploadId);
        if (it != _fileUploads.end())
        {
            bytesToTransfer = it->second->getBytesTransferred();
        }
        else
        {
            bytesToTransfer = -1;
        }

        return bytesToTransfer;
    }

    void BrainCloudComms2::startFileUpload(const Json::Value & in_jsonPrepareUploadResponse)
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

        std::unique_lock<std::recursive_mutex> lock(_uploaderMutex);

        // TODO: throttle file uploads to max #

        if (_fileUploads.find(fileUploadId) != _fileUploads.end())
        {
            // that can't be right....
            return;
        }

        CppRestFileUploader *uploader = new CppRestFileUploader();
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
};

#endif //__ANDROID__
