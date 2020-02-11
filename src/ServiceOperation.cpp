#include "braincloud/ServiceOperation.h"

namespace BrainCloud
{
	const ServiceOperation ServiceOperation::None = ServiceOperation("NONE");

	const ServiceOperation ServiceOperation::Authenticate = ServiceOperation("AUTHENTICATE");
	const ServiceOperation ServiceOperation::Attach = ServiceOperation("ATTACH");
	const ServiceOperation ServiceOperation::Merge = ServiceOperation("MERGE");
	const ServiceOperation ServiceOperation::Detach = ServiceOperation("DETACH");
	const ServiceOperation ServiceOperation::ResetEmailPassword = ServiceOperation("RESET_EMAIL_PASSWORD");
	const ServiceOperation ServiceOperation::ResetEmailPasswordAdvanced = ServiceOperation("RESET_EMAIL_PASSWORD_ADVANCED");
	const ServiceOperation ServiceOperation::ResetEmailPasswordWithExpiry = ServiceOperation("RESET_EMAIL_PASSWORD_WITH_EXPIRY");
	const ServiceOperation ServiceOperation::ResetEmailPasswordAdvancedWithExpiry = ServiceOperation("RESET_EMAIL_PASSWORD_ADVANCED_WITH_EXPIRY");
	const ServiceOperation ServiceOperation::ResetUniversalIdPassword = ServiceOperation("RESET_UNIVERSAL_ID_PASSWORD");
	const ServiceOperation ServiceOperation::ResetUniversalIdPasswordAdvanced = ServiceOperation("RESET_UNIVERSAL_ID_PASSWORD_ADVANCED");
	const ServiceOperation ServiceOperation::ResetUniversalIdPasswordWithExpiry = ServiceOperation("RESET_UNIVERSAL_ID_PASSWORD_WITH_EXPIRY");
	const ServiceOperation ServiceOperation::ResetUniversalIdPasswordAdvancedWithExpiry = ServiceOperation("RESET_UNIVERSAL_ID_PASSWORD_ADVANCED_WITH_EXPIRY");
	const ServiceOperation ServiceOperation::SwitchToChildProfile = ServiceOperation("SWITCH_TO_CHILD_PROFILE");
	const ServiceOperation ServiceOperation::SwitchToParentProfile = ServiceOperation("SWITCH_TO_PARENT_PROFILE");
	const ServiceOperation ServiceOperation::GetChildProfiles = ServiceOperation("GET_CHILD_PROFILES");
	const ServiceOperation ServiceOperation::GetIdentities = ServiceOperation("GET_IDENTITIES");
	const ServiceOperation ServiceOperation::GetExpiredIdentities = ServiceOperation("GET_EXPIRED_IDENTITIES");
	const ServiceOperation ServiceOperation::RefreshIdentity = ServiceOperation("REFRESH_IDENTITY");
	const ServiceOperation ServiceOperation::ChangeEmailIdentity = ServiceOperation("CHANGE_EMAIL_IDENTITY");
	const ServiceOperation ServiceOperation::AttachParentWithIdentity = ServiceOperation("ATTACH_PARENT_WITH_IDENTITY");
	const ServiceOperation ServiceOperation::AttachNonLoginUniversalId = ServiceOperation("ATTACH_NONLOGIN_UNIVERSAL");
	const ServiceOperation ServiceOperation::UpdateUniversalIdLogin = ServiceOperation("UPDATE_UNIVERSAL_LOGIN");
	const ServiceOperation ServiceOperation::AttachPeerProfile = ServiceOperation("ATTACH_PEER_PROFILE");
	const ServiceOperation ServiceOperation::DetachPeer = ServiceOperation("DETACH_PEER");
	const ServiceOperation ServiceOperation::GetPeerProfiles = ServiceOperation("GET_PEER_PROFILES");
	const ServiceOperation ServiceOperation::DetachParent = ServiceOperation("DETACH_PARENT");

	const ServiceOperation ServiceOperation::Create = ServiceOperation("CREATE");
	const ServiceOperation ServiceOperation::CreateWithIndexedId = ServiceOperation("CREATE_WITH_INDEXED_ID");
	const ServiceOperation ServiceOperation::Reset = ServiceOperation("RESET");
	const ServiceOperation ServiceOperation::Read = ServiceOperation("READ");
	const ServiceOperation ServiceOperation::ReadSingleton = ServiceOperation("READ_SINGLETON");
	const ServiceOperation ServiceOperation::ReadByType = ServiceOperation("READ_BY_TYPE");
	const ServiceOperation ServiceOperation::Verify = ServiceOperation("VERIFY");
	const ServiceOperation ServiceOperation::ReadShared = ServiceOperation("READ_SHARED");
	const ServiceOperation ServiceOperation::ReadSharedEntity = ServiceOperation("READ_SHARED_ENTITY");

	// push notification
	const ServiceOperation ServiceOperation::Deregister = ServiceOperation("DEREGISTER");
	const ServiceOperation ServiceOperation::DeregisterAll = ServiceOperation("DEREGISTER_ALL");
	const ServiceOperation ServiceOperation::Register = ServiceOperation("REGISTER");
	const ServiceOperation ServiceOperation::SendSimple = ServiceOperation("SEND_SIMPLE");
	const ServiceOperation ServiceOperation::SendRich = ServiceOperation("SEND_RICH");
	const ServiceOperation ServiceOperation::SendRaw = ServiceOperation("SEND_RAW");
	const ServiceOperation ServiceOperation::SendRawToGroup = ServiceOperation("SEND_RAW_TO_GROUP");
	const ServiceOperation ServiceOperation::SendRawBatch = ServiceOperation("SEND_RAW_BATCH");
	const ServiceOperation ServiceOperation::SendTemplatedToGroup = ServiceOperation("SEND_TEMPLATED_TO_GROUP");
	const ServiceOperation ServiceOperation::SendNormalizedToGroup = ServiceOperation("SEND_NORMALIZED_TO_GROUP");
	const ServiceOperation ServiceOperation::SendNormalized = ServiceOperation("SEND_NORMALIZED");
	const ServiceOperation ServiceOperation::SendNormalizedBatch = ServiceOperation("SEND_NORMALIZED_BATCH");
	const ServiceOperation ServiceOperation::ScheduleRichNotification = ServiceOperation("SCHEDULE_RICH_NOTIFICATION");
	const ServiceOperation ServiceOperation::ScheduleNormalizedNotification = ServiceOperation("SCHEDULE_NORMALIZED_NOTIFICATION");
	const ServiceOperation ServiceOperation::ScheduleRawNotification = ServiceOperation("SCHEDULE_RAW_NOTIFICATION");

