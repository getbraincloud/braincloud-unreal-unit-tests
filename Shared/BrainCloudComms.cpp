#if defined(__APPLE__) && !defined(HG_PLATFORM_BB)
#include "TargetConditionals.h"
#endif

#include "HTTP/cURLLoader.h"
#include "HTTP/cURLFileUploader.h"
#include "BrainCloudClient.h"
#include "BrainCloudComms.h"

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <ctype.h>
#include <string>
#include <list>
#include <sstream>
#include "HGEngine/md5x.h"


namespace BrainCloud {
    
    ////////////////////////////////////////////////////////
    // Constructors
    ////////////////////////////////////////////////////////
    
    /**
     * Constructor...
     */
    BrainCloudComms::BrainCloudComms() :
    _heartbeatTimer(NULL),
    _loader(NULL),
    _request(NULL),
    _retryTimer(NULL)
    
    {
        
        pthread_mutex_init(&_loaderMutex, NULL);
        pthread_mutex_init(&_queueMutex, NULL);
        
        pthread_mutexattr_t mutexAtts;
        pthread_mutexattr_init(&mutexAtts);
        pthread_mutexattr_settype(&mutexAtts, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&_mutex, &mutexAtts);
        pthread_mutexattr_destroy(&mutexAtts);
        
        resetErrorCache();
    }
    
    /**
     * Destructor
     */
    BrainCloudComms::~BrainCloudComms( )
    {
        pthread_mutex_destroy( &_loaderMutex );
        pthread_mutex_destroy( &_queueMutex );
        pthread_mutex_destroy( &_mutex );
    }
    
    
    ////////////////////////////////////////////////////////
    // Public methods
    ////////////////////////////////////////////////////////
    
    void BrainCloudComms::initialize(const char * serverURL, const char * gameId, const char * secretKey)
    {
        _serverUrl = serverURL;
        _uploadUrl = serverURL;
        size_t index = _uploadUrl.find("/dispatcherv2");
        if (index != std::string::npos)
        {
            _uploadUrl = _uploadUrl.substr(0, index);
        }
        _uploadUrl += "/uploader";
        _gameId = gameId;
        _secretKey = secretKey;
        _isInitialized = true;
    }
    
    /**
     * If data was received and needs to be communicated to the app layer, this is where it will be done
     */
    void BrainCloudComms::runCallbacks()
    {
        pthread_mutex_lock( &_mutex );
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
        
        pthread_mutex_unlock( &_mutex );
    }
    
    void BrainCloudComms::registerEventCallback(IEventCallback *in_eventCallback)
    {
        pthread_mutex_lock( &_mutex );
        _eventCallback = in_eventCallback;
        pthread_mutex_unlock( &_mutex );
    }
    
    void BrainCloudComms::deregisterEventCallback()
    {
        pthread_mutex_lock( &_mutex );
        _eventCallback = NULL;
        pthread_mutex_unlock( &_mutex );
    }
    
    void BrainCloudComms::registerFileUploadCallback(IFileUploadCallback *in_fileUploadCallback)
    {
        pthread_mutex_lock(&_mutex);
        _fileUploadCallback = in_fileUploadCallback;
        pthread_mutex_unlock(&_mutex);
    }
    
    void BrainCloudComms::deregisterFileUploadCallback()
    {
        pthread_mutex_lock(&_mutex);
        _fileUploadCallback = NULL;
        pthread_mutex_unlock(&_mutex);
    }
    
    void BrainCloudComms::registerRewardCallback(IRewardCallback *in_rewardCallback)
    {
        pthread_mutex_lock( &_mutex );
        _rewardCallback = in_rewardCallback;
        pthread_mutex_unlock( &_mutex );
    }
    
