//
//  URLResponse.cpp
//  GameClientLib
//


#include "URLResponse.h"


/**
 * Constructor
 */
URLResponse::URLResponse( std::string const & url )
    : _contentType("text/html"), _reasonPhrase("OK"), _statusCode(200) {
}  // end URLResponse::URLResponse


/**
 * Destructor
 */
URLResponse::~URLResponse( ) {
}  // end URLResponse::~URLResponse


/*
 * Public Methods
 */


/**
 * Add content data to the HTTP response.
 */
void URLResponse::addData( std::string const & data ) {
    _data.append(data);
}  // end URLResponse::addData


/**
 * Add a new header to the list.
 *
 * @param header - HTTP request header
 */
void URLResponse::addHeader( URLRequestHeader const & header ) {
    _responseHeaders.push_back(header);
}  // end URLResponse::addHeader


/**
 * Set the content type of the response.
 *
 * @param contentType
 */
void URLResponse::setContentType( std::string const & contentType ) {
    _contentType = contentType;
}  // end URLResponse::setData


/**
 * Set the reponse data.
 *
 * @param data
 */
void URLResponse::setData( std::string const & data ) {
    _data = data;
}  // end URLResponse::setData


/**
 * Set the phrase describing the status code.
 *
 * @param reasonPhrase
 */
void URLResponse::setReasonPhrase( std::string const & reasonPhrase ) {
    _reasonPhrase = reasonPhrase;
}  // end URLResponse::setReasonPhrase


/**
 * Set the status code of the response.
 *
 * @param statusCode
 */
void URLResponse::setStatusCode( unsigned short statusCode ) {
    _statusCode = statusCode;
}  // end URLResponse::setStatusCode