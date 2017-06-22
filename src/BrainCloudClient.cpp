// BrainCloudClient.cpp
// BrainCloudLib
// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#ifdef SEND_SIG
# include <CommonCrypto/CommonDigest.h>
#endif
#include <cstring>
#include <iomanip>
#include <sstream>
#include <vector>

#if defined(__APPLE__)
#include <CoreFoundation/CFLocale.h>
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFTimeZone.h>
#include <TargetConditionals.h>
#endif

#if defined(IW_SDK)
#include <s3e.h>
#endif

#if defined(WINAPI_FAMILY)
#include <Windows.h>
#include <WinBase.h>
#endif

#include "braincloud/BrainCloudClient.h"
#ifdef USE_NEW_COMMS
#include "braincloud/internal/win/BrainCloudComms2.h"
#else
#include "braincloud/internal/BrainCloudComms.h"
#endif

#include <iostream>

#include "braincloud/internal/URLRequestMethod.h"
#include "braincloud/internal/JsonUtil.h"

namespace BrainCloud {

	// Define all static member variables.
	BrainCloudClient * BrainCloudClient::_instance = NULL;
	std::string BrainCloudClient::s_brainCloudClientVersion = "3.5.2";

	/**
	 * Constructor
	 */
	BrainCloudClient::BrainCloudClient() :
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
		//#ifdef PTW32_STATIC_LIB
		//  pthread_win32_process_attach_np();
		//#endif
#ifdef USE_NEW_COMMS
		_brainCloudComms = new BrainCloudComms2(this);
#else
		_brainCloudComms = new BrainCloudComms(this);
#endif
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

#if defined(WINAPI_FAMILY)
#if WINAPI_FAMILY==WINAPI_FAMILY_PHONE_APP
		_releasePlatform = OperationParam::ReleasePlatformWindowsPhone.getValue();
		//#elif WINAPI_FAMILY_PARTITION==WINAPI_PARTITION_DESKTOP
#else
		_releasePlatform = OperationParam::ReleasePlatformWindows.getValue();
#endif
#elif defined(WIN32)
		_releasePlatform = OperationParam::ReleasePlatformWindows.getValue();
#elif defined(__APPLE__)
#if TARGET_OS_IOS
		_releasePlatform = OperationParam::ReleasePlatformIos.getValue();
#elif TARGET_OS_TV
		_releasePlatform = Platform::AppleTVOS.toString();
#elif TARGET_OS_MAC
		// this is true for ios/tv/watch as well... so do this check last
		_releasePlatform = OperationParam::ReleasePlatformMac.getValue();
#else
#error "Unknown __APPLE__ platform!"
#endif
#elif defined(__ANDROID__)
		// need to add code to determine which android platform (ie google play vs amazon etc)
		_releasePlatform = OperationParam::ReleasePlatformGoogleAndroid.getValue();
#elif defined(BB) // just a guess!
		_releasePlatform = OperationParam::ReleasePlatformBlackberry.getValue();
#elif defined(__linux__)
		_releasePlatform = OperationParam::ReleasePlatformLinux.getValue();
#elif defined(IW_SDK)
		//int deviceClass = s3eDeviceGetInt(S3E_DEVICE_CLASS);
		int deviceOs = s3eDeviceGetInt(S3E_DEVICE_OS);
		switch (deviceOs)
		{
		case S3E_OS_ID_OSX:
			_releasePlatform = Platform::Mac.toString();
			break;
		case S3E_OS_ID_IPHONE:
			_releasePlatform = Platform::iOS.toString();
			break;
		case S3E_OS_ID_ANDROID:
			_releasePlatform = Platform::GooglePlayAndroid.toString();
			break;
		case S3E_OS_ID_QNX: // playbook
			_releasePlatform = Platform::BlackBerry.toString();
			break;
		case S3E_OS_ID_ROKU: // TODO - add Roku platform!!!
			_releasePlatform = Platform::GooglePlayAndroid.toString();
			break;
		case S3E_OS_ID_WP8:
		case S3E_OS_ID_WP81:
			_releasePlatform = Platform::WindowsPhone.toString();
			break;
		case S3E_OS_ID_TIZEN:
			_releasePlatform = Platform::Tizen.toString();
			break;
		case S3E_OS_ID_WS8:
		case S3E_OS_ID_WS81:
		case S3E_OS_ID_WIN10:
		case S3E_OS_ID_WINDOWS:
			_releasePlatform = Platform::Windows.toString();
			break;
		case S3E_OS_ID_LINUX:
			_releasePlatform = Platform::Linux.toString();
			break;
		case S3E_OS_ID_NACL:
		case S3E_OS_ID_LG:
		case S3E_OS_ID_ARM_SEMIH:
		default:
			_releasePlatform = Platform::Windows.toString(); // who knows... assume windows
		}
		_releasePlatform = OperationParam::ReleasePlatformWindows.getValue();
#else
#error "Unknown platform!"
#endif

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
#if defined(WINAPI_FAMILY)
		TIME_ZONE_INFORMATION tzi;

