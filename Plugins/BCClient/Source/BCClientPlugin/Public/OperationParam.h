// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BCCLIENTPLUGIN_API OperationParam
{
  public:
	static const OperationParam Authenticate;

	//Push Notification Service - Send Params
	static const OperationParam PushNotificationSendParamToPlayerId;
	static const OperationParam PushNotificationSendParamProfileId;
	static const OperationParam PushNotificationSendParamNotificationTemplateId;
	static const OperationParam PushNotificationSendParamMessage;
	static const OperationParam PushNotificationSendParamSubstitution;
	static const OperationParam AlertContent;
	static const OperationParam CustomData;
	static const OperationParam StartTimeUTC;
	static const OperationParam MinutesFromNow;
	static const OperationParam FcmContent;
	static const OperationParam IosContent;
	static const OperationParam FacebookContent;

	//Push Notification Service - Register Params
	static const OperationParam PushNotificationRegisterParamDeviceType;
	static const OperationParam PushNotificationRegisterParamDeviceToken;
	static const OperationParam PushNotificationRegisterParamPushId;
	static const OperationParam PushNotificationRegisterParamToPlayerId;
	static const OperationParam PushNotificationRegisterParamContent;
	static const OperationParam PushNotificationRegisterParamSendInterval;
	static const OperationParam PushNotificationRegisterParamScheduleIn;

	// Twitter Service - Verify Params
	static const OperationParam TwitterServiceVerifyToken;
	static const OperationParam TwitterServiceVerifyVerifier;

	// Twitter Service - Tweet Params
	static const OperationParam TwitterServiceTweetToken;
	static const OperationParam TwitterServiceTweetSecret;
	static const OperationParam TwitterServiceTweetTweet;
	static const OperationParam TwitterServiceTweetPic;

	// Authenticate Service - Authenticate Params
	static const OperationParam AuthenticateServiceAuthenticateAuthenticationType;
	static const OperationParam AuthenticateServiceAuthenticateAuthenticationToken;
	static const OperationParam AuthenticateServiceAuthenticateExternalId;
	static const OperationParam AuthenticateServiceAuthenticateGameId;
	static const OperationParam AuthenticateServiceAuthenticateDeviceId;
	static const OperationParam AuthenticateServiceAuthenticateForceMergeFlag;
	static const OperationParam AuthenticateServiceAuthenticateReleasePlatform;
	static const OperationParam AuthenticateServiceAuthenticateGameVersion;
	static const OperationParam AuthenticateServiceAuthenticateBrainCloudVersion;
	static const OperationParam AuthenticateServiceAuthenticateAuthFacebook;
	static const OperationParam AuthenticateServiceAuthenticateAuthEmail;
	static const OperationParam AuthenticateServiceAuthenticateAuthGameCenter;
	static const OperationParam AuthenticateServiceAuthenticateAuthUniversal;
	static const OperationParam AuthenticateServiceAuthenticateAuthSteam;
	static const OperationParam AuthenticateServiceAuthenticateAuthGoogle;
	static const OperationParam AuthenticateServiceAuthenticateAuthParse;
	static const OperationParam AuthenticateServiceAuthenticateAuthExternal;

	static const OperationParam AuthenticateServiceAuthenticateAuthUpgradeId;
	static const OperationParam AuthenticateServiceAuthenticateAuthAnonymous;
	static const OperationParam AuthenticateServiceAuthenticateAnonymousId;
	static const OperationParam AuthenticateServiceAuthenticateProfileId;
	static const OperationParam AuthenticateServiceAuthenticateForceCreate;
	static const OperationParam AuthenticateServiceAuthenticateExternalAuthName;
	static const OperationParam AuthenticateServiceAuthenticateRegion;
	static const OperationParam AuthenticateServiceAuthenticateCountryCode;
	static const OperationParam AuthenticateServiceAuthenticateLanguageCode;
	static const OperationParam AuthenticateServiceAuthenticateTimeZoneOffset;
	static const OperationParam AuthenticateServiceAuthenticateAuthTwitter;
	static const OperationParam Peer;

	// Authenticate Service - Authenticate Params
	static const OperationParam IdentityServiceExternalId;
	static const OperationParam IdentityServiceAuthenticationType;
	static const OperationParam IdentityServiceConfirmAnonymous;

	static const OperationParam IdentityServiceOldEmailAddress;
	static const OperationParam IdentityServiceNewEmailAddress;
	static const OperationParam IdentityServiceUpdateContactEmail;

	// Async Match Service - Async Match Params
	static const OperationParam AsyncMatchServicePlayers;
	static const OperationParam AsyncMatchServiceMatchState;
	static const OperationParam AsyncMatchServiceMatchId;
	static const OperationParam AsyncMatchServiceCurrentPlayer;
	static const OperationParam AsyncMatchServiceMatchSummary;
	static const OperationParam AsyncMatchServicePushMessage;
	static const OperationParam AsyncMatchServiceOwnerId;
	static const OperationParam AsyncMatchServiceVersion;
	static const OperationParam AsyncMatchServiceStatistics;
	static const OperationParam AsyncMatchServiceMatchStatus;

	// Entity Service
	static const OperationParam EntityServiceEntityId;
	static const OperationParam EntityServiceEntityType;
	static const OperationParam EntityServiceEntitySubtype;
	static const OperationParam EntityServiceData;
	static const OperationParam EntityServiceAcl;
	static const OperationParam EntityServiceVersion;
	static const OperationParam EntityServiceFriendData;
	static const OperationParam EntityServiceTargetPlayerId;
	static const OperationParam EntityServiceUpdateOps;

	// Global Entity Service - Params
	static const OperationParam GlobalEntityServiceEntityId;
	static const OperationParam GlobalEntityServiceEntityType;
	static const OperationParam GlobalEntityServiceIndexedId;
	static const OperationParam GlobalEntityServiceTimeToLive;
	static const OperationParam GlobalEntityServiceData;
	static const OperationParam GlobalEntityServiceAcl;
	static const OperationParam GlobalEntityServiceVersion;
	static const OperationParam GlobalEntityServiceMaxReturn;
	static const OperationParam GlobalEntityServiceWhere;
	static const OperationParam GlobalEntityServiceOrderBy;
	static const OperationParam GlobalEntityServiceContext;
	static const OperationParam GlobalEntityServicePageOffset;
	static const OperationParam OwnerId;

	// Event Service - Send Params
	static const OperationParam EventServiceSendToId;
	static const OperationParam EventServiceSendEventType;
	static const OperationParam EventServiceSendEventId;
	static const OperationParam EventServiceSendEventData;
	static const OperationParam EventServiceSendRecordLocally;

	// Event Service - Update Event Data Params
	static const OperationParam EventServiceUpdateEventDataFromId;
	static const OperationParam EventServiceUpdateEventDataEventId;
	static const OperationParam EventServiceUpdateEventDataData;
	static const OperationParam EvId;

	// Event Service - Delete Incoming Params
	static const OperationParam EventServiceDeleteIncomingEventId;
	static const OperationParam EventServiceDeleteIncomingFromId;

	// Event Service - Delete Sent Params
	static const OperationParam EventServiceDeleteSentEventId;
	static const OperationParam EventServiceDeleteSentToId;
	static const OperationParam EventServiceIncludeIncomingEvents;
	static const OperationParam EventServiceIncludeSentEvents;

	// Friend Service - Read Player State Params
	static const OperationParam FriendServiceAuthenticationType;
	static const OperationParam FriendServiceEntityId;
	static const OperationParam FriendServiceExternalId;
	static const OperationParam FriendServiceProfileId;
	static const OperationParam FriendServiceFriendId;
	static const OperationParam FriendServiceEntityType;
	static const OperationParam FriendServiceIncludeSummaryData;
	static const OperationParam FriendServiceEntitySubType;
	static const OperationParam FriendServiceReadPlayerStateFriendId;
	static const OperationParam FriendServiceSearchText;
	static const OperationParam FriendServiceMaxResults;
	static const OperationParam FriendServiceFriendPlatform;
	static const OperationParam FriendServiceProfileIds;
	static const OperationParam ExternalAuthType;

	//Achievements Event Data Params
	static const OperationParam GamificationServiceAchievementsName;
	static const OperationParam GamificationServiceAchievementsData;
	static const OperationParam GamificationServiceAchievementsGranted;
	static const OperationParam GamificationServiceCategory;
	static const OperationParam GamificationServiceIncludeMetaData;
	static const OperationParam GamificationServiceMilestonesName;

	// Player Statistics Event Params
	static const OperationParam PlayerStatisticEventServiceEventName;
	static const OperationParam PlayerStatisticEventServiceEventMultiplier;
	static const OperationParam PlayerStatisticEventServiceEvents;

	// Presence Params
	static const OperationParam PresenceServicePlatform;
	static const OperationParam PresenceServiceIncludeOffline;
	static const OperationParam PresenceServiceGroupId;
	static const OperationParam PresenceServiceProfileIds;
	static const OperationParam PresenceServiceBidirectional;
	static const OperationParam PresenceServiceVisible;
	static const OperationParam PresenceServiceActivity;

	// Player State Service - Read Params
	static const OperationParam PlayerStateServiceReadEntitySubtype;

	// Player State Service - Update Summary Params
	static const OperationParam PlayerStateServiceUpdateSummaryFriendData;

	// Player State Service - Update Name Params
	static const OperationParam PlayerStateServiceUpdateNameData;

	// Player State Service - Atributes
	static const OperationParam PlayerStateServiceAttributes;
	static const OperationParam PlayerStateServiceWipeExisting;

	// Player State Service - Atributes
	static const OperationParam PlayerStateServicePictureUrl;
	static const OperationParam PlayerStateServiceContactEmail;

	// Player Statistics Service - Update Increment Params
	static const OperationParam PlayerStatisticsServiceStats;
	static const OperationParam PlayerStatisticsServiceStatNames;
	static const OperationParam PlayerStatisticsExperiencePoints;

	// Player Statistics Service - Read Params
	static const OperationParam PlayerStatisticsServiceReadEntitySubType;

	// Leaderboard Service - general parameters
	static const OperationParam LeaderboardServiceLeaderboardId;
	static const OperationParam LeaderboardServiceLeaderboardIds;
	static const OperationParam LeaderboardServiceReplaceName;
	static const OperationParam LeaderboardServiceScore;
	static const OperationParam LeaderboardServiceData;
	static const OperationParam LeaderboardServiceEventName;
	static const OperationParam LeaderboardServiceEventMultiplier;
	static const OperationParam LeaderboardServiceLeaderboardType;
	static const OperationParam LeaderboardServiceRotationType;
	static const OperationParam LeaderboardServiceRotationReset;
	static const OperationParam LeaderboardServiceRotationResetTime;
	static const OperationParam LeaderboardServiceRetainedCount;
	static const OperationParam LeaderboardServiceFetchType;
	static const OperationParam LeaderboardServiceMaxResults;
	static const OperationParam LeaderboardServiceSortOrder;
	static const OperationParam LeaderboardServiceStartIndex;
	static const OperationParam LeaderboardServiceEndIndex;
	static const OperationParam LeaderboardServiceBeforeCount;
	static const OperationParam LeaderboardServiceAfterCount;
	static const OperationParam LeaderboardServiceIncludeLeaderboardSize;
	static const OperationParam LeaderboardServiceVersionId;
	static const OperationParam LeaderboardServiceLeaderboardResultCount;
	static const OperationParam ProfileIds;
	static const OperationParam NumDaysToRotate;

	// Product service
	static const OperationParam ProductServiceVCId;
	static const OperationParam ProductServiceVCAmount;

	// Product Service - Get Inventory Params
	static const OperationParam ProductServiceGetInventoryPlatform;
	static const OperationParam ProductServiceGetInventoryUserCurrency;
	static const OperationParam ProductServiceGetInventoryCategory;

	// Product Service - Op Cash In Receipt Params
	static const OperationParam ProductServiceOpCashInReceiptReceipt;
	static const OperationParam ProductServiceOpCashInReceiptUrl;

	// Server Time Service - Read Params
	static const OperationParam ServerTimeServiceRead;

	// data creation params
	static const OperationParam ServiceMessageService;
	static const OperationParam ServiceMessageOperation;
	static const OperationParam ServiceMessageData;

	// data bundle creation Params
	static const OperationParam ServiceMessagePacketId;
	static const OperationParam ServiceMessageProfileId;
	static const OperationParam ServiceMessageSessionId;
	static const OperationParam ServiceMessageMessages;

	// Error Params
	static const OperationParam ServiceMessageReasonCode;
	static const OperationParam ServiceMessageStatusMessage;

	static const OperationParam ReleasePlatformIos;
	static const OperationParam ReleasePlatformFacebook;
	static const OperationParam ReleasePlatformBlackberry;
	static const OperationParam ReleasePlatformGoogleAndroid;
	static const OperationParam ReleasePlatformWindowsPhone;
	static const OperationParam ReleasePlatformWindows;
	static const OperationParam ReleasePlatformMac;
	static const OperationParam ReleasePlatformLinux;

	static const OperationParam ScriptServiceRunScriptName;
	static const OperationParam ScriptServiceRunScriptData;
	static const OperationParam ScriptServiceStartDateUTC;
	static const OperationParam ScriptServiceStartMinutesFromNow;
	static const OperationParam ScriptServiceJobId;

	static const OperationParam MatchMakingServicePlayerRating;
	static const OperationParam MatchMakingServiceMinutes;
	static const OperationParam MatchMakingServiceRangeDelta;
	static const OperationParam MatchMakingServiceNumMatches;
	static const OperationParam MatchMakingServiceExtraParams;
	static const OperationParam MatchMakingServiceAttributes;
	static const OperationParam MatchMakingServicePlayerId;
	static const OperationParam MatchMakingServicePlaybackStreamId;

	static const OperationParam OneWayMatchServicePlayerId;
	static const OperationParam OneWayMatchServiceRangeDelta;
	static const OperationParam OneWayMatchServicePlaybackStreamId;

	static const OperationParam PlaybackStreamServicePlaybackStreamId;
	static const OperationParam PlaybackStreamServiceTargetPlayerId;
	static const OperationParam PlaybackStreamServiceInitiatingPlayerId;
	static const OperationParam PlaybackStreamServiceMaxNumberOfStreams;
	static const OperationParam PlaybackStreamServiceIncludeSharedData;
	static const OperationParam PlaybackStreamServiceEventData;
	static const OperationParam PlaybackStreamServiceSummary;

	static const OperationParam ProductServiceTransId;
	static const OperationParam ProductServiceLanguage;
	static const OperationParam ProductServiceItemId;
	static const OperationParam ProductServiceReceipt;
	static const OperationParam ProductServiceOrderId;
	static const OperationParam ProductServiceProductId;
	static const OperationParam ProductServiceToken;

	// S3 Handling
	static const OperationParam S3HandlingServiceCategory;
	static const OperationParam S3HandlingServiceFileDetails;
	static const OperationParam S3HandlingServiceFileId;

	// Shared Identity
	static const OperationParam AuthenticationServiceAuthenticationLevelName;
	static const OperationParam ScriptServiceParentLevelName;
	static const OperationParam PlayerStateServiceIncludeSummaryData;
	static const OperationParam IdentityServiceForceSingleton;

	// Redemption Code
	static const OperationParam RedemptionCodeServiceScanCode;
	static const OperationParam RedemptionCodeServiceCodeType;
	static const OperationParam RedemptionCodeServiceCustomRedemptionInfo;

	// DataStream
	static const OperationParam DataStreamEventName;
	static const OperationParam DataStreamEventProperties;

	// Profanity
	static const OperationParam ProfanityText;
	static const OperationParam ProfanityReplaceSymbol;
	static const OperationParam ProfanityFlagEmail;
	static const OperationParam ProfanityFlagPhone;
	static const OperationParam ProfanityFlagUrls;
	static const OperationParam ProfanityLanguages;

	// Upload
	static const OperationParam UploadLocalPath;
	static const OperationParam UploadCloudPath;
	static const OperationParam UploadCloudFilename;
	static const OperationParam UploadShareable;
	static const OperationParam UploadReplaceIfExists;
	static const OperationParam UploadFileSize;
	static const OperationParam UploadRecurse;

	// Group
	static const OperationParam GroupId;
	static const OperationParam GroupProfileId;
	static const OperationParam GroupRole;
	static const OperationParam GroupAttributes;
	static const OperationParam GroupName;
	static const OperationParam GroupType;
	static const OperationParam GroupIsOpenGroup;
	static const OperationParam GroupAcl;
	static const OperationParam GroupData;
	static const OperationParam GroupOwnerAttributes;
	static const OperationParam GroupDefaultMemberAttributes;
	static const OperationParam GroupEntityType;
	static const OperationParam GroupIsOwnedByGroupMember;
	static const OperationParam GroupEntityId;
	static const OperationParam GroupVersion;
	static const OperationParam GroupContext;
	static const OperationParam GroupPageOffset;
	static const OperationParam GroupAutoJoinStrategy;
	static const OperationParam GroupWhere;

	//mail
	static const OperationParam ProfileId;
	static const OperationParam EmailAddress;
	static const OperationParam Subject;
	static const OperationParam Body;
	static const OperationParam ServiceParams;

	static const OperationParam LeaderboardId;
	static const OperationParam DivSetId;
	static const OperationParam VersionId;
	static const OperationParam TournamentCode;
	static const OperationParam InitialScore;
	static const OperationParam Score;
	static const OperationParam RoundStartedEpoch;
	static const OperationParam Data;

	//currency
	static const OperationParam VcId;
	static const OperationParam LevelName;
	static const OperationParam PeerCode;

	static const OperationParam ChatChannelId;
	static const OperationParam ChatMaxReturn;
	static const OperationParam ChatMessageId;
	static const OperationParam ChatVersion;
	static const OperationParam ChatChannelType;
	static const OperationParam ChatChannelSubId;
	static const OperationParam ChatContent;
	static const OperationParam ChatText;
	static const OperationParam ChatRich;
	static const OperationParam ChatRecordInHistory;
	
	static const OperationParam AllChannelType;
	static const OperationParam GlobalChannelType;
	static const OperationParam GroupChannelType;
	
	static const OperationParam MessagingMessageBox;
	static const OperationParam MessagingMessageIds;
	static const OperationParam MessagingContext;
	static const OperationParam MessagingPageOffset;
	static const OperationParam MessagingFromName;
	static const OperationParam MessagingToProfileIds;
	static const OperationParam MessagingContent;
	static const OperationParam MessagingSubject;
	static const OperationParam MessagingText;
	static const OperationParam InboxMessageType;
	static const OperationParam SentMessageType;
	
	static const OperationParam LobbyRoomType;
	static const OperationParam LobbyRating;
	static const OperationParam LobbyAlgorithm;
	static const OperationParam LobbyMaxSteps;
	static const OperationParam LobbyStrategy;
	static const OperationParam LobbyAlignment;
	static const OperationParam LobbyRanges;
	static const OperationParam LobbyFilterJson;
	static const OperationParam LobbySettings;
	static const OperationParam LobbyTimeoutSeconds;
	static const OperationParam LobbyIsReady;
	static const OperationParam LobbyOtherUserCxIds;
	static const OperationParam LobbyExtraJson;
	static const OperationParam LobbyTeamCode;
	static const OperationParam LobbyIdentifier;
	static const OperationParam LobbyToTeamName;
	static const OperationParam LobbySignalData;
	static const OperationParam LobbyConnectionId;

	FString getValue() const { return _value; }

	bool operator==(const OperationParam &s) const;
	void operator=(const OperationParam &s);

	static bool isOptionalParamValid(const FString &param);

  private:
	FString _value;

	OperationParam(const FString &value);
};