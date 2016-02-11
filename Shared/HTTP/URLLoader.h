//
//  URLLoader.h
//  GameClientLib
//


#ifndef _URLLOADER_H_
#define _URLLOADER_H_


#include "URLLoaderClient.h"
#include "URLRequest.h"


class URLLoader {

public:
    // Constructors
    URLLoader( URLLoaderClient * = NULL );
    URLLoader( URLLoader const & );

    // Destructor
    virtual ~URLLoader( );

    // Methods which must be overwritten.
    virtual void    close( ) = 0;
    virtual void    load( URLRequest const & ) = 0;
    virtual void    load( URLRequest const * ) = 0;
	virtual void	setTimeout( int milliseconds ) = 0;

    // Common methods.
    URLLoaderClient     * getClient( )          { return _client; }
    URLRequest const    getRequest( ) const     { return _urlRequest; }
    void    setClient( URLLoaderClient * c )    { _client = c; }
    void    setRequest( URLRequest const & r)   { _urlRequest = r; }

protected:

private:
	URLLoaderClient * _client;
    URLRequest      _urlRequest;

};  // end class


#endif  // _URLLOADER_H_
