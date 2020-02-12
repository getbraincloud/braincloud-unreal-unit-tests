#include "braincloud/OperationParam.h"

namespace BrainCloud
{
	//Push Notification Service - Send Params
	const OperationParam OperationParam::PushNotificationSendParamToPlayerId = OperationParam("toPlayerId");
	const OperationParam OperationParam::PushNotificationSendParamMessage = OperationParam("message");
	const OperationParam OperationParam::PushNotificationSendParamNotificationTemplateId = OperationParam("notificationTemplateId");
	const OperationParam OperationParam::PushNotificationSendParamSubstitution = OperationParam("substitutions");
	const OperationParam OperationParam::AlertContent = OperationParam("alertContent");
	const OperationParam OperationParam::CustomData = OperationParam("customData");
	const OperationParam OperationParam::StartDateUTC = OperationParam("startDateUTC");
	const OperationParam OperationParam::MinutesFromNow = OperationParam("minutesFromNow");
	const OperationParam OperationParam::FcmContent = OperationParam("fcmContent");
	const OperationParam OperationParam::IosContent = OperationParam("iosContent");
	const OperationParam OperationParam::FacebookContent = OperationParam("facebookContent");

	//Push Notification Service - Register Params
	const OperationParam OperationParam::PushNotificationRegisterParamDeviceType = OperationParam("deviceType");
	const OperationParam OperationParam::PushNotificationRegisterParamDeviceToken = OperationParam("deviceToken");
	const OperationParam OperationParam::PushNotificationRegisterParamPushId = OperationParam("pushId");
	const OperationParam OperationParam::PushNotificationRegisterParamToPlayerId = OperationParam("toPlayerId");
	const OperationParam OperationParam::PushNotificationRegisterParamContent = OperationParam("content");
	const OperationParam OperationParam::PushNotificationRegisterParamSendInterval = OperationParam("sendInterval");
	const OperationParam OperationParam::PushNotificationRegisterParamScheduleIn = OperationParam("scheduleIn");

	// Twitter Service - Verify Params
	const OperationParam OperationParam::TwitterServiceVerifyToken = OperationParam("token");
	const OperationParam OperationParam::TwitterServiceVerifyVerifier = OperationParam("verifier");

	// Twitter Service - Tweet Params
	const OperationParam OperationParam::TwitterServiceTweetToken = OperationParam("token");
	const OperationParam OperationParam::TwitterServiceTweetSecret = OperationParam("secret");
	const OperationParam OperationParam::TwitterServiceTweetTweet = OperationParam("tweet");
	const OperationParam OperationParam::TwitterServiceTweetPic = OperationParam("pic");

	// Authenticate Service - Authenticate Params
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthenticationType = OperationParam("authenticationType");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthenticationToken = OperationParam("authenticationToken");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateExternalId = OperationParam("externalId");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateUniversalId = OperationParam("universalId");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateEmailAddress = OperationParam("emailAddress");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateServiceParams = OperationParam("serviceParams");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateExpiryInMin = OperationParam("tokenTtlInMinutes");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateGameId = OperationParam("gameId");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateDeviceId = OperationParam("deviceId");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateForceMergeFlag = OperationParam("forceMergeFlag");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateReleasePlatform = OperationParam("releasePlatform");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateGameVersion = OperationParam("gameVersion");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateBrainCloudVersion = OperationParam("clientLibVersion");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthFacebook = OperationParam("Facebook");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthEmail = OperationParam("Email");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthGameCenter = OperationParam("GameCenter");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthUniversal = OperationParam("Universal");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthSteam = OperationParam("Steam");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthGoogle = OperationParam("Google");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthParse = OperationParam("Parse");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthUpgradeId = OperationParam("upgradeAppId");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthAnonymous = OperationParam("Anonymous");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthExternal = OperationParam("External");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAnonymousId = OperationParam("anonymousId");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateProfileId = OperationParam("profileId");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateForceCreate = OperationParam("forceCreate");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateExternalAuthName = OperationParam("externalAuthName");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateRegion = OperationParam("region");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateCountryCode = OperationParam("countryCode");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateLanguageCode = OperationParam("languageCode");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateTimeZoneOffset = OperationParam("timeZoneOffset");
	const OperationParam OperationParam::AuthenticateServiceAuthenticateAuthTwitter = OperationParam("Twitter");