	const ServiceOperation ServiceOperation::Trigger = ServiceOperation("TRIGGER");
	const ServiceOperation ServiceOperation::TriggerMultiple = ServiceOperation("TRIGGER_MULTIPLE");
	const ServiceOperation ServiceOperation::TriggerGrantExperience = ServiceOperation("TRIGGER_GRANT_EXPERIENCE");

	const ServiceOperation ServiceOperation::FullReset = ServiceOperation("FULL_PLAYER_RESET");
	const ServiceOperation ServiceOperation::DataReset = ServiceOperation("GAME_DATA_RESET");

	const ServiceOperation ServiceOperation::Update = ServiceOperation("UPDATE");
	const ServiceOperation ServiceOperation::UpdatePartial = ServiceOperation("UPDATE_PARTIAL");
	const ServiceOperation ServiceOperation::UpdateShared = ServiceOperation("UPDATE_SHARED");
	const ServiceOperation ServiceOperation::UpdateSingleton = ServiceOperation("UPDATE_SINGLETON");
	const ServiceOperation ServiceOperation::UpdateAcl = ServiceOperation("UPDATE_ACL");
	const ServiceOperation ServiceOperation::UpdateTimeToLive = ServiceOperation("UPDATE_TIME_TO_LIVE");
	const ServiceOperation ServiceOperation::Delete = ServiceOperation("DELETE");
	const ServiceOperation ServiceOperation::DeleteSingleton = ServiceOperation("DELETE_SINGLETON");
	const ServiceOperation ServiceOperation::UpdateSummary = ServiceOperation("UPDATE_SUMMARY");
	const ServiceOperation ServiceOperation::UpdateSetMinimum = ServiceOperation("UPDATE_SET_MINIMUM");
	const ServiceOperation ServiceOperation::UpdateIncrementToMaximum = ServiceOperation("UPDATE_INCREMENT_TO_MAXIMUM");
	const ServiceOperation ServiceOperation::UpdateEntityIndexedId = ServiceOperation("UPDATE_INDEXED_ID");
	const ServiceOperation ServiceOperation::UpdateEntityOwnerAndAcl = ServiceOperation("UPDATE_ENTITY_OWNER_AND_ACL");
	const ServiceOperation ServiceOperation::MakeSystemEntity = ServiceOperation("MAKE_SYSTEM_ENTITY");

	const ServiceOperation ServiceOperation::GetFriendProfileInfoForExternalId = ServiceOperation("GET_FRIEND_PROFILE_INFO_FOR_EXTERNAL_ID");
	const ServiceOperation ServiceOperation::GetProfileInfoForCredential = ServiceOperation("GET_PROFILE_INFO_FOR_CREDENTIAL");
	const ServiceOperation ServiceOperation::GetProfileInfoForExternalAuthId = ServiceOperation("GET_PROFILE_INFO_FOR_EXTERNAL_AUTH_ID");
	const ServiceOperation ServiceOperation::GetExternalIdForProfileId = ServiceOperation("GET_EXTERNAL_ID_FOR_PROFILE_ID");
	const ServiceOperation ServiceOperation::ReadFriendEntity = ServiceOperation("READ_FRIEND_ENTITY");
	const ServiceOperation ServiceOperation::ReadFriendsEntities = ServiceOperation("READ_FRIENDS_ENTITIES");
	const ServiceOperation ServiceOperation::ReadFriendsWithApplication = ServiceOperation("READ_FRIENDS_WITH_APPLICATION");
	const ServiceOperation ServiceOperation::ReadFriends = ServiceOperation("READ_FRIENDS");
	const ServiceOperation ServiceOperation::ReadFriendsPlayerState = ServiceOperation("READ_FRIEND_PLAYER_STATE");
	const ServiceOperation ServiceOperation::FindPlayerByName = ServiceOperation("FIND_PLAYER_BY_NAME");
	const ServiceOperation ServiceOperation::FindUsersByExactName = ServiceOperation("FIND_USERS_BY_EXACT_NAME");
	const ServiceOperation ServiceOperation::FindUserByExactUniversalId = ServiceOperation("FIND_USER_BY_EXACT_UNIVERSAL_ID");
	const ServiceOperation ServiceOperation::FindUsersByUniversalIdStartingWith= ServiceOperation("FIND_USERS_BY_UNIVERSAL_ID_STARTING_WITH");
	const ServiceOperation ServiceOperation::FindUsersByNameStartingWith= ServiceOperation("FIND_USERS_BY_NAME_STARTING_WITH");
	const ServiceOperation ServiceOperation::FindUsersBySubstrName = ServiceOperation("FIND_USERS_BY_SUBSTR_NAME");
	const ServiceOperation ServiceOperation::ListFriends = ServiceOperation("LIST_FRIENDS");
	const ServiceOperation ServiceOperation::AddFriends = ServiceOperation("ADD_FRIENDS");
	const ServiceOperation ServiceOperation::RemoveFriends = ServiceOperation("REMOVE_FRIENDS");
	const ServiceOperation ServiceOperation::GetUsersOnlineStatus = ServiceOperation("GET_USERS_ONLINE_STATUS");
	const ServiceOperation ServiceOperation::FindPlayerByUniversalId = ServiceOperation("FIND_PLAYER_BY_UNIVERSAL_ID");
	const ServiceOperation ServiceOperation::GetSocialLeaderboard = ServiceOperation("GET_SOCIAL_LEADERBOARD");
	const ServiceOperation ServiceOperation::GetSocialLeaderboardByVersion = ServiceOperation("GET_SOCIAL_LEADERBOARD_BY_VERSION");
	const ServiceOperation ServiceOperation::GetMultiSocialLeaderboard = ServiceOperation("GET_MULTI_SOCIAL_LEADERBOARD");
	const ServiceOperation ServiceOperation::GetGlobalLeaderboard = ServiceOperation("GET_GLOBAL_LEADERBOARD");
	const ServiceOperation ServiceOperation::GetGlobalLeaderboardPage = ServiceOperation("GET_GLOBAL_LEADERBOARD_PAGE");
	const ServiceOperation ServiceOperation::GetGlobalLeaderboardView = ServiceOperation("GET_GLOBAL_LEADERBOARD_VIEW");
	const ServiceOperation ServiceOperation::GetGlobalLeaderboardVersions = ServiceOperation("GET_GLOBAL_LEADERBOARD_VERSIONS");
	const ServiceOperation ServiceOperation::GetCompletedTournament = ServiceOperation("GET_COMPLETED_TOURNAMENT");
	const ServiceOperation ServiceOperation::RewardTournament = ServiceOperation("REWARD_TOURNAMENT");
	const ServiceOperation ServiceOperation::PostScore = ServiceOperation("POST_SCORE");
	const ServiceOperation ServiceOperation::PostScoreDynamic = ServiceOperation("POST_SCORE_DYNAMIC");
	const ServiceOperation ServiceOperation::GetGroupSocialLeaderboard = ServiceOperation("GET_GROUP_SOCIAL_LEADERBOARD");
	const ServiceOperation ServiceOperation::GetGroupSocialLeaderboardByVersion = ServiceOperation("GET_GROUP_SOCIAL_LEADERBOARD_BY_VERSION");
	const ServiceOperation ServiceOperation::PostScoreToGroupLeaderboard = ServiceOperation("POST_GROUP_SCORE");
	const ServiceOperation ServiceOperation::PostScoreToDynamicGroupLeaderboard = ServiceOperation("POST_GROUP_SCORE_DYNAMIC");
	const ServiceOperation ServiceOperation::RemoveGroupScore = ServiceOperation("REMOVE_GROUP_SCORE");
	const ServiceOperation ServiceOperation::GetGroupLeaderboardView = ServiceOperation("GET_GROUP_LEADERBOARD_VIEW");
	const ServiceOperation ServiceOperation::GetSummaryDataForProfileId = ServiceOperation("GET_SUMMARY_DATA_FOR_PROFILE_ID");
	const ServiceOperation ServiceOperation::GetPlayersSocialLeaderboard = ServiceOperation("GET_PLAYERS_SOCIAL_LEADERBOARD");
	const ServiceOperation ServiceOperation::GetPlayersSocialLeaderboardByVersion = ServiceOperation("GET_PLAYERS_SOCIAL_LEADERBOARD_BY_VERSION");
	const ServiceOperation ServiceOperation::ListAllLeaderboards = ServiceOperation("LIST_ALL_LEADERBOARDS");
	const ServiceOperation ServiceOperation::GetGlobalLeaderboardEntryCount = ServiceOperation("GET_GLOBAL_LEADERBOARD_ENTRY_COUNT");
	const ServiceOperation ServiceOperation::RemovePlayerScore = ServiceOperation("REMOVE_PLAYER_SCORE");
	const ServiceOperation ServiceOperation::GetPlayerScore = ServiceOperation("GET_PLAYER_SCORE");
	const ServiceOperation ServiceOperation::GetPlayerScoresFromLeaderboards = ServiceOperation("GET_PLAYER_SCORES_FROM_LEADERBOARDS");

