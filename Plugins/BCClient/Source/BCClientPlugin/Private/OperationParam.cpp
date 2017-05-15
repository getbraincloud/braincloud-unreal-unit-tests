// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#include "BCClientPluginPrivatePCH.h"
#include "OperationParam.h"

OperationParam::OperationParam(const FString& operation)
{
    _value = operation;
}

	//Push Notification Service - Send Params
	const OperationParam OperationParam::PushNotificationSendParamToPlayerId = OperationParam(TEXT("toPlayerId"));
	const OperationParam OperationParam::PushNotificationSendParamProfileId = OperationParam(TEXT("profileId"));
	const OperationParam OperationParam::PushNotificationSendParamMessage = OperationParam(TEXT("message"));
	const OperationParam OperationParam::PushNotificationSendParamNotificationTemplateId = OperationParam(TEXT("notificationTemplateId"));
	const OperationParam OperationParam::PushNotificationSendParamSubstitution = OperationParam(TEXT("substitutions"));
	const OperationParam OperationParam::AlertContent = OperationParam(TEXT("alertContent"));
	const OperationParam OperationParam::CustomData = OperationParam(TEXT("customData"));
	const OperationParam OperationParam::StartTimeUTC = OperationParam(TEXT("startDateUTC"));
	const OperationParam OperationParam::MinutesFromNow = OperationParam(TEXT("minutesFromNow"));

	//Push Notification Service - Register Params
	const OperationParam OperationParam::PushNotificationRegisterParamDeviceType = OperationParam(TEXT("deviceType"));
	const OperationParam OperationParam::PushNotificationRegisterParamDeviceToken = OperationParam(TEXT("deviceToken"));
	const OperationParam OperationParam::PushNotificationRegisterParamPushId = OperationParam(TEXT("pushId"));
	const OperationParam OperationParam::PushNotificationRegisterParamToPlayerId = OperationParam(TEXT("toPlayerId"));
	const OperationParam OperationParam::PushNotificationRegisterParamContent = OperationParam(TEXT("content"));
	const OperationParam OperationParam::PushNotificationRegisterParamSendInterval = OperationParam(TEXT("sendInterval"));
	const OperationParam OperationParam::PushNotificationRegisterParamScheduleIn = OperationParam(TEXT("scheduleIn"));

	// Twitter Service - Verify Params
	const OperationParam OperationParam::TwitterServiceVerifyToken = OperationParam(TEXT("token"));
	const OperationParam OperationParam::TwitterServiceVerifyVerifier = OperationParam(TEXT("verifier"));

	// Twitter Service - Tweet Params
	const OperationParam OperationParam::TwitterServiceTweetToken = OperationParam(TEXT("token"));
	const OperationParam OperationParam::TwitterServiceTweetSecret = OperationParam(TEXT("secret"));
	const OperationParam OperationParam::TwitterServiceTweetTweet = OperationParam(TEXT("tweet"));
	const OperationParam OperationParam::TwitterServiceTweetPic = OperationParam(TEXT("pic"));

	// Authenticate Service - Authenticate Params
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthenticationType = OperationParam(TEXT("authenticationType"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthenticationToken = OperationParam(TEXT("authenticationToken"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateExternalId = OperationParam(TEXT("externalId"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateGameId = OperationParam(TEXT("gameId"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateDeviceId = OperationParam(TEXT("deviceId"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateForceMergeFlag = OperationParam(TEXT("forceMergeFlag"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateReleasePlatform = OperationParam(TEXT("releasePlatform"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateGameVersion = OperationParam(TEXT("gameVersion"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateBrainCloudVersion = OperationParam(TEXT("clientLibVersion"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthFacebook = OperationParam(TEXT("Facebook"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthEmail = OperationParam(TEXT("Email"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthGameCenter = OperationParam(TEXT("GameCenter"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthUniversal = OperationParam(TEXT("Universal"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthSteam = OperationParam(TEXT("Steam"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthGoogle = OperationParam(TEXT("Google"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthParse = OperationParam(TEXT("Parse"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthUpgradeId = OperationParam(TEXT("upgradeAppId"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthAnonymous = OperationParam(TEXT("Anonymous"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthExternal = OperationParam(TEXT("External"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAnonymousId = OperationParam(TEXT("anonymousId"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateProfileId = OperationParam(TEXT("profileId"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateForceCreate = OperationParam(TEXT("forceCreate"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateExternalAuthName = OperationParam(TEXT("externalAuthName"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateRegion = OperationParam(TEXT("region"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateCountryCode = OperationParam(TEXT("countryCode"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateLanguageCode = OperationParam(TEXT("languageCode"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateTimeZoneOffset = OperationParam(TEXT("timeZoneOffset"));
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthTwitter = OperationParam(TEXT("Twitter"));
	const OperationParam OperationParam::Peer = OperationParam(TEXT("peer"));

	// Authenticate Service - Authenticate Params
	const OperationParam OperationParam::IdentityServiceExternalId = OperationParam(TEXT("externalId"));
	const OperationParam OperationParam::IdentityServiceAuthenticationType = OperationParam(TEXT("authenticationType"));
	const OperationParam OperationParam::IdentityServiceConfirmAnonymous = OperationParam(TEXT("confirmAnonymous"));

	// Async Match Service - Async Match Params
	const OperationParam OperationParam::AsyncMatchServicePlayers = OperationParam(TEXT("players"));
	const OperationParam OperationParam::AsyncMatchServiceMatchState = OperationParam(TEXT("matchState"));
	const OperationParam OperationParam::AsyncMatchServiceMatchId = OperationParam(TEXT("matchId"));
	const OperationParam OperationParam::AsyncMatchServiceCurrentPlayer = OperationParam(TEXT("currentPlayer"));
	const OperationParam OperationParam::AsyncMatchServiceMatchSummary = OperationParam(TEXT("summary"));
	const OperationParam OperationParam::AsyncMatchServicePushMessage = OperationParam(TEXT("pushContent"));
	const OperationParam OperationParam::AsyncMatchServiceOwnerId = OperationParam(TEXT("ownerId"));
	const OperationParam OperationParam::AsyncMatchServiceVersion = OperationParam(TEXT("version"));
	const OperationParam OperationParam::AsyncMatchServiceStatistics = OperationParam(TEXT("statistics"));
	const OperationParam OperationParam::AsyncMatchServiceMatchStatus = OperationParam(TEXT("status"));

	// Entity Service
	const OperationParam OperationParam::EntityServiceEntityId = OperationParam(TEXT("entityId"));
	const OperationParam OperationParam::EntityServiceEntityType = OperationParam(TEXT("entityType"));
	const OperationParam OperationParam::EntityServiceEntitySubtype = OperationParam(TEXT("entitySubtype"));
	const OperationParam OperationParam::EntityServiceData = OperationParam(TEXT("data"));
	const OperationParam OperationParam::EntityServiceAcl = OperationParam(TEXT("acl"));
	const OperationParam OperationParam::EntityServiceVersion = OperationParam(TEXT("version"));
	const OperationParam OperationParam::EntityServiceFriendData = OperationParam(TEXT("friendData"));
	const OperationParam OperationParam::EntityServiceTargetPlayerId = OperationParam(TEXT("targetPlayerId"));
	const OperationParam OperationParam::EntityServiceUpdateOps = OperationParam(TEXT("updateOps"));

	// Global Entity Service - Params
	const OperationParam OperationParam::GlobalEntityServiceEntityId = OperationParam(TEXT("entityId"));
	const OperationParam OperationParam::GlobalEntityServiceEntityType = OperationParam(TEXT("entityType"));
	const OperationParam OperationParam::GlobalEntityServiceIndexedId = OperationParam(TEXT("entityIndexedId"));
	const OperationParam OperationParam::GlobalEntityServiceTimeToLive = OperationParam(TEXT("timeToLive"));
	const OperationParam OperationParam::GlobalEntityServiceData = OperationParam(TEXT("data"));
	const OperationParam OperationParam::GlobalEntityServiceAcl = OperationParam(TEXT("acl"));
	const OperationParam OperationParam::GlobalEntityServiceVersion = OperationParam(TEXT("version"));
	const OperationParam OperationParam::GlobalEntityServiceMaxReturn = OperationParam(TEXT("maxReturn"));
	const OperationParam OperationParam::GlobalEntityServiceWhere = OperationParam(TEXT("where"));
	const OperationParam OperationParam::GlobalEntityServiceOrderBy = OperationParam(TEXT("orderBy"));
	const OperationParam OperationParam::GlobalEntityServiceContext = OperationParam(TEXT("context"));
	const OperationParam OperationParam::GlobalEntityServicePageOffset = OperationParam(TEXT("pageOffset"));
	const OperationParam OperationParam::OwnerId = OperationParam(TEXT("ownerId"));

	// Event Service - Send Params
	const OperationParam OperationParam::EventServiceSendToId = OperationParam(TEXT("toId"));
	const OperationParam OperationParam::EventServiceSendEventType = OperationParam(TEXT("eventType"));
	const OperationParam OperationParam::EventServiceSendEventId = OperationParam(TEXT("eventId"));
	const OperationParam OperationParam::EventServiceSendEventData = OperationParam(TEXT("eventData"));
	const OperationParam OperationParam::EventServiceSendRecordLocally = OperationParam(TEXT("recordLocally"));

	// Event Service - Update Event Data Params
	const OperationParam OperationParam::EventServiceUpdateEventDataFromId = OperationParam(TEXT("fromId"));
	const OperationParam OperationParam::EventServiceUpdateEventDataEventId = OperationParam(TEXT("eventId"));
	const OperationParam OperationParam::EventServiceUpdateEventDataData = OperationParam(TEXT("eventData"));
	const OperationParam OperationParam::EvId = OperationParam(TEXT("evId"));

	// Event Service - Delete Incoming Params
	const OperationParam OperationParam::EventServiceDeleteIncomingEventId = OperationParam(TEXT("eventId"));
	const OperationParam OperationParam::EventServiceDeleteIncomingFromId = OperationParam(TEXT("fromId"));

	// Event Service - Delete Sent Params
	const OperationParam OperationParam::EventServiceDeleteSentEventId = OperationParam(TEXT("eventId"));
	const OperationParam OperationParam::EventServiceDeleteSentToId = OperationParam(TEXT("toId"));
	const OperationParam OperationParam::EventServiceIncludeIncomingEvents = OperationParam(TEXT("includeIncomingEvents"));
	const OperationParam OperationParam::EventServiceIncludeSentEvents = OperationParam(TEXT("includeSentEvents"));

	// Friend Service - Params
	const OperationParam OperationParam::FriendServiceAuthenticationType = OperationParam(TEXT("authenticationType"));
	const OperationParam OperationParam::FriendServiceEntityId = OperationParam(TEXT("entityId"));
	const OperationParam OperationParam::FriendServiceExternalId = OperationParam(TEXT("externalId"));
	const OperationParam OperationParam::FriendServiceProfileId = OperationParam(TEXT("profileId"));
	const OperationParam OperationParam::FriendServiceFriendId = OperationParam(TEXT("friendId"));
	const OperationParam OperationParam::FriendServiceEntityType = OperationParam(TEXT("entityType"));
	const OperationParam OperationParam::FriendServiceEntitySubType = OperationParam(TEXT("entitySubtype"));
	const OperationParam OperationParam::FriendServiceIncludeSummaryData = OperationParam(TEXT("includeSummaryData"));
	const OperationParam OperationParam::FriendServiceReadPlayerStateFriendId = OperationParam(TEXT("friendId"));
	const OperationParam OperationParam::FriendServiceSearchText = OperationParam(TEXT("searchText"));
	const OperationParam OperationParam::FriendServiceMaxResults = OperationParam(TEXT("maxResults"));
	const OperationParam OperationParam::FriendServiceFriendPlatform = OperationParam(TEXT("friendPlatform"));
	const OperationParam OperationParam::FriendServiceProfileIds = OperationParam(TEXT("profileIds"));
	const OperationParam OperationParam::ExternalAuthType = OperationParam(TEXT("externalAuthType"));

	//Achievements Event Data Params
	const OperationParam OperationParam::GamificationServiceAchievementsName = OperationParam(TEXT("achievements"));
	const OperationParam OperationParam::GamificationServiceAchievementsData = OperationParam(TEXT("data"));
	const OperationParam OperationParam::GamificationServiceAchievementsGranted = OperationParam(TEXT("achievementsGranted"));
	const OperationParam OperationParam::GamificationServiceCategory = OperationParam(TEXT("category"));
	const OperationParam OperationParam::GamificationServiceIncludeMetaData = OperationParam(TEXT("includeMetaData"));
	const OperationParam OperationParam::GamificationServiceMilestonesName = OperationParam(TEXT("milestones"));

	// Player Statistics Event Params
	const OperationParam OperationParam::PlayerStatisticEventServiceEventName = OperationParam(TEXT("eventName"));
	const OperationParam OperationParam::PlayerStatisticEventServiceEventMultiplier = OperationParam(TEXT("eventMultiplier"));
	const OperationParam OperationParam::PlayerStatisticEventServiceEvents = OperationParam(TEXT("events"));

	// Player State Service - Read Params
	const OperationParam OperationParam::PlayerStateServiceReadEntitySubtype = OperationParam(TEXT("entitySubType"));

	// Player State Service - Update Summary Params
	const OperationParam OperationParam::PlayerStateServiceUpdateSummaryFriendData = OperationParam(TEXT("summaryFriendData"));

	// Player State Service - Update Name Params
	const OperationParam OperationParam::PlayerStateServiceUpdateNameData = OperationParam(TEXT("playerName"));

	// Player State Service - Atributes
	const OperationParam OperationParam::PlayerStateServiceAttributes = OperationParam(TEXT("attributes"));
	const OperationParam OperationParam::PlayerStateServiceWipeExisting = OperationParam(TEXT("wipeExisting"));

	// Player State Service - Atributes
	const OperationParam OperationParam::PlayerStateServicePictureUrl = OperationParam(TEXT("playerPictureUrl"));
	const OperationParam OperationParam::PlayerStateServiceContactEmail = OperationParam(TEXT("contactEmail"));

	// Player Statistics Service - Update Increment Params
	const OperationParam OperationParam::PlayerStatisticsServiceStats = OperationParam(TEXT("statistics"));
	const OperationParam OperationParam::PlayerStatisticsServiceStatNames = OperationParam(TEXT("statNames"));
	const OperationParam OperationParam::PlayerStatisticsExperiencePoints = OperationParam(TEXT("xp_points"));

	// Player Statistics Service - Read Params
	const OperationParam OperationParam::PlayerStatisticsServiceReadEntitySubType = OperationParam(TEXT("entitySubType"));

	// Leaderboard Service - Get Leaderboard Params
	const OperationParam OperationParam::LeaderboardServiceLeaderboardId = OperationParam(TEXT("leaderboardId"));
	const OperationParam OperationParam::LeaderboardServiceLeaderboardIds = OperationParam(TEXT("leaderboardIds"));
	const OperationParam OperationParam::LeaderboardServiceReplaceName = OperationParam(TEXT("replaceName"));
	const OperationParam OperationParam::LeaderboardServiceScore = OperationParam(TEXT("score"));
	const OperationParam OperationParam::LeaderboardServiceData = OperationParam(TEXT("data"));
	const OperationParam OperationParam::LeaderboardServiceEventName = OperationParam(TEXT("eventName"));
	const OperationParam OperationParam::LeaderboardServiceEventMultiplier = OperationParam(TEXT("eventMultiplier"));
	const OperationParam OperationParam::LeaderboardServiceLeaderboardType = OperationParam(TEXT("leaderboardType"));
	const OperationParam OperationParam::LeaderboardServiceRotationType = OperationParam(TEXT("rotationType"));
	const OperationParam OperationParam::LeaderboardServiceRotationReset = OperationParam(TEXT("rotationReset"));
	const OperationParam OperationParam::LeaderboardServiceRotationResetTime = OperationParam(TEXT("rotationResetTime"));
	const OperationParam OperationParam::LeaderboardServiceRetainedCount = OperationParam(TEXT("retainedCount"));
	const OperationParam OperationParam::LeaderboardServiceFetchType = OperationParam(TEXT("fetchType"));
	const OperationParam OperationParam::LeaderboardServiceSortOrder = OperationParam(TEXT("sort"));
	const OperationParam OperationParam::LeaderboardServiceMaxResults = OperationParam(TEXT("maxResults"));
	const OperationParam OperationParam::LeaderboardServiceStartIndex = OperationParam(TEXT("startIndex"));
	const OperationParam OperationParam::LeaderboardServiceEndIndex = OperationParam(TEXT("endIndex"));
	const OperationParam OperationParam::LeaderboardServiceBeforeCount = OperationParam(TEXT("beforeCount"));
	const OperationParam OperationParam::LeaderboardServiceAfterCount = OperationParam(TEXT("afterCount"));
	const OperationParam OperationParam::LeaderboardServiceIncludeLeaderboardSize = OperationParam(TEXT("includeLeaderboardSize"));
	const OperationParam OperationParam::LeaderboardServiceVersionId = OperationParam(TEXT("versionId"));
	const OperationParam OperationParam::LeaderboardServiceLeaderboardResultCount = OperationParam(TEXT("leaderboardResultCount"));
	const OperationParam OperationParam::ProfileIds = OperationParam("profileIds");
	const OperationParam OperationParam::NumDaysToRotate = OperationParam(TEXT("numDaysToRotate"));

	// Product service
	const OperationParam OperationParam::ProductServiceVCId = OperationParam(TEXT("vc_id"));
	const OperationParam OperationParam::ProductServiceVCAmount = OperationParam(TEXT("vc_amount"));

	// Product Service - Get Inventory Params
	const OperationParam OperationParam::ProductServiceGetInventoryPlatform = OperationParam(TEXT("platform"));
	const OperationParam OperationParam::ProductServiceGetInventoryUserCurrency = OperationParam(TEXT("user_currency"));
	const OperationParam OperationParam::ProductServiceGetInventoryCategory = OperationParam(TEXT("category"));

	// Product Service - Op Cash In Receipt Params
	const OperationParam OperationParam::ProductServiceOpCashInReceiptReceipt = OperationParam(TEXT("receipt"));
	const OperationParam OperationParam::ProductServiceOpCashInReceiptUrl = OperationParam(TEXT("url"));

	// Server Time Service - Read Params
	const OperationParam OperationParam::ServerTimeServiceRead = OperationParam(TEXT(""));

	// data creation parms
	const OperationParam OperationParam::ServiceMessageService = OperationParam(TEXT("service"));
	const OperationParam OperationParam::ServiceMessageOperation = OperationParam(TEXT("operation"));
	const OperationParam OperationParam::ServiceMessageData = OperationParam(TEXT("data"));

	// data bundle creation parms
	const OperationParam OperationParam::ServiceMessagePacketId = OperationParam(TEXT("packetId"));
	const OperationParam OperationParam::ServiceMessageProfileId = OperationParam(TEXT("profileId"));
	const OperationParam OperationParam::ServiceMessageSessionId = OperationParam(TEXT("sessionId"));
	const OperationParam OperationParam::ServiceMessageMessages = OperationParam(TEXT("messages"));

	// Error Params
	const OperationParam OperationParam::ServiceMessageReasonCode = OperationParam(TEXT("reasoncode"));
	const OperationParam OperationParam::ServiceMessageStatusMessage = OperationParam(TEXT("statusmessage"));

	// bad place to define these constants...
	const OperationParam OperationParam::ReleasePlatformIos = OperationParam(TEXT("IOS"));
	const OperationParam OperationParam::ReleasePlatformFacebook = OperationParam(TEXT("FB"));
	const OperationParam OperationParam::ReleasePlatformBlackberry = OperationParam(TEXT("BB"));
	const OperationParam OperationParam::ReleasePlatformGoogleAndroid = OperationParam(TEXT("ANG"));
	const OperationParam OperationParam::ReleasePlatformWindowsPhone = OperationParam(TEXT("WINP"));
	const OperationParam OperationParam::ReleasePlatformWindows = OperationParam(TEXT("WINDOWS"));
	const OperationParam OperationParam::ReleasePlatformMac = OperationParam(TEXT("MAC"));
	const OperationParam OperationParam::ReleasePlatformLinux = OperationParam(TEXT("LINUX"));

	const OperationParam OperationParam::ScriptServiceRunScriptName = OperationParam(TEXT("scriptName"));
	const OperationParam OperationParam::ScriptServiceRunScriptData = OperationParam(TEXT("scriptData"));
	const OperationParam OperationParam::ScriptServiceStartDateUTC = OperationParam(TEXT("startDateUTC"));
	const OperationParam OperationParam::ScriptServiceStartMinutesFromNow = OperationParam(TEXT("minutesFromNow"));
	const OperationParam OperationParam::ScriptServiceJobId = OperationParam(TEXT("jobId"));

	const OperationParam OperationParam::MatchMakingServicePlayerRating = OperationParam(TEXT("playerRating"));
	const OperationParam OperationParam::MatchMakingServiceMinutes = OperationParam(TEXT("minutes"));
	const OperationParam OperationParam::MatchMakingServiceRangeDelta = OperationParam(TEXT("rangeDelta"));
	const OperationParam OperationParam::MatchMakingServiceNumMatches = OperationParam(TEXT("numMatches"));
	const OperationParam OperationParam::MatchMakingServiceExtraParams = OperationParam(TEXT("extraParms"));
	const OperationParam OperationParam::MatchMakingServiceAttributes = OperationParam(TEXT("attributes"));
	const OperationParam OperationParam::MatchMakingServicePlayerId = OperationParam(TEXT("playerId"));
	const OperationParam OperationParam::MatchMakingServicePlaybackStreamId = OperationParam(TEXT("playbackStreamId"));

	const OperationParam OperationParam::OneWayMatchServicePlayerId = OperationParam(TEXT("playerId"));
	const OperationParam OperationParam::OneWayMatchServiceRangeDelta = OperationParam(TEXT("rangeDelta"));
	const OperationParam OperationParam::OneWayMatchServicePlaybackStreamId = OperationParam(TEXT("playbackStreamId"));

	const OperationParam OperationParam::PlaybackStreamServicePlaybackStreamId = OperationParam(TEXT("playbackStreamId"));
	const OperationParam OperationParam::PlaybackStreamServiceTargetPlayerId = OperationParam(TEXT("targetPlayerId"));
	const OperationParam OperationParam::PlaybackStreamServiceInitiatingPlayerId = OperationParam(TEXT("initiatingPlayerId"));
	const OperationParam OperationParam::PlaybackStreamServiceIncludeSharedData = OperationParam(TEXT("includeSharedData"));
	const OperationParam OperationParam::PlaybackStreamServiceEventData = OperationParam(TEXT("eventData"));
	const OperationParam OperationParam::PlaybackStreamServiceSummary = OperationParam(TEXT("summary"));

	const OperationParam OperationParam::ProductServiceTransId = OperationParam(TEXT("transId"));
	const OperationParam OperationParam::ProductServiceLanguage = OperationParam(TEXT("language"));
	const OperationParam OperationParam::ProductServiceItemId = OperationParam(TEXT("itemId"));
	const OperationParam OperationParam::ProductServiceReceipt = OperationParam(TEXT("receipt"));
	const OperationParam OperationParam::ProductServiceOrderId = OperationParam(TEXT("orderId"));
	const OperationParam OperationParam::ProductServiceProductId = OperationParam(TEXT("productId"));
	const OperationParam OperationParam::ProductServiceToken = OperationParam(TEXT("token"));

	// S3 handling service params
	const OperationParam OperationParam::S3HandlingServiceCategory = OperationParam(TEXT("category"));
	const OperationParam OperationParam::S3HandlingServiceFileDetails = OperationParam(TEXT("fileDetails"));
	const OperationParam OperationParam::S3HandlingServiceFileId = OperationParam(TEXT("fileId"));

	// Shared Identity params
	const OperationParam OperationParam::AuthenticationServiceAuthenticationLevelName = OperationParam(TEXT("levelName"));
	const OperationParam OperationParam::ScriptServiceParentLevelName = OperationParam(TEXT("parentLevel"));
	const OperationParam OperationParam::PlayerStateServiceIncludeSummaryData = OperationParam(TEXT("includePlayerSummaryData"));
	const OperationParam OperationParam::IdentityServiceForceSingleton = OperationParam(TEXT("forceSingleton"));

	// Redemption Code
	const OperationParam OperationParam::RedemptionCodeServiceScanCode = OperationParam(TEXT("scanCode"));
	const OperationParam OperationParam::RedemptionCodeServiceCodeType = OperationParam(TEXT("codeType"));
	const OperationParam OperationParam::RedemptionCodeServiceCustomRedemptionInfo = OperationParam(TEXT("customRedemptionInfo"));

	// DataStream
	const OperationParam OperationParam::DataStreamEventName = OperationParam(TEXT("eventName"));
	const OperationParam OperationParam::DataStreamEventProperties = OperationParam(TEXT("eventProperties"));

	// Profanity
	const OperationParam OperationParam::ProfanityText = OperationParam(TEXT("text"));
	const OperationParam OperationParam::ProfanityReplaceSymbol = OperationParam(TEXT("replaceSymbol"));
	const OperationParam OperationParam::ProfanityFlagEmail = OperationParam(TEXT("flagEmail"));
	const OperationParam OperationParam::ProfanityFlagPhone = OperationParam(TEXT("flagPhone"));
	const OperationParam OperationParam::ProfanityFlagUrls = OperationParam(TEXT("flagUrls"));
	const OperationParam OperationParam::ProfanityLanguages = OperationParam(TEXT("languages"));

	// Upload
	const OperationParam OperationParam::UploadLocalPath = OperationParam(TEXT("localPath"));
	const OperationParam OperationParam::UploadCloudPath = OperationParam(TEXT("cloudPath"));
	const OperationParam OperationParam::UploadCloudFilename = OperationParam(TEXT("cloudFilename"));
	const OperationParam OperationParam::UploadShareable = OperationParam(TEXT("shareable"));
	const OperationParam OperationParam::UploadReplaceIfExists = OperationParam(TEXT("replaceIfExists"));
	const OperationParam OperationParam::UploadFileSize = OperationParam(TEXT("fileSize"));
	const OperationParam OperationParam::UploadRecurse = OperationParam(TEXT("recurse"));

	// Group
	const OperationParam OperationParam::GroupId = OperationParam(TEXT("groupId"));
	const OperationParam OperationParam::GroupProfileId = OperationParam(TEXT("profileId"));
	const OperationParam OperationParam::GroupRole = OperationParam(TEXT("role"));
	const OperationParam OperationParam::GroupAttributes = OperationParam(TEXT("attributes"));
	const OperationParam OperationParam::GroupName = OperationParam(TEXT("name"));
	const OperationParam OperationParam::GroupType = OperationParam(TEXT("groupType"));
	const OperationParam OperationParam::GroupIsOpenGroup = OperationParam(TEXT("isOpenGroup"));
	const OperationParam OperationParam::GroupAcl = OperationParam(TEXT("acl"));
	const OperationParam OperationParam::GroupData = OperationParam(TEXT("data"));
	const OperationParam OperationParam::GroupOwnerAttributes = OperationParam(TEXT("ownerAttributes"));
	const OperationParam OperationParam::GroupDefaultMemberAttributes = OperationParam(TEXT("defaultMemberAttributes"));
	const OperationParam OperationParam::GroupEntityType = OperationParam(TEXT("entityType"));
	const OperationParam OperationParam::GroupIsOwnedByGroupMember = OperationParam(TEXT("isOwnedByGroupMember"));
	const OperationParam OperationParam::GroupEntityId = OperationParam(TEXT("entityId"));
	const OperationParam OperationParam::GroupVersion = OperationParam(TEXT("version"));
	const OperationParam OperationParam::GroupContext = OperationParam(TEXT("context"));
	const OperationParam OperationParam::GroupPageOffset = OperationParam(TEXT("pageOffset"));
	const OperationParam OperationParam::GroupAutoJoinStrategy = OperationParam(TEXT("autoJoinStrategy"));
	const OperationParam OperationParam::GroupWhere = OperationParam(TEXT("where"));

	const OperationParam OperationParam::ProfileId = OperationParam(TEXT("profileId"));
	const OperationParam OperationParam::Subject = OperationParam(TEXT("subject"));
	const OperationParam OperationParam::Body = OperationParam(TEXT("body"));
	const OperationParam OperationParam::ServiceParams = OperationParam(TEXT("serviceParams"));

	const OperationParam OperationParam::LeaderboardId = OperationParam(TEXT("leaderboardId"));
	const OperationParam OperationParam::VersionId = OperationParam(TEXT("versionId"));
	const OperationParam OperationParam::TournamentCode = OperationParam(TEXT("tournamentCode"));
	const OperationParam OperationParam::InitialScore = OperationParam(TEXT("initialScore"));
	const OperationParam OperationParam::Score = OperationParam(TEXT("score"));
	const OperationParam OperationParam::RoundStartedEpoch = OperationParam(TEXT("roundStartedEpoch"));
	const OperationParam OperationParam::Data = OperationParam(TEXT("data"));

bool OperationParam::operator== (const OperationParam& s) const
{
    return _value == s.getValue();
}

void OperationParam::operator= (const OperationParam& s)
{
    _value = s.getValue();
}

bool OperationParam::isOptionalParamValid(const FString& param)
{
    return param.Len() > 0;
}