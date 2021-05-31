// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once

class BCCLIENTPLUGIN_API ServiceOperation
{
  public:
	static const ServiceOperation None;

	static const ServiceOperation Authenticate;
	static const ServiceOperation Attach;
	static const ServiceOperation Merge;
	static const ServiceOperation Detach;
	static const ServiceOperation ResetEmailPassword;
	static const ServiceOperation ResetEmailPasswordAdvanced;
	static const ServiceOperation ResetEmailPasswordWithExpiry;
	static const ServiceOperation ResetEmailPasswordAdvancedWithExpiry;
	static const ServiceOperation ResetUniversalIdPassword;
	static const ServiceOperation ResetUniversalIdPasswordAdvanced;
	static const ServiceOperation ResetUniversalIdPasswordWithExpiry;
	static const ServiceOperation ResetUniversalIdPasswordAdvancedWithExpiry;
	static const ServiceOperation SwitchToChildProfile;
	static const ServiceOperation SwitchToParentProfile;
	static const ServiceOperation GetChildProfiles;
	static const ServiceOperation GetIdentities;
	static const ServiceOperation GetExpiredIdentities;
	static const ServiceOperation RefreshIdentity;
	static const ServiceOperation ChangeEmailIdentity;
	static const ServiceOperation AttachParentWithIdentity;
	static const ServiceOperation DetachParent;
	static const ServiceOperation AttachPeerProfile;
	static const ServiceOperation DetachPeer;
	static const ServiceOperation GetPeerProfiles;
	static const ServiceOperation AttachNonLoginUniversalId;
	static const ServiceOperation UpdateUniversalIdLogin;

	static const ServiceOperation Create;
	static const ServiceOperation CreateWithIndexedId;
	static const ServiceOperation Reset;
	static const ServiceOperation Read;
	static const ServiceOperation ReadSingleton;
	static const ServiceOperation ReadByType;
	static const ServiceOperation Verify;
	static const ServiceOperation ReadShared;
	static const ServiceOperation ReadSharedEntity;

	// push notification
	static const ServiceOperation Deregister;
	static const ServiceOperation DeregisterAll;
	static const ServiceOperation Register;
	static const ServiceOperation SendSimple;
	static const ServiceOperation SendRich;
	static const ServiceOperation SendRaw;
	static const ServiceOperation SendRawBatch;
	static const ServiceOperation SendRawToGroup;
	static const ServiceOperation SendTemplatedToGroup;
	static const ServiceOperation SendNormalizedToGroup;
	static const ServiceOperation SendNormalized;
	static const ServiceOperation SendNormalizedBatch;
	static const ServiceOperation ScheduleNormalizedNotifcation;
	static const ServiceOperation ScheduledRichNotifcation;
	static const ServiceOperation ScheduledRawNotifcation;

	static const ServiceOperation Trigger;
	static const ServiceOperation TriggerMultiple;
	static const ServiceOperation TriggerGrantExperience;

	static const ServiceOperation FullReset;
	static const ServiceOperation DataReset;
	static const ServiceOperation SubmitCrashReport;

	static const ServiceOperation Update;
	static const ServiceOperation UpdatePartial;
	static const ServiceOperation UpdateShared;
	static const ServiceOperation UpdateSingleton;
	static const ServiceOperation UpdateAcl;
	static const ServiceOperation UpdateTimeToLive;
	static const ServiceOperation Delete;
	static const ServiceOperation DeleteSingleton;
	static const ServiceOperation UpdateSummary;
	static const ServiceOperation UpdateSetMinimum;
	static const ServiceOperation UpdateIncrementToMaximum;
	static const ServiceOperation ProcessStatistics;
	static const ServiceOperation UpdateEntityIndexedId;
	static const ServiceOperation UpdateEntityOwnerAndAcl;
	static const ServiceOperation MakeSystemEntity;
	static const ServiceOperation AbandonMatchWithSummaryData;
	static const ServiceOperation CompleteMatchWithSummaryData;

	static const ServiceOperation AttachBlockchainIdentity;
	static const ServiceOperation DetachBlockchainIdentity;
	static const ServiceOperation RemoveUserItemFromBlockchain;

	static const ServiceOperation UpdateTimeZoneOffset;
	static const ServiceOperation UpdateLanguageCode;
	static const ServiceOperation GetScheduledCloudSripts;
	static const ServiceOperation GetRunningOrQueuedCloudScripts;