	const ServiceOperation ServiceOperation::InitThirdParty = ServiceOperation("initThirdParty");
	const ServiceOperation ServiceOperation::PostThirdPartyLeaderboardScore = ServiceOperation("postThirdPartyLeaderboardScore");
	const ServiceOperation ServiceOperation::IncrementThirdPartyLeaderboardScore = ServiceOperation("incrementThirdPartyLeaderboardScore");
	const ServiceOperation ServiceOperation::LaunchAchievementUI = ServiceOperation("launchAchievementUI");
	const ServiceOperation ServiceOperation::PostThirdPartyLeaderboardAchievement = ServiceOperation("postThirdPartyLeaderboardAchievement");
	const ServiceOperation ServiceOperation::IsThirdPartyAchievementComplete = ServiceOperation("isThirdPartyAchievementComplete");
	const ServiceOperation ServiceOperation::ResetThirdPartyAchievements = ServiceOperation("resetThirdPartyAchievements");
	const ServiceOperation ServiceOperation::QueryThirdPartyAchievements = ServiceOperation("queryThirdPartyAchievements");

	const ServiceOperation ServiceOperation::GetInventory = ServiceOperation("GET_INVENTORY");
	const ServiceOperation ServiceOperation::CashInReceipt = ServiceOperation("OP_CASH_IN_RECEIPT");
	const ServiceOperation ServiceOperation::AwardVC = ServiceOperation("AWARD_VC");
	const ServiceOperation ServiceOperation::ConsumeVC = ServiceOperation("CONSUME_VC");
	const ServiceOperation ServiceOperation::GetPlayerVC = ServiceOperation("GET_PLAYER_VC");
	const ServiceOperation ServiceOperation::ResetPlayerVC = ServiceOperation("RESET_PLAYER_VC");

	const ServiceOperation ServiceOperation::AwardParentVC = ServiceOperation("AWARD_PARENT_VC");
	const ServiceOperation ServiceOperation::ConsumeParentVC = ServiceOperation("CONSUME_PARENT_VC");
	const ServiceOperation ServiceOperation::GetParentVC = ServiceOperation("GET_PARENT_VC");
	const ServiceOperation ServiceOperation::ResetParentVC = ServiceOperation("RESET_PARENT_VC");

	const ServiceOperation ServiceOperation::Send = ServiceOperation("SEND");
	const ServiceOperation ServiceOperation::UpdateEventData = ServiceOperation("UPDATE_EVENT_DATA");
	const ServiceOperation ServiceOperation::DeleteSent = ServiceOperation("DELETE_SENT");
	const ServiceOperation ServiceOperation::DeleteIncoming = ServiceOperation("DELETE_INCOMING");
	const ServiceOperation ServiceOperation::GetEvents = ServiceOperation("GET_EVENTS");

	const ServiceOperation ServiceOperation::ProcessStatistics = ServiceOperation("PROCESS_STATISTICS");
	const ServiceOperation ServiceOperation::UpdateIncrement = ServiceOperation("UPDATE_INCREMENT");
	const ServiceOperation ServiceOperation::ReadNextXplevel = ServiceOperation("READ_NEXT_XPLEVEL");
	const ServiceOperation ServiceOperation::ReadXpLevels = ServiceOperation("READ_XP_LEVELS");
	const ServiceOperation ServiceOperation::SetXpPoints = ServiceOperation("SET_XPPOINTS");
	const ServiceOperation ServiceOperation::ReadSubset = ServiceOperation("READ_SUBSET");
	const ServiceOperation ServiceOperation::ReadForCategory = ServiceOperation("READ_FOR_CATEGORY");

