#ifndef _REASONCODES_H_
#define _REASONCODES_H_

// Error codes
static const int NO_REASON_CODE = 0;

static const int INVALID_NOTIFICATION = 20200;

static const int INVALID_REQUEST = 40001;

// 402
static const int SWITCHING_FACEBOOK_MEMORY = 40201;
static const int MERGING_MEMORY = 40202;
static const int RESETING_MEMORY = 40203;
static const int MOVING_ANONYMOUS_MEMORY = 40204;
static const int LOGIN_SECURITY_ERROR = 40205;
static const int MISSING_IDENTITY_ERROR = 40206;
static const int SWITCHING_PROFILES = 40207;
static const int MISSING_PROFILE_ERROR = 40208;

static const int SECURITY_ERROR = 40209;

static const int DOWNGRADING_TO_ANONYMOUS_ERROR = 40210;
static const int DUPLICATE_IDENTITY_TYPE = 40211;
static const int MERGE_PROFILES = 40212;
static const int INVALID_PROPERTY_NAME = 40213;
static const int EMAIL_NOT_VALIDATED = 40214;
static const int DATABASE_ERROR = 40215;
static const int PROPERTY_NOT_OVERRIDEABLE = 40216;
static const int UNKNOWN_AUTH_ERROR = 40217;


// Forbidden (403)... 
static const int UNABLE_TO_GET_FRIENDS_FROM_FACEBOOK = 40300;
static const int BAD_SIGNATURE = 40301;
static const int UNABLE_TO_VALIDATE_PLAYER = 40302;
static const int UNABLE_TO_VALIDATE_USER = UNABLE_TO_VALIDATE_PLAYER;
static const int PLAYER_SESSION_EXPIRED = 40303;
static const int USER_SESSION_EXPIRED = PLAYER_SESSION_EXPIRED;
static const int NO_SESSION = 40304;
static const int PLAYER_SESSION_MISMATCH = 40305;
static const int USER_SESSION_MISMATCH = PLAYER_SESSION_MISMATCH;
static const int OPERATION_REQUIRES_A_SESSION = 40306;
static const int TOKEN_DOES_NOT_MATCH_USER = 40307;
static const int EVENT_CAN_ONLY_SEND_TO_FRIEND_OR_SELF = 40309;
static const int NOT_FRIENDS = 40310;
static const int VC_BALANCE_CANNOT_BE_SPECIFIED = 40311;
static const int VC_LIMIT_EXCEEDED = 40312;
static const int UNABLE_TO_GET_MY_DATA_FROM_FACEBOOK = 40313;
static const int INVALID_AUTHENTICATION_TYPE = 40315;
static const int INVALID_GAME_ID = 40316;
static const int INVALID_APP_ID = INVALID_GAME_ID;

// This product and receipt have already been claimed
static const int APPLE_TRANS_ID_ALREADY_CLAIMED = 40317;
// @deprecated - use APPLE_TRANS_ID_ALREADY_CLAIMED
static const int ITUNES_PURCHASE_ALREADY_CLAIMED = APPLE_TRANS_ID_ALREADY_CLAIMED;

// 400 Bad version
static const int CLIENT_VERSION_NOT_SUPPORTED = 40318;
static const int BRAINCLOUD_VERSION_NOT_SUPPORTED = 40319;
static const int PLATFORM_NOT_SUPPORTED = 40320;

static const int INVALID_PLAYER_STATISTICS_EVENT_NAME = 40321;
static const int INVALID_USER_STATISTICS_EVENT_NAME = INVALID_PLAYER_STATISTICS_EVENT_NAME;

// Game Version No Longer Supported
static const int GAME_VERSION_NOT_SUPPORTED = 40322;
static const int APP_VERSION_NOT_SUPPORTED = GAME_VERSION_NOT_SUPPORTED;
// @deprecated - use GAME_VERSION_NOT_SUPPORTED
static const int APP_VERSION_NO_LONGER_SUPPORTED = GAME_VERSION_NOT_SUPPORTED;

