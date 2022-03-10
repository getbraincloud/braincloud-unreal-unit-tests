// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#pragma once
class BCCLIENTPLUGIN_API ReasonCodes
{
  public:
    // Error codes
    static const int32 NO_REASON_CODE = 0;

    static const int32 INVALID_NOTIFICATION = 20200;

    static const int32 INVALID_REQUEST = 40001;

    // 402
    static const int32 SWITCHING_FACEBOOK_MEMORY = 40201;
    static const int32 MERGING_MEMORY = 40202;
    static const int32 RESETING_MEMORY = 40203;
    static const int32 MOVING_ANONYMOUS_MEMORY = 40204;
    static const int32 LOGIN_SECURITY_ERROR = 40205;
    static const int32 MISSING_IDENTITY_ERROR = 40206;
    static const int32 SWITCHING_PROFILES = 40207;
    static const int32 MISSING_PROFILE_ERROR = 40208;

    static const int32 SECURITY_ERROR = 40209;
    static const int32 DOWNGRADING_TO_ANONYMOUS_ERROR = 40210;
    static const int32 DUPLICATE_IDENTITY_TYPE = 40211;
    static const int32 MERGE_PROFILES = 40212;
    static const int32 INVALID_PROPERTY_NAME = 40213;
    static const int32 EMAIL_NOT_VALIDATED = 40214;
    static const int32 DATABASE_ERROR = 40215;
    static const int32 PROPERTY_NOT_OVERRIDEABLE = 40216;
    static const int32 UNKNOWN_AUTH_ERROR = 40217;
	static const int32 DATABASE_DUP_KEY_ERROR = 40220;
	static const int32 EMAIL_NOT_VALID = 40221;
	
    // Forbidden (403)...
    static const int32 UNABLE_TO_GET_FRIENDS_FROM_FACEBOOK = 40300;
    static const int32 BAD_SIGNATURE = 40301;
    static const int32 UNABLE_TO_VALIDATE_PLAYER = 40302;
    static const int32 UNABLE_TO_VALIDATE_USER = UNABLE_TO_VALIDATE_PLAYER;
    static const int32 PLAYER_SESSION_EXPIRED = 40303;
    static const int32 USER_SESSION_EXPIRED = PLAYER_SESSION_EXPIRED;
    static const int32 NO_SESSION = 40304;
    static const int32 PLAYER_SESSION_MISMATCH = 40305;
    static const int32 USER_SESSION_MISMATCH = PLAYER_SESSION_MISMATCH;
    static const int32 OPERATION_REQUIRES_A_SESSION = 40306;
    static const int32 TOKEN_DOES_NOT_MATCH_USER = 40307;
	static const int32 MANUAL_REDIRECT = 40308;
    static const int32 EVENT_CAN_ONLY_SEND_TO_FRIEND_OR_SELF = 40309;
    static const int32 NOT_FRIENDS = 40310;
    static const int32 VC_BALANCE_CANNOT_BE_SPECIFIED = 40311;
    static const int32 VC_LIMIT_EXCEEDED = 40312;
    static const int32 UNABLE_TO_GET_MY_DATA_FROM_FACEBOOK = 40313;
	static const int32 TLS_VERSION_INVALID = 40314;
    static const int32 INVALID_AUTHENTICATION_TYPE = 40315;
    static const int32 INVALID_GAME_ID = 40316;
    static const int32 INVALID_APP_ID = INVALID_GAME_ID;

    // This product and receipt have already been claimed
    static const int32 APPLE_TRANS_ID_ALREADY_CLAIMED = 40317;
    // @deprecated - use APPLE_TRANS_ID_ALREADY_CLAIMED
    static const int32 ITUNES_PURCHASE_ALREADY_CLAIMED = APPLE_TRANS_ID_ALREADY_CLAIMED;

    // 400 Bad version
    static const int32 CLIENT_VERSION_NOT_SUPPORTED = 40318;
    static const int32 BRAINCLOUD_VERSION_NOT_SUPPORTED = 40319;
    static const int32 PLATFORM_NOT_SUPPORTED = 40320;

    static const int32 INVALID_PLAYER_STATISTICS_EVENT_NAME = 40321;
    static const int32 INVALID_USER_STATISTICS_EVENT_NAME = INVALID_PLAYER_STATISTICS_EVENT_NAME;