	const ServiceOperation ServiceOperation::Run = ServiceOperation("RUN");
	const ServiceOperation ServiceOperation::RunPeerScript = ServiceOperation("RUN_PEER_SCRIPT");
	const ServiceOperation ServiceOperation::RunPeerScriptAsync = ServiceOperation("RUN_PEER_SCRIPT_ASYNC");
	const ServiceOperation ServiceOperation::Tweet = ServiceOperation("TWEET");

	const ServiceOperation ServiceOperation::AwardAchievements = ServiceOperation("AWARD_ACHIEVEMENTS");
	const ServiceOperation ServiceOperation::ReadAchievements = ServiceOperation("READ_ACHIEVEMENTS");
	const ServiceOperation ServiceOperation::ReadAchievedAchievements = ServiceOperation("READ_ACHIEVED_ACHIEVEMENTS");

	const ServiceOperation ServiceOperation::SetPlayerRating = ServiceOperation("SET_PLAYER_RATING");
	const ServiceOperation ServiceOperation::ResetPlayerRating = ServiceOperation("RESET_PLAYER_RATING");
	const ServiceOperation ServiceOperation::IncrementPlayerRating = ServiceOperation("INCREMENT_PLAYER_RATING");
	const ServiceOperation ServiceOperation::DecrementPlayerRating = ServiceOperation("DECREMENT_PLAYER_RATING");
	const ServiceOperation ServiceOperation::ShieldOn = ServiceOperation("SHIELD_ON");
	const ServiceOperation ServiceOperation::ShieldOnFor = ServiceOperation("SHIELD_ON_FOR");
	const ServiceOperation ServiceOperation::IncrementShieldOnFor = ServiceOperation("INCREMENT_SHIELD_ON_FOR");
	const ServiceOperation ServiceOperation::ShieldOff = ServiceOperation("SHIELD_OFF");
	const ServiceOperation ServiceOperation::GetShieldExpiry = ServiceOperation("GET_SHIELD_EXPIRY");
	const ServiceOperation ServiceOperation::FindPlayers = ServiceOperation("FIND_PLAYERS");
	const ServiceOperation ServiceOperation::FindPlayersUsingFilter = ServiceOperation("FIND_PLAYERS_USING_FILTER");

	const ServiceOperation ServiceOperation::SubmitTurn = ServiceOperation("SUBMIT_TURN");
	const ServiceOperation ServiceOperation::UpdateMatchSummary = ServiceOperation("UPDATE_SUMMARY");
	const ServiceOperation ServiceOperation::Abandon = ServiceOperation("ABANDON");
	const ServiceOperation ServiceOperation::Complete = ServiceOperation("COMPLETE");
	const ServiceOperation ServiceOperation::ReadMatch = ServiceOperation("READ_MATCH");
	const ServiceOperation ServiceOperation::ReadMatchHistory = ServiceOperation("READ_MATCH_HISTORY");
	const ServiceOperation ServiceOperation::FindMatches = ServiceOperation("FIND_MATCHES");
	const ServiceOperation ServiceOperation::FindMatchesCompleted = ServiceOperation("FIND_MATCHES_COMPLETED");
	const ServiceOperation ServiceOperation::DeleteMatch = ServiceOperation("DELETE_MATCH");

	const ServiceOperation ServiceOperation::LastUploadStatus = ServiceOperation("LAST_UPLOAD_STATUS");

	const ServiceOperation ServiceOperation::ReadQuests = ServiceOperation("READ_QUESTS");
	const ServiceOperation ServiceOperation::ReadCompletedQuests = ServiceOperation("READ_COMPLETED_QUESTS");
	const ServiceOperation ServiceOperation::ReadInProgressQuests = ServiceOperation("READ_IN_PROGRESS_QUESTS");
	const ServiceOperation ServiceOperation::ReadNotStartedQuests = ServiceOperation("READ_NOT_STARTED_QUESTS");
	const ServiceOperation ServiceOperation::ReadQuestsWithStatus = ServiceOperation("READ_QUESTS_WITH_STATUS");
	const ServiceOperation ServiceOperation::ReadQuestsWithBasicPercentage = ServiceOperation("READ_QUESTS_WITH_BASIC_PERCENTAGE");
	const ServiceOperation ServiceOperation::ReadQuestsWithComplexPercentage = ServiceOperation("READ_QUESTS_WITH_COMPLEX_PERCENTAGE");
	const ServiceOperation ServiceOperation::ReadQuestsByCategory = ServiceOperation("READ_QUESTS_BY_CATEGORY");

	const ServiceOperation ServiceOperation::ReadGameStatisticsByCategory = ServiceOperation("READ_GAME_STATISTICS_BY_CATEGORY");
	const ServiceOperation ServiceOperation::ReadPlayerStatisticsByCategory = ServiceOperation("READ_PLAYER_STATISTICS_BY_CATEGORY");

	const ServiceOperation ServiceOperation::ReadMilestones = ServiceOperation("READ_MILESTONES");
	const ServiceOperation ServiceOperation::ReadMilestonesByCategory = ServiceOperation("READ_MILESTONES_BY_CATEGORY");
	const ServiceOperation ServiceOperation::ResetMilestones = ServiceOperation("RESET_MILESTONES");

	const ServiceOperation ServiceOperation::ReadCompletedMilestones = ServiceOperation("READ_COMPLETED_MILESTONES");
	const ServiceOperation ServiceOperation::ReadInProgressMilestones = ServiceOperation("READ_IN_PROGRESS_MILESTONES");

	const ServiceOperation ServiceOperation::Logout = ServiceOperation("LOGOUT");
	const ServiceOperation ServiceOperation::UpdateName = ServiceOperation("UPDATE_NAME");

	const ServiceOperation ServiceOperation::StartMatch = ServiceOperation("START_MATCH");
	const ServiceOperation ServiceOperation::CancelMatch = ServiceOperation("CANCEL_MATCH");
	const ServiceOperation ServiceOperation::CompleteMatch = ServiceOperation("COMPLETE_MATCH");
	const ServiceOperation ServiceOperation::EnableMatchMaking = ServiceOperation("ENABLE_FOR_MATCH");
	const ServiceOperation ServiceOperation::DisableMatchMaking = ServiceOperation("DISABLE_FOR_MATCH");