    void BrainCloudComms::deregisterRewardCallback()
    {
        pthread_mutex_lock( &_mutex );
        _rewardCallback = NULL;
        pthread_mutex_unlock( &_mutex );
    }
    
    
    /**
     * Add a new server call definition to the request queue.
     */
    void BrainCloudComms::addToQueue( ServerCall * sc )
    {
        // Add the new ServerCall to the end of the queue.
        pthread_mutex_lock( &_queueMutex );
        
        _queue.push_back( sc );
        pthread_mutex_unlock( &_queueMutex );
        
        // If no requests are in progress, make a request...
        pthread_mutex_lock( &_loaderMutex );
        
        if ( _loader == NULL ) {
            startLoader( ); // Always releases _loaderMutex
        }
        else {
            pthread_mutex_unlock( &_loaderMutex );
        }
    }
    
    
    /**
     * Handle the alarm resulting from a Timer firing.
     *
     * @param timer - Timer object which just fired
     */
    void BrainCloudComms::handleAlarm( Timer * timer )
    {
        // Make sure the Timer is valid.
        if ( timer != NULL ) {
            // Figure out which timer just fired.
            if ( timer == _heartbeatTimer && _isAuthenticated)
            {
                heartbeat();
                
                // The Heartbeat Timer is marked as non-repeatable.
                // This means the object is going to destroy itself immediately.
                // Do NOT try to stop the Timer.  Just assign it to NULL.
                _heartbeatTimer = NULL;
            }
            else if ( timer == _retryTimer )
            {
                resend();
                
                // The Retry Timer is marked as non-repeatable.
                // This means the object is going to destroy itself immediately.
                // Do NOT try to stop the Timer.  Just assign it to NULL.
                _retryTimer = NULL;
            }
            else {
                // Unknown timer.
                timer->stop();
            }
        }
    }  // end BrainCloudComms::handleAlarm
    
    
    void BrainCloudComms::cacheResult( URLResponse const & in_response )
    {
        pthread_mutex_lock( &_loaderMutex );
        _responses.push_back(in_response);
        pthread_mutex_unlock( &_loaderMutex );
    }
    
    
    void BrainCloudComms::handleResponseBundle(Json::Value & root)
    {
        Json::FastWriter writer;
        Json::Value messages = root["responses"];
        Json::Value apiRewards(Json::nullValue);
        int64_t receivedPacketId = root["packetId"].asInt64();
        if (_expectedPacketId == NO_PACKET_EXPECTED || receivedPacketId != _expectedPacketId)
        {
            // drop the packet - this is the wrong packet id
            if (_loggingEnabled)
            {
                std::cout << "#BCC Dropping packet id " << receivedPacketId << " as we're expecting " << _expectedPacketId << std::endl;
            }
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
        
        if (BrainCloudClient::SINGLE_THREADED)
        {
            pthread_mutex_lock( &_mutex );
        }
        
        for( unsigned int i = 0; i < _inProgress.size(); ++i )
        {
            ServerCall * serverCall = _inProgress[i];
            
            bool error = false;
            int reasonCode = messages[i]["reason_code"].asInt(); // will be 0 if json not present
            int statusCode = messages[i]["status"].asInt();
            std::string jsonError = "";
            if (statusCode > 299)
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
            
            if (!error)
            {
                filterIncomingMessages(serverCall, messages[i]);
            }
            else
            {
                if (reasonCode == PLAYER_SESSION_EXPIRED
                    || reasonCode == NO_SESSION
                    || reasonCode == PLAYER_SESSION_LOGGED_OUT)
                {
                    _isAuthenticated = false;
                    _sessionId.clear();
                    _heartbeatTimer = NULL;
                    
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
                        _heartbeatTimer = NULL;
                    }
                }
            }
            
            IServerCallback* callback = serverCall->getCallback();
            if (callback)
            {
                // if we're using a single threaded application, all callbacks must be called on the main thread
                if (BrainCloudClient::SINGLE_THREADED)
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
                else // if we aren't single threaded, call callbacks immediately
                {
                    if (error)
                    {
                        callback->serverError( serverCall->getService(), serverCall->getOperation(), statusCode, reasonCode, jsonError );
                    }
                    else
                    {
                        callback->serverCallback( serverCall->getService(), serverCall->getOperation(), writer.write(messages[i]) );
                    }
                }
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
                if (BrainCloudClient::SINGLE_THREADED)
                {
                    _rewardCallbackQueue.push_back(jsonApiRewards);
                }
                else
                {
                    _rewardCallback->rewardCallback(jsonApiRewards);
                }
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
                if (BrainCloudClient::SINGLE_THREADED)
                {
                    _eventCallbackQueue.push_back(jsonEvents);
                }
                else
                {
                    _eventCallback->eventCallback(jsonEvents);
                }
            }
        }
        
        if (BrainCloudClient::SINGLE_THREADED)
        {
            pthread_mutex_unlock( &_mutex );
        }
    }
    