    // App Version No Longer Supported
    static const int32 GAME_VERSION_NOT_SUPPORTED = 40322;
    static const int32 APP_VERSION_NOT_SUPPORTED = GAME_VERSION_NOT_SUPPORTED;
    // @deprecated - use APP_VERSION_NOT_SUPPORTED
    static const int32 APP_VERSION_NO_LONGER_SUPPORTED = GAME_VERSION_NOT_SUPPORTED;

    static const int32 BAD_REFERENCE_DATA = 40324;
    static const int32 MISSING_OAUTH_TOKEN = 40325;
    static const int32 MISSING_OAUTH_VERIFIER = 40326;
    static const int32 MISSING_OAUTH_TOKEN_SECRET = 40327;
    static const int32 MISSING_TWEET = 40328;
    static const int32 FACEBOOK_PAYMENT_ID_ALREADY_PROCESSED = 40329;
    static const int32 DISABLED_GAME = 40330;
    static const int32 DISABLED_APP = DISABLED_GAME;
    static const int32 MATCH_MAKING_DISABLED = 40331;
    static const int32 UPDATE_FAILED = 40332;
    static const int32 INVALID_OPERATION = 40333; // invalid operation for API call
    static const int32 MATCH_RANGE_ERROR = 40334;
    static const int32 PLAYER_IN_MATCH = 40335;
    static const int32 MATCH_PLAYER_SHIELDED = 40336;
    static const int32 MATCH_PLAYER_MISSING = 40337;
    static const int32 MATCH_PLAYER_LOGGED_IN = 40338;
    static const int32 INVALID_ITEM_ID = 40339;
    static const int32 MISSING_PRICE = 40340;
    static const int32 MISSING_USER_INFO = 40341;
    static const int32 MISSING_STEAM_RESPONSE = 40342;
    static const int32 MISSING_STEAM_TRANSACTION = 40343;
    static const int32 ENTITY_VERSION_MISMATCH = 40344;
    static const int32 MISSING_RECORD = 40345;
    static const int32 INSUFFICIENT_PERMISSIONS = 40346;
    static const int32 MISSING_IN_QUERY = 40347;
    static const int32 RECORD_EXPIRED = 40348;
    static const int32 INVALID_WHERE = 40349;
    static const int32 S3_ERROR = 40350;
    static const int32 INVALID_ATTRIBUTES = 40351;
    static const int32 IMPORT_MISSING_GAME_DATA = 40352;
    static const int32 IMPORT_MISSING_APP_DATA = IMPORT_MISSING_GAME_DATA;
    static const int32 IMPORT_SCHEMA_VERSION_TOO_OLD = 40353;
    static const int32 IMPORT_SCHEMA_VERSION_INVALID = 40355;
    static const int32 PLAYER_SESSION_LOGGED_OUT = 40356;
    static const int32 USER_SESSION_LOGGED_OUT = PLAYER_SESSION_LOGGED_OUT;
    static const int32 API_HOOK_SCRIPT_ERROR = 40357;
    static const int32 MISSING_REQUIRED_PARAMETER = 40358;
    static const int32 INVALID_PARAMETER_TYPE = 40359;
    static const int32 INVALID_IDENTITY_TYPE = 40360;
    static const int32 EMAIL_SEND_ERROR = 40361;
    static const int32 CHILD_ENTITY_PARTIAL_UPDATE_INVALID_DATA = 40362;
    static const int32 MISSING_SCRIPT = 40363;
    static const int32 SCRIPT_SECURITY_ERROR = 40364;
    static const int32 SERVER_SESSION_EXPIRED = 40365;
    static const int32 STREAM_DOES_NOT_EXIT = 40366;
    static const int32 STREAM_ACCESS_ERROR = 40367;
    static const int32 STREAM_COMPLETE = 40368;
    static const int32 INVALID_STATISTIC_NAME = 40369;
    static const int32 INVALID_HTTP_REQUEST = 40370;
    static const int32 GAME_LIMIT_REACHED = 40371;
    static const int32 APP_LIMIT_REACHED = GAME_LIMIT_REACHED;
    static const int32 GAME_RUNSTATE_DISABLED = 40372;
    static const int32 APP_RUNSTATE_DISABLED = GAME_RUNSTATE_DISABLED;
    static const int32 INVALID_COMPANY_ID = 40373;
    static const int32 INVALID_PLAYER_ID = 40374;
    static const int32 INVALID_USER_ID = INVALID_PLAYER_ID;
    static const int32 INVALID_TEMPLATE_ID = 40375;
    static const int32 MINIMUM_SEARCH_INPUT = 40376;
    static const int32 MISSING_GAME_PARENT = 40377;
    static const int32 MISSING_APP_PARENT = MISSING_GAME_PARENT;
    static const int32 GAME_PARENT_MISMATCH = 40378;
    static const int32 APP_PARENT_MISMATCH = GAME_PARENT_MISMATCH;
    static const int32 CHILD_PLAYER_MISSING = 40379;
    static const int32 CHILD_USER_MISSING = CHILD_PLAYER_MISSING;
    static const int32 MISSING_PLAYER_PARENT = 40380;
    static const int32 MISSING_USER_PARENT = MISSING_PLAYER_PARENT;
    static const int32 PLAYER_PARENT_MISMATCH = 40381;
    static const int32 USER_PARENT_MISMATCH = PLAYER_PARENT_MISMATCH;
    static const int32 MISSING_PLAYER_ID = 40382;
    static const int32 MISSING_USER_ID = MISSING_PLAYER_ID;
    static const int32 DECODE_CONTEXT = 40383;
    static const int32 INVALID_QUERY_CONTEXT = 40384;
    static const int32 GROUP_MEMBER_NOT_FOUND = 40385;
    static const int32 INVALID_SORT = 40386;
    static const int32 GAME_NOT_FOUND = 40387;
    static const int32 APP_NOT_FOUND = GAME_NOT_FOUND;
    static const int32 GAMES_NOT_IN_SAME_COMPANY = 40388;
    static const int32 APPS_NOT_IN_SAME_COMPANY = GAMES_NOT_IN_SAME_COMPANY;
    static const int32 IMPORT_NO_PARENT_ASSIGNED = 40389;
    static const int32 IMPORT_PARENT_CURRENCIES_MISMATCH = 40390;
    static const int32 INVALID_SUBSTITUION_ENTRY = 40391;
    static const int32 INVALID_TEMPLATE_STRING = 40392;
    static const int32 TEMPLATE_SUBSTITUTION_ERROR = 40393;
    static const int32 INVALID_OPPONENTS = 40394;
    static const int32 REDEMPTION_CODE_NOT_FOUND = 40395;
    static const int32 REDEMPTION_CODE_VERSION_MISMATCH = 40396;
    static const int32 REDEMPTION_CODE_ACTIVE = 40397;
    static const int32 REDEMPTION_CODE_NOT_ACTIVE = 40398;
    static const int32 REDEMPTION_CODE_TYPE_NOT_FOUND = 40399;
    static const int32 REDEMPTION_CODE_INVALID = 40400;
    static const int32 REDEMPTION_CODE_REDEEMED = 40401;
    static const int32 REDEMPTION_CODE_REDEEMED_BY_SELF = 40402;
    static const int32 REDEMPTION_CODE_REDEEMED_BY_OTHER = 40403;
    static const int32 SCRIPT_EMPTY = 40404;
    static const int32 ITUNES_COMMUNICATION_ERROR = 40405;
    static const int32 ITUNES_NO_RESPONSE = 40406;
    static const int32 ITUNES_RESPONSE_NOT_OK = 40407;
    static const int32 JSON_PARSING_ERROR = 40408;
    static const int32 ITUNES_NULL_RESPONSE = 40409;
    static const int32 ITUNES_RESPONSE_WITH_NULL_STATUS = 40410;
    static const int32 ITUNES_STATUS_BAD_JSON_RECEIPT = 40411;
    static const int32 ITUNES_STATUS_BAD_RECEIPT = 40412;
    static const int32 ITUNES_STATUS_RECEIPT_NOT_AUTHENTICATED = 40413;
    static const int32 ITUNES_STATUS_BAD_SHARED_SECRET = 40414;
    static const int32 ITUNES_STATUS_RECEIPT_SERVER_UNAVAILABLE = 40415;
    static const int32 ITUNES_RECEIPT_MISSING_ITUNES_PRODUCT_ID = 40416;
    static const int32 PRODUCT_NOT_FOUND_FOR_ITUNES_PRODUCT_ID = 40417;
    static const int32 DATA_STREAM_EVENTS_NOT_ENABLED = 40418;
    static const int32 INVALID_DEVICE_TOKEN = 40419;
    static const int32 ERROR_DELETING_DEVICE_TOKEN = 40420;
    static const int32 WEBPURIFY_NOT_CONFIGURED = 40421;
    static const int32 WEBPURIFY_EXCEPTION = 40422;
    static const int32 WEBPURIFY_FAILURE = 40423;
    static const int32 WEBPURIFY_NOT_ENABLED = 40424;
    static const int32 NAME_CONTAINS_PROFANITY = 40425;
    static const int32 NULL_SESSION = 40426;
    static const int32 PURCHASE_ALREADY_VERIFIED = 40427;
    static const int32 GOOGLE_IAP_NOT_CONFIGURED = 40428;
    static const int32 UPLOAD_FILE_TOO_LARGE = 40429;
    static const int32 FILE_ALREADY_EXISTS = 40430;
    static const int32 CLOUD_STORAGE_SERVICE_ERROR = 40431;
    static const int32 FILE_DOES_NOT_EXIST = 40432;
    static const int32 UPLOAD_ID_MISSING = 40433;
    static const int32 UPLOAD_JOB_MISSING = 40434;
    static const int32 UPLOAD_JOB_EXPIRED = 40435;
    static const int32 UPLOADER_EXCEPTION = 40436;
    static const int32 UPLOADER_FILESIZE_MISMATCH = 40437;
    static const int32 PUSH_NOTIFICATIONS_NOT_CONFIGURED = 40438;
    static const int32 MATCHMAKING_FILTER_SCRIPT_FAILURE = 40439;
    static const int32 ACCOUNT_ALREADY_EXISTS = 40440;
    static const int32 PROFILE_ALREADY_EXISTS = 40441;
    static const int32 MISSING_NOTIFICATION_BODY = 40442;
    static const int32 INVALID_SERVICE_CODE = 40443;
    static const int32 IP_ADDRESS_BLOCKED = 40444;
    static const int32 UNAPPROVED_SERVICE_CODE = 40445;
    static const int32 PROFILE_NOT_FOUND = 40446;
    static const int32 ENTITY_NOT_SHARED = 40447;
    static const int32 SELF_FRIEND = 40448;
    static const int32 PARSE_NOT_CONFIGURED = 40449;
    static const int32 PARSE_NOT_ENABLED = 40450;
    static const int32 PARSE_REQUEST_ERROR = 40451;
    static const int32 GROUP_CANNOT_ADD_OWNER = 40452;
    static const int32 NOT_GROUP_MEMBER = 40453;
    static const int32 INVALID_GROUP_ROLE = 40454;
    static const int32 GROUP_OWNER_DELETE = 40455;
    static const int32 NOT_INVITED_GROUP_MEMBER = 40456;
    static const int32 GROUP_IS_FULL = 40457;
    static const int32 GROUP_OWNER_CANNOT_LEAVE = 40458;
    static const int32 INVALID_INCREMENT_VALUE = 40459;
    static const int32 GROUP_VERSION_MISMATCH = 40460;
    static const int32 GROUP_ENTITY_VERSION_MISMATCH = 40461;
    static const int32 INVALID_GROUP_ID = 40462;
    static const int32 INVALID_FIELD_NAME = 40463;
    static const int32 UNSUPPORTED_AUTH_TYPE = 40464;
    static const int32 CLOUDCODE_JOB_NOT_FOUND = 40465;
    static const int32 CLOUDCODE_JOB_NOT_SCHEDULED = 40466;
    static const int32 GROUP_TYPE_NOT_FOUND = 40467;
    static const int32 MATCHING_GROUPS_NOT_FOUND = 40468;
    static const int32 GENERATE_CDN_URL_ERROR = 40469;
    static const int32 INVALID_PROFILE_IDS = 40470;
    static const int32 MAX_PROFILE_IDS_EXCEEDED = 40471;
    static const int32 PROFILE_ID_MISMATCH = 40472;
    static const int32 LEADERBOARD_DOESNOT_EXIST = 40473;
    static const int32 APP_LICENSING_EXCEEDED = 40474;
    static const int32 SENDGRID_NOT_INSTALLED = 40475;
    static const int32 SENDGRID_EMAIL_SEND_ERROR = 40476;
    static const int32 SENDGRID_NOT_ENABLED_FOR_APP = 40477;
    static const int32 SENDGRID_GET_TEMPLATES_ERROR = 40478;
    static const int32 SENDGRID_INVALID_API_KEY = 40479;
    static const int32 EMAIL_SERVICE_NOT_CONFIGURED = 40480;
    static const int32 INVALID_EMAIL_TEMPLATE_TYPE = 40481;
    static const int32 SENDGRID_KEY_EMPTY_OR_NULL = 40482;
    static const int32 BODY_TEMPLATE_CANNOT_COEXIST = 40483;
    static const int32 SUBSTITUTION_BODY_CANNOT_COEXIST = 40484;
    static const int32 INVALID_FROM_ADDRESS = 40485;
    static const int32 INVALID_FROM_NAME = 40486;
    static const int32 INVALID_REPLY_TO_ADDRESS = 40487;
    static const int32 INVALID_REPLY_TO_NAME = 40488;
    static const int32 FROM_NAME_WITHOUT_FROM_ADDRESS = 40489;
    static const int32 REPLY_TO_NAME_WITHOUT_REPLY_TO_ADDRESS = 40490;
    static const int32 CURRENCY_SECURITY_ERROR = 40491;
    static const int32 INVALID_PEER_CODE = 40492;
    static const int32 PEER_NO_LONGER_EXISTS = 40493;