	// Authenticate Service - Authenticate Params
	const OperationParam OperationParam::IdentityServiceExternalId = OperationParam("externalId");
	const OperationParam OperationParam::IdentityServiceAuthenticationType = OperationParam("authenticationType");
	const OperationParam OperationParam::IdentityServiceConfirmAnonymous = OperationParam("confirmAnonymous");
	const OperationParam OperationParam::Peer = OperationParam("peer");

	// Async Match Service - Async Match Params
	const OperationParam OperationParam::AsyncMatchServicePlayers = OperationParam("players");
	const OperationParam OperationParam::AsyncMatchServiceMatchState = OperationParam("matchState");
	const OperationParam OperationParam::AsyncMatchServiceMatchId = OperationParam("matchId");
	const OperationParam OperationParam::AsyncMatchServiceCurrentPlayer = OperationParam("currentPlayer");
	const OperationParam OperationParam::AsyncMatchServiceMatchSummary = OperationParam("summary");
	const OperationParam OperationParam::AsyncMatchServicePushMessage = OperationParam("pushContent");
	const OperationParam OperationParam::AsyncMatchServiceOwnerId = OperationParam("ownerId");
	const OperationParam OperationParam::AsyncMatchServiceVersion = OperationParam("version");
	const OperationParam OperationParam::AsyncMatchServiceStatistics = OperationParam("statistics");
	const OperationParam OperationParam::AsyncMatchServiceMatchStatus = OperationParam("status");

	// Entity Service
	const OperationParam OperationParam::EntityServiceEntityId = OperationParam("entityId");
	const OperationParam OperationParam::EntityServiceEntityType = OperationParam("entityType");
	const OperationParam OperationParam::EntityServiceEntitySubtype = OperationParam("entitySubtype");
	const OperationParam OperationParam::EntityServiceData = OperationParam("data");
	const OperationParam OperationParam::EntityServiceAcl = OperationParam("acl");
	const OperationParam OperationParam::EntityServiceVersion = OperationParam("version");
	const OperationParam OperationParam::EntityServiceFriendData = OperationParam("friendData");
	const OperationParam OperationParam::EntityServiceTargetPlayerId = OperationParam("targetPlayerId");
	const OperationParam OperationParam::EntityServiceUpdateOps = OperationParam("updateOps");

	// Global Entity Service - Params
	const OperationParam OperationParam::GlobalEntityServiceEntityId = OperationParam("entityId");
	const OperationParam OperationParam::GlobalEntityServiceEntityType = OperationParam("entityType");
	const OperationParam OperationParam::GlobalEntityServiceIndexedId = OperationParam("entityIndexedId");
	const OperationParam OperationParam::GlobalEntityServiceTimeToLive = OperationParam("timeToLive");
	const OperationParam OperationParam::GlobalEntityServiceData = OperationParam("data");
	const OperationParam OperationParam::GlobalEntityServiceAcl = OperationParam("acl");
	const OperationParam OperationParam::GlobalEntityServiceVersion = OperationParam("version");
	const OperationParam OperationParam::GlobalEntityServiceMaxReturn = OperationParam("maxReturn");
	const OperationParam OperationParam::GlobalEntityServiceWhere = OperationParam("where");
	const OperationParam OperationParam::GlobalEntityServiceOrderBy = OperationParam("orderBy");
	const OperationParam OperationParam::GlobalEntityServiceContext = OperationParam("context");
	const OperationParam OperationParam::GlobalEntityServicePageOffset = OperationParam("pageOffset");
	const OperationParam OperationParam::OwnerId = OperationParam("ownerId");

	// Event Service - Send Params
	const OperationParam OperationParam::EventServiceSendToId = OperationParam("toId");
	const OperationParam OperationParam::EventServiceSendEventType = OperationParam("eventType");
	const OperationParam OperationParam::EventServiceSendEventId = OperationParam("eventId");
	const OperationParam OperationParam::EventServiceSendEventData = OperationParam("eventData");
	const OperationParam OperationParam::EventServiceSendRecordLocally = OperationParam("recordLocally");

	// Event Service - Update Event Data Params
	const OperationParam OperationParam::EventServiceUpdateEventDataFromId = OperationParam("fromId");
	const OperationParam OperationParam::EventServiceUpdateEventDataEventId = OperationParam("eventId");
	const OperationParam OperationParam::EventServiceUpdateEventDataData = OperationParam("eventData");
	const OperationParam OperationParam::EvId = OperationParam("evId");

