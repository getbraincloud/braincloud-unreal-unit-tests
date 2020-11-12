#pragma once

#include "braincloud/IServerCallback.h"
#include "braincloud/ServiceName.h"
#include "braincloud/BrainCloudRTT.h"

#include <json/json.h>

#include <atomic>
#include <map>
#include <mutex>
#include <string>
#include <vector>
#include <condition_variable>

namespace BrainCloud
{
    class BrainCloudClient;
    class BrainCloudWSSocket;
    class IRTTConnectCallback;
    class IRTTCallback;
    class ISocket;
#if (TARGET_OS_WATCH != 1)
    class IWebSocket;
#endif

    class RTTComms : public IServerCallback
    {
    public:
        RTTComms(BrainCloudClient* in_client);
        virtual ~RTTComms();

        void initialize();
        bool isInitialized() const;
        void shutdown();
        void resetCommunication();

        void enableRTT(IRTTConnectCallback* in_callback, bool in_useWebSocket);
        void disableRTT();
        bool isRTTEnabled();
        bool getLoggingEnabled();
        BrainCloudRTT::RTTConnectionStatus getConnectionStatus();
        void enableLogging(bool isEnabled);
        const std::string& getConnectionId();

        void runCallbacks();
        void registerRTTCallback(const ServiceName& serviceName, IRTTCallback* in_callback);
        void deregisterRTTCallback(const ServiceName& serviceName);
        void deregisterAllRTTCallbacks();

    private:
        enum RTTCallbackType
        {
            ConnectSuccess,
            ConnectFailure,
            Event
        };

        class RTTCallback
        {
        public:
            RTTCallbackType _type;
            std::string _message;
            Json::Value _json;

            RTTCallback(RTTCallbackType type);
            RTTCallback(RTTCallbackType type, const std::string& message);
            RTTCallback(RTTCallbackType type, const Json::Value& json);
            RTTCallback(RTTCallbackType type, const Json::Value& json, const std::string& message);
        };

        // IServerCallback
        void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const std::string& jsonData);
        void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int statusCode, int reasonCode, const std::string& jsonError);

        void processRTTMessage(const ServiceOperation& serviceOperation, const Json::Value& jsonData);
        Json::Value getEndpointToUse(const Json::Value& endpoints) const;
        static Json::Value getEndpointForType(const Json::Value& endpoints, const std::string& type, bool wantSsl);

        void closeSocket();

        void connect();
        void failedToConnect();
        void onSocketConnected();
        void startReceiving();
        void startHeartbeat();
        Json::Value buildConnectionRequest(const std::string& protocol);
        bool send(const Json::Value& jsonData);
        void onRecv(const std::string& message);
        void processRttMessage(const Json::Value& json, const std::string& message);

        bool _isInitialized;

        BrainCloudClient* _client;
        bool _loggingEnabled;
        IRTTConnectCallback* _connectCallback;

        std::string _appId;
        std::string _sessionId;
        std::string _profileId;
        std::string _connectionId;

        Json::Value _auth;
        Json::Value _endpoint;

        ISocket* _socket;
        BrainCloudRTT::RTTConnectionStatus _rttConnectionStatus;
        std::mutex _socketMutex;
        std::condition_variable _threadsCondition;
        std::mutex _heartBeatMutex;
        std::condition_variable _heartbeatCondition;
        std::atomic<bool> _receivingRunning;
        std::atomic<bool> _heartbeatRunning;

        bool _useWebSocket;

        int _heartbeatSeconds;
        int64_t _lastHeartbeatTime;
    
        std::mutex _eventQueueMutex;
        std::vector<RTTCallback> _callbackEventQueue;
        std::map<std::string, IRTTCallback*> _callbacks;
    };
};
