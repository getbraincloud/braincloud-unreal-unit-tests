// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudClient.h"

#include "GameDelegates.h"
#include "BrainCloudComms.h"
#include "BrainCloudRTTComms.h"
#include "BrainCloudRelayComms.h"
#include "ServerCall.h"
#include "JsonUtil.h"
#include "IServerCallback.h"
#include "IEventCallback.h"
#include "IRewardCallback.h"
#include "IFileUploadCallback.h"
#include "IGlobalErrorCallback.h"
#include "INetworkErrorCallback.h"
#include "IRTTCallback.h"
#include "IRelayCallback.h"
#include "BCPlatform.h"

// Define all static member variables.
FString BrainCloudClient::s_brainCloudClientVersion = TEXT("4.6.1");

////////////////////////////////////////////////////
// (De)Constructors
////////////////////////////////////////////////////

/**
 * Constructor
 */
BrainCloudClient::BrainCloudClient()
{
	_brainCloudComms = new BrainCloudComms(this);
	_brainCloudRTTComms = new BrainCloudRTTComms(this);
	_brainCloudRelayComms = new BrainCloudRelayComms(this);
}

/**
 * Destructor
 */
BrainCloudClient::~BrainCloudClient()
{
	destroyService(_brainCloudComms);
	destroyService(_brainCloudRTTComms);
	destroyService(_brainCloudRelayComms);
	destroyService(_brainCloudTimeUtils);

	destroyService(_authenticationService);
	destroyService(_leaderboardService);
	destroyService(_playerStateService);
	destroyService(_gamificationService);
	destroyService(_globalEntityService);
	destroyService(_globalStatisticsService);
	destroyService(_entityService);
	destroyService(_playerStatisticsService);
	destroyService(_timeService);
	destroyService(_playerStatisticsEventService);
	destroyService(_identityService);
	destroyService(_itemCatalogService);
	destroyService(_userItemsService);
	destroyService(_eventService);
	destroyService(_s3HandlingService);
	destroyService(_scriptService);
	destroyService(_asyncMatchService);
	destroyService(_friendService);
	destroyService(_globalAppService);
	destroyService(_matchmakingService);
	destroyService(_oneWayMatchService);
	destroyService(_playbackStreamService);
	destroyService(_pushNotificationService);
	destroyService(_redemptionCodeService);
	destroyService(_dataStreamService);
	destroyService(_profanityService);
	destroyService(_fileService);
	destroyService(_groupService);
	destroyService(_mailService);
	destroyService(_tournamentService);
	destroyService(_globalFileService);
	destroyService(_customEntityService);
	destroyService(_presenceService);
	destroyService(_virtualCurrencyService);
	destroyService(_appStoreService);
	destroyService(_rttService);
	destroyService(_lobbyService);
	destroyService(_chatService);
	destroyService(_messagingService);
}

////////////////////////////////////////////////////
// Public Methods
////////////////////////////////////////////////////

void BrainCloudClient::initialize(
	const FString &serverUrl,
	const FString &secretKey,
	const FString &appId,
	const FString &appVersion)
{
	resetCommunication();
	FString error = "";
	if (serverUrl.IsEmpty())
		error = "serverURL was null or empty";
	else if (secretKey.IsEmpty())
		error = "secretKey was null or empty";
	else if (appId.IsEmpty())
		error = "appId was null or empty";
	else if (appVersion.IsEmpty())
		error = "appVersion was null or empty";

	if (!error.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR | Failed to initialize brainCloud - %s"), *error);
		return;
	}

	if (!_brainCloudComms)
		_brainCloudComms = new BrainCloudComms(this);

	_brainCloudComms->Initialize(serverUrl, secretKey, appId);
	determineReleasePlatform();

	_appId = appId;
	_appVersion = appVersion;

	if (_language.IsEmpty())
		_language = FInternationalization::Get().GetCurrentCulture()->GetTwoLetterISOLanguageName();
	if (_country.IsEmpty())
		_country = FInternationalization::Get().GetCurrentCulture()->GetRegion();
}

