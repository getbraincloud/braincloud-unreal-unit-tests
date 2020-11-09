#include "braincloud/internal/RTTComms.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IRTTCallback.h"
#include "braincloud/IRTTConnectCallback.h"
#include "braincloud/internal/ITCPSocket.h"
#if (TARGET_OS_WATCH != 1)
#include "braincloud/internal/IWebSocket.h"
#endif
#include "braincloud/internal/TimeUtil.h"

#include <iostream>
#include <thread>

namespace BrainCloud
{
    RTTComms::RTTCallback::RTTCallback(RTTCallbackType type)
        : _type(type)
    {
    }

    RTTComms::RTTCallback::RTTCallback(RTTCallbackType type, const std::string& message)
        : _type(type)
        , _message(message)
    {
    }

    RTTComms::RTTCallback::RTTCallback(RTTCallbackType type, const Json::Value& json)
        : _type(type)
        , _json(json)
    {
    }

    RTTComms::RTTCallback::RTTCallback(RTTCallbackType type, const Json::Value& json, const std::string& message)
        : _type(type)
        , _message(message)
        , _json(json)
    {
    }

    RTTComms::RTTComms(BrainCloudClient* in_client)
        : _isInitialized(false)
        , _client(in_client)
        , _loggingEnabled(false)
        , _connectCallback(NULL)
        , _socket(NULL)
        , _rttConnectionStatus(BrainCloudRTT::RTTConnectionStatus::Disconnected)
        , _receivingRunning(false)
        , _heartbeatRunning(false)
        , _useWebSocket(true)
        , _heartbeatSeconds(30)
        , _lastHeartbeatTime(0)
    {
    }

    RTTComms::~RTTComms()
    {
        shutdown();
    }

    void RTTComms::initialize()
    {
        _isInitialized = true;
    }

    bool RTTComms::isInitialized() const
    {
        return _isInitialized;
    }

    void RTTComms::shutdown()
    {
        resetCommunication();
        _isInitialized = false;
    }

    void RTTComms::resetCommunication()
    {
        if (isRTTEnabled())
        {
            _rttConnectionStatus = BrainCloudRTT::RTTConnectionStatus::Disconnecting;
            closeSocket();
            _eventQueueMutex.lock();
            _callbackEventQueue.clear();
            _eventQueueMutex.unlock();
            _rttConnectionStatus = BrainCloudRTT::RTTConnectionStatus::Disconnected;
        }
    }

    void RTTComms::closeSocket()
    {
        std::unique_lock<std::mutex> lock(_socketMutex);

        if (_socket)
        {
            _socket->close();

            // We wait for the recv/send threads to shutdown
            _heartBeatMutex.lock();
            _heartbeatCondition.notify_one();
            _heartBeatMutex.unlock();
            if (_receivingRunning || _heartbeatRunning)
            {
                _threadsCondition.wait(lock, [this]()
                {
                    return !(_receivingRunning || _heartbeatRunning);
                });
            }

            delete _socket;
            _socket = NULL;
        }
    }

    void RTTComms::enableRTT(IRTTConnectCallback* in_callback, bool in_useWebSocket)
    {
        if(isRTTEnabled() || _rttConnectionStatus == BrainCloudRTT::RTTConnectionStatus::Connecting)
        {
            return;
        }
        else
        {               
            _connectCallback = in_callback;
            _useWebSocket = in_useWebSocket;

            _appId = _client->getAppId();
            _sessionId = _client->getSessionId();
            _profileId = _client->getAuthenticationService()->getProfileId();

            _client->getRTTService()->requestClientConnection(this);
        }
    }

    void RTTComms::disableRTT()
    {
        if(!isRTTEnabled() || _rttConnectionStatus == BrainCloudRTT::RTTConnectionStatus::Disconnecting)
        {
            return;
        }
        else
        {     
            resetCommunication();   
        }
    }

    bool RTTComms::isRTTEnabled()
    {
        return _rttConnectionStatus == BrainCloudRTT::RTTConnectionStatus::Connected;
    }

    BrainCloudRTT::RTTConnectionStatus RTTComms::getConnectionStatus()
    {
        return _rttConnectionStatus;
    }

    bool RTTComms::getLoggingEnabled()
    {
        return _loggingEnabled;
    }

    void RTTComms::enableLogging(bool isEnabled)
    {
        _loggingEnabled = isEnabled;
    }

    const std::string& RTTComms::getConnectionId()
    {
        return _connectionId;
    }

    void RTTComms::runCallbacks()
    {
        _eventQueueMutex.lock();
        auto eventsCopy = _callbackEventQueue;
        _callbackEventQueue.clear();
        _eventQueueMutex.unlock();

        for (int i = 0; i < (int)eventsCopy.size(); ++i)
        {
            const RTTCallback& callback = eventsCopy[i];
            switch (callback._type)
            {
                case RTTCallbackType::ConnectSuccess:
                {
                    if (_connectCallback)
                    {
                        _connectCallback->rttConnectSuccess();
                    }
                    break;
                }
                case RTTCallbackType::ConnectFailure:
                {
                    if (_connectCallback)
                    {
                        _connectCallback->rttConnectFailure(callback._message);
                    }
                    break;
                }
                case RTTCallbackType::Event:
                {
                    std::string serviceName = callback._json["service"].asString();
                    std::map<std::string, IRTTCallback*>::iterator it = _callbacks.find(serviceName);
                    if (it != _callbacks.end())
                    {
                        it->second->rttCallback(callback._message);
                    }
                    break;
                }
            }
        }
    }