	// Event Service - Delete Incoming Params
	const OperationParam OperationParam::EventServiceDeleteIncomingEventId = OperationParam("eventId");
	const OperationParam OperationParam::EventServiceDeleteIncomingFromId = OperationParam("fromId");

	// Event Service - Delete Sent Params
	const OperationParam OperationParam::EventServiceDeleteSentEventId = OperationParam("eventId");
	const OperationParam OperationParam::EventServiceDeleteSentToId = OperationParam("toId");
	const OperationParam OperationParam::EventServiceIncludeIncomingEvents = OperationParam("includeIncomingEvents");
	const OperationParam OperationParam::EventServiceIncludeSentEvents = OperationParam("includeSentEvents");

	// Friend Service - Params
	const OperationParam OperationParam::FriendServiceAuthenticationType = OperationParam("authenticationType");
	const OperationParam OperationParam::FriendServiceEntityId = OperationParam("entityId");
	const OperationParam OperationParam::FriendServiceExternalId = OperationParam("externalId");
	const OperationParam OperationParam::FriendServiceProfileId = OperationParam("profileId");
	const OperationParam OperationParam::FriendServiceFriendId = OperationParam("friendId");
	const OperationParam OperationParam::FriendServiceEntityType = OperationParam("entityType");
	const OperationParam OperationParam::FriendServiceEntitySubType = OperationParam("entitySubtype");
	const OperationParam OperationParam::FriendServiceIncludeSummaryData = OperationParam("includeSummaryData");
	const OperationParam OperationParam::FriendServiceReadPlayerStateFriendId = OperationParam("friendId");
	const OperationParam OperationParam::FriendServiceSearchText = OperationParam("searchText");
	const OperationParam OperationParam::FriendServiceMaxResults = OperationParam("maxResults");
	const OperationParam OperationParam::FriendServiceFriendPlatform = OperationParam("friendPlatform");
	const OperationParam OperationParam::FriendServiceProfileIds = OperationParam("profileIds");
	const OperationParam OperationParam::ExternalAuthType = OperationParam("externalAuthType");

	//Achievements Event Data Params
	const OperationParam OperationParam::GamificationServiceAchievementsName = OperationParam("achievements");
	const OperationParam OperationParam::GamificationServiceAchievementsData = OperationParam("data");
	const OperationParam OperationParam::GamificationServiceAchievementsGranted = OperationParam("achievementsGranted");
	const OperationParam OperationParam::GamificationServiceCategory = OperationParam("category");
	const OperationParam OperationParam::GamificationServiceIncludeMetaData = OperationParam("includeMetaData");
	const OperationParam OperationParam::GamificationServiceMilestonesName = OperationParam("milestones");

	// Player Statistics Event Params
	const OperationParam OperationParam::PlayerStatisticEventServiceEventName = OperationParam("eventName");
	const OperationParam OperationParam::PlayerStatisticEventServiceEventMultiplier = OperationParam("eventMultiplier");
	const OperationParam OperationParam::PlayerStatisticEventServiceEvents = OperationParam("events");

	// Player State Service - Read Params
	const OperationParam OperationParam::PlayerStateServiceReadEntitySubtype = OperationParam("entitySubType");

	// Player State Service - Update Summary Params
	const OperationParam OperationParam::PlayerStateServiceUpdateSummaryFriendData = OperationParam("summaryFriendData");

	// Player State Service - Update Name Params
	const OperationParam OperationParam::PlayerStateServiceUpdateNameData = OperationParam("playerName");

	// Player State Service - Atributes
	const OperationParam OperationParam::PlayerStateServiceAttributes = OperationParam("attributes");
	const OperationParam OperationParam::PlayerStateServiceWipeExisting = OperationParam("wipeExisting");

	// Player State Service - Atributes
	const OperationParam OperationParam::PlayerStateServicePictureUrl = OperationParam("playerPictureUrl");
	const OperationParam OperationParam::PlayerStateServiceContactEmail = OperationParam("contactEmail");

	const OperationParam OperationParam::PlayerStateServiceTimeZoneOffset= OperationParam("timeZoneOffset");
	const OperationParam OperationParam::PlayerStateServiceLanguageCode = OperationParam("languageCode");

	// Player Statistics Service - Update Increment Params
	const OperationParam OperationParam::PlayerStatisticsServiceStats = OperationParam("statistics");
	const OperationParam OperationParam::PlayerStatisticsServiceStatNames = OperationParam("statNames");
	const OperationParam OperationParam::PlayerStatisticsExperiencePoints = OperationParam("xp_points");