void BrainCloudClient::initializeWithApps(
	const FString &serverUrl,
	const FString &appId,
	const TMap<FString, FString> &secretMap,
	const FString &appVersion)
{
	resetCommunication();
	const FString &newAppId = secretMap[appId];
	FString error = "";
	if (serverUrl.IsEmpty())
		error = "serverURL was null or empty";
	else if (appId.IsEmpty())
		error = "appId was null or empty";
	else if (newAppId.IsEmpty())
		error = "no matching secret for appId";
	else if (appVersion.IsEmpty())
		error = "appVersion was null or empty";

	if (!error.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR | Failed to initialize brainCloud - %s"), *error);
		return;
	}

	if (!_brainCloudComms)
		_brainCloudComms = new BrainCloudComms(this);

	_brainCloudComms->InitializeWithApps(serverUrl, secretMap, appId);
	determineReleasePlatform();

	_appId = appId;
	_appVersion = appVersion;

	if (_language.IsEmpty())
		_language = FInternationalization::Get().GetCurrentCulture()->GetTwoLetterISOLanguageName();
	if (_country.IsEmpty())
		_country = FInternationalization::Get().GetCurrentCulture()->GetRegion();
}

void BrainCloudClient::initializeIdentity(const FString &profileId, const FString &anonymousId)
{
	getAuthenticationService()->initialize(profileId, anonymousId);
}

void BrainCloudClient::runCallbacks(eBCUpdateType in_updateType /*= eBCUpdateType::ALL*/)
{
	switch (in_updateType)
	{
	case eBCUpdateType::REST:
	{
		if (_brainCloudComms)
			_brainCloudComms->RunCallbacks();
	}
	break;

	case eBCUpdateType::RTT:
	{
		if (_brainCloudRTTComms)
			_brainCloudRTTComms->RunCallbacks();
	}
	break;

	case eBCUpdateType::RS:
	{
		if (_brainCloudRelayComms)
			_brainCloudRelayComms->RunCallbacks();
	}
	break;

	default:
	case eBCUpdateType::ALL:
	{
		if (_brainCloudComms)
			_brainCloudComms->RunCallbacks();

		if (_brainCloudRTTComms)
			_brainCloudRTTComms->RunCallbacks();

		if (_brainCloudRelayComms)
			_brainCloudRelayComms->RunCallbacks();
	}
	break;
	}
}

void BrainCloudClient::registerEventCallback(IEventCallback *eventCallback)
{
	_brainCloudComms->RegisterEventCallback(eventCallback);
}

void BrainCloudClient::registerEventCallback(UBCBlueprintRestCallProxyBase *eventCallback)
{
	_brainCloudComms->RegisterEventCallback(eventCallback);
}

void BrainCloudClient::deregisterEventCallback()
{
	_brainCloudComms->DeregisterEventCallback();
}

void BrainCloudClient::registerRewardCallback(IRewardCallback *rewardCallback)
{
	_brainCloudComms->RegisterRewardCallback(rewardCallback);
}

void BrainCloudClient::registerRewardCallback(UBCBlueprintRestCallProxyBase *eventCallback)
{
	_brainCloudComms->RegisterRewardCallback(eventCallback);
}

void BrainCloudClient::deregisterRewardCallback()
{
	_brainCloudComms->DeregisterRewardCallback();
}

void BrainCloudClient::registerFileUploadCallback(IFileUploadCallback *fileUploadCallback)
{
	_brainCloudComms->RegisterFileUploadCallback(fileUploadCallback);
}

void BrainCloudClient::registerFileUploadCallback(UBCBlueprintRestCallProxyBase *eventCallback)
{
	_brainCloudComms->RegisterFileUploadCallback(eventCallback);
}

void BrainCloudClient::deregisterFileUploadCallback()
{
	_brainCloudComms->DeregisterFileUploadCallback();
}

void BrainCloudClient::registerGlobalErrorCallback(IGlobalErrorCallback *globalErrorCallback)
{
	_brainCloudComms->RegisterGlobalErrorCallback(globalErrorCallback);
}

void BrainCloudClient::registerGlobalErrorCallback(UBCBlueprintRestCallProxyBase *eventCallback)
{
	_brainCloudComms->RegisterGlobalErrorCallback(eventCallback);
}