	const ServiceOperation ServiceOperation::StartStream = ServiceOperation("START_STREAM");
	const ServiceOperation ServiceOperation::ReadStream = ServiceOperation("READ_STREAM");
	const ServiceOperation ServiceOperation::EndStream = ServiceOperation("END_STREAM");
	const ServiceOperation ServiceOperation::DeleteStream = ServiceOperation("DELETE_STREAM");
	const ServiceOperation ServiceOperation::AddEvent = ServiceOperation("ADD_EVENT");
	const ServiceOperation ServiceOperation::GetStreamSummariesForInitiatingPlayer = ServiceOperation("GET_STREAM_SUMMARIES_FOR_INITIATING_PLAYER");
	const ServiceOperation ServiceOperation::GetStreamSummariesForTargetPlayer = ServiceOperation("GET_STREAM_SUMMARIES_FOR_TARGET_PLAYER");
	const ServiceOperation ServiceOperation::GetRecentStreamsForInitiatingPlayer = ServiceOperation("GET_RECENT_STREAMS_FOR_INITIATING_PLAYER");
	const ServiceOperation ServiceOperation::GetRecentStreamsForTargetPlayer = ServiceOperation("GET_RECENT_STREAMS_FOR_TARGET_PLAYER");

	const ServiceOperation ServiceOperation::GetUserInfo = ServiceOperation("GET_USER_INFO");

	const ServiceOperation ServiceOperation::StartSteamTransaction = ServiceOperation("START_STEAM_TRANSACTION");
	const ServiceOperation ServiceOperation::FinalizeSteamTransaction = ServiceOperation("FINALIZE_STEAM_TRANSACTION");
	const ServiceOperation ServiceOperation::VerifyMicrosoftReceipt = ServiceOperation("VERIFY_MICROSOFT_RECEIPT");
	const ServiceOperation ServiceOperation::ConfirmGooglePlayPurchase = ServiceOperation("CONFIRM_GOOGLEPLAY_PURCHASE");
	const ServiceOperation ServiceOperation::EligiblePromotions = ServiceOperation("ELIGIBLE_PROMOTIONS");

	const ServiceOperation ServiceOperation::ReadSharedEntitesList = ServiceOperation("READ_SHARED_ENTITIES_LIST");
	const ServiceOperation ServiceOperation::GetList = ServiceOperation("GET_LIST");
	const ServiceOperation ServiceOperation::GetListByIndexedId = ServiceOperation("GET_LIST_BY_INDEXED_ID");
	const ServiceOperation ServiceOperation::GetListCount = ServiceOperation("GET_LIST_COUNT");
	const ServiceOperation ServiceOperation::GetPage = ServiceOperation("GET_PAGE");
	const ServiceOperation ServiceOperation::GetPageOffset = ServiceOperation("GET_PAGE_BY_OFFSET");
	const ServiceOperation ServiceOperation::IncrementUserEntityData = ServiceOperation("INCREMENT_USER_ENTITY_DATA");
	const ServiceOperation ServiceOperation::IncrementSharedUserEntityData = ServiceOperation("INCREMENT_SHARED_USER_ENTITY_DATA");
	const ServiceOperation ServiceOperation::IncrementGlobalEntityData = ServiceOperation("INCREMENT_GLOBAL_ENTITY_DATA");
	const ServiceOperation ServiceOperation::GetRandomEntitiesMatching = ServiceOperation("GET_RANDOM_ENTITIES_MATCHING");


	const ServiceOperation ServiceOperation::GetAttributes = ServiceOperation("GET_ATTRIBUTES");
	const ServiceOperation ServiceOperation::UpdateAttributes = ServiceOperation("UPDATE_ATTRIBUTES");
	const ServiceOperation ServiceOperation::RemoveAttributes = ServiceOperation("REMOVE_ATTRIBUTES");
	const ServiceOperation ServiceOperation::UpdatePlayerPicture = ServiceOperation("UPDATE_PICTURE_URL");
	const ServiceOperation ServiceOperation::UpdateContactEmail = ServiceOperation("UPDATE_CONTACT_EMAIL");

	const ServiceOperation ServiceOperation::ReadProperties = ServiceOperation("READ_PROPERTIES");

	const ServiceOperation ServiceOperation::GetUpdatedFiles = ServiceOperation("GET_UPDATED_FILES");
	const ServiceOperation ServiceOperation::GetFileList = ServiceOperation("GET_FILE_LIST");

	const ServiceOperation ServiceOperation::ScheduleCloudScript = ServiceOperation("SCHEDULE_CLOUD_SCRIPT");
	const ServiceOperation ServiceOperation::RunParentScript = ServiceOperation("RUN_PARENT_SCRIPT");
	const ServiceOperation ServiceOperation::CancelScheduledScript = ServiceOperation("CANCEL_SCHEDULED_SCRIPT");

	const ServiceOperation ServiceOperation::RedeemCode = ServiceOperation("REDEEM_CODE");
	const ServiceOperation ServiceOperation::GetRedeemedCodes = ServiceOperation("GET_REDEEMED_CODES");

	const ServiceOperation ServiceOperation::CustomPageEvent = ServiceOperation("CUSTOM_PAGE_EVENT");
	const ServiceOperation ServiceOperation::CustomScreenEvent = ServiceOperation("CUSTOM_SCREEN_EVENT");
	const ServiceOperation ServiceOperation::CustomTrackEvent = ServiceOperation("CUSTOM_TRACK_EVENT");

	// profanity
	const ServiceOperation ServiceOperation::ProfanityCheck = ServiceOperation("PROFANITY_CHECK");
	const ServiceOperation ServiceOperation::ProfanityReplaceText = ServiceOperation("PROFANITY_REPLACE_TEXT");
	const ServiceOperation ServiceOperation::ProfanityIdenitfyBadWords = ServiceOperation("PROFANITY_IDENTIFY_BAD_WORDS");

	// file
	const ServiceOperation ServiceOperation::PrepareUserUpload = ServiceOperation("PREPARE_USER_UPLOAD");
	const ServiceOperation ServiceOperation::ListUserFiles = ServiceOperation("LIST_USER_FILES");
	const ServiceOperation ServiceOperation::DeleteUserFiles = ServiceOperation("DELETE_USER_FILES");
	const ServiceOperation ServiceOperation::GetCdnUrl = ServiceOperation("GET_CDN_URL");