	// Player Statistics Service - Read Params
	const OperationParam OperationParam::PlayerStatisticsServiceReadEntitySubType = OperationParam("entitySubType");

	// Social Leaderboard Service - Get Leaderboard Params
	const OperationParam OperationParam::SocialLeaderboardServiceLeaderboardId = OperationParam("leaderboardId");
	const OperationParam OperationParam::SocialLeaderboardServiceLeaderboardIds = OperationParam("leaderboardIds");
	const OperationParam OperationParam::SocialLeaderboardServiceReplaceName = OperationParam("replaceName");
	const OperationParam OperationParam::SocialLeaderboardServiceScore = OperationParam("score");
	const OperationParam OperationParam::SocialLeaderboardServiceData = OperationParam("data");
	const OperationParam OperationParam::SocialLeaderboardServiceEventName = OperationParam("eventName");
	const OperationParam OperationParam::SocialLeaderboardServiceEventMultiplier = OperationParam("eventMultiplier");
	const OperationParam OperationParam::SocialLeaderboardServiceLeaderboardType = OperationParam("leaderboardType");
	const OperationParam OperationParam::SocialLeaderboardServiceRotationType = OperationParam("rotationType");
	const OperationParam OperationParam::SocialLeaderboardServiceRotationReset = OperationParam("rotationReset");
	const OperationParam OperationParam::SocialLeaderboardServiceRotationResetTime = OperationParam("rotationResetTime");
	const OperationParam OperationParam::SocialLeaderboardServiceRetainedCount = OperationParam("retainedCount");
	const OperationParam OperationParam::NumDaysToRotate = OperationParam("numDaysToRotate");
	const OperationParam OperationParam::SocialLeaderboardServiceFetchType = OperationParam("fetchType");
	const OperationParam OperationParam::SocialLeaderboardServiceSortOrder = OperationParam("sort");
	const OperationParam OperationParam::SocialLeaderboardServiceMaxResults = OperationParam("maxResults");
	const OperationParam OperationParam::SocialLeaderboardServiceStartIndex = OperationParam("startIndex");
	const OperationParam OperationParam::SocialLeaderboardServiceEndIndex = OperationParam("endIndex");
	const OperationParam OperationParam::SocialLeaderboardServiceBeforeCount = OperationParam("beforeCount");
	const OperationParam OperationParam::SocialLeaderboardServiceAfterCount = OperationParam("afterCount");
	const OperationParam OperationParam::SocialLeaderboardServiceIncludeLeaderboardSize = OperationParam("includeLeaderboardSize");
	const OperationParam OperationParam::SocialLeaderboardServiceVersionId = OperationParam("versionId");
	const OperationParam OperationParam::SocialLeaderboardServiceLeaderboardResultCount = OperationParam("leaderboardResultCount");
	const OperationParam OperationParam::ProfileIds = OperationParam("profileIds");


	// Product service
	const OperationParam OperationParam::ProductServiceVCId = OperationParam("vc_id");
	const OperationParam OperationParam::ProductServiceVCAmount = OperationParam("vc_amount");

	// Currency service
	const OperationParam OperationParam::VirtualCurrencyServiceVCId = OperationParam("vcId");
	const OperationParam OperationParam::VirtualCurrencyServiceLevelName = OperationParam("levelName");
	const OperationParam OperationParam::VirtualCurrencyServicePeerCode = OperationParam("peerCode");
	const OperationParam OperationParam::VirtualCurrencyServiceAmount = OperationParam("vcAmount");

	// Product Service - Get Inventory Params
	const OperationParam OperationParam::ProductServiceGetInventoryPlatform = OperationParam("platform");
	const OperationParam OperationParam::ProductServiceGetInventoryUserCurrency = OperationParam("user_currency");
	const OperationParam OperationParam::ProductServiceGetInventoryCategory = OperationParam("category");

	// Product Service - Op Cash In Receipt Params
	const OperationParam OperationParam::ProductServiceOpCashInReceiptReceipt = OperationParam("receipt");
	const OperationParam OperationParam::ProductServiceOpCashInReceiptUrl = OperationParam("url");

	// Server Time Service - Read Params
	const OperationParam OperationParam::ServerTimeServiceRead = OperationParam("");

	// data creation parms
	const OperationParam OperationParam::ServiceMessageService = OperationParam("service");
	const OperationParam OperationParam::ServiceMessageOperation = OperationParam("operation");
	const OperationParam OperationParam::ServiceMessageData = OperationParam("data");