void BrainCloudClient::deregisterGlobalErrorCallback()
{
	_brainCloudComms->DeregisterGlobalErrorCallback();
}

void BrainCloudClient::registerNetworkErrorCallback(INetworkErrorCallback *networkErrorCallback)
{
	_brainCloudComms->RegisterNetworkErrorCallback(networkErrorCallback);
}

void BrainCloudClient::registerNetworkErrorCallback(UBCBlueprintRestCallProxyBase *eventCallback)
{
	_brainCloudComms->RegisterNetworkErrorCallback(eventCallback);
}

void BrainCloudClient::deregisterNetworkErrorCallback()
{
	_brainCloudComms->DeregisterNetworkErrorCallback();
}

void BrainCloudClient::enableLogging(bool shouldEnable)
{
	_brainCloudComms->EnableLogging(shouldEnable);
}

bool BrainCloudClient::isLoggingEnabled()
{
	return _brainCloudComms->IsLoggingEnabled();
}

bool BrainCloudClient::isAuthenticated()
{
	return _brainCloudComms != nullptr ? _brainCloudComms->IsAuthenticated() : false;
}

bool BrainCloudClient::isInitialized()
{
	return _brainCloudComms != nullptr ? _brainCloudComms->IsInitialized() : false;
}

void BrainCloudClient::heartbeat()
{
	_brainCloudComms->Heartbeat();
}

void BrainCloudClient::sendRequest(ServerCall *serviceMessage)
{
	_brainCloudComms->AddToQueue(serviceMessage);
}

void BrainCloudClient::resetCommunication()
{
	_brainCloudComms->ResetCommunication();
	_brainCloudRTTComms->disableRTT();
	_brainCloudRelayComms->disconnect();

	if (_authenticationService)
		_authenticationService->clearSavedProfileId();
}

void BrainCloudClient::setHeartbeatInterval(int32 intervalInMilliseconds)
{
	_brainCloudComms->SetHeartbeatInterval(intervalInMilliseconds);
}

void BrainCloudClient::setPacketTimeouts(const TArray<int32> &timeouts)
{
	_brainCloudComms->SetPacketTimeouts(timeouts);
}

void BrainCloudClient::setPacketTimeoutsToDefault()
{
	_brainCloudComms->SetPacketTimeoutsToDefault();
}

const TArray<int32> &BrainCloudClient::getPacketTimeouts()
{
	return _brainCloudComms->GetPacketTimeouts();
}

int32 BrainCloudClient::getAuthenticationPacketTimeout()
{
	return _brainCloudComms->GetAuthenticationPacketTimeout();
}

void BrainCloudClient::setAuthenticationPacketTimeout(int32 timeoutSecs)
{
	_brainCloudComms->SetAuthenticationPacketTimeout(timeoutSecs);
}

int32 BrainCloudClient::getUploadLowTransferRateTimeout()
{
	return _brainCloudComms->GetUploadLowTransferRateTimeout();
}

void BrainCloudClient::setUploadLowTransferRateTimeout(int32 timeoutSecs)
{
	_brainCloudComms->SetUploadLowTransferRateTimeout(timeoutSecs);
}

int32 BrainCloudClient::getUploadLowTransferRateThreshold()
{
	return _brainCloudComms->GetUploadLowTransferRateThreshold();
}

void BrainCloudClient::setUploadLowTransferRateThreshold(int32 bytesPerSec)
{
	_brainCloudComms->SetUploadLowTransferRateThreshold(bytesPerSec);
}

void BrainCloudClient::setOldStyleStatusMessageErrorCallback(bool enabled)
{
	_brainCloudComms->SetOldStyleStatusMessageErrorCallback(enabled);
}

void BrainCloudClient::setErrorCallbackOn202Status(bool isError)
{
	_brainCloudComms->SetErrorCallbackOn202Status(isError);
}

void BrainCloudClient::enableNetworkErrorMessageCaching(bool enabled)
{
	_brainCloudComms->EnableNetworkErrorMessageCaching(enabled);
}