    void RTTComms::registerRTTCallback(const ServiceName& serviceName, IRTTCallback* in_callback)
    {
        _callbacks[serviceName.getValue()] = in_callback;
    }

    void RTTComms::deregisterRTTCallback(const ServiceName& serviceName)
    {
        std::map<std::string, IRTTCallback*>::iterator it = _callbacks.find(serviceName.getValue());
        if (it != _callbacks.end())
        {
            _callbacks.erase(it);
        }
    }

    void RTTComms::deregisterAllRTTCallbacks()
    {
        _callbacks.clear();
    }

    // IServerCallback
    void RTTComms::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const std::string& jsonData)
    {
        if (serviceName == ServiceName::RTTRegistration)
        {
            Json::Reader reader;
            Json::Value json;
            reader.parse(jsonData, json);
            processRTTMessage(serviceOperation, json);
        }
    }

    void RTTComms::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int statusCode, int reasonCode, const std::string& jsonError)
    {
        if (_connectCallback)
        {
            _connectCallback->rttConnectFailure(jsonError);
        }
    }

    void RTTComms::serverWarning(ServiceName serviceName, ServiceOperation serviceOperation, int statusCode, int reasonCode, int numRetries, const std::string& statusMessage)
    {
    }

    void RTTComms::processRTTMessage(const ServiceOperation& serviceOperation, const Json::Value& jsonData)
    {
        if (serviceOperation == ServiceOperation::RequestClientConnection)
        {
            const Json::Value& data = jsonData["data"];
            _endpoint = getEndpointToUse(data["endpoints"]);
            if (_endpoint.isNull())
            {
                if (_connectCallback)
                {
                    _connectCallback->rttConnectFailure("No endpoint available");
                    return;
                }
            }

            _auth = data["auth"];
            connect();
        }
    }

    Json::Value RTTComms::getEndpointToUse(const Json::Value& endpoints) const
    {
        if (_useWebSocket)
        {
            //   1st choice: websocket + ssl
            //   2nd: websocket
            Json::Value endpoint = getEndpointForType(endpoints, "ws", true);
            if (!endpoint.isNull())
            {
                return endpoint;
            }
            return getEndpointForType(endpoints, "ws", false);
        }
        else
        {
            //   1st choice: tcp
            //   2nd: tcp + ssl (not implemented yet)
            Json::Value endpoint = getEndpointForType(endpoints, "tcp", false);
            if (!endpoint.isNull())
            {
                return endpoint;
            }
            return getEndpointForType(endpoints, "tcp", true);
        }
    }

    Json::Value RTTComms::getEndpointForType(const Json::Value& endpoints, const std::string& type, bool wantSsl)
    {
        for (int i = 0; i < (int)endpoints.size(); ++i)
        {
            const Json::Value& endpoint = endpoints[i];
            const std::string protocol = endpoint["protocol"].asString();
            if (protocol == type)
            {
                if (wantSsl)
                {
                    if (endpoint["ssl"].asBool())
                    {
                        return endpoint;
                    }
                }
                else
                {
                    return endpoint;
                }
            }
        }

        return Json::nullValue;
    }

    void RTTComms::connect()
    {
        _rttConnectionStatus = BrainCloudRTT::RTTConnectionStatus::Connecting;
#if (TARGET_OS_WATCH != 1)
        std::thread connectionThread([this]
        {
            std::string host = _endpoint["host"].asString();
            int port = _endpoint["port"].asInt();

            std::map<std::string, std::string> headers;
            std::vector<std::string> keys = _auth.getMemberNames();
            for (int i = 0; i < (int)keys.size(); ++i)
            {
                headers[keys[i]] = _auth[keys[i]].asString();
            }

            {
                {
                    std::unique_lock<std::mutex> lock(_socketMutex);
                    if (_useWebSocket)
                    {
                        if (_endpoint["ssl"].asBool())
                        {
                            host = "wss://" + host;
                        }
                        else
                        {
                            host = "ws://" + host;
                        }
                        
                        // Add headers to the query URL
                        if (!headers.empty())
                        {
                            host += "?";
                            for (std::map<std::string, std::string>::iterator it = headers.begin(); it != headers.end(); ++it)
                            {
                                const std::string& key = it->first;
                                const std::string& value = it->second;

                                if (host.back() != '?')
                                {
                                    host += "&";
                                }
                                host += key + "=" + value;
                            }
                        }

                        _socket = IWebSocket::create(host, port, headers);
                    }
                    else
                    {
                        _socket = ITCPSocket::create(host, port);
                    }
                }
                if (!_socket->isValid())
                {
                    closeSocket();
                    failedToConnect();
                    _rttConnectionStatus = BrainCloudRTT::RTTConnectionStatus::Disconnected;
                    return;
                }

                _rttConnectionStatus = BrainCloudRTT::RTTConnectionStatus::Connected;
            }

            _lastHeartbeatTime = TimeUtil::getCurrentTimeMillis();

            if (_loggingEnabled)
            {
                std::cout << "RTT: connected" << std::endl;
            }

            onSocketConnected();
        });
        connectionThread.detach();
#else
        failedToConnect();
#endif
    }

    void RTTComms::failedToConnect()
    {
        std::string host;
        int port = 0;

        if (!_endpoint.isNull())
        {
            host = _endpoint["host"].asString();
            port = _endpoint["port"].asInt();
        }

        _eventQueueMutex.lock();
        _callbackEventQueue.push_back(RTTCallback(RTTCallbackType::ConnectFailure, "Failed to connect to RTT Event server: " + host + ":" + std::to_string(port)));
        _eventQueueMutex.unlock();
    }

    Json::Value RTTComms::buildConnectionRequest(const std::string& protocol)
    {
        Json::Value json;
        json["operation"] = "CONNECT";
        json["service"] = "rtt";
        
        Json::Value system;
        system["protocol"] = protocol;
        system["platform"] = "C++";
        
        Json::Value jsonData;
        jsonData["appId"] = _appId;
        jsonData["profileId"] = _profileId;
        jsonData["sessionId"] = _sessionId;
        jsonData["auth"] = _auth;
        jsonData["system"] = system;
        json["data"] = jsonData;

        return json;
    }

    void RTTComms::onSocketConnected()
    {
        startReceiving();

        if (!send(buildConnectionRequest("tcp")))
        {
            failedToConnect();
        }
    }

    bool RTTComms::send(const Json::Value& jsonData)
    {
        Json::StyledWriter writer;
        std::string message = writer.write(jsonData);

        if (_loggingEnabled)
        {
            std::cout << "RTT SEND " << message << std::endl;
        }

        std::unique_lock<std::mutex> lock(_socketMutex);
        if (isRTTEnabled())
        {
            _socket->send(message);
        }

        return true;
    }

    void RTTComms::startReceiving()
    {
        _receivingRunning = true;
        std::thread receiveThread([this]
        {
            while (isRTTEnabled())
            {
                std::string message = _socket->recv();
                if (message.empty())
                {
                    break;
                }
                onRecv(message);
            }

            std::unique_lock<std::mutex> lock(_socketMutex);
            _receivingRunning = false;
            _threadsCondition.notify_one();
        });
        receiveThread.detach();
    }

    void RTTComms::startHeartbeat()
    {
        _heartbeatRunning = true;
        std::thread heartbeatThread([this]
        {
            Json::Value jsonHeartbeat;
            jsonHeartbeat["operation"] = "HEARTBEAT";
            jsonHeartbeat["service"] = "rtt";

            std::unique_lock<std::mutex> lock(_heartBeatMutex);

            while (isRTTEnabled())
            {
                int64_t sleepTime = ((int64_t)_heartbeatSeconds * 1000) - (TimeUtil::getCurrentTimeMillis() - _lastHeartbeatTime);
                if (sleepTime > 0)
                {
                    _heartbeatCondition.wait_for(lock, std::chrono::milliseconds(sleepTime));
                }
                else
                {
                    send(jsonHeartbeat);
                    _lastHeartbeatTime = TimeUtil::getCurrentTimeMillis();
                }
            }

            _heartbeatRunning = false;
            _threadsCondition.notify_one();
        });
        heartbeatThread.detach();
    }

    void RTTComms::onRecv(const std::string& message)
    {
        if (_loggingEnabled)
        {
            std::cout << "RTT RECV: " << message << std::endl;
        }

        Json::Reader reader;
        Json::Value jsonData;
        if (!reader.parse(message, jsonData))
        {
            failedToConnect();
            return;
        }

        std::string serviceName = jsonData["service"].asString();
        printf("serviceName: %s", serviceName.c_str());
        processRttMessage(jsonData, message);
    }

    void RTTComms::processRttMessage(const Json::Value& json, const std::string& message)
    {
        std::string serviceName = json["service"].asString();
        std::string operation = json["operation"].asString();
        if (serviceName == "rtt" && operation == "CONNECT")
        {
            _heartbeatSeconds = json["data"].get("heartbeatSeconds", 30).asInt();
            _connectionId = json["data"]["cxId"].asString();

            startHeartbeat();

            _eventQueueMutex.lock();
            _callbackEventQueue.push_back(RTTCallback(RTTCallbackType::ConnectSuccess));
            _eventQueueMutex.unlock();
        }
        else
        {
            _eventQueueMutex.lock();
            _callbackEventQueue.push_back(RTTCallback(RTTCallbackType::Event, json, message));
            _eventQueueMutex.unlock();
        }
    }
};