	// data bundle creation parms
	const OperationParam OperationParam::ServiceMessagePacketId = OperationParam("packetId");
	const OperationParam OperationParam::ProfileId = OperationParam("profileId");
	const OperationParam OperationParam::ServiceMessageSessionId = OperationParam("sessionId");
	const OperationParam OperationParam::ServiceMessageMessages = OperationParam("messages");

	// Error Params
	const OperationParam OperationParam::ServiceMessageReasonCode = OperationParam("reasoncode");
	const OperationParam OperationParam::ServiceMessageStatusMessage = OperationParam("statusmessage");

	const OperationParam OperationParam::ScriptServiceRunScriptName = OperationParam("scriptName");
	const OperationParam OperationParam::ScriptServiceRunScriptData = OperationParam("scriptData");
	const OperationParam OperationParam::ScriptServiceStartDateUTC = OperationParam("startDateUTC");
	const OperationParam OperationParam::ScriptServiceStartMinutesFromNow = OperationParam("minutesFromNow");
	const OperationParam OperationParam::ScriptServiceJobId = OperationParam("jobId");

	const OperationParam OperationParam::MatchMakingServicePlayerRating = OperationParam("playerRating");
	const OperationParam OperationParam::MatchMakingServiceMinutes = OperationParam("minutes");
	const OperationParam OperationParam::MatchMakingServiceRangeDelta = OperationParam("rangeDelta");
	const OperationParam OperationParam::MatchMakingServiceNumMatches = OperationParam("numMatches");
	const OperationParam OperationParam::MatchMakingServiceExtraParams = OperationParam("extraParms");
	const OperationParam OperationParam::MatchMakingServiceAttributes = OperationParam("attributes");
	const OperationParam OperationParam::MatchMakingServicePlayerId = OperationParam("playerId");
	const OperationParam OperationParam::MatchMakingServicePlaybackStreamId = OperationParam("playbackStreamId");

	const OperationParam OperationParam::OneWayMatchServicePlayerId = OperationParam("playerId");
	const OperationParam OperationParam::OneWayMatchServiceRangeDelta = OperationParam("rangeDelta");
	const OperationParam OperationParam::OneWayMatchServicePlaybackStreamId = OperationParam("playbackStreamId");

	const OperationParam OperationParam::PlaybackStreamServicePlaybackStreamId = OperationParam("playbackStreamId");
	const OperationParam OperationParam::PlaybackStreamServiceTargetPlayerId = OperationParam("targetPlayerId");
	const OperationParam OperationParam::PlaybackMaxNumberOfStreams = OperationParam("maxNumStreams");
	const OperationParam OperationParam::PlaybackStreamServiceInitiatingPlayerId = OperationParam("initiatingPlayerId");
	const OperationParam OperationParam::PlaybackStreamServiceIncludeSharedData = OperationParam("includeSharedData");
	const OperationParam OperationParam::PlaybackStreamServiceEventData = OperationParam("eventData");
	const OperationParam OperationParam::PlaybackStreamServiceSummary = OperationParam("summary");

	const OperationParam OperationParam::ProductServiceTransId = OperationParam("transId");
	const OperationParam OperationParam::ProductServiceLanguage = OperationParam("language");
	const OperationParam OperationParam::ProductServiceItemId = OperationParam("itemId");
	const OperationParam OperationParam::ProductServiceReceipt = OperationParam("receipt");
	const OperationParam OperationParam::ProductServiceOrderId = OperationParam("orderId");
	const OperationParam OperationParam::ProductServiceProductId = OperationParam("productId");
	const OperationParam OperationParam::ProductServiceToken = OperationParam("token");

	// S3 handling service params
	const OperationParam OperationParam::S3HandlingServiceCategory = OperationParam("category");
	const OperationParam OperationParam::S3HandlingServiceFileDetails = OperationParam("fileDetails");
	const OperationParam OperationParam::S3HandlingServiceFileId = OperationParam("fileId");

	// Shared Identity params
	const OperationParam OperationParam::AuthenticationServiceAuthenticationLevelName = OperationParam("levelName");
	const OperationParam OperationParam::ScriptServiceParentLevelName = OperationParam("parentLevel");
	const OperationParam OperationParam::PlayerStateServiceIncludeSummaryData = OperationParam("includePlayerSummaryData");
	const OperationParam OperationParam::IdentityServiceForceSingleton = OperationParam("forceSingleton");

