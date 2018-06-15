// BrainCloudClient.cpp
// BrainCloudLib
// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "braincloud/BrainCloudClient.h"

#include "braincloud/internal/Device.h"
#include "braincloud/internal/JsonUtil.h"
#include "braincloud/internal/URLRequestMethod.h"

namespace BrainCloud
{
	// Define all static member variables.
    bool BrainCloudClient::EnableSingletonMode = false;
	const char * BrainCloudClient::SingletonUseErrorMessage =
			"Singleton usage is disabled. If called by mistake, use your own variable that holds an instance of the bcWrapper/bcClient.";

	BrainCloudClient * BrainCloudClient::_instance = NULL;
	std::string BrainCloudClient::s_brainCloudClientVersion = "3.8.0";

	/**
	 * Constructor
	 */
	BrainCloudClient::BrainCloudClient() :
        _brainCloudComms(IBrainCloudComms::create(this)),
		_asyncMatchService(new BrainCloudAsyncMatch(this)),
		_authenticationService(new BrainCloudAuthentication(this)),
		_dataStreamService(new BrainCloudDataStream(this)),
		_entityService(new BrainCloudEntity(this)),
		_eventService(new BrainCloudEvent(this)),
		_fileService(new BrainCloudFile(this)),
		_friendService(new BrainCloudFriend(this)),
		_gamificationService(new BrainCloudGamification(this)),
		_globalAppService(new BrainCloudGlobalApp(this)),
		_globalEntityService(new BrainCloudGlobalEntity(this)),
		_globalStatisticsService(new BrainCloudGlobalStatistics(this)),
		_groupService(new BrainCloudGroup(this)),
		_identityService(new BrainCloudIdentity(this)),
		_mailService(new BrainCloudMail(this)),
		_matchmakingService(new BrainCloudMatchmaking(this)),
		_oneWayMatchService(new BrainCloudOneWayMatch(this)),
		_playbackStreamService(new BrainCloudPlaybackStream(this)),
		_playerStateService(new BrainCloudPlayerState(this)),
		_playerStatisticsService(new BrainCloudPlayerStatistics(this)),
		_playerStatisticsEventService(new BrainCloudPlayerStatisticsEvent(this)),
		_productService(new BrainCloudProduct(this)),
		_profanityService(new BrainCloudProfanity(this)),
		_pushNotificationService(new BrainCloudPushNotification(this)),
		_redemptionCodeService(new BrainCloudRedemptionCode(this)),
		_s3HandlingService(new BrainCloudS3Handling(this)),
		_scriptService(new BrainCloudScript(this)),
		_socialLeaderboardService(new BrainCloudSocialLeaderboard(this)),
		_steamService(new BrainCloudSteam(this)),
		_timeService(new BrainCloudTime(this)),
		_tournamentService(new BrainCloudTournament(this)),
		_releasePlatform(""),
		_appVersion(""),
		_timezoneOffset(0.0)
	{
	}

    BrainCloudClient::~BrainCloudClient()
    {
        delete _brainCloudComms;
        delete _tournamentService;
        delete _timeService;
        delete _steamService;
        delete _socialLeaderboardService;
        delete _scriptService;
        delete _s3HandlingService;
        delete _redemptionCodeService;
        delete _pushNotificationService;
        delete _profanityService;
        delete _productService;
        delete _playerStatisticsEventService;
        delete _playerStatisticsService;
        delete _playerStateService;
        delete _playbackStreamService;
        delete _oneWayMatchService;
        delete _matchmakingService;
        delete _mailService;
        delete _identityService;
        delete _groupService;
        delete _globalStatisticsService;
        delete _globalEntityService;
        delete _globalAppService;
        delete _gamificationService;
        delete _friendService;
        delete _fileService;
        delete _eventService;
        delete _entityService;
        delete _dataStreamService;
        delete _authenticationService;
        delete _asyncMatchService;
    }

	////////////////////////////////////////////////////
	// Public Methods
	////////////////////////////////////////////////////

	const char * BrainCloudClient::getSessionId() const {
		return(_brainCloudComms->getSessionId().c_str());
	}