	static const ServiceOperation GetFriendProfileInfoForExternalId;
	static const ServiceOperation GetProfileInfoForCredential;
	static const ServiceOperation GetProfileInfoForExternalAuthId;
	static const ServiceOperation GetExternalIdForProfileId;
	static const ServiceOperation ReadFriendEntity;
	static const ServiceOperation ReadFriendsEntities;
	static const ServiceOperation ReadFriendsWithApplication;
	static const ServiceOperation ReadFriends;
	static const ServiceOperation ReadFriendsPlayerState;
	static const ServiceOperation FindPlayerByName;
	static const ServiceOperation FindUsersByExactName;
	static const ServiceOperation FindUsersBySubstrName;
	static const ServiceOperation ListFriends;
	static const ServiceOperation GetMySocialInfo;
	static const ServiceOperation AddFriends;
	static const ServiceOperation GetUsersOnlineStatus;
	static const ServiceOperation RemoveFriends;
	static const ServiceOperation FindUserByUniversalId;
	static const ServiceOperation FindPlayerByUniversalId;
	static const ServiceOperation FindUserByExactUniversalId;
	static const ServiceOperation FindUsersByUniversalIdStartingWith;
	static const ServiceOperation FindUsersByNameStartingWith;
	static const ServiceOperation GetSocialLeaderboard;
	static const ServiceOperation GetSocialLeaderboardByVersion;
	static const ServiceOperation GetMultiSocialLeaderboard;
	static const ServiceOperation GetGlobalLeaderboard;
	static const ServiceOperation GetGlobalLeaderboardPage;
	static const ServiceOperation GetGlobalLeaderboardView;
	static const ServiceOperation GetGlobalLeaderboardVersions;
	static const ServiceOperation GetCompletedTournament;
	static const ServiceOperation RewardTournament;
	static const ServiceOperation PostScore;
	static const ServiceOperation PostScoreDynamic;
	static const ServiceOperation GetGroupSocialLeaderboard;
	static const ServiceOperation GetGroupSocialLeaderboardByVersion;
	static const ServiceOperation GetSummaryDataForProfileId;
	static const ServiceOperation GetPlayersSocialLeaderboard;
	static const ServiceOperation GetPlayersSocialLeaderboardByVersion;
	static const ServiceOperation ListAllLeaderboards;
	static const ServiceOperation GetGlobalLeaderboardEntryCount;
	static const ServiceOperation RemovePlayerScore;
	static const ServiceOperation GetPlayerScore;
	static const ServiceOperation GetPlayerScores;
	static const ServiceOperation GetPlayerScoresFromLeaderboards;
	static const ServiceOperation PostScoreToGroupLeaderboard;
	static const ServiceOperation PostScoreToDynamicGroupLeaderboard;
	static const ServiceOperation RemoveGroupScore;
	static const ServiceOperation GetGroupLeaderboardView;

	//Global File
	static const ServiceOperation GetFileInfo;
	static const ServiceOperation GetFileInfoSimple;
	static const ServiceOperation GetGlobalCDNUrl;
	static const ServiceOperation GetGlobalFileList;

	static const ServiceOperation InitThirdParty;
	static const ServiceOperation PostThirdPartyLeaderboardScore;
	static const ServiceOperation IncrementThirdPartyLeaderboardScore;
	static const ServiceOperation LaunchAchievementUI;
	static const ServiceOperation PostThirdPartyLeaderboardAchievement;
	static const ServiceOperation IsThirdPartyAchievementComplete;
	static const ServiceOperation ResetThirdPartyAchievements;
	static const ServiceOperation QueryThirdPartyAchievements;

	static const ServiceOperation GetInventory;
	static const ServiceOperation CashInReceipt;
	static const ServiceOperation AwardVC;
	static const ServiceOperation ConsumeVC;
	static const ServiceOperation GetPlayerVC;
	static const ServiceOperation ResetPlayerVC;

	static const ServiceOperation AwardParentVC;
	static const ServiceOperation ConsumeParentVC;
	static const ServiceOperation GetParentVC;
	static const ServiceOperation ResetParentVC;

	static const ServiceOperation Send;
	static const ServiceOperation UpdateEventData;
	static const ServiceOperation DeleteSent;
	static const ServiceOperation DeleteIncoming;
	static const ServiceOperation DeleteIncomingEvents;
	static const ServiceOperation DeleteIncomingEventsOlderThan;
	static const ServiceOperation DeleteIncomingEventsByTypeOlderThan;
	static const ServiceOperation GetEvents;

