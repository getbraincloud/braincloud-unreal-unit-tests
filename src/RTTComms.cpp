#include "braincloud/internal/RTTComms.h"

#include "braincloud/BrainCloudClient.h"
#include "braincloud/IRTTConnectCallback.h"

namespace BrainCloud
{
	RTTComms::RTTComms(BrainCloudClient* in_client)
		: _isInitialized(false)
		, _client(in_client)
		, _loggingEnabled(false)
	{
	// bool _loggingEnabled;

	// std::string _appId;
	// std::string _sessionId;
	// std::string _profileId;
	// std::string _connectionId;

	// Json::Value _auth;
	// Json::Value _endpoint;

	// BrainCloudTCPSocket* _socket;
	// bool _isConnected;

	// bool _useWebSocket;
	// BrainCloudWSSocket* _webSocketClient;

	// int _heartbeatSeconds;
	// uint64_t _lastHeartbeatTime;
	}

	RTTComms::~RTTComms()
	{

	}

	void RTTComms::initialize()
	{

	}

	bool RTTComms::isInitialized() const
	{
		return _isInitialized;
	}

	void RTTComms::shutdown()
	{

	}

	void RTTComms::resetCommunication()
	{

	}

	void RTTComms::enableRTT(IRTTConnectCallback* in_callback, bool in_useWebSocket)
	{

	}

	void RTTComms::disableRTT()
	{

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
		static std::string emptyConnId;
		return emptyConnId;
	}

	void RTTComms::runCallbacks()
	{

	}

	void RTTComms::registerRTTCallback(const std::string& serviceName, IRTTCallback* in_callback)
	{

	}

	void RTTComms::deregisterRTTCallback(const std::string& serviceName)
	{

	}

	void RTTComms::deregisterAllCallbacks()
	{

	}

	// IServerCallback
	void RTTComms::serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const std::string& jsonData)
	{

	}

	void RTTComms::serverError(ServiceName serviceName, ServiceOperation serviceOperation, int statusCode, int reasonCode, const std::string& jsonError)
	{

	}

	void RTTComms::serverWarning(ServiceName serviceName, ServiceOperation serviceOperation, int statusCode, int reasonCode, int numRetries, const std::string& statusMessage)
	{

	}
};