		wchar_t wbuf[16];
		char cbuf[16];
		size_t bytes;

		GetTimeZoneInformation(&tzi);
		_timezoneOffset = (float)tzi.Bias / (float)-60.0;
		GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT, LOCALE_SISO639LANGNAME, wbuf, 16);
		wcstombs_s(&bytes, cbuf, 16, wbuf, 15);
		_languageCode = cbuf;
		GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT, LOCALE_SISO3166CTRYNAME, wbuf, 16);
		wcstombs_s(&bytes, cbuf, 16, wbuf, 15);
		_countryCode = cbuf;

#elif defined(__APPLE__)
		char charBuf[16];
		charBuf[0] = '\0';

		CFLocaleRef locale = CFLocaleCopyCurrent();
		if (locale != nil)
		{
			CFStringRef langCode = (CFStringRef)CFLocaleGetValue(locale, kCFLocaleLanguageCode);
			if (langCode != nil)
			{
				CFStringGetCString(langCode, charBuf, 16, kCFStringEncodingUTF8);
				_languageCode = std::string(charBuf);
			}
			CFStringRef countryCode = (CFStringRef)CFLocaleGetValue(locale, kCFLocaleCountryCode);
			if (countryCode != nil)
			{
				CFStringGetCString(countryCode, charBuf, 16, kCFStringEncodingUTF8);
				_countryCode = std::string(charBuf);
			}
			CFTimeZoneRef tz = CFTimeZoneCopySystem();
			if (tz != nil)
			{
				CFTimeInterval utcOffset = CFTimeZoneGetSecondsFromGMT(tz, CFAbsoluteTimeGetCurrent());
				_timezoneOffset = utcOffset / 3600.0f;
				CFRelease(tz);
			}
			CFRelease(locale);
		}

#elif defined (__ANDROID__)
		// do NOT set countryCode etc here as the android
		// java layer is responsible for setting it.
#elif defined (IW_SDK)
		//[read, string] Return the current device locale as a language-country code pair using the
		// ISO 639 and ISO 3166 formats respectively. For example, if the device is set to English (UK)
		// it will return "en_GB". If the device does not support providing a locale, it will return the empty string.
		std::string locale = s3eDeviceGetString(S3E_DEVICE_LOCALE);
		size_t sep = locale.find('_');
		if (sep != std::string::npos)
		{
			_languageCode = locale.substr(0, sep);
			_countryCode = locale.substr(sep + 1, locale.length());
		}

		// the other way to get language on marmalade
		//int lang = s3eDeviceGetInt(S3E_DEVICE_LANGUAGE);
		//S3E_DEVICE_LANGUAGE_ENGLISH etc

		_timezoneOffset = 0.0; // not available on marmalade... have to parse the timezone string!
#else
		//_countryCode = "";
		//_languageCode = "";
		//_timezoneOffset = 0.0;
#endif
	}
}  // end namespace
