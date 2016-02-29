//
//  URLResponse.h
//  GameClientLib
//


#ifndef _URLRESPONSE_H_
#define _URLRESPONSE_H_


#include <string>
#include <vector>
#include "URLRequestHeader.h"


class URLResponse {

public:
    URLResponse( std::string const & = std::string() );
    virtual ~URLResponse( );

    void        addData( std::string const & );
    void        addHeader( URLRequestHeader const & );
    const std::string & getContentType( ) const     { return _contentType; }
    const std::string & getData( ) const            { return _data; }
    const std::vector<URLRequestHeader> & getHeaders( ) const
                                            { return _responseHeaders; }
    const std::string & getReasonPhrase( ) const    { return _reasonPhrase; }
    unsigned short  getStatusCode( ) const  { return _statusCode; }

    void        setContentType( std::string const & );
    void        setData( std::string const & );
    void        setReasonPhrase( std::string const & );
    void        setStatusCode( unsigned short );

protected:

private:
    std::string                     _contentType;
    std::string                     _data;
    std::string                     _reasonPhrase;
    std::vector<URLRequestHeader>   _responseHeaders;
    unsigned short                  _statusCode;

};  // end class


#endif  // _URLRESPONSE_H_