	static const ServiceOperation UpdateIncrement;
	static const ServiceOperation ReadNextXplevel;
	static const ServiceOperation ReadXpLevels;
	static const ServiceOperation ReadSubset;
	static const ServiceOperation ReadForCategory;

	static const ServiceOperation SetXpPoints;

	static const ServiceOperation Run;
	static const ServiceOperation Tweet;

	static const ServiceOperation AwardAchievements;
	static const ServiceOperation ReadAchievements;
	static const ServiceOperation ReadAchievedAchievements;

	static const ServiceOperation SetPlayerRating;
	static const ServiceOperation ResetPlayerRating;
	static const ServiceOperation IncrementPlayerRating;
	static const ServiceOperation DecrementPlayerRating;
	static const ServiceOperation ShieldOn;
	static const ServiceOperation ShieldOnFor;
	static const ServiceOperation ShieldOff;
	static const ServiceOperation IncrementShieldOnFor;
	static const ServiceOperation GetShieldExpiry;
	static const ServiceOperation FindPlayers;
	static const ServiceOperation FindPlayersUsingFilter;

	static const ServiceOperation SubmitTurn;
	static const ServiceOperation UpdateMatchSummary;
	static const ServiceOperation Abandon;
	static const ServiceOperation Complete;
	static const ServiceOperation ReadMatch;
	static const ServiceOperation ReadMatchHistory;
	static const ServiceOperation FindMatches;
	static const ServiceOperation FindMatchesCompleted;
	static const ServiceOperation DeleteMatch;

	static const ServiceOperation LastUploadStatus;

	static const ServiceOperation ReadQuests;
	static const ServiceOperation ReadCompletedQuests;
	static const ServiceOperation ReadInProgressQuests;
	static const ServiceOperation ReadNotStartedQuests;
	static const ServiceOperation ReadQuestsWithStatus;
	static const ServiceOperation ReadQuestsWithBasicPercentage;
	static const ServiceOperation ReadQuestsWithComplexPercentage;
	static const ServiceOperation ReadQuestsByCategory;

	static const ServiceOperation ReadGameStatisticsByCategory;
	static const ServiceOperation ReadPlayerStatisticsByCategory;

	static const ServiceOperation ReadMilestones;
	static const ServiceOperation ReadMilestonesByCategory;
	static const ServiceOperation ResetMilestones;

	static const ServiceOperation ReadCompletedMilestones;
	static const ServiceOperation ReadInProgressMilestones;

	static const ServiceOperation Logout;
	static const ServiceOperation UpdateName;

	static const ServiceOperation StartMatch;
	static const ServiceOperation CancelMatch;
	static const ServiceOperation CompleteMatch;
	static const ServiceOperation EnableMatchMaking;
	static const ServiceOperation DisableMatchMaking;

	static const ServiceOperation StartStream;
	static const ServiceOperation ReadStream;
	static const ServiceOperation EndStream;
	static const ServiceOperation DeleteStream;
	static const ServiceOperation AddEvent;
	static const ServiceOperation GetStreamSummariesForInitiatingPlayer;
	static const ServiceOperation GetStreamSummariesForTargetPlayer;
	static const ServiceOperation GetRecentStreamsForInitiatingPlayer;
	static const ServiceOperation GetRecentStreamsForTargetPlayer;

	static const ServiceOperation GetUserInfo;

	static const ServiceOperation StartSteamTransaction;
	static const ServiceOperation FinalizeSteamTransaction;
	static const ServiceOperation VerifyMicrosoftReceipt;
	static const ServiceOperation ConfirmGooglePlayPurchase;
	static const ServiceOperation EligiblePromotions;

	static const ServiceOperation ReadSharedEntitesList;
	static const ServiceOperation GetList;
	static const ServiceOperation GetListByIndexedId;
	static const ServiceOperation GetListCount;
	static const ServiceOperation CustomEntityGetPage;
	static const ServiceOperation CustomEntityGetPageOffset;
	static const ServiceOperation CustomEntityGetEntityPage;
	static const ServiceOperation CustomEntityGetEntityPageOffset;
	static const ServiceOperation IncrementUserEntityData;
	static const ServiceOperation IncrementSharedUserEntityData;
	static const ServiceOperation IncrementGlobalEntityData;
	static const ServiceOperation GetRandomEntitiesMatching;
	static const ServiceOperation DeleteEntities;


	static const ServiceOperation GetAttributes;
	static const ServiceOperation UpdateAttributes;
	static const ServiceOperation RemoveAttributes;
	static const ServiceOperation UpdatePlayerPicture;
	static const ServiceOperation UpdateContactEmail;
	static const ServiceOperation ClearUserStatus;
	static const ServiceOperation ExtendUserStatus;
	static const ServiceOperation GetUserStatus;
	static const ServiceOperation SetUserStatus;

