//
//  URLRequest.cpp
//  GameClientLib
//


#include "URLRequest.h"


/**
 * Constructor
 */
URLRequest::URLRequest( std::string const & url )
    : _authenticate(false), _cacheResponse(false), _contentType("text/json"),
      _followRedirects(false), _idleTimeout(0), _manageCookies(false),
      _method("POST"), _url(url), _useCache(false) {
}  // end URLRequest::URLRequest


/**
 * Destructor
 */
URLRequest::~URLRequest( ) {
}  // end URLRequest::~URLRequest


/*
 * Public Methods
 */


/**
 * Add a new header to the list.
 */
void URLRequest::addHeader( URLRequestHeader const & header ) {
    _requestHeaders.push_back(header);
}  // end URLReqeust::addHeader


/**
 * Set the content type of the request.
 *
 * @param contentType
 */
void URLRequest::setContentType( std::string const & contentType ) {
    _contentType = contentType;
}  // end URLRequest::setData


/**
 * Set the request data.
 *
 * @param data
 */
void URLRequest::setData( std::string const & data ) {
    _data = data;
}  // end URLRequest::setData


/**
 * Set the request method.
 *
 * @param method
 */
void URLRequest::setMethod( std::string const & method ) {
    _method = method;
}  // end URLRequest::setMethod


/**
 * Set the user agent.
 *
 * @param userAgent
 */
void URLRequest::setUserAgent( std::string const & userAgent ) {
    _userAgent = userAgent;
}  // end URLRequest::setUserAgent