void BrainCloudClient::retryCachedMessages()
{
	_brainCloudComms->RetryCachedMessages();
}

void BrainCloudClient::flushCachedMessages(bool sendApiErrorCallbacks)
{
	_brainCloudComms->FlushCachedMessages(sendApiErrorCallbacks);
}

void BrainCloudClient::insertEndOfMessageBundleMarker()
{
	_brainCloudComms->InsertEndOfMessageBundleMarker();
}

BrainCloudTimeUtils *BrainCloudClient::getUtil()
{
	if (_brainCloudTimeUtils == nullptr)
	{
		_brainCloudTimeUtils = new BrainCloudTimeUtils(this);
	}
	return _brainCloudTimeUtils;
}

BrainCloudAuthentication *BrainCloudClient::getAuthenticationService()
{
	if (_authenticationService == nullptr)
	{
		_authenticationService = new BrainCloudAuthentication(this);
	}
	return _authenticationService;
}

BrainCloudLeaderboard *BrainCloudClient::getLeaderboardService()
{
	if (_leaderboardService == nullptr)
	{
		_leaderboardService = new BrainCloudLeaderboard(this);
	}
	return _leaderboardService;
}

BrainCloudPlayerState *BrainCloudClient::getPlayerStateService()
{
	if (_playerStateService == nullptr)
	{
		_playerStateService = new BrainCloudPlayerState(this);
	}
	return _playerStateService;
}

BrainCloudGamification *BrainCloudClient::getGamificationService()
{
	if (_gamificationService == nullptr)
	{
		_gamificationService = new BrainCloudGamification(this);
	}
	return _gamificationService;
}

BrainCloudGlobalEntity *BrainCloudClient::getGlobalEntityService()
{
	if (_globalEntityService == nullptr)
	{
		_globalEntityService = new BrainCloudGlobalEntity(this);
	}
	return _globalEntityService;
}

BrainCloudGlobalStatistics *BrainCloudClient::getGlobalStatisticsService()
{
	if (_globalStatisticsService == nullptr)
	{
		_globalStatisticsService = new BrainCloudGlobalStatistics(this);
	}
	return _globalStatisticsService;
}

BrainCloudEntity *BrainCloudClient::getEntityService()
{
	if (_entityService == nullptr)
	{
		_entityService = new BrainCloudEntity(this);
	}
	return _entityService;
}

BrainCloudPlayerStatistics *BrainCloudClient::getPlayerStatisticsService()
{
	if (_playerStatisticsService == nullptr)
	{
		_playerStatisticsService = new BrainCloudPlayerStatistics(this);
	}
	return _playerStatisticsService;
}

BrainCloudTime *BrainCloudClient::getTimeService()
{
	if (_timeService == nullptr)
	{
		_timeService = new BrainCloudTime(this);
	}
	return _timeService;
}

BrainCloudPlayerStatisticsEvent *BrainCloudClient::getPlayerStatisticsEventService()
{
	if (_playerStatisticsEventService == nullptr)
	{
		_playerStatisticsEventService = new BrainCloudPlayerStatisticsEvent(this);
	}
	return _playerStatisticsEventService;
}

BrainCloudPresence *BrainCloudClient::getPresenceService()
{
	if (_presenceService == nullptr)
	{
		_presenceService = new BrainCloudPresence(this);
	}
	return _presenceService;
}

BrainCloudIdentity *BrainCloudClient::getIdentityService()
{
	if (_identityService == nullptr)
	{
		_identityService = new BrainCloudIdentity(this);
	}
	return _identityService;
}

BrainCloudItemCatalog *BrainCloudClient::getItemCatalogService()
{
	if (_itemCatalogService == nullptr)
	{
		_itemCatalogService = new BrainCloudItemCatalog(this);
	}
	return _itemCatalogService;
}

BrainCloudUserItems *BrainCloudClient::getUserItemsService()
{
	if (_userItemsService == nullptr)
	{
		_userItemsService = new BrainCloudUserItems(this);
	}
	return _userItemsService;
}