	// group
	const ServiceOperation ServiceOperation::AcceptGroupInvitation = ServiceOperation("ACCEPT_GROUP_INVITATION");
	const ServiceOperation ServiceOperation::AddGroupMember = ServiceOperation("ADD_GROUP_MEMBER");
	const ServiceOperation ServiceOperation::ApproveGroupJoinRequest = ServiceOperation("APPROVE_GROUP_JOIN_REQUEST");
	const ServiceOperation ServiceOperation::AutoJoinGroup = ServiceOperation("AUTO_JOIN_GROUP");
	const ServiceOperation ServiceOperation::AutoJoinGroupMulti = ServiceOperation("AUTO_JOIN_GROUP_MULTI");
	const ServiceOperation ServiceOperation::CancelGroupInvitation = ServiceOperation("CANCEL_GROUP_INVITATION");
	const ServiceOperation ServiceOperation::CreateGroup = ServiceOperation("CREATE_GROUP");
	const ServiceOperation ServiceOperation::CreateGroupEntity = ServiceOperation("CREATE_GROUP_ENTITY");
	const ServiceOperation ServiceOperation::DeleteGroup = ServiceOperation("DELETE_GROUP");
	const ServiceOperation ServiceOperation::DeleteGroupEntity = ServiceOperation("DELETE_GROUP_ENTITY");
	const ServiceOperation ServiceOperation::DeleteGroupMemeber = ServiceOperation("DELETE_MEMBER_FROM_GROUP");
	const ServiceOperation ServiceOperation::GetMyGroups = ServiceOperation("GET_MY_GROUPS");
	const ServiceOperation ServiceOperation::IncrementGroupData = ServiceOperation("INCREMENT_GROUP_DATA");
	const ServiceOperation ServiceOperation::IncrementGroupEntityData = ServiceOperation("INCREMENT_GROUP_ENTITY_DATA");
	const ServiceOperation ServiceOperation::InviteGroupMember = ServiceOperation("INVITE_GROUP_MEMBER");
	const ServiceOperation ServiceOperation::JoinGroup = ServiceOperation("JOIN_GROUP");
	const ServiceOperation ServiceOperation::LeaveGroup = ServiceOperation("LEAVE_GROUP");
	const ServiceOperation ServiceOperation::ListGroupsPage = ServiceOperation("LIST_GROUPS_PAGE");
	const ServiceOperation ServiceOperation::ListGroupsPageByOffset = ServiceOperation("LIST_GROUPS_PAGE_BY_OFFSET");
	const ServiceOperation ServiceOperation::ListGroupsWithMember = ServiceOperation("LIST_GROUPS_WITH_MEMBER");
	const ServiceOperation ServiceOperation::ReadGroup = ServiceOperation("READ_GROUP");
	const ServiceOperation ServiceOperation::ReadGroupData = ServiceOperation("READ_GROUP_DATA");
	const ServiceOperation ServiceOperation::ReadGroupEntitiesPage = ServiceOperation("READ_GROUP_ENTITIES_PAGE");
	const ServiceOperation ServiceOperation::ReadGroupEntitiesPageByOffset = ServiceOperation("READ_GROUP_ENTITIES_PAGE_BY_OFFSET");
	const ServiceOperation ServiceOperation::ReadGroupEntity = ServiceOperation("READ_GROUP_ENTITY");
	const ServiceOperation ServiceOperation::ReadGroupMembers = ServiceOperation("READ_GROUP_MEMBERS");
	const ServiceOperation ServiceOperation::RejectGroupInvitation = ServiceOperation("REJECT_GROUP_INVITATION");
	const ServiceOperation ServiceOperation::RejectGroupJoinRequest = ServiceOperation("REJECT_GROUP_JOIN_REQUEST");
	const ServiceOperation ServiceOperation::RemoveGroupMember = ServiceOperation("REMOVE_GROUP_MEMBER");
	const ServiceOperation ServiceOperation::UpdateGroupData = ServiceOperation("UPDATE_GROUP_DATA");
	const ServiceOperation ServiceOperation::UpdateGroupEntity = ServiceOperation("UPDATE_GROUP_ENTITY_DATA");
	const ServiceOperation ServiceOperation::UpdateGroupMember = ServiceOperation("UPDATE_GROUP_MEMBER");
	const ServiceOperation ServiceOperation::UpdateGroupName = ServiceOperation("UPDATE_GROUP_NAME");
	const ServiceOperation ServiceOperation::SetGroupOpen = ServiceOperation("SET_GROUP_OPEN");
	const ServiceOperation ServiceOperation::GetRandomGroupsMatching = ServiceOperation("GET_RANDOM_GROUPS_MATCHING");
	const ServiceOperation ServiceOperation::UpdateGroupSummaryData = ServiceOperation("UPDATE_GROUP_SUMMARY_DATA");

	//tournament
	const ServiceOperation ServiceOperation::GetTournamentStatus = ServiceOperation("GET_TOURNAMENT_STATUS");
	const ServiceOperation ServiceOperation::GetDivisionInfo = ServiceOperation("GET_DIVISION_INFO");
	const ServiceOperation ServiceOperation::GetMyDivisions = ServiceOperation("GET_MY_DIVISIONS");
	const ServiceOperation ServiceOperation::JoinDivision = ServiceOperation("JOIN_DIVISION");
	const ServiceOperation ServiceOperation::JoinTournament = ServiceOperation("JOIN_TOURNAMENT");
	const ServiceOperation ServiceOperation::LeaveDivisionInstance = ServiceOperation("LEAVE_DIVISION_INSTANCE");
	const ServiceOperation ServiceOperation::LeaveTournament = ServiceOperation("LEAVE_TOURNAMENT");
	const ServiceOperation ServiceOperation::PostTournamentScore = ServiceOperation("POST_TOURNAMENT_SCORE");
	const ServiceOperation ServiceOperation::PostTournamentScoreWithResults = ServiceOperation("POST_TOURNAMENT_SCORE_WITH_RESULTS");
	const ServiceOperation ServiceOperation::ViewCurrentReward = ServiceOperation("VIEW_CURRENT_REWARD");
	const ServiceOperation ServiceOperation::ViewReward = ServiceOperation("VIEW_REWARD");
	const ServiceOperation ServiceOperation::ClaimTournamentReward = ServiceOperation("CLAIM_TOURNAMENT_REWARD");