    static const int32 CANNOT_MODIFY_TOURNAMENT_WITH_LEADERBOARD_SERVICE = 40494;
    static const int32 NO_TOURNAMENT_ASSOCIATED_WITH_LEADERBOARD = 40495;
    static const int32 TOURNAMENT_NOT_ASSOCIATED_WITH_LEADERBOARD = 40496;
    static const int32 PLAYER_ALREADY_TOURNAMENT_FOR_LEADERBOARD = 40497;
    static const int32 PLAYER_EARLY_FOR_JOINING_TOURNAMENT = 40498;
    static const int32 NO_LEADERBOARD_FOUND = 40499;
    static const int32 PLAYER_NOT_IN_TIME_RANGE_FOR_POSTSCORE_TOURNAMENT = 40500;
    static const int32 LEADERBOARD_ID_BAD = 40501;
    static const int32 SCORE_INPUT_BAD = 40502;
    static const int32 ROUND_STARTED_EPOCH_INPUT_BAD = 40503;
    static const int32 TOURNAMENT_CODE_INPUT_BAD = 40504;
    static const int32 PLAYER_NOT_ENROLLED_IN_TOURNAMENT = 40505;
    static const int32 LEADERBOARD_VERSION_ID_INVALID = 40506;
    static const int32 NOT_ENOUGH_BALANCE_TO_JOIN_TOURNAMENT = 40507;
    static const int32 PARENT_ALREADY_ATTACHED = 40508;
    static const int32 PEER_ALREADY_ATTACHED = 40509;
    static const int32 IDENTITY_NOT_ATTACHED_WITH_PARENT = 40510;
    static const int32 IDENTITY_NOT_ATTACHED_WITH_PEER = 40511;
    static const int32 LEADERBOARD_SCORE_UPDATE_ERROR = 40512;
    static const int32 ERROR_CLAIMING_REWARD = 40513;
    static const int32 NOT_ENOUGH_PARENT_BALANCE_TO_JOIN_TOURNAMENT = 40514;
    static const int32 NOT_ENOUGH_PEER_BALANCE_TO_JOIN_TOURNAMENT = 40515;
    static const int32 PLAYER_LATE_FOR_JOINING_TOURNAMENT = 40516;
    static const int32 VIEWING_REWARD_FOR_NON_PROCESSED_TOURNAMENTS = 40517;
    static const int32 NO_REWARD_ASSOCIATED_WITH_LEADERBOARD = 40518;
    static const int32 PROFILE_PEER_NOT_FOUND = 40519;
    static const int32 LEADERBOARD_IN_ACTIVE_STATE = 40520;
    static const int32 LEADERBOARD_IN_CALCULATING_STATE = 40521;
    static const int32 TOURNAMENT_RESULT_PROCESSING_FAILED = 40522;
    static const int32 TOURNAMENT_REWARDS_ALREADY_CLAIMED = 40523;
    static const int32 NO_TOURNAMENT_FOUND = 40524;
    static const int32 UNEXPECTED_ERROR_RANK_ZERO_AFTER_PROCESSING = 40525;
    static const int32 UNEXPECTED_ERROR_DELETING_TOURNAMENT_LEADERBOARD_SCORE = 40526;
    static const int32 INVALID_RUN_STATE = 40527;
    static const int32 LEADERBOARD_SCORE_DOESNOT_EXIST = 40528;
    static const int32 INITIAL_SCORE_NULL = 40529;