	// Redemption Code
	const OperationParam OperationParam::RedemptionCodeServiceScanCode = OperationParam("scanCode");
	const OperationParam OperationParam::RedemptionCodeServiceCodeType = OperationParam("codeType");
	const OperationParam OperationParam::RedemptionCodeServiceCustomRedemptionInfo = OperationParam("customRedemptionInfo");

	// DataStream
	const OperationParam OperationParam::DataStreamEventName = OperationParam("eventName");
	const OperationParam OperationParam::DataStreamEventProperties = OperationParam("eventProperties");

	// Profanity
	const OperationParam OperationParam::ProfanityText = OperationParam("text");
	const OperationParam OperationParam::ProfanityReplaceSymbol = OperationParam("replaceSymbol");
	const OperationParam OperationParam::ProfanityFlagEmail = OperationParam("flagEmail");
	const OperationParam OperationParam::ProfanityFlagPhone = OperationParam("flagPhone");
	const OperationParam OperationParam::ProfanityFlagUrls = OperationParam("flagUrls");
	const OperationParam OperationParam::ProfanityLanguages = OperationParam("languages");

	// Upload
	const OperationParam OperationParam::UploadLocalPath = OperationParam("localPath");
	const OperationParam OperationParam::UploadCloudPath = OperationParam("cloudPath");
	const OperationParam OperationParam::UploadCloudFilename = OperationParam("cloudFilename");
	const OperationParam OperationParam::UploadShareable = OperationParam("shareable");
	const OperationParam OperationParam::UploadReplaceIfExists = OperationParam("replaceIfExists");
	const OperationParam OperationParam::UploadFileSize = OperationParam("fileSize");
	const OperationParam OperationParam::UploadRecurse = OperationParam("recurse");

	// Group
	const OperationParam OperationParam::GroupId = OperationParam("groupId");
	const OperationParam OperationParam::GroupProfileId = OperationParam("profileId");
	const OperationParam OperationParam::GroupRole = OperationParam("role");
	const OperationParam OperationParam::GroupAttributes = OperationParam("attributes");
	const OperationParam OperationParam::GroupName = OperationParam("name");
	const OperationParam OperationParam::GroupType = OperationParam("groupType");
	const OperationParam OperationParam::GroupTypes = OperationParam("groupTypes");
	const OperationParam OperationParam::GroupIsOpenGroup = OperationParam("isOpenGroup");
	const OperationParam OperationParam::GroupAcl = OperationParam("acl");
	const OperationParam OperationParam::GroupData = OperationParam("data");
	const OperationParam OperationParam::GroupOwnerAttributes = OperationParam("ownerAttributes");
	const OperationParam OperationParam::GroupDefaultMemberAttributes = OperationParam("defaultMemberAttributes");
	const OperationParam OperationParam::GroupEntityType = OperationParam("entityType");
	const OperationParam OperationParam::GroupIsOwnedByGroupMember = OperationParam("isOwnedByGroupMember");
	const OperationParam OperationParam::GroupEntityId = OperationParam("entityId");
	const OperationParam OperationParam::GroupVersion = OperationParam("version");
	const OperationParam OperationParam::GroupContext = OperationParam("context");
	const OperationParam OperationParam::GroupPageOffset = OperationParam("pageOffset");
	const OperationParam OperationParam::GroupAutoJoinStrategy = OperationParam("autoJoinStrategy");
	const OperationParam OperationParam::GroupWhere = OperationParam("where");
	const OperationParam OperationParam::GroupSummaryData = OperationParam("summaryData");


	//change mail
	const OperationParam OperationParam::OldEmailAddress = OperationParam("oldEmailAddress");
	const OperationParam OperationParam::NewEmailAddress = OperationParam("newEmailAddress");
	const OperationParam OperationParam::UpdateContactEmail = OperationParam("updateContactEmail");
	const OperationParam OperationParam::FieldAuthenticationToken = OperationParam("authenticationToken");


	//mail
	const OperationParam OperationParam::EmailAddress = OperationParam("emailAddress");
	const OperationParam OperationParam::Subject = OperationParam("subject");
	const OperationParam OperationParam::Body = OperationParam("body");
	const OperationParam OperationParam::ServiceParams = OperationParam("serviceParams");