static const int BAD_REFERENCE_DATA = 40324;
static const int MISSING_OAUTH_TOKEN = 40325;
static const int MISSING_OAUTH_VERIFIER = 40326;
static const int MISSING_OAUTH_TOKEN_SECRET = 40327;
static const int MISSING_TWEET = 40328;
static const int FACEBOOK_PAYMENT_ID_ALREADY_PROCESSED = 40329;
static const int DISABLED_GAME = 40330;
static const int DISABLED_APP = DISABLED_GAME;
static const int MATCH_MAKING_DISABLED = 40331;
static const int UPDATE_FAILED = 40332;
static const int INVALID_OPERATION = 40333; // invalid operation for API call
static const int MATCH_RANGE_ERROR = 40334;
static const int PLAYER_IN_MATCH = 40335;
static const int MATCH_PLAYER_SHIELDED = 40336;
static const int MATCH_PLAYER_MISSING = 40337;
static const int MATCH_PLAYER_LOGGED_IN = 40338;
static const int INVALID_ITEM_ID = 40339;
static const int MISSING_PRICE = 40340;
static const int MISSING_USER_INFO = 40341;
static const int MISSING_STEAM_RESPONSE = 40342;
static const int MISSING_STEAM_TRANSACTION = 40343;
static const int ENTITY_VERSION_MISMATCH = 40344;
static const int MISSING_RECORD = 40345;
static const int INSUFFICIENT_PERMISSIONS = 40346;
static const int MISSING_IN_QUERY = 40347;
static const int RECORD_EXPIRED = 40348;
static const int INVALID_WHERE = 40349;
static const int S3_ERROR = 40350;
static const int INVALID_ATTRIBUTES = 40351;
static const int IMPORT_MISSING_GAME_DATA = 40352;
static const int IMPORT_MISSING_APP_DATA = IMPORT_MISSING_GAME_DATA;
static const int IMPORT_SCHEMA_VERSION_TOO_OLD = 40353;
static const int IMPORT_SCHEMA_VERSION_INVALID = 40355;
static const int PLAYER_SESSION_LOGGED_OUT = 40356;
static const int USER_SESSION_LOGGED_OUT = PLAYER_SESSION_LOGGED_OUT;
static const int API_HOOK_SCRIPT_ERROR = 40357;
static const int MISSING_REQUIRED_PARAMETER = 40358;
static const int INVALID_PARAMETER_TYPE = 40359;
static const int INVALID_IDENTITY_TYPE = 40360;
static const int EMAIL_SEND_ERROR = 40361;
static const int CHILD_ENTITY_PARTIAL_UPDATE_INVALID_DATA = 40362;
static const int MISSING_SCRIPT = 40363;
static const int SCRIPT_SECURITY_ERROR = 40364;
static const int SERVER_SESSION_EXPIRED = 40365;
static const int STREAM_DOES_NOT_EXIT = 40366;
static const int STREAM_ACCESS_ERROR = 40367;
static const int STREAM_COMPLETE = 40368;
static const int INVALID_STATISTIC_NAME = 40369;
static const int INVALID_HTTP_REQUEST = 40370;
static const int GAME_LIMIT_REACHED = 40371;
static const int APP_LIMIT_REACHED = GAME_LIMIT_REACHED;
static const int GAME_RUNSTATE_DISABLED = 40372;
static const int APP_RUNSTATE_DISABLED = GAME_RUNSTATE_DISABLED;
static const int INVALID_COMPANY_ID = 40373;
static const int INVALID_PLAYER_ID = 40374;
static const int INVALID_USER_ID = INVALID_PLAYER_ID;
static const int INVALID_TEMPLATE_ID = 40375;
static const int MINIMUM_SEARCH_INPUT = 40376;
static const int MISSING_GAME_PARENT = 40377;
static const int MISSING_APP_PARENT = MISSING_GAME_PARENT;
static const int GAME_PARENT_MISMATCH = 40378;
static const int APP_PARENT_MISMATCH = GAME_PARENT_MISMATCH;
static const int CHILD_PLAYER_MISSING = 40379;
static const int CHILD_USER_MISSING = CHILD_PLAYER_MISSING;
static const int MISSING_PLAYER_PARENT = 40380;
static const int MISSING_USER_PARENT = MISSING_PLAYER_PARENT;
static const int PLAYER_PARENT_MISMATCH = 40381;
static const int USER_PARENT_MISMATCH = PLAYER_PARENT_MISMATCH;
static const int MISSING_PLAYER_ID = 40382;
static const int MISSING_USER_ID = MISSING_PLAYER_ID;
static const int DECODE_CONTEXT = 40383;
static const int INVALID_QUERY_CONTEXT = 40384;
static const int GROUP_MEMBER_NOT_FOUND = 40385;
static const int INVALID_SORT = 40386;
static const int GAME_NOT_FOUND = 40387;
static const int APP_NOT_FOUND = GAME_NOT_FOUND;
static const int GAMES_NOT_IN_SAME_COMPANY = 40388;
static const int APPS_NOT_IN_SAME_COMPANY = GAMES_NOT_IN_SAME_COMPANY;
static const int IMPORT_NO_PARENT_ASSIGNED = 40389;
static const int IMPORT_PARENT_CURRENCIES_MISMATCH = 40390;
static const int INVALID_SUBSTITUION_ENTRY = 40391;
static const int INVALID_TEMPLATE_STRING = 40392;
static const int TEMPLATE_SUBSTITUTION_ERROR = 40393;
static const int INVALID_OPPONENTS = 40394;
static const int REDEMPTION_CODE_NOT_FOUND = 40395;
static const int REDEMPTION_CODE_VERSION_MISMATCH = 40396;
static const int REDEMPTION_CODE_ACTIVE = 40397;
static const int REDEMPTION_CODE_NOT_ACTIVE = 40398;
static const int REDEMPTION_CODE_TYPE_NOT_FOUND = 40399;
static const int REDEMPTION_CODE_INVALID = 40400;
static const int REDEMPTION_CODE_REDEEMED = 40401;
static const int REDEMPTION_CODE_REDEEMED_BY_SELF = 40402;
static const int REDEMPTION_CODE_REDEEMED_BY_OTHER = 40403;
static const int SCRIPT_EMPTY = 40404;
static const int ITUNES_COMMUNICATION_ERROR = 40405;
static const int ITUNES_NO_RESPONSE = 40406;
static const int ITUNES_RESPONSE_NOT_OK = 40407;
static const int JSON_PARSING_ERROR = 40408;
static const int ITUNES_NULL_RESPONSE = 40409;
static const int ITUNES_RESPONSE_WITH_NULL_STATUS = 40410;
static const int ITUNES_STATUS_BAD_JSON_RECEIPT = 40411;
static const int ITUNES_STATUS_BAD_RECEIPT = 40412;
static const int ITUNES_STATUS_RECEIPT_NOT_AUTHENTICATED = 40413;
static const int ITUNES_STATUS_BAD_SHARED_SECRET = 40414;
static const int ITUNES_STATUS_RECEIPT_SERVER_UNAVAILABLE = 40415;
static const int ITUNES_RECEIPT_MISSING_ITUNES_PRODUCT_ID = 40416;
static const int PRODUCT_NOT_FOUND_FOR_ITUNES_PRODUCT_ID = 40417;
static const int DATA_STREAM_EVENTS_NOT_ENABLED = 40418;
static const int INVALID_DEVICE_TOKEN = 40419;
static const int ERROR_DELETING_DEVICE_TOKEN = 40420;
static const int WEBPURIFY_NOT_CONFIGURED = 40421;
static const int WEBPURIFY_EXCEPTION = 40422;
static const int WEBPURIFY_FAILURE = 40423;
static const int WEBPURIFY_NOT_ENABLED = 40424;
static const int NAME_CONTAINS_PROFANITY = 40425;
static const int NULL_SESSION = 40426;
static const int PURCHASE_ALREADY_VERIFIED = 40427;
static const int GOOGLE_IAP_NOT_CONFIGURED = 40428;
static const int UPLOAD_FILE_TOO_LARGE = 40429;
static const int FILE_ALREADY_EXISTS = 40430;
static const int CLOUD_STORAGE_SERVICE_ERROR = 40431;
static const int FILE_DOES_NOT_EXIST = 40432;
static const int UPLOAD_ID_MISSING = 40433;
static const int UPLOAD_JOB_MISSING = 40434;
static const int UPLOAD_JOB_EXPIRED = 40435;
static const int UPLOADER_EXCEPTION = 40436;
static const int UPLOADER_FILESIZE_MISMATCH = 40437;
static const int PUSH_NOTIFICATIONS_NOT_CONFIGURED = 40438;
static const int MATCHMAKING_FILTER_SCRIPT_FAILURE = 40439;
static const int ACCOUNT_ALREADY_EXISTS = 40440;
static const int PROFILE_ALREADY_EXISTS = 40441;
static const int MISSING_NOTIFICATION_BODY = 40442;
static const int INVALID_SERVICE_CODE = 40443;
static const int IP_ADDRESS_BLOCKED = 40444;
static const int UNAPPROVED_SERVICE_CODE = 40445;
static const int PROFILE_NOT_FOUND = 40446;
static const int ENTITY_NOT_SHARED = 40447;
static const int SELF_FRIEND = 40448;
static const int PARSE_NOT_CONFIGURED = 40449;
static const int PARSE_NOT_ENABLED = 40450;
static const int PARSE_REQUEST_ERROR = 40451;
static const int GROUP_CANNOT_ADD_OWNER = 40452;
static const int NOT_GROUP_MEMBER = 40453;
static const int INVALID_GROUP_ROLE = 40454;
static const int GROUP_OWNER_DELETE = 40455;
static const int NOT_INVITED_GROUP_MEMBER = 40456;
static const int GROUP_IS_FULL = 40457;
static const int GROUP_OWNER_CANNOT_LEAVE = 40458;
static const int INVALID_INCREMENT_VALUE = 40459;
static const int GROUP_VERSION_MISMATCH = 40460;
static const int GROUP_ENTITY_VERSION_MISMATCH = 40461;
static const int INVALID_GROUP_ID = 40462;
static const int INVALID_FIELD_NAME = 40463;
static const int UNSUPPORTED_AUTH_TYPE = 40464;
static const int CLOUDCODE_JOB_NOT_FOUND = 40465;
static const int CLOUDCODE_JOB_NOT_SCHEDULED = 40466;
static const int GROUP_TYPE_NOT_FOUND = 40467;
static const int MATCHING_GROUPS_NOT_FOUND = 40468;
static const int GENERATE_CDN_URL_ERROR = 40469;
static const int INVALID_PROFILE_IDS = 40470;
static const int MAX_PROFILE_IDS_EXCEEDED = 40471;
static const int PROFILE_ID_MISMATCH = 40472;
static const int LEADERBOARD_DOESNOT_EXIST = 40473;
static const int APP_LICENSING_EXCEEDED = 40474;
static const int SENDGRID_NOT_INSTALLED = 40475;
static const int SENDGRID_EMAIL_SEND_ERROR = 40476;
static const int SENDGRID_NOT_ENABLED_FOR_APP = 40477;
static const int SENDGRID_GET_TEMPLATES_ERROR = 40478;
static const int SENDGRID_INVALID_API_KEY = 40479;
static const int EMAIL_SERVICE_NOT_CONFIGURED = 40480;
static const int INVALID_EMAIL_TEMPLATE_TYPE = 40481;
static const int SENDGRID_KEY_EMPTY_OR_NULL = 40482;
static const int BODY_TEMPLATE_CANNOT_COEXIST = 40483;
static const int SUBSTITUTION_BODY_CANNOT_COEXIST = 40484;
static const int INVALID_FROM_ADDRESS = 40485;
static const int INVALID_FROM_NAME = 40486;
static const int INVALID_REPLY_TO_ADDRESS = 40487;
static const int INVALID_REPLY_TO_NAME = 40488;
static const int FROM_NAME_WITHOUT_FROM_ADDRESS = 40489;
static const int REPLY_TO_NAME_WITHOUT_REPLY_TO_ADDRESS = 40490;
static const int CURRENCY_SECURITY_ERROR = 40491;
static const int INVALID_PEER_CODE = 40492;
static const int PEER_NO_LONGER_EXISTS = 40493;