	static const int32 UPLOLAD_IN_PROGRESS = 40724;
	static const int32 REFRESH_IN_PROGRESS = 40725;
	static const int32 REFRESH_INTERRUPTED = 40726;
	static const int32 GAMELIFT_ERROR = 40727;
	static const int32 GAMELIFT_LAUNCH_ERROR = 40728;
	static const int32 MAX_HOSTED_SERVERS_REACHED = 40729;
	static const int32 DUPLICATE_PACKET_ID = 40730;
	static const int32 FEATURE_NOT_SUPPORTED_BY_BILLING_PLAN = 40731;
	static const int32 NO_FRIENDS_FOUND = 40740;
	static const int32 PRODUCT_TRANSACTION_NOT_FOUND = 40741;
	static const int32 ITEM_DEF_NOT_FOUND = 40742;
	static const int32 ITEM_DEF_HAS_DEPENDENCIES = 40743;
	static const int32 TRANSFER_JOB_IDLE_TIMEOUT = 40744;
	static const int32 GROUP_MEMBER_ACL_MORE_RESTRICTIVE_THAN_OTHER = 40745;
	static const int32 GROUP_MEMBER_ACL_MUST_BE_READ_WRITE_FOR_UNOWNED_ENTITY = 40746;
	static const int32 GROUP_MEMBER_ACL_REQUIRED = 40747;
	static const int32 GROUP_TYPE_MAX_MEMBERS_EXCEEDED = 40748;
	