BrainCloudEvent *BrainCloudClient::getEventService()
{
	if (_eventService == nullptr)
	{
		_eventService = new BrainCloudEvent(this);
	}
	return _eventService;
}

BrainCloudS3Handling *BrainCloudClient::getS3HandlingService()
{
	if (_s3HandlingService == nullptr)
	{
		_s3HandlingService = new BrainCloudS3Handling(this);
	}
	return _s3HandlingService;
}

BrainCloudScript *BrainCloudClient::getScriptService()
{
	if (_scriptService == nullptr)
	{
		_scriptService = new BrainCloudScript(this);
	}
	return _scriptService;
}

BrainCloudAsyncMatch *BrainCloudClient::getAsyncMatchService()
{
	if (_asyncMatchService == nullptr)
	{
		_asyncMatchService = new BrainCloudAsyncMatch(this);
	}
	return _asyncMatchService;
}

BrainCloudFriend *BrainCloudClient::getFriendService()
{
	if (_friendService == nullptr)
	{
		_friendService = new BrainCloudFriend(this);
	}
	return _friendService;
}

BrainCloudGlobalApp *BrainCloudClient::getGlobalAppService()
{
	if (_globalAppService == nullptr)
	{
		_globalAppService = new BrainCloudGlobalApp(this);
	}
	return _globalAppService;
}

BrainCloudMatchmaking *BrainCloudClient::getMatchmakingService()
{
	if (_matchmakingService == nullptr)
	{
		_matchmakingService = new BrainCloudMatchmaking(this);
	}
	return _matchmakingService;
}

BrainCloudOneWayMatch *BrainCloudClient::getOneWayMatchService()
{
	if (_oneWayMatchService == nullptr)
	{
		_oneWayMatchService = new BrainCloudOneWayMatch(this);
	}
	return _oneWayMatchService;
}

BrainCloudPlaybackStream *BrainCloudClient::getPlaybackStreamService()
{
	if (_playbackStreamService == nullptr)
	{
		_playbackStreamService = new BrainCloudPlaybackStream(this);
	}
	return _playbackStreamService;
}

BrainCloudPushNotification *BrainCloudClient::getPushNotificationService()
{
	if (_pushNotificationService == nullptr)
	{
		_pushNotificationService = new BrainCloudPushNotification(this);
	}
	return _pushNotificationService;
}

BrainCloudRedemptionCode *BrainCloudClient::getRedemptionCodeService()
{
	if (_redemptionCodeService == nullptr)
	{
		_redemptionCodeService = new BrainCloudRedemptionCode(this);
	}
	return _redemptionCodeService;
}

BrainCloudDataStream *BrainCloudClient::getDataStreamService()
{
	if (_dataStreamService == nullptr)
	{
		_dataStreamService = new BrainCloudDataStream(this);
	}
	return _dataStreamService;
}

BrainCloudProfanity *BrainCloudClient::getProfanityService()
{
	if (_profanityService == nullptr)
	{
		_profanityService = new BrainCloudProfanity(this);
	}
	return _profanityService;
}

BrainCloudFile *BrainCloudClient::getFileService()
{
	if (_fileService == nullptr)
	{
		_fileService = new BrainCloudFile(this);
	}
	return _fileService;
}

BrainCloudGroup *BrainCloudClient::getGroupService()
{
	if (_groupService == nullptr)
	{
		_groupService = new BrainCloudGroup(this);
	}
	return _groupService;
}

BrainCloudMail *BrainCloudClient::getMailService()
{
	if (_mailService == nullptr)
	{
		_mailService = new BrainCloudMail(this);
	}
	return _mailService;
}

BrainCloudTournament *BrainCloudClient::getTournamentService()
{
	if (_tournamentService == nullptr)
	{
		_tournamentService = new BrainCloudTournament(this);
	}
	return _tournamentService;
}

BrainCloudGlobalFile *BrainCloudClient::getGlobalFileService()
{
	if (_globalFileService == nullptr)
	{
		_globalFileService = new BrainCloudGlobalFile(this);
	}
	return _globalFileService;
}

BrainCloudCustomEntity *BrainCloudClient::getCustomEntityService()
{
	if (_customEntityService == nullptr)
	{
		_customEntityService = new BrainCloudCustomEntity(this);
	}
	return _customEntityService;
}

