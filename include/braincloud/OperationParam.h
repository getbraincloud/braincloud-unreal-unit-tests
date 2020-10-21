#pragma once

#include <string>

namespace BrainCloud {

	class OperationParam
	{
	public:
		static const OperationParam Authenticate;

		//Push Notification Service - Send Params
		static const OperationParam PushNotificationSendParamToPlayerId;
		static const OperationParam PushNotificationSendParamNotificationTemplateId;
		static const OperationParam PushNotificationSendParamMessage;
		static const OperationParam PushNotificationSendParamSubstitution;
		static const OperationParam AlertContent;
		static const OperationParam CustomData;
		static const OperationParam StartDateUTC;
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
		static const OperationParam AuthenticateServiceAuthenticateUniversalId;
		static const OperationParam AuthenticateServiceAuthenticateEmailAddress;
		static const OperationParam AuthenticateServiceAuthenticateServiceParams;
		static const OperationParam AuthenticateServiceAuthenticateTokenTtlInMinutes;
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

		// Authenticate Service - Authenticate Params
		static const OperationParam IdentityServiceExternalId;
		static const OperationParam IdentityServiceAuthenticationType;
		static const OperationParam IdentityServiceConfirmAnonymous;
		static const OperationParam Peer;

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

		static const OperationParam PlayerStateServiceTimeZoneOffset;
		static const OperationParam PlayerStateServiceLanguageCode;

		// Player Statistics Service - Update Increment Params
		static const OperationParam PlayerStatisticsServiceStats;
		static const OperationParam PlayerStatisticsServiceStatNames;
		static const OperationParam PlayerStatisticsExperiencePoints;

		// Player Statistics Service - Read Params
		static const OperationParam PlayerStatisticsServiceReadEntitySubType;

		// Social Leaderboard Service - general parameters
		static const OperationParam SocialLeaderboardServiceLeaderboardId;
		static const OperationParam SocialLeaderboardServiceLeaderboardIds;
		static const OperationParam SocialLeaderboardServiceReplaceName;
		static const OperationParam SocialLeaderboardServiceScore;
		static const OperationParam SocialLeaderboardServiceData;
		static const OperationParam SocialLeaderboardServiceEventName;
		static const OperationParam SocialLeaderboardServiceEventMultiplier;
		static const OperationParam SocialLeaderboardServiceLeaderboardType;
		static const OperationParam SocialLeaderboardServiceRotationType;
		static const OperationParam SocialLeaderboardServiceRotationReset;
		static const OperationParam SocialLeaderboardServiceRotationResetTime;
		static const OperationParam SocialLeaderboardServiceRetainedCount;
		static const OperationParam NumDaysToRotate;
		static const OperationParam SocialLeaderboardServiceFetchType;
		static const OperationParam SocialLeaderboardServiceMaxResults;
		static const OperationParam SocialLeaderboardServiceSortOrder;
		static const OperationParam SocialLeaderboardServiceStartIndex;
		static const OperationParam SocialLeaderboardServiceEndIndex;
		static const OperationParam SocialLeaderboardServiceBeforeCount;
		static const OperationParam SocialLeaderboardServiceAfterCount;
		static const OperationParam SocialLeaderboardServiceIncludeLeaderboardSize;
		static const OperationParam SocialLeaderboardServiceVersionId;
		static const OperationParam SocialLeaderboardServiceLeaderboardResultCount;
		static const OperationParam ProfileIds;

		// Product service
		static const OperationParam ProductServiceVCId;
		static const OperationParam ProductServiceVCAmount;

        // Virtual Currency
        static const OperationParam VirtualCurrencyServiceVCId;
        static const OperationParam VirtualCurrencyServiceLevelName;
        static const OperationParam VirtualCurrencyServicePeerCode;
        static const OperationParam VirtualCurrencyServiceAmount;

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
		static const OperationParam ProfileId;
		static const OperationParam ServiceMessageSessionId;
		static const OperationParam ServiceMessageMessages;

		// Error Params
		static const OperationParam ServiceMessageReasonCode;
		static const OperationParam ServiceMessageStatusMessage;

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
		static const OperationParam PlaybackMaxNumberOfStreams;
		static const OperationParam PlaybackStreamServiceInitiatingPlayerId;
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

		//GlobalFileV3
		static const OperationParam GlobalFileV3ServiceFileId;
		static const OperationParam GlobalFileV3ServiceFolderPath;
		static const OperationParam GlobalFileV3ServiceFileName;
		static const OperationParam GlobalFileV3ServiceRecurse;

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
		static const OperationParam GroupTypes;
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
		static const OperationParam GroupSummaryData;

		//mail
		static const OperationParam OldEmailAddress;
		static const OperationParam NewEmailAddress;
		static const OperationParam UpdateContactEmail;
		static const OperationParam FieldAuthenticationToken;

		static const OperationParam EmailAddress;
		static const OperationParam Subject;
		static const OperationParam Body;
		static const OperationParam ServiceParams;