	void BrainCloudClient::initialize(const char * in_serverURL, const char * in_secretKey, const char * in_appId, const char * in_appVersion)
	{
		std::string error = "";
		if (in_serverURL == NULL || strlen(in_serverURL) <= 0)
			error = "serverURL was null or empty";
		else if (in_secretKey == NULL || strlen(in_secretKey) <= 0)
			error = "secretKey was null or empty";
		else if (in_appId == NULL || strlen(in_appId) <= 0)
			error = "appId was null or empty";
		else if (in_appVersion == NULL || strlen(in_appVersion) <= 0)
			error = "appVersion was null or empty";

		if (error.length() > 0)
		{
			std::cout << "ERROR | Failed to initialize brainCloud - " << error;
			return;
		}

		if (_brainCloudComms)
		{
			// automatically upgrade any older clients using "dispatcher" url
			// to "dispatcherv2" endpoint. Comms supports this now and otherwise
			// the change is transparent to the client.
			const char * urlToUse = in_serverURL;
			std::string url = in_serverURL;
			if (url.find("dispatcherv2") == std::string::npos)
			{
				size_t index = url.find("dispatcher");
				if (index != std::string::npos)
				{
					url = url.substr(0, index);
					url += "dispatcherv2";
					urlToUse = url.c_str();
				}
			}
			_brainCloudComms->initialize(urlToUse, in_appId, in_secretKey);
		}

		setupOSLocaleData();

        _releasePlatform = Device::getPlatformName();

		_appVersion = in_appVersion;
	}

	void BrainCloudClient::initializeIdentity(const char * in_profileId, const char * in_anonymousId)
	{
		_authenticationService->initialize(in_profileId, in_anonymousId);
	}

	void BrainCloudClient::runCallbacks()
	{
		_brainCloudComms->runCallbacks();
	}

	void BrainCloudClient::registerEventCallback(IEventCallback *in_eventCallback)
	{
		_brainCloudComms->registerEventCallback(in_eventCallback);
	}

	void BrainCloudClient::deregisterEventCallback()
	{
		_brainCloudComms->deregisterEventCallback();
	}

	void BrainCloudClient::registerRewardCallback(IRewardCallback *in_rewardCallback)
	{
		_brainCloudComms->registerRewardCallback(in_rewardCallback);
	}

	void BrainCloudClient::deregisterRewardCallback()
	{
		_brainCloudComms->deregisterRewardCallback();
	}

	void BrainCloudClient::registerFileUploadCallback(IFileUploadCallback * in_fileUploadCallback)
	{
		_brainCloudComms->registerFileUploadCallback(in_fileUploadCallback);
	}

	void BrainCloudClient::deregisterFileUploadCallback()
	{
		_brainCloudComms->deregisterFileUploadCallback();
	}

	void BrainCloudClient::registerGlobalErrorCallback(IGlobalErrorCallback * in_globalErrorCallback)
	{
		_brainCloudComms->registerGlobalErrorCallback(in_globalErrorCallback);
	}

	void BrainCloudClient::deregisterGlobalErrorCallback()
	{
		_brainCloudComms->deregisterGlobalErrorCallback();
	}

	void BrainCloudClient::registerNetworkErrorCallback(INetworkErrorCallback * in_networkErrorCallback)
	{
		_brainCloudComms->registerNetworkErrorCallback(in_networkErrorCallback);
	}

	void BrainCloudClient::deregisterNetworkErrorCallback()
	{
		_brainCloudComms->deregisterNetworkErrorCallback();
	}

	void BrainCloudClient::enableLogging(bool shouldEnable)
	{
		_brainCloudComms->enableLogging(shouldEnable);
	}

	/**
	 * Heart beat to keep session(s) current, and retrieve any pending events...
	 */
	void BrainCloudClient::heartbeat()
	{
		_brainCloudComms->sendHeartbeat();
	}

	void BrainCloudClient::sendRequest(ServerCall * in_serviceMessage)
	{
		_brainCloudComms->addToQueue(in_serviceMessage);
	}

	void BrainCloudClient::resetCommunication()
	{
		_brainCloudComms->resetCommunication();
		_brainCloudComms->setSessionId("");
		_authenticationService->setProfileId("");
	}