	static const int32 INVALID_LEADERBOARD_TOURNAMENT_SETTING = 40840;
	static const int32 LEADERBOARD_EDIT_TOURNAMENT_SETTINGS_ERROR = 40841;
	static const int32 LEADERBOARD_SCORES_EXIST = 40842;
	static const int32 TOURNAMENT_SCORES_EXIST = 40843;
	static const int32 LEADERBOARD_DBVERSION_MISMATCH = 40844;
	static const int32 LEADERBOARD_API_DOES_NOT_APPLY = 40845;

	static const int32 SCRIPT_DUPLICATE_EXISTS = 40908;
	static const int32 INVALID_UPLOAD_EXTENSION = 40909;

    static const int32 NO_TWITTER_CONSUMER_KEY = 500001;
    static const int32 NO_TWITTER_CONSUMER_SECRET = 500002;
    static const int32 INVALID_CONFIGURATION = 500003;
    static const int32 ERROR_GETTING_REQUEST_TOKEN = 500004;
    static const int32 ERROR_GETTING_ACCESS_TOKEN = 500005;

    static const int32 FACEBOOK_ERROR = 500010;
    static const int32 FACEBOOK_SECRET_MISMATCH = 500011;
    static const int32 FACEBOOK_AUTHENTICATION_ERROR = 500012;
    static const int32 FACEBOOK_APPLICATION_TOKEN_REQUEST_ERROR = 500013;
    static const int32 FACEBOOK_BAD_APPLICATION_TOKEN_SIGNATURE = 500014;