BrainCloudVirtualCurrency *BrainCloudClient::getVirtualCurrencyService()
{
	if (_virtualCurrencyService == nullptr)
	{
		_virtualCurrencyService = new BrainCloudVirtualCurrency(this);
	}
	return _virtualCurrencyService;
}

BrainCloudAppStore *BrainCloudClient::getAppStoreService()
{
	if (_appStoreService == nullptr)
	{
		_appStoreService = new BrainCloudAppStore(this);
	}
	return _appStoreService;
}

BrainCloudRTT *BrainCloudClient::getRTTService()
{
	if (_rttService == nullptr)
	{
		_rttService = new BrainCloudRTT(_brainCloudRTTComms, this);
	}
	return _rttService;
}

BrainCloudLobby *BrainCloudClient::getLobbyService()
{
	if (_lobbyService == nullptr)
	{
		_lobbyService = new BrainCloudLobby(this);
	}
	return _lobbyService;
}

BrainCloudChat *BrainCloudClient::getChatService()
{
	if (_chatService == nullptr)
	{
		_chatService = new BrainCloudChat(this);
	}
	return _chatService;
}

BrainCloudMessaging *BrainCloudClient::getMessagingService()
{
	if (_messagingService == nullptr)
	{
		_messagingService = new BrainCloudMessaging(this);
	}
	return _messagingService;
}


BrainCloudRelay *BrainCloudClient::getRelayService()
{
	if (_relayService == nullptr)
	{
		_relayService = new BrainCloudRelay(this, _brainCloudRelayComms);
	}
	return _relayService;
}

const FString &BrainCloudClient::getSessionId()
{
	return _brainCloudComms->GetSessionId();
}

const FString &BrainCloudClient::getRTTConnectionId()
{
	return _brainCloudRTTComms->getConnectionId();
}

const FString &BrainCloudClient::getEventServer()
{
	return _brainCloudRTTComms->getEventServer();
}

////////////////////////////////////////////////////
// Private Methods
////////////////////////////////////////////////////

void BrainCloudClient::determineReleasePlatform()
{
	FString platform = UGameplayStatics::GetPlatformName();

	if (platform == TEXT("Windows"))
		_releasePlatform = BCPlatform::EnumToString(EBCPlatform::WINDOWS);
	else if (platform == TEXT("Mac"))
		_releasePlatform = BCPlatform::EnumToString(EBCPlatform::MAC);
	else if (platform == TEXT("IOS"))
		_releasePlatform = BCPlatform::EnumToString(EBCPlatform::IOS);
	else if (platform == TEXT("Android"))
	{
		#if PLATFORM_ANDROID
		if(FAndroidMisc::GetDeviceMake() == TEXT("Amazon"))
		{
			_releasePlatform = BCPlatform::EnumToString(EBCPlatform::AMAZON_ANDROID);
		}
		else{
			_releasePlatform = BCPlatform::EnumToString(EBCPlatform::GOOGLE_PLAY_ANDROID);
		}
		#endif
	}
	else if (platform == TEXT("Linux"))
		_releasePlatform = BCPlatform::EnumToString(EBCPlatform::LINUX_PLATFORM);
	else if (platform == TEXT("HTML5"))
		_releasePlatform = BCPlatform::EnumToString(EBCPlatform::WEB);
	else if (platform == TEXT("XboxOne"))
		_releasePlatform = BCPlatform::EnumToString(EBCPlatform::XBOX_ONE);
	else if (platform == TEXT("PS4"))
		_releasePlatform = BCPlatform::EnumToString(EBCPlatform::PS4);
	else
	{
		_releasePlatform = BCPlatform::EnumToString(EBCPlatform::UNKNOWN);
		UE_LOG(LogTemp, Warning, TEXT("brainCloud does not recognize target platform %s. Platform set to Unknown."), *platform);
	}
}

template <class T>
void BrainCloudClient::destroyService(T *&service)
{
	if (service != nullptr)
	{
		delete (service);
		service = nullptr;
	}
}
