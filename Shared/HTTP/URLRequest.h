//
//  URLRequest.h
//  GameClientLib
//


#ifndef _URLREQUEST_H_
#define _URLREQUEST_H_


#include <string>
#include <vector>
#include "URLRequestHeader.h"


class URLRequest {

public:
    URLRequest( std::string const & = std::string() );
    virtual ~URLRequest( );

    void        addHeader( URLRequestHeader const & );
    bool        authenticate( ) const       { return _authenticate; }
    bool        cacheResponse( ) const      { return _cacheResponse; }
    bool        followRedirects( ) const    { return _followRedirects; }
    std::string getContentType( ) const     { return _contentType; }
    std::string getData( ) const            { return _data; }
    std::vector<URLRequestHeader>   getHeaders( ) const
                                            { return _requestHeaders; }
    int         getIdleTimeout( ) const     { return _idleTimeout; }
    std::string getMethod( ) const          { return _method; }
    std::string getUrl( ) const             { return _url; }
    std::string getUserAgent( ) const       { return _userAgent; }
    bool        manageCookies( ) const      { return _manageCookies; }
    bool        useCache( ) const           { return _useCache; }

    void        setContentType( std::string const & );
    void        setData( std::string const & );
    void        setMethod( std::string const & );
    void        setUserAgent( std::string const & );

protected:

private:
    bool                            _authenticate;
    bool                            _cacheResponse;
    std::string                     _contentType;
    std::string                     _data;
    bool                            _followRedirects;
    int                             _idleTimeout;
    bool                            _manageCookies;
    std::string                     _method;
    std::vector<URLRequestHeader>   _requestHeaders;
    std::string                     _url;
    bool                            _useCache;
    std::string                     _userAgent;

};  // end class


#endif  // _URLREQUEST_H_
