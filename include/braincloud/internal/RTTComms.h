#pragma once

#include "braincloud/IServerCallback.h"

#include <string>
#include <json/json.h>

namespace BrainCloud
{
	class BrainCloudClient;
	class BrainCloudTCPSocket;
	class BrainCloudWSSocket;
	class IRTTConnectCallback;
	class IRTTCallback;

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
		bool getLoggingEnabled();
		void enableLogging(bool isEnabled);
		const std::string& getConnectionId();

		void runCallbacks();
		void registerRTTCallback(const std::string& serviceName, IRTTCallback* in_callback);
		void deregisterRTTCallback(const std::string& serviceName);
		void deregisterAllCallbacks();

	private:
		// IServerCallback
        void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const std::string& jsonData);
        void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int statusCode, int reasonCode, const std::string& jsonError);
        void serverWarning(ServiceName serviceName, ServiceOperation serviceOperation, int statusCode, int reasonCode, int numRetries, const std::string& statusMessage);

		bool _isInitialized;

		BrainCloudClient* _client;
		bool _loggingEnabled;

		std::string _appId;
		std::string _sessionId;
		std::string _profileId;
		std::string _connectionId;

		Json::Value _auth;
		Json::Value _endpoint;

		BrainCloudTCPSocket* _socket;
		bool _isConnected;

		bool _useWebSocket;
		BrainCloudWSSocket* _webSocketClient;

		int _heartbeatSeconds;
		long _lastHeartbeatTime;
	};
};