	const OperationParam OperationParam::LeaderboardId = OperationParam("leaderboardId");
	const OperationParam OperationParam::DivSetID = OperationParam("divSetId");
	const OperationParam OperationParam::VersionId = OperationParam("versionId");
	const OperationParam OperationParam::TournamentCode = OperationParam("tournamentCode");
	const OperationParam OperationParam::InitialScore = OperationParam("initialScore");
	const OperationParam OperationParam::Score = OperationParam("score");
	const OperationParam OperationParam::RoundStartedEpoch = OperationParam("roundStartedEpoch");
	const OperationParam OperationParam::Data = OperationParam("data");

	//customEntity
	const OperationParam OperationParam::CustomEntityServiceEntityType = OperationParam("entityType");
	const OperationParam OperationParam::CustomEntityServiceData = OperationParam("entityData");
	const OperationParam OperationParam::CustomEntityServiceAcl = OperationParam("entityAcl");
	const OperationParam OperationParam::CustomEntityServiceTimeToLive = OperationParam("timeToLive");
	const OperationParam OperationParam::CustomEntityServiceIsOwned = OperationParam("isOwned");
	const OperationParam OperationParam::CustomEntityServiceVersion =OperationParam("version"); 
	const OperationParam OperationParam::CustomEntityServiceRowsPerPage= OperationParam("rowsPerPage");
	const OperationParam OperationParam::CustomEntityServiceSearchJson = OperationParam("searchJson");
	const OperationParam OperationParam::CustomEntityServiceSortJson = OperationParam("sortJson");
	const OperationParam OperationParam::CustomEntityServiceDoCount = OperationParam("doCount");
	const OperationParam OperationParam::CustomEntityServiceContext = OperationParam("context");
	const OperationParam OperationParam::CustomEntityServicePageOffset = OperationParam("pageOffset");
	const OperationParam OperationParam::CustomEntityServiceEntityId = OperationParam("entityId");
	const OperationParam OperationParam::CustomEntityFieldsJson = OperationParam("fieldsJson");

	//chat
	const OperationParam OperationParam::ChannelId = OperationParam("channelId");
	const OperationParam OperationParam::MsgId = OperationParam("msgId");
	const OperationParam OperationParam::Version = OperationParam("version");
	const OperationParam OperationParam::ChannelType = OperationParam("channelType");
	const OperationParam OperationParam::ChannelSubId = OperationParam("channelSubId");
	const OperationParam OperationParam::MaxReturn = OperationParam("maxReturn");
	const OperationParam OperationParam::Content = OperationParam("content");
	const OperationParam OperationParam::RecordInHistory = OperationParam("recordInHistory");
	const OperationParam OperationParam::Text = OperationParam("text");

	//lobby
	const OperationParam OperationParam::LobbyType = OperationParam("lobbyType");
	const OperationParam OperationParam::LobbyTypes = OperationParam("lobbyTypes");
	const OperationParam OperationParam::Rating = OperationParam("rating");
	const OperationParam OperationParam::OtherUserCxIds = OperationParam("otherUserCxIds");
	const OperationParam OperationParam::IsReady = OperationParam("isReady");
	const OperationParam OperationParam::ExtraJson = OperationParam("extraJson");
	const OperationParam OperationParam::TeamCode = OperationParam("teamCode");
	const OperationParam OperationParam::Settings = OperationParam("settings");
	const OperationParam OperationParam::MaxSteps = OperationParam("maxSteps");
	const OperationParam OperationParam::Algo = OperationParam("algo");
	const OperationParam OperationParam::Filter = OperationParam("filter");
	const OperationParam OperationParam::LobbyId = OperationParam("lobbyId");
	const OperationParam OperationParam::CxId = OperationParam("cxId");
	const OperationParam OperationParam::SignalData = OperationParam("signalData");
	const OperationParam OperationParam::ToTeamCode = OperationParam("toTeamCode");
	const OperationParam OperationParam::PingData = OperationParam("pingData");

	//messaging
	const OperationParam OperationParam::MessagingMsgbox = OperationParam("msgbox");
	const OperationParam OperationParam::MessagingMsgIds = OperationParam("msgIds");
	const OperationParam OperationParam::MessagingMarkAsRead = OperationParam("markAsRead");
	const OperationParam OperationParam::MessagingContext = OperationParam("context");
	const OperationParam OperationParam::MessagingPageOffset = OperationParam("pageOffset");
	const OperationParam OperationParam::MessagingToProfileIds = OperationParam("toProfileIds");
	const OperationParam OperationParam::MessagingText = OperationParam("text");
	const OperationParam OperationParam::MessagingSubject = OperationParam("subject");
	const OperationParam OperationParam::MessagingContentJson = OperationParam("contentJson");