static const int CANNOT_MODIFY_TOURNAMENT_WITH_LEADERBOARD_SERVICE = 40494;
static const int NO_TOURNAMENT_ASSOCIATED_WITH_LEADERBOARD = 40495;
static const int TOURNAMENT_NOT_ASSOCIATED_WITH_LEADERBOARD = 40496;
static const int PLAYER_ALREADY_TOURNAMENT_FOR_LEADERBOARD = 40497;
static const int PLAYER_EARLY_FOR_JOINING_TOURNAMENT = 40498;
static const int NO_LEADERBOARD_FOUND = 40499;
static const int PLAYER_NOT_IN_TIME_RANGE_FOR_POSTSCORE_TOURNAMENT = 40500;
static const int LEADERBOARD_ID_BAD = 40501;
static const int SCORE_INPUT_BAD = 40502;
static const int ROUND_STARTED_EPOCH_INPUT_BAD = 40503;
static const int TOURNAMENT_CODE_INPUT_BAD = 40504;
static const int PLAYER_NOT_ENROLLED_IN_TOURNAMENT = 40505;
static const int LEADERBOARD_VERSION_ID_INVALID = 40506;
static const int NOT_ENOUGH_BALANCE_TO_JOIN_TOURNAMENT = 40507;
static const int PARENT_ALREADY_ATTACHED = 40508;
static const int PEER_ALREADY_ATTACHED = 40509;
static const int IDENTITY_NOT_ATTACHED_WITH_PARENT = 40510;
static const int IDENTITY_NOT_ATTACHED_WITH_PEER = 40511;
static const int LEADERBOARD_SCORE_UPDATE_ERROR = 40512;
static const int ERROR_CLAIMING_REWARD = 40513;
static const int NOT_ENOUGH_PARENT_BALANCE_TO_JOIN_TOURNAMENT = 40514;
static const int NOT_ENOUGH_PEER_BALANCE_TO_JOIN_TOURNAMENT = 40515;
static const int PLAYER_LATE_FOR_JOINING_TOURNAMENT = 40516;
static const int VIEWING_REWARD_FOR_NON_PROCESSED_TOURNAMENTS = 40517;
static const int NO_REWARD_ASSOCIATED_WITH_LEADERBOARD = 40518;
static const int PROFILE_PEER_NOT_FOUND = 40519;
static const int LEADERBOARD_IN_ACTIVE_STATE = 40520;
static const int LEADERBOARD_IN_CALCULATING_STATE = 40521;
static const int TOURNAMENT_RESULT_PROCESSING_FAILED = 40522;
static const int TOURNAMENT_REWARDS_ALREADY_CLAIMED = 40523;
static const int NO_TOURNAMENT_FOUND = 40524;
static const int UNEXPECTED_ERROR_RANK_ZERO_AFTER_PROCESSING = 40525;
static const int UNEXPECTED_ERROR_DELETING_TOURNAMENT_LEADERBOARD_SCORE = 40526;
static const int INVALID_RUN_STATE = 40527;
static const int LEADERBOARD_SCORE_DOESNOT_EXIST = 40528;
static const int INITIAL_SCORE_NULL = 40529;
static const int TOURNAMENT_NOTIFICATIONS_PROCESSING_FAILED = 40530;
static const int ACL_NOT_READABLE = 40531;
static const int INVALID_OWNER_ID = 40532;
static const int IMPORT_MISSING_PEERS_DATA = 40533;
static const int INVALID_CREDENTIAL = 40534;

static const int NO_TWITTER_CONSUMER_KEY = 500001;
static const int NO_TWITTER_CONSUMER_SECRET = 500002;
static const int INVALID_CONFIGURATION = 500003;
static const int ERROR_GETTING_REQUEST_TOKEN = 500004;
static const int ERROR_GETTING_ACCESS_TOKEN = 500005;

static const int FACEBOOK_ERROR = 500010;
static const int FACEBOOK_SECRET_MISMATCH = 500011;
static const int FACEBOOK_AUTHENTICATION_ERROR = 500012;
static const int FACEBOOK_APPLICATION_TOKEN_REQUEST_ERROR = 500013;
static const int FACEBOOK_BAD_APPLICATION_TOKEN_SIGNATURE = 500014;

static const int MONGO_DB_EXCEPTION = 600001;

// Client defined value for a timeout detected client-side.
static const int CLIENT_NETWORK_ERROR_TIMEOUT = 90001;
static const int CLIENT_UPLOAD_FILE_CANCELLED = 90100;
static const int CLIENT_UPLOAD_FILE_TIMED_OUT = 90101;
static const int CLIENT_UPLOAD_FILE_UNKNOWN = 90102;
static const int CLIENT_DISABLED = 90200;

#endif