	static const ServiceOperation ReadProperties;

	static const ServiceOperation GetUpdatedFiles;
	static const ServiceOperation GetFileList;

	static const ServiceOperation ScheduleCloudScript;
	static const ServiceOperation RunParentScript;
	static const ServiceOperation CancelScheduledScript;
	static const ServiceOperation RunPeerScript;
	static const ServiceOperation RunPeerScriptAsync;

	static const ServiceOperation RedeemCode;
	static const ServiceOperation GetRedeemedCodes;

	static const ServiceOperation CustomPageEvent;
	static const ServiceOperation CustomScreenEvent;
	static const ServiceOperation CustomTrackEvent;

	// profanity
	static const ServiceOperation ProfanityCheck;
	static const ServiceOperation ProfanityReplaceText;
	static const ServiceOperation ProfanityIdenitfyBadWords;

	// file
	static const ServiceOperation PrepareUserUpload;
	static const ServiceOperation ListUserFiles;
	static const ServiceOperation DeleteUserFiles;
	static const ServiceOperation GetCdnUrl;

	//group
	static const ServiceOperation AcceptGroupInvitation;
	static const ServiceOperation AddGroupMember;
	static const ServiceOperation ApproveGroupJoinRequest;
	static const ServiceOperation AutoJoinGroup;
	static const ServiceOperation AutoJoinGroupMulti;
	static const ServiceOperation CancelGroupInvitation;
	static const ServiceOperation CreateGroup;
	static const ServiceOperation CreateGroupEntity;
	static const ServiceOperation DeleteGroup;
	static const ServiceOperation DeleteGroupEntity;
	static const ServiceOperation DeleteGroupMemeber;
	static const ServiceOperation GetMyGroups;
	static const ServiceOperation IncrementGroupData;
	static const ServiceOperation IncrementGroupEntityData;
	static const ServiceOperation InviteGroupMember;
	static const ServiceOperation JoinGroup;
	static const ServiceOperation LeaveGroup;
	static const ServiceOperation ListGroupsPage;
	static const ServiceOperation ListGroupsPageByOffset;
	static const ServiceOperation ListGroupsWithMember;
	static const ServiceOperation ReadGroup;
	static const ServiceOperation ReadGroupData;
	static const ServiceOperation ReadGroupEntitiesPage;
	static const ServiceOperation ReadGroupEntitiesPageByOffset;
	static const ServiceOperation ReadGroupEntity;
	static const ServiceOperation ReadGroupMembers;
	static const ServiceOperation RejectGroupInvitation;
	static const ServiceOperation RejectGroupJoinRequest;
	static const ServiceOperation RemoveGroupMember;
	static const ServiceOperation UpdateGroupData;
	static const ServiceOperation UpdateGroupEntity;
	static const ServiceOperation UpdateGroupMember;
	static const ServiceOperation UpdateGroupName;
	static const ServiceOperation SetGroupOpen;
	static const ServiceOperation UpdateGroupSummaryData;
	static const ServiceOperation GetRandomGroupsMatching;

	//mail
	static const ServiceOperation SendBasicEmail;
	static const ServiceOperation SendAdvancedEmail;
	static const ServiceOperation SendAdvancedEmailByAddress;

	//tournament
	static const ServiceOperation GetTournamentStatus;
	static const ServiceOperation GetDivisionInfo;
	static const ServiceOperation GetMyDivisions;
	static const ServiceOperation JoinDivision;
	static const ServiceOperation LeaveDivisionInstance;
	static const ServiceOperation JoinTournament;
	static const ServiceOperation LeaveTournament;
	static const ServiceOperation PostTournamentScore;
	static const ServiceOperation PostTournamentScoreWithResults;
	static const ServiceOperation ViewCurrentReward;
	static const ServiceOperation ViewReward;
	static const ServiceOperation ClaimTournamentReward;

	//CustomEntity
	static const ServiceOperation CreateEntity;
	static const ServiceOperation DeleteEntity;
	static const ServiceOperation GetCount;
	static const ServiceOperation GetPage;
	static const ServiceOperation GetPageOffset;
	static const ServiceOperation GetEntityPage;
	static const ServiceOperation GetEntityPageOffset;
	static const ServiceOperation ReadEntity;
	static const ServiceOperation IncrementData;
	static const ServiceOperation UpdateEntity;
	static const ServiceOperation UpdateEntityFields;
	static const ServiceOperation UpdateSingletonFields;
	