	//presence
	const OperationParam OperationParam::PresencePlatform = OperationParam("platform");
	const OperationParam OperationParam::PresenceIncludeOffline = OperationParam("includeOffline");
	const OperationParam OperationParam::PresenceGroupId = OperationParam("groupId");
	const OperationParam OperationParam::PresenceProfileIds = OperationParam("profileIds");
	const OperationParam OperationParam::PresenceBidirectional = OperationParam("bidirectional");
	const OperationParam OperationParam::PresenceVisible = OperationParam("visible");
	const OperationParam OperationParam::PresenceActivity = OperationParam("activity");

	//appstore
	const OperationParam OperationParam::AppStoreStoreId = OperationParam("storeId");
	const OperationParam OperationParam::AppStoreReceiptData = OperationParam("receiptData");
	const OperationParam OperationParam::AppStorePriceInfoCriteria = OperationParam("priceInfoCriteria");
	const OperationParam OperationParam::AppStoreUserCurrency = OperationParam("userCurrency");
	const OperationParam OperationParam::AppStoreCategory = OperationParam("category");
	const OperationParam OperationParam::AppStorePurchaseData = OperationParam("purchaseData");
	const OperationParam OperationParam::AppStoreTransactionId = OperationParam("transactionId");
	const OperationParam OperationParam::AppStoreTransactionData = OperationParam("transactionData");

	//item catalog
	const OperationParam OperationParam::ItemCatalogServiceDefId = OperationParam("defId");
	const OperationParam OperationParam::ItemCatalogServiceContext = OperationParam("context");
	const OperationParam OperationParam::ItemCatalogServicePageOffset = OperationParam("pageOffset");
	//UserItems
  
	const OperationParam OperationParam::UserItemsServiceDefId = OperationParam("defId");
	const OperationParam OperationParam::UserItemsServiceQuantity = OperationParam("quantity");
	const OperationParam OperationParam::UserItemsServiceIncludeDef = OperationParam("includeDef");
	const OperationParam OperationParam::UserItemsServiceItemId = OperationParam("itemId");
	const OperationParam OperationParam::UserItemsServiceCriteria = OperationParam("criteria");
	const OperationParam OperationParam::UserItemsServiceContext = OperationParam("context");
	const OperationParam OperationParam::UserItemsServicePageOffset = OperationParam("pageOffset");
	const OperationParam OperationParam::UserItemsServiceVersion = OperationParam("version");
	const OperationParam OperationParam::UserItemsServiceImmediate = OperationParam("immediate");
	const OperationParam OperationParam::UserItemsServiceProfileId = OperationParam("profileId");
	const OperationParam OperationParam::UserItemsServiceShopId = OperationParam("shopId");
	const OperationParam OperationParam::UserItemsServiceNewItemData = OperationParam("newItemData");

	//Datastream
	const OperationParam OperationParam::DataStreamCrashType = OperationParam("crashType");
	const OperationParam OperationParam::DataStreamErrorMsg = OperationParam("errorMsg");
	const OperationParam OperationParam::DataStreamCrashJson = OperationParam("crashJson");
	const OperationParam OperationParam::DataStreamCrashLog = OperationParam("crashLog");
	const OperationParam OperationParam::DataStreamUsername = OperationParam("playerName");
	const OperationParam OperationParam::DataStreamUserEmail = OperationParam("userEmail");
	const OperationParam OperationParam::DataStreamUserNotes = OperationParam("userNotes");
	const OperationParam OperationParam::DataStreamUserSubmitted = OperationParam("userSubmitted");

	const OperationParam OperationParam::PlayerStateServiceStatusName = OperationParam("statusName");
	const OperationParam OperationParam::PlayerStateServiceAdditionalSecs = OperationParam("additionalSecs");
	const OperationParam OperationParam::PlayerStateServiceDetails = OperationParam("details");
	const OperationParam OperationParam::PlayerStateServiceDurationSecs = OperationParam("durationSecs");

	const OperationParam OperationParam::IdentityServiceBlockchainConfig = OperationParam("blockchainConfig");
	const OperationParam OperationParam::IdentityServicePublicKey = OperationParam("publicKey");

	OperationParam::OperationParam(const char * value)
	{
		_value = value;
	}

	bool OperationParam::operator== (const OperationParam& s) const
	{
		return _value == s.getValue();
	}
	void OperationParam::operator= (const OperationParam& s)
	{
		_value = s.getValue();
	}
}