		static const OperationParam LeaderboardId;
		static const OperationParam DivSetID;
		static const OperationParam VersionId;
		static const OperationParam TournamentCode;
		static const OperationParam InitialScore;
		static const OperationParam Score;
		static const OperationParam RoundStartedEpoch;
		static const OperationParam Data;

		//Custom Entity
		static const OperationParam CustomEntityServiceEntityType;
		static const OperationParam CustomEntityServiceData;
		static const OperationParam CustomEntityServiceMaxReturn;
		static const OperationParam CustomEntityServiceAcl;
		static const OperationParam CustomEntityServiceTimeToLive;
		static const OperationParam CustomEntityServiceIsOwned;
		static const OperationParam CustomEntityServiceVersion;
		static const OperationParam CustomEntityServiceRowsPerPage;
		static const OperationParam CustomEntityServiceSearchJson;
		static const OperationParam CustomEntityServiceSortJson;
		static const OperationParam CustomEntityServiceDoCount;
		static const OperationParam CustomEntityServiceContext;
		static const OperationParam CustomEntityServicePageOffset;
		static const OperationParam CustomEntityServiceEntityId;
		static const OperationParam CustomEntityFieldsJson;
		static const OperationParam CustomEntityServiceDeleteCriteria;

		//chat
		static const OperationParam ChannelId;
		static const OperationParam MsgId;
		static const OperationParam Version;
		static const OperationParam ChannelType;
		static const OperationParam ChannelSubId;
		static const OperationParam MaxReturn;
		static const OperationParam Content;
		static const OperationParam RecordInHistory;
		static const OperationParam Text;

		//lobby
		static const OperationParam LobbyType;
		static const OperationParam LobbyTypes;
		static const OperationParam Rating;
		static const OperationParam OtherUserCxIds;
		static const OperationParam IsReady;
		static const OperationParam ExtraJson;
		static const OperationParam TeamCode;
		static const OperationParam Settings;
		static const OperationParam MaxSteps;
		static const OperationParam Algo;
		static const OperationParam Filter;
		static const OperationParam LobbyId;
		static const OperationParam CxId;
		static const OperationParam SignalData;
		static const OperationParam ToTeamCode;
		static const OperationParam PingData;

		//messaging
		static const OperationParam MessagingMsgbox;
		static const OperationParam MessagingMsgIds;
		static const OperationParam MessagingMarkAsRead;
		static const OperationParam MessagingContext;
		static const OperationParam MessagingPageOffset;
		static const OperationParam MessagingToProfileIds;
		static const OperationParam MessagingText;
		static const OperationParam MessagingSubject;
		static const OperationParam MessagingContentJson;

		//presence
		static const OperationParam PresencePlatform;
		static const OperationParam PresenceIncludeOffline;
		static const OperationParam PresenceGroupId;
		static const OperationParam PresenceProfileIds;
		static const OperationParam PresenceBidirectional;
		static const OperationParam PresenceVisible;
		static const OperationParam PresenceActivity;

        //appstore
		static const OperationParam AppStoreStoreId;
		static const OperationParam AppStoreReceiptData;
		static const OperationParam AppStorePriceInfoCriteria;
		static const OperationParam AppStoreUserCurrency;
		static const OperationParam AppStoreCategory;
		static const OperationParam AppStorePurchaseData;
		static const OperationParam AppStoreTransactionId;
		static const OperationParam AppStoreTransactionData;

		//item catalog
		static const OperationParam ItemCatalogServiceDefId;
		static const OperationParam ItemCatalogServiceContext;
		static const OperationParam ItemCatalogServicePageOffset;
		
		//UserItems
		static const OperationParam UserItemsServiceDefId;
		static const OperationParam UserItemsServiceQuantity;
		static const OperationParam UserItemsServiceIncludeDef;
		static const OperationParam UserItemsServiceItemId;
		static const OperationParam UserItemsServiceCriteria;
		static const OperationParam UserItemsServiceContext;
		static const OperationParam UserItemsServicePageOffset;
		static const OperationParam UserItemsServiceVersion;
		static const OperationParam UserItemsServiceImmediate;
		static const OperationParam UserItemsServiceProfileId;
		static const OperationParam UserItemsServiceShopId;
		static const OperationParam UserItemsServiceNewItemData;

		//Datastream
		static const OperationParam DataStreamCrashType;
		static const OperationParam DataStreamErrorMsg;
		static const OperationParam DataStreamCrashJson;
		static const OperationParam DataStreamCrashLog;
		static const OperationParam DataStreamUsername;
		static const OperationParam DataStreamUserEmail;
		static const OperationParam DataStreamUserNotes;
		static const OperationParam DataStreamUserSubmitted;

		static const OperationParam PlayerStateServiceStatusName;
		static const OperationParam PlayerStateServiceAdditionalSecs;
		static const OperationParam PlayerStateServiceDetails;
		static const OperationParam PlayerStateServiceDurationSecs;

		static const OperationParam IdentityServiceBlockchainConfig;
		static const OperationParam IdentityServicePublicKey;

		std::string getValue() const { return _value; }

		bool operator== (const OperationParam& s) const;
		void operator= (const OperationParam& s);

	private:
		std::string _value;

		OperationParam(const char * value);
	};

}