    /**
     * This gets called from the URLLoader via a callback...
     * Used to retrieve data from our call
     *
     * @param event
     */
    void BrainCloudComms::handleResult( URLResponse const & response )
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
        if( _inProgress.empty() )
        {
            return;
        }
        
        
        bool processNextRequest = false;
        
        if (responseStatus != HTTP_OK
            || responseData.length() <= 0
            || !reader.parse(responseData, root))
        {
            // deals with retry timers
            handleError(response);
            
            // handleError method sets retry count to zero if we've hit retry limit.
            // this is not a good way to check the value but hard to unwind the code.
            bool retry = (_retryCount != 0);
            
            // if ran out of retries, fake an error response
            if (!retry)
            {
                size_t numMessages = _inProgress.size();
                Json::Value errorRoot;
                errorRoot["packetId"] = (Json::Int64) _expectedPacketId;
                Json::Value messages;
                for (size_t i = 0; i < numMessages; ++i)
                {
                    Json::Value msg;
                    if (responseStatus == HTTP_OK
                        || responseStatus == HTTP_CUSTOM
                        || responseStatus == HTTP_UNAVAILABLE) //503 from bc means we should keep trying but are out of retries
                    {
                        msg["status"] = HTTP_CUSTOM;
                        msg["reason_code"] = CLIENT_NETWORK_ERROR_TIMEOUT;
                        msg["status_message"] = "Network timeout";
                        msg["severity"] = "ERROR";
                    }
                    else
                    {
                        msg["status"] = responseStatus;
                        msg["reason_code"] = 0;
                        msg["status_message"] = responseData;
                        msg["severity"] = "ERROR";
                    }
                    messages.append(msg);
                }
                errorRoot["responses"] = messages;
                handleResponseBundle(errorRoot);
                processNextRequest = true;
            }
        }
        else
        {
            handleResponseBundle(root);
            processNextRequest = true;
        }
        