	//mail
	const ServiceOperation ServiceOperation::SendBasicEmail = ServiceOperation("SEND_BASIC_EMAIL");
	const ServiceOperation ServiceOperation::SendAdvancedEmail = ServiceOperation("SEND_ADVANCED_EMAIL");
	const ServiceOperation ServiceOperation::SendAdvancedEmailByAddress = ServiceOperation("SEND_ADVANCED_EMAIL_BY_ADDRESS");

	//rtt registration
	const ServiceOperation ServiceOperation::RequestClientConnection = ServiceOperation("REQUEST_CLIENT_CONNECTION");

	//chat
	const ServiceOperation ServiceOperation::ChannelConnect = ServiceOperation("CHANNEL_CONNECT");
	const ServiceOperation ServiceOperation::ChannelDisconnect = ServiceOperation("CHANNEL_DISCONNECT");
	const ServiceOperation ServiceOperation::DeleteChatMessage = ServiceOperation("DELETE_CHAT_MESSAGE");
	const ServiceOperation ServiceOperation::GetChannelId = ServiceOperation("GET_CHANNEL_ID");
	const ServiceOperation ServiceOperation::GetChannelInfo = ServiceOperation("GET_CHANNEL_INFO");
	const ServiceOperation ServiceOperation::GetChatMessage = ServiceOperation("GET_CHAT_MESSAGE");
	const ServiceOperation ServiceOperation::GetRecentChatMessages = ServiceOperation("GET_RECENT_CHAT_MESSAGES");
	const ServiceOperation ServiceOperation::GetSubscribedChannels = ServiceOperation("GET_SUBSCRIBED_CHANNELS");
	const ServiceOperation ServiceOperation::PostChatMessage = ServiceOperation("POST_CHAT_MESSAGE");
	const ServiceOperation ServiceOperation::UpdateChatMessage = ServiceOperation("UPDATE_CHAT_MESSAGE");

	//lobby
	const ServiceOperation ServiceOperation::GetRegionsForLobbies = ServiceOperation("GET_REGIONS_FOR_LOBBIES");
	const ServiceOperation ServiceOperation::PingRegions = ServiceOperation("PING_REGIONS");
	const ServiceOperation ServiceOperation::CreateLobby = ServiceOperation("CREATE_LOBBY");
	const ServiceOperation ServiceOperation::CreateLobbyWithPingData = ServiceOperation("CREATE_LOBBY_WITH_PING_DATA");
	const ServiceOperation ServiceOperation::FindLobby = ServiceOperation("FIND_LOBBY");
	const ServiceOperation ServiceOperation::FindLobbyWithPingData = ServiceOperation("FIND_LOBBY_WITH_PING_DATA");
	const ServiceOperation ServiceOperation::FindOrCreateLobby = ServiceOperation("FIND_OR_CREATE_LOBBY");
	const ServiceOperation ServiceOperation::FindOrCreateLobbyWithPingData = ServiceOperation("FIND_OR_CREATE_LOBBY_WITH_PING_DATA");
	const ServiceOperation ServiceOperation::GetLobbyData = ServiceOperation("GET_LOBBY_DATA");
	const ServiceOperation ServiceOperation::LeaveLobby = ServiceOperation("LEAVE_LOBBY");
	const ServiceOperation ServiceOperation::JoinLobby = ServiceOperation("JOIN_LOBBY");
	const ServiceOperation ServiceOperation::JoinLobbyWithPingData = ServiceOperation("JOIN_LOBBY_WITH_PING_DATA");
	const ServiceOperation ServiceOperation::RemoveMember = ServiceOperation("REMOVE_MEMBER");
	const ServiceOperation ServiceOperation::SendSignal = ServiceOperation("SEND_SIGNAL");
	const ServiceOperation ServiceOperation::SwitchTeam = ServiceOperation("SWITCH_TEAM");
	const ServiceOperation ServiceOperation::UpdateReady = ServiceOperation("UPDATE_READY");
	const ServiceOperation ServiceOperation::UpdateSettings = ServiceOperation("UPDATE_SETTINGS");
	const ServiceOperation ServiceOperation::CancelFindRequest = ServiceOperation("CANCEL_FIND_REQUEST");

	//messaging
	const ServiceOperation ServiceOperation::DeleteMessages = ServiceOperation("DELETE_MESSAGES");
	const ServiceOperation ServiceOperation::GetMessageboxes = ServiceOperation("GET_MESSAGE_BOXES");
	const ServiceOperation ServiceOperation::GetMessageCounts = ServiceOperation("GET_MESSAGE_COUNTS");
	const ServiceOperation ServiceOperation::GetMessages = ServiceOperation("GET_MESSAGES");
	const ServiceOperation ServiceOperation::GetMessagesPage = ServiceOperation("GET_MESSAGES_PAGE");
	const ServiceOperation ServiceOperation::GetMessagesPageOffset = ServiceOperation("GET_MESSAGES_PAGE_OFFSET");
	const ServiceOperation ServiceOperation::MarkMessagesRead = ServiceOperation("MARK_MESSAGES_READ");
	const ServiceOperation ServiceOperation::MessagingSendMessage = ServiceOperation("SEND_MESSAGE");
	const ServiceOperation ServiceOperation::SendMessageSimple = ServiceOperation("SEND_MESSAGE_SIMPLE");

	//presence
	const ServiceOperation ServiceOperation::ForcePush = ServiceOperation("FORCE_PUSH");
	const ServiceOperation ServiceOperation::GetPresenceOfFriends = ServiceOperation("GET_PRESENCE_OF_FRIENDS");
	const ServiceOperation ServiceOperation::GetPresenceOfGroup = ServiceOperation("GET_PRESENCE_OF_GROUP");
	const ServiceOperation ServiceOperation::GetPresenceOfUsers = ServiceOperation("GET_PRESENCE_OF_USERS");
	const ServiceOperation ServiceOperation::RegisterListenersForFriends = ServiceOperation("REGISTER_LISTENERS_FOR_FRIENDS");
	const ServiceOperation ServiceOperation::RegisterListenersForGroup = ServiceOperation("REGISTER_LISTENERS_FOR_GROUP");
	const ServiceOperation ServiceOperation::RegisterListenersForProfiles = ServiceOperation("REGISTER_LISTENERS_FOR_PROFILES");
	const ServiceOperation ServiceOperation::SetVisibility = ServiceOperation("SET_VISIBILITY");
	const ServiceOperation ServiceOperation::StopListening = ServiceOperation("STOP_LISTENING");
	const ServiceOperation ServiceOperation::UpdateActivity = ServiceOperation("UPDATE_ACTIVITY");