	//presence
	static const ServiceOperation ForcePush;
	static const ServiceOperation GetPresenceOfFriends;
	static const ServiceOperation GetPresenceOfGroup;
	static const ServiceOperation GetPresenceOfUsers;
	static const ServiceOperation RegisterListenersForFriends;
	static const ServiceOperation RegisterListenersForGroup;
	static const ServiceOperation RegisterListenersForProfiles;
	static const ServiceOperation SetVisibility;
	static const ServiceOperation StopListening;
	static const ServiceOperation UpdateActivity;

	//virtualCurrency
	static const ServiceOperation GetPlayerCurrency;
	static const ServiceOperation GetParentCurrency;
	static const ServiceOperation GetPeerCurrency;
	static const ServiceOperation ConsumeVirtualCurrency;
	static const ServiceOperation AwardVirtualCurrency;

	//App Store
	static const ServiceOperation VerifyPurchase;
	static const ServiceOperation GetEligiblePromotions;
	static const ServiceOperation GetSalesInventory;
	static const ServiceOperation GetSalesInventoryByCategory;
	static const ServiceOperation StartPurchase;
	static const ServiceOperation FinalizePurchase;
	static const ServiceOperation RefreshPromotions;

	// rtt
	static const ServiceOperation RequestClientConnection;
	static const ServiceOperation Connect;

	// chat
	static const ServiceOperation ChannelConnect;
	static const ServiceOperation ChannelDisconnect;
	static const ServiceOperation DeleteChatMessage;
	static const ServiceOperation GetChannelId;
	static const ServiceOperation GetChannelInfo;
	static const ServiceOperation GetChatMessage;
	static const ServiceOperation GetRecentChatMessages;
	static const ServiceOperation GetSubscribedChannels;
	static const ServiceOperation PostChatMessage;
	static const ServiceOperation PostChatMessageSimple;
	static const ServiceOperation UpdateChatMessage;
	// messaging
	static const ServiceOperation DeleteMessages;
	static const ServiceOperation GetMessageBoxes;
	static const ServiceOperation GetMessageCounts;
	static const ServiceOperation GetMessages;
	static const ServiceOperation GetMessagesPage;
	static const ServiceOperation GetMessagesPageOffset;
	static const ServiceOperation MarkMessagesRead;
	static const ServiceOperation SEND_MESSAGE;
	static const ServiceOperation SendMessageSimple;
	// lobby
	static const ServiceOperation FindLobby;
	static const ServiceOperation FindLobbyWithPingData;
	static const ServiceOperation CreateLobby;
	static const ServiceOperation CreateLobbyWithPingData;
	static const ServiceOperation FindOrCreateLobby;
	static const ServiceOperation FindOrCreateLobbyWithPingData;
	static const ServiceOperation GetLobbyData;
	static const ServiceOperation UpdateReady;
	static const ServiceOperation UpdateSettings;
	static const ServiceOperation SwitchTeam;
	static const ServiceOperation SendSignal;
	static const ServiceOperation JoinLobby;
	static const ServiceOperation JoinLobbyWithPingData;
	static const ServiceOperation LeaveLobby;
	static const ServiceOperation RemoveMember;
	static const ServiceOperation CancelFindRequest;
	static const ServiceOperation GetRegionsForLobbies;
	static const ServiceOperation PingData;

	//Item Catalog
	static const ServiceOperation GetCatalogItemDefinition;
	static const ServiceOperation GetCatalogItemsPage;
	static const ServiceOperation GetCatalogItemsPageOffset;

	//UserItemsManagement
	static const ServiceOperation AwardUserItem;
	static const ServiceOperation DropUserItem;
	static const ServiceOperation GetUserItemsPage;
	static const ServiceOperation GetUserItemsPageOffset;
	static const ServiceOperation GetUserItem;
	static const ServiceOperation GiveUserItemTo;
	static const ServiceOperation PurchaseUserItem;
	static const ServiceOperation ReceiveUserItemFrom;
	static const ServiceOperation SellUserItem;
	static const ServiceOperation UpdateUserItemData;
	static const ServiceOperation UseUserItem;
	static const ServiceOperation PublishUserItemToBlackchain;
	static const ServiceOperation RefreshBlockchainUserItems;

	FString getValue() const { return _value; }

	bool operator==(const ServiceOperation &s) const;
	void operator=(const ServiceOperation &s);

  private:
	ServiceOperation(const FString &operation);

	FString _value;
};