        if (processNextRequest)
        {
            _retryCount = 0;
            _expectedPacketId = NO_PACKET_EXPECTED;
            
            if( _retryTimer != NULL ) {
                _retryTimer->stop();
            }
            _retryTimer = NULL;
            
            // Clear the inProgress queue
            while( !_inProgress.empty() ) {
                delete _inProgress.back();
                _inProgress.pop_back();
            }
            
            // Make another call if there is more data.
            pthread_mutex_lock( &_loaderMutex );
            
            if( _loader != NULL ) {
                delete _loader;
            }
            _loader = NULL;
            
            // NOTE:  startLoader() always releases _loaderMutex
            if( !startLoader() && _isAuthenticated ) {
                // Nothing being sent, start the heartbeat timer to fire in
                // 1 minute (only if we are authenticated!)
                _heartbeatTimer = NULL;
                
                if (_heartbeatInterval > 0) {
                    _heartbeatTimer = new Timer( this, _heartbeatInterval, NULL, 1 );
                }
            }
        }
        
    }  // end BrainCloudComms::handleResult
    
    
    /**
     * This method would normally just be in the BrainCloud, but because we call
     * it from within the manager via a timer, we're placing it here...
     */
    void BrainCloudComms::heartbeat( )
    {
        ServerCall * sc = new ServerCall( ServiceName::HeartBeat, ServiceOperation::Read, Json::Value(Json::nullValue), NULL );
        addToQueue( sc );
    }
    
    void BrainCloudComms::resetCommunication()
    {
        _isAuthenticated = false;
        _sessionId.clear();
        
        resetErrorCache();
        
        if( _retryTimer != NULL ) {
            _retryTimer->stop();
            _retryTimer = NULL;
        }
        
        pthread_mutex_lock(&_loaderMutex);
        if( _loader != NULL ) {
            
            // preston - causes a memory leak but we have no safe way to wait
            // for the loader thread at this point. All we can do is null out the
            // client so that callbacks will not hit the comms object.
            //_loader->close(true);
            //delete _loader;
            
            _loader->setClient(NULL);
            
            _loader = NULL;
        }
        pthread_mutex_unlock(&_loaderMutex);
        
        _retryCount = 0;
        _request = NULL;
        
        while( !_inProgress.empty() ) {
            delete _inProgress.back();
            _inProgress.pop_back();
        }
        
        pthread_mutex_lock( &_queueMutex );
        while( !_queue.empty() ) {
            delete _queue.back();
            _queue.pop_back();
        }
        _eventCallbackQueue.clear();
        pthread_mutex_unlock( &_queueMutex );
        
    }  // end BrainCloudComms::resetCommunication
    
    
    ////////////////////////////////////////////////////////
    // Private methods
    ////////////////////////////////////////////////////////
    
    bool BrainCloudComms::shouldRetryPacket()
    {
        for( unsigned int i = 0; i < _inProgress.size(); ++i )
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
    
    long BrainCloudComms::getRetryTimeoutMillis(int retryAttempt)
    {
        if (!shouldRetryPacket())
        {
            return _authenticationTimeoutMillis;
        }
        
        return _packetTimeouts[retryAttempt >= (int) _packetTimeouts.size() ? _packetTimeouts.size() - 1 : retryAttempt] * 1000;
    }
    
    int BrainCloudComms::getMaxSendAttempts()
    {
        if (!shouldRetryPacket())
        {
            return 1;
        }
        
        return (int) _packetTimeouts.size();
    }
    
    
    void BrainCloudComms::handleError( URLResponse const & response )
    {
#if ( defined(GAMECLIENT_DEBUGLEVEL)  )
        std::cout << "BrainCloudComms::handleError() status(" << response.getStatusCode()
        << ") reasonPhrase: " << response.getReasonPhrase() << " data: " << response.getData() << std::endl;
#endif
        
        // Get the singleton instance of the BrainCloud object.
        _retryCount++;
        
        if ( _retryCount < getMaxSendAttempts()) {
            // We haven't reached the maximum number of retries yet.  Try again.
            
            int64_t delta = Timer::getCurrentTimeMillis() - _packetSendTimeMillis;
			int64_t sleepTime = (int64_t) (getRetryTimeoutMillis(_retryCount));
            
            // still more time to spend sleeping
            if (delta > 0 && sleepTime > delta)
            {
                sleepTime -= delta;
            }
            // looks like we've waited long enough (but within max margin of 2 secs over retry timeout
            // in case we get some weird time altering event like system clock being changed)
            else if (delta > sleepTime && delta < (getRetryTimeoutMillis(_retryCount) + 2000))
            {
                sleepTime = 1; // hack to follow same timer callback flow
            }
            
            if (_immediateRetryOnError)
            {
                // hack to still follow same flow (retry timer triggers resend)
                // but we schedule it to trigger in 1 ms
                sleepTime = 1;
            }
            
            // Cancel any current retries.
            if ( _retryTimer != NULL ) {
                _retryTimer->stop();
            }
            
            // Set up a new Timer for the retry of the request.
            _retryTimer = new Timer( this, sleepTime, NULL, false );
        }
        else {
            // Give up here...
            _retryCount = 0;
            
            pthread_mutex_lock( &_loaderMutex );
            if ( _loader != NULL ) {
                delete _loader;
            }
            _loader = NULL;
            pthread_mutex_unlock( &_loaderMutex );
        }
        
    }  // end BrainCloudComms::handleError
    
    
    /**
     * Attempt to resend the last HTTP request.
     */
    void BrainCloudComms::resend( )
    {
#if ( defined(GAMECLIENT_DEBUGLEVEL) )
        std::cout << "BrainCloudComms::resend() packetId(" << (_expectedPacketId)
        << ") retry(" << _retryCount << ") request: " << _request << std::endl;
#endif
        // Retry the request.
        pthread_mutex_lock(&_loaderMutex);
        
        if( _loader != NULL && _request != NULL ) {
            pthread_mutex_unlock( &_loaderMutex );
            _loader->setTimeout((int)getRetryTimeoutMillis(_retryCount));
            _loader->load( _request );
            _packetSendTimeMillis = Timer::getCurrentTimeMillis();
        }
        else {
            pthread_mutex_unlock( &_loaderMutex );
        }
    }
    
    /**
     * Creates a fake response to stop packets being sent to the server
     * without a valid session.
     */
    void BrainCloudComms::handleNoAuth()
    {
        size_t numMessages = _inProgress.size();
        Json::Value errorRoot;
        errorRoot["packetId"] = (Json::Int64) _expectedPacketId;
        Json::Value messages;
        for (size_t i = 0; i < numMessages; ++i)
        {
            Json::Value msg;
            
            msg["status"] = _statusCodeCache;
            msg["reason_code"] = _reasonCodeCache;
            msg["status_message"] = "INTERNAL | " + _statusMessageCache;
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
        while( !_inProgress.empty() ) {
            delete _inProgress.back();
            _inProgress.pop_back();
        }
    }
    
    void BrainCloudComms::resetErrorCache()
    {
        _statusCodeCache = HTTP_FORBIDDEN;
        _reasonCodeCache = NO_SESSION;
        _statusMessageCache = "No session";
    }
    
    /**
     * If there are requests in the queue, make a call to the server.
     */
    bool BrainCloudComms::startLoader( )
    {
        bool started = false;
        
        pthread_mutex_lock( &_queueMutex );
        
        if( !_queue.empty() ) {
            // Stop the heartbeat timer by setting to NULL
            _heartbeatTimer = NULL;
            
            std::string url = _serverUrl;
            URLRequest * request = NULL;
            
            // Bundle our messages...
            Json::Value messages( Json::arrayValue );
            bool authenticating = false;
            
            // We want to cap the number of messages in each bundle.
            while( !_queue.empty() && _inProgress.size() < MAX_BUNDLE_SIZE ) {
                // Copy the payload describing this message.
                ServerCall * call = _queue.front();
                messages.append( *(call->getPayload()) );
                
                // Copy the request pointer to _inProgress.
                _inProgress.push_back( call );
                
                // Remove the request pointer from the _queue.
                _queue.erase( _queue.begin() );
                
                if(call->getOperation() == ServiceOperation::Authenticate ||
                   call->getOperation() == ServiceOperation::ResetEmailPassword)
                {
                    authenticating = true;
                }
            }
            
            _expectedPacketId = _packetId++;
            
            Json::Value allMessages;
            allMessages["messages"] = messages;
            allMessages["gameId"] = _gameId;
            allMessages["sessionId"] = _sessionId;
            allMessages["packetId"] = (Json::Int64) _expectedPacketId;
            
            Json::StyledWriter writer;
            std::string dataString = writer.write( allMessages );
            dataString += "\r\n\r\n";
            
            if (_loggingEnabled)
            {
                std::cout << "#BCC OUTGOING " << dataString << std::endl;
            }
            
            //handle session errors locally
            if(!_isAuthenticated && !authenticating)
            {
                handleNoAuth();
                pthread_mutex_unlock( &_loaderMutex );
                pthread_mutex_unlock( &_queueMutex );
                return false;
            }
            
            request = new URLRequest( url );
            request->setData( dataString );
            request->setContentType( "application/json" );
            
            // Now we'll take our string append an application secret, and MD5 it, adding that to the HTTP header
            // This is based loosely on facebook signatures...
            // http://developers.facebook.com/docs/authentication/fb_sig/
            if (_secretKey.length()) {
                // append secret key
                dataString += _secretKey;
                // get binary md5 digest
                
                //encode the string in an md5 format
                const int DIGEST_LENGTH = 16;
                md5_state_t		state;
                md5_byte_t 		digest[DIGEST_LENGTH];
                
                md5_init(&state);
                md5_append(&state, (const md5_byte_t *) dataString.c_str(), (int) dataString.length());
                md5_finish(&state, digest);
                
                /* [md] now using cross platform md5x lib
                 CC_MD5_CTX md5;
                 CC_MD5_Init(&md5);
                 CC_MD5_Update(&md5, dataString.c_str(), dataString.length());
                 unsigned char digest[CC_MD5_DIGEST_LENGTH];
                 CC_MD5_Final(digest, &md5);
                 */
                
                // convert each byte to string form
                char buf[DIGEST_LENGTH*2 + 1];
                for (unsigned char i = 0; i < DIGEST_LENGTH; ++i) sprintf(&buf[i*2], "%02x", digest[i]);
                // convert to std::string
                std::string sig((const char*)buf, DIGEST_LENGTH*2);
                // convert string to uppercase
                std::transform(sig.begin(), sig.end(), sig.begin(), toupper);
                // add signature to header
                request->addHeader(URLRequestHeader("X-SIG", sig));
            }
            
            pthread_mutex_unlock(&_queueMutex);
            
            // Store the currently active HTTP Request in the object.
            if( _request != NULL ) {
                delete _request;
            }
            _request = request;
            
            if ( _loader != NULL ) {
                delete _loader;
            }
            _loader = new cURLLoader( this );
            
            // Prevent the new thread from owning _loaderMutex.
            pthread_mutex_unlock( &_loaderMutex );
            
            _loader->setTimeout((int)getRetryTimeoutMillis(_retryCount));
            _loader->load( request ); // Start loading the web page.
            _packetSendTimeMillis = Timer::getCurrentTimeMillis();
            started = true;
        }
        else {
            pthread_mutex_unlock( &_loaderMutex );
            pthread_mutex_unlock( &_queueMutex );
        }
        
        return started;
    }
    
    
    // UPLOADER STUFF
    void BrainCloudComms::cancelUpload(const char * in_fileUploadId)
    {
        pthread_mutex_lock(&_mutex);
        tFileUploadsIterator it = _fileUploads.find(in_fileUploadId);
        if (it != _fileUploads.end())
        {
            it->second->cancelUpload();
        }
        pthread_mutex_unlock(&_mutex);
    }
    
    double BrainCloudComms::getUploadProgress(const char * in_fileUploadId)
    {
        double progress = 0;
        pthread_mutex_lock(&_mutex);
        tFileUploadsIterator it = _fileUploads.find(in_fileUploadId);
        if (it != _fileUploads.end())
        {
            progress = it->second->getProgress();
        }
        else
        {
            progress = -1;
        }
        pthread_mutex_unlock(&_mutex);
        
        return progress;
    }
    
    int64_t BrainCloudComms::getUploadTotalBytesToTransfer(const char * in_fileUploadId)
    {
        int64_t totalBytesToTransfer = 0;
        pthread_mutex_lock(&_mutex);
        tFileUploadsIterator it = _fileUploads.find(in_fileUploadId);
        if (it != _fileUploads.end())
        {
            totalBytesToTransfer = it->second->getTotalBytesToTransfer();
        }
        else
        {
            totalBytesToTransfer = -1;
        }
        pthread_mutex_unlock(&_mutex);
        
        return totalBytesToTransfer;
    }
    
    int64_t BrainCloudComms::getUploadBytesTransferred(const char * in_fileUploadId)
    {
        int64_t bytesToTransfer = 0;
        pthread_mutex_lock(&_mutex);
        tFileUploadsIterator it = _fileUploads.find(in_fileUploadId);
        if (it != _fileUploads.end())
        {
            bytesToTransfer = it->second->getBytesTransferred();
        }
        else
        {
            bytesToTransfer = -1;
        }
        pthread_mutex_unlock(&_mutex);
        
        return bytesToTransfer;
    }
    
    void BrainCloudComms::startFileUpload(const Json::Value & in_jsonPrepareUploadResponse)
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

        pthread_mutex_lock(&_mutex);
        
        if (_fileUploads.find(fileUploadId) != _fileUploads.end())
        {
            // that can't be right....
            pthread_mutex_unlock(&_mutex);
            return;
        }
        
        cURLFileUploader *uploader = new cURLFileUploader();
        uploader->enableLogging(_loggingEnabled);
        uploader->setUploadLowTransferRateThreshold(_uploadLowTransferRateThresholdBytesPerSec);
        uploader->setUploadLowTransferRateTimeout(_uploadLowTransferRateTimeoutSecs);
        _fileUploads[fileUploadId] = uploader;
        if (!uploader->uploadFile(_sessionId, fileUploadId, localPath, fileSize, _uploadUrl))
        {
            _fileUploads.erase(_fileUploads.find(fileUploadId));
            delete uploader;
        }
        
        pthread_mutex_unlock(&_mutex);
    }

    
}