    static const int32 MONGO_DB_EXCEPTION = 600001;
	static const int32 BUILDER_API_CREATED_AT_MISMATCH = 60111;
	
    // RTT 
    static const int32 RTT_LEFT_BY_CHOICE = 80000;
    static const int32 RTT_EVICTED = 80001;
    static const int32 RTT_LOST_CONNECTION = 80002;
    static const int32 RTT_TIMEOUT = 80100;
    static const int32 RTT_ROOM_READY = 80101;
    static const int32 RTT_ROOM_CANCELLED = 80102;
    static const int32 RTT_ERROR_ASSIGNING_ROOM = 80103;
    static const int32 RTT_ERROR_LAUNCHING_ROOM = 80104;
    static const int32 RTT_NO_LOBBIES_FOUND = 80200;
    static const int32 RTT_CLIENT_ERROR = 80300;

    // Client defined value for a timeout detected client-side.
    static const int32 CLIENT_NETWORK_ERROR_TIMEOUT = 90001;
    static const int32 CLIENT_UPLOAD_FILE_CANCELLED = 90100;
    static const int32 CLIENT_UPLOAD_FILE_TIMED_OUT = 90101;
    static const int32 CLIENT_UPLOAD_FILE_UNKNOWN = 90102;
    static const int32 CLIENT_DISABLED = 90200;

    // RS
    static const int32 RS_CLIENT_ERROR = 90300;
};

using ReasonCode = ReasonCodes;