	//virtual currency
	const ServiceOperation ServiceOperation::VirtualCurrencyGetCurrency = ServiceOperation("GET_PLAYER_VC");
	const ServiceOperation ServiceOperation::VirtualCurrencyGetParentCurrency = ServiceOperation("GET_PARENT_VC");
	const ServiceOperation ServiceOperation::VirtualCurrencyGetPeerCurrency = ServiceOperation("GET_PEER_VC");
	const ServiceOperation ServiceOperation::VirtualCurrencyResetCurrency = ServiceOperation("RESET_PLAYER_VC");

	//app store
	const ServiceOperation ServiceOperation::AppStoreVerifyPurchase = ServiceOperation("VERIFY_PURCHASE");
	const ServiceOperation ServiceOperation::AppStoreGetEligiblePromotions = ServiceOperation("ELIGIBLE_PROMOTIONS");
	const ServiceOperation ServiceOperation::AppStoreGetSalesInventory = ServiceOperation("GET_INVENTORY");
	const ServiceOperation ServiceOperation::AppStoreStartPurchase = ServiceOperation("START_PURCHASE");
	const ServiceOperation ServiceOperation::AppStoreFinalizePurchase = ServiceOperation("FINALIZE_PURCHASE");

	//UserItems
	const ServiceOperation ServiceOperation::AwardUserItem = ServiceOperation("AWARD_USER_ITEM");
	const ServiceOperation ServiceOperation::DropUserItem = ServiceOperation("DROP_USER_ITEM");
	const ServiceOperation ServiceOperation::GetUserItemsPage = ServiceOperation("GET_USER_ITEMS_PAGE");
	const ServiceOperation ServiceOperation::GetUserItemsPageOffset = ServiceOperation("GET_USER_ITEMS_PAGE_OFFSET");
	const ServiceOperation ServiceOperation::GetUserItem = ServiceOperation("GET_USER_ITEM");
	const ServiceOperation ServiceOperation::GiveUserItemTo = ServiceOperation("GIVE_USER_ITEM_TO");
	const ServiceOperation ServiceOperation::PurchaseUserItem = ServiceOperation("PURCHASE_USER_ITEM");
	const ServiceOperation ServiceOperation::ReceiveUserItemFrom = ServiceOperation("RECEIVE_USER_ITEM_FROM");
	const ServiceOperation ServiceOperation::SellUserItem = ServiceOperation("SELL_USER_ITEM");
	const ServiceOperation ServiceOperation::UpdateUserItemData = ServiceOperation("UPDATE_USER_ITEM_DATA");
	const ServiceOperation ServiceOperation::UseUserItem = ServiceOperation("USE_USER_ITEM");
	const ServiceOperation ServiceOperation::PublishUserItemToBlockchain = ServiceOperation("PUBLISH_USER_ITEM_TO_BLOCKCHAIN");
	const ServiceOperation ServiceOperation::RefreshBlockchainUserItems = ServiceOperation("REFRESH_BLOCKCHAIN_USER_ITEMS");
	const ServiceOperation ServiceOperation::RemoveUserItemFromBlockchain = ServiceOperation("REMOVE_USER_ITEM_FROM_BLOCKCHAIN");

	//itemCatalog
	const ServiceOperation ServiceOperation::GetCatalogItemDefinition = ServiceOperation("GET_CATALOG_ITEM_DEFINITION");
	const ServiceOperation ServiceOperation::GetCatalogItemsPage = ServiceOperation("GET_CATALOG_ITEMS_PAGE");
	const ServiceOperation ServiceOperation::GetCatalogItemsPageOffset = ServiceOperation("GET_CATALOG_ITEMS_PAGE_OFFSET");

	//custom entity
	const ServiceOperation ServiceOperation::CreateEntity = ServiceOperation("CREATE_ENTITY");
	const ServiceOperation ServiceOperation::DeleteEntity = ServiceOperation("DELETE_ENTITY");
	const ServiceOperation ServiceOperation::GetCount = ServiceOperation("GET_COUNT");
	const ServiceOperation ServiceOperation::ReadEntity = ServiceOperation("READ_ENTITY");
	const ServiceOperation ServiceOperation::UpdateEntity = ServiceOperation("UPDATE_ENTITY");
	const ServiceOperation ServiceOperation::UpdateEntityFields = ServiceOperation("UPDATE_ENTITY_FIELDS");
	const ServiceOperation ServiceOperation::GetEntityPage = ServiceOperation("GET_PAGE");
	const ServiceOperation ServiceOperation::GetCustomEntityPage = ServiceOperation("GET_ENTITY_PAGE");
	const ServiceOperation ServiceOperation::GetEntityPageOffset = ServiceOperation("GET_ENTITY_PAGE_OFFSET");

	const ServiceOperation ServiceOperation::SubmitCrashReport = ServiceOperation("SEND_CRASH_REPORT");

	const ServiceOperation ServiceOperation::ClearUserStatus = ServiceOperation("CLEAR_USER_STATUS");
	const ServiceOperation ServiceOperation::ExtendUserStatus = ServiceOperation("EXTEND_USER_STATUS");
	const ServiceOperation ServiceOperation::GetUserStatus = ServiceOperation("GET_USER_STATUS");
	const ServiceOperation ServiceOperation::SetUserStatus = ServiceOperation("SET_USER_STATUS");

	const ServiceOperation ServiceOperation::AttachBlockchainIdentity = ServiceOperation("ATTACH_BLOCKCHAIN_IDENTITY");
	const ServiceOperation ServiceOperation::DetachBlockchainIdentity = ServiceOperation("DETACH_BLOCKCHAIN_IDENTITY");
	const ServiceOperation ServiceOperation::CompleteMatchWithSummaryData = ServiceOperation("COMPLETE_MATCH_WITH_SUMMARY_DATA");
	const ServiceOperation ServiceOperation::AbandonMatchWithSummaryData = ServiceOperation("ABANDON_MATCH_WITH_SUMMARY_DATA");

	ServiceOperation::ServiceOperation(const char * value)
	{
		_value = value;
	}

	bool ServiceOperation::operator== (const ServiceOperation& s) const
	{
		return _value == s.getValue();
	}

	bool ServiceOperation::operator!= (const ServiceOperation& s) const
	{
		return _value != s.getValue();
	}

	void ServiceOperation::operator= (const ServiceOperation& s)
	{
		_value = s.getValue();
	}

}
