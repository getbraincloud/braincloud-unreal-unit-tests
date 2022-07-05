#pragma once

class BCCLIENTPLUGIN_API HttpCode
{
  public:
    static const int ACCEPTED = 202;          // HTTP Status-Code 202: Accepted.
    static const int BAD_GATEWAY = 502;       // HTTP Status-Code 502: Bad Gateway.
    static const int BAD_METHOD = 405;        // HTTP Status-Code 405: Method Not Allowed.
    static const int BAD_REQUEST = 400;       // HTTP Status-Code 400: Bad Request.
    static const int CLIENT_TIMEOUT = 408;    // HTTP Status-Code 408: Request Time-Out.
    static const int CONFLICT = 409;          // HTTP Status-Code 409: Conflict.
    static const int CREATED = 201;           // HTTP Status-Code 201: Created.
    static const int ENTITY_TOO_LARGE = 413;  // HTTP Status-Code 413: Request Entity Too Large.
    static const int FORBIDDEN = 403;         // HTTP Status-Code 403: Forbidden.
    static const int GATEWAY_TIMEOUT = 504;   // HTTP Status-Code 504: Gateway Timeout.
    static const int GONE = 410;              // HTTP Status-Code 410: Gone.
    static const int INTERNAL_ERROR = 500;    // HTTP Status-Code 500: Internal Server Error.
    static const int LENGTH_REQUIRED = 411;   // HTTP Status-Code 411: Length Required.
    static const int MOVED_PERM = 301;        // HTTP Status-Code 301: Moved Permanently.
    static const int MOVED_TEMP = 302;        // HTTP Status-Code 302: Temporary Redirect.
    static const int MULT_CHOICE = 300;       // HTTP Status-Code 300: Multiple Choices.
    static const int NO_CONTENT = 204;        // HTTP Status-Code 204: No Content.
    static const int NOT_ACCEPTABLE = 406;    // HTTP Status-Code 406: Not Acceptable.
    static const int NOT_AUTHORITATIVE = 203; // HTTP Status-Code 203: Non-Authoritative Information.
    static const int NOT_FOUND = 404;         // HTTP Status-Code 404: Not Found.
    static const int NOT_IMPLEMENTED = 501;   // HTTP Status-Code 501: Not Implemented.
    static const int NOT_MODIFIED = 304;      // HTTP Status-Code 304: Not Modified.
    static const int OK = 200;                // HTTP Status-Code 200: OK.
    static const int PARTIAL = 206;           // HTTP Status-Code 206: Partial Content.
    static const int PAYMENT_REQUIRED = 402;  // HTTP Status-Code 402: Payment Required.
    static const int PRECON_FAILED = 412;     // HTTP Status-Code 412: Precondition Failed.
    static const int PROXY_AUTH = 407;        // HTTP Status-Code 407: Proxy Authentication Required.
    static const int REQ_TOO_LONG = 414;      // HTTP Status-Code 414: Request-URI Too Large.
    static const int RESET = 205;             // HTTP Status-Code 205: Reset Content.
    static const int SEE_OTHER = 303;         // HTTP Status-Code 303: See Other.
    static const int SERVER_ERROR = 500;      // Deprecated. it is misplaced and shouldn't have existed.
    static const int UNAUTHORIZED = 401;      // HTTP Status-Code 401: Unauthorized.
    static const int UNAVAILABLE = 503;       // HTTP Status-Code 503: Service Unavailable.
    static const int UNSUPPORTED_TYPE = 415;  // HTTP Status-Code 415: Unsupported Media Type.
    static const int USE_PROXY = 305;         // HTTP Status-Code 305: Use Proxy.
    static const int VERSION = 505;           // HTTP Status-Code 505: HTTP Version Not Supported.

    static const int CLIENT_NETWORK_ERROR = 900; // A custom status code raised internally by bc client
};