	void BrainCloudClient::shutdown()
	{
		_brainCloudComms->shutdown();
		_brainCloudComms->setSessionId("");
		_authenticationService->setProfileId("");
	}

	bool BrainCloudClient::isAuthenticated()
	{
		return _brainCloudComms->isAuthenticated();
	}

	bool BrainCloudClient::isInitialized()
	{
		return _brainCloudComms->isInitialized();
	}

	void BrainCloudClient::setImmediateRetryOnError(bool value)
	{
		_brainCloudComms->setImmediateRetryOnError(value);
	}

	/**
	 * Retrieve the pointer to the singleton BrainCloudClient instance.
	 */
	BrainCloudClient * BrainCloudClient::getInstance()
	{
        if(EnableSingletonMode == false) {
            throw std::invalid_argument(SingletonUseErrorMessage);
        }

		if (_instance == NULL) {
			_instance = new BrainCloudClient();
		}
		return _instance;
	}

	void BrainCloudClient::setHeartbeatInterval(int in_intervalInMilliseconds) {
		_brainCloudComms->setHeartbeatInterval(in_intervalInMilliseconds);
	}

	const std::vector<int> & BrainCloudClient::getPacketTimeouts()
	{
		return _brainCloudComms->getPacketTimeouts();
	}

	void BrainCloudClient::setPacketTimeouts(const std::vector<int> & in_packetTimeouts)
	{
		_brainCloudComms->setPacketTimeouts(in_packetTimeouts);
	}

	void BrainCloudClient::setPacketTimeoutsToDefault()
	{
		_brainCloudComms->setPacketTimeoutsToDefault();
	}

	void BrainCloudClient::setAuthenticationPacketTimeout(int in_timeoutSecs)
	{
		_brainCloudComms->setAuthenticationPacketTimeout(in_timeoutSecs);
	}

	int BrainCloudClient::getAuthenticationPacketTimeout()
	{
		return _brainCloudComms->getAuthenticationPacketTimeout();
	}

	void BrainCloudClient::setOldStyleStatusMessageErrorCallback(bool in_enabled)
	{
		_brainCloudComms->setOldStyleStatusMessageErrorCallback(in_enabled);
	}

	void BrainCloudClient::setErrorCallbackOn202Status(bool in_isError)
	{
		_brainCloudComms->setErrorCallbackOn202Status(in_isError);
	}

	int BrainCloudClient::getUploadLowTransferRateTimeout()
	{
		return _brainCloudComms->getUploadLowTransferRateTimeout();
	}

	void BrainCloudClient::setUploadLowTransferRateTimeout(int in_timeoutSecs)
	{
		_brainCloudComms->setUploadLowTransferRateTimeout(in_timeoutSecs);
	}

	int BrainCloudClient::getUploadLowTransferRateThreshold()
	{
		return _brainCloudComms->getUploadLowTransferRateThreshold();
	}

	void BrainCloudClient::setUploadLowTransferRateThreshold(int in_bytesPerSec)
	{
		_brainCloudComms->setUploadLowTransferRateThreshold(in_bytesPerSec);
	}

	void BrainCloudClient::enableNetworkErrorMessageCaching(bool in_enabled)
	{
		_brainCloudComms->enableNetworkErrorMessageCaching(in_enabled);
	}

	void BrainCloudClient::retryCachedMessages()
	{
		_brainCloudComms->retryCachedMessages();
	}

	void BrainCloudClient::flushCachedMessages(bool in_sendApiErrorCallbacks)
	{
		_brainCloudComms->flushCachedMessages(in_sendApiErrorCallbacks);
	}

	void BrainCloudClient::insertEndOfMessageBundleMarker()
	{
		_brainCloudComms->insertEndOfMessageBundleMarker();
	}

	////////////////////////////////////////////////////
	// Private Methods
	////////////////////////////////////////////////////
	void BrainCloudClient::setupOSLocaleData()
	{
        Device::getLocale(&_timezoneOffset, &_languageCode, &_countryCode);
	}
}  // end namespace
